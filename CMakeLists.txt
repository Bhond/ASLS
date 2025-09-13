cmake_minimum_required(VERSION 3.15)
project(ASLS_Core LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")

# Variables
set(PATH_ROOT ${CMAKE_SOURCE_DIR})
set(PATH_RESOURCES "${CMAKE_SOURCE_DIR}/res")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/main/common.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/main/common.hpp" @ONLY)

# 1) Help CMake find Homebrew’s SFML install:
#    this usually resolves to /opt/homebrew/opt/sfml
set(SFML_DIR "$(brew --prefix sfml)/lib/cmake/SFML")
list(APPEND CMAKE_PREFIX_PATH "${SFML_DIR}")

# 2) Find exactly the SFML modules you need (uppercase names!):
find_package(SFML 3.0 REQUIRED
  COMPONENTS
    Window
    Graphics
    System
)

# Boost
find_package(Boost)

# 3) Your library (or executable) target:
add_executable(${PROJECT_NAME}
  "src/main/main.cpp"
  "src/main/mymath.hpp"
  "src/main/common.hpp"
  "src/main/simulation.cpp"
  "src/main/simulation.hpp"
  "src/main/misc.hpp"
  "src/graphics/entities.hpp" 
  "src/graphics/entity.hpp" 
  "src/graphics/entity.cpp" 
  "src/graphics/entities.cpp" 
  "src/models/entitymodel.hpp" 
  "src/models/entitymodel.cpp"
  "src/models/solver.cpp"
  "src/models/solver.hpp"
  "src/models/genome.hpp"
  "src/models/genome.cpp"
  "src/graphics/groupcontrol.hpp" 
  "src/graphics/control.hpp"
  # "src/main/stats.hpp"
  # "src/main/stats.cpp"
  "src/models/model.hpp"
  "src/main/brain.hpp"
  "src/main/brain.cpp"
  "src/main/configreader.hpp"
  "src/main/configreader.cpp"
  # "src/models/foodmodel.hpp"
  # "src/models/foodmodel.cpp"
  # "src/graphics/foods.cpp"
  # "src/graphics/foods.hpp"
  # "src/graphics/food.cpp"
  # "src/graphics/food.hpp"
)

# 4) Link SFML imported-targets to your target.
#    This will automatically pull in the correct include dirs and dylibs.
target_link_libraries(${PROJECT_NAME}
    PRIVATE 
      SFML::System
      SFML::Window
      SFML::Graphics
)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR} )
target_link_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR} )
