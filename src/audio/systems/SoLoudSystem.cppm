module;

#include <entt/fwd.hpp>
#include <soloud.h>

export module Audio.SoLoudSystem;

import Core.EnTTRegistry;
import Core.Scheduler;

export namespace Audio {

	class SoLoudSystem {
	public:
		SoLoudSystem(Core::EnTTRegistry&, Core::Scheduler&);
		~SoLoudSystem();

		void tick(entt::registry& registry);

	private:
		SoLoud::Soloud mSoloud;
		Core::EnTTRegistry& mRegistry;
		Core::Scheduler& mScheduler;
		Core::TaskHandle mTickHandle{};
	};

} // namespace Audio
