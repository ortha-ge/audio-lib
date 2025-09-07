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
import Core.FileLoadRequest;
import Core.RawDataResource;
import Core.ResourceHandle;

namespace Audio {

	struct SoLoudAudioSource {
		std::unique_ptr<SoLoud::Wav> wav;
	};

	SoLoudSystem::SoLoudSystem(Core::EnTTRegistry& registry, Core::Scheduler& scheduler)
		: mRegistry{ registry }
		, mScheduler{ scheduler } {

		mSoloud.init();
		mTickHandle = mScheduler.schedule([this]() { tick(mRegistry); });
	}

	SoLoudSystem::~SoLoudSystem() {
		mScheduler.unschedule(std::move(mTickHandle));
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
				if (audioSource.soundResource == entt::null) {
					return;
				}

				if (!registry.all_of<Core::ResourceHandle>(audioSource.soundResource)) {
					return;
				}

				const auto* soLoudAudioSource = Core::getResource<SoLoudAudioSource>(registry, audioSource.soundResource);
				if (!soLoudAudioSource) {
					return;
				}

				auto handle = mSoloud.play(*soLoudAudioSource->wav, request.volumeScale);
				mSoloud.setLooping(handle, request.looping);

				registry.erase<PlaySoundSourceRequest>(entity);
			});
	}

} // namespace Audio
