
export module Ortha.Audio.SystemsService;

export import Ortha.Audio.Systems;

import kangaru;
import Ortha.Core.EnTTRegistryService;
import Ortha.Core.SchedulerService;

export namespace Ortha::Audio {

	void initAudioSubSystems(AudioSystems&, kgr::container&);

    struct AudioSystemsService
	    : kgr::single_service<AudioSystems>
	    , kgr::autocall<kgr::invoke_method<initAudioSubSystems>>{};

} // Audio
