#pragma once
#include <iostream>
#include "conecta4.h"
using namespace std;

class menu{
    public:
        Connect4 juego;
        char jugador = 'O'; 
        int puntajeJugador = 0;
        int puntajeIA = 0;
        int nivelDificultad = juego.preguntarDificultad();
        char opcion;
        void imprimirMenu(){
            do {
                juego.mostrarPuntuacion(puntajeJugador, puntajeIA);

                cout << "\nMenu:\n";
                cout << "1. Jugar\n";
                cout << "2. Cargar Partida\n";
                cout << "3. Guardar Partida\n";
                cout << "4. Salir\n";
                cout << "Seleccione una opcion: ";
                cin >> opcion;

                switch (opcion) {
                    case '1':
                        juego.imprimirTablero();
                        juego.jugarUsuario();
                    
                        if (juego.evaluarTablero( 'O')) {
                            cout << "¡Ganaste!" << endl;
                            juego.vaciarTablero();
                            break;
                        } else if (juego.hayEmpate()) {
                            juego.vaciarTablero();
                            cout << "¡Empate!" << endl;
                            break;
                        }

                        if (nivelDificultad == 1) {
                            // Dificultad Facil: IA toma las peores decisiones
                            juego.jugarIA(nivelDificultad);
                        } else {
                            // Dificultad Difícil: IA toma las mejores decisiones
                            juego.jugarIA(nivelDificultad);
                        }

                        if (juego.evaluarTablero('X')) {
                            cout << "¡La IA (X) gano!" << endl;
                            juego.vaciarTablero();
                            break;
                        }
                        break;
                    case '2':
                        juego.cargarPartida(jugador, puntajeJugador, puntajeIA);
                        break;
                    case '3':
                        juego.guardarPartida(jugador, puntajeJugador, puntajeIA);
                        break;


                    case '4':
                        cout << "Saliendo del juego. ¡Hasta luego!" << endl;
                        break;
                    default:
                        cout << "Opción no valida. Intente de nuevo." << endl;
                }
            } while (opcion != '4');
        }
};