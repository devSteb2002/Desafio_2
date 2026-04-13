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

        string cadena = "";
        for (short i = 0; i < linea.length(); i++){
            if (linea[i] == ';'){
                numerodeCara++;
                cadena = "";

                if (numerodeCara == 1){
                    equipos[indexEquipos].setNombre(cadena);
                }

                continue;
            }

             cadena += linea[i];

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
