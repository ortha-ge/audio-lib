 
cmake_minimum_required(VERSION 3.31)

find_package(glfw3 CONFIG REQUIRED)

set (audio-lib-src
        src/audio/systems/AudioSystems.cpp
        src/audio/systems/SoLoudSystem.cpp
)

set (audio-lib-modules
        src/audio/AudioSource.cppm
        src/audio/PlaySoundSourceRequest.cppm
        src/audio/SoundDescriptor.cppm
        src/audio/services/AudioSystemsService.cppm
        src/audio/systems/AudioSystems.cppm
        src/audio/systems/SoLoudSystem.cppm
)

add_library(audio-lib STATIC ${audio-lib-src} ${audio-lib-modules})

target_sources(audio-lib PUBLIC FILE_SET modules TYPE CXX_MODULES FILES ${audio-lib-modules})
target_compile_features(audio-lib PUBLIC cxx_std_23)
target_link_libraries(audio-lib PUBLIC core-lib glfw soloud)
target_include_directories(audio-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

#add_subdirectory(tests)
