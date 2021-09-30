# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("TP1_Reseau")

set(${PROJECT_NAME}_SRC 
                        "src/client.cpp"
                        "src/server.cpp")

set(${PROJECT_NAME}_HEADERS "src/client.h"
                            "src/server.h"
							"src/Connection.h"
							"src/Terminal.h"
							"src/UDPConnection.h"
							"src/TCPConnection.h"
							"src/MotherClass.h")

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})