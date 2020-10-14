cmake_minimum_required(VERSION 3.18)

project(
  PineEngine
  LANGUAGES C CXX)

if(MINGW)
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif(MINGW)

if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif(MSVC)

add_subdirectory(pine)
add_subdirectory(sandbox)
