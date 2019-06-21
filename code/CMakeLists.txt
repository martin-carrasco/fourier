cmake_minimum_required(VERSION 3.0) # setting this is required
project(Project)            # this sets the project name

###############################################################################
## file globbing ##############################################################
###############################################################################

# These instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables
# `libs`.
file(GLOB_RECURSE libs      lib/*.cpp)
file(GLOB_RECURSE includes      include/*.h)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wfloat-conversion")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

find_package(OpenCV REQUIRED)
# You can use set(sources src/main.cpp) etc if you don't want to
# use globbing to find files automatically.

###############################################################################
## target definitions #########################################################
###############################################################################

# The data is just added to the executable, because in some IDEs (QtCreator)
# files are invisible when they are not explicitly part of the project.
message( ${libs} )
message( ${includes} )
add_executable(project src/main.cpp ${libs} ${includes})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
# Just for example add some compiler flags.
# target_compile_options(project PUBLIC -std=c++17 -Wall -Wfloat-conversion)

# This allows to include files relative to the root of the src directory with a <> pair
# target_include_directories(project PUBLIC include)

###############################################################################
## dependencies ###############################################################
###############################################################################

# This defines the variables Boost_LIBRARIES that containts all library names
# that we need to link into the program.
# find_package(Boost 1.36.0 COMPONENTS filesystem system REQUIRED)

# target_link_libraries(example PUBLIC
#  ${Boost_LIBRARIES}
#  # here you can add any library dependencies
#)
