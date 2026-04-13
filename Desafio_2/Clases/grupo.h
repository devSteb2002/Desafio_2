#ifndef GRUPO_H
#define GRUPO_H

#include "equipo.h"

class Grupo{
    public:
        Grupo();

    private:
        char id;
        Equipo* equipos;
};

#endif // GRUPO_H
