
cmake_minimum_required(VERSION 3.31)

find_package(Catch2 3 REQUIRED)

set(ortha-audio-tests-src
        SoLoudSystemTests.cpp
)

set(ortha-audio-tests-modules
)

add_executable(ortha-audio-tests ${ortha-audio-tests-src})

target_sources(ortha-audio-tests PUBLIC FILE_SET modules TYPE CXX_MODULES FILES ${ortha-audio-tests-modules})
target_compile_features(ortha-audio-tests PUBLIC cxx_std_23)
target_link_libraries(ortha-audio-tests PRIVATE core-lib ortha-audio Catch2::Catch2WithMain)

#add_custom_target(ortha-audio-tests-assets
#        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
#        "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
#        "$<TARGET_FILE_DIR:ortha-audio-tests>/assets/"
#        COMMENT "Copying assets"
#)

#add_dependencies(ortha-audio-tests ortha-audio-tests-assets)

include(CTest)
include(Catch)
catch_discover_tests(ortha-audio-tests)
