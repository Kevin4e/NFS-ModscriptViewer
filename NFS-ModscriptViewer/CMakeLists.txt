cmake_minimum_required(VERSION 3.16)

project(NFS-ModscriptViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# 1. Gather files from the new 'src' folder
file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB HEADERS CONFIGURE_DEPENDS src/*.hpp)

add_executable(${PROJECT_NAME} WIN32
    ${SOURCES}
    ${HEADERS}
    ui/AboutDialog.ui
    ui/MainWindow.ui
    ui/SupportDialog.ui
    resources/resources.qrc
    resources/app.rc
)

# 2. Correctly set the AUTOUIC search path property for your executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui"
)

# 3. Tell CMake to look inside 'src' for your header files
target_include_directories(${PROJECT_NAME} PRIVATE
    src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)