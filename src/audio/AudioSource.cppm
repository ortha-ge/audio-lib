module;

#include <entt/entity/entity.hpp>

export module Audio.AudioSource;

export namespace Audio {

	struct AudioSource {
		entt::entity soundResource{ entt::null };
	};

} // namespace Audio
