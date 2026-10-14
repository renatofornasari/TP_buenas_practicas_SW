#ifndef SEMAFORO_H
#define SEMAFORO_H

#define MAX_BUFFER 50

/* Estructura que almacena los datos de la intersección semafórica */
typedef struct {
    char calle_principal[MAX_BUFFER];
    char calle_interseccion[MAX_BUFFER];
    int trafico;
} Semaforo;

/**
 * Registra o expande el bloque de memoria dinámico para una nueva intersección.
 * @param datos Puntero al arreglo dinámico de semáforos.
 * @param cantidad Puntero a la cantidad actual de elementos registrados.
 * @param trafico Nivel de tráfico generado aleatoriamente.
 * @return Puntero actualizado al bloque de memoria dinámico.
 */
Semaforo* registrarDatos(Semaforo *datos, int *cantidad, int trafico);

/**
 * Verifica si un texto contiene un patrón determinado (búsqueda insensible a mayúsculas/minúsculas).
 */
int contiene(const char *texto, const char *patron);

/**
 * Muestra por consola todos los registros cargados en el sistema.
 */
void mostrarRegistro(Semaforo *datos, int cantidad);

/**
 * Lee una calle ingresada por el usuario de forma segura utilizando fgets.
 */
void insertarCalle(const char *mensaje, char *calle);

/**
 * Lee un par de calles ingresadas por el usuario para búsquedas o registros.
 */
void insertarDosCalles(char *calle1, char *calle2);

/**
 * Permite seleccionar una intersección existente a partir de su índice numérico.
 */
void seleccionoCalle(Semaforo *str_semaforo, char *calle_ppal, int *cantidad);

/**
 * Busca coincidencias de calles en el registro almacenado.
 */
int buscoDato(Semaforo *arreglo, int cantidad);

/**
 * Despliega el menú principal de opciones en pantalla.
 */
void menu();

#endif // SEMAFORO_H