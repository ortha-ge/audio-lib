module;

#include <thread>
#include <utility>

#include <entt/entt.hpp>
#include <soloud.h>
#include <soloud_wav.h>

module Audio.SoLoudSystem;

import Audio.AudioSource;
import Audio.PlaySoundSourceRequest;
import Audio.SoundDescriptor;
import Audio.SoundPlayback;
import Core.FileLoadRequest;
import Core.RawDataResource;
import Core.ResourceHandle;
import Core.ResourceHandleUtils;

namespace Audio::SoLoudSystemInternal {

	struct SoLoudAudioSource {
		std::unique_ptr<SoLoud::Wav> wav;
	};

	struct SoLoudSoundPlayback {
		SoLoud::handle mHandle;
	};

} // namespace Audio::SoLoudSystemInternal

namespace Audio {

	SoLoudSystem::SoLoudSystem(Core::EnTTRegistry& registry, Core::Scheduler& scheduler)
		: mRegistry{ registry }
		, mScheduler{ scheduler } {

		mSoloud.init();

		connectCallbacks(registry);

		mTickHandle = mScheduler.schedule([this]() { tick(mRegistry); });
	}

	SoLoudSystem::~SoLoudSystem() {
		using namespace SoLoudSystemInternal;

		mScheduler.unschedule(std::move(mTickHandle));

		disconnectCallbacks(mRegistry);

		mSoloud.stopAll();

		while (mSoloud.getActiveVoiceCount() > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		entt::registry& registry(mRegistry);
		auto audioSourceView = registry.view<SoLoudAudioSource>();
		registry.destroy(audioSourceView.begin(), audioSourceView.end());

		mSoloud.deinit();
	}

	void SoLoudSystem::tick(entt::registry& registry) {
		using namespace SoLoudSystemInternal;

		registry
			.view<const Core::RawDataResource, Audio::SoundDescriptor>(
				entt::exclude<Core::FileLoadRequest, SoLoudAudioSource>)
			.each([&registry](entt::entity entity, const Core::RawDataResource& rawData) {
				auto& soLoudAudioSource{ registry.emplace<SoLoudAudioSource>(entity) };
				soLoudAudioSource.wav = std::make_unique<SoLoud::Wav>();
				soLoudAudioSource.wav->loadMem(rawData.rawData.data(), rawData.size, true, false);
			});

		registry.view<AudioSource, PlaySoundSourceRequest>().each(
			[this, &registry](entt::entity entity, AudioSource& audioSource, const PlaySoundSourceRequest& request) {
				if (!audioSource.soundResource) {
					return;
				}

				const auto* soLoudAudioSource = Core::getResource<SoLoudAudioSource>(registry, audioSource.soundResource);
				if (!soLoudAudioSource) {
					return;
				}

				auto handle = mSoloud.play(*soLoudAudioSource->wav, request.volumeScale);
				mSoloud.setLooping(handle, request.looping);

				registry.erase<PlaySoundSourceRequest>(entity);
				registry.emplace<SoLoudSoundPlayback>(entity, handle);
				registry.emplace<SoundPlayback>(entity);
			});
	}

	void SoLoudSystem::connectCallbacks(entt::registry& registry) {
		using namespace SoLoudSystemInternal;

		registry.on_destroy<SoundPlayback>()
			.connect<&SoLoudSystem::removeSoLoudSoundPlayback>(this);

		registry.on_destroy<SoLoudSoundPlayback>()
			.connect<&SoLoudSystem::stopSoLoudSoundPlayback>(this);
	}

	void SoLoudSystem::disconnectCallbacks(entt::registry& registry) {
		using namespace SoLoudSystemInternal;

		registry.on_destroy<SoLoudSoundPlayback>()
					.disconnect<&SoLoudSystem::stopSoLoudSoundPlayback>(this);

		registry.on_destroy<SoundPlayback>()
			.disconnect<&SoLoudSystem::removeSoLoudSoundPlayback>(this);
	}

	void SoLoudSystem::removeSoLoudSoundPlayback(entt::registry& registry, const entt::entity entity) {
		using namespace SoLoudSystemInternal;

		if (!registry.all_of<SoLoudSoundPlayback>(entity)) {
			return;
		}

		registry.remove<SoLoudSoundPlayback>(entity);
	}

	void SoLoudSystem::stopSoLoudSoundPlayback(entt::registry& registry, const entt::entity entity) {
		using namespace SoLoudSystemInternal;

		if (!registry.all_of<SoLoudSoundPlayback>(entity)) {
			return;
		}

		auto& soLoudPlayback{ registry.get<SoLoudSoundPlayback>(entity) };
		mSoloud.stop(soLoudPlayback.mHandle);
	}

} // namespace Audio
