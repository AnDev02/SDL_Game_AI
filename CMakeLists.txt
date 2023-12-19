cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

project(SdlCreateWindow VERSION 1.0.0)
add_executable(${PROJECT_NAME} src/main.cpp src/ball.cpp src/commonFn.cpp src/game.cpp)

if(WIN32)
  message("Win32 App")
  set(SDL_INCLUDE_DIR C:/SDL/include/SDL2)
  set(SDL_LIB 0)
  set(SDL_LIB_IMAGE C:/SDL/lib/libSDL2_image.dll)
elseif(APPLE)
  message("macOS App")
  set(SDL_INCLUDE_DIR /usr/local/include/SDL2)
  set(SDL_LIB //usr/local/Cellar/sdl2/2.28.3/lib/libSDL2.dylib)
  set(SDL_LIB_IMAGE /usr/local/Cellar/sdl2_image/2.6.3_2/lib/libSDL2_image.dylib)
elseif(UNIX)

endif()

target_include_directories(
  ${PROJECT_NAME} 
  PRIVATE 
  ${SDL_INCLUDE_DIR}
)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  ${SDL_LIB}
  ${SDL_LIB_IMAGE}
)

# Copy file
file(COPY assets DESTINATION ./)
file(COPY ${SDL_LIB} DESTINATION ./)
file(COPY ${SDL_LIB_IMAGE} DESTINATION ./)