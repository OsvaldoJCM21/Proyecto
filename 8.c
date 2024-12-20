#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACTIVOS 100
#define MAX_USUARIOS 10

typedef struct {
    char nombre[50];
    char tipo[20];
    char proyecto[50];
    char empleado[50];
    float valor_original;
    int vida_util;
    int anio_compra;
} Activo;

Activo inventario[MAX_ACTIVOS];
int total_activos = 0;

char usuario[50];
char clave[50];

void guardarCredenciales() {
    FILE *archivo = fopen("credenciales.txt", "w");
    if (archivo == NULL) {
        printf("Error al guardar las credenciales.\n");
        return;
    }
    fprintf(archivo, "%s\n%s\n", usuario, clave);
    fclose(archivo);
}

void cargarCredenciales() {
    FILE *archivo = fopen("credenciales.txt", "r");
    if (archivo == NULL) {
        printf("No se encontraron credenciales. Se usarán valores predeterminados.\n");
        strcpy(usuario, "admin");
        strcpy(clave, "1234");
        guardarCredenciales();
        return;
    }
    fscanf(archivo, "%s\n%s", usuario, clave);
    fclose(archivo);
}

void guardarDatos() {
    FILE *archivo = fopen("inventario.txt", "w");
    if (archivo == NULL) {
        printf("Error al guardar los datos.\n");
        return;
    }

    fprintf(archivo, "%d\n", total_activos);
    for (int i = 0; i < total_activos; i++) {
        fprintf(archivo, "%s %s %s %s %.2f %d %d\n", inventario[i].nombre, inventario[i].tipo, 
                inventario[i].proyecto, inventario[i].empleado, inventario[i].valor_original, 
                inventario[i].vida_util, inventario[i].anio_compra);
    }

    fclose(archivo);
}

void cargarDatos() {
    FILE *archivo = fopen("inventario.txt", "r");
    if (archivo == NULL) {
        printf("No se encontraron datos guardados.\n");
        return;
    }

    fscanf(archivo, "%d", &total_activos);
    for (int i = 0; i < total_activos; i++) {
        fscanf(archivo, "%s %s %s %s %f %d %d", inventario[i].nombre, inventario[i].tipo, 
               inventario[i].proyecto, inventario[i].empleado, &inventario[i].valor_original, 
               &inventario[i].vida_util, &inventario[i].anio_compra);
    }

    fclose(archivo);
}

void cambiarUsuarioYClave() {
    char clave_actual[50];
    printf("Ingrese la clave actual: ");
    scanf("%s", clave_actual);

    if (strcmp(clave_actual, clave) == 0) {
        printf("Ingrese el nuevo usuario: ");
        scanf("%s", usuario);
        printf("Ingrese la nueva clave: ");
        scanf("%s", clave);
        guardarCredenciales();
        printf("Usuario y clave cambiados con éxito.\n");
    } else {
        printf("Clave incorrecta.\n");
    }
}

void agregarActivo() {
    if (total_activos >= MAX_ACTIVOS) {
        printf("No se pueden agregar más activos.\n");
        return;
    }

    Activo nuevo;
    printf("Ingrese el nombre del activo: ");
    scanf("%s", nuevo.nombre);
    printf("Ingrese el tipo de activo: ");
    scanf("%s", nuevo.tipo);
    printf("Ingrese el proyecto asignado: ");
    scanf("%s", nuevo.proyecto);
    printf("Ingrese el nombre del empleado al que se le asigna el activo: ");
    scanf("%s", nuevo.empleado);
    printf("Ingrese el valor original del activo: ");
    scanf("%f", &nuevo.valor_original);
    printf("Ingrese la vida útil del activo (en años): ");
    scanf("%d", &nuevo.vida_util);
    printf("Ingrese el año de compra: ");
    scanf("%d", &nuevo.anio_compra);

    inventario[total_activos] = nuevo;
    total_activos++;
    guardarDatos();
    printf("Activo agregado con éxito.\n");
}

void consultarActivos() {
    for (int i = 0; i < total_activos; i++) {
        printf("Activo %d:\n", i + 1);
        printf("Nombre: %s\n", inventario[i].nombre);
        printf("Tipo: %s\n", inventario[i].tipo);
        printf("Proyecto: %s\n", inventario[i].proyecto);
        printf("Empleado asignado: %s\n", inventario[i].empleado);
        printf("Valor original: %.2f\n", inventario[i].valor_original);
        printf("Vida útil: %d\n", inventario[i].vida_util);
        printf("Año de compra: %d\n\n", inventario[i].anio_compra);
    }
}

void desasignarActivo() {
    int indice;
    consultarActivos();

    if (total_activos == 0) {
        printf("No hay activos para desasignar.\n");
        return;
    }

    printf("Ingrese el número del activo a desasignar: ");
    scanf("%d", &indice);

    if (indice < 1 || indice > total_activos) {
        printf("Índice inválido.\n");
        return;
    }

    for (int i = indice - 1; i < total_activos - 1; i++) {
        inventario[i] = inventario[i + 1];
    }

    total_activos--;
    guardarDatos();
    printf("Activo desasignado con éxito.\n");
}

void menu() {
    int opcion;
    do {
        printf("\n--- Menú de Inventario ---\n");
        printf("1. Agregar activo\n");
        printf("2. Consultar activos\n");
        printf("3. Desasignar activo\n");
        printf("4. Cambiar usuario y clave\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarActivo();
                break;
            case 2:
                consultarActivos();
                break;
            case 3:
                desasignarActivo();
                break;
            case 4:
                cambiarUsuarioYClave();
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 5);
}

int main() {
    char usuario_ingresado[50], clave_ingresada[50];

    cargarCredenciales();
    cargarDatos();

    printf("--- Inicio de sesión ---\n");
    printf("Usuario: ");
    scanf("%s", usuario_ingresado);
    printf("Clave: ");
    scanf("%s", clave_ingresada);

    if (strcmp(usuario_ingresado, usuario) == 0 && strcmp(clave_ingresada, clave) == 0) {
        printf("Acceso concedido.\n");
        menu();
    } else {
        printf("Usuario o clave incorrectos.\n");
    }

    return 0;
}
