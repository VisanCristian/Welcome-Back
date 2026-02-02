cmake_minimum_required(VERSION 3.5)

set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(WARNINGS_AS_ERRORS OFF)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        3.0.0
        GIT_SHALLOW    1
)

FetchContent_MakeAvailable(SFML)

###############################################################################

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

###############################################################################

add_executable(${MAIN_EXECUTABLE_NAME}
    main.cpp
    src/GameObject.cpp
    headers/GameObject.h
    src/Puzzle.cpp
    headers/Puzzle.h
    src/Player.cpp
    headers/Player.h
    src/ButtonsInOrder.cpp
    headers/ButtonsInOrder.h
    src/TagZones.cpp
    headers/TagZones.h
    src/PuzzleFactory.cpp
    headers/PuzzleFactory.h
    src/Computer.cpp
    headers/Computer.h
    src/GameError.cpp
    headers/GameError.h
    headers/Result.h
    src/InvalidConfigFile.cpp
    headers/InvalidConfigFile.h
    src/ConstructorError.cpp
    headers/ConstructorError.h
    src/InternalError.cpp
    headers/InternalError.h
    src/RememberNumbers.cpp
    headers/RememberNumbers.h
    src/Noir.cpp
    headers/Noir.h
    src/Lucas.cpp
    headers/Lucas.h
    src/Killer.cpp
    headers/Killer.h
    src/Police.cpp
    headers/Police.h
)

target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(${MAIN_EXECUTABLE_NAME}
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
)

set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

###############################################################################

target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System Threads::Threads)

install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
