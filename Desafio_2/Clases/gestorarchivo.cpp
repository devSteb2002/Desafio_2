#include "gestorarchivo.h"
#include <fstream>

using namespace std;

GestorArchivo::GestorArchivo(const string &nomArcEquipos)  {
    ifstream archivo(nomArcEquipos);
    string     linea;
    int         cont = 0;

    if (!archivo.is_open()) return;
    while (getline(archivo, linea)) if (isdigit(linea[0])) cont++;

    this->setNumeroDeEquipos(cont);

    archivo.close();
}


void GestorArchivo::cargarEquipos( Equipo*& equipos, const string& nombreArchivo){
    ifstream archivo(nombreArchivo);
    string    linea;
    short     indexEquipos = 0;
    short     numerodeCara  = 0;

    if (!archivo.is_open()) return;

    while (getline(archivo, linea)){

        if (!isdigit(linea[0]) || linea.empty()) continue;

        const string formatLinea = ";" + linea;
        short   numOcurrecias = 0;
        short   indexCaracter = 0;

        while (numOcurrecias < 10){

            size_t   posicion1 = formatLinea.find(";", indexCaracter);
            size_t   posicion2 = formatLinea.find(";", posicion1 + 1);

            string  cadena = formatLinea.substr(posicion1 + 1,  posicion2 - posicion1 - 1);
            //cout << posicion1 << "   "  << posicion2 <<  "  " << cadena <<  "  " <<  numOcurrecias << endl;

            if (numOcurrecias == 0) equipos[indexEquipos].setRankinFifa(stoi(cadena));
            else if (numOcurrecias == 1) equipos[indexEquipos].setPais(cadena);
            else if (numOcurrecias == 2) equipos[indexEquipos].setDirector(cadena);
            else if (numOcurrecias == 3) equipos[indexEquipos].setFederacion(cadena);
            else if (numOcurrecias == 4) equipos[indexEquipos].setConfederacion(cadena);
            else if (numOcurrecias == 5) equipos[indexEquipos].setGolesAFavor(stoi(cadena));
            else if (numOcurrecias == 6) equipos[indexEquipos].setGolesEnContra(stoi(cadena));
            else if (numOcurrecias == 7) equipos[indexEquipos].setPartidosGanados(stoi(cadena));
            else if (numOcurrecias == 8) equipos[indexEquipos].setPartidosEmpatados(stoi(cadena));
            else if (numOcurrecias == 9) equipos[indexEquipos].setPartidosPerdidos(stoi(cadena));

            indexCaracter = posicion2;
            numOcurrecias++;
        }

         indexEquipos++;
    }


    archivo.close();
}

void GestorArchivo::guardarEquipos(Equipo*& equipos, const string& nombreArchivo ){

}



void GestorArchivo::guardarJugadores(Jugador *& jugadores, const string& nombreArchivo){

}



short GestorArchivo::getNumeroDeEquipos() const
{
    return numeroDeEquipos;
}

void GestorArchivo::setNumeroDeEquipos(short newNumeroDeEquipos)
{
    numeroDeEquipos = newNumeroDeEquipos;
}
