/*
 * Taller 01 de Computación Paralela y Distribuida
 * Primer Semestre de 2022
 * Integrantes: Allan Morales / Oscar Muñoz / Germán Ramirez
 * 
 * Programa: Resultados PAU - Secuencial
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "funciones.h"

int main(int argc, char** argv){

    /* Puntero a archivos */
    FILE* archivo_entrada = AbrirArch(argv[1], "rt");
    FILE* archivo_salida = AbrirArch(argv[2], "wt");
    
    struct stat sb;
    if (stat(argv[1], &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    /* Procesar archivo entrada y archivo de salida*/

    // Buffer
    char* registro = (char*)malloc(sb.st_size);
    
    // Encabezado para la salida
    EncabezadoSalida(&archivo_salida);

    // Proceso de contabilización de preguntas y registro de resultados
    int iterador = 0;
    resultado resultado_ = {0,0,0,0.0,0.0};
    const char delimitador[2] = ";";
    char* token;

    // Ignorar el encabezado del archivo de entrada (alternativa: fseek)
    fscanf(archivo_entrada, "%[^\n] ", registro);

    while (fscanf(archivo_entrada, "%[^\n] ", registro) != EOF) {
        char* cpy_registro = (char*)malloc((strlen(registro)+1)*sizeof(char));
        strcpy(cpy_registro,registro);

        //UUID
        token = strtok(cpy_registro, delimitador);
        fprintf(archivo_salida,"\n%s",token);

        //El resto de las columnas
        token = strtok(NULL, delimitador);
        while( token != NULL ) {
            //Clasificacion de respuestas
            Calcular(&resultado_, token[1], pauta[iterador++]);
            token = strtok(NULL, delimitador);
        }
        //Registro en archivo de salida
        Registrar(&resultado_,archivo_salida);
        iterador = 0;
    }

    fclose(archivo_entrada);
    fclose(archivo_salida);

    Finalizar();

    return EXIT_SUCCESS;
}