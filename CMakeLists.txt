cmake_minimum_required(VERSION 3.12)
project(Simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

# Find Geant4
find_package(Geant4 REQUIRED)

# Include Geant4 directories
include(${Geant4_USE_FILE})

# Add Gmsh library
set(GMSH_LIB_DIR /home/gmsh/lib)
link_directories(${GMSH_LIB_DIR})

# Compiler flags
set(CMAKE_CXX_FLAGS "-fdiagnostics-color -O2 -g ${Geant4_CXX_FLAGS}")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--copy-dt-needed-entries -fdiagnostics-color -lm ${Geant4_LIBRARIES} -L${GMSH_LIB_DIR} -lgmsh")

# Source files
file(GLOB SOURCE_FILES "*.cc" "src_G4/*.cc")
add_executable(sim ${SOURCE_FILES})

target_link_libraries(sim ${Geant4_LIBRARIES} gmsh)

target_include_directories(sim PRIVATE ${Geant4_INCLUDE_DIRS})

target_compile_options(sim PRIVATE ${Geant4_CXX_FLAGS})

# Install target
install(TARGETS sim DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

add_custom_target(test
    COMMAND echo ${CMAKE_EXE_LINKER_FLAGS}
    COMMENT "Printing linker flags."
)
add_custom_target(clean_build
    COMMAND rm -f *.o src_G4/*.o
    COMMENT "Cleaning build files."
)
