#include "jugador.h"

Jugador::Jugador() {}


void Jugador::actualizarDatos(const short&  goles, const short& amarillas, const short& rojas, const short& faltas, const string &etapaEnQueJuega){
    this->setNumeroGoles(this->getNumeroGoles() + goles);
    this->setCaTarAmarilla(this->getCaTarAmarilla() + amarillas);
    this->setCaTarRojas(this->getCaTarRojas() + rojas);
    this->setCaFaltas(this->getCaFaltas() + faltas);
    this->setEtapaEnQueJuega(etapaEnQueJuega);
}

string Jugador::getNombre() const
{
    return nombre;
}

void Jugador::setNombre(const string &newNombre)
{
    nombre = newNombre;
}

string Jugador::getApellido() const
{
    return apellido;
}

void Jugador::setApellido(const string &newApellido)
{
    apellido = newApellido;
}

short Jugador::getNumeroCamisa() const
{
    return numeroCamisa;
}

void Jugador::setNumeroCamisa(short newNumeroCamisa)
{
    numeroCamisa = newNumeroCamisa;
}

short Jugador::getPartidosJugados() const
{
    return partidosJugados;
}

void Jugador::setPartidosJugados(short newPartidosJugados)
{
    partidosJugados = newPartidosJugados;
}

short Jugador::getNumeroGoles() const
{
    return numeroGoles;
}

void Jugador::setNumeroGoles(short newNumeroGoles)
{
    numeroGoles = newNumeroGoles;
}

int Jugador::getMinutosTotalesJ() const
{
    return minutosTotalesJ;
}

void Jugador::setMinutosTotalesJ(int newMinutosTotalesJ)
{
    minutosTotalesJ = newMinutosTotalesJ;
}

short Jugador::getAsistencias() const
{
    return asistencias;
}

void Jugador::setAsistencias(short newAsistencias)
{
    asistencias = newAsistencias;
}

short Jugador::getCaTarAmarilla() const
{
    return caTarAmarilla;
}

void Jugador::setCaTarAmarilla(short newCaTarAmarilla)
{
    caTarAmarilla = newCaTarAmarilla;
}

short Jugador::getCaTarRojas() const
{
    return caTarRojas;
}

void Jugador::setCaTarRojas(short newCaTarRojas)
{
    caTarRojas = newCaTarRojas;
}

short Jugador::getCaFaltas() const
{
    return caFaltas;
}

void Jugador::setCaFaltas(short newCaFaltas)
{
    caFaltas = newCaFaltas;
}

bool Jugador::getJuega() const
{
    return juega;
}

void Jugador::setJuega(bool newJuega)
{
    juega = newJuega;
}

string Jugador::getEtapaEnQueJuega() const
{
    return etapaEnQueJuega;
}

void Jugador::setEtapaEnQueJuega(const string &newEtapaEnQueJuega)
{
    etapaEnQueJuega = newEtapaEnQueJuega;
}



