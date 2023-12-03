# Taller-2---Estructura
Brayan Cortes Borquez
Comando:  g++ main.cpp -o main , ./main

Implementación:
- Estructuras de Datos: Se utiliza una matriz bidimensional (tablero[FILAS][COLUMNAS]) para representar el tablero de juego. Se utiliza variables y funciones para manejar el estado del juego, como puntajeJugador, puntajeIA, jugador, y funciones como jugar, jugarIA, evaluarTablero, entre otras.
- Guardar y Cargar Partida: Se implementa funciones guardarPartida y cargarPartida que guardan y cargan el estado del tablero, el jugador actual y los puntajes en un archivo CSV.
- Jugada del Usuario y de la IA: jugarUsuario: Permite al usuario realizar una jugada ingresando la columna. jugarIA: Implementa la lógica de la IA utilizando el algoritmo minimax con poda alfa-beta.
- Dificultad de la IA: El usuario puede seleccionar entre dos niveles de dificultad: Fácil y Difícil. En el nivel Fácil, la IA elige las peores jugadas, mientras que en el nivel Difícil, elige las mejores jugadas.
- Menú Principal: Presenta un menú principal con opciones para Jugar, Cargar Partida, Guardar Partida y Salir.

Decisiones de Diseño:
- El código utiliza un enfoque modular al dividir el programa en funciones para realizar operaciones específicas, facilitando el mantenimiento y la comprensión del código.
- Se utiliza un archivo CSV para guardar y cargar partidas, donde cada celda del tablero y la información del juego se separan por comas.

Resultados de Pruebas (Comparación de Minimax sin poda y con poda):
- La eficacia del algoritmo minimax con poda alfa-beta se manifiesta en la mejora del rendimiento de la IA en comparación con una implementación de minimax sin poda. La poda alfa-beta reduce la cantidad de nodos evaluados, acelerando el proceso de toma de decisiones de la IA.
Sin poda su complejidad algoritmica es O(n^k)
con poda su complejidad algoritmica en el mejor caso: O(n x k)
con poda su complejidad algoritmica en el peor caso : O(n^k/2)
