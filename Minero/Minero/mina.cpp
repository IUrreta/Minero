//Realizado por Mario Gonzalez de Santos e Ignacio Urretavizcaya Tato


#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "mina.h"
using namespace std;



//funcion que comprueba si una casilla determinada esta dentro del plano o no
bool dentroPlano(tMina const& mina, int i, int j) {
	bool dentro = false;
	if (((i < mina.nfilas) && (i >= 0)) &&
		((j < mina.ncolumnas) && (j >= 0))) {
		dentro = true;		//dentro solo será true cuando las coordenadas i y j sean mayores que 0 y menores que el numero de filas y columnas de la mina
	}
	return dentro;
}


//Dibuja la mina a escala 1:1
void dibujar1_1(const tMina& mina) {
	int i = 0, j = 0;
	for (i = 0; i < mina.nfilas; i++) {		//Bucle para dibujar cada fila
		if (i > 0) cout << endl;
		for (j = 0; j < mina.ncolumnas; j++) {		//Bucle para dibujar cada columna de una fila en concreto
			if (mina.plano[i][j] == MINERO) {
				colorFondo(8);
				cout << "M";
			}
			else if (mina.plano[i][j] == PIEDRA) {
				colorFondo(4);
				cout << " @";
			}
			else if (mina.plano[i][j] == MURO) {
				colorFondo(4);
				cout << " X";
			}
			else if (mina.plano[i][j] == TIERRA) {
				colorFondo(4);
				cout << " .";
			}
			else if (mina.plano[i][j] == GEMA) {
				colorFondo(2);
				cout << " G"; 
			}
			else if (mina.plano[i][j] == LIBRE) {
				colorFondo(4);
				cout << "  ";
			}
			else if (mina.plano[i][j] == SALIDA) {
				colorFondo(9);
				cout << " S";
			}
			else if (mina.plano[i][j] == DINAMITA) {
				colorFondo(15);
				cout << " D";
			}
			colorFondo(0);		//Se vuelve a establecer el color de fondo predeterminado
		}
	}

}


//Dibuja la mina a escala 1:3
void dibujar1_3(const tMina& mina) {
	tPlanoCaracteres caracteres;
	tPlanoColores colores;
	for (int i = 0; i < (3 * mina.nfilas); i++) {		//Bucle para recorrer todas las filas del plano

		for (int j = 0; j < (3 * mina.ncolumnas); j++) {		//Bucle para recorrer todas las columnas
			if ((i < mina.ncolumnas) && (j < mina.ncolumnas)) dibuja3x3(mina.plano[i][j], caracteres, colores, i, j);		//Invoca a dibujar3x3 que dibuja una casilla del 1x1 como una del 3x3 en un plano "virtual"
			colorFondo(colores[i][j]); 
			cout << caracteres[i][j] << " ";		//Va dibujando cada uno de los caracteres del plano virtual por consola
		}
		cout << endl;
	}
	colorFondo(0);
}


