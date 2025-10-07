
export module Ortha.Audio.SoLoudSystemService;

export import Ortha.Audio.SoLoudSystem;

import kangaru;
import Ortha.Core.EnTTRegistryService;
import Ortha.Core.SchedulerService;

export namespace Ortha::Audio {

	struct SoLoudSystemService : kgr::single_service<SoLoudSystem, kgr::dependency<Ortha::Core::EnTTRegistryService, Ortha::Core::SchedulerService>>{};

} // Audio
