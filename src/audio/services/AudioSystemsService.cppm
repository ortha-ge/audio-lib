
export module Audio.SystemsService;

export import Audio.Systems;

import kangaru;
import Core.EnTTRegistryService;
import Core.SchedulerService;

export namespace Audio {

	void initAudioSubSystems(AudioSystems&, kgr::container&);

    struct AudioSystemsService
	    : kgr::single_service<AudioSystems>
	    , kgr::autocall<kgr::invoke_method<initAudioSubSystems>>{};

} // Audio
