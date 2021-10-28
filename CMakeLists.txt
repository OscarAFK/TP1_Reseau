# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("TP3_Reseau")


include(FetchContent)

FetchContent_Declare(
  TP1_Reseau_Sockets
  GIT_REPOSITORY https://github.com/OscarAFK/TP1_Reseau_Sockets.git
  GIT_TAG        9649226bfa9ac71b1e93050b4e4063283b918a5d
)

FetchContent_Declare(
  TP2_Reseau_Serialization
  GIT_REPOSITORY https://github.com/OscarAFK/TP2_Reseau_Serialization.git
  GIT_TAG        277c702454fdf51a8f721872cca8f0f9f8c4408c
)

FetchContent_MakeAvailable(TP1_Reseau_Sockets)
FetchContent_MakeAvailable(TP2_Reseau_Serialization)

##########La lib d'utilities
set(Utils_SRC 
                        "utils/framework.cpp"
                        "utils/NetworkObject.cpp"
                        "utils/Enemy.cpp"
                        "utils/Player.cpp"
						)

set(Utils_HEADERS 
							"utils/framework.h"
                            "utils/NetworkObject.h"
                            "utils/Enemy.h"
                            "utils/Player.h")

add_library(Utils_TP3 STATIC ${Utils_SRC} ${Utils_HEADERS})

##########

##########La lib du TP3
set(TP3_libReplication_SRC 
                        "libReplication/ClassRegistry.cpp"
						"libReplication/ReplicationManager.cpp"
						"libReplication/LinkingContext.cpp"
						)

set(TP3_libReplication_HEADERS
						"libReplication/ClassRegistry.h"
						"libReplication/ReplicationManager.h"
						"libReplication/LinkingContext.h"
						)

add_library(TP3_libReplication STATIC ${TP3_libReplication_SRC} ${TP3_libReplication_HEADERS})

##########

#Les executables du TP3
add_executable( "TP3_Server" "libReplication/mainServer.cpp" )
target_link_libraries( "TP3_Server" PUBLIC TP3_libReplication )
target_link_libraries( "TP3_Server" PUBLIC Utils_TP3 )

add_executable( "TP3_Client" "libReplication/mainClient.cpp" )
target_link_libraries( "TP3_Client" PUBLIC TP3_libReplication )
target_link_libraries( "TP3_Client" PUBLIC Utils_TP3 )

