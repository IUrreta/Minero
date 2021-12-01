//Realizado por Mario Gonzalez de Santos e Ignacio Urretavizcaya Tato


#pragma once
#ifndef mina_h
#define mina_h

#include <iostream>

using namespace std;


const int MAX = 50;

enum tCasilla { LIBRE, TIERRA, GEMA, PIEDRA, MURO, SALIDA, MINERO, DINAMITA };

typedef tCasilla tPlano[MAX][MAX];
typedef char tPlanoCaracteres[3 * MAX][3 * MAX];
typedef int tPlanoColores[3 * MAX][3 * MAX];



struct tMina {
	tPlano plano;
	int nfilas, ncolumnas;
	int filaJ, columnJ;
};




bool dentroPlano(tMina const& mina, int i, int j);	//funcion que comprueba si una casilla determinada esta dentro del plano o no
void dibujar1_1(const tMina& mina);		//Dibuja la mina a escala 1:1
void dibujar1_3(const tMina& mina);		//Dibuja la mina a escala 1:3
void dibuja3x3(tCasilla casilla, tPlanoCaracteres caracteres,		//Crea el plano virtual de la mina y sus colores a escala 1:3
	tPlanoColores colores, int i, int j);
void cargarMina(istream& fichero, tMina& mina, int nivel);		//Carga la mina desde el fichero que se le pasa por parametro
void colorFondo(int color);		//Funcion que establece los colores de la mina




#endif /* mina_h */
