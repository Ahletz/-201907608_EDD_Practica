#include <iostream>
#include <fstream>
#include "json.hpp"

// EJEMPLO DE RUTA: C:/Users/ludwi/OneDrive/Escritorio/EDDv/-201907608_EDD_Practica/Datos.json


using json = nlohmann::json;


//LISTA CIRCULAR DOBLEMENTE ENLAZADA
struct NodoCircularD
{
    //VARIABLES DEL NODO 
    std::string vuelo;
    std::string numero_Registro;
    std::string modelo;
    std::string fabricante;
    int ano_fabricacion;
    int capacidad;
    int peso_maximo;
    std::string aerolinea;
    std::string estado;

    //siguiente y anterior de la lista
    NodoCircularD* next;
    NodoCircularD* prev;

    //constructor del nodo
    NodoCircularD(std::string& vuelo,std::string& numero_Registro, std::string& modelo, std::string& fabricante, int ano_fabricacion, int capacidad, int peso_maximo, std::string& aerolinea, std::string& estado)
    {
        this-> vuelo = vuelo;
        this-> numero_Registro = numero_Registro;
        this-> modelo = modelo;
        this-> fabricante = fabricante;
        this-> ano_fabricacion = ano_fabricacion;
        this-> capacidad = capacidad;
        this-> peso_maximo = peso_maximo;
        this-> aerolinea = aerolinea;
        this-> estado = estado;

        this->next = nullptr;
        this->prev = nullptr;
    }


};

class CircularDoble
{
    //creacion de la cabeza de la lista en clase privada
    private: 
    NodoCircularD* head;

    //metodos publicos de la clase para manipulacion
    public: 
    CircularDoble() //constructor para head -> nullo (vacio)
    {
        head = nullptr;
    }

    void Mostrar() //metodo para mostrar contenido de la lista
    {
        if (head == nullptr)
        {
            std::cout<< "LISTA VACIA, NO SE ENCUENTRA NINGUN ELEMENTO DENTRO!"<< std::endl;
            return;
        }
        NodoCircularD* current = head; //variuable currrent apuntador de la cabeza de la lista

        //ciclo que recorre la lista
        do
        {   
            std::cout<< "-------------------------------------------------------------"<< std::endl;
            std::cout<< "-------------------------------------------------------------"<< std::endl;
            std::cout<<"|| NUMERO DE VUELO: "<<current->vuelo <<std::endl;
            std::cout<<"|| REGISTRO: "<<current->numero_Registro <<std::endl;
            std::cout<<"|| AEROLINEA: "<<current->aerolinea <<std::endl;
            std::cout<<"|| ESTADO: "<<current->estado <<std::endl;
            std::cout<< "-------------------------------------------------------------"<< std::endl;
            std::cout<< "-------------------------------------------------------------"<< std::endl;
            current = current -> next; //cambiamos al siguiente nodo que este apuntando

        } while (current != head); // si la variable ya no apunta a la cabeza y apunta a nulo termina ciclo
        std::cout<< std::endl; //salto de linea
        
        
    }

    //metodo para agregar un nuevo nodo a la lista circular
    void agragar(std::string& vuelo,std::string& numero_Registro, std::string& modelo, std::string& fabricante, int ano_fabricacion, int capacidad, int peso_maximo, std::string& aerolinea, std::string& estado)
    {
        //instanciando el nuevo nodo
        NodoCircularD* newNodo = new NodoCircularD(vuelo, numero_Registro, modelo, fabricante, ano_fabricacion, capacidad, peso_maximo,aerolinea, estado);
        
        if (head == nullptr) //si no hay nodos dentro de la lista
        {
            head = newNodo; //nuevo nodo se vuelve cabeza
            newNodo->next = head; //siguiente que es si mismo
            newNodo->prev = head; //previo que es si mismo

        }else //si existe nodo en la lista 
        {
            NodoCircularD* tail = head->prev; // cola sera el anterior de la cabeza existente
            tail->next = newNodo; // el siguiente de la cola existente sera el nuevo nodo
            newNodo-> prev = tail; // el previo del nuevo nodo es la cola
            newNodo->next = head; //siguiente del nuevo nodo sera la cabeza (null)
            head->prev = newNodo; // el previo de la cabeza sera el nuevo nodo 
        }
        
        

    }

