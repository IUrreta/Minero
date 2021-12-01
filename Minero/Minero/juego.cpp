//Realizado por Mario Gonzalez de Santos e Ignacio Urretavizcaya Tato

#include <conio.h>
#include "juego.h"
#include <fstream>
#include <string>
using namespace std;


//Funcion para leer la tecla independientemente de si la entrada es por fichero o por teclado
tTecla leerTecla(istream& movimientos) {
	char mov;
	movimientos >> mov;
	tTecla tecla;
	switch (mov) {		//diferentes valores que puede tomar la letra del movimiento

	case 'A': tecla = ARRIBA;
		break;
	case 'Z': tecla = ABAJO;
		break;
	case 'N': tecla = IZQUIERDA;
		break;
	case 'M': tecla = DERECHA;
		break;
	case 'D': tecla = TNT;
		break;
	case 'S': tecla = SALIR;
		break;
	default: tecla = NADA;
		break;
	}
	return tecla;
}


//Funcion que ejecuta el movimiento correspondiente con la tecla que le llega por parametro
void hacerMovimiento(tJuego& juego, tTecla tecla) {
	int i = 0, j = 0;
	if (tecla == ARRIBA) {		//todas las posibilidades y sus consecuencias al efectuar el movimiento hacia arriba
		if (juego.mina.plano[juego.mina.filaJ - 1][juego.mina.columnJ] == PIEDRA) {
			juego.mina.plano[juego.mina.filaJ - 2][juego.mina.columnJ] = PIEDRA;
			juego.mina.plano[juego.mina.filaJ - 1][juego.mina.columnJ] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.filaJ--;
		}
		else if (juego.mina.plano[juego.mina.filaJ - 1][juego.mina.columnJ] == TIERRA) {
			juego.mina.plano[juego.mina.filaJ - 1][juego.mina.columnJ] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.filaJ--;
		}
		else if (juego.mina.plano[juego.mina.filaJ - 1][juego.mina.columnJ] == GEMA) {
			juego.mina.plano[juego.mina.filaJ - 1][juego.mina.columnJ] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.filaJ--;
			juego.gemas++;
		}
		else if (juego.mina.plano[juego.mina.filaJ - 1][juego.mina.columnJ] == LIBRE) {
			juego.mina.plano[juego.mina.filaJ - 1][juego.mina.columnJ] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.filaJ--;
		}
		else if (juego.mina.plano[juego.mina.filaJ - 1][juego.mina.columnJ] == SALIDA) {
			juego.mina.plano[juego.mina.filaJ - 1][juego.mina.columnJ] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.filaJ--;
			juego.casillaSalida = true;
		}
	}

	else if (tecla == ABAJO) {		//todas las posibilidades y sus consecuencias al efectuar el movimiento hacia abajo
		if (juego.mina.plano[juego.mina.filaJ + 1][juego.mina.columnJ] == TIERRA) {
			juego.mina.plano[juego.mina.filaJ + 1][juego.mina.columnJ] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.filaJ++;

		}
		else if (juego.mina.plano[juego.mina.filaJ + 1][juego.mina.columnJ] == GEMA) {
			juego.mina.plano[juego.mina.filaJ + 1][juego.mina.columnJ] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.filaJ++;
			juego.gemas++;

		}
		else if (juego.mina.plano[juego.mina.filaJ + 1][juego.mina.columnJ] == LIBRE) {
			juego.mina.plano[juego.mina.filaJ + 1][juego.mina.columnJ] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.filaJ++;

		}
		else if (juego.mina.plano[juego.mina.filaJ + 1][juego.mina.columnJ] == SALIDA) {
			juego.mina.plano[juego.mina.filaJ + 1][juego.mina.columnJ] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.filaJ++;

			juego.casillaSalida = true;
		}
		caerPiedras(juego);		//Actualiza las piedras cada vez que se muevee  hacia abajo
	}
	else if (tecla == DERECHA) {		//todas las posibilidades y sus consecuencias al efectuar el movimiento hacia la derecha
		if (juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ + 1] == PIEDRA) {
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ + 2] = PIEDRA;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ + 1] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.columnJ++;
		}
		else if (juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ + 1] == TIERRA) {
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ + 1] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.columnJ++;
		}
		else if (juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ + 1] == GEMA) {
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ + 1] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.columnJ++;
			juego.gemas++;
		}
		else if (juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ + 1] == LIBRE) {
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ + 1] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.columnJ++;
		}
		else if (juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ + 1] == SALIDA) {
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ + 1] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.columnJ++;
			juego.casillaSalida = true;
		}
		caerPiedras(juego);		//Actualiza las piedras cada vez que se mueve  hacia la derecha
	}
	else if (tecla == IZQUIERDA) {		//todas las posibilidades y sus consecuencias al efectuar el movimiento hacia la izquierda
		if (juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ - 1] == PIEDRA) {
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ - 2] = PIEDRA;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ - 1] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.columnJ--;
		}
		else if (juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ - 1] == TIERRA) {
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ - 1] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.columnJ--;
		}
		else if (juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ - 1] == GEMA) {
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ - 1] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.columnJ--;
			juego.gemas++;
		}
		else if (juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ - 1] == LIBRE) {
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ - 1] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.columnJ--;
		}
		else if (juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ - 1] == SALIDA) {
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ - 1] = MINERO;
			juego.mina.plano[juego.mina.filaJ][juego.mina.columnJ] = LIBRE;
			juego.mina.columnJ--;
			juego.casillaSalida = true;
		}
		caerPiedras(juego);		//Actualiza las piedras cada vez que se muevee  hacia la izquierda
	}
	else if (tecla == SALIR) juego.termina = true;		//termina se vuelve true porque el usuario ha decidido salir
	else if (tecla == TNT) {
		actualizaDinamita(juego);		//Efectua las acciones propias de la dinamita
		caerPiedras(juego);		//Actualiza las piedras después por si la dinamita ha explotado alguna superficie sobre la que se encontraba alguna piedra
		juego.dinamitas++;
	}
	
}


