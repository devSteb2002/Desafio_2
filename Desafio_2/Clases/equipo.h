#ifndef EQUIPO_H
#define EQUIPO_H

#include "jugador.h"
#include <iostream>

using namespace std;

class Equipo {
    public:
        Equipo();

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
        short getTarjetasAmarillas() const;
        void setTarjetasAmarillas(short newTarjetasAmarillas);
        short getTarjetasRojas() const;
        void setTarjetasRojas(short newTarjetasRojas);
        short getCantidadFaltas() const;
        void setCantidadFaltas(short newCantidadFaltas);
        Jugador *getJuagores() const;
        void setJuagores(Jugador *newJuagores);
        string getFederacion() const;
        void setFederacion(const string &newFederacion);

        ~Equipo();

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
        short        tarjetasAmarillas;
        short        tarjetasRojas;
        short        cantidadFaltas;
        Jugador*  juagores;
        bool         eliminado = false;
        string       fase = "NA";

};

#endif // EQUIPO_H
