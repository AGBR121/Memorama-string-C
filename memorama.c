/*
- Autor: Ing(c) Burbano Rodriguez Angel Gabriel
- Nombre del lenguaje utilizado: C
- Versión del lenguaje utilizado: C11
- Versión del compilador utilizado: GCC 6.3.0
- Versión del S.O: Windows 10 Pro Versión 22H2
- Descripcion del programa: Este programa consiste en un algoritmo para jugar el juego del memorama con solo string.
- Salvedad: si se ingresa un dato que no sea un entero, no garantizamos los resultados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/*
Función CreateString que crea un string de caracteres repetidos de acuerdo a lo que se desee
- cadena: es la cadena final a devolver
- counter: es el contador de la función recursiva
- number: es el ancla para la cantidad de caracteres del string
- letter: es el caracter a agregar
*/
char* CreateString(char cadena[], int counter, int number, char letter) {
    if (counter < number) {
        cadena[counter] = letter;
        return CreateString(cadena, counter + 1, number, letter);
    } else {
        cadena[counter] = '\0'; 
        return cadena;
    }
}

/*
Función GenerateCadena que genera una string aleatoria para el juego del memorama
- cadena: es la cadena final a devolver
- counter: es el contador de la función recursiva
- counter2: es el contador de letras repetidas para el juego
- letter: es el caracter a agregar
*/
char* GenerateCadena(char cadena[], int counter, int counter2, int letter) {
    int num = rand() % 16;  
    if (counter < 16) {
        if (cadena[counter] != 'a') {
            return GenerateCadena(cadena, counter + 1, counter2, letter);
        } else {
            if (counter2 < 2) {
                if (cadena[num] == 'a') {
                    cadena[num] = letter; 
                    return GenerateCadena(cadena, 0, counter2 + 1, letter);
                } else {
                    return GenerateCadena(cadena, 0, counter2, letter);
                }
            } else {
                return GenerateCadena(cadena, 0, 0, letter + 1);  
            }
        }
    } else {
        return cadena; 
    }
}

/*
Función PrintTable que se encarga de imprimir el tablero del juego
- table: es el juego a imprimir
- player1: es el nombre del jugador 1
- player2: es el nombre del jugador 2
- player: es el jugador al que le toca jugar en la ronda
- score1: es la cantidad de puntos del jugador 1
- score2: es la cantidad de puntos del jugador 2
- status: es el que guarda el texto de si el jugador ganó o no
*/
void PrintTable(char table[], char player1[], char player2[], char player[], int score1, int score2, char status[]) {
    //Longitud1 guarda la cantidad de caracteres que tiene la variable player1
    int longitud1 = strlen(player1);
    //Longitud2 guarda la cantidad de caracteres que tiene la variable player2
    int longitud2 = strlen(player2);
    //nEspacios es la variable que contiene la cantidad de espacios que hay entre el nombre y la puntuacion
    int nEspacios = 14;
    //espacios1 es la variable que guarda los espacios totales entre el nombre del jugador 1 y su puntuación
    char espacios1[50] = "";
    //espacios2 es la variable que guarda los espacios totales entre el nombre del jugador 2 y su puntuación
    char espacios2[50] = "";

    CreateString(espacios1, 0, nEspacios - longitud1, ' '); 
    CreateString(espacios2, 0, nEspacios - longitud2, ' ');
    printf("\n+---+---+---+---+  JUEGO DEL CONCENTRESE          SCORE\n");
    printf("| %c | %c | %c | %c |  Nombre jugador 01: %s%s%i\n", table[0], table[1], table[2], table[3], player1, espacios1, score1);
    printf("+---+---+---+---+  Nombre jugador 02: %s%s%i\n", player2, espacios2, score2);
    printf("| %c | %c | %c | %c |\n", table[4], table[5], table[6], table[7]);
    printf("+---+---+---+---+  Juega: %s\n", player);
    printf("| %c |%c%c |%c%c |%c%c |  Status: %s\n", table[8], table[9], table[10], table[11], table[12], table[13], table[14], status);
    printf("+---+---+---+---+\n");
    printf("|%c%c |%c%c |%c%c |%c%c |\n", table[15], table[16], table[17], table[18], table[19], table[20], table[21], table[22]);
    printf("+---+---+---+---+\n");
}

