
module Audio.Systems;

namespace Audio {

	AudioSystems::AudioSystems(Core::EnTTRegistry& registry, Core::Scheduler& scheduler)
		: mSoLoudSystem(registry, scheduler) {}

	AudioSystems::~AudioSystems() = default;

} // namespace Audio
