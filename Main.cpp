#include <iostream>

int main(int argc, char const *argv[])
{   

    bool exit = true; // VARIABLE DE SALIDA DEL CICLO
    int seleccion; //variable seleccion de menu
   

    while (exit)
    {
        std::cout << "||---------- Menu ----------||" << std::endl;
        std::cout << "|| 1. CARGAR AVIONES.       ||" << std::endl;
        std::cout << "|| 2. CARGAR PASAJEROS.     ||" << std::endl;
        std::cout << "|| 3. CARGA DE MOVIMIENTOS. ||" << std::endl;
        std::cout << "|| 4. CONSULTA PASAJEROS.   ||" << std::endl;
        std::cout << "|| 5. VISUALIZAR REPORTES.  ||" << std::endl;
        std::cout << "|| 6. SALIR.                ||" << std::endl;

        std::cin >> seleccion; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

        if (seleccion == 6)
        {
            exit = false;
        }

        switch (seleccion)
        {
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            /* code */
            break;
        case 6:
            /* code */
            break;
        
        default:

            std::cout << " NO INGRESO UNA OPCION VALIDA! " << std::endl;

            break;
        }
    }
    
    
    
    return 0;
}
