#include <iostream>
#include "Clases/gestorarchivo.h"
#include "Clases/jugador.h"
#include "Clases/grupo.h"
#include "Clases//partido.h"
#include <iomanip>

using namespace std;

int main()
{

    int opcion;

    int iteraciones = 0;
    int totalMemoria = 0;

    short numeroGrupos = 12;
    short numeroEquipos = 0;

    GestorArchivo* gestorArchivo = nullptr;
    Equipo* listaEquipos = nullptr;
    Grupo* listaGrupos = nullptr;

    const string archivoEquipos = "selecciones_clasificadas_mundial.csv";
    const string letras = "ABCDEFGHIJKL";

    Partido** matrixPartidos = nullptr;
    Equipo** clasificados32 = nullptr;
    short contC = 0;

    Equipo** cabezas = nullptr;
    Equipo** segundos = nullptr;
    Equipo** terceros = nullptr;
    Equipo** lista32 = nullptr;

    // Punteros para los ganadores de cada fase
    Equipo** ganadores16 = nullptr;
    Equipo** ganadores8 = nullptr;
    Equipo** ganadores4 = nullptr;
    Equipo** finalistas = nullptr;
    Equipo** podio = nullptr;
    Equipo** perdedoresSemis = nullptr;
    Equipo** tercerLugarArreglo = nullptr;

    do {
        cout << "\n===== MENU UdeAWorldCup =====\n";
        cout << "1. Cargar datos\n";
        cout << "2. Generar grupos\n";
        cout << "3. Simular fase de grupos\n";
        cout << "4. Mostrar tabla\n";
        cout << "5. Eliminatorias\n";
        cout << "6. Estadisticas finales\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if(opcion == 1) {
            cout << "Cargando datos...\n";
            cout << " ====================================================================================" << endl;
            cout << "                                  UdeAWorldCup                                 "  << endl;
            cout << " ====================================================================================" << endl;
            cout << endl;
            cout << "Cargando datos...\n";

            if(gestorArchivo != nullptr) delete gestorArchivo;
            if(listaEquipos != nullptr) delete[] listaEquipos;
            if(listaGrupos != nullptr) delete[] listaGrupos;

            gestorArchivo = new GestorArchivo(archivoEquipos, iteraciones, totalMemoria);

            numeroEquipos = gestorArchivo->getNumeroDeEquipos();

            totalMemoria += sizeof(gestorArchivo) + sizeof(archivoEquipos) + sizeof(numeroEquipos);

            listaEquipos = new Equipo[numeroEquipos];
            listaGrupos  = new Grupo[numeroGrupos];

            totalMemoria += sizeof(listaEquipos) * numeroEquipos + sizeof(listaGrupos) * numeroGrupos;

            gestorArchivo->cargarEquipos(listaEquipos, archivoEquipos, iteraciones, totalMemoria);

            for (short i = 0; i < numeroEquipos; i++){
                Jugador *jugadores = new Jugador[26];
                listaEquipos[i].setJuagores(jugadores);

                for (short f = 0; f < 26; f++){
                    listaEquipos[i].getJuagores()[f].setNombre("nombre" + to_string(f + 1));
                    listaEquipos[i].getJuagores()[f].setApellido("apellido" + to_string(f + 1));
                    listaEquipos[i].getJuagores()[f].setNumeroCamisa(f + 1);
                }
            }

            totalMemoria += numeroEquipos * 26 * sizeof(Jugador);
        }

        else if(opcion == 2) {
            if(listaEquipos == nullptr) {
                cout << "Primero debes cargar los datos (opcion 1)\n";
            } else {
                cout << "Generando grupos...\n";

                short   bombos[4][12];
                short   salto = 0;
                short   indexFila = 0;

                totalMemoria += 48 * 2 + 2 + 2;

                for (short i = 0; i < numeroEquipos - 1; i++) {
                    iteraciones++;

                    for (short j = 0; j < numeroEquipos - i - 1; j++) {
                        iteraciones++;

                        if (listaEquipos[j].getRankinFifa() > listaEquipos[j + 1].getRankinFifa()) {

                            Equipo temp = listaEquipos[j];
                            listaEquipos[j] = listaEquipos[j + 1];
                            listaEquipos[j + 1] = temp;
                            totalMemoria += sizeof(temp);
                        }
                    }
                }

                for (short i = 0; i < numeroEquipos; i++){
                    iteraciones++;

                    bombos[indexFila][salto] = listaEquipos[i].getRankinFifa();

                    if (salto == 11){
                        salto = 0;
                        indexFila++;
                        continue;
                    }
                    salto++;
                }



                cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                cout << "|                                                   CONFORMACION DE GRUPOS                                             |" << endl;
                cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
                cout << "| " << left  << setw(7) << "Grupo"
                     << " | " << left << setw(23) << "Equipo 1"
                     << " | " << left << setw(23) << "Equipo 2"
                     << " | " << left << setw(23) << "Equipo 3"
                     << " | " << left << setw(23) << "Equipo 4                     |" << endl;
                cout << "------------------------------------------------------------------------------------------------------------------------" << endl;


                for (short  i = 0; i < numeroGrupos; i++){
                    iteraciones++;

                    listaGrupos[i].setId(letras[i]);
                    listaGrupos[i].selecEquipos(bombos, listaEquipos, numeroEquipos, iteraciones, totalMemoria);

                    cout <<  "| "  << left << setw(7) <<  listaGrupos[i].getId();

                    for (short c = 0; c < 4; c++){
                        iteraciones++;

                        string nombreEquipo = "";
                        string nombreConfere = "";

                        for (short f = 0; f < numeroEquipos; f++){
                            iteraciones++;

                            if (listaEquipos[f].getRankinFifa() == listaGrupos[i].getEquiposRF()[c]){
                                nombreEquipo = listaEquipos[f].getPais();
                                nombreConfere = listaEquipos[f].getConfederacion();
                                break;
                            }
                        }

                        const string texto = nombreEquipo + " (" + nombreConfere + ")";

                        cout << " |" << left << setw(24) << texto;
                    }
                    cout <<  endl;
                }

                cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

                totalMemoria += 24 + 24 + 24;
                totalMemoria = totalMemoria / 1024;

                cout << "Numero de iteraciones: " << iteraciones << endl;
                cout << "Total memoria usada: " << totalMemoria  << " KB" << endl;
            }
        }


        else if(opcion == 3) {
            if(listaGrupos == nullptr) {
                cout << "[!] Error: Primero debes generar los grupos (opcion 2)\n";
            } else {
                cout << "Simulando fase de grupos...\n";


                short  partidosPorGrupo = 6;
                short  indexPartidos = 0;

                Partido* listaPartidos = new Partido[12*partidosPorGrupo];

                for (short  c = 0; c < numeroGrupos; c++){
                    iteraciones++;
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

                totalMemoria += sizeof(short)*5 + sizeof(listaPartidos) * 12 * partidosPorGrupo + 8;

                Partido **matrixPartidos = new Partido*[12];

                for (short i = 0; i < 12; i++) {
                    iteraciones++;
                    matrixPartidos[i] = new Partido[6];
                }

                for (short i = 0; i < 72; i++) {
                    iteraciones++;
                    short fila = i / 6;
                    short col  = i % 6;

                    matrixPartidos[fila][col] = listaPartidos[i];
                }

                delete[] listaPartidos;

                totalMemoria += sizeof(matrixPartidos) * 72 -  sizeof(listaPartidos) * 12 * partidosPorGrupo;


                short dias = 1;
                for (short col = 0; col < 6; col++){
                    iteraciones++;
                    for (short row = 0; row < 12; row++){
                        iteraciones++;
                        matrixPartidos[row][col].setDia(dias);
                        matrixPartidos[row][col].generarFecha(dias, totalMemoria);

                        if (row == 3 || row == 7 || row == 11) dias++;


                        matrixPartidos[row][col].simularOcurrencia(listaEquipos, numeroEquipos, "EL", iteraciones, totalMemoria);
                    }
                }

                totalMemoria += sizeof(short) + sizeof(float) * 4;

                for (short i = 0; i < numeroGrupos; i++) {
                    iteraciones++;
                    listaGrupos[i].ordenarPorPuntos(listaEquipos, numeroEquipos, iteraciones, totalMemoria);
                }



                cout << endl;
                cout << "---------------------------------------------------------------------------------------" << endl;
                cout << "|                                 PARTIDOS ELIMINATORIAS                              |" << endl;
                cout << "---------------------------------------------------------------------------------------" << endl;
                cout << "| " << left  << setw(10) << "Fecha"
                     << " | " << left << setw(19) << "Equipo 1"
                     << " | " << left << setw(0) << "Goleador 1"
                     << " | " << left << setw(22) << "Equipo 2"
                     << " | " << left << setw(0) << "Goleador 2 |" << endl;
                cout << "---------------------------------------------------------------------------------------" << endl;


                for (short i = 0; i < 12; i++){
                    iteraciones++;
                    for (short c = 0; c < 6; c++){
                        iteraciones++;
                        string pais1 = "";
                        string pais2 = "";
                        short numeroCamisa1 = 0;
                        short numeroCamisa2 = 0;

                        for (short f = 0; f < numeroEquipos; f++){
                            iteraciones++;
                            if (listaEquipos[f].getRankinFifa() == matrixPartidos[i][c].getRankingFifaequip1()) {
                                pais1 = listaEquipos[f].getPais();
                                numeroCamisa1 = listaEquipos[f].obtenerGoleador(iteraciones, totalMemoria);
                            }
                            if (listaEquipos[f].getRankinFifa() == matrixPartidos[i][c].getRankingFifaequip2()) {
                                pais2 = listaEquipos[f].getPais();
                                numeroCamisa2 = listaEquipos[f].obtenerGoleador(iteraciones, totalMemoria);
                            }
                        }

                        cout << "|" <<  left << setw(11) <<  matrixPartidos[i][c].getFecha()
                             << " |" << left << setw(20) << pais1
                             << " |" << left << setw(11) << numeroCamisa1
                             << " |"  << left << setw(23) << pais2
                             << " |"  << left << setw(5) << numeroCamisa2 << "       |" << endl;


                    }
                }
                cout << "---------------------------------------------------------------------------------------" << endl;

                totalMemoria += sizeof(short)*2 + sizeof(string)*2;
                cout << "Numero de iteraciones: " << iteraciones << endl;
                cout << "Total memoria usada: " << totalMemoria  << " KB" << endl;}
            }







         if(opcion == 4) {
                if(listaGrupos == nullptr) {
                    cout << "[!] Error: No hay datos de grupos para mostrar. Ejecuta la opcion 3.\n";
                } else {


                cout << "Mostrando tabla...\n";
                cout << endl;
                cout << "---------------------------------------------------------------------" << endl;
                cout << "|                    RESULTADOS ELIMINATORIAS                       |" << endl;
                cout << "---------------------------------------------------------------------";

                for (short c = 0; c < numeroGrupos; c++) {
                    iteraciones++;
                    const string grupo = "Grupo " + string(1, listaGrupos[c].getId());

                    cout << endl;
                    cout << "| " << left << setw(23) << grupo
                         << " | " << right << setw(4) << "PJ"
                         << " | " << right << setw(4) << "PG"
                         << " | " << right << setw(4) << "PE"
                         << " | " << right << setw(4) << "PP"
                         << " | " << right << setw(4) << "DG"
                         << " | " << right << setw(4) << "PTS" << " |" << endl;
                    cout << "---------------------------------------------------------------------" << endl;

                    for (short k = 0; k < 4; k++) {
                        iteraciones++;
                        const short rankingfifa = listaGrupos[c].getEquiposRF()[k];

                        for (short i = 0; i < numeroEquipos; i++) {
                            iteraciones++;
                            if (listaEquipos[i].getRankinFifa() == rankingfifa) {
                                const short DG = listaEquipos[i].getGolesAFavor() - listaEquipos[i].getGolesEnContra();
                                const short PT = listaEquipos[i].getPartidosGanados() * 3 + listaEquipos[i].getPartidosEmpatados();

                                listaEquipos[i].setPuntos(PT);
                                cout << "| " << left << setw(23) << listaEquipos[i].getPais()
                                     << " |" << right << setw(5) << listaEquipos[i].getPartidosJugados()
                                     << " |" << right << setw(5) << listaEquipos[i].getPartidosGanados()
                                     << " |" << right << setw(5) << listaEquipos[i].getPartidosEmpatados()
                                     << " |" << right << setw(5) << listaEquipos[i].getPartidosPerdidos()
                                     << " |" << right << setw(5) << DG
                                     << " |" << right << setw(5) << PT
                                     << " |" << endl;
                            }
                        }
                    }
                    cout << "---------------------------------------------------------------------";
                }
                cout << endl;


                cout << "Numero de iteraciones: " << iteraciones << endl;
                cout << "Total memoria usada: " << totalMemoria << " KB" << endl;
                cout << endl;


                if (matrixPartidos != nullptr) {
                    for (short c = 0; c < 12; c++) {
                        iteraciones++;
                        delete[] matrixPartidos[c];
                    }
                    delete[] matrixPartidos;
                    matrixPartidos = nullptr;
                }


                clasificados32 = new Equipo*[32];
                short contC = 0;


                for (short i = 0; i < 12; i++) {
                    iteraciones++;
                    short rf1 = listaGrupos[i].getEquiposRF()[0];
                    short rf2 = listaGrupos[i].getEquiposRF()[1];
                    for (short e = 0; e < numeroEquipos; e++) {
                        iteraciones++;
                        if (contC < 32) {
                            if (listaEquipos[e].getRankinFifa() == rf1) clasificados32[contC++] = &listaEquipos[e];
                            if (contC < 32 && listaEquipos[e].getRankinFifa() == rf2) clasificados32[contC++] = &listaEquipos[e];
                        }
                    }
                }


                terceros = new Equipo*[12];
                for (short i = 0; i < 12; i++) {
                    iteraciones++;
                    short rf3 = listaGrupos[i].getEquiposRF()[2];
                    for (short e = 0; e < numeroEquipos; e++) {
                        iteraciones++;
                        if (listaEquipos[e].getRankinFifa() == rf3) terceros[i] = &listaEquipos[e];
                    }
                }


                for (short i = 0; i < 11; i++) {
                    iteraciones++;
                    for (short j = 0; j < 11 - i; j++) {
                        iteraciones++;
                        if (terceros[j]->getPuntos() < terceros[j+1]->getPuntos()) {
                            Equipo* temp = terceros[j];
                            terceros[j] = terceros[j+1];
                            terceros[j+1] = temp;
                        }
                    }
                }


                cabezas = new Equipo*[12];
                segundos = new Equipo*[12];

                for (short i = 0; i < 12; i++) {
                    iteraciones++;
                    cabezas[i] = clasificados32[i * 2];
                    segundos[i] = clasificados32[i * 2 + 1];
                }


                for (short i = 0; i < 11; i++) {
                    iteraciones++;
                    for (short j = 0; j < 11 - i; j++) {
                        iteraciones++;
                        if (segundos[j] != nullptr && segundos[j+1] != nullptr) {
                            if (segundos[j]->getPuntos() < segundos[j+1]->getPuntos()) {
                                Equipo* temp = segundos[j];
                                segundos[j] = segundos[j+1];
                                segundos[j+1] = temp;
                            }
                        }
                    }
                }


                totalMemoria += (sizeof(Equipo*) * 32) + (sizeof(Equipo*) * 12 * 3);
            }

         }


        else if(opcion == 5) {
             if(cabezas == nullptr || segundos == nullptr || terceros == nullptr) {
                 cout << "[!] Error: Primero debes organizar los clasificados (opcion 4).\n";
             } else {



                cout << "Ejecutando eliminatorias...\n";
                cout << "---------------------------------------------------------------------" << endl;
                cout << "|            CRUCES DE DIECISEISAVOS DE FINAL                       |" << endl;
                cout << "---------------------------------------------------------------------" << endl;
                cout << "|" <<  left << setw(4) <<" #P  "
                     << "|" << left << setw(20) << " Pais 1"
                     << "|" << left << setw(4) << "vs"
                     << "|" << left << setw(23) << " Pais 2"
                     << "|" << left << setw(10) << "Resumen"
                     << right << setw(1) << " |" << endl;

                cout << "---------------------------------------------------------------------" << endl;

                short numP = 1;

                for (short i = 0; i < 8; i++) {
                    cout << "|" << left << setw(5) << numP++
                         << "|" << left << setw(20) << cabezas[i]->getPais()
                         << "|" << left << setw(4) << " vs"
                         << "|" << left << setw(23) << terceros[i]->getPais()
                         << "|" << left << setw(2) << " (C vs T)"
                         << right << setw(3) << "|" << endl;
                }
                for (short i = 8; i < 12; i++) {
                    cout << "|" << left << setw(5) << numP++
                         << "|" << left << setw(20) << cabezas[i]->getPais()
                         << "|" << left << setw(4) << " vs"
                         << "|" << left << setw(23) << segundos[i]->getPais()
                         << "|" << left << setw(2) << " (C vs S)"
                         << right << setw(3) << "|" << endl;
                }
                for (short i = 0; i < 4; i++) {
                    cout << "|" << left << setw(5) << numP++
                         << "|" << left << setw(20) << segundos[i]->getPais()
                         << "|" << left << setw(4) << " vs"
                         << "|" << left << setw(23) << segundos[7-i]->getPais()
                         << "|" << left << setw(2) << " (S vs S)"
                         << right << setw(3) << "|" << endl;
                }

                cout << "---------------------------------------------------------------------" << endl;


                lista32 = new Equipo*[32];
                short idx = 0;

                for (short i = 0; i < 8; i++) {
                    iteraciones++;
                    lista32[idx++] = cabezas[i];
                    lista32[idx++] = terceros[i];
                }
                for (short i = 8; i < 12; i++) {
                    iteraciones++;
                    lista32[idx++] = cabezas[i];
                    lista32[idx++] = segundos[i];
                }
                for (short i = 0; i < 4; i++) {
                    iteraciones++;
                    lista32[idx++] = segundos[i];
                    lista32[idx++] = segundos[7-i];
                }

                totalMemoria += sizeof(numP) + sizeof(lista32)*32 + sizeof(idx);

                ganadores16 = Partido::simularEtapaMataMata(lista32, 16, "Dieciseisavos", listaEquipos, numeroEquipos, iteraciones, totalMemoria);
                ganadores8  = Partido::simularEtapaMataMata(ganadores16, 8, "Octavos de Final", listaEquipos, numeroEquipos, iteraciones, totalMemoria);
                ganadores4  = Partido::simularEtapaMataMata(ganadores8, 4, "Cuartos de Final", listaEquipos, numeroEquipos, iteraciones, totalMemoria);
                finalistas  = Partido::simularEtapaMataMata(ganadores4, 2, "Semifinales", listaEquipos, numeroEquipos, iteraciones, totalMemoria);

                totalMemoria += sizeof(ganadores16)*16 + sizeof(ganadores8) *8 + sizeof(ganadores4)*4 + sizeof(finalistas)*2;

                perdedoresSemis = new Equipo*[2];
                perdedoresSemis[0] = (finalistas[0] == ganadores4[0]) ? ganadores4[1] : ganadores4[0];
                perdedoresSemis[1] = (finalistas[1] == ganadores4[2]) ? ganadores4[3] : ganadores4[2];

                tercerLugarArreglo = Partido::simularEtapaMataMata(perdedoresSemis, 1, "Tercer Puesto", listaEquipos, numeroEquipos, iteraciones, totalMemoria);
                podio = Partido::simularEtapaMataMata(finalistas, 1, "GRAN FINAL", listaEquipos, numeroEquipos, iteraciones, totalMemoria);

                totalMemoria += sizeof(perdedoresSemis) * 2 + sizeof(tercerLugarArreglo) + sizeof(podio);

                cout << endl;
                cout << "**********************************************************" << endl;
                cout << "   EL NUEVO CAMPEON MUNDIAL ES: " << podio[0]->getPais() << "!" << endl;
                cout << "**********************************************************" << endl;

                podio[0]->setFase("CAMPEON");

                cout << "Numero de iteraciones: " << iteraciones << endl;
                cout << "Total memoria usada: " << totalMemoria  << " KB" << endl;
                cout << endl;
            }
         }




        else if(opcion == 6) {

            if(podio == nullptr) {
                cout << "[!] Error: No hay datos. Primero simula las eliminatorias (opcion 5).\n";
            } else {
                cout << "Mostrando estadisticas...\n";
                cout << "\n--- ESTADISTICAS FINALES DEL TORNEO ---" << endl;

                cout << "1. Ranking de Honor:" << endl;
                cout << "   1ro: " << podio[0]->getPais() << endl;
                cout << "   2do: " << (podio[0] == finalistas[0] ? finalistas[1]->getPais() : finalistas[0]->getPais()) << endl;
                cout << "   3ro: " << tercerLugarArreglo[0]->getPais() << endl;
                cout << "   4to: " << (tercerLugarArreglo[0] == perdedoresSemis[0] ? perdedoresSemis[1]->getPais() : perdedoresSemis[0]->getPais()) << endl;

                cout << "\n2. Goleador del Campeon: Dorsal " << podio[0]->obtenerGoleador(iteraciones, totalMemoria) << " de " << podio[0]->getPais() << endl;

                cout << "3. Top 3 Goleadores del Torneo:" << endl;
                Equipo* subcampeon = (podio[0] == finalistas[0] ? finalistas[1] : finalistas[0]);
                cout << "   1ro: Dorsal " << podio[0]->obtenerGoleador(iteraciones, totalMemoria) << " (" << podio[0]->getPais() << ")" << endl;
                cout << "   2do: Dorsal " << subcampeon->obtenerGoleador(iteraciones, totalMemoria) << " (" << subcampeon->getPais() << ")" << endl;
                cout << "   3ro: Dorsal " << tercerLugarArreglo[0]->obtenerGoleador(iteraciones, totalMemoria) << " (" << tercerLugarArreglo[0]->getPais() << ")" << endl;

                Equipo* masGoles = &listaEquipos[0];
                for(int i = 1; i < numeroEquipos; i++) {
                    iteraciones++;
                    if(listaEquipos[i].getGolesAFavor() > masGoles->getGolesAFavor()) {
                        masGoles = &listaEquipos[i];
                    }
                }
                cout << "\n4. Equipo con mas goles totales: " << masGoles->getPais() << " (" << masGoles->getGolesAFavor() << " goles)" << endl;

                cout << "\n5. Confederacion con mayor presencia por etapa:" << endl;
                string nombresC[] = {"UEFA", "CONMEBOL", "CONCACAF", "AFC", "CAF", "OFC"};

                int c32[6] = {0};
                for(int i=0; i<32; i++) {
                    iteraciones++;
                    for(int k=0; k<6; k++) {
                        iteraciones++;
                        if(lista32[i]->getConfederacion() == nombresC[k]) c32[k]++;
                    }
                }
                int m32=0; for(int i=1; i<6; i++) if(c32[i] > c32[m32]) m32=i;
                cout << "   En Dieciseisavos (R32): " << nombresC[m32] << endl;

                int c16[6] = {0};
                for(int i=0; i<16; i++){
                    iteraciones++;
                    for(int k=0; k<6; k++) {
                        iteraciones++;
                        if(ganadores16[i]->getConfederacion() == nombresC[k]) c16[k]++;
                    }
                }
                int m16=0; for(int i=1; i<6; i++) if(c16[i] > c16[m16]) m16=i;
                cout << "   En Octavos (R16):        " << nombresC[m16] << endl;

                int c8[6] = {0};
                for(int i=0; i<8; i++) for(int k=0; k<6; k++) {
                        iteraciones++;
                        if(ganadores8[i]->getConfederacion() == nombresC[k]) c8[k]++;
                    }
                int m8=0; for(int i=1; i<6; i++) if(c8[i] > c8[m8]) m8=i;
                cout << "   En Cuartos (R8):         " << nombresC[m8] << endl;

                int c4[6] = {0};
                for(int i=0; i<4; i++) for(int k=0; k<6; k++) {
                        iteraciones++;
                        if(ganadores4[i]->getConfederacion() == nombresC[k]) c4[k]++;
                    }
                int m4=0; for(int i=1; i<6; i++) if(c4[i] > c4[m4]) m4=i;
                cout << "   En Semifinales (R4):     " << nombresC[m4] << endl;

                totalMemoria += sizeof(subcampeon) + sizeof(masGoles) + sizeof(nombresC) *6
                                + sizeof(c32) * 6 + sizeof(c16)*6 + sizeof(c8)*6 + sizeof(c4)*6
                                + sizeof(m32) + sizeof(m16) + sizeof(m8) + sizeof(m4);

                gestorArchivo->guardarEquipos(listaEquipos, "resultado_mundial_final.csv", iteraciones);
                gestorArchivo->guardarEquipos(listaEquipos, "juadores_mundial.csv", iteraciones, true);

                cout << endl;
                cout << "Numero de iteraciones: " << iteraciones << endl;
                cout << "Total memoria usada: " << totalMemoria  << " KB" << endl;
                cout << endl;
            }
        }





        else if(opcion == 0) {
            cout << "Saliendo...\n";
        }
        else {
            cout << "Opcion invalida\n";
        }

    } while(opcion != 0);


    delete[] perdedoresSemis;
    delete[] tercerLugarArreglo;
    delete[] ganadores16;
    delete[] ganadores8;
    delete[] ganadores4;
    delete[] finalistas;
    delete[] podio;
    delete[] lista32;

    delete[] terceros;
    delete[] clasificados32;

    delete gestorArchivo;
    delete[] listaEquipos;
    delete[] listaGrupos;

    cout << "\n--- PROGRAMA FINALIZADO CON EXITO ---" << endl;
    return 0;
}
