#include <iostream>
#include <climits>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

const int FILAS = 6;
const int COLUMNAS = 7;
const int OBJETIVO = 4;

int puntajeConsecutivas(char tablero[FILAS][COLUMNAS], char jugador, int longitud);

void guardarPartida(char tablero[FILAS][COLUMNAS], char jugador, int puntajeJugador, int puntajeIA) {
    ofstream archivo("partida_guardada.csv");

    if (archivo.is_open()) {
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                char contenido = (tablero[i][j] == ' ') ? '_' : tablero[i][j];
                archivo << contenido << ",";
            }
            archivo << endl;
        }
        archivo << jugador << "," << puntajeJugador << "," << puntajeIA;
        archivo.close();
        cout << "Partida guardada exitosamente." << endl;
    } else {
        cout << "Error al guardar la partida." << endl;
    }
}

void cargarPartida(char tablero[FILAS][COLUMNAS], char &jugador, int &puntajeJugador, int &puntajeIA) {
    ifstream archivo("partida_guardada.csv");

    if (archivo.is_open()) {
        for (int i = 0; i < FILAS; ++i) {
            string fila;
            getline(archivo, fila);

            // Iterar sobre los caracteres en la fila
            for (int j = 0; j < COLUMNAS * 2 - 1; j += 2) {
                if (fila[j] == '_') {
                    tablero[i][j / 2] = ' ';  // Tratar '_' como celda vacía
                } else {
                    tablero[i][j / 2] = fila[j];
                }
            }
        }

        // Leer la línea final que contiene jugador y puntuaciones
        string ultimaLinea;
        getline(archivo, ultimaLinea);

        // Extraer datos de la línea final
        stringstream ss(ultimaLinea);
        string valor;

        // Leer jugador
        getline(ss, valor, ',');
        jugador = valor[0];

        // Leer puntajes
        getline(ss, valor, ',');
        puntajeJugador = stoi(valor);
        getline(ss, valor, ',');
        puntajeIA = stoi(valor);

        cout << "Partida cargada exitosamente." << endl;
        archivo.close();
    } else {
        cout << "Error al cargar la partida." << endl;
    }
}

void mostrarPuntuacion(int puntajeJugador, int puntajeIA) {
    cout << "Puntuacion Actual:\n";
    cout << "Jugador (O): " << puntajeJugador << "\tMáquina (X): " << puntajeIA << endl;
}

void imprimirTablero(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            cout << tablero[i][j] << " "<< "|";
        }
        cout << "\n---------------------\n";
    }
   cout << "0  1  2  3  4  5  6" << endl;
}

bool hayEmpate(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            if (tablero[i][j] == ' ')
                return false;
        }
    }
    return true;
}

bool movimientoValido(char tablero[FILAS][COLUMNAS], int columna) {
    return columna >= 0 && columna < COLUMNAS && tablero[0][columna] == ' ';
}

bool evaluarTablero(char tablero[FILAS][COLUMNAS], char jugador) {
    // Verificar conexiones horizontales
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j <= COLUMNAS - OBJETIVO; ++j) {
            bool conectado = true;
            for (int k = 0; k < OBJETIVO; ++k) {
                if (tablero[i][j + k] != jugador) {
                    conectado = false;
                    break;
                }
            }
            if (conectado) return true;
        }
    }

    // Verificar conexiones verticales
    for (int i = 0; i <= FILAS - OBJETIVO; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            bool conectado = true;
            for (int k = 0; k < OBJETIVO; ++k) {
                if (tablero[i + k][j] != jugador) {
                    conectado = false;
                    break;
                }
            }
            if (conectado) return true;
        }
    }

    // Verificar conexiones diagonales ascendentes
    for (int i = OBJETIVO - 1; i < FILAS; ++i) {
        for (int j = 0; j <= COLUMNAS - OBJETIVO; ++j) {
            bool conectado = true;
            for (int k = 0; k < OBJETIVO; ++k) {
                if (tablero[i - k][j + k] != jugador) {
                    conectado = false;
                    break;
                }
            }
            if (conectado) return true;
        }
    }

    // Verificar conexiones diagonales descendentes
for (int i = 0; i <= FILAS - OBJETIVO; ++i) {
    for (int j = 0; j < COLUMNAS; ++j) {
        bool conectado = true;
        for (int k = 0; k < OBJETIVO; ++k) {
            if (tablero[i + k][j + k] != jugador) {
                conectado = false;
                break;
            }
        }
        if (conectado) return true;
    }
}

    return false; // No hay conexión de 4 fichas en línea
}

