#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct{
	char calle1[50];
	char calle2 [50];
	int Trafico;
}Semaforo;

Semaforo* registrarDatos(Semaforo *datos, int *cantidad, char *calle1, char *calle2 ,int trafico) {

  Semaforo *temp = realloc(datos, (*cantidad + 1) * sizeof(Semaforo));

    if (temp == NULL) {
        printf("Error al reservar memoria.\n");
        return datos;  // devuelve el original intacto
    }

    datos = temp;
    strcpy(datos[*cantidad].calle1,calle1);
    
    strcpy(datos[*cantidad].calle2,calle2);
    datos[*cantidad].Trafico = trafico;
    (*cantidad)++;  // actualizamos el contador desde afuera via puntero
	
    return datos;
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
    }

    printf("\n=== REGISTRO DE DATOS ===\n");
    printf("%-10s %-10s %-10s %-6s\n", "Registro", "Calle principal", "Interseccion", "Trafico");
    printf("------------------------\n");
    int i;
    for ( i = 0; i < cantidad; i++) {
        printf("%-6d %-18s %-18s %-4d\n", i + 1, datos[i].calle1, datos[i].calle2,datos[i].Trafico);
    }
    //printf("------------------------\n");
    //printf("Total: %d disparos\n", cantidad);
}

void nuevaCalle (char *callePpal){
	char nuevacalle[50];
	printf("Elija la nueva calle a evaluar: \n");
	//scanf("%s",&nuevacalle);
	//gets(nuevacalle);
	scanf("%s", &nuevacalle);
	strcpy(callePpal,nuevacalle);	
}

void seleccionoCalle(Semaforo *str_semaforo ,char *callePpal, int *cantidad){
	int numero;
    do {
        printf("Ingrese por indice la nueva calle: \n");
        scanf("%d", &numero);
        while (getchar() != '\n'); 
    } while (numero <= 0 || numero > *cantidad);
    
    strcpy(callePpal, str_semaforo[numero - 1].calle2);
}

void BuscoDato(char *calle1, char *calle2, Semaforo *arreglo, int cantidad) {
    int i, encontrado = 0;
    for (i = 0; i < cantidad; i++) {
        if (contiene(arreglo[i].calle1,calle1) && contiene(arreglo[i].calle2,calle2)) {
            printf("%-6d %-20s %-15s %-6d\n", i + 1, arreglo[i].calle1, arreglo[i].calle2, arreglo[i].Trafico);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("No se hallaron los datos\n");
}

void menu(){
	printf("\n1.Inserte interseccion\n");
	printf("\n2.Mostrar datos de intersecciones\n");
	printf("\n3.Elegir nueva calle\n");
	printf("\n4.Elegir nueva calle por indice\n");
	printf("\n5.Busqueda de datos\n");
	printf("\n6.Salir del programa\n\n");
}

int main(int argc, char *argv[]) {
	srand(time(NULL)); 
	char callePpal[50];
	char interseccion[50];
	char calleuno[50];
	char calledos[50];
	int contador=0;
	int *cont;
	cont= &contador;
	int opcion;
	Semaforo *centro_datos= NULL;
	printf("Ingrese calle principal: \n");
	gets(callePpal);
	int bandera = 1;
	do{
	menu();
	scanf("%d",&opcion);
	int nivel_trafico = (rand() % 100) + 1;
		switch (opcion){
		case 1:
			printf("Ingrese interseccion: \n");
			while (getchar() != '\n');  
			gets(interseccion);		
			centro_datos = registrarDatos(centro_datos, cont, callePpal, interseccion , nivel_trafico);
			break;
		case 2:
			mostrarRegistro(centro_datos,*cont);
			break;
		case 3:
			//centro_datos = registrarDatos(centro_datos, cont, callePpal, interseccion ,nivel_trafico);
			nuevaCalle(callePpal);
			break;
		case 4:
            seleccionoCalle(centro_datos,callePpal,cont);  
            //centro_datos = registrarDatos(centro_datos, cont, callePpal, interseccion ,nivel_trafico);
			break;
		case 5: 
			printf("Ingrese calle1 \n");
			while (getchar() != '\n');  // limpia buffer
			gets(calleuno);
			printf("Ingrese calle2 \n");
			gets(calledos);
			BuscoDato(calleuno,calledos,centro_datos,*cont);
			break;	
		case 6:		
			free(centro_datos);
			bandera=0;
			break;
		}
	}while(bandera!=0);
	
	return 0;
}


