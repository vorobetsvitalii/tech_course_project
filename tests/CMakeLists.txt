cmake_minimum_required(VERSION 3.5)
project(SportHubTests LANGUAGES CXX)

enable_testing()
set(PROJECT_SOURCES
    main.cpp
    tst_sporthubtests.cpp
    CategoriesModelSerializationAndDeserializationTests.cpp
    SubcategoriesModelSerializationAndDeserializationTests.cpp
    TeamsModelSerializationAndDeserializationTests.cpp
    ../server/categoriesmodel.h
    ../server/subcategoryModel.h
    ../server/Dbmodel.h
    ../server/categoriesmodel.cpp
    ../server/subcategoryModel.cpp
    ../server/Dbmodel.cpp
    ../server/teammodel.h
    ../server/teammodel.cpp
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Core Sql REQUIRED)
find_package(Threads REQUIRED)

# Set the common directory path
set(COMMON_DIR "../common")


# Retrieve a list of all files in the common directory
file(GLOB COMMON_SOURCES "${COMMON_DIR}/*.cpp" "${COMMON_DIR}/*.h")

# Set the model directory path
set(MODELS_DIR "../common/model")


# Retrieve a list of all files in the model directory
file(GLOB MODELS_SOURCES "${MODELS_DIR}/*.cpp" "${MODELS_DIR}/*.h")

# Set the model directory path
set(INTERFACE_DIR "../common/interface")


# Retrieve a list of all files in the model directory
file(GLOB INTERFACE_SOURCES "${INTERFACE_DIR}/*.cpp" "${INTERFACE_DIR}/*.h")

# Set the DAL directory path
set(DAL_DIR "../dal")

# Retrieve a list of all files in the DAL directory
file(GLOB DAL_SOURCES "${DAL_DIR}/*.cpp" "${DAL_DIR}/*.h")
if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "C:/Users/Administrator/Desktop/Softserve_project/tech_course_project/googletest" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "C:/Users/Administrator/Desktop/Softserve_project/tech_course_project/googletest")
endif ()

if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message(FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(
    ${GTestIncludes}
    ${COMMON_DIR}
    ${MODELS_DIR}
    ${INTERFACE_DIR}
    ${DAL_DIR}
    ${Qt6Core_INCLUDE_DIRS}
    ${Qt6Widgets_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)


add_executable(SportHubTests ${PROJECT_SOURCES}  ${COMMON_SOURCES} ${MODELS_SOURCES} ${INTERFACE_SOURCES} ${DAL_SOURCES}
               ${GTestFiles})

target_link_libraries(SportHubTests PRIVATE Threads::Threads)
target_link_libraries(SportHubTests PRIVATE Qt6::Core Qt6::Sql Qt6::Gui)
# Include and link Qt libraries
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
target_link_libraries(SportHubTests PRIVATE Qt${QT_VERSION_MAJOR}::Core)

# Include and link Poco libraries
set(POCO_DIR "C:/msys64/mingw64")
include_directories("${POCO_DIR}/include")
target_link_libraries(SportHubTests PRIVATE
    "${POCO_DIR}/lib/libPocoFoundation.dll.a"
    "${POCO_DIR}/lib/libPocoNet.dll.a"
    "${POCO_DIR}/lib/libPocoJWT.dll.a"
    "${POCO_DIR}/lib/libPocoJSON.dll.a"
)

add_test(NAME SportHubTests COMMAND SportHubTests)