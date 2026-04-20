#include <iostream>
#include "Clases/gestorarchivo.h"
#include "Clases/jugador.h"
#include "Clases/grupo.h"
#include "Clases//partido.h"

using namespace std;

int main()
{

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

    // ============== III ===========================
    //  a) Eliminatorias de grupo
    // 6 partidos por grupos
    short  partidosPorGrupo = 6;
    short  indexPartidos = 0;

    Partido* listaPartidos = new Partido[12*partidosPorGrupo];

    for (short  c = 0; c < numeroGrupos; c++){
        const short  equipo1 = listaGrupos[c].getEquiposRF()[0];
        const short  equipo2 = listaGrupos[c].getEquiposRF()[1];
        const short  equipo3 = listaGrupos[c].getEquiposRF()[2];
        const short  equipo4 =  listaGrupos[c].getEquiposRF()[3];

        listaPartidos[indexPartidos].setRankingFifaequip1(equipo1);
        listaPartidos[indexPartidos].setRankingFifaequip2(equipo2);
        indexPartidos++;

        listaPartidos[indexPartidos].setRankingFifaequip1(equipo1);
        listaPartidos[indexPartidos].setRankingFifaequip2(equipo3);
        indexPartidos++;

        listaPartidos[indexPartidos].setRankingFifaequip1(equipo1);
        listaPartidos[indexPartidos].setRankingFifaequip2(equipo4);
       indexPartidos++;

        listaPartidos[indexPartidos].setRankingFifaequip1(equipo2);
        listaPartidos[indexPartidos].setRankingFifaequip2(equipo3);
        indexPartidos++;

        listaPartidos[indexPartidos].setRankingFifaequip1(equipo2);
        listaPartidos[indexPartidos].setRankingFifaequip2(equipo4);
        indexPartidos++;

        listaPartidos[indexPartidos].setRankingFifaequip1(equipo3);
        listaPartidos[indexPartidos].setRankingFifaequip2(equipo4);
        indexPartidos++;
    }

    Partido **matrixPartidos = new Partido*[12];

    for (short i = 0; i < 12; i++) matrixPartidos[i] = new Partido[6];

    for (short i = 0; i < 72; i++) { // llenar la matriz por rondas
        short fila = i / 6;
        short col  = i % 6;

       matrixPartidos[fila][col] = listaPartidos[i];
    }

    delete[] listaPartidos;

    // generacion de fechas para cada partido segun las reglas
    //ocurrencia de goles (definir que equipo gano y actualizar estadisticas)
    short dias = 1;
    for (short col = 0; col < 6; col++){
        for (short row = 0; row < 12; row++){
            matrixPartidos[row][col].setDia(dias);
            matrixPartidos[row][col].generarFecha(dias);

            if (row == 3 || row == 7 || row == 11) dias++;

            //simulacion ocurrencia de goles
            matrixPartidos[row][col].simularOcurrencia(listaEquipos, numeroEquipos);
        }
    }






    for (short i = 0; i < 12; i++){
        for (short c = 0; c < 6; c++){
            cout <<  matrixPartidos[i][c].getRankingFifaequip1() <<"  " << matrixPartidos[i][c].getRankingFifaequip2() << "  " <<   matrixPartidos[i][c].getFecha() <<  "  |  ";
        }

        cout << endl;
    }




    delete gestorArchivo;
    delete[] listaEquipos;
    delete[] listaGrupos;
    return 0;
}
