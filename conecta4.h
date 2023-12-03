#pragma once
#include <iostream>
#include <climits>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

class Connect4 {
private:
    const int FILAS = 6;
    const int COLUMNAS = 7;
    const int OBJETIVO = 4;
    char tablero[6][7] = { { ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                                      { ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                                      { ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                                      { ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                                      { ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                                      { ' ', ' ', ' ', ' ', ' ', ' ', ' ' } };
    

public:
    void guardarPartida(char jugador, int puntajeJugador, int puntajeIA) {
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

    void cargarPartida(char &jugador, int &puntajeJugador, int &puntajeIA) {
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
        cout << "Jugador (O): " << puntajeJugador << " ia (X): " << puntajeIA << endl;
    }

    void imprimirTablero() {
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                cout << tablero[i][j] << " "<< "|";
            }
            cout << "\n---------------------\n";
        }
    cout << "0  1  2  3  4  5  6" << endl;
    }

    bool hayEmpate() {
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                if (tablero[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

    bool movimientoValido(int columna) {
        return columna >= 0 && columna < COLUMNAS && tablero[0][columna] == ' ';
    }

    bool evaluarTablero(char jugador) {
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

    int puntajeConsecutivas(char jugador, int longitud) {
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

    int minimax(int profundidad, int alpha, int beta, bool maximizando, int nivelDificultad) {
        char jugador = maximizando ? 'X' : 'O';

        if (profundidad == 0 || hayEmpate())
            return 0;

        int mejorPuntaje = maximizando ? INT_MIN : INT_MAX;

        // Ordena las columnas para que la IA considere primero las del medio
        int ordenColumnas[COLUMNAS] = {3, 2, 4, 1, 5, 0, 6};

        for (int i = 0; i < COLUMNAS; ++i) {
            int columna = ordenColumnas[i];
            if (movimientoValido(columna)) {
                // Realizar el movimiento
                for (int fila = FILAS - 1; fila >= 0; --fila) {
                    if (tablero[fila][columna] == ' ') {
                        tablero[fila][columna] = jugador;
                        break;
                    }
                }

                int puntaje;

                if (nivelDificultad == 1) {
                    // Dificultad Facil: Elige las peores jugadas
                    puntaje = minimax(profundidad - 1, alpha, beta, !maximizando, nivelDificultad);
                } else {
                    // Dificultad Difícil: Elige las mejores jugadas
                    puntaje = evaluarTablero(jugador);
                    if (puntaje != 0)
                        puntaje = (puntaje > 0) ? profundidad : -profundidad;
                    else {
                        puntaje += puntajeConsecutivas(jugador, 3); // Verificar 3 fichas consecutivas
                        puntaje += minimax( profundidad - 1, alpha, beta, !maximizando, nivelDificultad);
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


    int obtenerMejorJugada(int nivelDificultad) {
        int mejorColumna = -1;
        int mejorPuntaje = INT_MIN;

        for (int columna = 0; columna < COLUMNAS; ++columna) {
            if (movimientoValido(columna)) {
                // Realizar el movimiento
                for (int fila = FILAS - 1; fila >= 0; --fila) {
                    if (tablero[fila][columna] == ' ') {
                        tablero[fila][columna] = 'X';
                        break;
                    }
                }

                int puntaje;

                // Verificar si la IA tiene una jugada ganadora en su próximo turno
                if (evaluarTablero('X')) {
                    puntaje = 10000;
                } else if (nivelDificultad == 1) {
                    // Dificultad Facil: Elige las peores jugadas
                    puntaje = minimax(5, INT_MIN, INT_MAX, false, nivelDificultad);
                } else {
                    // Dificultad Difícil: Elige las mejores jugadas
                    puntaje = minimax(5, INT_MIN, INT_MAX, false, nivelDificultad);
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


    void jugar(int columna, char jugador) {
        for (int fila = FILAS - 1; fila >= 0; --fila) {
            if (tablero[fila][columna] == ' ') {
                tablero[fila][columna] = jugador;
                break;
            }
        }
    }

    void jugarIA(int nivelDificultad) {
        int mejorColumna = obtenerMejorJugada(nivelDificultad);
        jugar(mejorColumna, 'X');
        cout << "Turno de la IA (X):" << endl;
        imprimirTablero();
    }

    void jugarUsuario() {
        int columna;
        cout << "Tu turno. Ingresa la columna: ";
        cin >> columna;

        while (columna < 0 || columna >= COLUMNAS || !movimientoValido(columna)) {
            cout << "Movimiento no valido. Ingresa una columna valida: ";
            cin.clear();  // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada incorrecta
            cin >> columna;
        }

        jugar(columna, 'O');
        cout << "Turno del jugador (O):" << endl;
        imprimirTablero();
    }

    int preguntarDificultad() {
        int dificultad;
        cout << "Selecciona la dificultad:\n";
        cout << "1. Facil\n";
        cout << "2. Dificil\n";
        cout << "Ingrese el numero correspondiente a la dificultad: ";
        cin >> dificultad;

        while (dificultad < 1 || dificultad > 2) {
            cout << "Opción no valida. Por favor, ingrese 1 para Facil o 2 para Dificil: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> dificultad;
        }

        return dificultad;
    }

    void vaciarTablero() {
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                tablero[i][j] = ' ';
            }
        }
    }
};