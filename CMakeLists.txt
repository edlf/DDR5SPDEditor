cmake_minimum_required(VERSION 3.5)

project(DDR5SPDEditor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(Qt6_USE_STATIC_LIBS ON)
set(Qt6_USE_STATIC_RUNTIME ON)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DDR5SPDEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ddr5spd.h ddr5spd.cpp
        utilities.cpp
        utilities.h
        xmp3.h
        xmp3.cpp
        ddr5spd_structs.h
        expo.h
        expo.cpp
        mainwindow_jedec.cpp
        mainwindow_xmp1.cpp
        mainwindow_xmp2.cpp
        mainwindow_xmp3.cpp
        mainwindow_xmpu1.cpp
        mainwindow_xmpu2.cpp
        mainwindow_expo1.cpp
        mainwindow_expo2.cpp
        mainwindow_misc.cpp
    )
else()
    add_executable(DDR5SPDEditor
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(DDR5SPDEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(DDR5SPDEditor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DDR5SPDEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DDR5SPDEditor)
endif()
