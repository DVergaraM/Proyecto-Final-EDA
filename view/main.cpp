#include "../controller/controller.h"


void menu() {
    int opcion;
    do {
        // Mostrar el menú principal
        cout << "\n-- Menú Principal --" << endl;
        cout << "1. Crear actividad recurrente" << endl;
        cout << "2. Organizar responsables de tareas por nombre" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        // Ejecutar la función correspondiente según la opción seleccionada
        switch (opcion) {
            case 1:
                actividades_recurrentes();
                break;
            case 2:
                responsables_por_nombre(); // FIXME: Ponerle parametrós a la función.
                break;
            case 3:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
        }
    } while (opcion != 3);
}

int main() {
    return 0;
}


