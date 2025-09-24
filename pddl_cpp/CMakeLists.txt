cmake_minimum_required(VERSION 3.0.2)
project(pddl_cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  pddl_msgs
  )

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES pddl_cpp
  CATKIN_DEPENDS actionlib
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
  include
 ${catkin_INCLUDE_DIRS}
)

 add_library(${PROJECT_NAME} SHARED
   src/pddl_cpp.cpp
 )

 target_link_libraries(${PROJECT_NAME}
   ${catkin_LIBRARIES}
   )

 add_executable(sample_hanoi
   sample/sample_hanoi.cpp)

 target_link_libraries(sample_hanoi
   ${PROJECT_NAME}
   )


#############
## Install ##
#############

 install(TARGETS ${PROJECT_NAME}
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
 )

 install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h"
   PATTERN ".svn" EXCLUDE
 )
