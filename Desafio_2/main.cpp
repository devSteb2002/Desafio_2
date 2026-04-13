#include <iostream>
#include "Clases/gestorarchivo.h"

using namespace std;

int main()
{
    cout << " ============================ " << endl;
    cout << "          UdeAWorldCup                                 "  << endl;
    cout << " ============================" << endl;

    cout << endl;

    cout << "Simulando Eliminatorias de grupos..." << endl;

    const string archivoEquipos = "selecciones_clasificadas_mundial.csv";


    GestorArchivo* gestorArchivo = new GestorArchivo(archivoEquipos);
    Equipo* listaEquipos = new Equipo[gestorArchivo->getNumeroDeEquipos()];

    gestorArchivo->cargarEquipos(listaEquipos, archivoEquipos);

    for (short i = 0; i < gestorArchivo->getNumeroDeEquipos(); i++){
           cout << listaEquipos[i].getNombre() << endl;
    }





    delete gestorArchivo;
    delete[] listaEquipos;
    return 0;
}
