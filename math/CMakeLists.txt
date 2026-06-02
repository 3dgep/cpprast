cmake_minimum_required(VERSION 3.15...4.2)

set( INC_FILES
    inc/math/AABB.hpp
    inc/math/Line.hpp
    inc/math/Math.hpp
    inc/math/OutCodes.hpp
    inc/math/Rect.hpp
    inc/math/Viewport.hpp
    inc/math/bitmask_operators.hpp
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
