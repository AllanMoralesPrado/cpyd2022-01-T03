/**
 * File: funciones.h
 * Archivo de funciones para leer las respuestas, corregirlas y escribir los resultados
 */
#ifndef FUNCIONES_H
#define FUNCIONES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Solucionario
extern const char pauta[12];
// Contador de respuestas
struct resultado_s{
    int correctas;
    int incorrectas;
    int omitidas;
    double puntaje;
    double nota;
};
typedef struct resultado_s resultado;

/* Prototipos de funcion */

// Abrir archivos de entrada y salida
/**
 * @param ruta_archivo Puntero a cadena de texto con la ruta(relativa o absoluta del archivo).
 * @param modo De apertura del archivo en formato texto: lectura ("rt") o creación/sobreescritura ("wt").
 * @return Un puntero a un archivo (si este existe) o fin de ejecución. 
*/
FILE* AbrirArch(char* ruta_archivo, char* modo);

/**
 * Función que inserta el encabezado en el archivo de salida
 * @param archivo_salida Referencia al puntero al archivo de salida.
*/
void EncabezadoSalida(FILE** archivo_salida);

// Calcular resultados
/**
 * Función que contabiliza el tipo de respuesta y calcula puntaje y nota de la prueba 
 * @param result Referencia a la estructura resultado, que posee la calificación de una prueba 
 * @param respuesta Caracter con la alternativa que responde a una pregunta
 * @param pauta Caracter con la alternativa correcta
*/
void Calcular(resultado* result, char respuesta, char pauta);

// Calcular resultados
/**
 * Función para registrar la calificación de una prueba en el archivo de salida
 * @param archivo_salida Referencia al puntero al archivo de salida.
 * @param result Referencia a la estructura resultado, que posee la calificación de una prueba 
*/
void Registrar(resultado* result, FILE* archivo_salida);

/**
 * Función para finalizar la ejecución del programa 
*/
void Finalizar();

#ifdef __cplusplus
}
#endif

#endif /* FUNCIONES_H */