cmake_minimum_required(VERSION 3.00)
project(simple-c-quiz-game LANGUAGES C) # <--- Project name updated here!

# The rest of your root CMakeLists.txt content as previously discussed:
# # Define the 'MATH' variable if linking to the math library (e.g., on Linux/macOS)
# # ... (your MATH variable setup) ...

# # Create HEADER-ONLY library
 add_library(HEADER-ONLY INTERFACE)
# # ... (HEADER-ONLY include directories and link libraries) ...

# # Add the 'src' subdirectory.
 add_subdirectory(src) 

# # Define your executable target.
 add_executable(simple-c-quiz-game src/main.c) # <--- Executable name likely updated too for consistency

# # Link your HEADER-ONLY library to the executable.
 target_link_libraries(simple-c-quiz-game PRIVATE HEADER-ONLY) # <--- Link to the new executable name