int main() {
    //Limpiamos la consola antes de empezar el juego
    system("cls");
    srand(time(NULL));
    //cadena que será usado para generar el juego aleatorio
    char cadena[] = "aaaaaaaaaaaaaaaa";  
    //game que será usado para guardar el juego aleatorio
    char* game = GenerateCadena(cadena, 0, 0, 'A');
    //player1 que guardará el nombre del jugador 1
    char player1[50] = "";
    //player2 que guardará el nombre del jugador 2
    char player2[50] = "";
    //initialTable que guarda el juego antes del turno de algun jugador
    char initialTable[] = "12345678910111213141516";
    //auxiliarTable que guarda el juego durante el turno de algun jugador
    char auxiliarTable[] = "12345678910111213141516";
    //variable turn que guarda el turno del jugador
    int turn = 1;
    //variable counter para saber cuantas elecciones ha hecho un jugador
    int counter = 1;
    //score1 que guarda la puntuación de player1
    int score1 = 0;
    //score2 que guarda la puntuación de player2
    int score2 = 0;
    //respuesta que guarda la elección del jugador
    int respuesta = 0;
    //auxiliarRespuesta que guarda la elección del jugador y ser usada para la posición de la cadena aleatoria
    int auxiliarRespuesta = 0;
    //previousAnswer que guarda la elección anterior del jugador
    int previousAnswer = 0;

    printf("\nEntre el nombre del jugador 1: ");
    scanf("%49s", player1); 
    
    printf("\nEntre el nombre del jugador 2: ");
    scanf("%49s", player2);

    //answer que guardará si el juego desea ser continuado o no
    char answer = 's';

    //imprime el juego inicial
    PrintTable(initialTable, player1, player2, player1, score1, score2, "");
    
    while(score1+score2 != 8){
        printf("\nEntre número casilla 0%i: ", turn);
        scanf("%i", &respuesta);
        respuesta --;
        auxiliarRespuesta = respuesta;
        if(respuesta > 15 || respuesta < 0){
            printf("\nCasila inválida");
        }else{
            if(respuesta > 8){
                respuesta = (respuesta-8)*2 + 8;
            }
            if(!isdigit(auxiliarTable[respuesta])){
                printf("\nError casilla ya jugada");
            }else{
                if(auxiliarRespuesta > 8){
                    auxiliarTable[respuesta] = game[auxiliarRespuesta];
                    auxiliarTable[respuesta-1] = ' ';
                }else{
                    auxiliarTable[respuesta] = game[auxiliarRespuesta];
                }
                if(counter % 2 == 0){
                    score1 = (auxiliarTable[respuesta] == auxiliarTable[previousAnswer] && turn == 1) ? score1+1 : score1;
                    score2 = (auxiliarTable[respuesta] == auxiliarTable[previousAnswer] && turn == 2) ? score2+1 : score2;
                    PrintTable(auxiliarTable, player1, player2, (turn == 1) ? player1 : player2, score1, score2, (auxiliarTable[respuesta] == auxiliarTable[previousAnswer]) ? "ADIVINO" : "PERDIO" );
                    turn = (auxiliarTable[respuesta] == auxiliarTable[previousAnswer]) ? turn : (turn == 1) ? 2 : 1;
                    if(auxiliarTable[respuesta] == auxiliarTable[previousAnswer]){
                        strcpy(initialTable, auxiliarTable);
                    }
                    if(score1+score2 != 8){
                    strcpy(auxiliarTable, initialTable);
                    counter = 1;
                    printf("Desea continuar(s/n): ");
                    scanf(" %c", &answer);
                    if (tolower(answer) != 's') {
                    break;
                   }
                   PrintTable(initialTable, player1, player2, (turn == 1) ? player1 : player2, score1, score2, "");
                   }
                }else{
                    PrintTable(auxiliarTable, player1, player2, (turn == 1) ? player1 : player2, score1, score2, "");
                    previousAnswer = respuesta;
                    counter++;
                }
            }
        }
    }
    if (tolower(answer) == 's') {
        if(score1 < score2){
            printf("\nJugador 2 ha ganado!");
        }else if(score1 > score2){
            printf("\nJugador 1 ha ganado!");
        }else{
            printf("\nEmpate");
        }
    }
    return 0;
}