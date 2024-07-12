# Cmake version
cmake_minimum_required(VERSION 3.26)

# Variables
set(PATH_ROOT ${CMAKE_SOURCE_DIR})
set(PATH_RESOURCES "${CMAKE_SOURCE_DIR}/res")
configure_file("main/common.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/main/common.h" @ONLY)

# SFML
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
if (${SFML_Found})
	message("Found SFML")
endif()

# Boost
find_package(Boost)
if (${Boost_FOUND})
	message("Found Boost")
endif()

# Exec
add_executable(${PROJECT_NAME}
"main/main.cpp"
"main/mymath.h"
"main/common.h"
"main/simulation.cpp"
"main/simulation.h"
"main/app.cpp"
"main/app.h"


"main/misc.h"




"graphics/entities.h" 
"graphics/entity.h" 
"graphics/entity.cpp" 
"graphics/entities.cpp" 
"models/entitymodel.h" 
"models/entitymodel.cpp"
"models/solver.cpp"
"models/solver.h"
"models/genome.h"
"models/genome.cpp"
"graphics/groupcontrol.h" 
"graphics/control.h"
"main/stats.h"
"main/stats.cpp"


"models/model.h"
"models/model.cpp"


"main/brain.h"
"main/brain.cpp"
"main/configreader.h"
"main/configreader.cpp"
"models/foodmodel.h"
"models/foodmodel.cpp"
"graphics/foods.cpp"
"graphics/foods.h"
"graphics/food.cpp"
"graphics/food.h")

# Links
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR} )
target_link_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR} )