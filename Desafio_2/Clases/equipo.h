#ifndef EQUIPO_H
#define EQUIPO_H

#include "jugador.h"
#include <iostream>

using namespace std;

class Equipo {
    public:
        Equipo();

        void seleccionarJugadores(short *& listaJugadores, int& iteraciones, int& totalMemoria);
        void metricasJugadores(short *& listaJugadores, const float& golesEsperados, const string&etapa,int& iteraciones, int& totalMemoria);
        short obtenerGoleador(int& iteraciones, int& totalMemoria);

        string getConfederacion() const;
        void setConfederacion(const string &newConfederacion);
        string getPais() const;
        void setPais(const string &newPais);
        string getDirector() const;
        void setDirector(const string &newDirector);
        int getRankinFifa() const;
        void setRankinFifa(int newRankinFifa);
        short getGolesAFavor() const;
        void setGolesAFavor(short newGolesAFavor);
        short getGolesEnContra() const;
        void setGolesEnContra(short newGolesEnContra);
        short getPartidosGanados() const;
        void setPartidosGanados(short newPartidosGanados);
        short getPartidosEmpatados() const;
        void setPartidosEmpatados(short newPartidosEmpatados);
        short getPartidosPerdidos() const;
        void setPartidosPerdidos(short newPartidosPerdidos);
        Jugador *getJuagores() const;
        void setJuagores(Jugador *newJuagores);
        string getFederacion() const;
        void setFederacion(const string &newFederacion);

        ~Equipo();

        short getPartidosJugados() const;
        void setPartidosJugados(short newPartidosJugados);

        short getPuntos() const;
        void setPuntos(short newPuntos);

        string getFase() const;
        void setFase(const string &newFase);

    private:
        string       confederacion;
        string       federacion;
        string       pais;
        string       director;
        int            rankinFifa;
        short        golesAFavor;
        short        golesEnContra;
        short        partidosGanados;
        short        partidosEmpatados;
        short        partidosPerdidos;
        short        partidosJugados = 0;
        short        puntos;
        Jugador*  juagores;
        bool         eliminado = false;
        string       fase = "Eliminatorias";

};

#endif // EQUIPO_H
