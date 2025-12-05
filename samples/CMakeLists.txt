cmake_minimum_required(VERSION 4.0...4.2)

macro(add_sample DIR_NAME)
    add_subdirectory(${DIR_NAME})
    set_target_properties(${DIR_NAME}
        PROPERTIES
        FOLDER samples
        DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${DIR_NAME})
endmacro()

add_sample(01-ClearScreen)
add_sample(02-ImGui)
