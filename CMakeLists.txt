 
cmake_minimum_required(VERSION 3.31)

find_package(glfw3 CONFIG REQUIRED)

set (ortha-audio-src
        src/audio/services/AudioSystemsService.cpp
        src/audio/systems/AudioSystems.cpp
        src/audio/systems/SoLoudSystem.cpp
)

set (ortha-audio-modules
        src/audio/AudioSource.cppm
        src/audio/PlaySoundSourceRequest.cppm
        src/audio/SoundDescriptor.cppm
        src/audio/SoundPlayback.cppm
        src/audio/services/AudioSystemsService.cppm
        src/audio/services/SoLoudSystemService.cppm
        src/audio/systems/AudioSystems.cppm
        src/audio/systems/SoLoudSystem.cppm
)

add_library(ortha-audio STATIC ${ortha-audio-src} ${ortha-audio-modules})

target_sources(ortha-audio PUBLIC FILE_SET modules TYPE CXX_MODULES FILES ${ortha-audio-modules})
target_compile_features(ortha-audio PUBLIC cxx_std_23)
target_link_libraries(ortha-audio PUBLIC ortha-core soloud)
target_include_directories(ortha-audio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

#add_subdirectory(tests)
