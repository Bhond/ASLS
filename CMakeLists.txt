cmake_minimum_required(VERSION 3.15)
project(ASLS VERSION 0.1 LANGUAGES CXX)

# -------------------------
# User options
# -------------------------
option(ASLS_ENABLE_GUI "Build the graphical application (requires SFML)" ON)
option(ASLS_ENABLE_ASAN "Enable AddressSanitizer in Debug builds (GCC/Clang only)" ON)

# -------------------------
# Basic compiler settings
# -------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to Release if not set (useful for single-config generators)
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, defaulting to Release")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

# -------------------------
# Paths & generated include
# -------------------------
set(PATH_ROOT ${CMAKE_SOURCE_DIR})
set(PATH_RESOURCES "${CMAKE_SOURCE_DIR}/res")
set(GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_DIR})

# Configure common.hpp into build tree (if template exists)
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main/common.hpp.in")
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/main/common.hpp.in"
                 "${GENERATED_DIR}/common.hpp" @ONLY)
  set(GENERATED_COMMON_HEADER "${GENERATED_DIR}/common.hpp")
endif()

# -------------------------
# Try to help find Homebrew SFML on macOS (best-effort)
# -------------------------
if (APPLE)
  execute_process(
    COMMAND brew --prefix sfml
    RESULT_VARIABLE _brew_res
    OUTPUT_VARIABLE _brew_sfml_prefix
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
  if (_brew_res EQUAL 0 AND _brew_sfml_prefix)
    list(APPEND CMAKE_PREFIX_PATH "${_brew_sfml_prefix}/lib/cmake/SFML")
    message(STATUS "Added Homebrew SFML CMake dir: ${_brew_sfml_prefix}/lib/cmake/SFML")
  endif()
endif()

# -------------------------
# Source discovery (exclude main.cpp from library)
# -------------------------
file(GLOB_RECURSE ASLS_SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx")
file(GLOB_RECURSE ASLS_HDRS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

# locate main; adjust path if your app entry is different
set(ASLS_MAIN_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/main/main.cpp")
if (NOT EXISTS ${ASLS_MAIN_SRC})
  # try alternative
  file(GLOB ALT_MAIN CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/main/*.cpp")
  list(LENGTH ALT_MAIN _alt_len)
  if (_alt_len GREATER 0)
    list(GET ALT_MAIN 0 ASLS_MAIN_SRC)
  endif()
endif()

# Remove main from library sources (if present)
list(REMOVE_ITEM ASLS_SRCS ${ASLS_MAIN_SRC})

# -------------------------
# Core library target
# -------------------------
add_library(asls_core STATIC ${ASLS_SRCS} ${ASLS_HDRS})
target_include_directories(asls_core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${GENERATED_DIR}>
)

# Make generated header visible in IDEs (if present)
if (DEFINED GENERATED_COMMON_HEADER)
  target_sources(asls_core PRIVATE ${GENERATED_COMMON_HEADER})
endif()

# Nice IDE organization
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source" FILES ${ASLS_SRCS} ${ASLS_HDRS})
if (DEFINED GENERATED_COMMON_HEADER)
  source_group("Generated" FILES ${GENERATED_COMMON_HEADER})
endif()

# -------------------------
# AddressSanitizer flags (Debug, GCC/Clang)
# -------------------------
if (ASLS_ENABLE_ASAN AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  message(STATUS "ASAN support enabled for Debug builds (GCC/Clang)")
  target_compile_options(asls_core PRIVATE
    $<$<CONFIG:Debug>:-g -fsanitize=address -fno-omit-frame-pointer>
  )
  target_link_options(asls_core PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
  )
endif()

# -------------------------
# Optional Boost
# -------------------------
find_package(Boost QUIET)
if (Boost_FOUND)
  message(STATUS "Found Boost: ${Boost_INCLUDE_DIRS}")
  target_include_directories(asls_core PRIVATE ${Boost_INCLUDE_DIRS})
  if (DEFINED Boost_LIBRARIES AND Boost_LIBRARIES)
    target_link_libraries(asls_core PRIVATE ${Boost_LIBRARIES})
  endif()
endif()

# -------------------------
# SFML (if GUI enabled)
# -------------------------
if (ASLS_ENABLE_GUI)
  # Try SFML 3 first (modern targets), fallback to SFML 2.5
  set(SFML_OK FALSE)
  find_package(SFML 3 QUIET COMPONENTS Window Graphics System)
  if (TARGET SFML::Graphics)
    message(STATUS "Found SFML 3 via imported targets")
    target_link_libraries(asls_core PUBLIC SFML::System SFML::Window SFML::Graphics)
    set(SFML_OK TRUE)
  else()
    find_package(SFML 2.5 QUIET COMPONENTS system window graphics)
    if (TARGET sfml-graphics OR TARGET sfml_graphics OR TARGET sfml-graphics-s)
      message(STATUS "Found SFML 2.x (legacy targets)")
      # prefer lowercase target names if present
      if (TARGET sfml-graphics)
        target_link_libraries(asls_core PUBLIC sfml-system sfml-window sfml-graphics)
      elseif (TARGET sfml_graphics)
        target_link_libraries(asls_core PUBLIC sfml_system sfml_window sfml_graphics)
      else()
        # fallback: try linking by name (platform specific)
        target_link_libraries(asls_core PUBLIC sfml-graphics sfml-window sfml-system)
      endif()
      set(SFML_OK TRUE)
    endif()
  endif()

  # Last-resort manual locate (Homebrew or /usr/local)
  if (NOT SFML_OK)
    message(STATUS "find_package(SFML) failed — trying common include/lib locations")
    find_path(SFML_INCLUDE_DIR SFML/Graphics.hpp
              PATHS /opt/homebrew/include /usr/local/include /usr/include NO_DEFAULT_PATH)
    find_library(SFML_GRAPHICS_LIB NAMES sfml-graphics sfml_graphics
                 PATHS /opt/homebrew/lib /usr/local/lib /usr/lib NO_DEFAULT_PATH)
    if (SFML_INCLUDE_DIR AND SFML_GRAPHICS_LIB)
      message(STATUS "Manually found SFML headers in ${SFML_INCLUDE_DIR} and libs in ${SFML_GRAPHICS_LIB}")
      target_include_directories(asls_core PUBLIC ${SFML_INCLUDE_DIR})
      target_link_libraries(asls_core PUBLIC ${SFML_GRAPHICS_LIB})
    else()
      message(FATAL_ERROR "ASLS_ENABLE_GUI=ON but SFML could not be found. Install SFML (e.g. `brew install sfml`) or set CMAKE_PREFIX_PATH/SFML_DIR.")
    endif()
  endif()
else()
  message(STATUS "ASLS_ENABLE_GUI=OFF — building headless/core without SFML")
endif()

# -------------------------
# Executable target
# -------------------------
if (ASLS_MAIN_SRC)
  add_executable(ASLS ${ASLS_MAIN_SRC})
  target_link_libraries(ASLS PRIVATE asls_core)

  # propagate resource dir as a preprocessor define for runtime usage
  target_compile_definitions(ASLS PRIVATE RESOURCE_DIR=\"${PATH_RESOURCES}\")

  # if using ASAN, also apply to executable
  if (ASLS_ENABLE_ASAN AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(ASLS PRIVATE
      $<$<CONFIG:Debug>:-g -fsanitize=address -fno-omit-frame-pointer>
    )
    target_link_options(ASLS PRIVATE
      $<$<CONFIG:Debug>:-fsanitize=address>
    )
  endif()
else()
  message(WARNING "No main.cpp found under src/main. Skipping ASLS creation.")
endif()

# -------------------------
# Install rules (optional)
# -------------------------
include(GNUInstallDirs)
install(TARGETS ASLS RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS asls_core ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/asls
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

# -------------------------
# Diagnostics & summary
# -------------------------
message(STATUS "Project root: ${PATH_ROOT}")
message(STATUS "Resources dir: ${PATH_RESOURCES}")
message(STATUS "Generated dir: ${GENERATED_DIR}")
message(STATUS "GUI enabled: ${ASLS_ENABLE_GUI}")
message(STATUS "ASAN enabled: ${ASLS_ENABLE_ASAN}")
