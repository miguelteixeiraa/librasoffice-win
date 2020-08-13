cmake_minimum_required(VERSION 3.5)

project(LIBRASOffice-win LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QML_IMPORT_PATH "C:\\Qt\\5.15.0\\mingw81_64\\qml")

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui Quick)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

if(ANDROID)
    add_library(LIBRASOffice-win SHARED
        main.cpp
        wineventlistener.cpp
        listenercontroller.cpp
        jsonsdatabase.cpp
        librasoffice_app.cpp
        qml.qrc
    )
else()
    add_executable(LIBRASOffice-win
      main.cpp
      jsonsdatabase.cpp
      librasoffice_app.cpp
      WinEventListener/focuschangedeventhandler.cpp
      WinEventListener/generaleventshandler.cpp
      WinEventListener/wineventlistener.cpp
      qml.qrc
    )
endif()

target_compile_definitions(LIBRASOffice-win
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries (LIBRASOffice-win
                        PUBLIC Qt5::Core
                               Qt5::Quick
                               Qt5::Gui
                               Qt5::Widgets
                       )
