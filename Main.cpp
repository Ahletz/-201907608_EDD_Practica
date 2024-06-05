#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

json leerJSON() {
    std::ifstream inputFile("C:/Users/ludwi/OneDrive/Escritorio/EDD VACAS/-201907608_EDD_Practica/Datos.json");
    json jsonData;

    if (inputFile.is_open()) {
        inputFile >> jsonData;
        inputFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << std::endl;
        throw std::runtime_error("Archivo no encontrado");
    }

     // Mostrar el contenido del JSON
    //std::cout << jsonData.dump(4) << std::endl;

    // Acceder a los elementos del JSON
    std::string nombre = jsonData["nombre"];
    int edad = jsonData["edad"];
    std::vector<std::string> amigos = jsonData["amigos"].get<std::vector<std::string>>();

    std::cout << nombre << std::endl;
    std::cout << edad << std::endl;

    return jsonData;
}

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
            leerJSON();
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


