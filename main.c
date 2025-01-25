#include <stdio.h>
#include "funciones.h"

int main() {
    Registros registros;
    cargarDatosDesdeArchivo(&registros);

    int opcion;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Agregar zona\n");
        printf("2. Ingresar datos para una zona\n");
        printf("3. Prediccion para el siguiente dia\n");
        printf("4. Calcular promedio historico\n");
        printf("5. Mostrar historico de 30 dias con recomendaciones\n");
        printf("6. Imprimir informe en formato tabla\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            ingresarZona(&registros);
            break;
        case 2:
            ingresarDatosZona(&registros);
            break;
        case 3:
        prediccionSiguienteDia(&registros);
            break;
        case 4:
            calcularPromedioHistorico(&registros);
            break;
        case 5:
            imprimirHistorico(&registros);
            break;
         case 6:
        imprimirInformeTabla(&registros);
        break;
        case 7:
        guardarDatosEnArchivo(&registros);
        printf("¡Adiós!\n");
        break;
        default:
        printf("Opción no válida.\n");
}
    } while (opcion != 7);

    return 0;
}
