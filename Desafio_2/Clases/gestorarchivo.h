#ifndef GESTORARCHIVO_H
#define GESTORARCHIVO_H

#include "equipo.h"

class GestorArchivo{
    public:
        GestorArchivo(const string &nomArcEquipos);
        void cargarEquipos( Equipo*& equipos, const string& nombreArchivo);
        void guardarEquipos(Equipo*& equipos, const string& nombreArchivo );
        void guardarJugadores(Jugador *& jugadores, const string& nombreArchivo);

        short getNumeroDeEquipos() const;
        void setNumeroDeEquipos(short newNumeroDeEquipos);

    private:
        short  numeroDeEquipos = 0;

};

#endif // GESTORARCHIVO_H
