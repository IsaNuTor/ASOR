#include<iostream>
#include<string>
#include<fstream>
#include <stdlib.h>     /* srand, rand */
#include <ctime> // Aleatorios
#include <cstdlib> // Convertir string a entero

using namespace std;

struct Pregunta {
	string enunciado = "";
	string respuestaA = "";
	string respuestaB = "";
	string respuestaC = "";
	char respuestaCorrecta;
} pregunta;

void menu() {
	// Menú, podemos elegir hacer todas las preguntas que tengamos, o hacer un examen de 10 preguntas, salir si pulsamos 0
	cout << "------------------------MENU---------------------------" << endl;
	cout << "	¡Vamos a aprobar ASOR!" << endl;											
	cout << "	1 - Estudiar todo (Todas las preguntas)" << endl;
	cout << "	2 - Examen test 10 preguntas aleatorias" << endl;
	cout << "	0 - salir" << endl;
	cout << "	Elige una opción: ";
}


int main(){
	setlocale(LC_ALL, ""); // Tildes
	int opcion, preguntasTotales = -1;
	int acertadas = 0, falladas = 0; // RESULTADOS, preguntas acertadas y falladas
	string lineaFichero;
	char respuesta;

	// Menú, podemos elegir hacer todas las preguntas que tengamos, o hacer un examen de 10 preguntas, salir si pulsamos 0
	menu();
	cin >> opcion;
	cout << endl;

	while (opcion != 0) {

		/*Leemos las preguntas del fichero y las guardamos en las estructuras correspondientes.
		En el fichero la primera linea corresponde al total de las preguntas, las preguntas empiezan por 1
		El formato de la pregunta es, pregunta en una linea, las 3 opciones en las líneas siguientes como a, b y c
		por último ponemos la letra de la respuesta correcta, si fuera la a seria a, así sucesivamente leemos
		preguntas hasta encontrar el fin de fichero
		PARA LAS TILDES DEL FICHERO TIENE QUE ESTAR GUARDADO EN FORMATO ANSI NO UTF8 */

		ifstream ficheroPreguntas;
		string linea;
		// Creamos un array con las preguntas
		struct Pregunta arrayPreguntas[200];
		int contadorArray = 0;

		struct Pregunta arrayPreguntasFalladas[200]; // Array donde guardaremos las falladas para luego mostrar los resultados.
		int contadorFalladas = 0;

// Abrimos el fichero

		//ficheroPreguntas.open("preguntasT1Redes.txt");
		//ficheroPreguntas.open("preguntasT2Redes.txt");
		//ficheroPreguntas.open("preguntasT3Filtrado.txt");
		//ficheroPreguntas.open("preguntasT3Dns.txt");
		//ficheroPreguntas.open("preguntasT4Redes.txt");
		ficheroPreguntas.open("preguntasT5Redes.txt");

		//ficheroPreguntas.open("zpreguntasT1SO.txt");
		//ficheroPreguntas.open("zpreguntasT2SO.txt");
		//ficheroPreguntas.open("zpreguntasT3SO.txt");


		/*getline(ficheroPreguntas, linea);
		preguntasTotales = atoi(linea.c_str()); // Lo convertimos a entero el primer número que nos indica el total de preguntas del fichero. // Contador del array*/

		// Mientras no lleguemos a fin de fichero, seguimos leyendo
		while (!ficheroPreguntas.eof()) {

			getline(ficheroPreguntas, pregunta.enunciado);
			getline(ficheroPreguntas, pregunta.respuestaA);
			getline(ficheroPreguntas, pregunta.respuestaB);
			getline(ficheroPreguntas, pregunta.respuestaC);
			getline(ficheroPreguntas, linea);
			/*ficheroPreguntas >> pregunta.enunciado;
			ficheroPreguntas >> pregunta.respuestaA;
			ficheroPreguntas >> pregunta.respuestaB;
			ficheroPreguntas >> pregunta.respuestaC;
			ficheroPreguntas >> linea;*/
			pregunta.respuestaCorrecta = linea[0];

			// Añadimos las preguntas al array de preguntas.
			arrayPreguntas[contadorArray] = pregunta;
			contadorArray++;
		}
		contadorArray = contadorArray - 1;
		preguntasTotales = contadorArray;

		ficheroPreguntas.close();

		cout << "	Total preguntas del fichero: " << preguntasTotales << endl << endl;
		
		if (opcion == 1) { // Estudiar todo
			
			for (int i = 0; i < preguntasTotales; i++) {

				// Nos miestra la pregunta aleatoria
				cout << arrayPreguntas[i].enunciado << endl;
				cout << "	" << arrayPreguntas[i].respuestaA << endl;
				cout << "	" << arrayPreguntas[i].respuestaB << endl;
				cout << "	" << arrayPreguntas[i].respuestaC << endl;
				cout << "	Elige la respuesta correcta (a,b,c): ";
				cin >> respuesta;
				cout << "------------------------------------------------------------------------------------" << endl;
				cout << endl;
				
				// Comparamos con la respuesta, si no es correcta además de añadirla al contador de falladas, la añadimos al array de falladas
				// que mostraremos al final del examen.
				if (respuesta == arrayPreguntas[i].respuestaCorrecta) { // RESPUESTA ACERTADA
					acertadas++;
				}
				else { // RESPUESTA FALLADA
					falladas++;
					arrayPreguntasFalladas[contadorFalladas] = arrayPreguntas[i];
					contadorFalladas++;
				}
			}

			// MOSTRAMOS RESULTADOS
			cout << "	Preguntas acertadas = " << acertadas << endl;
			cout << "	Preguntas falladas = " << falladas << endl;

			// Calculamos si hemos aprobado o no el examen, cada fallo resta el 50%, osea por cada respuesta bien se pueden tener dos mal y se queda en 0
			// Pregunta correcta 1 punto, pregunta incorrecta -0.5 puntos
			double totalPuntuacion = ((acertadas * 1) - (falladas * 0.5));

			if (totalPuntuacion >= double(preguntasTotales/2)) cout << "	Has aprobado!!!" << endl;
			else cout << "	Game Over, vuelve a intentarlo" << endl;
			
		}
		else { // TEST 10 preguntas aleatorias
/***NUMaleatorias****/
			int numPreguntasTest = 10;
			// Creamos un número aleatorio entre 0 y el total de las preguntas
			for (int i = 0; i < numPreguntasTest; i++) {
				srand(time(NULL));
				int aleatorio, DESDE = 0, HASTA = preguntasTotales - 1;
				aleatorio = rand() % (HASTA - DESDE + 1) + DESDE;

				// Nos miestra la pregunta aleatoria
				cout << arrayPreguntas[aleatorio].enunciado << endl;
				cout << "	" << arrayPreguntas[aleatorio].respuestaA << endl;
				cout << "	" << arrayPreguntas[aleatorio].respuestaB << endl;
				cout << "	" << arrayPreguntas[aleatorio].respuestaC << endl;
				cout << "	Elige la respuesta correcta (a,b,c): ";
				cin >> respuesta;
				cout << "------------------------------------------------------------------------------------" << endl;
				cout << endl;

				// Comparamos con la respuesta, si no es correcta además de añadirla al contador de falladas, la añadimos al array de falladas
				// que mostraremos al final del examen.
				if (respuesta == arrayPreguntas[aleatorio].respuestaCorrecta) { // RESPUESTA ACERTADA
					acertadas++;
				}
				else { // RESPUESTA FALLADA
					falladas++;
					arrayPreguntasFalladas[contadorFalladas] = arrayPreguntas[aleatorio];
					contadorFalladas++;
				}
			}

			// MOSTRAMOS RESULTADOS
			cout << "	Preguntas acertadas = " << acertadas << endl;
			cout << "	Preguntas falladas = " << falladas << endl;

			// Calculamos si hemos aprobado o no el examen, cada fallo resta el 50%, osea por cada respuesta bien se pueden tener dos mal y se queda en 0
			// Pregunta correcta 1 punto, pregunta incorrecta -0.5 puntos
			double totalPuntuacion = ((acertadas * 1) - (falladas * 0.5));

			if (totalPuntuacion >= double(numPreguntasTest/2)) cout << "	Has aprobado!!!" << endl;
			else cout << "	Game Over, vuelve a intentarlo" << endl;
		}

		// PRUEBA MOSTRAR LO QUE HA GUARDADO EL ARRAY DE PREGUNTAS
		/*cout << "Preguntas totales: " << preguntasTotales << endl;
		for (int i = 0; i < preguntasTotales; i++) {
			cout << arrayPreguntas[i].enunciado << endl;
			cout << arrayPreguntas[i].respuestaA << endl;
			cout << arrayPreguntas[i].respuestaB << endl;
			cout << arrayPreguntas[i].respuestaC << endl;
			cout << "La solución es la opción: " << arrayPreguntas[i].respuestaCorrecta << endl;
		}*/

		if (falladas > 0) {
			cout << endl << "********************************************************************" << endl;
			cout << "		HAS FALLADO EN ESTAS PREGUNTAS			" << endl;
			cout << "********************************************************************" << endl << endl;

			for (int i = 0; i < contadorFalladas; i++) {
				cout << "	" << arrayPreguntasFalladas[i].enunciado << endl;
				cout << "	" << arrayPreguntasFalladas[i].respuestaA << endl;
				cout << "	" << arrayPreguntasFalladas[i].respuestaB << endl;
				cout << "	" << arrayPreguntasFalladas[i].respuestaC << endl;
				cout << "	La solución es la opción: " << arrayPreguntasFalladas[i].respuestaCorrecta << endl;
				cout << "------------------------------------------------------------------------------------" << endl;
				cout << endl;
			}
		}

		// Reiniciamos resultados
		acertadas = 0;
		falladas = 0;

		cout << endl;
		menu();
		cin >> opcion;
		cout << endl;
	}

	return 0;
}