module;

#include <soloud.h>
#include <entt/fwd.hpp>

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

} // Audio
