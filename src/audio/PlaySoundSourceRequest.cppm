
export module Ortha.Audio.PlaySoundSourceRequest;

export namespace Ortha::Audio {

	struct PlaySoundSourceRequest {
		float volumeScale{ 1.0f };
		bool looping{ false };
		bool stopExistingPlayback{ false };
	};

} // namespace Ortha::Audio
