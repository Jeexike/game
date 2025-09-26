cmake_minimum_required(VERSION 3.10)
project(Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Найти потоки (обязательно для std::thread)
find_package(Threads REQUIRED)

# Указать путь к SFML (если установлен локально)
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

# Исходные файлы
set(SOURCE_FILES
    main.cpp
    engine/AbstractEntity.cpp  # если есть .cpp файлы — добавьте их
    engine/Context.cpp
    # ... остальные .cpp, если есть
)

# Если у вас ВСЕ классы в .h (header-only), то main.cpp достаточно

add_executable(Game main.cpp)

# Include директории
target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/engine
    ${CMAKE_SOURCE_DIR}/SFML-2.6.2/include
)

# Линковка
target_link_libraries(Game PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    Threads::Threads  # ← критически важно для std::thread
)

# Опционально: предупреждения
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(Game PRIVATE -Wall -Wextra -Wno-unused-parameter)
endif()