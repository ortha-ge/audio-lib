module;

#include <utility>

#include <soloud.h>
#include <soloud_wav.h>
#include <entt/entt.hpp>

module Audio.SoLoudSystem;

import Audio.AudioSource;
import Audio.PlaySoundSourceRequest;
import Audio.SoundDescriptor;
import Core.FileLoadRequest;
import Core.RawDataResource;

namespace Audio {

    struct SoLoudAudioSource {
        std::unique_ptr<SoLoud::Wav> wav{};
    };

    SoLoudSystem::SoLoudSystem(Core::EnTTRegistry& registry, Core::Scheduler& scheduler)
        : mRegistry{ registry }
        , mScheduler{ scheduler } {

        mSoloud.init();
        mTickHandle = mScheduler.schedule([this]() {
            tick(mRegistry);
        });
    }

    SoLoudSystem::~SoLoudSystem() {
        mScheduler.unschedule(std::move(mTickHandle));
        mSoloud.deinit();
    }

    void SoLoudSystem::tick(entt::registry& registry) {
        auto createSoundResourceView = registry.view<const Core::RawDataResource, Audio::SoundDescriptor>(entt::exclude<Core::FileLoadRequest, SoLoudAudioSource>);
        createSoundResourceView.each([&registry](entt::entity entity, const Core::RawDataResource& rawData) {
            auto wavSource = std::make_unique<SoLoud::Wav>();
            wavSource->loadMem(const_cast<unsigned char*>(rawData.rawData.data()), rawData.size, true, false);

            registry.emplace<SoLoudAudioSource>(entity, std::move(wavSource));
        });

        auto playSoundSourceRequestView = registry.view<Audio::AudioSource, PlaySoundSourceRequest>();
        playSoundSourceRequestView.each([this, &registry](entt::entity entity, Audio::AudioSource& audioSource, const PlaySoundSourceRequest& request) {
            if (!registry.all_of<SoLoudAudioSource>(audioSource.soundResource)) {
                return;
            }

            auto& soLoudSource = registry.get<SoLoudAudioSource>(audioSource.soundResource);

            auto handle = mSoloud.play(*soLoudSource.wav);
            mSoloud.setLooping(handle, request.looping);

            registry.erase<PlaySoundSourceRequest>(entity);
        });
    }

} // Audio
