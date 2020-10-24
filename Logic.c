#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include <time.h>

#ifndef OUT_OF_MEMORY
#define OUT_OF_MEMORY
#endif

arr2d_t mx_new()
{
    arr2d_t mtrx; //Define una matriz de ladrillos
    srand(time(0)); //Necesario para números random
    for(int x = 0; x<ROWS; x++){
        for(int y = 0; y<COLS; y++){
            if(x<2){
                //Filas rojas
                mtrx.ladrillos[x][y].puntaje = 40; //Asigna puntaje
                mtrx.ladrillos[x][y].powerUp = 0; //Inicializa el power up
                mtrx.ladrillos[x][y].isBreak = 0; //0 Si está sin romper, 1 si está roto
            }
            else if(x >= 2 && x < 4){
                //Filas anaranjadas
                mtrx.ladrillos[x][y].puntaje = 30; //Asigna puntaje
                mtrx.ladrillos[x][y].powerUp = 0; //Inicializa el power up
                mtrx.ladrillos[x][y].isBreak = 0; //0 Si está sin romper, 1 si está roto
            }
            else if(x >= 4 && x < 6){
                //Filas amarillas
                mtrx.ladrillos[x][y].puntaje = 20; //Asigna puntaje
                mtrx.ladrillos[x][y].powerUp = 0; //Inicializar el power up
                mtrx.ladrillos[x][y].isBreak = 0; //0 Si está sin romper, 1 si está roto
            }
            else if(x >= 6 && x < 8){
                //Filas verdes
                mtrx.ladrillos[x][y].puntaje = 10; //Asigna puntaje
                mtrx.ladrillos[x][y].powerUp = 0; //Inicializa el power up
                mtrx.ladrillos[x][y].isBreak = 0; //0 Si está sin romper, 1 si está roto
            }
        }
    }
    //Devuelve matriz de ladrillos
    return mtrx;
}

void mx_fprint(arr2d_t mtrx){
    for (size_t i = 0; i < ROWS; i++){
        for (size_t j = 0; j < COLS; j++){
            printf("%d", mtrx.ladrillos[i][j].powerUp); //Imprime los estados alterados de los ladrillos
        }
    printf("\n");
    }
}

void adminMenu(){
    arr2d_t m = mx_new();
    pm = &m;
    int selection;                
    int r;
    int c;
    while(1){
        printf("================================");
        printf("====BIENVENIDO=ADMINISTRADOR====");
        printf("================================");
        printf("\n1. Dar una vida más al jugador \n2. Desplegar un nuevo balón en pantalla \n3. Duplicar el tamaño de la raqueta \n4. Reducir el tamaño de la raqueta por la mitad \n5. Aumentar la velocidad de la bola \n6. Disminuir la velocidad de la bola\n");
        printf("Elige una opción: ");
        scanf("%d", &selection);

        switch(selection){
            case 1:
                printf("\nIngrese la fila: ");
                scanf("%d", &r);
                printf("\nIngrese la columna: ");
                scanf("%d", &c);

                if(get_ladri(*pm, r, c).isBreak == 0){
                     set_power(pm,r,c,1);
                     break;   
                }
                printf("El ladrillo se encuentra destruido");
                break;
            case 2:
                printf("\nIngrese la fila: ");
                scanf("%d", &r);
                printf("\nIngrese la columna: ");
                scanf("%d", &c);
                if(get_ladri(*pm, r, c).isBreak == 0){
                     set_power(pm,r,c,2);
                     break;   
                }
                printf("\nEl ladrillo se encuentra destruido");
                break;
            case 3:
                printf("\nIngrese la fila: ");
                scanf("%d", &r);
                printf("\nIngrese la columna: ");
                scanf("%d", &c);
                if(get_ladri(*pm, r, c).isBreak == 0){
                     set_power(pm,r,c,3);
                     break;   
                }
                printf("\nEl ladrillo se encuentra destruido");
                break;
            case 4:
                printf("\nIngrese la fila: ");
                scanf("%d", &r);
                printf("\nIngrese la columna: ");
                scanf("%d", &c);
                if(get_ladri(*pm, r, c).isBreak == 0){
                     set_power(pm,r,c,4);
                     break;   
                }
                printf("\nEl ladrillo se encuentra destruido");
                break;
            case 5:
                printf("\nIngrese la fila: ");
                scanf("%d", &r);
                printf("\nIngrese la columna: ");
                scanf("%d", &c);
                if(get_ladri(*pm, r, c).isBreak == 0){
                     set_power(pm,r,c,5);
                     break;   
                }
                printf("\nEl ladrillo se encuentra destruido");
                break;
            case 6:
                printf("\nIngrese la fila: ");
                scanf("%d", &r);
                printf("\nIngrese la columna: ");
                scanf("%d", &c);
                if(get_ladri(*pm, r, c).isBreak == 0){
                     set_power(pm,r,c,6);
                     break;   
                }
                printf("\nEl ladrillo se encuentra destruido");
                break;
            default: 
                scanf("%*s");
                printf("Input inválido\n");
                break;
        }        

    }
}

ladrillo_t get_ladri(arr2d_t matr, int i, int j){
    return matr.ladrillos[i][j];
}

void set_power(arr2d_t (*matr), int i, int j, int power){
    matr->ladrillos[i][j].powerUp = power;
    mx_fprint(*matr);
}

int main (int argc, char *argv[]) {
    //arr2d_t m = mx_new();
    //mx_fprint(m);
    adminMenu();
    return 0;
}