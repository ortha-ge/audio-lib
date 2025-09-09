
export module Audio.PlaySoundSourceRequest;

export namespace Audio {

	struct PlaySoundSourceRequest {
		float volumeScale{ 1.0f };
		bool looping{ false };
	};

} // namespace Audio
