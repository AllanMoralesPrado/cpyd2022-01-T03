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

void Contabilizar(resultado* result, char respuesta, int area, char pauta){
    if(area == 0){
        if(respuesta == pauta)
            result->preguntas_m[0]++;
        else{
            if(respuesta == '-')
                result->preguntas_m[1]++;
            else
                result->preguntas_m[2]++;
        }
    } else if(area == 1){
                if(respuesta == pauta)
                    result->preguntas_c[0]++;
                else{
                    if(respuesta == '-')
                        result->preguntas_c[1]++;
                    else
                        result->preguntas_c[2]++;
                }      
            } else if(area == 2){
                if(respuesta == pauta)
                    result->preguntas_h[0]++;
                else{
                    if(respuesta == '-')
                        result->preguntas_h[1]++;
                    else
                        result->preguntas_h[2]++;
                }
            }
}

void Calcular(resultado* result){
    int correctas = result->preguntas_m[0] + result->preguntas_c[0] + result->preguntas_h[0];
    int incorrectas = result->preguntas_m[2] + result->preguntas_c[2] + result->preguntas_h[2];
    result->puntaje_m = 0.5*correctas-0.12*(result->preguntas_m[2]);
    result->puntaje_c = 0.5*correctas-0.12*(result->preguntas_c[2]);;
    result->puntaje_h = 0.5*correctas-0.12*(result->preguntas_h[2]);;
    result->puntaje = 0.5*correctas-0.12*incorrectas;
}

void CrearRegistro(resultado result, seleccion* mat, seleccion* cien, seleccion* hum){
    // puntaje segun el area de interes
    mat->puntaje_area = result.puntaje_m;
    cien->puntaje_area = result.puntaje_c;
    hum->puntaje_area = result.puntaje_h;
    
    // puntaje general (aplica en todas las areas)
    mat->puntaje = cien->puntaje = hum->puntaje = result.puntaje;
}

void HeapSortInsert(seleccion area[], seleccion buffer, int pos_del, int pos_tra, int med, int tam){
    
    if(pos_tra == -1){
        area[++pos_tra] = buffer;
    }
    
    double mediana = area[med].puntaje_area;

    if(buffer.puntaje_area > mediana){
        HeapSortInsert(area,buffer,pos_del,med,((med+1)%2 == 0) ? (med/2)+1:med/2,tam);
    }
    else{
        HeapSortInsert(area,buffer,med,(tam+med)/2,pos_tra,tam);
    }

    int iterador;
    for(iterador = (tam == MAX_CUPOS) ? MAX_CUPOS-1:tam-1; iterador > pos_tra; iterador--){
        area[iterador] = area[iterador-1];
    }
    
    area[pos_tra] = buffer;
}

void Registrar(seleccion area, FILE* archivo_salida){
    fprintf(archivo_salida,"\"%s\"",area.uuid);
    fprintf(archivo_salida,";\"%.1lf\"",area.puntaje_area);
    fprintf(archivo_salida,";\"%.1lf\"",area.puntaje);
}

void Finalizar(){
    printf("FINALIZADO!\n");
    printf("Integrantes\n - Allan Morales\n - Oscar Muñoz\n");
}