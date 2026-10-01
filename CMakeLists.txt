cmake_minimum_required(VERSION 3.28)

project(Raytracing LANGUAGES C CXX)

# Top-level only settings
if (PROJECT_IS_TOP_LEVEL)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    # Build Types
    get_property(multi GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if (multi)
        set(CMAKE_CONFIGURATION_TYPES "Debug;Profile;Release" CACHE STRING "" FORCE)
    elseif (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Profile" "Release")
    endif ()
endif ()


# Dependencies
include(FetchContent)

FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
    GIT_SHALLOW    TRUE
)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
FetchContent_Declare(SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.2.24
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(glm SDL3)

# Executable
add_executable(Raytracing
    src/Main.cpp
    src/geometry/HitRecord.cpp
    src/geometry/Ray.cpp
    src/geometry/Sphere.cpp
    src/lighting/Light.cpp
    src/lighting/PointLight.cpp
    src/material/Color.cpp
    src/material/Dielectric.cpp
    src/material/Material.cpp
    src/material/Metal.cpp
    src/material/SolidColorTexture.cpp
    src/material/Texture.cpp
    src/rendering/Camera.cpp
    src/rendering/Scene.cpp
)

target_include_directories(Raytracing PRIVATE
    include
    include/geometry
    include/geometry/objects
    include/lighting
    include/material
    include/material/material
    include/material/texture
    include/rendering
)

target_compile_features(Raytracing PRIVATE cxx_std_20)
target_link_libraries(Raytracing PRIVATE glm::glm SDL3::SDL3)

# Compile Options
set(RAYTRACING_COMPILE_OPTIONS
        # --- MSVC Config ---
        $<$<CXX_COMPILER_ID:MSVC>:
        $<$<CONFIG:Profile>:/O2 /Zi>
        /W4 /permissive- /Zc:preprocessor /WX
        >

        # --- GCC/Clang Config ---
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:
        $<$<CONFIG:Profile>:-O3 -g>
        -Wall -Wextra -pedantic -Werror
        >
)
target_compile_options(Raytracing PRIVATE ${RAYTRACING_COMPILE_OPTIONS})