    //metodo para eliminar un nodo en la lista circular 
    void eliminar(const std::string& numero_registro)
    {
        if (head == nullptr) //si no hay nodos en la cola 
        {
            std::cout<<"NO HAY ELEMENTOS PARA ELIMINAR" << std::endl;
            return;
        }

        NodoCircularD* current = head; //current contiene la cabeza de la lista circular
        do
        {
            if (current->numero_Registro == numero_registro) // si encuentra el numero de registro 
            {
                if (current->next == current) //si solo hay un nodo en la lista
                {
                    delete current; //eliminar de la memoria el nodo
                    head = nullptr; //cabeza apunta a nulo
                    return;
                }

                current->prev->next = current->next; //siguiente del anterior ahora sera siguiente
                current->next->prev = current->prev; //anterior del siguiente a hora apunta al previo 
                
                if (current == head)
                {
                    head = current->next;
                    return;
                }
                
                
            }
            current = current->next; //avanzar en la lista
        } while (current != head);
        std::cout<< " AVION CON REGISTRO "<< numero_registro <<" NO ENCONTRADO"<<std::endl;
        
        
    }

    void Reporte() {
        
    // Crear un objeto de salida de archivo
    std::ofstream archivo("listaCircularDoble.dot");

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
        return;
    }

    // Crear una variable string vacía
    std::string contenido;
    int contador = 1;

    contenido += "digraph G {\n"
                        "    rankdir=LR;\n"
                        "    node [shape=record];\n";


     if (head == nullptr)
        {
            std::cout<< "LISTA VACIA, NO SE ENCUENTRA NINGUN ELEMENTO DENTRO!"<< std::endl;
            return;
        }

        NodoCircularD* current = head; //variuable currrent apuntador de la cabeza de la lista

        //ciclo que recorre la lista
        do
        {   

            // Convertir el entero a string
            std::string numeroStr = std::to_string(contador);

            // Definición de los nodos
            std::string aux;

            aux += "node";
            aux += numeroStr;
            aux += " [label=\"<prev> | {";
            aux += current->vuelo;
            aux += "|";
            aux += current->numero_Registro;
            aux += "} | <next>\"];\n";  

            
            contador ++; //aumenta contador

            contenido += aux;

            current = current -> next; //cambiamos al siguiente nodo que este apuntando

        } while (current != head); // si la variable ya no apunta a la cabeza y apunta a nulo termina ciclo

        int contador2 =1;
        do
        {
            int num1;
            int num2;
            std::string aux;

            num1 = contador2;
            num2 = contador2+1;

            // Convertir el entero a string
            std::string numeroStr1 = std::to_string(num1);
            std::string numeroStr2 = std::to_string(num2);

            aux += std::string("nodo") + numeroStr1 + ":next -> node" + numeroStr2 + ":prev;\n" ;
            aux += std::string("nodo") + numeroStr2 + ":prev -> node" + numeroStr1 + ":next;\n" ;

            contador2 ++;
            contenido += aux;   

        } while (contador2 != contador);

        std::string fin = std::to_string(contador);

        contenido += std::string("nodo") + fin+ ":next -> node1:prev;\n" ;
        contenido += std::string("nodo1") + ":prev -> node" + fin + ":next;\n}" ;
        
    

    // Escribir el contenido en el archivo
    archivo << contenido;

    // Cerrar el archivo
    archivo.close();

    std::cout << "El archivo se escribió correctamente." << std::endl;
}

};


//COLA DE PASAJEROS

// Estructura para almacenar los datos del pasajero
struct Pasajero {

    //
    std::string nombre;
    std::string nacionalidad;
    std::string numeroPasaporte;
    std::string vuelo;
    int asiento;
    std::string destino;
    std::string origen;
    int equipajeFacturado;

    //siguiente en la cola
    Pasajero* siguiente;

    //constructor
    Pasajero(std::string nombre, std::string nacionalidad, std::string numeroPasaporte, std::string vuelo,int asiento, std::string destino, std::string origen, int equipajeFacturado)
    {
        this-> nombre = nombre;
        this-> nacionalidad = nacionalidad;
        this-> numeroPasaporte = numeroPasaporte;
        this-> vuelo = vuelo;
        this-> asiento = asiento;
        this-> destino = destino;
        this-> origen = origen;
        this-> equipajeFacturado = equipajeFacturado;

        this-> siguiente = nullptr;
    }
};

// Clase para la cola
class Cola {

private:
    Pasajero* frente; //primer pasajero
    Pasajero* fondo; //ultimo pasajero

public:

    Cola() : frente(nullptr), fondo(nullptr) {}

    // Método para agregar un pasajero a la cola
    void agregar(std::string nombre, std::string nacionalidad, std::string numeroPasaporte, std::string vuelo, int asiento, std::string destino, std::string origen, int equipajeFacturado) {
        Pasajero* nuevoPasajero = new Pasajero(nombre, nacionalidad, numeroPasaporte, vuelo, asiento, destino, origen, equipajeFacturado);
        if (fondo == nullptr) {
            frente = fondo = nuevoPasajero;
        } else {
            fondo->siguiente = nuevoPasajero;
            fondo = nuevoPasajero;
        }
    }

