add_library(logger logger.cpp)

target_compile_options(logger PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_include_directories(logger PUBLIC include)

target_link_libraries(logger
 PRIVATE
 config)

