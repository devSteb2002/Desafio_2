#ifndef PARTIDO_H
#define PARTIDO_H

#include "equipo.h"
#include <cmath>

class Partido{
    public:
    Partido();

        void  generarFecha(const short &dia, int &totalMemoria);
        void  simularOcurrencia(Equipo *& listaEquipos, const short &numEquipos, const string& etapa, int &iteraciones, int &totalMemoria);

        string getFecha() const;
        void setFecha(const string &newFecha);
        string getHora() const;
        void setHora(const string &newHora);
        string getSede() const;
        void setSede(const string &newSede);
        string getCodArbitro1() const;
        void setCodArbitro1(const string &newCodArbitro1);
        string getCodArbitro2() const;
        void setCodArbitro2(const string &newCodArbitro2);
        string getCodArbitro3() const;
        void setCodArbitro3(const string &newCodArbitro3);
        short getRankingFifaequip1() const;
        void setRankingFifaequip1(short newRankingFifaequip1);
        short getRankingFifaequip2() const;
        void setRankingFifaequip2(short newRankingFifaequip2);
        bool getFinalizado() const;
        void setFinalizado(bool newFinalizado);
        short getDia() const;
        void setDia(short newDia);
        static Equipo** simularEtapaMataMata(Equipo** participantes, short numPartidos,std::string nombreEtapa, Equipo* listaTotal, short totalEquipos,  int &iteraciones, int& totalMemoria);

    private:
        string    fecha;
        string    hora = "00:00";
        string    sede = "nombreSede";
        string    codArbitro1 = "codArbitro1";
        string    codArbitro2 = "codArbitro1";
        string    codArbitro3 = "codArbitro1";
        short     rankingFifaequip1;
        short     rankingFifaequip2;
        bool      finalizado = false;
        short     dia = 0;
};

#endif // PARTIDO_H
