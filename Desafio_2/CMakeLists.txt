cmake_minimum_required(VERSION 3.16)

project(Desafio_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Desafio_2 main.cpp
    Clases/equipo.h Clases/equipo.cpp
    Clases/jugador.h Clases/jugador.cpp
    Clases/partido.h Clases/partido.cpp
    Clases/grupo.h Clases/grupo.cpp
    Clases/gestorarchivo.h Clases/gestorarchivo.cpp)

include(GNUInstallDirs)
install(TARGETS Desafio_2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
