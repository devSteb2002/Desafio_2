#ifndef PARTIDO_H
#define PARTIDO_H

#include "equipo.h"

class Partido{
    public:
    Partido();

    private:
        string    fecha;
        string    hora = "00:00";
        string    sede;
        string    codArbitro1 = "codArbitro1";
        string    codArbitro2 = "codArbitro1";
        string    codArbitro3 = "codArbitro1";
        short  rankingFifaequip1;
        short  rankingFifaequip2;
};

#endif // PARTIDO_H
