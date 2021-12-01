//Realizado por Mario Gonzalez de Santos e Ignacio Urretavizcaya Tato


#ifndef juego_h
#define juego_h


#include "mina.h"
#include <fstream>
using namespace std;

enum tTecla { ARRIBA, ABAJO, IZQUIERDA, DERECHA, TNT, NADA, SALIR };

struct tJuego {
	tMina mina;
	int gemas = 0, movimientos = 0, dinamitas = 0, escala = 1;
	bool casillaSalida = false;		//bool para comprobar si el jugador ha alcanzado la casilla de salida
	int nivel = 0;		//Contador para controlar el nivel 
	bool termina = false;		//Termina controla si el jugador ha abandonado o muerto
	int entrada = -1; //0 si es por teclado 1 si es por fichero
};

tTecla leerTecla(istream& movimientos);		//Funcion para leer la tecla independientemente de si la entrada es por fichero o por teclado
void hacerMovimiento(tJuego& juego, tTecla tecla);		//Funcion que ejecuta el movimiento correspondiente con la tecla que le llega por parametro
void caerPiedras(tJuego& juego);		//Funcion que simula con un bucle la caida de varias piedras o gemas 
void actualizaDinamita(tJuego& juego);		//Funcion que colca la dinamita, posteriormente la hace caer y finalmente la detona (ambas llamando a caer() y explotaSuelo())
void explotaSuelo(int filaDin, int colDin, tJuego& juego);		//Funcion que destruye las casillas que estan alrededor de la dinamita una vez esta ha llegado al punto finalk de la caida
void dibujar(tJuego juego);		//Funcion que determina si se dibuja la mina a escala 1:1 o 1:3 y escribe en consola el numero de movimientos, gemas recogidas y dinamitas usadas
bool leerMovimiento(tJuego& juego, tTecla& tecla, istream& movimiento);		//Funcion que determina si un movimiento que el jugador pretende hacer es valido o no es posible de ejecutar
void Jugar(tJuego& juego, istream& mapa, istream& movimientos);		//Bucle para hacer los movimientos y dibujar la mina mientras el jugador no termine un nivel o abandone
void caer(tJuego& juego, int i, int j, int& ni, int& nj);		//Funcion quie simula la caida de un elemento independientemente de que este sea una piedra, gema o dinamita


#endif /* juego_h */