int puntajeConsecutivas(char tablero[FILAS][COLUMNAS], char jugador, int longitud) {
    int puntaje = 0;

// Verificar conexiones horizontales
for (int i = 0; i < FILAS; ++i) {
    for (int j = 0; j <= COLUMNAS - OBJETIVO; ++j) {
        bool conectado = true;
        bool bloqueado = false;
        for (int k = 0; k < OBJETIVO; ++k) {
            if (tablero[i][j + k] != jugador) {
                conectado = false;
                if (tablero[i][j + k] == 'X') {
                    bloqueado = true;
                }
                break;
            }
        }
        if (conectado && !bloqueado) return true;
    }
}

    // Verificar conexiones verticales
    for (int i = 0; i <= FILAS - longitud; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            int contadorIA = 0;
            int contadorJugador = 0;
            for (int k = 0; k < longitud; ++k) {
                if (tablero[i + k][j] == 'X') {
                    contadorIA++;
                } else if (tablero[i + k][j] == 'O') {
                    contadorJugador++;
                }
            }
            // Asignar puntajes basados en las fichas del jugador y la IA
            if (contadorIA == longitud - 1) {
                puntaje += 150;
            }
            if (contadorJugador == longitud - 1) {
                puntaje -= 100;
            }
        }
    }

    // Verificar conexiones diagonales ascendentes
    for (int i = longitud - 1; i < FILAS; ++i) {
        for (int j = 0; j <= COLUMNAS - longitud; ++j) {
            int contadorIA = 0;
            int contadorJugador = 0;
            for (int k = 0; k < longitud; ++k) {
                if (tablero[i - k][j + k] == 'X') {
                    contadorIA++;
                } else if (tablero[i - k][j + k] == 'O') {
                    contadorJugador++;
                }
            }
            // Asignar puntajes basados en las fichas del jugador y la IA
            if (contadorIA == longitud - 1) {
                puntaje += 100;
            }
            if (contadorJugador == longitud - 1) {
                puntaje -= 100;
            }
        }
    }

    // Verificar conexiones diagonales descendentes
    for (int i = 0; i <= FILAS - longitud; ++i) {
        for (int j = 0; j <= COLUMNAS - longitud; ++j) {
            int contadorIA = 0;
            int contadorJugador = 0;
            for (int k = 0; k < longitud; ++k) {
                if (tablero[i + k][j + k] == 'X') {
                    contadorIA++;
                } else if (tablero[i + k][j + k] == 'O') {
                    contadorJugador++;
                }
            }
            // Asignar puntajes basados en las fichas del jugador y la IA
            if (contadorIA == longitud - 1) {
                puntaje += 100;
            }
            if (contadorJugador == longitud - 1) {
                puntaje -= 100;
            }
        }
    }

    return puntaje;
}

int minimax(char tablero[FILAS][COLUMNAS], int profundidad, int alpha, int beta, bool maximizando, int nivelDificultad) {
    char jugador = maximizando ? 'X' : 'O';

    if (profundidad == 0 || hayEmpate(tablero))
        return 0;

    int mejorPuntaje = maximizando ? INT_MIN : INT_MAX;

    // Ordena las columnas para que la IA considere primero las del medio
    int ordenColumnas[COLUMNAS] = {3, 2, 4, 1, 5, 0, 6};

    for (int i = 0; i < COLUMNAS; ++i) {
        int columna = ordenColumnas[i];
        if (movimientoValido(tablero, columna)) {
            // Realizar el movimiento
            for (int fila = FILAS - 1; fila >= 0; --fila) {
                if (tablero[fila][columna] == ' ') {
                    tablero[fila][columna] = jugador;
                    break;
                }
            }

            int puntaje;

            if (nivelDificultad == 1) {
                // Dificultad Fácil: Elige las peores jugadas
                puntaje = minimax(tablero, profundidad - 1, alpha, beta, !maximizando, nivelDificultad);
            } else {
                // Dificultad Difícil: Elige las mejores jugadas
                puntaje = evaluarTablero(tablero, jugador);
                if (puntaje != 0)
                    puntaje = (puntaje > 0) ? profundidad : -profundidad;
                else {
                    puntaje += puntajeConsecutivas(tablero, jugador, 3); // Verificar 3 fichas consecutivas
                    puntaje += minimax(tablero, profundidad - 1, alpha, beta, !maximizando, nivelDificultad);
                }
            }

            // Deshacer el movimiento
            for (int fila = 0; fila < FILAS; ++fila) {
                if (tablero[fila][columna] != ' ') {
                    tablero[fila][columna] = ' ';
                    break;
                }
            }

            if (maximizando) {
                mejorPuntaje = max(mejorPuntaje, puntaje);
                alpha = max(alpha, puntaje);
            } else {
                mejorPuntaje = min(mejorPuntaje, puntaje);
                beta = min(beta, puntaje);
            }

            if (beta <= alpha)
                break;
        }
    }

    return mejorPuntaje;
}


