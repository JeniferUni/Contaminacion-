#include <stdio.h>
#include <string.h>
#include "funciones.h"

// Inicializa el registro
void inicializarRegistros(Registros *registros) {
    registros->cantidadZonas = 0;
}

// Permite agregar una nueva zona
void ingresarZona(Registros *registros) {
    if (registros->cantidadZonas >= MAX_ZONAS) {
        printf("No se pueden agregar mas zonas.\n");
        return;
    }
    printf("Ingrese el nombre de la nueva zona: ");
    scanf(" %[^\n]", registros->zonas[registros->cantidadZonas].nombre);

    registros->zonas[registros->cantidadZonas].diasRegistrados = 0;
    registros->cantidadZonas++;

    printf("Zona agregada correctamente.\n");
}

// Ingresa datos para una zona y día específico
void ingresarDatosZona(Registros *registros) {
    printf("Seleccione la zona:\n");
    for (int i = 0; i < registros->cantidadZonas; i++) {
        printf("%d. %s\n", i + 1, registros->zonas[i].nombre);
    }
      int opcionZona;
    printf("Seleccione una zona (1-%d): ", registros->cantidadZonas);
    scanf("%d", &opcionZona);

    if (opcionZona < 1 || opcionZona > registros->cantidadZonas) {
        printf("Opcion no valida.\n");
        return;
    }
Zona *zonaSeleccionada = &registros->zonas[opcionZona - 1];

    if (zonaSeleccionada->diasRegistrados >= DIAS_MES) {
        printf("Ya se han registrado los datos para los 30 dias de esta zona.\n");
        return;
    }

    Dia *dia = &zonaSeleccionada->dias[zonaSeleccionada->diasRegistrados];

    printf("Ingrese CO2 (ppm): ");
    scanf("%f", &dia->co2);
    printf("Ingrese SO2 (ppm): ");
    scanf("%f", &dia->so2);
    printf("Ingrese NO2 (ppm): ");
    scanf("%f", &dia->no2);
    printf("Ingrese PM2.5 (ppm): ");
    scanf("%f", &dia->pm25);

    zonaSeleccionada->diasRegistrados++;
    printf("Datos ingresados para el dia %d en la zona '%s'.\n",
           zonaSeleccionada->diasRegistrados, zonaSeleccionada->nombre);
}

// Coeficientes para cada parámetro
#define CO2_COEF 0.5
#define SO2_COEF 0.8
#define NO2_COEF 1.2
#define PM25_COEF 1.5
#define TEMPERATURA_COEF 0.3
#define VIENTO_COEF 0.5
#define HUMEDAD_COEF 0.2

