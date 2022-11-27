file(GLOB SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)

add_library(scene ${SOURCE_FILES})

target_include_directories(scene
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(scene PUBLIC mesh supportclasses)