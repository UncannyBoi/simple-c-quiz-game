cmake_minimum_required(VERSION 3.00)
project(simple-c-quiz-game
 LANGUAGES C)

# Define the 'MATH' variable if linking to the math library (e.g., on Linux/macOS)
# On Windows, basic math functions are typically in the C runtime and don't need explicit linking.
# If you are targeting Linux/macOS and need 'libm':
# set(MATH "m") 
# If targeting Windows, you might just leave MATH undefined or set it to an empty string.
# A more robust way to find system libraries for cross-platform:
find_package(Threads) # Example: if you need pthreads, though not for math.
# For math on *some* systems, you might find a specific package or just link 'm'.
# For now, let's assume 'm' is what you intended if on a Unix-like system.
# set(MATH "m") # Uncomment this if you are on Linux/macOS and need 'libm'


# Create HEADER-ONLY library
# This is an INTERFACE library, used to propagate include directories and link libraries.
add_library(HEADER-ONLY INTERFACE)

# Add project's 'include/' directory to HEADER-ONLY.
# CMAKE_SOURCE_DIR points to the root of your project where this CMakeLists.txt is.
target_include_directories(HEADER-ONLY INTERFACE ${CMAKE_SOURCE_DIR}/include)

# If you have headers in a 'lib/' directory that HEADER-ONLY should expose:
# target_include_directories(HEADER-ONLY INTERFACE ${CMAKE_SOURCE_DIR}/lib)

# Link the math library to HEADER-ONLY.

target_link_libraries(HEADER-ONLY INTERFACE ${MATH})


# Add the 'src' subdirectory.
add_subdirectory(src) 


# Define your executable target.
add_executable(simple-c-quiz-game
 src/main.c)

# Link your HEADER-ONLY library to the Cgame executable.
target_link_libraries(simple-c-quiz-game
 PRIVATE HEADER-ONLY)
