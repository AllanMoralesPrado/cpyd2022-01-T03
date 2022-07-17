/*
 * Taller 01 de Computación Paralela y Distribuida
 * Primer Semestre de 2022
 * Integrantes: Allan Morales / Oscar Muñoz / Germán Ramirez
 * 
 * Programa: Resultados PAU - Distribuido
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h> 

#define PARTICION 999
#define BUFFER 220;

struct contador_s{
    int correct;
    int incorrect;
    int omitid;
    double puntaje;
    double notas;
};
typedef struct contador_s cont;

/* Funcion para capturar en trozos los registros de las pruebas y enviarlos
 * a los procesos esclavo
 *
 * @param entrada puntero a archivo con las pruebas
 * @param registros doble puntero a caracter (por referencia) para definir y almacenar los trozos (chunk) capturados
 */
void LeerArchivo(File* entrada, char*** registros);

int main(int argc, char** argv) {
    int mi_rango; /* rango del proceso    */
    int p; /* numero de procesos   */
    int fuente; /* rango del que envia  */
    int dest; /* rango del que recibe */
    int tag = 0; /* etiqueta del mensaje */
    char mensaje[100]; /* mensaje  */
    MPI_Status estado; /* devuelve estado al recibir*/
    const char pauta[12] = {'A','E','C','B','B','D','A','B','E','C','B','D'};

    
    /*Verificación de argumentos*/
    if(argc < 3){
        puts("Se requieren 3 argumentos (aplicacion, archivo_entrada, archivo_salida) para ejecutar esta aplicacion");
        exit(EXIT_FAILURE);
    }

    /*Apertura de archivos*/
    FILE* archivo_entrada = NULL;
    FILE* archivo_salida = NULL;
    //Verificar si se pudo abrir el archivo de entrada
    if((archivo_entrada = fopen(argv[1],"rt")) == NULL){
        puts("No se pudo abrir el archivo de entrada");
        exit(EXIT_FAILURE);
    }

    //Verificar si se pudo abrir el archivo de salida
    if((archivo_salida = fopen(argv[2],"wt")) == NULL){
        puts("No se pudo abrir el archivo de salida");
        exit(EXIT_FAILURE);
    }
    
    /*Saltar el encabezado del archivo de entrada*/
    char* header = (char*)malloc(220*sizeof(char));
    fgets(header,220,archivo_entrada);
    free(header); header = NULL;

    /*Insertar encabezado en la salida*/
    char header_salida[] = "\"Identificador de estudiante\";"
                           "\"Preguntas correctas\";"
                           "\"Preguntas incorrectas\";"
                           "\"Preguntas omitidas\";"
                           "\"Puntaje\";"
                           "\"Nota\"\n";
    fputs(header_salida,archivo_salida);
    
    /* Comienza las llamadas a MPI */
    MPI_Init(&argc, &argv);

    /* Averiguamos el rango de nuestro proceso */
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);

    /* Averiguamos el número de procesos que estan 
     * ejecutando nuestro porgrama 
     */
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    
    if (p <= mi_rango) {
        fprintf(stderr, "ERROR, el programa necesita al menos 3 nodos de procesamiento");
        return EXIT_FAILURE;
    }
    
    /*Contenedores de registros*/
    char** registros_entrada = NULL;
    
    while(!feof(archivo_entrada)){
        if(mi_rango == 0){
            LeerArchivo(archivo_entrada,&registro_entrada);
        }

    }
/*
    if (mi_rango != 0) {
        // Crea mensaje
        sprintf(mensaje, "Saludos del proceso %d!", mi_rango);
        dest = 0;
        // Usa strlen+1 para que la marca /0 se transmita
        MPI_Send(mensaje, strlen(mensaje) + 1, MPI_CHAR,
                dest, tag, MPI_COMM_WORLD);
    } else { // mi_rango == 0
        for (fuente = 1; fuente < p; fuente++) {
            MPI_Recv(mensaje, 100, MPI_CHAR, fuente,
                    tag, MPI_COMM_WORLD, &estado);
            printf("%s\n", mensaje);
        }
    }
*/

    /* Termina con MPI. Recordemos que después de 
     * esta llamada no podemos llamar a funciones 
     * MPI, ni siquiera de nuevo a MPI_Init 
     */
    MPI_Finalize();
    return EXIT_SUCCESS;
}

void LeerArchivo(File* entrada, char*** registros){
    while(!feof(entrada)){
        for(int iter = 0; iter < PARTICION && !feof(entrada); iter++){
            *registro = (char**)realloc(*registro,(iter+1)*sizeof(char*));
            if(*registro == NULL){
				printf("Error en reserva de memoria (registro)\n");
				exit(EXIT_FAILURE);
			}
            (*registro)[iter] = (char*)malloc(BUFFER*sizeof(char));
            if((*registro)[iterador] == NULL){
				printf("Error en reserva de memoria (iregistro[])\n");
				exit(EXIT_FAILURE);
			}
            fgets(registro[iterador],BUFFER,archivo_entrada);
        }
    }
}