#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void Game(int turn,char stringTable[], char initialTable[], char actualTable[], char player1[], char player2[], int score1, int score2, int selection, int counter);

char* CreateString(char cadena[], int counter, int number, char letter) {
    if (counter < number) {
        cadena[counter] = letter;
        return CreateString(cadena, counter + 1, number, letter);
    } else {
        cadena[counter] = '\0'; 
        return cadena;
    }
}

int EndGame(const char* str, int pos) {
    if (pos == 64) {
        return 1;  
    }
    if (isdigit(str[pos])) {
        return 0; 
    }
    return EndGame(str, pos + 1);
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

int Desicion(char option) {
    if (option == 's' || option == 'S') {
        return 1; 
    } else {
        return 0;
    }
}

void ChangeChar(char str[], int pos, char newChar) {
    int length = strlen(str); 

    if (pos < length) {
        if (pos < 39) {
            str[pos] = newChar;
        } else {
            str[pos - 1] = ' ';
            str[pos] = newChar;
        }
    }
}

void PrintTable(char table[], char player1[], char player2[], char player[], char winner1[], char winner2[], char status[]) {
    int longitud1 = strlen(player1);
    int longitud2 = strlen(player2);
    int nEspacios = 12;
    char espacios1[50];
    char espacios2[50];
    CreateString(espacios1, 0, nEspacios - longitud1, ' ');
    CreateString(espacios2, 0, nEspacios - longitud2, ' ');

    printf("\n+---+---+---+---+  JUEGO DEL CONCENTRESE        SCORE");
    printf("%.16s |  Nombre jugador 01: %s%s0\n", table, player1, espacios1);
    
}


void CheckMove(char* actualTable, char* newTable, int position, int selection1, int turn, char* player1, char* player2, int score1, int score2, int counter) {
    if (isdigit(actualTable[position])) {
        if (newTable[position] == newTable[selection1]) {
            PrintTable(newTable, player1, player2, (turn == 1) ? player1 : player2, 
                       (turn == 1) ? "1" : "0", (turn == 2) ? "1" : "0", 
                       (score1 + score2 == 7) ? ((turn == 1 && score2 == 4) || (turn == 2 && score1 == 4)) ? 
                       "Fin del juego empatados" : "Has Ganado!" : "Adivinó");
            if (EndGame(newTable, 0)) {
                return;
            } else {
                Game(turn, newTable, newTable, actualTable, player1, player2, 
                     (turn == 1) ? score1 + 1 : score1, (turn == 2) ? score2 + 1 : score2, 0, 1);
            }
        } else {
            if (counter == 2) {
                PrintTable(newTable, player1, player2, (turn == 1) ? player1 : player2, "0", "0", "Perdió");
                printf("Desea continuar (s/n): ");
                char option;
                scanf(" %c", &option);
                if (Desicion(option)) {
                    PrintTable(newTable, player1, player2, (turn == 1) ? player1 : player2, "0", "0", " ");
                    Game(turn == 1 ? 2 : 1, newTable, newTable, actualTable, player1, player2, score1, score2, 0, 1);
                }
            } else {
                PrintTable(newTable, player1, player2, (turn == 1) ? player1 : player2, "0", "0", " ");
                Game(turn, newTable, newTable, actualTable, player1, player2, score1, score2, position, counter + 1);
            }
        }
    } else {
        if (EndGame(actualTable, 0)) {
            return;
        } else {
            printf("Error, casilla ya jugada\n");
            PrintTable(newTable, player1, player2, (turn == 1) ? player1 : player2, "0", "0", " ");
            Game(turn, newTable, newTable, actualTable, player1, player2, score1, score2, selection1, counter);
        }
    }
}


void Game(int turn, char stringTable[], char initialTable[], char actualTable[], char player1[], char player2[], int score1, int score2, int selection, int counter) {
    char newTable[100];
    int position = 0;
    printf("Entre número casilla 0%i: ", turn);
    scanf("%i", &position);
    position = (position * 4) - 1;
    strcpy(newTable, actualTable);
    if (isdigit(actualTable[position])) {
        int newCharIndex = (position + 1) / 4 - 1; 
        char newChar = stringTable[newCharIndex];
        ChangeChar(newTable, position, newChar);
    }
    CheckMove(actualTable, newTable, position, selection, turn, player1, player2, score1, score2, counter);
}


int main() {
    srand(time(NULL));

    char cadena[] = "aaaaaaaaaaaaaaaa";  
    char* game = GenerateCadena(cadena, 0, 0, 'A');
    char player1[50];
    char player2[50];
    char initialTable[] = "\n| 1 | 2 | 3 | 4\n| 5 | 6 | 7 | 8\n| 9 |10 |11 |12\n|13 |14 |15 |16 ";
    printf("\nEntre el nombre del jugador 1: ");
    scanf("%49s", player1); 
    
    printf("\nEntre el nombre del jugador 2: ");
    scanf("%49s", player2);
    
    int longitud1 = strlen(player1);
    int longitud2 = strlen(player2);
    int nEspacios = 12; 
    
    char espacios1[50]; 
    char espacios2[50]; 
    CreateString(espacios1, 0, nEspacios - longitud1, ' ');
    CreateString(espacios2, 0, nEspacios - longitud2, ' ');

    printf("\n%s\n", game);
    printf("+---+---+---+---+  JUEGO DEL CONCENTRESE        SCORE\n| 1 | 2 | 3 | 4 |  Nombre jugador 01: %s%s0\n+---+---+---+---+  Nombre jugador 02: %s%s0\n", player1, espacios1, player2, espacios2);
    printf("| 5 | 6 | 7 | 8 |\n+---+---+---+---+  Juega: %s\n| 9 |10 |11 |12 |  Status:\n+---+---+---+---+\n|13 |14 |15 |16 |\n+---+---+---+---+\n", player1);
    
    Game(1, game, initialTable, initialTable, player1, player2, 0, 0, 0, 1);
    return 0;
}
