#include "partido.h"

Partido::Partido(){}

void Partido::generarFecha(const short &dia){
    const short diaBase = 20; // 20 de junio
    short  mes = 6;  // junio
    string fecha = "";

    if (dia + diaBase > 30) {
        short reinicioDia;
        mes = 7;
        reinicioDia = dia + diaBase - 30;
        fecha = to_string(reinicioDia) + "/" + to_string(mes) + "/2026";
        this->setFecha(fecha);
    }
    else {
        short newDia = diaBase + dia;
        fecha = to_string(newDia) + "/" + to_string(mes) + "/2026";
        this->setFecha(fecha);
    }
}

void Partido::simularOcurrencia(Equipo *& listaEquipos, const short &numEquipos, const string &etapa, long &iteraciones, long &totalMemoria){
    const float u = 1.35;
    const float a = 0.6;
    const float B = 0.4;
    float goleEsperadosEquipo1 = 0.0;
    float golesEsperadosEquipo2 = 0.0;

    for (short i = 0; i < numEquipos; i++){
        iteraciones++;
        if (listaEquipos[i].getRankinFifa() == this->rankingFifaequip1){
            const short golesAFavor    = listaEquipos[i].getGolesAFavor();
            const short golesEnContra = listaEquipos[i].getGolesEnContra();

            goleEsperadosEquipo1 = floor(u * pow((golesAFavor / u), a) * pow((golesEnContra / u), B));
        }

        if (listaEquipos[i].getRankinFifa() == this->rankingFifaequip2){
            const short golesAFavor    = listaEquipos[i].getGolesAFavor();
            const short golesEnContra = listaEquipos[i].getGolesEnContra();

            golesEsperadosEquipo2 = floor(u * pow((golesAFavor / u), a) * pow((golesEnContra / u), B));
        }
    }

    short *listaJugadoresA = new short[11];
    short *listaJugadoresB = new short[11];

    for (short i = 0; i < numEquipos; i++){
        iteraciones++;
        if (listaEquipos[i].getRankinFifa() == this->rankingFifaequip1){
            if (goleEsperadosEquipo1 > golesEsperadosEquipo2){
                listaEquipos[i].setPartidosGanados(listaEquipos[i].getPartidosGanados() + 1);
            }
            else if (goleEsperadosEquipo1 < golesEsperadosEquipo2){
                listaEquipos[i].setPartidosPerdidos(listaEquipos[i].getPartidosPerdidos() + 1);
            }
            else listaEquipos[i].setPartidosEmpatados(listaEquipos[i].getPartidosEmpatados() + 1);

            listaEquipos[i].setPartidosJugados(listaEquipos[i].getPartidosJugados() + 1);
            listaEquipos[i].seleccionarJugadores(listaJugadoresA);
            listaEquipos[i].metricasJugadores(listaJugadoresA, goleEsperadosEquipo1, etapa, iteraciones, totalMemoria);
        }

        if (listaEquipos[i].getRankinFifa() == this->rankingFifaequip2){
            if (goleEsperadosEquipo1 < golesEsperadosEquipo2){
                listaEquipos[i].setPartidosGanados(listaEquipos[i].getPartidosGanados() + 1);
            }
            else if (goleEsperadosEquipo1 > golesEsperadosEquipo2){
                listaEquipos[i].setPartidosPerdidos(listaEquipos[i].getPartidosPerdidos() + 1);
            }
            else listaEquipos[i].setPartidosEmpatados(listaEquipos[i].getPartidosEmpatados() + 1);

            listaEquipos[i].setPartidosJugados(listaEquipos[i].getPartidosJugados() + 1);
            listaEquipos[i].seleccionarJugadores(listaJugadoresB);
            listaEquipos[i].metricasJugadores(listaJugadoresB, golesEsperadosEquipo2, etapa, iteraciones, totalMemoria);
        }
    }

    delete[] listaJugadoresA;
    delete[] listaJugadoresB;
}


string Partido::getFecha() const
{
    return fecha;
}

void Partido::setFecha(const string &newFecha)
{
    fecha = newFecha;
}

string Partido::getHora() const
{
    return hora;
}

void Partido::setHora(const string &newHora)
{
    hora = newHora;
}

string Partido::getSede() const
{
    return sede;
}

