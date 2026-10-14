#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "semaforo.h"

int main(int argc, char *argv[]) {
    srand(time(NULL)); 
    char calle_ppal[MAX_BUFFER];
    int contador = 0;
    int *cont = &contador;
    int opcion;
    Semaforo *centro_datos = NULL;
    int bandera = 1;

    insertarCalle("Ingrese calle principal: \n", calle_ppal);
    
    do {
        menu();
        scanf("%d", &opcion);
        while (getchar() != '\n'); // Limpia el búfer de entrada después del scanf
        
        int nivel_trafico = (rand() % 100) + 1;

        switch (opcion) {
            case 1: {
                centro_datos = registrarDatos(centro_datos, cont, nivel_trafico);
                strcpy(centro_datos[*cont - 1].calle_principal, calle_ppal);
                insertarCalle("Ingrese interseccion: \n", centro_datos[*cont - 1].calle_interseccion);
                break;
            } // case 1
            case 2: {
                mostrarRegistro(centro_datos, *cont);
                break;
            } // case 2
            case 3: {
                if (centro_datos == NULL || *cont == 0) {
                    printf("No hay registros cargados todavia.\n");
                    break;
                }
                insertarCalle("Elija la nueva calle a evaluar: \n", calle_ppal);
                break;
            } // case 3
            case 4: {
                if (centro_datos == NULL || *cont == 0) {
                    printf("No hay registros cargados todavia.\n");
                    break;
                }
                seleccionoCalle(centro_datos, calle_ppal, cont);
                break;
            } // case 4
            case 5: {
                if (centro_datos == NULL || *cont == 0) {
                    printf("No hay registros cargados todavia.\n");
                    break;
                }
                buscoDato(centro_datos, *cont);
                break;
            } // case 5
            case 6: {        
                free(centro_datos);
                bandera = 0;
                break;
            } // case 6
            default: {
                printf("Opcion invalida.\n");
                break;
            } // default
        } // switch (opcion)
    } while (bandera != 0);
    
    return 0;
}

Semaforo* registrarDatos(Semaforo *datos, int *cantidad, int trafico) {
    Semaforo *temp = (Semaforo *) realloc(datos, (*cantidad + 1) * sizeof(Semaforo));

    if (temp == NULL) {
        printf("Error al reservar memoria.\n");
        return datos;  
    } // if

    datos = temp;
    datos[*cantidad].trafico = trafico;
    (*cantidad)++;  
    
    return datos;
}

void insertarCalle(const char *mensaje, char *calle) {
    printf("%s", mensaje);
    if (fgets(calle, MAX_BUFFER, stdin) != NULL) {
        size_t len = strlen(calle);
        if (len > 0 && calle[len - 1] == '\n') {
            calle[len - 1] = '\0';
        } // if
    } // if    
}
 
void insertarDosCalles(char *calle1, char *calle2) {
    insertarCalle("Ingrese calle 1:\n", calle1);
    insertarCalle("Ingrese calle 2:\n", calle2);
}

int contiene(const char *texto, const char *patron) {
    size_t lt = strlen(texto), lp = strlen(patron);
    if (lp == 0) {
        return 1;
    } // if
    if (lp > lt) {
        return 0;
    } // if
    
    size_t i;
    for (i = 0; i + lp <= lt; i++) {
        size_t j = 0;
        while (j < lp && tolower((unsigned char) texto[i + j]) == tolower((unsigned char) patron[j])) {
            j++;
        } // while
        if (j == lp) {
            return 1;
        } // if
    } // for
    return 0;
}

void mostrarRegistro(Semaforo *datos, int cantidad) {
    if (cantidad == 0) {
        printf("No hay datos registrados.\n");
        return;
    } // if

    printf("\n=== REGISTRO DE DATOS ===\n");
    printf("%-10s %-18s %-18s %-6s\n", "Registro", "Calle principal", "Interseccion", "Trafico");
    printf("----------------------------------------------------\n");
    
    int i;
    for (i = 0; i < cantidad; i++) {
        printf("%-6d %-18s %-18s %-4d\n", i + 1, datos[i].calle_principal, datos[i].calle_interseccion, datos[i].trafico);
    } // for
}

void seleccionoCalle(Semaforo *str_semaforo, char *calle_ppal, int *cantidad) {
    int numero;
    do {
        printf("Ingrese por indice la nueva calle: \n");
        scanf("%d", &numero);
        while (getchar() != '\n'); 
    } while (numero <= 0 || numero > *cantidad);
    
    strcpy(calle_ppal, str_semaforo[numero - 1].calle_interseccion);
}

int buscoDato(Semaforo *arreglo, int cantidad) {
    char calle_uno[MAX_BUFFER], calle_dos[MAX_BUFFER];
    insertarDosCalles(calle_uno, calle_dos);
    
    int i;
    for (i = 0; i < cantidad; i++) {
        if (contiene(arreglo[i].calle_principal, calle_uno) && contiene(arreglo[i].calle_interseccion, calle_dos)) {
            printf("%-6d %-20s %-15s %-6d\n", i + 1, arreglo[i].calle_principal, arreglo[i].calle_interseccion, arreglo[i].trafico);
            return 1;
        } // if
    } // for

    printf("No se hallaron los datos\n");
    return 0;
}

void menu() {
    printf("\n1. Inserte interseccion\n");
    printf("2. Mostrar datos de intersecciones\n");
    printf("3. Elegir nueva calle\n");
    printf("4. Elegir nueva calle por indice\n");
    printf("5. Busqueda de datos\n");
    printf("6. Salir del programa\n\n");
}


