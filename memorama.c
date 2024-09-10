#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* CreateString(char cadena[], int counter, int number){
    if(counter < number){
        cadena[counter]= ' ';
        
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

void Game(int turn, char game[]) {
    int num = 0;
    printf("Escoja la casilla: ");
    scanf("%i", &num);
}

int main() {
    srand(time(NULL));

    char cadena[] = "aaaaaaaaaaaaaaaa";  
    char* game = GenerateCadena(cadena, 0, 0, 'A');
    char player1[] = "";
    char player2[] = "";
    printf("\nEntre el nombre del jugador 1: ");
    scanf("%s", player1);
    printf("\nEntre el nombre del jugador 2: ");
    scanf("%s", player2);
    int longitud1 = strlen(player1);
    int longitud2 = strlen(player2);
    int espacios = strlen("                     ");
    printf("\n%s\n", game);
    printf("+---+---+---+---+  JUEGO DEL CONCENTRESE        SCORE\n| 1 | 2 | 3 | 4 |  JUGADOR 1:                     0\n+---+---+---+---+  JUGADOR 2:                     0\n");
    printf("| 5 | 6 | 7 | 8 |\n+---+---+---+---+\n| 9 | 10| 11| 12|\n+---+---+---+---+\n| 13| 14| 15| 16|\n+---+---+---+---+\n");
    //Game(1, game);
    
    return 0;
}
