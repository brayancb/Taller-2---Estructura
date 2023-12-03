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
Se implemento las siguientes clases y funciones:

- La clase Connect4 se encarga de toda la lógica del juego, como la creación del tablero, el control de los turnos, la comprobación de victorias, y la implementación de la inteligencia artificial que juega contra el usuario. Dentro de esta clase se han definido varias funciones privadas que realizan tareas específicas, como evaluar el estado del tablero, calcular los puntajes consecutivos de cada color, aplicar el algoritmo minimax con poda alfa-beta para elegir la mejor jugada, y otras funciones auxiliares.
- La clase Menu se ocupa de la gestión del menú principal y las interacciones con el usuario. Esta clase permite al usuario elegir entre jugar una partida nueva o cargar una partida guardada, seleccionar el nivel de dificultad, y guardar o salir de la partida en cualquier momento. Dentro de esta clase se ha definido una función preguntarDificultad que valida la entrada del usuario al escoger la dificultad, asegurándose de que sea una opción válida.
- Se ha utilizado una enumeración (Difficulty) para representar los distintos niveles de dificultad del juego: fácil y difícil. Esto facilita la lectura y comprensión del código, y evita posibles errores al comparar los niveles de dificultad.
- Se ha aplicado el principio de encapsulamiento, definiendo las funciones y variables como privadas cuando sea posible, para ocultar los detalles de implementación y evitar el acceso directo desde fuera de la clase. De esta forma se garantiza la integridad de los datos y se facilita el mantenimiento del código.
- Se ha organizado el código en varios archivos (conecta4.cpp, menu.cpp y main.cpp) para mejorar la modularidad y la estructura del proyecto. Cada archivo contiene una clase con una única responsabilidad, siguiendo el principio de responsabilidad única.
- Se han implementado funciones para guardar y cargar partidas en un archivo CSV, usando el formato "fila,columna,color" para cada ficha colocada en el tablero. Esto permite a los usuarios guardar su progreso y continuar partidas anteriores.

Resultados de Pruebas (Comparación de Minimax sin poda y con poda):
- La eficacia del algoritmo minimax con poda alfa-beta se manifiesta en la mejora del rendimiento de la IA en comparación con una implementación de minimax sin poda. La poda alfa-beta reduce la cantidad de nodos evaluados, acelerando el proceso de toma de decisiones de la IA.
Sin poda su complejidad algoritmica es O(n^k)
con poda su complejidad algoritmica en el mejor caso: O(n x k)
con poda su complejidad algoritmica en el peor caso : O(n^k/2)
