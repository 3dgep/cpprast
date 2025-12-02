cmake_minimum_required(VERSION 3.15...4.2)

set( INC_FILES
    inc/math/AABB.hpp
    inc/math/Math.hpp
    inc/math/Viewport.hpp
)

set( SRC_FILES
    src/Math.cpp
)

set( ALL_FILES 
    ${INC_FILES} 
    ${SRC_FILES} 
    ../.clang-format
)

add_library( math STATIC ${ALL_FILES} )
add_library( cpprast::math ALIAS math )

target_compile_features( math PUBLIC cxx_std_20 )

target_include_directories( math
    PUBLIC inc
)

target_link_libraries( math
    PUBLIC glm::glm
)
