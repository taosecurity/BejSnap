cmake_minimum_required(VERSION 3.10)

project(BejSnap VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES
    src/main.cpp
    src/bejsnapapp.cpp
    src/bejsnapwindow.cpp
    src/regionselector.cpp
    src/previewwindow.cpp
    src/filemanager.cpp
    src/settingsdialog.cpp
    src/thememanager.cpp
)

set(HEADERS
    src/bejsnapapp.h
    src/bejsnapwindow.h
    src/regionselector.h
    src/previewwindow.h
    src/filemanager.h
    src/settingsdialog.h
    src/thememanager.h
    src/constants.h
)

qt5_add_resources(RESOURCES
    resources/bejsnap.qrc
)

add_executable(BejSnap ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(BejSnap PRIVATE Qt5::Widgets)

install(TARGETS BejSnap
    RUNTIME DESTINATION bin
)
