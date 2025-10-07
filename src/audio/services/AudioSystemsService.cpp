module Ortha.Audio.SystemsService;

import Ortha.Audio.SoLoudSystemService;

namespace Ortha::Audio {

	void initAudioSubSystems(AudioSystems&, kgr::container& container) {
		container.emplace<SoLoudSystemService>();
	}

} // namespace Ortha::Audio
