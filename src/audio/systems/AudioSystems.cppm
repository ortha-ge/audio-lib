
export module Audio.Systems;

import Audio.SoLoudSystem;
import Core.EnTTRegistry;
import Core.Scheduler;

export namespace Audio {

    class AudioSystems {
    public:

        AudioSystems(Core::EnTTRegistry&, Core::Scheduler&);
        ~AudioSystems();

        AudioSystems(AudioSystems&&) = delete;
        AudioSystems& operator=(AudioSystems&&) noexcept = delete;

        AudioSystems(const AudioSystems&) = delete;
        AudioSystems& operator=(const AudioSystems&) = delete;

    private:

        SoLoudSystem mSoLoudSystem;

    };

} // Audio
