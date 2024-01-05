cmake_minimum_required(VERSION 3.20)
project(beastgres)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(BOOST_VERSION 1.84.0)
set(BOOST_ROOT /usr/local/boost)
# Find the Boost library components you need
find_package(Boost ${BOOST_VERSION} REQUIRED COMPONENTS system context)
# Find PostgreSQL
find_package(PostgreSQL REQUIRED)

# Add your source files
add_executable(beastgres main.cpp)

# Include directories for PostgreSQL
include_directories(${PostgreSQL_INCLUDE_DIRS})

# Link the libraries
target_link_libraries(beastgres ${PostgreSQL_LIBRARIES} Boost::system Boost::context)

# Display Boost version in the output
message("Boost version: ${Boost_VERSION}")

