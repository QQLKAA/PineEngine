add_library(pine STATIC
  src/log.cc
  src/shader.cc
  src/window.cc)

target_compile_features(pine PUBLIC cxx_std_17)

target_include_directories(pine PUBLIC include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw)

add_subdirectory(libs/spdlog)
add_subdirectory(libs/glad)

find_package(OpenGL REQUIRED)

target_link_libraries(pine glfw spdlog::spdlog OpenGL::GL glad)
