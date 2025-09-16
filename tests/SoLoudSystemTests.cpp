
#include <catch2/catch_test_macros.hpp>

#include <entt/entt.hpp>

import Audio.AudioSource;
import Audio.PlaySoundSourceRequest;
import Audio.SoLoudSystem;
import Audio.SoundPlayback;
import Core.EnTTRegistry;
import Core.Scheduler;

// TEST_CASE("AudioSourceWithEmptySoundAndPlaybackRequest_TickSoLoudSystem_NoPlaybackHandleAndRequestRemoved", "SoLoudSystem") {
// 	using namespace Audio;
// 	Core::EnTTRegistry enttRegistry;
// 	Core::Scheduler scheduler;
// 	SoLoudSystem soLoudSystem(enttRegistry, scheduler);
// 	entt::registry& registry(enttRegistry);
// 	const entt::entity audioSourceEntity{ registry.create() };
// 	registry.emplace<AudioSource>(audioSourceEntity);
// 	registry.emplace<PlaySoundSourceRequest>(audioSourceEntity);
//
// 	scheduler.tick();
//
// 	const bool hasSoundPlaybackHandle = registry.all_of<SoundPlayback>(audioSourceEntity);
// 	const bool hasPlaySoundSourceRequest = registry.all_of<PlaySoundSourceRequest>(audioSourceEntity);
// 	REQUIRE(!hasSoundPlaybackHandle);
// 	REQUIRE(!hasPlaySoundSourceRequest);
// }