//Funcion que simula con un bucle la caida de varias piedras o gemas
void caerPiedras(tJuego& juego) {
	int i = 0, j = 0;
	int ni, nj;
	for (i = juego.mina.nfilas - 1; i >= 0; i--) {		//bucle que empieza desde la ultima fila y las recorre hacia arriba para comprobar todas las piedras, ya que si se hace a la inversa, si hay 2 piedras en cascada, la que esté encima de la otra no caerá
		for (j = juego.mina.ncolumnas - 1; j >= 0; j--) {		//Bucle que recorre cada columna de una fila desde el final hasta el principio
			if ((juego.mina.plano[i][j] == PIEDRA) || (juego.mina.plano[i][j] == GEMA)) caer(juego, i, j, ni, nj);
		}
	}
}


//Funcion quie simula la caida de un elemento independientemente de que este sea una piedra, gema o dinamita
void caer(tJuego& juego, int i, int j, int& ni, int& nj) {
	while ((dentroPlano(juego.mina, i + 1, j)) && (juego.mina.plano[i + 1][j] == LIBRE)) {		//Bucle para hacer descender el elemento fila a fila
		juego.mina.plano[i + 1][j] = juego.mina.plano[i][j];		//Copia debajo del elemento el propio elemento
		juego.mina.plano[i][j] = LIBRE;								//Y la antigua posición del elemento se queda libre
		i++;
		system("cls");
		dibujar(juego);		//dibuja para que se vea la animacion de la caida
	}
	ni = i;		//Actualiza las coordenadas finales del elemento al haber caido
	nj = j;
}


//Funcion que colca la dinamita, posteriormente la hace caer y finalmente la detona (ambas llamando a caer() y explotaSuelo())
void actualizaDinamita(tJuego& juego) {
	int i = juego.mina.filaJ, j = juego.mina.columnJ;
	int ni, nj;
	juego.mina.plano[i + 1][j] = DINAMITA;		//Coloca la dinamita debajo del minero 
	caer(juego, i + 1, j, ni, nj);				//Hace la dinamita caer
	system("cls");
	explotaSuelo(ni, nj, juego);				//Explota la dinamita
}	


//Funcion que destruye las casillas que estan alrededor de la dinamita una vez esta ha llegado al punto finalk de la caida
void explotaSuelo(int filaDin, int colDin, tJuego& juego) {
	int i = filaDin - 1, j = colDin - 1;
	for (i; ((i < juego.mina.nfilas) && (i < filaDin + 2)); i++) {		//Bucle para recorrer las 3 filas que ocupan los alrededores de la dinamita
		for (j = colDin - 1; j < colDin + 2; j++) {		//Bucle para recorrer cada columna de una fila en concreto
			if (juego.mina.plano[i][j] == MINERO) {		//Rama en la que el minero muere
				dibujar(juego);
				cout << "El minero ha muerto" << endl;
				juego.termina = true;
				system("pause");
			}
			if (juego.mina.plano[i][j] != SALIDA) juego.mina.plano[i][j] = LIBRE;	//Todas las casilas que no sean la salida quedarán como vavcías

		}
	}
	dibujar(juego);
	system("cls");

}


