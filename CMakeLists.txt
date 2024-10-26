cmake_minimum_required(VERSION 3.15)

if(NOT DEFINED CMAKE_JS_INC)
    # Указываем путь вручную, например, для CMake.js, установленного глобально
    set(CMAKE_JS_INC "~/.cmake-js/electron-arm64/v33.0.2/include/node")
endif()

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/.build")
set(CMAKE_Swift_COMPILER "/usr/bin/swiftc") # Замените на путь к swiftc, если он другой

# Настройки проекта
project(swift-bridge LANGUAGES CXX)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути и зависимости
set(SWIFT_LIB_PATH "${CMAKE_SOURCE_DIR}/.build/swift-bridge.a")

message(CMAKE_JS_INC: ${CMAKE_JS_INC})
include_directories(${CMAKE_JS_INC} .build)

# Источники
file(GLOB SOURCE_FILES "bridge/bridge.cpp")

# Создание целевой библиотеки
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})

# Настройки для Objective-C++
set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "-x objective-c++ -Warc-bridge-casts-disallowed-in-nonarc")

# Настройки целевой библиотеки
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
        PREFIX ""
        SUFFIX ".node"
)

# Линковка библиотек
target_link_libraries(${PROJECT_NAME}
        ${CMAKE_JS_LIB}
        ${SWIFT_LIB_PATH}
)