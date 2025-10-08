cmake_minimum_required(VERSION 3.16)

project(CaculateInfinite_EN VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_program(LUPDATE_EXECUTABLE lupdate)
find_program(LRELEASE_EXECUTABLE lrelease)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CaculateInfinite_EN
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        All.qrc
        infinitemode.h infinitemode.cpp infinitemode.ui
        welcome.h welcome.cpp welcome.ui
        setting.h setting.cpp setting.ui
        dead.h dead.cpp dead.ui
    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CaculateInfinite_EN APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CaculateInfinite_EN SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CaculateInfinite_EN
            ${PROJECT_SOURCES}
        )
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
        "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"/SUBSYSTEM:WINDOWS")
    endif()
endif()

target_link_libraries(CaculateInfinite_EN PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries (CaculateInfinite_EN PRIVATE Qt6::Sql)
target_link_libraries (CaculateInfinite_EN PRIVATE Qt6::Multimedia)
target_link_libraries (CaculateInfinite_EN PRIVATE Qt6::Network)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CaculateInfinite_EN)
endif()



set_target_properties(CaculateInfinite_EN PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CaculateInfinite_EN
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CaculateInfinite_EN)
endif()

