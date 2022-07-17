#include "funciones.h"

 const char pauta[12] = {'A','E','C','B','B','D','A','B','E','C','B','D'};

FILE* AbrirArch(char* ruta_archivo, char* modo){
    FILE* archivo = NULL;
    if((archivo = fopen(ruta_archivo,modo)) == NULL){
        printf("\nError al abrir \'%s\' en modo %s.\n", ruta_archivo, (modo[0] == 'r') ? "lectura":"escritura");
        exit(EXIT_FAILURE);
    }
    else
        return archivo;
}

void EncabezadoSalida(FILE** archivo_salida){
    char *Encabezado_salida[6] = {
        "Identificador de estudiante",
        "Preguntas correctas",
        "Preguntas incorrectas",
        "Preguntas omitidas",
        "Puntaje",
        "Nota"
    };
    int iterador = 0;
    fprintf(*archivo_salida,"\"%s\"",Encabezado_salida[iterador]);
    for (iterador = 1; iterador < 6; iterador++){
        fprintf(*archivo_salida,";\"%s\"",Encabezado_salida[iterador]);
    }
}

void Calcular(resultado* result, char respuesta, char pauta){
    if(respuesta == pauta)
        result->correctas++;
    else{
        if(respuesta == '-')
            result->omitidas++;
        else
            result->incorrectas++;
    }
    result->puntaje = result->correctas*(0.5) + result->incorrectas*(-0.12);
    result->nota = 1 + result->puntaje;
}

void Registrar(resultado* result, FILE* archivo_salida){
    fprintf(archivo_salida,";\"%d\"",result->correctas); result->correctas = 0;
    fprintf(archivo_salida,";\"%d\"",result->incorrectas); result->incorrectas = 0;
    fprintf(archivo_salida,";\"%d\"",result->omitidas); result->omitidas = 0;
    fprintf(archivo_salida,";\"%.1lf\"",result->puntaje); result->puntaje = 0.0;
    fprintf(archivo_salida,";\"%.1lf\"",result->nota); result->nota = 0.0;
}

void Finalizar(){
    printf("FINALIZADO!\n");
    printf("Integrantes\n - Allan Morales\n - Oscar Muñoz\n");
}