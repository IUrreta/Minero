//Realizado por Mario Gonzalez de Santos e Ignacio Urretavizcaya Tato
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include<conio.h>
#include<string>


#ifndef PUNTUACIONES_H

using namespace std;
const int NUM_TOTAL_MINAS = 5;



struct tDatosMina {		//Datos de cada mina en carticular, de cada jugador
	int IdMina;
	int numMovimientos;
	int numGemas;
	int numDinamitas;
	int puntosMina;
};

struct tPuntuacionJugador {				//Informacion de cada jugador y el array de minas recorridas
	string nombre;
	int punt_total;
	int minasRecorridas;
	tDatosMina vMinasRecorridas[NUM_TOTAL_MINAS];
};

struct tPuntuaciones {						//Informacion sobre el numero de jugadores y la capacidad del array dinámico
	int capacidad = 4;
	int num_jugadores;
	tPuntuacionJugador* array_clasificacion;
	bool partidaIniciada = false;
	int posJugador = 0;
};


bool cargar_Marcador(tPuntuaciones& marcador);      //carga en el array dinámico los datos de los jugadores
bool guardar_Marcador(tPuntuaciones& marcador);		//guarda en el fichero "puntuaciones" los datos del array dinámico al final de la partida
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont); //Muestra las estadísticas de los jugadores cuando entra un jugador ya registrado
void mostrar_Alfabetico(const tPuntuaciones& marcador);		//Muestra los puntos de los jugadores registrados cuando entra un nuevo jugador
void mostrar_Datos_Usuario(const tPuntuaciones& marcador);	//Muestra las estadísticas de cada jugador tras haber jugado una partida
void inicializar_Marcador(tPuntuaciones& marcador);			//genera el array dinámico base
void aumentar_Capacidad(tPuntuaciones& marcador);			//esta función amplia el array dinámico cuando es llamada
void destruir(tPuntuaciones& marcador);						//elimina el array dinámico
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos);		//comprueba si el jugador introducido ya había jugado previamente
void insertar(tPuntuaciones& marcador, string const& nombre, int pos);			//introduce al nuevo jugador dentro del array dinámico
int	 iniciarPartida(tPuntuaciones& marcador);				//Pide el nombre del jugador y la mina que deseará recorrer


#endif 