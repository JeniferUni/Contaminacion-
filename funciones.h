#ifndef FUNCIONES_H
#define FUNCIONES_H

#define DIAS_MES 30
#define MAX_ZONAS 10 

// Coeficientes para cada parámetro
#define CO2_COEF 0.5
#define SO2_COEF 0.8
#define NO2_COEF 1.2
#define PM25_COEF 1.5
#define TEMPERATURA_COEF 0.3
#define VIENTO_COEF 0.5
#define HUMEDAD_COEF 0.2

// Estructuras
typedef struct {
    float co2, so2, no2, pm25;
} Dia;

typedef struct {
    char nombre[50];
    Dia dias[DIAS_MES];
    int diasRegistrados; // Contador de días registrados
} Zona;

typedef struct {
    Zona zonas[MAX_ZONAS];
    int cantidadZonas; // Número de zonas registradas
} Registros;

// Prototipos
void inicializarRegistros(Registros *registros);
void ingresarZona(Registros *registros);
void ingresarDatosZona(Registros *registros);
void prediccionSiguienteDia(const Registros *registros);
void calcularPromedioHistorico(const Registros *registros);
void imprimirHistorico(const Registros *registros);  // Función para imprimir el histórico con recomendaciones
void guardarDatosEnArchivo(const Registros *registros);
void cargarDatosDesdeArchivo(Registros *registros);
void imprimirInformeTabla(const Registros *registros);

#endif
