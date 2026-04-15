#include <iostream>
#include "Clases/gestorarchivo.h"
#include "Clases/jugador.h"
#include "Clases/grupo.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));

    cout << " ============================ " << endl;
    cout << "          UdeAWorldCup                                 "  << endl;
    cout << " ============================" << endl;

    cout << endl;

    cout << "Simulando Eliminatorias de grupos..." << endl;

    short numeroGrupos = 12;
    const string letras      = "ABCDEFGHIJKL";

    // ========= I ================ //
    const string archivoEquipos = "selecciones_clasificadas_mundial.csv";
    GestorArchivo* gestorArchivo = new GestorArchivo(archivoEquipos);

    const short  numeroEquipos = gestorArchivo->getNumeroDeEquipos();
    Equipo* listaEquipos = new Equipo[numeroEquipos];
    Grupo*  listaGrupos  = new Grupo[numeroGrupos];

    gestorArchivo->cargarEquipos(listaEquipos, archivoEquipos); //llenar datos de los equipos en la lista de equipos

    for (short i = 0; i < numeroEquipos; i++){
        Jugador *jugadores = new Jugador[26]; //inicializar arreglo de 26 jugadores y añadirlo al equipo
        listaEquipos[i].setJuagores(jugadores); // añadir los 26 jugadores a cada equipo

        for (short  f = 0; f < 26; f++){ // definir valores iniciales para cada jugador
            listaEquipos[i].getJuagores()[f].setNombre("nombre" + to_string(f + 1));
            listaEquipos[i].getJuagores()[f].setApellido("apellido" + to_string(f + 1));
            listaEquipos[i].getJuagores()[f].setNumeroCamisa(f + 1);
        }
    }

      // ========= II ================ //
    short   bombos[4][12];
    short   salto = 0;
    short   indexFila = 0;

    for (short i = 0; i < numeroEquipos - 1; i++) { // metodo de burbuja para ordenar por rankingFifa
        for (short j = 0; j < numeroEquipos - i - 1; j++) {

            if (listaEquipos[j].getRankinFifa() > listaEquipos[j + 1].getRankinFifa()) {

                Equipo temp = listaEquipos[j];
                listaEquipos[j] = listaEquipos[j + 1];
                listaEquipos[j + 1] = temp;
            }
        }
    }

    for (short i = 0; i < numeroEquipos; i++){     //generar bombos
        bombos[indexFila][salto] = listaEquipos[i].getRankinFifa();

        if (salto == 11){
            salto = 0;
            indexFila++;
            continue;
        }
        salto++;
    }

    //generar los 12 grupos con 4 equipos de diferente bombos (clasificatorias)

    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|                                  CONFORMACION DE GRUPOS                      |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;


    for (short  i = 0; i < numeroGrupos; i++){
        listaGrupos[i].setId(letras[i]);
        listaGrupos[i].selecEquipos(bombos, listaEquipos, numeroEquipos);


        cout <<  "|   "  <<  listaGrupos[i].getId()     << "   => ";

        for (short c = 0; c < 4; c++){
            string nombreEquipo = "";
            string nombreConfere = "";

            for (short f = 0; f < numeroEquipos; f++){
                if (listaEquipos[f].getRankinFifa() == listaGrupos[i].getEquiposRF()[c]){
                    nombreEquipo = listaEquipos[f].getPais();
                    nombreConfere = listaEquipos[f].getConfederacion();
                    break;
                }
            }

            cout << " " << nombreEquipo << "  (" << nombreConfere  << "),  ";
        }
        cout << endl;
    }

     cout << "---------------------------------------------------------------------------------------------------------------" << endl;

    for (short i = 0; i <4; i++){
        for (short f = 0; f < 12; f++){
            cout << bombos[i][f] << "   ";
        }

        cout << endl;
    }

    // ============== III ===========================



    delete gestorArchivo;
    delete[] listaEquipos;
    delete[] listaGrupos;
    return 0;
}
