#include <iostream>
#include "Clases/gestorarchivo.h"
#include "Clases/jugador.h"
#include "Clases/grupo.h"
#include "Clases//partido.h"
#include <iomanip>

using namespace std;

int main()
{

    cout << " ====================================================================================" << endl;
    cout << "                                  UdeAWorldCup                                 "  << endl;
    cout << " ====================================================================================" << endl;

    cout << endl;

    cout << "Simulando Eliminatorias de grupos..." << endl;

    short numeroGrupos = 12;
    const string letras      = "ABCDEFGHIJKL";

    // ----------------------------I--------------------------------- //
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

      // --------------------------- II -----------------------//
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
        listaGrupos[i].setId(letras[i]);
        listaGrupos[i].selecEquipos(bombos, listaEquipos, numeroEquipos);


        cout <<  "| "  << left << setw(7) <<  listaGrupos[i].getId();

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

            const string texto = nombreEquipo + " (" + nombreConfere + ")";

            cout << " |" << left << setw(24) << texto;
        }
        cout <<  endl;
    }

     cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

    // ------------------------------- III --------------------------//
    //  --------------------------a) -------------------------------//
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
            matrixPartidos[row][col].simularOcurrencia(listaEquipos, numeroEquipos, "EL");
        }
    }

    for (short i = 0; i < numeroGrupos; i++) {
        listaGrupos[i].ordenarPorPuntos(listaEquipos, numeroEquipos);}

    //impresion de los partidos de la eliminatoria de grupos

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
        for (short c = 0; c < 6; c++){
            string pais1 = "";
            string pais2 = "";
            short numeroCamisa1 = 0;
            short numeroCamisa2 = 0;

            for (short f = 0; f < numeroEquipos; f++){
                if (listaEquipos[f].getRankinFifa() == matrixPartidos[i][c].getRankingFifaequip1()) {
                    pais1 = listaEquipos[f].getPais();
                    numeroCamisa1 = listaEquipos[f].obtenerGoleador();
                }
                if (listaEquipos[f].getRankinFifa() == matrixPartidos[i][c].getRankingFifaequip2()) {
                    pais2 = listaEquipos[f].getPais();
                    numeroCamisa2 = listaEquipos[f].obtenerGoleador();
                }
            }

            cout << "|" <<  left << setw(11) <<  matrixPartidos[i][c].getFecha()
                 << " |" << left << setw(20) << pais1
                 << " |" << left << setw(11) << numeroCamisa1
                 << " |"  << left << setw(23) << pais2
                 << " |"  << left << setw(5) << numeroCamisa2 << "       |" << endl;

            //cout <<  matrixPartidos[i][c].getFecha() << " => " << pais1 << " ("<< numeroCamisa1 <<") "  <<  "vs"  << "  " << pais2 << " (" << numeroCamisa2 << ")" << endl;
        }
    }

    cout << "---------------------------------------------------------------------------------------" << endl;


    //------------------ b) ------------------//
    //      avance a dieciseisavos          //
    cout << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "|                    RESULTADOS ELIMINATORIAS                       |" << endl;
    cout << "---------------------------------------------------------------------";

    for (short c = 0; c < numeroGrupos; c++) {
        const string grupo = "Grupo " + string(1,listaGrupos[c].getId());
       // cout << "---------------------------------------------------------------------" << endl;

        cout << endl;
        cout << "| " << left  << setw(23) << grupo
             << " | " << right << setw(4) << "PJ"
             << " | " << right << setw(4) << "PG"
             << " | " << right << setw(4) << "PE"
             << " | " << right << setw(4) << "PP"
             << " | " << right << setw(4) << "DG"
             << " | " << right << setw(4) << "PTS" << " |" << endl;
        cout << "---------------------------------------------------------------------" << endl;

        for (short k = 0; k < 4; k++) {
            const short rankingfifa = listaGrupos[c].getEquiposRF()[k];

            for (short i = 0; i < numeroEquipos; i++) {
                if (listaEquipos[i].getRankinFifa() == rankingfifa) {
                    const short DG = listaEquipos[i].getGolesAFavor() - listaEquipos[i].getGolesEnContra();
                    const short PT = listaEquipos[i].getPartidosGanados() * 3 + listaEquipos[i].getPartidosEmpatados();

                    listaEquipos[i].setPuntos(PT);
                    cout << "| " << left << setw(23) << listaEquipos[i].getPais()
                         << " |"  << right << setw(5) << listaEquipos[i].getPartidosJugados()
                         << " |"   << right << setw(5) << listaEquipos[i].getPartidosGanados()
                         << " |"   << right << setw(5) << listaEquipos[i].getPartidosEmpatados()
                         << " |"   << right << setw(5) << listaEquipos[i].getPartidosPerdidos()
                         << " |"   << right << setw(5) << DG
                         << " |"   << right << setw(5) << PT
                         << " |" << endl;
                }
            }
        }

        cout << "---------------------------------------------------------------------";
        
    }
    

    cout << endl;

   

    for (short c = 0; c < 12; c++) delete[] matrixPartidos[c];
    delete[] matrixPartidos;

    Equipo** clasificados32 = new Equipo*[32];
    short contC = 0;

    for (short i = 0; i < 12; i++) {
        short rf1 = listaGrupos[i].getEquiposRF()[0];
        short rf2 = listaGrupos[i].getEquiposRF()[1];
        for (short e = 0; e < numeroEquipos; e++) {
            if (contC < 32) {

                if (listaEquipos[e].getRankinFifa() == rf1) clasificados32[contC++] = &listaEquipos[e];
                if (contC < 32 && listaEquipos[e].getRankinFifa() == rf2) clasificados32[contC++] = &listaEquipos[e];
            }
        }
    }


    Equipo** terceros = new Equipo*[12];
    for (short i = 0; i < 12; i++) {
        short rf3 = listaGrupos[i].getEquiposRF()[2];
        for (short e = 0; e < numeroEquipos; e++) {
            if (listaEquipos[e].getRankinFifa() == rf3) terceros[i] = &listaEquipos[e];
        }
    }

    for (short i = 0; i < 11; i++) {
        for (short j = 0; j < 11 - i; j++) {
            if (j + 1 < 12) {
                if (terceros[j]->getPuntos() < terceros[j+1]->getPuntos()) {
                    Equipo* temp = terceros[j]; // temp ahora es puntero
                    terceros[j] = terceros[j+1];
                    terceros[j+1] = temp;
                }
            }
        }
    }


    Equipo** cabezas = new Equipo*[12];
    Equipo** segundos = new Equipo*[12];

    for (short i = 0; i < 12; i++) {
        
        if ((i * 2 + 1) < 32) {
            cabezas[i] = clasificados32[i * 2];
            segundos[i] = clasificados32[i * 2 + 1];
        }
    }

   
    for (short i = 0; i < 11; i++) {
        for (short j = 0; j < 11 - i; j++) {
            if (segundos[j] != nullptr && segundos[j+1] != nullptr) { // ESCUDO
                if (segundos[j]->getPuntos() < segundos[j+1]->getPuntos()) {
                    Equipo* temp = segundos[j];
                    segundos[j] = segundos[j+1];
                    segundos[j+1] = temp;
                }
            }
        }
    }


    cout << "\n==========================================================" << endl;
    cout << "           CRUCES DE DIECISEISAVOS DE FINAL               " << endl;
    cout << "==========================================================" << endl;

    short numP = 1;


    for (short i = 0; i < 8; i++) {
        cout << "P" << setw(2) << numP++ << ": " << left << setw(20)
        << cabezas[i]->getPais() << " vs " << terceros[i]->getPais() << " (C vs T)" << endl;
    }
    for (short i = 8; i < 12; i++) {
        cout << "P" << setw(2) << numP++ << ": " << left << setw(20)
        << cabezas[i]->getPais() << " vs " << segundos[i]->getPais() << " (C vs S)" << endl;
    }
    for (short i = 0; i < 4; i++) {
        cout << "P" << setw(2) << numP++ << ": " << left << setw(20)
        << segundos[i]->getPais() << " vs " << segundos[7-i]->getPais() << " (S vs S)" << endl;
    }

    cout << "==========================================================" << endl;


    Equipo** lista32 = new Equipo*[32];
    short idx = 0;
    for (short i = 0; i < 8; i++) { lista32[idx++] = cabezas[i]; lista32[idx++] = terceros[i]; }
    for (short i = 8; i < 12; i++) { lista32[idx++] = cabezas[i]; lista32[idx++] = segundos[i]; }
    for (short i = 0; i < 4; i++) { lista32[idx++] = segundos[i]; lista32[idx++] = segundos[7-i]; }


    Equipo** ganadores16 = Partido::simularEtapaMataMata(lista32, 16, "Dieciseisavos", listaEquipos, numeroEquipos);
    Equipo** ganadores8  = Partido::simularEtapaMataMata(ganadores16, 8, "Octavos de Final", listaEquipos, numeroEquipos);
    Equipo** ganadores4  = Partido::simularEtapaMataMata(ganadores8, 4, "Cuartos de Final", listaEquipos, numeroEquipos);
    Equipo** finalistas  = Partido::simularEtapaMataMata(ganadores4, 2, "Semifinales", listaEquipos, numeroEquipos);


    Equipo** perdedoresSemis = new Equipo*[2];
    perdedoresSemis[0] = (finalistas[0] == ganadores4[0]) ? ganadores4[1] : ganadores4[0];
    perdedoresSemis[1] = (finalistas[1] == ganadores4[2]) ? ganadores4[3] : ganadores4[2];

    Equipo** tercerLugarArreglo = Partido::simularEtapaMataMata(perdedoresSemis, 1, "Tercer Puesto", listaEquipos, numeroEquipos);
    Equipo** podio = Partido::simularEtapaMataMata(finalistas, 1, "GRAN FINAL", listaEquipos, numeroEquipos);

    cout << "\n\n**********************************************************" << endl;
    cout << "   ¡EL NUEVO CAMPEON MUNDIAL ES: " << podio[0]->getPais() << "!" << endl;
    cout << "**********************************************************" << endl;

    podio[0]->setFase("CAMPEON");


    cout << "\n--- ESTADISTICAS FINALES DEL TORNEO ---" << endl;

    cout << "1. Ranking de Honor:" << endl;
    cout << "   1ro: " << podio[0]->getPais() << endl;
    cout << "   2do: " << (podio[0] == finalistas[0] ? finalistas[1]->getPais() : finalistas[0]->getPais()) << endl;
    cout << "   3ro: " << tercerLugarArreglo[0]->getPais() << endl;
    cout << "   4to: " << (tercerLugarArreglo[0] == perdedoresSemis[0] ? perdedoresSemis[1]->getPais() : perdedoresSemis[0]->getPais()) << endl;

    cout << "\n2. Goleador del Campeon: Dorsal " << podio[0]->obtenerGoleador() << " de " << podio[0]->getPais() << endl;

    cout << "3. Top 3 Goleadores del Torneo:" << endl;
    Equipo* subcampeon = (podio[0] == finalistas[0] ? finalistas[1] : finalistas[0]);
    cout << "   1ro: Dorsal " << podio[0]->obtenerGoleador() << " (" << podio[0]->getPais() << ")" << endl;
    cout << "   2do: Dorsal " << subcampeon->obtenerGoleador() << " (" << subcampeon->getPais() << ")" << endl;
    cout << "   3ro: Dorsal " << tercerLugarArreglo[0]->obtenerGoleador() << " (" << tercerLugarArreglo[0]->getPais() << ")" << endl;


    Equipo* masGoles = &listaEquipos[0];
    for(int i = 1; i < numeroEquipos; i++) {
        if(listaEquipos[i].getGolesAFavor() > masGoles->getGolesAFavor()) {
            masGoles = &listaEquipos[i];
        }
    }
    cout << "\n4. Equipo con mas goles totales: " << masGoles->getPais() << " (" << masGoles->getGolesAFavor() << " goles)" << endl;


    cout << "\n5. Confederacion con mayor presencia por etapa:" << endl;
    string nombresC[] = {"UEFA", "CONMEBOL", "CONCACAF", "AFC", "CAF", "OFC"};


    int c32[6] = {0};
    for(int i=0; i<32; i++) for(int k=0; k<6; k++) if(lista32[i]->getConfederacion() == nombresC[k]) c32[k]++;
    int m32=0; for(int i=1; i<6; i++) if(c32[i] > c32[m32]) m32=i;
    cout << "   En Dieciseisavos (R32): " << nombresC[m32] << endl;


    int c16[6] = {0};
    for(int i=0; i<16; i++) for(int k=0; k<6; k++) if(ganadores16[i]->getConfederacion() == nombresC[k]) c16[k]++;
    int m16=0; for(int i=1; i<6; i++) if(c16[i] > c16[m16]) m16=i;
    cout << "   En Octavos (R16):       " << nombresC[m16] << endl;


    int c8[6] = {0};
    for(int i=0; i<8; i++) for(int k=0; k<6; k++) if(ganadores8[i]->getConfederacion() == nombresC[k]) c8[k]++;
    int m8=0; for(int i=1; i<6; i++) if(c8[i] > c8[m8]) m8=i;
    cout << "   En Cuartos (R8):        " << nombresC[m8] << endl;


    int c4[6] = {0};
    for(int i=0; i<4; i++) for(int k=0; k<6; k++) if(ganadores4[i]->getConfederacion() == nombresC[k]) c4[k]++;
    int m4=0; for(int i=1; i<6; i++) if(c4[i] > c4[m4]) m4=i;
    cout << "   En Semifinales (R4):    " << nombresC[m4] << endl;




    gestorArchivo->guardarEquipos(listaEquipos, "resultado_mundial_final.csv");

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
