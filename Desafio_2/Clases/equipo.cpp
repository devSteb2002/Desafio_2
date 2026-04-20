#include "equipo.h"

Equipo::Equipo() {}



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

short Equipo::getTarjetasAmarillas() const
{
    return tarjetasAmarillas;
}

void Equipo::setTarjetasAmarillas(short newTarjetasAmarillas)
{
    tarjetasAmarillas = newTarjetasAmarillas;
}

short Equipo::getTarjetasRojas() const
{
    return tarjetasRojas;
}

void Equipo::setTarjetasRojas(short newTarjetasRojas)
{
    tarjetasRojas = newTarjetasRojas;
}

short Equipo::getCantidadFaltas() const
{
    return cantidadFaltas;
}

void Equipo::setCantidadFaltas(short newCantidadFaltas)
{
    cantidadFaltas = newCantidadFaltas;
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