//Crea el plano virtual de la mina y sus colores a escala 1:3
void dibuja3x3(tCasilla casilla, tPlanoCaracteres caracteres,
	tPlanoColores colores, int i, int j) {
	if (casilla == PIEDRA) {
		for (int k = 0; k < 3; k++) {		//Bucle para recorrer las 3 filas de una piedra
			for (int l = 0; l < 3; l++) {		//Bucle para recorrer las 3 columnas de cada fila de la piedra
				caracteres[(i * 3) + k][(j * 3) + l] = '@';
				colores[(i * 3) + k][(j * 3) + l] = 4;
			}
		}
	}
	else if (casilla == TIERRA) {		
		for (int k = 0; k < 3; k++) {		//Bucle para recorrer las 3 filas de una tierra
			for (int l = 0; l < 3; l++) {		//Bucle para recorrer las 3 columnas de cada fila de la tierra
				caracteres[(i * 3) + k][(j * 3) + l] = '.';
				colores[(i * 3) + k][(j * 3) + l] = 4;
			}
		}
	}
	else if (casilla == LIBRE) {		
		for (int k = 0; k < 3; k++) {		//Bucle para recorrer las 3 filas de cada fila de una casilla libre
			for (int l = 0; l < 3; l++) {		//Bucle para recorrer las 3 columnas de cada fila de una casilla libre
				caracteres[(i * 3) + k][(j * 3) + l] = ' ';
				colores[(i * 3) + k][(j * 3) + l] = 4;
			}
		}
	}
	else if (casilla == GEMA) {		
		for (int k = 0; k < 3; k++) {		//Bucle para recorrer las 3 filas de cada fila de la gema
			for (int l = 0; l < 3; l++) {		//Bucle para recorrer las 3 columnas de cada fila de la gema
				caracteres[(i * 3) + k][(j * 3) + l] = 'G';
				colores[(i * 3) + k][(j * 3) + l] = 2;
			}
		}
	}
	else if (casilla == MURO) {			
		for (int k = 0; k < 3; k++) {		//Bucle para recorrer las 3 filas de cada fila de un muro
			for (int l = 0; l < 3; l++) {		//Bucle para recorrer las 3 columnas de cada fila de un muro
				caracteres[(i * 3) + k][(j * 3) + l] = 'X';
				colores[(i * 3) + k][(j * 3) + l] = 4;
			}
		}
	}
	else if (casilla == SALIDA) {		
		for (int k = 0; k < 3; k++) {		//Bucle para recorrer las 3 filas de cada fila de la salida
			for (int l = 0; l < 3; l++) {		//Bucle para recorrer las 3 columnas de cada fila de la salida
				caracteres[(i * 3) + k][(j * 3) + l] = 'S';
				colores[(i * 3) + k][(j * 3) + l] = 9;
			}
		}
	}
	else if (casilla == MINERO) {		
		for (int k = 0; k < 3; k++) {		//Bucle para recorrer las 3 filas de cada fila del minero
			for (int l = 0; l < 3; l++) {		//Bucle para recorrer las 3 columnas de cada fila del minero
				caracteres[(i * 3) + k][(j * 3) + l] = 'M';
				colores[(i * 3) + k][(j * 3) + l] = 8;
			}
		}
	}
	else if (casilla == DINAMITA) {
		for (int k = 0; k < 3; k++) {		//Bucle para recorrer las 3 filas de cada fila de una dinamita
			for (int l = 0; l < 3; l++) {		//Bucle para recorrer las 3 columnas de cada fila de una dinamita
				caracteres[(i * 3) + k][(j * 3) + l] = 'D';
				colores[(i * 3) + k][(j * 3) + l] = 15;
			}
		}
	}

}

//Carga la mina desde el fichero que se le pasa por parametro
void cargarMina(istream& fichero, tMina& mina, int nivel) {
	string elemMina;
	string caracter;

	fichero >> mina.nfilas;
	fichero >> mina.ncolumnas;
	getline(fichero, elemMina);		//Primer getline para asegurarse de que el siguiente getline funcione bien
	for (int i = 0; i < mina.nfilas; i++) {
		getline(fichero, elemMina);		//Se guarda en elemMina una fila de la mina
		for (int j = 0; j < mina.ncolumnas; j++) {

			caracter = elemMina.substr(j, 1);		//se coge cada elemento de la fila que se ha guardado para cargarlo por separado

			if (caracter == "G") {		//Lo compara con todas las posibilidades que hay
				mina.plano[i][j] = GEMA;
			}
			else if (caracter == "M") {
				mina.plano[i][j] = MURO;
			}
			else if (caracter == "J") {
				mina.plano[i][j] = MINERO;
				mina.columnJ = j;
				mina.filaJ = i;
			}
			else if (caracter == "T") {
				mina.plano[i][j] = TIERRA;
			}
			else if (caracter == " ") {
				mina.plano[i][j] = LIBRE;
			}
			else if (caracter == "P") {
				mina.plano[i][j] = PIEDRA;
			}
			else if (caracter == "S") {
				mina.plano[i][j] = SALIDA;
			}

		}


	}

}


//Funcion que establece los colores de la mina
void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}