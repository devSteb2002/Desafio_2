#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
using namespace std;

class Jugador{
    public:
        Jugador();



    private:
        string    nombre;
        string    apellido;
        short     numeroCamisa;
        short     partidosJugados;
        short     numeroGoles;
        int         minutosTotalesJ;
        short     asistencias;
        short     caTarAmarilla;
        short     caTarRojas;
        short     caFaltas;
        bool       juega;
};

#endif // JUGADOR_H
