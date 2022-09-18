cmake_minimum_required(VERSION 3.5)

project(Aviatar-Qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VULKAN_SDK /Users/algasami/Applications/VulkanSDK)
set(VULKAN_VERSION 1.3.224.1)
set(VULKAN_PATH ${VULKAN_SDK}/${VULKAN_VERSION}/macOS)
set(VULKAN_LIB_LIST "Vulkan::Vulkan")
set(GLFW_LIB_LIST "glfw")
set(GLFW_PATH /opt/homebrew/Cellar/glfw/3.3.8)
set(QT_PATH /Users/algasami/Applications/Qt/6.3.2/macos)

set(CMAKE_PREFIX_PATH ${QT_PATH}/lib/cmake)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PROJECT_SOURCES
    ${SRC}/main.cpp
    ${SRC}/mainwindow.cpp
    ${SRC}/mainwindow.hpp
    ${SRC}/mainwindow.ui

    ${SRC}/application.cpp

    ${SRC}/application.hpp
    ${SRC}/supplement.hpp
)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Aviatar-Qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Aviatar-Qt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Aviatar-Qt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Aviatar-Qt
            ${PROJECT_SOURCES}
        )
    endif()
endif()



set_target_properties(Aviatar-Qt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


install(TARGETS Aviatar-Qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Aviatar-Qt)
endif()


link_directories(${VULKAN_PATH}/bin;${VULKAN_PATH}/lib;${GLFW_PATH}/lib;)

target_link_libraries(Aviatar-Qt PRIVATE
Qt${QT_VERSION_MAJOR}::Widgets
${VULKAN_LIB_LIST}
${GLFW_LIB_LIST}
)

target_include_directories(Aviatar-Qt PRIVATE
${CMAKE_BINARY_DIR}/Test_autogen/include_Debug;
${GLFW_PATH}/include;
${VULKAN_PATH}/include;
)
