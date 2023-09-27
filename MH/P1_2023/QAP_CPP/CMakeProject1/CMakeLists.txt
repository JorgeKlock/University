# CMakeList.txt: proyecto de CMake para CMakeProject1, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeProject1")

# Agregue un origen al ejecutable de este proyecto.
add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h" "random.hpp")

# TODO: Agregue pruebas y destinos de instalación si es necesario.
