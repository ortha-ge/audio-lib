
export module Audio.SystemsService;

import kangaru;
import Core.EnTTRegistryService;
import Core.SchedulerService;
export import Audio.Systems;

export namespace Audio {

    class AudioSystemsService : public kgr::single_service<AudioSystems, kgr::dependency<Core::EnTTRegistryService, Core::SchedulerService>>{};

} // Audio
