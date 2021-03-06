#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#ifndef OUT_OF_MEMORY
#define OUT_OF_MEMORY
#endif

char mensaje[1024];
bool conexion = true;

arr2d_t mx_new()
{
    arr2d_t mtrx; //Define una matriz de ladrillos
    srand(time(0)); //Necesario para números random
    for(int x = 0; x<ROWS; x++){
        for(int y = 0; y<COLS; y++){
            if(x<2){
                //Filas rojas
                mtrx.ladrillos[x][y].powerUp = 0; //Inicializa el power up
                mtrx.ladrillos[x][y].isBreak = 0; //0 Si está sin romper, 1 si está roto
            }
            else if(x >= 2 && x < 4){
                //Filas anaranjadas
                mtrx.ladrillos[x][y].powerUp = 0; //Inicializa el power up
                mtrx.ladrillos[x][y].isBreak = 0; //0 Si está sin romper, 1 si está roto
            }
            else if(x >= 4 && x < 6){
                //Filas amarillas
                mtrx.ladrillos[x][y].powerUp = 0; //Inicializar el power up
                mtrx.ladrillos[x][y].isBreak = 0; //0 Si está sin romper, 1 si está roto
            }
            else if(x >= 6 && x < 8){
                //Filas verdes
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

void *server(){
    sleep(1);
    int conexion_servidor, conexion_cliente, puerto;
    socklen_t longc;
    struct sockaddr_in servidor, cliente;
    char buffer[100];

    puerto = 25558;
    conexion_servidor = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *)&servidor, sizeof(servidor));
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(puerto);
    servidor.sin_addr.s_addr = INADDR_ANY;

    if (bind(conexion_servidor, (struct sockaddr *) &servidor, sizeof(servidor)) < 0) {
        printf("Error al asociar el puerto a la conexion\n");
        close(conexion_servidor);
        return;
    }
    while (conexion) {
        sprintf(mensaje, "");
        listen(conexion_servidor, 3);
        printf("A la escucha en el puerto %d\n", ntohs(servidor.sin_port));
        longc = sizeof(cliente); //Asignamos el tamaño de la estructura a esta variable

        conexion_cliente = accept(conexion_servidor, (struct sockaddr *) &cliente, &longc);
        if (conexion_cliente < 0) {
            while (conexion_cliente < 0) {
                conexion_cliente = accept(conexion_servidor, (struct sockaddr *) &cliente, &longc);
            }
        }
        printf("Conectando con el cliente\n");


        if (recv(conexion_cliente, buffer, 100, 0) < 0) {
            //Si recv() recibe 0 el cliente ha cerrado la conexion. Si es menor que 0 ha habido algún error.
            printf("Error al recibir los datos\n");
            close(conexion_servidor);
            return;
        } else {
            printf("%s\n", buffer);

            char first[2];
            first[0] = buffer[0];

            int ro;
            
            ro = atoi(first);

            char substr[4];
            substr[0] = buffer[2];
            substr[1] = buffer[3];

            int col;

            col = atoi(substr);

            set_broken(ro, col);
            clientExp(ro, col);

            bzero((char *) &buffer, sizeof(buffer));

            if(conexion) {
                send(conexion_cliente, mensaje, 1024, 0);
            }
        }
        close(conexion_cliente);
    }
    close(conexion_servidor);
    return;
}

void *clientExp(int i, int j){

    char ich = i + '0';

    char jch[3];
    snprintf(jch, sizeof(jch), "%d", j); 

    int csiz = sizeof(jch)/sizeof(jch[0]);

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    char buff[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        printf("Socket creation failed...\n");
        exit(0);
    }
    else{
        printf("Socket succesfully created...\n");
        bzero(&servaddr, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(25556);

        if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))!=0){
            printf("connection with the server failed...\n");
            exit(0);
        }
        else{
            printf("connected\n");
            bzero(buff, sizeof(buff));
            buff[0] = ich;
            buff[1] = 'c';
            strcat(buff, jch);
            
            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
            close(sockfd);
        }
    }

}

void *client(int  i, int j, int power){

    char num = power + '0';
    char ich = i + '0';

    char jch[3];
    snprintf(jch, sizeof(jch), "%d", j); 

    int csiz = sizeof(jch)/sizeof(jch[0]);

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    char buff[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        printf("Socket creation failed...\n");
        exit(0);
    }
    else{
        printf("Socket succesfully created...\n");
        bzero(&servaddr, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(25557);

        if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))!=0){
            printf("connection with the server failed...\n");
            exit(0);
        }
        else{
            printf("connected\n");
            bzero(buff, sizeof(buff));
            buff[0] = '2';
            buff[1] = 'f';
            buff[2] = ich;
            buff[3] = 'c';
            strcat(buff, jch);
            if(csiz == 2){
                buff[5] = 'p';
                buff[6] = num;
            }
            if(csiz == 3){
                buff[6] = 'p';
                buff[7] = num;
            }
            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
            close(sockfd);
        }
    }
}

void *client1(int  i, int puntaje){
    char poinch[20];
    char ich = i + '0';
    snprintf(poinch, sizeof(poinch), "%d", puntaje); 

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    char buff[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        printf("Socket creation failed...\n");
        exit(0);
    }
    else{
        printf("Socket succesfully created...\n");
        bzero(&servaddr, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(25557);

        if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))!=0){
            printf("connection with the server failed...\n");
            exit(0);
        }
        else{
            printf("connected\n");
            bzero(buff, sizeof(buff));
            buff[0] = '1';
            buff[1] = 'f';
            buff[2] = ich;
            buff[3] = 'p';
            strcat(buff, poinch);


            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
            close(sockfd);
        }
    }
}

