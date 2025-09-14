
cmake_minimum_required(VERSION 3.31)

find_package(Catch2 3 REQUIRED)

set(audio-lib-tests-src
        SoLoudSystemTests.cpp
)

set(audio-lib-tests-modules
)

add_executable(audio-lib-tests ${audio-lib-tests-src})

target_sources(audio-lib-tests PUBLIC FILE_SET modules TYPE CXX_MODULES FILES ${audio-lib-tests-modules})
target_compile_features(audio-lib-tests PUBLIC cxx_std_23)
target_link_libraries(audio-lib-tests PRIVATE core-lib Catch2::Catch2WithMain)

#add_custom_target(audio-lib-tests-assets
#        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
#        "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
#        "$<TARGET_FILE_DIR:audio-lib-tests>/assets/"
#        COMMENT "Copying assets"
#)

#add_dependencies(audio-lib-tests audio-lib-tests-assets)

include(CTest)
include(Catch)
catch_discover_tests(audio-lib-tests)