// Predice datos para el siguiente día de una zona
void prediccionSiguienteDia(const Registros *registros) {
    printf("Seleccione la zona para realizar la prediccion:\n");
    for (int i = 0; i < registros->cantidadZonas; i++) {
        printf("%d. %s\n", i + 1, registros->zonas[i].nombre);
    }
 int opcionZona;
    printf("Seleccione una zona (1-%d): ", registros->cantidadZonas);
    scanf("%d", &opcionZona);

    if (opcionZona < 1 || opcionZona > registros->cantidadZonas) {
        printf("Opcion no valida.\n");
        return;
    }

    Zona *zonaSeleccionada = &registros->zonas[opcionZona - 1];
    int diasRegistrados = zonaSeleccionada->diasRegistrados;

    if (diasRegistrados < 3) {
        printf("No hay suficientes datos para realizar una prediccion en la zona '%s'.\n", zonaSeleccionada->nombre);
        return;
    }
    Dia *dias = zonaSeleccionada->dias;

    // Promedio de los últimos 3 días
    float promedioCO2 = 0, promedioSO2 = 0, promedioNO2 = 0, promedioPM25 = 0;

    for (int i = diasRegistrados - 3; i < diasRegistrados; i++) {
        promedioCO2 += dias[i].co2;
        promedioSO2 += dias[i].so2;
        promedioNO2 += dias[i].no2;
        promedioPM25 += dias[i].pm25;
    }

    promedioCO2 /= 3;
    promedioSO2 /= 3;
    promedioNO2 /= 3;
    promedioPM25 /= 3;

    // Aplicar los coeficientes a los promedios
    float prediccionCO2 = promedioCO2 * CO2_COEF;
    float prediccionSO2 = promedioSO2 * SO2_COEF;
    float prediccionNO2 = promedioNO2 * NO2_COEF;
    float prediccionPM25 = promedioPM25 * PM25_COEF;
    printf("\n--- Prediccion para el dia siguiente en la zona '%s' ---\n", zonaSeleccionada->nombre);
    printf("CO2 (ppm): %.2f\n", prediccionCO2);
    printf("SO2 (ppm): %.2f\n", prediccionSO2);
    printf("NO2 (ppm): %.2f\n", prediccionNO2);
    printf("PM2.5 (ppm): %.2f\n", prediccionPM25);

    // Recomendaciones según los niveles de contaminación
    printf("\n--- Recomendaciones ---\n");
    if (prediccionCO2 > 400) {
        printf("Se recomienda reducir las emisiones de CO2.\n");
    }
    if (prediccionSO2 > 0.3) {
        printf("Nivel de SO2 elevado. Evite actividades al aire libre.\n");
    }
    if (prediccionNO2 > 0.4) {
        printf("Nivel de NO2 elevado. Restrinja el trafico vehicular.\n");
    }
    if (prediccionPM25 > 50) {
        printf("Nivel de PM2.5 elevado. Uso de mascarillas recomendado.\n");
    }
}
// Para imprimir el histórico de los 30 días con recomendaciones
void imprimirHistorico(const Registros *registros) {
    for (int i = 0; i < registros->cantidadZonas; i++) {
        Zona *zona = &registros->zonas[i];
        printf("\n--- Historico de 30 dias para la zona '%s' ---\n", zona->nombre);

        for (int j = 0; j < zona->diasRegistrados; j++) {
            Dia *dia = &zona->dias[j];
            printf("Día %d: CO2 = %.2f, SO2 = %.2f, NO2 = %.2f, PM2.5 = %.2f\n", 
                   j + 1, dia->co2, dia->so2, dia->no2, dia->pm25);

            // Recomendaciones basadas en el día
            printf("Recomendaciones: \n");
            if (dia->co2 > 400) {
                printf("    Reducir emisiones de CO2.\n");
            }
            if (dia->so2 > 0.3) {
                printf("    Evitar actividades al aire libre por SO2.\n");
            }
 if (dia->no2 > 0.4) {
                printf("    Restringir trafico vehicular debido a NO2.\n");
            }
            if (dia->pm25 > 50) {
                printf("    Uso de mascarillas recomendado por PM2.5.\n");
            }
        }
    }
}
void calcularPromedioHistorico(const Registros *registros) {
    printf("Seleccione la zona para calcular el promedio historico:\n");
    for (int i = 0; i < registros->cantidadZonas; i++) {
        printf("%d. %s\n", i + 1, registros->zonas[i].nombre);
    }

    int opcionZona;
    printf("Seleccione una zona (1-%d): ", registros->cantidadZonas);
    scanf("%d", &opcionZona);
    if (opcionZona < 1 || opcionZona > registros->cantidadZonas) {
        printf("Opcion no valida.\n");
        return;
    }

    Zona *zonaSeleccionada = &registros->zonas[opcionZona - 1];
    int diasRegistrados = zonaSeleccionada->diasRegistrados;

    if (diasRegistrados == 0) {
        printf("No hay datos registrados en esta zona para calcular el promedio historico.\n");
        return;
    }

    float sumaCO2 = 0, sumaSO2 = 0, sumaNO2 = 0, sumaPM25 = 0;

    // Sumar los valores de cada parámetro de los días registrados
    for (int i = 0; i < diasRegistrados; i++) {
        sumaCO2 += zonaSeleccionada->dias[i].co2;
        sumaSO2 += zonaSeleccionada->dias[i].so2;
        sumaNO2 += zonaSeleccionada->dias[i].no2;
        sumaPM25 += zonaSeleccionada->dias[i].pm25;
    }

    // Calcular el promedio de cada parámetro
    float promedioCO2 = sumaCO2 / diasRegistrados;
    float promedioSO2 = sumaSO2 / diasRegistrados;
    float promedioNO2 = sumaNO2 / diasRegistrados;
    float promedioPM25 = sumaPM25 / diasRegistrados;

    if (diasRegistrados < DIAS_MES) {
        printf("\n*** No se cuentan con los datos de los 30 dias. ***\n");
        printf("Promedio historico de los ultimos %d dias en la zona '%s'\n", 
               diasRegistrados, zonaSeleccionada->nombre);
    } else {
        printf("\n--- Promedio historico de los 30 dias en la zona '%s' ---\n", 
               zonaSeleccionada->nombre);
    }

    printf("\nResumen de promedios:\n");
    printf("--------------------------------\n");
    printf("CO2 (ppm): %.2f\n", promedioCO2);
    printf("SO2 (ppm): %.2f\n", promedioSO2);
    printf("NO2 (ppm): %.2f\n", promedioNO2);
    printf("PM2.5 (ppm): %.2f\n", promedioPM25);
    printf("--------------------------------\n");

    // Recomendaciones basadas en el promedio histórico
    printf("\n--- Recomendaciones ---\n");
    if (promedioCO2 > 400) {
        printf(" Se recomienda reducir las emisiones de CO2.\n");
    }
    if (promedioSO2 > 0.3) {
        printf(" Nivel de SO2 elevado. Evite actividades al aire libre.\n");
    }
    if (promedioNO2 > 0.4) {
        printf(" Nivel de NO2 elevado. Restrinja el trafico vehicular.\n");
    }
    if (promedioPM25 > 50) {
        printf(" Nivel de PM2.5 elevado. Uso de mascarillas recomendado.\n");
    }
}

