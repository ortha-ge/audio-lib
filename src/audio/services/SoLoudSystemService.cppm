
export module Audio.SoLoudSystemService;

export import Audio.SoLoudSystem;

import kangaru;
import Core.EnTTRegistryService;
import Core.SchedulerService;

export namespace Audio {

	struct SoLoudSystemService : kgr::single_service<SoLoudSystem, kgr::dependency<Core::EnTTRegistryService, Core::SchedulerService>>{};

} // Audio
