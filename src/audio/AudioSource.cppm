module;

#include <memory>

export module Ortha.Audio.AudioSource;

import Ortha.Core.ResourceHandle;

export namespace Ortha::Audio {

	struct AudioSource {
		std::shared_ptr<Core::ResourceHandle> soundResource{};
	};

} // namespace Ortha::Audio