void *adminMenu(){
    sleep(1);
   
    int choice;
    int puntaje;
    int selection;                
    int r;
    int c;
    while(1){
        printf("\n================================");
        printf("====BIENVENIDO=ADMINISTRADOR====");
        printf("================================");
        printf("\n1. Agregar valor a una fila \n2. Agregar power up a un bloque \n");
        scanf("%d", &choice);
        switch(choice){
            case 1: printf("\nIngrese la fila: ");
                    scanf("%d", &r);
                    printf("\nIngrese el puntaje: ");
                    scanf("%d", &puntaje);
                    if(r<8 && r >= 0){
                        set_score(pm, r, puntaje);
                        client1(r, puntaje);
                        break;
                    }else{
                        printf("\nFila fuera de rango");
                        break;
                    }
            case 2: printf("\n1. Dar una vida más al jugador \n2. Desplegar un nuevo balón en pantalla \n3. Duplicar el tamaño de la raqueta \n4. Reducir el tamaño de la raqueta por la mitad \n5. Aumentar la velocidad de la bola \n6. Disminuir la velocidad de la bola\n");
                    printf("Elige una opción: ");
                    scanf("%d", &selection);

                    switch(selection){
                        case 1:
                            printf("\nIngrese la fila: ");
                            scanf("%d", &r);
                            printf("\nIngrese la columna: ");
                            scanf("%d", &c);
                            if(r<8 && r>=0 && c < 14 && c >= 0){
                                if(get_ladri(*pm, r, c).isBreak == 0){
                                set_power(pm,r,c,1);
                                client(r, c, 1);
                                break;   
                                }
                                printf("\nEl ladrillo se encuentra destruido");
                            }else{
                                printf("\nFila o columna fuera de rango");
                            }
                            break;
                        case 2:
                            printf("\nIngrese la fila: ");
                            scanf("%d", &r);
                            printf("\nIngrese la columna: ");
                            scanf("%d", &c);
                            if(r<8 && r>=0 && c < 14 && c >= 0){
                                if(get_ladri(*pm, r, c).isBreak == 0){
                                set_power(pm,r,c,2);
                                client(r, c, 2);
                                break;   
                                }
                                printf("\nEl ladrillo se encuentra destruido");
                            }else{
                                printf("\nFila o columna fuera de rango");
                            }
                            break;
                        case 3:
                            printf("\nIngrese la fila: ");
                            scanf("%d", &r);
                            printf("\nIngrese la columna: ");
                            scanf("%d", &c);
                            if(r<8 && r>=0 && c < 14 && c >=0){
                                if(get_ladri(*pm, r, c).isBreak == 0){
                                set_power(pm,r,c,3);
                                client(r, c, 3);
                                break;   
                                }
                                printf("\nEl ladrillo se encuentra destruido");
                            }else{
                                printf("\nFila o columna fuera de rango");
                            }
                            break;
                        case 4:
                            printf("\nIngrese la fila: ");
                            scanf("%d", &r);
                            printf("\nIngrese la columna: ");
                            scanf("%d", &c);
                            if(r<8 && r>=0 && c < 14 && c >=0){
                                if(get_ladri(*pm, r, c).isBreak == 0){
                                set_power(pm,r,c,4);
                                client(r, c, 4);
                                break;   
                                }
                                printf("\nEl ladrillo se encuentra destruido");
                            }else{
                                printf("\nFila o columna fuera de rango");
                            }
                            break;
                        case 5:
                            printf("\nIngrese la fila: ");
                            scanf("%d", &r);
                            printf("\nIngrese la columna: ");
                            scanf("%d", &c);
                            if(r<8 && r>=0 && c < 14 && c >=0){
                                if(get_ladri(*pm, r, c).isBreak == 0){
                                set_power(pm,r,c,5);
                                client(r, c, 5);
                                break;   
                                }
                                printf("\nEl ladrillo se encuentra destruido");
                            }else{
                                printf("\nFila o columna fuera de rango");
                            }
                            break;
                        case 6:
                            printf("\nIngrese la fila: ");
                            scanf("%d", &r);
                            printf("\nIngrese la columna: ");
                            scanf("%d", &c);
                            if(r<8 && r>=0 && c < 14 && c >=0){
                                if(get_ladri(*pm, r, c).isBreak == 0){
                                set_power(pm,r,c,6);
                                client(r, c, 6);
                                break;   
                                }
                                printf("\nEl ladrillo se encuentra destruido");
                            }else{
                                printf("\nFila o columna fuera de rango");
                            }
                            break;
                    }
        }

        
    }
}

ladrillo_t get_ladri(arr2d_t matr, int i, int j){
    return matr.ladrillos[i][j];
}

void set_score(arr2d_t (*matr), int i, int puntos){
    for(int j = 0; j<14; j++){
        matr->ladrillos[i][j].puntaje = puntos;
    }
}

void set_power(arr2d_t (*matr), int i, int j, int power){
    matr->ladrillos[i][j].powerUp = power;
    mx_fprint(*matr);
}

void set_broken(int i, int j){
    m.ladrillos[i][j].isBreak = 1;
}

int main (int argc, char *argv[]) {
    m = mx_new();
    pm = &m;
    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_2, NULL, adminMenu, NULL);
    pthread_create(&thread_1, NULL, server, NULL);
    
    pthread_join(thread_2, NULL); 
    pthread_join(thread_1, NULL);

    sleep(60); 
    return 0;
}