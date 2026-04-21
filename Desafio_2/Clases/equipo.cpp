#include "equipo.h"
#include <random>

Equipo::Equipo() {}

void Equipo::seleccionarJugadores(short *&listaJugadores){

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 26);

    short random;
    bool completo = false;

    for (short i = 0; i < 11; i++) listaJugadores[i] = 0;

    while (!completo){
        completo = true;
        for (short c = 0; c < 11; c++){
            if (listaJugadores[c] == 0) {
                completo = false;
                break;
            }
        }

        random = dis(gen);
        bool   yaSeleccionado = false;

        for (short i = 0; i < 11; i++){
            if (listaJugadores[i] == random) {
                yaSeleccionado = true;
                break;
            }
        }

        if (!yaSeleccionado){
            for (short c = 0; c < 11; c++){
                if (listaJugadores[c] == 0){
                    listaJugadores[c] = random;
                    break;
                }
            }
        }
    }

}

void Equipo::metricasJugadores(short *&listaJugadores, const float &golesEsperados, const string &etapa){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);
    float golesContabilizados = 0.0;
    short golesJugador[11] = {0};
    short tarAmarillas[11] = {0};
    short tarRojas[11] = {0};
    short faltas[11] = {0};
    short posesionBalon[11] = {0};
    int intentosMaximos = 40;
    int intentos = 0;

    while (golesContabilizados < golesEsperados && intentos < intentosMaximos){
        intentos++;

        if (golesContabilizados >= golesEsperados) break;

        for (short c = 0; c < 11; c++){
            short random = dis(gen);

            //goles (4%)
            if (golesContabilizados < golesEsperados){
                if (random <= 400){
                    golesJugador[c] += 1;
                    golesContabilizados++;
                }
            }

            //faltas
            random = dis(gen);

             if (faltas[c] == 0){
                if (random <= 1300) faltas[c] = 1;
            } else if (faltas[c] == 1){
                if (random <= 275) faltas[c] = 2;
            } else if (faltas[c] == 2){
                if (random <= 70) faltas[c] = 3;
            }

            //amarillas y tojas
            random = dis(gen);

            if (tarRojas[c] == 0){
                 if (tarAmarillas[c] == 0){
                    if (random <= 600) tarAmarillas[c] = 1;
                }
                else if (tarAmarillas[c]  == 1){
                     if (random <= 115) tarAmarillas[c] = 2;
                }

                if (tarAmarillas[c] == 2) tarRojas[c] = 1;
            }

            //falta posesion del balo;

        }
    }

    for (short c = 0; c < 11; c++){
        for (short i = 0; i < 26; i++){
            if (listaJugadores[c] == this->juagores[i].getNumeroCamisa()){
                this->juagores[i].actualizarDatos(golesJugador[c], tarAmarillas[c], tarRojas[c], faltas[c], etapa);
            }
        }
    }

}


short Equipo::obtenerGoleador(){

    short numeroCamisa = 1;
    short numeroGoles = 0;

    for (short c = 0; c < 26; c++){
        if (this->juagores[c].getEtapaEnQueJuega() == "EL"){
            if (this->juagores[c].getNumeroGoles() > numeroGoles){
                numeroGoles = this->juagores[c].getNumeroGoles();
                numeroCamisa = this->juagores[c].getNumeroCamisa();
            }
        }
    }

    return numeroCamisa;
}

Equipo:: ~Equipo(){
    if (this->juagores != nullptr) delete[] this->juagores;
}

short Equipo::getPartidosJugados() const
{
    return partidosJugados;
}

void Equipo::setPartidosJugados(short newPartidosJugados)
{
    partidosJugados = newPartidosJugados;
}

short Equipo::getPuntos() const
{
    return puntos;
}

void Equipo::setPuntos(short newPuntos)
{
    puntos = newPuntos;
}

string Equipo::getConfederacion() const
{
    return confederacion;
}

void Equipo::setConfederacion(const string &newConfederacion)
{
    confederacion = newConfederacion;
}

string Equipo::getPais() const
{
    return pais;
}

void Equipo::setPais(const string &newPais)
{
    pais = newPais;
}

string Equipo::getDirector() const
{
    return director;
}

void Equipo::setDirector(const string &newDirector)
{
    director = newDirector;
}

int Equipo::getRankinFifa() const
{
    return rankinFifa;
}

void Equipo::setRankinFifa(int newRankinFifa)
{
    rankinFifa = newRankinFifa;
}

short Equipo::getGolesAFavor() const
{
    return golesAFavor;
}

void Equipo::setGolesAFavor(short newGolesAFavor)
{
    golesAFavor = newGolesAFavor;
}

short Equipo::getGolesEnContra() const
{
    return golesEnContra;
}

void Equipo::setGolesEnContra(short newGolesEnContra)
{
    golesEnContra = newGolesEnContra;
}

short Equipo::getPartidosGanados() const
{
    return partidosGanados;
}

void Equipo::setPartidosGanados(short newPartidosGanados)
{
    partidosGanados = newPartidosGanados;
}

short Equipo::getPartidosEmpatados() const
{
    return partidosEmpatados;
}

void Equipo::setPartidosEmpatados(short newPartidosEmpatados)
{
    partidosEmpatados = newPartidosEmpatados;
}

short Equipo::getPartidosPerdidos() const
{
    return partidosPerdidos;
}

void Equipo::setPartidosPerdidos(short newPartidosPerdidos)
{
    partidosPerdidos = newPartidosPerdidos;
}

Jugador *Equipo::getJuagores() const
{
    return juagores;
}

void Equipo::setJuagores(Jugador *newJuagores)
{
    juagores = newJuagores;
}

string Equipo::getFederacion() const
{
    return federacion;
}

void Equipo::setFederacion(const string &newFederacion)
{
    federacion = newFederacion;
}