//Funcion que determina si se dibuja la mina a escala 1:1 o 1:3 y escribe en consola el numero de movimientos, gemas recogidas y dinamitas usadas
void dibujar(tJuego juego) {
	if (juego.escala == 1) dibujar1_1(juego.mina);		//Escala 1:1
	else dibujar1_3(juego.mina);						//Escaal 1:3
	cout << endl;										//Contador de gemas, movimientos y dinamitas usadas
	cout << "Gemas recogidas: " << juego.gemas << endl;			
	cout << "Numero de movimientos: " << juego.movimientos << endl;
	cout << "Numero de dinamitas usadas: " << juego.dinamitas << endl << endl;
}


//Bucle para hacer los movimientos y dibujar la mina mientras el jugador no termine un nivel o abandone
void Jugar(tJuego& juego, istream& mapa, istream& movimientos) {
	tTecla tecla;
 	cargarMina(mapa, juego.mina, juego.nivel);
	juego.casillaSalida = false;
	juego.movimientos = 0;
	juego.dinamitas = 0;
	juego.gemas = 0;
	while ((!juego.termina) && (!juego.casillaSalida)){		//Mientras el jugador no abandone o muera o haya llegado a la salida...
		system("cls");
		dibujar(juego);
		leerMovimiento(juego, tecla, movimientos);		
		if (juego.entrada == 1) system("pause");		//Pause por si el input es el fichero, para que haya que pulsar una tecla cada vez que el jugador puede moverse despues de que todas las piedras hayan caido
		hacerMovimiento(juego, tecla);
		
	}
}


//Funcion que determina si un movimiento que el jugador pretende hacer es valido o no es posible de ejecutar
bool leerMovimiento(tJuego& juego, tTecla& tecla, istream& movimiento) {
	bool puede = false;								//se inicializa a false para que entre en el bucle automaticamente
	int i = juego.mina.filaJ, j = juego.mina.columnJ;		//Variables para facilitar la lectura del codigo		
	while (!puede) {
		tecla = leerTecla(movimiento);
		if (tecla == ARRIBA) {		//Analiza los casos en los que no se puede mover hacia arriba, y si no es ninguno de ellos, puede se convierte en true
			if (dentroPlano(juego.mina, juego.mina.filaJ - 1, juego.mina.columnJ)) {
				if (juego.mina.plano[i - 1][j] == MURO) puede = false;
				else if (juego.mina.plano[i - 1][j] == PIEDRA) {
					if ((dentroPlano(juego.mina, juego.mina.filaJ - 2, juego.mina.columnJ)) || (juego.mina.plano[i - 2][j] != LIBRE)) puede = false;
					else puede = true;
				}
				else puede = true;
			}
		}
		else if (tecla == ABAJO) {		//Analiza los casos en los que no se puede mover hacia abajo, y si no es ninguno de ellos, puede se convierte en true
			if (dentroPlano(juego.mina, juego.mina.filaJ + 1, juego.mina.columnJ)) {
				if (juego.mina.plano[i + 1][j] == MURO) puede = false;
				else if (juego.mina.plano[i + 1][j] == PIEDRA) puede = false;
				else puede = true;
			}
		}
		else if (tecla == DERECHA) {		//Analiza los casos en los que no se puede mover hacia la derecha, y si no es ninguno de ellos, puede se convierte en true
			if (dentroPlano(juego.mina, juego.mina.filaJ, juego.mina.columnJ + 1)) {
				if (juego.mina.plano[i][j + 1] == MURO) puede = false;
				else if (juego.mina.plano[i][j + 1] == PIEDRA) {
					if (!(dentroPlano(juego.mina, juego.mina.filaJ, juego.mina.columnJ + 2)) || (juego.mina.plano[i][j + 2] != LIBRE)) puede = false;
					else puede = true;
				}
				else puede = true;
			}
		}
		else if (tecla == IZQUIERDA) {		//Analiza los casos en los que no se puede mover hacia la izquierda, y si no es ninguno de ellos, puede se convierte en true
			if (dentroPlano(juego.mina, juego.mina.filaJ, juego.mina.columnJ - 1)) {
				if (juego.mina.plano[i][j - 1] == MURO) puede = false;
				else if (juego.mina.plano[i][j - 1] == PIEDRA) {
					if ((dentroPlano(juego.mina, juego.mina.filaJ, juego.mina.columnJ - 2)) || (juego.mina.plano[i][j - 2] != LIBRE)) puede = false;
					else puede = true;
				}
				else puede = true;
			}
		}
		else if (tecla == TNT) puede = true;		//La dinamita se puede poner siempre
		else if (tecla == SALIR) {					//siempre se puede salir
			puede = true;
			juego.termina = true;		//termina se pone a true porque el juego acaba
		}
	}
	juego.movimientos++;			//Movimientos solo aumenta si puede acaba siendo true
	return puede;
}




