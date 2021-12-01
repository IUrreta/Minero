//Realizado por Mario Gonzalez de Santos e Ignacio Urretavizcaya Tato
#include "Puntuaciones.h"


//genera el array dinámico base
void inicializar_Marcador(tPuntuaciones& marcador) {
	tPuntuacionJugador* puntuacion = new tPuntuacionJugador[marcador.capacidad];		//crea por primera vez el array dinámico con un tamaño preestablecido
	marcador.array_clasificacion = puntuacion;
	puntuacion = NULL;
}


//carga en el array dinámico los datos de los jugadores
bool cargar_Marcador(tPuntuaciones& marcador) {
	ifstream archivo;
	bool final_array = false;
	int i = 0;
	int numero_mina;
	string nombre;
	archivo.open("Puntuaciones.txt");
	if (!archivo.is_open()) cout << "Error al abrir el archivo asegurese de que está en la carpeta" << endl;	//comprueba que el fichero Puntuaciones.txt está en la carpeta
	else {
		while (!final_array) {		//mientras haya jugadores por cargar...
			int contadorMinasLeidas = 0;
			if (i == marcador.capacidad) aumentar_Capacidad(marcador);
			archivo >> nombre;																				//carga el nombre del jugador, si es igual a 000 entonces ha llegado al final del fichero
			if (nombre == "000") final_array = true;
			else {
				marcador.array_clasificacion[i].nombre = nombre;
				archivo >> marcador.array_clasificacion[i].punt_total;										//guarda en el array dinámico los datos generales deljugador
				archivo >> marcador.array_clasificacion[i].minasRecorridas;
				if (marcador.array_clasificacion[i].minasRecorridas != 0)archivo >> numero_mina;
				else numero_mina = 0;
				for (int j = 0; j < 5; j++) {																//comprueba si el jugador ha rocorrido la mina j
					if (numero_mina != j + 1) {																	//si el numero de la mina es distinto al valor del elemento j, la mina j no ha sido recorrida por el jugador
						marcador.array_clasificacion[i].vMinasRecorridas[j].IdMina = j + 1;						//la puntuacion del jugador en la mina j es cero en todos los valores
						marcador.array_clasificacion[i].vMinasRecorridas[j].numMovimientos = 0;
						marcador.array_clasificacion[i].vMinasRecorridas[j].numGemas = 0;
						marcador.array_clasificacion[i].vMinasRecorridas[j].numDinamitas = 0;
						marcador.array_clasificacion[i].vMinasRecorridas[j].puntosMina = 0;
					}
					else {																				//caso en el que el jugador si ha recorrido la mina j
						marcador.array_clasificacion[i].vMinasRecorridas[j].IdMina = numero_mina;		//se carga los datos del jugador en dicha mina
						archivo >> marcador.array_clasificacion[i].vMinasRecorridas[j].numMovimientos;
						archivo >> marcador.array_clasificacion[i].vMinasRecorridas[j].numGemas;
						archivo >> marcador.array_clasificacion[i].vMinasRecorridas[j].numDinamitas;
						archivo >> marcador.array_clasificacion[i].vMinasRecorridas[j].puntosMina;
						contadorMinasLeidas++;
						if ((j != 4) && (contadorMinasLeidas < marcador.array_clasificacion[i].minasRecorridas)) archivo >> numero_mina;			//Si no es la última vuelta del bucle, carga el siguiente numero de la mina recorrida por el jugador, para hacer la comprobación en la próxima vuelta del bucle
					}
				}
				i++;
				marcador.num_jugadores = i;


			}

		}
		archivo.close();
		return final_array;

	}
}




//esta función amplia el array dinámico cuando es llamada
void aumentar_Capacidad(tPuntuaciones& marcador) {
	tPuntuacionJugador* ptrPuntuacion = new tPuntuacionJugador[2 * marcador.capacidad];		//genera un nuevo array dinámico del doble de capacidad que el que tenemos actualmente
	int i = 0;
	for (i = 0; i < marcador.capacidad; i++) {							//Copia los datos del array actual en el nuevo, que tiene mayor capacidad
		ptrPuntuacion[i] = marcador.array_clasificacion[i];
	}
	delete[] marcador.array_clasificacion;							//elimina el array actual para quedarnos con el nuevo que hemos creado con mayor capacidad
	marcador.array_clasificacion = ptrPuntuacion;
	marcador.capacidad *= 2;
	ptrPuntuacion = NULL;										//Ahora solo el array que está dentro de marcador apuntará a los datos

}



