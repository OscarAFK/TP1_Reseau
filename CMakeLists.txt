﻿# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project ("TP3_Reseau")

add_subdirectory(includes)

##########La lib d'utilities
set(Utils_TP3_SRC 
                        "utils/NetworkObject.cpp"
                        "utils/Enemy.cpp"
                        "utils/PlayerTP3.cpp"
                        "utils/frameworkTP3.cpp"
						)

set(Utils_TP3_HEADERS 
							"utils/frameworkTP3.h"
                            "utils/NetworkObject.h"
                            "utils/Enemy.h"
                            "utils/PlayerTP3.h")

add_library(Utils_TP3 STATIC ${Utils_TP3_SRC} ${Utils_TP3_HEADERS})
target_link_libraries( Utils_TP3 PUBLIC TP2_libSerializer)
target_include_directories(Utils_TP3 PUBLIC utils)

##########

##########La lib du TP3
set(TP3_libReplication_SRC 
                        "libReplication/src/ClassRegistry.cpp"
						"libReplication/src/ReplicationManager.cpp"
						"libReplication/src/LinkingContext.cpp"
						)

set(TP3_libReplication_HEADERS
						"libReplication/include/ClassRegistry.h"
						"libReplication/include/ReplicationManager.h"
						"libReplication/include/LinkingContext.h"
						)

add_library(TP3_libReplication STATIC ${TP3_libReplication_SRC} ${TP3_libReplication_HEADERS})
target_link_libraries( TP3_libReplication PUBLIC UQACNetwork TP2_libSerializer Utils_TP3)
target_include_directories(TP3_libReplication PUBLIC libReplication)
target_include_directories(TP3_libReplication PUBLIC includes)

##########

target_include_directories(TP3_libReplication PUBLIC Utils_TP3)
target_include_directories(Utils_TP3 PUBLIC libReplication)

#Les executables du TP3
add_executable( TP3_Server "libReplication/src/main.cpp" )
target_link_libraries( TP3_Server PUBLIC TP3_libReplication Utils_TP3)