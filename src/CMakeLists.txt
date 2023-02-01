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