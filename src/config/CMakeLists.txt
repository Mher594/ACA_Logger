find_package(toml11 REQUIRED)

add_library(config config.cpp)

target_compile_options(config PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_include_directories(config PUBLIC include)

target_link_libraries(config
 PRIVATE
 toml11::toml11)

