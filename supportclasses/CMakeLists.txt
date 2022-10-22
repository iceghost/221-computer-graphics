file(GLOB SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)

add_library(supportclasses ${SOURCE_FILES})

target_include_directories(supportclasses
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)