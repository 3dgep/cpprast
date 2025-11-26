cmake_minimum_required(VERSION 3.15...4.2)

set( TARGET_NAME 02-ImGui )

add_executable( ${TARGET_NAME} main.cpp )

target_link_libraries( ${TARGET_NAME} 
    PRIVATE cpprast::graphics 
)