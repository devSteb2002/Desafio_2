#ifndef EQUIPO_H
#define EQUIPO_H

#include "jugador.h"
#include <iostream>

using namespace std;

class Equipo {
    public:
        Equipo();

        string getNombre() const;
        void setNombre(const string &newNombre);

    private:
        string       nombre;
        string       confederacion;
        string       pais;
        string       director;
        int            rankinFifa;
        short        golesAFavor;
        short        golesEnContra;
        short        partidosGanados;
        short        partidosEmpatados;
        short        partidosPerdidos;
        short        tarjetasAmarillas;
        short        tarjetasRojas;
        short        cantidadFaltas;
        Jugador*  juagores;

};

#endif // EQUIPO_H
