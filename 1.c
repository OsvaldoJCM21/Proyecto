#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para los equipos
typedef struct {
    char nombre[50];
    char proyecto[50];
    int usoSemanal;  // Horas de uso semanal
    int vidaUtil;    // Vida útil en semanas
    int semanasUso;  // Semanas utilizadas
} Equipo;

// Constantes
#define MAX_EQUIPOS 50
#define PASSWORD_FILE "password.txt"
#define INVENTORY_FILE "inventario.dat"

// Variables globales
Equipo inventario[MAX_EQUIPOS];
int totalEquipos = 0;
char password[20] = "admin123";

// Prototipos de funciones
void cargarInventario();
void guardarInventario();
void cargarPassword();
void guardarPassword();
int login();
void menu();
void agregarEquipo();
void mostrarEquipos();
void consultarPorProyecto();
void calcularDepreciacion();
void modificarPassword();

// Función principal
int main() {
    cargarInventario();
    cargarPassword();

    if (login()) {
        menu();
    } else {
        printf("Acceso denegado. Programa finalizado.\n");
    }

    return 0;
}

// Función para cargar el inventario desde el archivo
void cargarInventario() {
    FILE *file = fopen(INVENTORY_FILE, "rb");
    if (file) {
        fread(&totalEquipos, sizeof(int), 1, file);
        fread(inventario, sizeof(Equipo), totalEquipos, file);
        fclose(file);
    }
}

// Función para guardar el inventario en el archivo
void guardarInventario() {
    FILE *file = fopen(INVENTORY_FILE, "wb");
    if (file) {
        fwrite(&totalEquipos, sizeof(int), 1, file);
        fwrite(inventario, sizeof(Equipo), totalEquipos, file);
        fclose(file);
    }
}

// Función para cargar la contraseña desde el archivo
void cargarPassword() {
    FILE *file = fopen(PASSWORD_FILE, "r");
    if (file) {
        fgets(password, sizeof(password), file);
        fclose(file);
    }
}

// Función para guardar la contraseña en el archivo
void guardarPassword() {
    FILE *file = fopen(PASSWORD_FILE, "w");
    if (file) {
        fputs(password, file);
        fclose(file);
    }
}

// Función de inicio de sesión
int login() {
    char input[20];
    printf("Ingrese la contraseña: ");
    scanf("%s", input);
    return strcmp(input, password) == 0;
}

// Función del menú principal
void menu() {
    int opcion;
    do {
        printf("\n--- Menú Principal ---\n");
        printf("1. Agregar equipo\n");
        printf("2. Mostrar inventario\n");
        printf("3. Consultar por proyecto\n");
        printf("4. Calcular depreciación\n");
        printf("5. Modificar contraseña\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: agregarEquipo(); break;
            case 2: mostrarEquipos(); break;
            case 3: consultarPorProyecto(); break;
            case 4: calcularDepreciacion(); break;
            case 5: modificarPassword(); break;
            case 6: guardarInventario(); printf("Inventario guardado. Saliendo...\n"); break;
            default: printf("Opción no válida.\n");
        }
    } while (opcion != 6);
}

// Función para agregar un equipo
void agregarEquipo() {
    if (totalEquipos < MAX_EQUIPOS) {
        printf("Ingrese el nombre del equipo: ");
        scanf(" %[^\n]", inventario[totalEquipos].nombre);
        printf("Ingrese el proyecto asociado: ");
        scanf(" %[^\n]", inventario[totalEquipos].proyecto);
        printf("Ingrese las horas de uso semanal: ");
        scanf("%d", &inventario[totalEquipos].usoSemanal);
        printf("Ingrese la vida útil en semanas: ");
        scanf("%d", &inventario[totalEquipos].vidaUtil);
        inventario[totalEquipos].semanasUso = 0;
        totalEquipos++;
        printf("Equipo agregado con éxito.\n");
    } else {
        printf("El inventario está lleno.\n");
    }
}

// Función para mostrar el inventario
void mostrarEquipos() {
    printf("\n--- Inventario ---\n");
    for (int i = 0; i < totalEquipos; i++) {
        printf("Equipo: %s\n", inventario[i].nombre);
        printf("Proyecto: %s\n", inventario[i].proyecto);
        printf("Horas de uso semanal: %d\n", inventario[i].usoSemanal);
        printf("Vida útil: %d semanas\n", inventario[i].vidaUtil);
        printf("Semanas de uso: %d\n", inventario[i].semanasUso);
        printf("-------------------------\n");
    }
}

// Función para consultar equipos por proyecto
void consultarPorProyecto() {
    char proyecto[50];
    printf("Ingrese el nombre del proyecto: ");
    scanf(" %[^\n]", proyecto);

    printf("\n--- Equipos del proyecto '%s' ---\n", proyecto);
    for (int i = 0; i < totalEquipos; i++) {
        if (strcmp(inventario[i].proyecto, proyecto) == 0) {
            printf("Equipo: %s\n", inventario[i].nombre);
        }
    }
}

// Función para calcular depreciación y reemplazo
void calcularDepreciacion() {
    printf("\n--- Depreciación y reemplazo ---\n");
    for (int i = 0; i < totalEquipos; i++) {
        int vidaRestante = inventario[i].vidaUtil - inventario[i].semanasUso;
        printf("Equipo: %s\n", inventario[i].nombre);
        printf("Vida restante: %d semanas\n", vidaRestante);
        if (vidaRestante <= 0) {
            printf("Este equipo debe ser reemplazado.\n");
        }
        printf("-------------------------\n");
    }
}

// Función para modificar la contraseña
void modificarPassword() {
    char nuevaPassword[20];
    printf("Ingrese la nueva contraseña: ");
    scanf("%s", nuevaPassword);
    strcpy(password, nuevaPassword);
    guardarPassword();
    printf("Contraseña modificada con éxito.\n");
}