void Partido::setSede(const string &newSede)
{
    sede = newSede;
}

string Partido::getCodArbitro1() const
{
    return codArbitro1;
}

void Partido::setCodArbitro1(const string &newCodArbitro1)
{
    codArbitro1 = newCodArbitro1;
}

string Partido::getCodArbitro2() const
{
    return codArbitro2;
}

void Partido::setCodArbitro2(const string &newCodArbitro2)
{
    codArbitro2 = newCodArbitro2;
}

string Partido::getCodArbitro3() const
{
    return codArbitro3;
}

void Partido::setCodArbitro3(const string &newCodArbitro3)
{
    codArbitro3 = newCodArbitro3;
}

short Partido::getRankingFifaequip1() const
{
    return rankingFifaequip1;
}

void Partido::setRankingFifaequip1(short newRankingFifaequip1)
{
    rankingFifaequip1 = newRankingFifaequip1;
}

short Partido::getRankingFifaequip2() const
{
    return rankingFifaequip2;
}

void Partido::setRankingFifaequip2(short newRankingFifaequip2)
{
    rankingFifaequip2 = newRankingFifaequip2;
}

bool Partido::getFinalizado() const
{
    return finalizado;
}

void Partido::setFinalizado(bool newFinalizado)
{
    finalizado = newFinalizado;
}

short Partido::getDia() const
{
    return dia;
}

void Partido::setDia(short newDia)
{
    dia = newDia;
}
Equipo** simularEtapaMataMata(Equipo** participantes, short numPartidos, string nombreEtapa, Equipo* listaTotal, short totalE, long &iteraciones, long&totalMemoria) {
    Equipo** ganadores = new Equipo*[numPartidos];

    // --- ESTO ES LO QUE FALTA: EL TÍTULO DE LA ETAPA ---
    cout << "\n==========================================================" << endl;
    cout << "          SIMULANDO: " << nombreEtapa << endl;
    cout << "==========================================================" << endl;

    for (short i = 0; i < numPartidos; i++) {
        iteraciones++;
        Equipo* e1 = participantes[i * 2];
        Equipo* e2 = participantes[i * 2 + 1];

        short* indicesE1 = new short[11];
        short* indicesE2 = new short[11];

        e1->seleccionarJugadores(indicesE1);
        e2->seleccionarJugadores(indicesE2);

        Partido p;
        p.setRankingFifaequip1(e1->getRankinFifa());
        p.setRankingFifaequip2(e2->getRankinFifa());

        short golesAntesE1 = e1->getGolesAFavor();
        short golesAntesE2 = e2->getGolesAFavor();

        p.simularOcurrencia(listaTotal, totalE, "EL", iteraciones, totalMemoria);

        short golesHoyE1 = e1->getGolesAFavor() - golesAntesE1;
        short golesHoyE2 = e2->getGolesAFavor() - golesAntesE2;

        e1->metricasJugadores(indicesE1, (float)golesHoyE1, nombreEtapa, iteraciones, totalMemoria);
        e2->metricasJugadores(indicesE2, (float)golesHoyE2, nombreEtapa, iteraciones, totalMemoria);

        // Lógica de Desempate
        if (golesHoyE1 == golesHoyE2) {
            if (e1->getRankinFifa() < e2->getRankinFifa()) {
                golesHoyE1++;
                e1->setGolesAFavor(e1->getGolesAFavor() + 1);
                ganadores[i] = e1;
                e2->setFase(nombreEtapa);
            } else {
                golesHoyE2++;
                e2->setGolesAFavor(e2->getGolesAFavor() + 1);
                ganadores[i] = e2;
                e1->setFase(nombreEtapa);
            }
            cout << "[RF] ";
        } else {
            if (golesHoyE1 > golesHoyE2) { ganadores[i] = e1; e2->setFase(nombreEtapa); }
            else { ganadores[i] = e2; e1->setFase(nombreEtapa); }
        }

        cout << e1->getPais() << " (" << golesHoyE1 << ") vs ("
             << golesHoyE2 << ") " << e2->getPais()
             << " | Goleador: " << e1->obtenerGoleador() << endl;

        delete[] indicesE1;
        delete[] indicesE2;
    }

    totalMemoria += sizeof(ganadores) * numPartidos;
    return ganadores;
}
