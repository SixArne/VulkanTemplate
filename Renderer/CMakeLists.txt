set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

add_executable(Renderer
    src/main.cpp
    src/Core/Window/Window.cpp
    src/Core/Application/Application.cpp
    src/Core/Vulkan/VulkanInstance.cpp
    src/Core/Vulkan/VulkanApplication.cpp
)

# Set compiler warnings as errors
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "[Game] Setting warnings as errors for GNU/Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
elseif(MSVC)
    message(STATUS "[Game] Setting warnings as errors for MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
endif()

# Enable debug define
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode enabled. Optimizations disabled.")
    target_compile_definitions(Renderer PUBLIC DEBUG=1)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release mode enabled. Optimizations enabled.")
    target_compile_definitions(Renderer PUBLIC DEBUG=0)
endif()

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/SixArne/glm.git
    GIT_TAG "master"
    DOWNLOAD_NO_PROGRESS ON
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
    message(STATUS "Fetching glm from https://github.com/SixArne/glm.git on branch master")
    message(STATUS "Setting GLM_INCLUDE_DIR to ${glm_SOURCE_DIR}")
    set(GLM_INCLUDE_DIR "${glm_SOURCE_DIR}")
endif()

# spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/SixArne/spdlog.git
    GIT_TAG "v1.x"
    DOWNLOAD_NO_PROGRESS ON
)

FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
    FetchContent_Populate(spdlog)
    message(STATUS "Fetching spdlog from https://github.com/SixArne/spdlog.git on branch v1.x")
    message(STATUS "Setting SPDLOG_INCLUDE_DIR to ${spdlog_SOURCE_DIR}")
    set(SPDLOG_INCLUDE_DIR "${spdlog_SOURCE_DIR}")
endif()

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG "master"
    DOWNLOAD_NO_PROGRESS ON
)

FetchContent_MakeAvailable(glfw)

# Vulkan
find_package(Vulkan REQUIRED)

set (RendererIncludes
    ${GLM_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${SPDLOG_INCLUDE_DIR}/include
)

foreach(RendererInclude in ${RendererIncludes})
    message(STATUS "Including: ${engineInclude} in Renderer")
endforeach()

target_include_directories(Renderer PUBLIC
    # self include
    ${CMAKE_CURRENT_SOURCE_DIR}

    ${Vulkan_INCLUDE_DIRS}
    ${RendererIncludes}
)

target_link_libraries(Renderer PUBLIC
    glfw
    Vulkan::Vulkan
)