cmake_minimum_required(VERSION 3.15)

project(NonEuclidean
  LANGUAGES CXX
  VERSION 0.1.0
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(GLEW CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_executable(NonEuclidean WIN32
  NonEuclidean/Camera.cpp
  NonEuclidean/Camera.h
  NonEuclidean/Collider.cpp
  NonEuclidean/Collider.h
  NonEuclidean/Engine.cpp
  NonEuclidean/Engine.h
  NonEuclidean/Floorplan.h
  NonEuclidean/FrameBuffer.cpp
  NonEuclidean/FrameBuffer.h
  NonEuclidean/GameHeader.h
  NonEuclidean/Ground.h
  NonEuclidean/House.h
  NonEuclidean/Input.cpp
  NonEuclidean/Input.h
  NonEuclidean/Level1.cpp
  NonEuclidean/Level1.h
  NonEuclidean/Level2.cpp
  NonEuclidean/Level2.h
  NonEuclidean/Level3.cpp
  NonEuclidean/Level3.h
  NonEuclidean/Level4.cpp
  NonEuclidean/Level4.h
  NonEuclidean/Level5.cpp
  NonEuclidean/Level5.h
  NonEuclidean/Level6.cpp
  NonEuclidean/Level6.h
  NonEuclidean/Main.cpp
  NonEuclidean/Mesh.cpp
  NonEuclidean/Mesh.h
  NonEuclidean/Object.cpp
  NonEuclidean/Object.h
  NonEuclidean/Physical.cpp
  NonEuclidean/Physical.h
  NonEuclidean/Pillar.h
  NonEuclidean/PillarRoom.h
  NonEuclidean/Player.cpp
  NonEuclidean/Player.h
  NonEuclidean/Portal.cpp
  NonEuclidean/Portal.h
  NonEuclidean/Resources.cpp
  NonEuclidean/Resources.h
  NonEuclidean/Scene.h
  NonEuclidean/Shader.cpp
  NonEuclidean/Shader.h
  NonEuclidean/Sky.h
  NonEuclidean/Sphere.h
  NonEuclidean/Statue.h
  NonEuclidean/Texture.cpp
  NonEuclidean/Texture.h
  NonEuclidean/Timer.h
  NonEuclidean/Tunnel.h
  NonEuclidean/Vector.h
)

target_link_libraries(NonEuclidean
  PRIVATE
    GLEW::glew_s
    SDL2::SDL2-static
    SDL2::SDL2main
)

set_target_properties(NonEuclidean
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if(MSVC)
  set_target_properties(NonEuclidean
    PROPERTIES
      VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:NonEuclidean>
      MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
  )
endif()

set(MESHES
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/bunny.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/double_quad.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/floorplan.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/ground.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/ground_slope.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/pillar.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/pillar_room.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/quad.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/square_rooms.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/suzanne.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/teapot.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/tunnel.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/tunnel_scale.obj
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Meshes/tunnel_slope.obj
)

set(SHADERS
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Shaders/pink.frag
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Shaders/pink.vert
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Shaders/portal.frag
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Shaders/portal.vert
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Shaders/sky.frag
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Shaders/sky.vert
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Shaders/texture.frag
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Shaders/texture.vert
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Shaders/texture_array.frag
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Shaders/texture_array.vert
)

set(TEXTURES
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Textures/checker_gray.bmp
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Textures/checker_green.bmp
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Textures/floorplan_textures.bmp
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Textures/gold.bmp
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Textures/three_room.bmp
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Textures/three_room2.bmp
  ${PROJECT_SOURCE_DIR}/NonEuclidean/Textures/white.bmp
)

add_custom_command(TARGET NonEuclidean
  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
      $<TARGET_FILE_DIR:NonEuclidean>/Meshes
    COMMAND ${CMAKE_COMMAND} -E make_directory
      $<TARGET_FILE_DIR:NonEuclidean>/Shaders
    COMMAND ${CMAKE_COMMAND} -E make_directory
      $<TARGET_FILE_DIR:NonEuclidean>/Textures
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${MESHES}
      $<TARGET_FILE_DIR:NonEuclidean>/Meshes
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${SHADERS}
      $<TARGET_FILE_DIR:NonEuclidean>/Shaders
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${TEXTURES}
      $<TARGET_FILE_DIR:NonEuclidean>/Textures
)