// Guarda los datos en un archivo binario
void guardarDatosEnArchivo(const Registros *registros) {
    FILE *archivo = fopen("aire.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }
    fwrite(registros, sizeof(Registros), 1, archivo);
    fclose(archivo);
    printf("Datos guardados correctamente.\n");
}

// Carga los datos de un archivo binario
void cargarDatosDesdeArchivo(Registros *registros) {
    FILE *archivo = fopen("aire.dat", "rb");
    if (archivo == NULL) {
        printf("No se encontraron datos previos. Se inicializaran los registros.\n");
        inicializarRegistros(registros);
        return;
    }
    fread(registros, sizeof(Registros), 1, archivo);
    fclose(archivo);
    printf("Datos cargados correctamente.\n");
}
void imprimirInformeTabla(const Registros *registros) {
    printf("\n=================================== INFORME DE CALIDAD DEL AIRE ===================================\n");
    printf("%-20s | %-10s | %-10s | %-10s | %-10s | %-10s\n", 
           "ZONA", "DIA", "CO2", "SO2", "NO2", "PM2.5");
    printf("------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < registros->cantidadZonas; i++) {
        Zona *zona = &registros->zonas[i];
        for (int j = 0; j < zona->diasRegistrados; j++) {
            Dia *dia = &zona->dias[j];
            printf("%-20s | %-10d | %-10.2f | %-10.2f | %-10.2f | %-10.2f\n",
                   zona->nombre,
                   j + 1,
                   dia->co2,
                   dia->so2,
                   dia->no2,
                   dia->pm25);
        }
        if (i < registros->cantidadZonas - 1) {
            printf("------------------------------------------------------------------------------------------------\n");
        }
    }
    printf("=================================================================================================\n");
}
