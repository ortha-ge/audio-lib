
export module Ortha.Audio.Systems;

export namespace Ortha::Audio {

	class AudioSystems {
	public:
		AudioSystems();
		~AudioSystems();

		AudioSystems(AudioSystems&&) = delete;
		AudioSystems& operator=(AudioSystems&&) noexcept = delete;

		AudioSystems(const AudioSystems&) = delete;
		AudioSystems& operator=(const AudioSystems&) = delete;

	};

} // namespace Ortha::Audio
