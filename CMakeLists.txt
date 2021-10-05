# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("TP1_Reseau")

set(${PROJECT_NAME}_SRC 
                        "src/client.cpp"
                        "src/server.cpp"
						"src/Terminal.cpp"
						"src/Connection.cpp"
						"src/Network.cpp"
						)

set(${PROJECT_NAME}_HEADERS "src/client.h"
                            "src/server.h"
							"src/Connection.h"
							"src/Terminal.h"
							"src/UDPConnection.h"
							"src/TCPConnection.h"
							"src/Network.h"
							"src/MotherClass.h")

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})

add_executable( "server" "src/mainServer.cpp" )
target_link_libraries( "server" PUBLIC ${PROJECT_NAME} )

add_executable( "client" "src/mainClient.cpp" )
target_link_libraries( "client" PUBLIC ${PROJECT_NAME} )