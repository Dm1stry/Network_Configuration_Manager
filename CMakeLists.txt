cmake_minimum_required(VERSION 3.24)

project(NetConf_Manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt5 COMPONENTS PrintSupport Core Widgets Network Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport Core Widgets Network Gui REQUIRED)

set(W_DIR widgets)  # Widgets directory
set(SW_DIR ${W_DIR}/subwidgets)  # Subwidgets directory

set(WIDGETS
)

set(SOURCES
    ${WIDGETS}
    main.cpp
)

add_executable(${CMAKE_PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Core
)

# target_include_directories(${PROJECT_NAME} PRIVATE 
# )