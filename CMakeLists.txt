# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("TP_Reseau")



##########La lib du TP1
set(${PROJECT_NAME}_libSocket_SRC 
                        "libSocket/client.cpp"
                        "libSocket/server.cpp"
						"libSocket/Terminal.cpp"
						"libSocket/Connection.cpp"
						"libSocket/UDPConnection.cpp"
						"libSocket/TCPConnection.cpp"
						"libSocket/Network.cpp"
						"libSocket/SocketManager.cpp"
						)

set(${PROJECT_NAME}_libSocket_HEADERS "libSocket/client.h"
                            "libSocket/server.h"
							"libSocket/Connection.h"
							"libSocket/Terminal.h"
							"libSocket/UDPConnection.h"
							"libSocket/TCPConnection.h"
							"libSocket/Network.h"
							"libSocket/SocketManager.h")

add_library(${PROJECT_NAME}_libSocket STATIC ${${PROJECT_NAME}_libSocket_SRC} ${${PROJECT_NAME}_libSocket_HEADERS})

##########

##########La lib du TP2
set(${PROJECT_NAME}_libSerializer_SRC 
                        "libSerializer/framework.cpp"
                        "libSerializer/Serializer.cpp"
                        "libSerializer/Compressor.cpp"                        
						)

set(${PROJECT_NAME}_libSerializer_HEADERS
						"libSerializer/framework.h"
						"libSerializer/Serializer.h"
						"libSerializer/Compressor.h"
						)

add_library(${PROJECT_NAME}_libSerializer STATIC ${${PROJECT_NAME}_libSerializer_SRC} ${${PROJECT_NAME}_libSerializer_HEADERS})

##########


#Les executables du TP1
add_executable( "server" "libSocket/mainServer.cpp" )
target_link_libraries( "server" PUBLIC ${PROJECT_NAME}_libSocket )

add_executable( "client" "libSocket/mainClient.cpp" )
target_link_libraries( "client" PUBLIC ${PROJECT_NAME}_libSocket )

add_executable( "compressor" "libSerializer/mainCompressor.cpp" )
target_link_libraries( "compressor" PUBLIC ${PROJECT_NAME}_libSerializer )

