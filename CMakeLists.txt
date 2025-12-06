cmake_minimum_required(VERSION 3.19)
project(testx LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Charts SerialPort)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(testx
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    workerreader.h workerreader.cpp
    workerdisplay.h workerdisplay.cpp
    workersave.h workersave.cpp

    sharedresource.h


)

target_link_libraries(testx
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Charts
        Qt::SerialPort
)
target_link_libraries(testx PRIVATE Qt6::Widgets)

include(GNUInstallDirs)

install(TARGETS testx
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET testx
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
