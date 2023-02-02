add_subdirectory(config)
add_subdirectory(logger)

add_executable(main main.cpp)

target_compile_options(main PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_link_libraries(main
 PRIVATE
 logger
 config)

 # Copy <filename> to build directory
set(copy_source_dir "${CMAKE_SOURCE_DIR}/src")
set(copy_dest_dir "${CMAKE_BINARY_DIR}/src/$<CONFIG>")
set(copy_file_name "logger.toml")

message(${copy_dest_dir})

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${copy_dest_dir}
)
add_custom_command(
    TARGET main POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy "${copy_source_dir}/${copy_file_name}" "${copy_dest_dir}/${copy_file_name}"
    COMMENT "Copying ${copy_file_name} to build directory")