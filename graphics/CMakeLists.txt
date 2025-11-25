cmake_minimum_required(VERSION 3.15...4.2)

set(INC_FILES
    inc/graphics/Window.hpp
)

set(SRC_FILES
    src/Window.cpp
)

set(ALL_FILES
    ${SRC_FILES}
    ${INC_FILES}
    ../.clang-format
)

add_library(graphics STATIC ${ALL_FILES})
add_library(cpprast::graphics ALIAS graphics) # Add alias target.

target_compile_features(graphics PUBLIC cxx_std_23)

target_include_directories(graphics PUBLIC inc)

target_link_libraries(graphics PUBLIC SDL3::SDL3 )

# Warning level 4 and treat warnings as errors.
target_compile_options(graphics
    PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Wpedantic -Werror>
)
