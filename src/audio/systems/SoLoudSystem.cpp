module;

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
		// BUG: Wav data seems to be used after shutdown, deleting causes crash.
		SoLoud::Wav* wav{nullptr};
	};

	SoLoudSystem::SoLoudSystem(Core::EnTTRegistry& registry, Core::Scheduler& scheduler) :
		mRegistry{registry}, mScheduler{scheduler} {

		mSoloud.init();
		mTickHandle = mScheduler.schedule([this]() { tick(mRegistry); });
	}

	SoLoudSystem::~SoLoudSystem() {
		mScheduler.unschedule(std::move(mTickHandle));
		mSoloud.stopAll();
		mSoloud.deinit();
	}

	void SoLoudSystem::tick(entt::registry& registry) {
		auto createSoundResourceView = registry.view<const Core::RawDataResource, Audio::SoundDescriptor>(
				entt::exclude<Core::FileLoadRequest, SoLoudAudioSource>);
		createSoundResourceView.each([&registry](entt::entity entity, const Core::RawDataResource& rawData) {
			auto& soLoudAudioSource{registry.emplace<SoLoudAudioSource>(entity)};
			soLoudAudioSource.wav = new SoLoud::Wav();
			soLoudAudioSource.wav->loadMem(rawData.rawData.data(), rawData.size, true, false);
		});

		registry.view<AudioSource, PlaySoundSourceRequest>().each(
				[this, &registry](entt::entity entity, AudioSource& audioSource,
								  const PlaySoundSourceRequest& request) {
					if (audioSource.soundResource == entt::null) {
						return;
					}

					if (!registry.all_of<Core::ResourceHandle>(audioSource.soundResource)) {
						return;
					}

					const auto& soundResourceHandle = registry.get<Core::ResourceHandle>(audioSource.soundResource);
					if (soundResourceHandle.mResourceEntity == entt::null ||
						!registry.all_of<SoLoudAudioSource>(soundResourceHandle.mResourceEntity)) {
						return;
					}

					auto& soLoudSource = registry.get<SoLoudAudioSource>(soundResourceHandle.mResourceEntity);

					auto handle = mSoloud.play(*soLoudSource.wav);
					mSoloud.setLooping(handle, request.looping);

					registry.erase<PlaySoundSourceRequest>(entity);
				});
	}

} // namespace Audio
