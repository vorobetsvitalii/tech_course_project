cmake_minimum_required(VERSION 3.5)
project(Server_poco LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the POCO library directory
set(POCO_DIR "C:/msys64/mingw64")


# Include directories for POCO
include_directories("${POCO_DIR}/include")

# Set the Qt6 installation directory
set(CMAKE_PREFIX_PATH "C:/Qt/6.0.0/msvc2019_64" ${CMAKE_PREFIX_PATH})

# Find and include the Qt6 package with SQL module
find_package(Qt6 COMPONENTS Core Sql REQUIRED)
# Add the Qt6 include directories to the project
include_directories(${Qt6Core_INCLUDE_DIRS})

# Add the category.cpp file to the project sources
list(APPEND PROJECT_SOURCES "../common/model/category.cpp")
list(APPEND PROJECT_SOURCES "../dal/querybuilder.h")
list(APPEND PROJECT_SOURCES "../dal/querybuilder.cpp")
list(APPEND PROJECT_SOURCES "../dal/dbexecutor.h")
list(APPEND PROJECT_SOURCES "../dal/dbexecutor.cpp")



# Add your source files to the project
add_executable(
    Server_poco
    main.cpp
    server.h
    server.cpp
    database.cpp
    database.h
    user.cpp
    user.h
    storage.cpp
    storage.h
    dbmodel.h
    dbmodel.cpp
    categoriesmodel.h
    categoriesmodel.cpp
    ${PROJECT_SOURCES} # Include the added source files here
)




# Link against the Qt6 libraries
target_link_libraries(Server_poco PRIVATE Qt6::Core Qt6::Sql)


#Poco installation start


# Include directories for POCO

include_directories("${POCO_DIR}/include")

target_link_libraries(Server_poco PRIVATE
    "${POCO_DIR}/lib/libPocoFoundation.dll.a"
    "${POCO_DIR}/lib/libPocoNet.dll.a"
    "${POCO_DIR}/lib/libPocoJWT.dll.a"
    "${POCO_DIR}/lib/libPocoJSON.dll.a"
)

install(TARGETS Server_poco
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

#Poco installation finish
