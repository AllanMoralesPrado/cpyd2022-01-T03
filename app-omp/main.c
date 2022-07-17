/*
 * Taller 01 de Computación Paralela y Distribuida
 * Primer Semestre de 2022
 * Integrantes: Allan Morales / Oscar Muñoz / Germán Ramirez
 * 
 * Programa: Resultados PAU - Paralelo
*/

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main(int argc, char** argv){
    
    //ValidarArgumentos(argc);

    //arch_e: archivo entrada, arch_s: archivo salida
    FILE *arch_e = NULL, *arch_s = NULL;
    AbrirArchivos(&arch_e,argv[1],&arch_s,argv[2]);

    LlenarSalida(arch_e,arch_s);
    Integrantes();

    fclose(arch_e);
    fclose(arch_s);
    return 0;
}