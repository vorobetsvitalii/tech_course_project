cmake_minimum_required(VERSION 3.5)

project(dal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core REQUIRED)
include_directories(${Qt6Core_INCLUDE_DIRS})

# Find and include the Qt6 package with SQL module
find_package(Qt6 COMPONENTS Core Sql REQUIRED)

add_executable(dal main.cpp dbexecutor.cpp querybuilder.cpp idatamodel.h dbexecutor.h querybuilder.h)
target_link_libraries(dal PRIVATE Qt6::Core Qt6::Sql)

install(TARGETS dal
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
