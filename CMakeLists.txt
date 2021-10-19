# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("TPs_Reseau")



##########La lib du TP1
set(TP1_libSocket_SRC 
                        "libSocket/client.cpp"
                        "libSocket/server.cpp"
						"libSocket/Terminal.cpp"
						"libSocket/Connection.cpp"
						"libSocket/UDPConnection.cpp"
						"libSocket/TCPConnection.cpp"
						"libSocket/Network.cpp"
						"libSocket/SocketManager.cpp"
						)

set(TP1_libSocket_HEADERS "libSocket/client.h"
                            "libSocket/server.h"
							"libSocket/Connection.h"
							"libSocket/Terminal.h"
							"libSocket/UDPConnection.h"
							"libSocket/TCPConnection.h"
							"libSocket/Network.h"
							"libSocket/SocketManager.h")

add_library(TP1_libSocket STATIC ${TP1_libSocket_SRC} ${TP1_libSocket_HEADERS})

##########

##########La lib du TP2
set(TP2_libSerializer_SRC 
                        "libSerializer/framework.cpp"
						)

set(TP2_libSerializer_HEADERS
						"libSerializer/framework.h"
						)

add_library(TP2_libSerializer STATIC ${TP2_libSerializer_SRC} ${TP2_libSerializer_HEADERS})

##########


#Les executables du TP1
add_executable( "TP1_Server" "libSocket/mainServer.cpp" )
target_link_libraries( "TP1_Server" PUBLIC TP1_libSocket )

add_executable( "TP1_Client" "libSocket/mainClient.cpp" )
target_link_libraries( "TP1_Client" PUBLIC TP1_libSocket )


#L'executable du TP2
add_executable( "TP2_PlayerSerialization" "libSerializer/mainSerialization.cpp" "libSerializer/Player.cpp" "libSerializer/Player.h")
target_link_libraries( "TP2_PlayerSerialization" PUBLIC TP2_libSerializer )

