cmake_minimum_required( VERSION 3.15...4.20 )

option( BUILD_SHARED_LIBS "Build using shared libraries" OFF )
option( CPPRAST_BUILD_SAMPLES "Build samples." ON )
option( CPPRAST_BUILD_TESTS "Build tests." OFF )

set( CPPRAST_VERSION_MAJOR 0 )
set( CPPRAST_VERSION_MINOR 0 )
set( CPPRAST_VERSION_PATCH 1 )
set( CPPRAST_VERSION ${CPPRAST_VERSION_MAJOR}.${CPPRAST_VERSION_MINOR}.${CPPRAST_VERSION_PATCH})

project( cpprast VERSION ${CPPRAST_VERSION} LANGUAGES C CXX )

# Enable multi-processor builds in MSVC.
if(MSVC)
    add_compile_options(/MP)
endif(MSVC)
