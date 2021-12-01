//Realizado por Mario Gonzalez de Santos e Ignacio Urretavizcaya Tato

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "juego.h"
#include "Puntuaciones.h"
using namespace std;

const int A = 10;
const int B = 2;

void menuEscala(tJuego& juego);			//Menu para elegir a la escala a la que se va a dibujar la mina

void menuNivel(tJuego& juego);			//Menu para elegir si pasar al siguiente nivel o salir

void menuEntrada(tJuego& juego);		//Funcion paras elegir el metodo de entrada

void importarDatos(tPuntuaciones& marcador, tJuego juego);		//Funcion que sirve de enlace entre las estadisticas del modulo juego y las del modulo puntuaciones


int main() {

	tJuego juego;
	ifstream ficheroMina;
	ifstream movimientos;
	tPuntuaciones marcador;
	inicializar_Marcador(marcador);
	cargar_Marcador(marcador);

	menuEscala(juego);
	system("cls");
	while ((!juego.termina) && (juego.escala != 0)) {		//Mientras no haya terminado el juego (muera o salga), no haya llegado a la salida o no haya superado todos los niveles...
		juego.nivel = iniciarPartida(marcador);
		if (juego.nivel == 0) juego.termina = true;
		system("cls");
		if (!juego.termina) {		//proteccion por si en menuNivel se elige salir, que no abra mas archivos ni llame a mas subrutinas
			menuEntrada(juego);		//1 si es fichero, 0 si es teclado

			ficheroMina.open(to_string(juego.nivel) + ".txt");
			if (!ficheroMina.is_open()) cout << "No se ha podido encontrar el fihchero deseado" << endl;
			else {
				if (juego.entrada == 1) {		//Si la entrada es por fichero se abre el fichero de movimientos, y se pasa por parametro a Jugar()
					if (juego.nivel == 1) movimientos.open("movimientos.txt");		//Proteccion para que solo abra el fichero de movimientos una vez(cuando se empieza el primer nivel)	
					Jugar(juego, ficheroMina, movimientos);
				}
				else Jugar(juego, ficheroMina, cin);		//Si la entrada es por teclado, se pasa por parametro el cin a Jugar()
				ficheroMina.close();

			}
			importarDatos(marcador, juego);
		}
		mostrar_Datos_Usuario(marcador);
	}
	guardar_Marcador(marcador);
	system("cls");
	destruir(marcador);
	return 0;
}

//Menu para elegir a la escala a la que se va a dibujar la mina
void menuEscala(tJuego& juego) {
	juego.escala = -1;		//se inicializa a -1 para que entre en el bucle automaticamente
	while ((juego.escala < 0) || (juego.escala > 2)) {
		cout << "1. Jugar partida a escala 1:1." << endl << "2. Jugar partida a escala 1:3." << endl << "0. Salir." << endl;
		cin >> juego.escala;
		system("cls");
	}
}

//Menu para elegir si pasar al siguiente nivel o salir
void menuNivel(tJuego& juego) {
	int opcion = -1;		//se inicializa a -1 para que entre en el bucle automaticamente
	while ((opcion < 0) || (opcion > 1)) {
		cout << "1. Siguiente Nivel" << endl << "0. Salir" << endl;
		cin >> opcion;
		system("cls");
	}
	if (opcion == 1) {
		juego.nivel++;		//Si ha seleccionado 1, se aumenta el nivel, y se pone a false el que ha llegado a la casilla de salida
		juego.casillaSalida = false;
	}
	else juego.termina = true;		//Si no se ha selecccionado 1, es porque se ha seleccionado 0, por lo que el juego termina

}

//Funcion paras elegir el metodo de entrada
void  menuEntrada(tJuego& juego) {
	juego.entrada = -1;		//se inicializa a -1 para que entre en el bucle automaticamente
	while ((juego.entrada < 0) || (juego.entrada > 1)) {
		cout << "Eliga una opcion de entrada de movimientos: " << endl;
		cout << "0. Teclado" << endl << "1. Fichero" << endl;
		cin >> juego.entrada;
		system("cls");
	}
}

//Funcion que sirve de enlace entre las estadisticas del modulo juego y las del modulo puntuaciones
void importarDatos(tPuntuaciones& marcador, tJuego juego) {
	int i = 0;
	int puntosNoGuardados = ((juego.mina.ncolumnas * juego.mina.nfilas) + (A * juego.gemas) - juego.movimientos - (B * juego.dinamitas));
	if (puntosNoGuardados > marcador.array_clasificacion[marcador.posJugador].vMinasRecorridas[juego.nivel - 1].puntosMina) {		//Proteccion para que se registren solo las minas mas altas
		marcador.array_clasificacion[marcador.posJugador].vMinasRecorridas[juego.nivel - 1].numDinamitas = juego.dinamitas;
		marcador.array_clasificacion[marcador.posJugador].vMinasRecorridas[juego.nivel - 1].numGemas = juego.gemas;
		marcador.array_clasificacion[marcador.posJugador].vMinasRecorridas[juego.nivel - 1].numMovimientos = juego.movimientos;
		marcador.array_clasificacion[marcador.posJugador].vMinasRecorridas[juego.nivel - 1].puntosMina = puntosNoGuardados;
		if (marcador.array_clasificacion[marcador.posJugador].vMinasRecorridas[juego.nivel - 1].numMovimientos == 0)		//Solo si no has recorrido la mina X antes suma uno al contador de minas recorridas
			marcador.array_clasificacion[marcador.posJugador].minasRecorridas++;
		marcador.array_clasificacion[marcador.posJugador].vMinasRecorridas[juego.nivel - 1].IdMina = juego.nivel;
		marcador.array_clasificacion[marcador.posJugador].punt_total = 0;
		for (i = 0; i < 5; i++) {		//Bucle para sumar todos los puntos mina por mina
			marcador.array_clasificacion[marcador.posJugador].punt_total = marcador.array_clasificacion[marcador.posJugador].punt_total + marcador.array_clasificacion[marcador.posJugador].vMinasRecorridas[i].puntosMina;
		}
	}
	else cout << endl << "Tu puntuacion de " << puntosNoGuardados << " puntos en la mina " << juego.nivel << " es inferior a la que hay guardada (" << marcador.array_clasificacion[marcador.posJugador].vMinasRecorridas[juego.nivel - 1].puntosMina << ") por lo que se mantiene la puntuacion mas alta." << endl << endl;
	system("pause");
}


