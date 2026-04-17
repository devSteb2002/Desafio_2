#ifndef GRUPO_H
#define GRUPO_H

#include "equipo.h"


class Grupo{
    public:
    Grupo();
        void  selecEquipos(short (&bombos)[4][12], Equipo*& listaEquipos, const short &numEquipos);

        char getId() const;
        void setId(char newId);
        Equipo *getEquipos() const;
        void setEquipos(Equipo *newEquipos);

        short *getEquiposRF() const;
        void setEquiposRF(short *newEquiposRF);

         ~Grupo();
    private:
        char id;
        short*  equiposRF = nullptr;

};

#endif // GRUPO_H
