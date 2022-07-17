/**
 * File: db.h
 * Archivo de funciones para interactuar con el motor de base de datos.
 */
#ifndef DB_H
#define DB_H

#ifdef __cplusplus
extern "C" {
#endif

#define BUFF_SIZE 256
#define PREGUNTAS 12

struct cont_resp_s{
    int correctas;
    int incorrectas;
    int omitidas;
    double puntaje;
    double nota;
};
typedef struct cont_resp_s conteo;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <omp.h>

/* Prototipos de funciones */

/**
* Verifica que la cantidad de argumentos ingresados por consola permita la ejecición de la app.
*
* @param argc contador de argumentos ingresados por consola
*/
void ValidarArgumentos(int argc);
/**
* Abre los archivos de pruebas y de resultados para procesarlos en modo lectura y escritura respectivamente
*
* @param arch_e Puntero a archivo (por referencia) de entrada en modo lectura ASCII
* @param ruta_e Ruta del archivo de entrada con las pruebas
* @param arch_s Puntero a archivo (por referencia) de salida en modo escritura ASCII
* @param ruta_s Ruta del archivo de salida con los resultados
*/
void AbrirArchivos(FILE** arch_e, char* ruta_e, FILE** arch_s, char* ruta_s);
/**
* Lee el archivo con las pruebas para registrar los resultados en el archivo de resultados
*
* @param arch_e Puntero a archivo (por valor) de entrada en modo lectura ASCII
* @param arch_s Puntero a archivo (por valor) de salida en modo escritura ASCII
*/
void LlenarSalida(FILE* arch_e, FILE* arch_s);
/**
* Procesamiento paralelo donde cada hilo convierte el registro de una prueba en un registro de resultado
* En el mismo contenedor
*
* @param iterador Cantidad de registros de prueba (tamaño del chunk)
* @param iregistro Chunk con registros de pruebas
*/
void LlenarChunk(size_t iterador, char** iregistro);
/**
 * Retorna un registro (string) de resultado de un registro de prueba
 *
 * @param registro texto que corresponde al registro de una prueba
 * @return texto que corresponde al registro del resultado de una prueba
 */
char* Evaluar(char* registro);
/**
* Muestra por la terminal la lista con los nombres y apellidos de los autores de esta app
* 
*/
void Integrantes();

#ifdef __cplusplus
}
#endif

#endif /* DB_H */