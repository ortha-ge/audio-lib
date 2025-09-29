module Audio.SystemsService;

import Audio.SoLoudSystemService;

namespace Audio {

	void initAudioSubSystems(AudioSystems&, kgr::container& container) {
		container.emplace<SoLoudSystemService>();
	}

} // namespace Audio
