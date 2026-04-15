#include "grupo.h"
#include <cstdlib>
#include <ctime>

Grupo::Grupo() {}

void  Grupo::selecEquipos(short (&bombos)[4][12], Equipo *&listaEquipos, const short& numEquipos ){

    short  bomboFial = 0;
    short *equipos = new short[4];
    string confederaciones[4] = {"", "", "", ""};
    short random;

    while (bomboFial < 4){

        short intentos = 0;
        while (intentos < 320){
            intentos++;
            random = rand() % 12;

            if (bombos[bomboFial][random] == -1) continue;
            short rankingFifa  = bombos[bomboFial][random];


            bool encontrado = false;
            bool yaExiste = false;
            short cuantosUEFA = 0;

            for (short c = 0; c < numEquipos; c++){
                if (listaEquipos[c].getRankinFifa() == rankingFifa){
                    confederaciones[bomboFial] = listaEquipos[c].getConfederacion();
                    encontrado = true;
                    break;
                }
            }

            if(!encontrado) continue;

            for (short c = 0; c < 4; c++) if (confederaciones[c] == "UEFA") cuantosUEFA++;

            for (short c = 0; c < 4; c++){
                if (confederaciones[c] == "") continue;

                if (c != bomboFial && confederaciones[c] == confederaciones[bomboFial]) {
                    if (confederaciones[c] == "UEFA" && cuantosUEFA <= 2) {
                        yaExiste = false;
                        break;
                    }

                    yaExiste = true;
                }
            }

            if (yaExiste) continue;

            bombos[bomboFial][random] = -1;
            equipos[bomboFial] = rankingFifa;

            break;
        }

        bomboFial++;
    }

    this->equiposRF = equipos;
}

Grupo::~Grupo(){
    if (this->equiposRF != nullptr){
        delete[] this->equiposRF;
    }
}


char Grupo::getId() const
{
    return id;
}

void Grupo::setId(char newId)
{
    id = newId;
}

short *Grupo::getEquiposRF() const
{
    return equiposRF;
}

void Grupo::setEquiposRF(short *newEquiposRF)
{
    equiposRF = newEquiposRF;
}