    // Método para eliminar un pasajero de la cola
    void eliminar() {
        if (frente == nullptr) {
            std::cout << "La cola está vacía. No se puede eliminar." << std::endl;
            return;
        }
        Pasajero* temp = frente;
        frente = frente->siguiente;
        if (frente == nullptr) {
            fondo = nullptr;
        }
        delete temp;
    }

    // Método para mostrar los pasajeros en la cola
    void mostrar() {
        if (frente == nullptr) {
           std::cout << "La cola está vacía." << std::endl;
            return;
        }
        Pasajero* temp = frente;
        while (temp != nullptr) {
            std::cout << "Nombre: " << temp->nombre << ", Nacionalidad: " << temp->nacionalidad << ", Número de Pasaporte: " << temp->numeroPasaporte
                 << ", Vuelo: " << temp->vuelo << ", Asiento: " << temp->asiento << ", Destino: " << temp->destino
                 << ", Origen: " << temp->origen << ", Equipaje Facturado: " << temp->equipajeFacturado << std::endl;
            temp = temp->siguiente;
        }
    }

    // Método para buscar y mostrar un pasajero por su número de pasaporte
    void buscarPasajero(const std::string &numeroPasaporte) {
        if (frente == nullptr) {
            std::cout << "La cola está vacía." << std::endl;
            return;
        }
        Pasajero* temp = frente;
        while (temp != nullptr) {
            if (temp->numeroPasaporte == numeroPasaporte) {
                std::cout << "Pasajero encontrado:" << std::endl;
                std::cout << "Nombre: " << temp->nombre << ", Nacionalidad: " << temp->nacionalidad << ", Número de Pasaporte: " << temp->numeroPasaporte
                          << ", Vuelo: " << temp->vuelo << ", Asiento: " << temp->asiento << ", Destino: " << temp->destino
                          << ", Origen: " << temp->origen << ", Equipaje Facturado: " << temp->equipajeFacturado << std::endl;
                return;
            }
            temp = temp->siguiente;
        }
        std::cout << "Pasajero con número de pasaporte " << numeroPasaporte << " no encontrado." << std::endl;
    }


};


// Nodo para la pila
struct NodoPila {
    Pasajero pasajero;
    NodoPila* siguiente;

    NodoPila(Pasajero p) : pasajero(p), siguiente(nullptr) {}
};

// Clase para la pila
class Pila {
private:
    NodoPila* tope;

public:
    Pila() : tope(nullptr) {}

    // Método para agregar un pasajero a la pila
    void agregar(Pasajero pasajero) {
        NodoPila* nuevoNodo = new NodoPila(pasajero); //crea un nuevo pasajero en la pila
        nuevoNodo->siguiente = tope;
        tope = nuevoNodo;
    }

    // Método para eliminar un pasajero de la pila
    void eliminar() {
        if (tope == nullptr) {
            std::cout << "La pila está vacía. No se puede eliminar." << std::endl;
            return;
        }
        NodoPila* temp = tope;
        tope = tope->siguiente;
        delete temp;
    }

    // Método para mostrar los pasajeros en la pila
    void mostrar() {
        if (tope == nullptr) {
            std::cout << "La pila está vacía." << std::endl;
            return;
        }
        NodoPila* temp = tope;
        while (temp != nullptr) {
            std::cout << "Nombre: " << temp->pasajero.nombre << ", Nacionalidad: " << temp->pasajero.nacionalidad << ", Número de Pasaporte: " << temp->pasajero.numeroPasaporte
                 << ", Vuelo: " << temp->pasajero.vuelo << ", Asiento: " << temp->pasajero.asiento << ", Destino: " << temp->pasajero.destino
                 << ", Origen: " << temp->pasajero.origen << ", Equipaje Facturado: " << temp->pasajero.equipajeFacturado << std::endl;
            temp = temp->siguiente;
        }
    }
};


// Nodo para la lista enlazada doble
struct NodoListaDoble {

    Pasajero pasajero;
    NodoListaDoble* anterior;
    NodoListaDoble* siguiente;

    NodoListaDoble(Pasajero p) : pasajero(p), anterior(nullptr), siguiente(nullptr) {}
};

// Clase para la lista enlazada doble
class ListaEnlazadaDoble {
private:
    NodoListaDoble* cabeza;

public:
    ListaEnlazadaDoble() : cabeza(nullptr) {}

