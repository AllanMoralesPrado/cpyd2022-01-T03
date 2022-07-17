#include "funciones.h"

void ValidarArgumentos(int argc){
    if(argc < 3){
        printf("Requiere ubicación del nuevo archivo\nLa app se cerrará\n");
        exit(EXIT_FAILURE);
    }
}

void AbrirArchivos(FILE** arch_e, char* ruta_e, FILE** arch_s, char* ruta_s){
    if((*arch_e = fopen(ruta_e,"rt")) == NULL){
        printf("Archivo de entrada no encontrado.\n");
        exit(EXIT_FAILURE);
    }
    if((*arch_s = fopen(ruta_s,"wt")) == NULL){
        printf("Archivo de salida no encontrado/creado.\n");
        exit(EXIT_FAILURE);
    }
}

void LlenarSalida(FILE* arch_e, FILE* arch_s){

    //Encabezado salida
    char* oencabezado = 
        "\"Identificador de estudiante\";"
        "\"Preguntas correctas\";"
        "\"Preguntas incorrectas\";"
        "\"Preguntas omitidas\";"
        "\"Puntaje\";"
        "\"Nota\"";

    fputs(oencabezado,arch_s);
    //Fin Encabezado salida

    //Encabezado entrada
    char* iencabezado = (char*)malloc(BUFF_SIZE*sizeof(char));
    fgets(iencabezado,BUFF_SIZE,arch_e);
    free(iencabezado);
    //Fin Encabezado entrada

    size_t chunk_size = USHRT_MAX, iterador;
    char** iregistro = NULL;

    while(!feof(arch_e)){
        for(iterador = 0; iterador < chunk_size && !feof(arch_e); iterador++){
            iregistro = (char**)realloc(iregistro,(iterador+1)*sizeof(char*));
            if(iregistro == NULL){
				printf("Error en reserva de memoria (iregistro)\n");
				exit(EXIT_FAILURE);
			}
            iregistro[iterador] = (char*)malloc(BUFF_SIZE*sizeof(char));
            if(iregistro[iterador] == NULL){
				printf("Error en reserva de memoria (iregistro[])\n");
				exit(EXIT_FAILURE);
			}
            fgets(iregistro[iterador],BUFF_SIZE,arch_e);
        }

        LlenarChunk(iterador,iregistro);

        int iter;
        for(iter = 0; iter < iterador; iter++){
            fputs(iregistro[iter],arch_s);
            free(iregistro[iter]);
        }

        free(iregistro);
        iregistro = NULL;
    }
    
}

void LlenarChunk(size_t iterador, char** iregistro){
#pragma omp parallel
    {
#pragma omp for
        for(size_t posicion = 0; posicion < iterador; posicion++){
            char* resultado = Evaluar(iregistro[posicion]);
            strcpy(iregistro[posicion],resultado);
            free(resultado);
        }        
    }    
}

char* Evaluar(char* registro){
    const char pauta[PREGUNTAS] = {'A','E','C','B','B','D','A','B','E','C','B','D'};
    
    char* cpy_registro = (char*)malloc((strlen(registro)+1)*sizeof(char));
    strcpy(cpy_registro,registro);
    char* token = strtok(cpy_registro,";");

    char* resultado = (char*)malloc((strlen(cpy_registro)+2)*sizeof(char));
    sprintf(resultado,"\n%s",cpy_registro);

    conteo res = {0,0,0,0.0,0.0};
    int iterador = 0;
    
    while((token = strtok(NULL,";")) != NULL){
        if(token[1] == pauta[iterador++])
            res.correctas++;
        else{
            if(token[1] == '-')
                res.omitidas++;
            else
                res.incorrectas++;
        }
    }

    res.puntaje = res.correctas*(0.5) + res.incorrectas*(-0.12);
    res.nota = 1 + res.puntaje;

    //longitud(';"0";"10";"2";"-1.20";"-0.20"\n') = 30
    char* score = (char*)malloc(30*sizeof(char));
    sprintf(score,";\"%d\";\"%d\";\"%d\";\"%.1lf\";\"%.1lf\"",
        res.correctas,res.incorrectas,res.omitidas,res.puntaje,res.nota);
    
    resultado = (char*)realloc(resultado,(strlen(resultado)+strlen(score)+1)*sizeof(char));
    strcat(resultado,score);

    return resultado;
}

void Integrantes(){
    printf("======Integrantes======"
    "\nAllan Morales"
    "\nOscar Muñoz"
    "\nGerman Ramirez"
"\n⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢾⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠏⠃⠀⠀⣀⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠋⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⡟⠀⠀⢀⡀⠀⠀⠀⠀⠀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⠷⠛⣫⣭⡉⠉⠲⣾⡿⠋⠉⣩⣭⣍⠛⢶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⡇⠀⢸⣿⣿⣿⠀⠀⠟⠧⠀⠸⣿⣿⣿⠀⠈⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠉⠋⠁⣠⣆⣀⣀⣠⣄⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⢈⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠉⠛⠻⠿⢿⣿⡿⠟⠛⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀"
"\n⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠀⠀⠀⠀"
"\n⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⡇⠀⠀⠀"
"\n⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⠀⢀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣿⠁⢃⠀⠀⠀"
"\n⠀⠀⣿⣿⣿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠻⠿⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⡇⢸⠀⠀⠀"
"\n⠀⢸⣿⣿⡇⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣦⣤⣄⣀⡀⠀⠀⠀⠀⠀⠀⣀⣤⡄⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⢿⣷⢸⡀⠀⠀"
"\n⠀⣼⣿⣿⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⣠⣿⣿⣿⣿⠃⠀⣿⡏⡇⠀⠀"
"\n⠀⣿⣿⡇⠀⠀⠀⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣀⣀⣤⣶⣿⣿⣿⠟⠁⠀⠀⠉⠁⡇⠀⠀"
"\n⠀⡿⠛⠃⠀⠀⠀⠀⠀⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⡇⠀⠀"
"\n⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠉⠀⠀⠀⠀⠀⠀⡀⠀⡇⠀⠀"
"\n⠀⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡟⠛⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⢠⠀⡇⠀⠀"
"\n⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠁⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⠀⠀⠀⢹⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⣷⠀⠀"
"\n⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⣿⠀⠀"
"\n⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⢹⡄⠀"
"\n⢠⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⡀"
"\n⢸⣿⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣣"
"\n⣾⣿⠀⠀⢹⡀⠀⠀⠀⠀⠀⠀⠀⠀⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⢀⣿"
"\n⢿⢿⡄⠀⠀⠳⡀⠀⠀⠀⠀⠀⠀⠀⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⠁⠀⣾⡟"
"\n⠸⡈⢧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠁"
"\n⠀⠑⢌⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠴⠞⠉⠀⠀"
"\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⠃⠀⠀⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⢠⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⠀⠀⠀⣤⡴⠋⠀⢀⣠⢿⡇⠀⣀⠔⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⢸⣿⠀⠀⠀⠻⣀⣀⠀⠀⠀⠀⠀⠀⠀"
"\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠁⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠢⠀⠸⠛⠓⠢⠄⠀⠉⠉⠁⠀⠀⠀⠀⠀⠀");
}