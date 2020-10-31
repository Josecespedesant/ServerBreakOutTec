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

/**
 * Función que establece el score de una fila
 * Entradas: matriz, fila y cantidad de puntos
 **/
void set_score(arr2d_t (*matr), int i, int puntos);

/**
 * Función que envia la fila con el puntaje
 * Entradas: fila y cantidad de puntos
 **/
void *client1(int  i, int puntaje);

/**
 * Función que envia la fila, la columna y el poder del bloque
 * Entradas: fila, columna y poder
 **/
void *client(int  i, int j, int power);

/**
 * Función que establece el bloque como roto
 * Entradas: fila y columna
 **/
void set_broken(int i, int j);

/**
 * Función que envia al cliente expectador la fila y col del bloque destruido
 * Entradas: fila y columna
 **/
void *clientExp(int i, int j);

/**
 * Función que imprime la matriz
 * Entrada: Matriz de ladrillos.
 * No devuelve nada, imprime la matriz. 
 **/
void mx_fprint(arr2d_t mtrx);

/**
 * Menú del administrador
 **/
void *adminMenu();

/**
 * Servidor que recibe los bloques destruidos
 **/
void *server();

/**
 * Función que devuelve un ladrillo en específico del grid.
 * Entradas: Matriz, fila y columna.
 * Salida: Ladrillo en dada fila y columna.
 **/
ladrillo_t get_ladri(arr2d_t matr, int i, int j);

/**
 * Establece el poder de un bloque
 * Entradas: matriz, fila, columna y poder
 **/
void set_power(arr2d_t (*matr), int i, int j, int power);

#endif