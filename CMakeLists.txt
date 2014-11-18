project(glfw-game-engine)
cmake_minimum_required(VERSION 2.8)

# Add deps subdirectory
add_subdirectory(deps)

# Get all source files from src
aux_source_directory(src SRC_LIST)

# Get Include Directories
set (
      INCLUDE_DIRS
      include
      deps/glfw/include/GLFW
      deps/glew/include/GL
      deps/glm/glm
      deps/glm/gtc
      deps/glm/gtx
      deps/stb_image
      deps/soil/src
      deps/tinyobjloader
    )

include_directories(${INCLUDE_DIRS})

# Add executable to project
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Link GLFW and GLEW to main executable
target_link_libraries(${PROJECT_NAME} libglew_static glfw ${GLFW_LIBRARIES} SOIL tinyobjloader)

# Define GLEW_STATIC for Windows
if(MSVC)
  add_definitions(-DGLEW_STATIC)
endif()

# Copy resources to output directory
# TODO: Figure out why this isn't working -- possibly because we're checking if directory exists?
file(COPY res/shaders/. DESTINATION ${CMAKE_BINARY_DIR}/res/shaders)
file(COPY res/textures/. DESTINATION ${CMAKE_BINARY_DIR}/res/textures)
file(COPY res/meshes/. DESTINATION ${CMAKE_BINARY_DIR})
