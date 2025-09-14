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

		void connectCallbacks(entt::registry& registry);
		void disconnectCallbacks(entt::registry& registry);

		void removeSoLoudSoundPlayback(entt::registry& registry, entt::entity entity);
		void stopSoLoudSoundPlayback(entt::registry& registry, entt::entity entity);

		SoLoud::Soloud mSoloud;
		Core::EnTTRegistry& mRegistry;
		Core::Scheduler& mScheduler;
		Core::TaskHandle mTickHandle{};
	};

} // namespace Audio
