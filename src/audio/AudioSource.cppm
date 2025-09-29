module;

#include <memory>

export module Audio.AudioSource;

import Core.ResourceHandle;

export namespace Audio {

	struct AudioSource {
		std::shared_ptr<Core::ResourceHandle> soundResource{};
	};

} // namespace Audio