    // Método para agregar un pasajero al final de la lista
    void agregarAlFinal(Pasajero pasajero) {
        NodoListaDoble* nuevoNodo = new NodoListaDoble(pasajero);
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            NodoListaDoble* temp = cabeza;
            while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoNodo;
            nuevoNodo->anterior = temp;
        }
    }

    // Método para eliminar un pasajero de la lista
    void eliminar(NodoListaDoble* nodo) {
        if (nodo == nullptr) {
            std::cout << "El nodo no existe en la lista." << std::endl;
            return;
        }
        if (nodo == cabeza) {
            cabeza = nodo->siguiente;
        }
        if (nodo->anterior != nullptr) {
            nodo->anterior->siguiente = nodo->siguiente;
        }
        if (nodo->siguiente != nullptr) {
            nodo->siguiente->anterior = nodo->anterior;
        }
        delete nodo;
    }

    // Método para mostrar los pasajeros en la lista
    void mostrar() {
        if (cabeza == nullptr) {
            std::cout << "La lista está vacía." << std::endl;
            return;
        }
        NodoListaDoble* temp = cabeza;
        while (temp != nullptr) {
            std::cout << "Nombre: " << temp->pasajero.nombre << ", Nacionalidad: " << temp->pasajero.nacionalidad << ", Número de Pasaporte: " << temp->pasajero.numeroPasaporte
                 << ", Vuelo: " << temp->pasajero.vuelo << ", Asiento: " << temp->pasajero.asiento << ", Destino: " << temp->pasajero.destino
                 << ", Origen: " << temp->pasajero.origen << ", Equipaje Facturado: " << temp->pasajero.equipajeFacturado << std::endl;
            temp = temp->siguiente;
        }
    }
};

//INICIALIZACION ESTRUCTURAS 
CircularDoble Lista1;
CircularDoble Lista2;
Cola Pasajeros;


json leerJSON_Aviones() {
    
    std::string documento; //variable con nombre del documento

    std::cout << "INGRESE LA RUTA DEL ARCHIVO: " << std::endl;
    std::cin >> documento; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

    std::cout << "ruta: " <<documento<< std::endl;

    std::ifstream inputFile(documento);
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
    for (const auto& aviones : jsonData) {

        //OBTENER LOS ELEMENTOS DEL JSON AVIONES
        std::string vuelo = aviones["vuelo"];
        std::string numero_Registro = aviones["numero_de_registro"];
        std::string modelo = aviones["modelo"];
        std::string fabricante = aviones["fabricante"];
        int ano_fabricacion = aviones["ano_fabricacion"];
        int capacidad = aviones["capacidad"];
        int peso_maximo = aviones["peso_max_despegue"];
        std::string aerolinea = aviones["aerolinea"];
        std::string estado = aviones["estado"];

        /*

        std::cout<< "-------------------------------------------------------------"<< std::endl;
        std::cout<< vuelo<< std::endl;
        std::cout<< numero_Registro<< std::endl;
        std::cout<< modelo<< std::endl;
        std::cout<< fabricante<< std::endl;
        std::cout<< ano_fabricacion<< std::endl;
        std::cout<< capacidad<< std::endl;
        std::cout<< peso_maximo<< std::endl;
        std::cout<< aerolinea<< std::endl;
        std::cout<< estado<< std::endl;
        std::cout<< "-------------------------------------------------------------"<< std::endl;

        */

        //AGREGAR LOS ELEMENTOS DEL JSON A LA LISTA DOBLE CIRCULAR
        //Aviones.agregar(vuelo, numero_Registro, modelo, fabricante, ano_fabricacion, capacidad, peso_maximo, aerolinea, estado);
        

        if (estado == "Disponible")
        {
            Lista1.agragar(vuelo, numero_Registro, modelo, fabricante, ano_fabricacion, capacidad, peso_maximo, aerolinea, estado);
        }else
        {
            Lista2.agragar(vuelo, numero_Registro, modelo, fabricante, ano_fabricacion, capacidad, peso_maximo, aerolinea, estado);
        }
        
        
        
    }

    Lista1.Mostrar();

    Lista2.Mostrar();

     return jsonData; // Retornar los datos JSON leídos

}

