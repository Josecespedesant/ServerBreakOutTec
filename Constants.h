#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
/**
 * Constantes del programa, número de filas y columnas de la matriz.
 **/
#define ROWS 8
#define COLS 14

/**
 * Estructura que representa a un ladrillo del breakOutTec.
 * Tiene como miembros el color del ladrillo, su powerUp que corresponde al estado alterado que brinda al romperse
 * y un puntaje pre-establecido.
 **/
typedef struct ladrillo_t{
    int powerUp;
    int puntaje;
    int isBreak;
} ladrillo_t;

/**
 * Estructura que representa un array de dos dimensiones compuesto por ladrillos (matriz de ladrillos).
 * Tiene como miembro un array de dos dimensiones de ladrillos.
 **/
typedef struct arr2d{
    struct ladrillo_t ladrillos[ROWS][COLS];
}arr2d_t;

arr2d_t m;
arr2d_t *pm;


/**
 * Función que genera una nueva matriz 8x14 que corresponde al grid
 * del juego.
 * No tiene parámetros.
 * Salida: La matriz de tipo arr2d.
 **/
arr2d_t mx_new();

void set_score(arr2d_t (*matr), int i, int puntos);
void *client1(int  i, int puntaje);
void *client(int  i, int j, int power);

/**
 * Función que imprime la matriz.
 * Entrada: Matriz de ladrillos.
 * No devuelve nada, imprime la matriz. 
 **/
void mx_fprint(arr2d_t mtrx);

void *adminMenu();
void *server();

/**
 * Función que devuelve un ladrillo en específico del grid.
 * Entradas: Matriz, fila y columna.
 * Salida: Ladrillo en dada fila y columna.
 **/
ladrillo_t get_ladri(arr2d_t matr, int i, int j);

void set_power(arr2d_t (*matr), int i, int j, int power);

#endif