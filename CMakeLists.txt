cmake_minimum_required (VERSION 3.12.4)
project (financeGUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# check Qt modules
MESSAGE("----------------Qt---------------")
find_package(Qt5Core)
MESSAGE("Found Core package")
find_package(Qt5Widgets)
MESSAGE("Found Widgets package")
find_package(Qt5Sql)
MESSAGE("Found Sql package")

# add ressources
file(GLOB RESSOURCES
      src/*.ui
)

# add ressources
file(GLOB HEADERS
      src/*.h
)

# add ressources
file(GLOB SOURCES
      src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Sql)
