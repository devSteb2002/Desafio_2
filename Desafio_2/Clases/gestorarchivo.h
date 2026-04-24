#ifndef GESTORARCHIVO_H
#define GESTORARCHIVO_H

#include "equipo.h"

class GestorArchivo{
    public:
        GestorArchivo(const string &nomArcEquipos, int& iteraciones, int &totalMemoria);
        void cargarEquipos( Equipo*& equipos, const string& nombreArchivo, int & iteraciones, int &totalMemoria);
        void guardarEquipos(Equipo*& equipos, const string& nombreArchivo, int & iteraciones);
        void guardarEquipos(Equipo*& equipos, const string& nombreArchivo, int & iteraciones, bool jugadores);

        short getNumeroDeEquipos() const;
        void setNumeroDeEquipos(short newNumeroDeEquipos);

    private:
        short  numeroDeEquipos = 0;

};

#endif // GESTORARCHIVO_H
