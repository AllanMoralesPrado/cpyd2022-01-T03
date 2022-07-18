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
#define MAX_CUPOS 1000000

// Solucionario
extern const char pauta[12];
/* Contador de respuestas
    int preguntas_<inicial_asignatura>[3] = {int correctas, int incorrectas, int omitidas}
*/ 
struct resultado_s{
    int preguntas_m[3];
    int preguntas_c[3];
    int preguntas_h[3];
    double puntaje_m;
    double puntaje_c;
    double puntaje_h;
    double puntaje;
};
typedef struct resultado_s resultado;

/* Estructura de selección en matemáticas */
struct seleccion_{
    char uuid[37];
    double puntaje_area;
    double puntaje;
};
typedef struct seleccion_ seleccion;

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

// Contabilizar resultados
/**
 * Función que contabiliza el tipo de respuesta y calcula puntaje y nota de la prueba 
 * @param result Referencia a la estructura resultado, que posee la calificación de una prueba 
 * @param respuesta Caracter con la alternativa que responde a una pregunta
 * @param area Numero indicador del area (asignatura) de la evaluacion (0: matematicas, 1: ciencias, 2: humanidades)
 * @param pauta Caracter con la alternativa correcta
*/
void Contabilizar(resultado* result, char respuesta, int area, char pauta);

// Calcular resultados
/**
 * Función que contabiliza el tipo de respuesta y calcula puntaje y nota de la prueba 
 * @param result Referencia a la estructura resultado, que posee la calificación de una prueba 
*/
void Calcular(resultado* result);

// CrearRegistro
/**
 * Función que filtra los datos necesarios de un resultado a un area determinada 
 * @param result Referencia a la estructura resultado, que posee la calificación de una prueba 
 * @param mat Registros con los resultados del area de matematicas
 * @param cien Registros con los resultados del area de ciencias
 * @param hum Registros con los resultados del area de humanidades
 */
void CrearRegistro(resultado result, seleccion* mat, seleccion* cien, seleccion* hum);

// insertar por HeapSort binario
/**
 * Función que inserta por orden de prioridad (puntaje area o puntaje general) los resultados en el TOP de cada area 
 * @param area HEAP de registros de seleccion del TOP 1000000 de un area especifica
 * @param buffer Registro que se va a intertar al Array 'area' si cumple las condiciones de prioridad
 * @param pos_del Indice de la posicion del registro ubicado en la cabeza del HEAP
 * @param pos_tra Indice de la posicion del registro ubicado en la cabeza del HEAP
 * @param med Indice de la posicion centra del HEAP
 * @param tam Elementos registrados en el HEAP. No confundir con capacidad del HEAP (MAX_CUPOS)
 * @param indice_area Indice el area evaluativa (0: matematica, 1: ciencias, 2: humanidades)
*/
void HeapSortInsert(seleccion area[], seleccion buffer, int pos_del, int pos_tra, int med, int tam);

// Registrar resultados
/**
 * Función para registrar la calificación de una prueba en el archivo de salida
 * @param area Array de registros de seleccion del TOP 1000000 de un area especifica
 * @param result archivo_salida Referencia al puntero al archivo de salida.
*/
void Registrar(seleccion area, FILE* archivo_salida);

/**
 * Función para finalizar la ejecución del programa 
*/
void Finalizar();

#ifdef __cplusplus
}
#endif

#endif /* FUNCIONES_H */