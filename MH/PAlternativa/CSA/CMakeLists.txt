# CMakeList.txt: proyecto de CMake para CSA, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

project ("CSA")

# Agregue un origen al ejecutable de este proyecto.
add_executable (CSA "CSA.cpp" "CSA.h")

# TODO: Agregue pruebas y destinos de instalación si es necesario.
