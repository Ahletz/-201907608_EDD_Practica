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
            std::cout<<"|| NUMERO DE VUELO: "<<current->vuelo <<std::endl;
            std::cout<<"|| REGISTRO: "<<current->numero_Registro <<std::endl;
            std::cout<<"|| AEROLINEA: "<<current->aerolinea <<std::endl;
            std::cout<<"|| ESTADO: "<<current->estado <<std::endl;
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


