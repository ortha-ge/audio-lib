module;

#include <soloud.h>

export module Audio.SoLoudSystem;

import Core.Scheduler;
import entt;

export namespace Audio {

	class SoLoudSystem {
	public:
		SoLoudSystem(entt::registry&, Core::Scheduler&);
		~SoLoudSystem();

		void tick(entt::registry& registry);

	private:

		void connectCallbacks(entt::registry& registry);
		void disconnectCallbacks(entt::registry& registry);

		void removeSoLoudSoundPlayback(entt::registry& registry, entt::entity entity);
		void stopSoLoudSoundPlayback(entt::registry& registry, entt::entity entity);

		SoLoud::Soloud mSoloud;
		entt::registry& mRegistry;
		Core::Scheduler& mScheduler;
		Core::TaskHandle mTickHandle{};
	};

} // namespace Audio
