# Cmake version
cmake_minimum_required(VERSION 3.26)

# Variables
set(PATH_ROOT ${CMAKE_SOURCE_DIR})
set(PATH_SHADERS "${CMAKE_SOURCE_DIR}/assets/shaders")
set(PATH_SCRIPTS "${CMAKE_SOURCE_DIR}/scripts")
configure_file("main/common.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/main/common.h" @ONLY)

# Qt
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
if (${Qt5_FOUND})
    message("Found Qt: " ${Qt5_VERSION})
endif()

# SFML
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
if (${SFML_Found})
	message("Found SFML")
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
"main/vc.h"
"main/vc.cpp"
"main/misc.h"
"graphics/qsfmlcanvas.h"
"graphics/qsfmlcanvas.cpp"
"graphics/labelvaluepair.h"
"graphics/labelvaluepair.cpp"
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
"graphics/labelprogressbarpair.h"
"graphics/labelprogressbarpair.cpp" "models/model.h" "models/model.cpp")

# Links
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)