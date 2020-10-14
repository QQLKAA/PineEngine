add_executable(sandbox
  src/sandbox.cc)

target_link_libraries(sandbox pine)

add_custom_command(TARGET sandbox POST_BUILD COMMAND
  ${CMAKE_COMMAND} -E create_symlink 
  ${CMAKE_CURRENT_SOURCE_DIR}/assets 
  ${CMAKE_CURRENT_BINARY_DIR}/assets)
