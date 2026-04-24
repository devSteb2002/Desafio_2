#include "grupo.h"
#include <random>

Grupo::Grupo() {}

void  Grupo::selecEquipos(short (&bombos)[4][12], Equipo *&listaEquipos, const short& numEquipos ){

    short  bomboFial = 0;
    short *equipos = new short[4];
    short random;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 11);

    while (bomboFial < 4){ // generacion aleatoria de los equipos segun este grupo
        string confederaciones[4] = {"", "", "", ""};
        bool   confValidas = true;

        for (short c = 0; c < 4; c++){
            if (confederaciones[c] == "") {
                confValidas = false;
                break;
            }
        }

        while (!confValidas){
            random = dis(gen);

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
                    if (confederaciones[c] == "UEFA" && cuantosUEFA < 2) {
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

    //hacer que el equipo de USA quede en el bombo 1
    short rankingFifaUsa;
    for (short f = 0; f < numEquipos; f++){
        if (listaEquipos[f].getPais() == "United States"){
            rankingFifaUsa = listaEquipos[f].getRankinFifa();
            break;
        }
    }

    for (short c = 0; c < 4; c++){
        if (equipos[c] == rankingFifaUsa && c > 0){
            short tempRanking = equipos[0];
            equipos[0] = rankingFifaUsa;
            equipos[c] = tempRanking;
            break;
        }
    }

    this->equiposRF = equipos;
}


void Grupo::ordenarPorPuntos(Equipo* listaGlobalEquipos, short totalEquipos) {
    // Usamos burbuja para ordenar los 4 equipos guardados en equiposRF
    for (short i = 0; i < 3; i++) {
        for (short j = 0; j < 3 - i; j++) {

            // Buscamos los punteros a los objetos Equipo correspondientes a los Rankings en la lista global
            Equipo* eqA = nullptr;
            Equipo* eqB = nullptr;

            for (short k = 0; k < totalEquipos; k++) {
                if (listaGlobalEquipos[k].getRankinFifa() == equiposRF[j]) eqA = &listaGlobalEquipos[k];
                if (listaGlobalEquipos[k].getRankinFifa() == equiposRF[j + 1]) eqB = &listaGlobalEquipos[k];
            }

            if (eqA != nullptr && eqB != nullptr) {
                // Calculamos Puntos y Diferencia de Goles
                short ptsA = eqA->getPartidosGanados() * 3 + eqA->getPartidosEmpatados();
                short ptsB = eqB->getPartidosGanados() * 3 + eqB->getPartidosEmpatados();
                short dgA = eqA->getGolesAFavor() - eqA->getGolesEnContra();
                short dgB = eqB->getGolesAFavor() - eqB->getGolesEnContra();

                bool intercambio = false;

                // CRITERIOS DE DESEMPATE:
                if (ptsA < ptsB) {
                    intercambio = true;
                } else if (ptsA == ptsB) {
                    if (dgA < dgB) {
                        intercambio = true;
                    } else if (dgA == dgB) {
                        if (eqA->getGolesAFavor() < eqB->getGolesAFavor()) {
                            intercambio = true;
                        }
                    }
                }

                if (intercambio) {
                    short temp = equiposRF[j];
                    equiposRF[j] = equiposRF[j + 1];
                    equiposRF[j + 1] = temp;
                }
            }
        }
    }
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