int obtenerMejorJugada(char tablero[FILAS][COLUMNAS], int nivelDificultad) {
    int mejorColumna = -1;
    int mejorPuntaje = INT_MIN;

    for (int columna = 0; columna < COLUMNAS; ++columna) {
        if (movimientoValido(tablero, columna)) {
            // Realizar el movimiento
            for (int fila = FILAS - 1; fila >= 0; --fila) {
                if (tablero[fila][columna] == ' ') {
                    tablero[fila][columna] = 'X';
                    break;
                }
            }

            int puntaje;

            // Verificar si la IA tiene una jugada ganadora en su próximo turno
            if (evaluarTablero(tablero, 'X')) {
                puntaje = 10000;
            } else if (nivelDificultad == 1) {
                // Dificultad Fácil: Elige las peores jugadas
                puntaje = minimax(tablero, 5, INT_MIN, INT_MAX, false, nivelDificultad);
            } else {
                // Dificultad Difícil: Elige las mejores jugadas
                puntaje = minimax(tablero, 5, INT_MIN, INT_MAX, false, nivelDificultad);
            }

            // Deshacer el movimiento
            for (int fila = 0; fila < FILAS; ++fila) {
                if (tablero[fila][columna] != ' ') {
                    tablero[fila][columna] = ' ';
                    break;
                }
            }

            if (puntaje > mejorPuntaje) {
                mejorPuntaje = puntaje;
                mejorColumna = columna;
            }
        }
    }

    return mejorColumna;
}


void jugar(char tablero[FILAS][COLUMNAS], int columna, char jugador) {
    for (int fila = FILAS - 1; fila >= 0; --fila) {
        if (tablero[fila][columna] == ' ') {
            tablero[fila][columna] = jugador;
            break;
        }
    }
}

void jugarIA(char tablero[FILAS][COLUMNAS], int nivelDificultad) {
    int mejorColumna = obtenerMejorJugada(tablero, nivelDificultad);
    jugar(tablero, mejorColumna, 'X');
    cout << "Turno de la IA (X):" << endl;
    imprimirTablero(tablero);
}

void jugarUsuario(char tablero[FILAS][COLUMNAS]) {
    int columna;
    cout << "Tu turno. Ingresa la columna: ";
    cin >> columna;

    while (columna < 0 || columna >= COLUMNAS || !movimientoValido(tablero, columna)) {
        cout << "Movimiento no válido. Ingresa una columna válida: ";
        cin.clear();  // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada incorrecta
        cin >> columna;
    }

    jugar(tablero, columna, 'O');
    cout << "Turno del jugador (O):" << endl;
    imprimirTablero(tablero);
}

int preguntarDificultad() {
    int dificultad;
    cout << "Selecciona la dificultad:\n";
    cout << "1. Facil\n";
    cout << "2. Dificil\n";
    cout << "Ingrese el número correspondiente a la dificultad: ";
    cin >> dificultad;

    while (dificultad < 1 || dificultad > 2) {
        cout << "Opción no válida. Por favor, ingrese 1 para Fácil o 2 para Difícil: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> dificultad;
    }

    return dificultad;
}

void vaciarTablero(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            tablero[i][j] = ' ';
        }
    }
}

int main() {
    char tablero[FILAS][COLUMNAS] = { { ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                                      { ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                                      { ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                                      { ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                                      { ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                                      { ' ', ' ', ' ', ' ', ' ', ' ', ' ' } };

    char jugador = 'O'; 
    int puntajeJugador = 0;
    int puntajeIA = 0;
    int nivelDificultad = preguntarDificultad();
    char opcion;
    do {
        
        mostrarPuntuacion(puntajeJugador, puntajeIA);

        cout << "\nMenu:\n";
        cout << "1. Jugar\n";
        cout << "2. Cargar Partida\n";
        cout << "3. Guardar Partida\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case '1':
                imprimirTablero(tablero);
                jugarUsuario(tablero);
            
                if (evaluarTablero(tablero, 'O')) {
                    cout << "¡Ganaste!" << endl;
                    vaciarTablero(tablero);
                    break;
                } else if (hayEmpate(tablero)) {
                    vaciarTablero(tablero);
                    cout << "¡Empate!" << endl;
                    break;
                }

                if (nivelDificultad == 1) {
                    // Dificultad Fácil: IA toma las peores decisiones
                    jugarIA(tablero, nivelDificultad);
                } else {
                    // Dificultad Difícil: IA toma las mejores decisiones
                    jugarIA(tablero, nivelDificultad);
                }

                if (evaluarTablero(tablero, 'X')) {
                    cout << "¡La IA (X) gano!" << endl;
                    vaciarTablero(tablero);
                    break;
                }
                break;
            case '2':
                cargarPartida(tablero, jugador, puntajeJugador, puntajeIA);
                break;
            case '3':
                guardarPartida(tablero, jugador, puntajeJugador, puntajeIA);
                break;


            case '4':
                cout << "Saliendo del juego. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción no valida. Intente de nuevo." << endl;
        }
    } while (opcion != '4');

    return 0;
}