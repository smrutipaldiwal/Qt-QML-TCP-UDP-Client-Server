# Optional standalone build file, supplied because your client CMake was absent.
# Keep your own build file if it already registers QML/resources correctly.
cmake_minimum_required(VERSION 3.16)
project(AjayClient LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # Compiles qml.qrc into the executable.
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Network)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Main.qml" OR
   NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/RecordForm.qml")
    message(FATAL_ERROR "Copy your original Main.qml and RecordForm.qml into client/ first.")
endif()
add_executable(AjayClient main.cpp clientcontroller.cpp clientcontroller.h
    tcpsender.cpp tcpsender.h udpreceiver.cpp udpreceiver.h
    ../common/protocol.h qml.qrc)
target_include_directories(AjayClient PRIVATE ../common)
target_link_libraries(AjayClient PRIVATE Qt6::Core Qt6::Gui Qt6::Qml
    Qt6::Quick Qt6::Network)
