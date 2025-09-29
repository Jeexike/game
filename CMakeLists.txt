cmake_minimum_required(VERSION 3.10)
project(Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

set(SOURCE_FILES
    main.cpp
    engine/AbstractEntity.cpp
    engine/Bullet.cpp
    engine/Context.cpp
    engine/EnemySpawner.cpp
    engine/EntityHolder.cpp
    engine/FastEnemy.cpp
    engine/FillerText.cpp
    engine/HeavyEnemy.cpp
    engine/IntervalTimer.cpp
    engine/Player.cpp
    engine/ScoreCounter.cpp
    engine/Tower.cpp
    engine/WalkerEnemy.cpp
    engine/Engine.cpp
)

add_executable(Game ${SOURCE_FILES})

target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/engine
    ${CMAKE_SOURCE_DIR}/SFML-2.6.2/include
)

target_link_libraries(Game PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    Threads::Threads
)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(Game PRIVATE -Wall -Wextra -Wno-unused-parameter)
endif()