//comprueba si el jugador introducido ya había jugado previamente
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos) {
	int ini = 0, fin = marcador.num_jugadores - 1, mitad;
	bool encontrado = false;
	while ((ini <= fin) && (!encontrado)) {					//Busca si el jugador introducido existía previamente
		mitad = (ini + fin) / 2;
		if (nombre == marcador.array_clasificacion[mitad].nombre) {
			encontrado = true;
			pos = mitad;
		}
		else if (nombre < marcador.array_clasificacion[mitad].nombre) fin = mitad - 1;
		else ini = mitad + 1;
		if (ini > fin) pos = ini;
	}
	
	return encontrado;					//Devuelve true si ya existía y false en caso contrario
}



//elimina el array dinámico
void destruir(tPuntuaciones& marcador) {
	delete[] marcador.array_clasificacion;		//suprime el array dinámico para ahorrar memoria
	marcador.capacidad = 0;
}


//introduce al nuevo jugador dentro del array dinámico
void insertar(tPuntuaciones& marcador, string const& nombre, int pos) {
	int i = 0, j = 0;
	if (marcador.num_jugadores == marcador.capacidad) aumentar_Capacidad(marcador);		//En el caso en el que la capacidad del array sea insuficiente para incluir a un nuevo jugador se llamará a aumentar capacidad
	else {
		for (i = marcador.num_jugadores - 1; i >= pos; i--) {							//mueve una posicion a la derecha a los jugadores que, por nombre, estén dentrás del nuevo jugador
			marcador.array_clasificacion[i + 1] = marcador.array_clasificacion[i];
		}
		marcador.array_clasificacion[pos].nombre = nombre;
		marcador.array_clasificacion[pos].minasRecorridas = 0;
		marcador.array_clasificacion[pos].punt_total = 0;
		for (j = 0; j < 5; j++) {													//Inicializa a 0 los datos del nuevo jugador en el array, en su posición corres pondiente
			marcador.array_clasificacion[pos].vMinasRecorridas[j].IdMina = j + 1;
			marcador.array_clasificacion[pos].vMinasRecorridas[j].numDinamitas = 0;
			marcador.array_clasificacion[pos].vMinasRecorridas[j].numGemas = 0;
			marcador.array_clasificacion[pos].vMinasRecorridas[j].numMovimientos = 0;
			marcador.array_clasificacion[pos].vMinasRecorridas[j].puntosMina = 0;
		}
	}
	marcador.num_jugadores++;
}



//Muestra las estadísticas de los jugadores cuando entra un jugador ya registrado
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont) {
	bool primerLinea = false;
	cout << "        Ya estas registrado/a." << endl;
	cout << "        Mira las minas que has recorrido ordenadas por nivel." << endl << endl;
	cout << " " << marcador.array_clasificacion[cont].nombre << "  Movimientos  Gemas  Dinamitas  Puntos      Puntos en Total" << endl;
	for (int i = 0; i < 5; i++) {
		if (marcador.array_clasificacion[cont].vMinasRecorridas[i].numMovimientos == 0);
		else {
			cout << " Mina " << i + 1 << "        " << marcador.array_clasificacion[cont].vMinasRecorridas[i].numMovimientos << "         " << marcador.array_clasificacion[cont].vMinasRecorridas[i].numGemas << "        " << marcador.array_clasificacion[cont].vMinasRecorridas[i].numDinamitas << "        " << marcador.array_clasificacion[cont].vMinasRecorridas[i].puntosMina;
			if (!primerLinea) {
				cout << "             " << marcador.array_clasificacion[cont].punt_total;			//Solo aparecen los puntos totales de cada jugador una vez junto a los datos de la primera mina recorrida
				primerLinea = true;

			}
			cout << endl;
		}
	}
	cout << endl;
}



//Muestra los puntos de los jugadores registrados cuando entra un nuevo jugador
void mostrar_Alfabetico(const tPuntuaciones& marcador) {
	cout << "        Mira las puntuaciones de los otros jugadores." << endl << endl;
	cout << "           -----------  LISTA DE JUGADORES   -----------" << endl << endl;
	for (int i = 0; i < marcador.num_jugadores; i++) {
		cout << "                          " << marcador.array_clasificacion[i].nombre << "  " << marcador.array_clasificacion[i].punt_total << endl;
	}
	cout << endl;
	system("pause");
	cout << endl;
}



