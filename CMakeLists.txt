# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("TP1_Reseau")

add_subdirectory(src)

add_executable("client" "src/client.cpp")
add_executable("server" "src/server.cpp")