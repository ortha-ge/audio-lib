
export module Audio.Systems;

export namespace Audio {

	class AudioSystems {
	public:
		AudioSystems();
		~AudioSystems();

		AudioSystems(AudioSystems&&) = delete;
		AudioSystems& operator=(AudioSystems&&) noexcept = delete;

		AudioSystems(const AudioSystems&) = delete;
		AudioSystems& operator=(const AudioSystems&) = delete;

	};

} // namespace Audio
