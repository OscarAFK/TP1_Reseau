cmake_minimum_required(VERSION 3.19)

set(${PROJECT_NAME}_Version ${Version})

set(${PROJECT_NAME}_SRC 
                        
                        "src/uqacNetwork.cpp"  "src/Connection.cpp" "src/Terminal.cpp")

set(${PROJECT_NAME}_HEADERS 
                           "include/UQACNetwork/uqacNetwork.hpp"  "include/UQACNetwork/config.hpp" "include/UQACNetwork/Terminal.hpp" "include/UQACNetwork/Connection.hpp"  "include/UQACNetwork/framework.hpp")

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include)