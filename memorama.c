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

char* CreateString(char cadena[], int counter, int number, char letter) {
    if (counter < number) {
        cadena[counter] = letter;
        return CreateString(cadena, counter + 1, number, letter);
    } else {
        cadena[counter] = '\0'; 
        return cadena;
    }
}


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


void ChangeChar(char str[], int pos, char newChar) {
    if (pos < 9) {
        str[pos] = newChar;
    } else {
        int index = (pos - 9) * 2 + 9;
        str[index] = ' ';
        str[index + 1] = newChar;
    }
}


void PrintTable(char table[], char player1[], char player2[], char player[], int score1, int score2, char status[]) {
    int longitud1 = strlen(player1);
    int longitud2 = strlen(player2);
    int nEspacios = 12;
    char espacios1[50];
    char espacios2[50];

    CreateString(espacios1, 0, nEspacios - longitud1, ' '); 
    CreateString(espacios2, 0, nEspacios - longitud2, ' ');
    printf("\n+---+---+---+---+  JUEGO DEL CONCENTRESE        SCORE\n");
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
    system("cls");
    srand(time(NULL));
    char cadena[] = "aaaaaaaaaaaaaaaa";  
    char* game = GenerateCadena(cadena, 0, 0, 'A');
    char player1[50];
    char player2[50];
    char initialTable[] = "12345678910111213141516";
    char auxiliarTable[] = "12345678910111213141516";
    int turn = 1;
    int counter = 1;
    int score1 = 0;
    int score2 = 0;
    int respuesta = 0;
    int auxiliarRespuesta = 0;
    int respuestaAnterior = 0;

    printf("\nEntre el nombre del jugador 1: ");
    scanf("%49s", player1); 
    
    printf("\nEntre el nombre del jugador 2: ");
    scanf("%49s", player2);
    
    int longitud1 = strlen(player1);
    int longitud2 = strlen(player2);
    int nEspacios = 16; 
    char answer = 's';
    char espacios1[50]; 
    char espacios2[50]; 
    CreateString(espacios1, 0, nEspacios - longitud1, ' ');
    CreateString(espacios2, 0, nEspacios - longitud2, ' ');

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
                    score1 = (auxiliarTable[respuesta] == auxiliarTable[respuestaAnterior] && turn == 1) ? score1+1 : score1;
                    score2 = (auxiliarTable[respuesta] == auxiliarTable[respuestaAnterior] && turn == 2) ? score2+1 : score2;
                    PrintTable(auxiliarTable, player1, player2, (turn == 1) ? player1 : player2, score1, score2, (auxiliarTable[respuesta] == auxiliarTable[respuestaAnterior]) ? "ADIVINO" : "PERDIO" );
                    turn = (auxiliarTable[respuesta] == auxiliarTable[respuestaAnterior]) ? turn : (turn == 1) ? 2 : 1;
                    if(auxiliarTable[respuesta] == auxiliarTable[respuestaAnterior]){
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
                    respuestaAnterior = respuesta;
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