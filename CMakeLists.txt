cmake_minimum_required(VERSION 3.5)

project(Transactions VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wpedantic -Werror -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Wpedantic -pthread")

set(CMAKE_PREFIX_PATH "/Users/rulemore/code/Qt/6.7.0/macos/lib/cmake")

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
    set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

set(UI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ui)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${UI_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(OpenSSL REQUIRED COMPONENTS SSL Crypto)

file(GLOB SOURCES
  ${SRC_DIR}/main.cpp    
  ${SRC_DIR}/*.cpp
  ${INC_DIR}/*.h
  ${UI_DIR}/*.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Transactions
        MANUAL_FINALIZATION
        ${SOURCES}
    )
else()
    add_executable(Transactions
        ${SOURCES}
    )
endif()

target_link_libraries(Transactions PRIVATE Qt${QT_VERSION_MAJOR}::Widgets OpenSSL::SSL OpenSSL::Crypto)

set_target_properties(Transactions PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Transactions
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Transactions)
endif()

target_include_directories(Transactions PRIVATE ${INC_DIR})