//Pide el nombre del jugador y la mina que deseará recorrer
int	 iniciarPartida(tPuntuaciones& marcador) {
	int pos;
	int op = -1;
	string nombre;
	if (!marcador.partidaIniciada) {							//Cuando el jugador comienza la partida se le pide el nombre y comprueba si está dentro del array de jugadores
		cout << "        Introduce tu nombre de jugador/a: ";
		cin >> nombre;
		if (buscar(nombre, marcador, pos)) mostrar_Minas_Usuario(marcador, pos);
		else {
			cout << "        Eres nuevo/a: " << nombre << endl;							//Si el jugador es nuevo se le incluye dentro del array dinámico
			mostrar_Alfabetico(marcador);
			insertar(marcador, nombre, pos);
		}
		marcador.partidaIniciada = true;		//Un booleano indica que el jugador ya ha se ha inicializado los datos del jugador y por tanto no volverá a preguntar su nombre
		marcador.posJugador = pos;
	}
	cout << " " << marcador.array_clasificacion[marcador.posJugador].nombre << ", Que mina quieres explorar?" << endl;		
	cout << "Introduce un numero entre 1 y 5 para explorar una mina y 0 para salir." << endl;
	while ((op < 0) || (op > 5)) {
		cin >> op;
		if ((op < 0) || (op > 5)) cout << "Opcion no valida" << endl;
	}
	return op;									//Devuelve el número de la mina que recorrerá el jugador
}



//Muestra las estadísticas de cada jugador tras haber jugado una partida
void mostrar_Datos_Usuario(const tPuntuaciones& marcador) {
	int i = 0;
	int j = 0;
	bool primerLinea = false;
	system("cls");
	cout << "           -----------  LISTA DE JUGADORES   -----------" << endl << endl;
	for (i = 0; i < marcador.num_jugadores; i++) {
		primerLinea = false;
		cout << " " << marcador.array_clasificacion[i].nombre << "  Movimientos  Gemas  Dinamitas  Puntos      Puntos en Total" << endl;
		for (j = 0; j < 5; j++) {
			if (marcador.array_clasificacion[i].vMinasRecorridas[j].numMovimientos == 0);
			else {
				cout << " Mina " << j + 1 << "        " << marcador.array_clasificacion[i].vMinasRecorridas[j].numMovimientos << "         " << marcador.array_clasificacion[i].vMinasRecorridas[j].numGemas << "        " << marcador.array_clasificacion[i].vMinasRecorridas[j].numDinamitas << "        " << marcador.array_clasificacion[i].vMinasRecorridas[j].puntosMina;
				if (!primerLinea) {
					cout << "             " << marcador.array_clasificacion[i].punt_total;		//Solo aparecen los puntos totales de cada jugador una vez junto a los datos de la primera mina recorrida
					primerLinea = true;
					cout << endl;
				}
				else cout << endl;
			}
		}
		cout << endl << endl;
	}
	cout << endl;
	system("pause");


	cout << endl;
}



//guarda en el fichero "puntuaciones" los datos del array dinámico al final de la partida
bool guardar_Marcador(tPuntuaciones& marcador) {
	ofstream archivo;
	int i = 0;
	int j = 0;
	archivo.open("puntuaciones.txt");
	if (!archivo.is_open()) cout << "No se ha podido enco0ntrar el archivo para guardar las puntuaciones" << endl << endl;
	else {
		for (i = 0; i < marcador.num_jugadores; i++) {								//guarda uno por uno los datos de los jugadores
			archivo << marcador.array_clasificacion[i].nombre << endl;
			archivo << marcador.array_clasificacion[i].punt_total << endl;
			archivo << marcador.array_clasificacion[i].minasRecorridas << endl;
			for (j = 0; j < 5; j++) {												//guarda una por una los datos de cada mina recorrida por cada jugador
				if (marcador.array_clasificacion[i].vMinasRecorridas[j].numMovimientos == 0);
				else {
					archivo << marcador.array_clasificacion[i].vMinasRecorridas[j].IdMina << " ";
					archivo << marcador.array_clasificacion[i].vMinasRecorridas[j].numMovimientos << " ";
					archivo << marcador.array_clasificacion[i].vMinasRecorridas[j].numGemas << " ";
					archivo << marcador.array_clasificacion[i].vMinasRecorridas[j].numDinamitas << " ";
					archivo << marcador.array_clasificacion[i].vMinasRecorridas[j].puntosMina << endl;
				}
			}
		}
		archivo << "000";											//se escribe 000 al final del archivo para saber que este ha llegado a su fin
	}
	archivo.close();
	return true;
}
