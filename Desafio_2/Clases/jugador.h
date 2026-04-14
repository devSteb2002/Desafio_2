#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
using namespace std;

class Jugador{
    public:
        Jugador();



        string getNombre() const;
        void setNombre(const string &newNombre);
        string getApellido() const;
        void setApellido(const string &newApellido);
        short getNumeroCamisa() const;
        void setNumeroCamisa(short newNumeroCamisa);
        short getPartidosJugados() const;
        void setPartidosJugados(short newPartidosJugados);
        short getNumeroGoles() const;
        void setNumeroGoles(short newNumeroGoles);
        int getMinutosTotalesJ() const;
        void setMinutosTotalesJ(int newMinutosTotalesJ);
        short getAsistencias() const;
        void setAsistencias(short newAsistencias);
        short getCaTarAmarilla() const;
        void setCaTarAmarilla(short newCaTarAmarilla);
        short getCaTarRojas() const;
        void setCaTarRojas(short newCaTarRojas);
        short getCaFaltas() const;
        void setCaFaltas(short newCaFaltas);
        bool getJuega() const;
        void setJuega(bool newJuega);

    private:
        string    nombre;
        string    apellido;
        short     numeroCamisa;
        short     partidosJugados = 0;
        short     numeroGoles = 0;
        int         minutosTotalesJ = 0;
        short     asistencias = 0;
        short     caTarAmarilla = 0;
        short     caTarRojas  = 0;
        short     caFaltas  = 0;
        bool       juega;
};

#endif // JUGADOR_H
