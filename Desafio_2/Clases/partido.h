#ifndef PARTIDO_H
#define PARTIDO_H

#include "equipo.h"

class Partido{
    public:
        Partido();

    private:
        string    fecha;
        string    hora;
        string    sede;
        string    codArbitro1;
        string    codArbitro2;
        string    codArbitro3;
        Equipo* equipo1;
        Equipo* equipo2;
};

#endif // PARTIDO_H
