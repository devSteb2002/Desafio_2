#ifndef GESTORARCHIVO_H
#define GESTORARCHIVO_H

#include "equipo.h"

class GestorArchivo{
    public:
        GestorArchivo(const string &nomArcEquipos, long & iteraciones, long &totalMemoria);
        void cargarEquipos( Equipo*& equipos, const string& nombreArchivo, long & iteraciones, long &totalMemoria);
        void guardarEquipos(Equipo*& equipos, const string& nombreArchivo );
        void guardarJugadores(Jugador *& jugadores, const string& nombreArchivo);

        short getNumeroDeEquipos() const;
        void setNumeroDeEquipos(short newNumeroDeEquipos);

    private:
        short  numeroDeEquipos = 0;

};

#endif // GESTORARCHIVO_H
