file(GLOB SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)

add_library(mesh ${SOURCE_FILES})

target_include_directories(mesh
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(mesh PUBLIC supportclasses)