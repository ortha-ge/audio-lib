
export module Audio.PlaySoundSourceRequest;

export namespace Audio {

	struct PlaySoundSourceRequest {
		bool looping{ false };
		float volumeScale{ 1.0f };
	};

} // namespace Audio