json leerJSON_Pasajeros() {
    
    std::string documento; //variable con nombre del documento

    std::cout << "INGRESE LA RUTA DEL ARCHIVO: " << std::endl;
    std::cin >> documento; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

    std::cout << "ruta: " <<documento<< std::endl;

    std::ifstream inputFile(documento);
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
    for (const auto& pasajero : jsonData) {

        //OBTENER LOS ELEMENTOS DEL JSON AVIONES
        std::string nombre = pasajero["nombre"];
        std::string nacionalidad = pasajero["nacionalidad"];
        std::string numero_pasaporte = pasajero["numero_de_pasaporte"];
        std::string vuelo = pasajero["vuelo"];
        int asiento = pasajero["asiento"];
        int equipaje = pasajero["equipaje_facturado"];
        std::string destino = pasajero["destino"];
        std::string origen = pasajero["origen"];

        Pasajeros.agregar(nombre, nacionalidad, numero_pasaporte,vuelo,asiento,destino,origen,equipaje);
    }


    Pasajeros.mostrar();
     return jsonData; // Retornar los datos JSON leídos

}


// Función para leer un archivo de texto y mostrar su contenido
void leerArchivo() {

    std::string documento; //variable con nombre del documento

    std::cout << "INGRESE LA RUTA DEL ARCHIVO: " << std::endl;
    std::cin >> documento; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

    std::cout << "ruta: " <<documento<< std::endl;

    std::ifstream archivo(documento);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << documento << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::cout << linea << std::endl; //lee la linea 

        std::string lineaProcesada = linea;
    
        // Eliminar espacios
        trim(lineaProcesada);

        // Verificar y procesar la línea
        if (lineaProcesada == "IngresoEquipajes;") {

            std::cout << "Línea de tipo: IngresoEquipajes" << std::endl;

        } else if (lineaProcesada.substr(0, 19) == "MantenimientoAviones") {
        // Separar los campos
        std::stringstream ss(lineaProcesada);
        std::string segmento;
        std::vector<std::string> segmentos;

        while (std::getline(ss, segmento, ',')) {
            segmentos.push_back(segmento);
        }

        // Verificar que la línea tenga los 3 segmentos esperados y termine con ';'
        if (segmentos.size() == 3 && segmentos[2].back() == ';') {
            segmentos[2].pop_back(); // Eliminar el ';' final

            // Identificar si es Ingreso o Salida
            std::string tipo = segmentos[1];
            std::string identificador = segmentos[2];

            if (tipo == "Ingreso" || tipo == "Salida") {
                std::cout << "Línea de tipo: MantenimientoAviones" << std::endl;
                std::cout << "Tipo: " << tipo << std::endl;
                std::cout << "Identificador: " << identificador << std::endl;
            } else {
                std::cout << "Línea desconocida o con formato incorrecto" << std::endl;
            }
        } else {
            std::cout << "Línea desconocida o con formato incorrecto" << std::endl;
        }
    } else {
        std::cout << "Línea desconocida o con formato incorrecto" << std::endl;
    }


    }

    archivo.close();
}

void trim(std::string &str) {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}




int main(int argc, char const *argv[])
{   

    bool exit = true; // VARIABLE DE SALIDA DEL CICLO
    int seleccion; //variable seleccion de menu
    std::string pasaporte; //variable con numero de pasaporte
    
   

    while (exit)
    {
        std::cout << "||---------- Menu ----------||" << std::endl;
        std::cout << "|| 1. CARGAR AVIONES.       ||" << std::endl; //CARGA COMPLETADA
        std::cout << "|| 2. CARGAR PASAJEROS.     ||" << std::endl; //carga completa
        std::cout << "|| 3. CARGA DE MOVIMIENTOS. ||" << std::endl; //completo
        std::cout << "|| 4. CONSULTA PASAJEROS.   ||" << std::endl; //consulta completa
        std::cout << "|| 5. VISUALIZAR REPORTES.  ||" << std::endl;
        std::cout << "|| 6. SALIR.                ||" << std::endl; //funciona

        std::cin >> seleccion; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

        if (seleccion == 6)
        {
            exit = false;
        }

        switch (seleccion)
        {
        case 1:
            try {
                    json avionesData = leerJSON_Aviones();
            } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                return 1;
            }

            break;
        case 2:
            try {
                    json pasajerosData = leerJSON_Pasajeros();
            } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                return 1;
            }
            break;
        case 3:
            /* code */
            break;
        case 4:

            std::cout << "INGRESE EL NUMERO DE PASAPORTE: " << std::endl;
            std::cin >> pasaporte; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

            std::cout << "BUSCANDO EL PASAPORTE: " <<pasaporte<< std::endl;
            Pasajeros.buscarPasajero(pasaporte);

            break;
        case 5:
            /* code */
            break;
        
        default:

            std::cout << " NO INGRESO UNA OPCION VALIDA! " << std::endl;

            break;
        }
    }
    
    
    
    return 0;
}


