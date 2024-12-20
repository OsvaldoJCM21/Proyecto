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

char usuario[50] = "admin";
char clave[50] = "1234";

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
    if (archivo != NULL) {
        fscanf(archivo, "%s", usuario);
        fscanf(archivo, "%s", clave);
        fclose(archivo);
    } else {
        printf("No se encontraron credenciales guardadas. Usando valores predeterminados.\n");
    }
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

void cambiarCredenciales() {
    char clave_actual[50];
    printf("Ingrese la clave actual: ");
    scanf("%s", clave_actual);

    if (strcmp(clave_actual, clave) == 0) {
        printf("Ingrese el nuevo usuario: ");
        scanf("%s", usuario);
        printf("Ingrese la nueva clave: ");
        scanf("%s", clave);
        guardarCredenciales();
        printf("Usuario y clave cambiados con exito.\n");
    } else {
        printf("Clave incorrecta.\n");
    }
}

void agregarActivo() {
    if (total_activos >= MAX_ACTIVOS) {
        printf("No se pueden agregar mas activos.\n");
        return;
    }

    Activo nuevo;
    getchar(); // Consumir el carácter de nueva línea pendiente
    printf("Ingrese el nombre del activo: ");
    fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0'; // Eliminar el salto de línea

    printf("Ingrese el tipo de activo: ");
    fgets(nuevo.tipo, sizeof(nuevo.tipo), stdin);
    nuevo.tipo[strcspn(nuevo.tipo, "\n")] = '\0';

    printf("Ingrese el proyecto asignado: ");
    fgets(nuevo.proyecto, sizeof(nuevo.proyecto), stdin);
    nuevo.proyecto[strcspn(nuevo.proyecto, "\n")] = '\0';

    printf("Ingrese el nombre del empleado al que se le asigna el activo: ");
    fgets(nuevo.empleado, sizeof(nuevo.empleado), stdin);
    nuevo.empleado[strcspn(nuevo.empleado, "\n")] = '\0';

    printf("Ingrese el valor original del activo: ");
    scanf("%f", &nuevo.valor_original);

    printf("Ingrese la vida util del activo (en anos): ");
    scanf("%d", &nuevo.vida_util);

    printf("Ingrese el ano de compra: ");
    scanf("%d", &nuevo.anio_compra);

    inventario[total_activos] = nuevo;
    total_activos++;
    guardarDatos();
    printf("Activo agregado con exito.\n");
}

float calcularDepreciacion(Activo activo) {
    // Depreciación anual
    return activo.valor_original / activo.vida_util;
}

void consultarActivos() {
    for (int i = 0; i < total_activos; i++) {
        printf("Activo %d:\n", i + 1);
        printf("Nombre: %s\n", inventario[i].nombre);
        printf("Tipo: %s\n", inventario[i].tipo);
        printf("Proyecto: %s\n", inventario[i].proyecto);
        printf("Empleado asignado: %s\n", inventario[i].empleado);
        printf("Valor original: %.2f\n", inventario[i].valor_original);
        printf("Vida util: %d\n", inventario[i].vida_util);
        printf("Ano de compra: %d\n", inventario[i].anio_compra);

        // Mostrar la depreciación anual
        printf("Depreciacion anual: %.2f\n\n", calcularDepreciacion(inventario[i]));
    }
}

void desasignarActivo() {
    int indice;
    consultarActivos();

    if (total_activos == 0) {
        printf("No hay activos para desasignar.\n");
        return;
    }

    printf("Ingrese el numero del activo a desasignar: ");
    scanf("%d", &indice);

    if (indice < 1 || indice > total_activos) {
        printf("Indice invalido.\n");
        return;
    }

    for (int i = indice - 1; i < total_activos - 1; i++) {
        inventario[i] = inventario[i + 1];
    }

    total_activos--;
    guardarDatos();
    printf("Activo desasignado con exito.\n");
}

void menu() {
    int opcion;
    do {
        printf("\n--- Menu de Inventario ---\n");
        printf("1. Agregar activo\n");
        printf("2. Consultar activos\n");
        printf("3. Desasignar activo\n");
        printf("4. Cambiar usuario y clave\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
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
                cambiarCredenciales();
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 5);
}

int main() {
    char usuario_ingresado[50], clave_ingresada[50];

    cargarCredenciales();
    cargarDatos();

    while (1) {
        printf("--- Inicio de sesion ---\n");
        printf("Usuario: ");
        scanf("%s", usuario_ingresado);
        printf("Clave: ");
        scanf("%s", clave_ingresada);

        if (strcmp(usuario_ingresado, usuario) == 0 && strcmp(clave_ingresada, clave) == 0) {
            printf("Acceso concedido.\n");
            menu();
            break;
        } else {
            printf("Usuario o clave incorrectos. Intente de nuevo.\n");
        }
    }

    return 0;
}
