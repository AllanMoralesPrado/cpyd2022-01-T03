/*
 * Taller 01 de Computación Paralela y Distribuida
 * Primer Semestre de 2022
 * Integrantes: Allan Morales / Oscar Muñoz / Germán Ramirez
 * 
 * Programa: Resultados PAU por categorias - Secuencial
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "funciones.h"

int main(){

    /* Puntero a archivo de entrada */
    //int argc, char** argv
    //FILE* archivo_entrada = AbrirArch(argv[1], "rt");
    FILE* archivo_entrada = AbrirArch("../../pruebas.csv", "rt");
    /* Puntero a archivos de salida */
    FILE* archivo_salida_m = AbrirArch("matematicas.csv", "wt");
    FILE* archivo_salida_c = AbrirArch("ciencias.csv", "wt");
    FILE* archivo_salida_h = AbrirArch("humanidades.csv", "wt");
    /*
    struct stat sb;
    if (stat(argv[1], &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }*/

    struct stat sb;
    if (stat("../../pruebas.csv", &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    /* Procesar archivo entrada y archivos de salida*/

    // Buffer
    char* registro = (char*)malloc(sb.st_size);
    
    // Encabezado para la salida
    EncabezadoSalida(&archivo_salida_m);
    EncabezadoSalida(&archivo_salida_c);
    EncabezadoSalida(&archivo_salida_h);

    // Proceso de contabilización de preguntas y registro de resultados
    int iterador = 0;
    resultado resultado_ = {
        {0,0,0},    //preguntas_m
        {0,0,0},    //preguntas_c
        {0,0,0},    //preguntas_h
        0.0,        //puntaje_m
        0.0,        //puntaje_c
        0.0,        //puntaje_h
        0.0         //puntaje
    };

    const char delimitador[2] = ";";
    char* token;

    int registrados = 0;
    seleccion top_matematicas[MAX_CUPOS];
    seleccion top_ciencias[MAX_CUPOS];
    seleccion top_humanidades[MAX_CUPOS];

    seleccion buffer_mat, buffer_cien, buffer_hum;

    // Ignorar el encabezado del archivo de entrada (alternativa: fseek)
    fscanf(archivo_entrada, "%[^\n] ", registro);

    while (fscanf(archivo_entrada, "%[^\n] ", registro) != EOF) {
        char* cpy_registro = (char*)malloc((strlen(registro)+1)*sizeof(char));
        strcpy(cpy_registro,registro);

        // leer UUID
        token = strtok(cpy_registro, delimitador);
        
        // registrar UUID
        strcpy(buffer_mat.uuid,token);
        strcpy(buffer_cien.uuid,token);
        strcpy(buffer_hum.uuid,token);

        // El resto de las columnas
        token = strtok(NULL, delimitador);
        while( token != NULL ) {
            //Calificacion de respuestas
            if(iterador >= 0 || iterador < 4){
                Contabilizar(&resultado_, token[1], 0, pauta[iterador++]);
            } else {
                if(iterador >= 4 || iterador < 8){
                    Contabilizar(&resultado_, token[1], 1, pauta[iterador++]);
                } else {
                    Contabilizar(&resultado_, token[1], 2, pauta[iterador++]);
                }
            }
            token = strtok(NULL, delimitador);
        }
        //Calcular puntajes por area y general
        Calcular(&resultado_);

        //Filtrar puntajes por area de aprendizaje
        CrearRegistro(resultado_, &buffer_mat, &buffer_cien, &buffer_hum);

        //Insertar mediante HEAPSORT cada resultado del estudiante a las respectivas areas
        HeapSortInsert(top_matematicas, buffer_mat, 0, registrados-1, (registrados-1)/2, registrados);
        HeapSortInsert(top_ciencias, buffer_cien, 0, registrados-1, (registrados-1)/2, registrados);
        HeapSortInsert(top_humanidades, buffer_hum, 0, registrados-1, (registrados-1)/2, registrados);
        registrados++;
        
        //Reiniciar iterador de preguntas
        iterador = 0;
    }

    int linea;
    for(linea = 0; linea < MAX_CUPOS; linea++){
        Registrar(top_matematicas[linea], archivo_salida_m);
        Registrar(top_ciencias[linea], archivo_salida_c);
        Registrar(top_humanidades[linea], archivo_salida_h);
    }

    fclose(archivo_entrada);
    fclose(archivo_salida_m);
    fclose(archivo_salida_c);
    fclose(archivo_salida_h);
    
    Finalizar();

    return EXIT_SUCCESS;
}