/*
Horacio Araiza Gonzalez
Tarea 3 Estructura de Datos

*/

#include "Pila.h"

//*********************
//  CONSTRUCTORES:    *
//*********************

template <typename T>
Pila<T>::Pila(): tope(NULL), numElem(0){} //Agregamos inicializadores.

template <typename T>
Pila<T>::Pila(const Pila<T> &p): tope(NULL), numElem(0) //Nuevamente usamos inicializadores.
{
    //Esta es nuestra Pila que llama a la instancia que despu�s se vuelve igual a la Pila que llam� previamente.
    *this = p;
}

template <typename T>
Pila<T> & Pila<T>::operator=(const Pila<T> &p)
{
    //Para nada m�s la que ya est�, entonces devolvemos esa y termina el proceso.
    if(&p == this) return *this;
    //Declaramos una Pila auxilair.
    Pila<T> pAux;
    //Vaciamos para destruir la Pila previamente puesta.
    Vaciar();
    //Ciclo for para que auxiliar tome el valor del siguiente elemento que se encuentra
    //en nuestra Pila.
    for (Elemento *aux = p.tope; aux != NULL; aux = aux->siguiente)
        pAux.Apilar(aux->valor);
    //Apilamos a nuestra Pila auxiliar.
    for (Elemento *aux = pAux.tope; aux != NULL; aux = aux->siguiente)
        Apilar(aux->valor);
    //Retornamos a lo que apunta this, que ser�a nuestros elementos nuevos guardados en ese puntero.
    return *this;
}

template <typename T>
Pila<T>::~Pila()
{
    //Para el destructor simplemente necesitamos vaciar a la Pila, ya que esta funci�n de la clase
    //es precisamente lo que hace: eliminar los elementos que existan en esa Pila dentro de nuestra
    //memoria, as� que es todo lo que necesita. Es debido a c�mo est� construida la funci�n "Vaciar()".
    Vaciar();
}

template <typename T>
void Pila<T>::Apilar(const T & valor)
{
    //Declaramos en Elemento un puntero para nuevo para crear un nuevo
    //Elemento que contenga el valor y tope de nuestra Pila.
    Elemento *nuevo = new Elemento(valor, tope);
    tope = nuevo;//Declaramos que el tope es el nuevo elemento a Apilar en nuestra Pila.
    //Y le sumamos de uno en uno de los n�meros de elemento.
    ++numElem;
}

template <typename T>
void Pila<T>::Desapilar()
{
    //Si la pila ya se encuentra vac�a, no hay necesidad alguna de continuar con un
    //proceso, as� que s�lo tiramos una excepci�n. :)
    if(EstaVacia()) throw "No es posible desapilar ya que su pila ya se encuentra vac\241a.";
    //Guardamos el tope en un auxiliar, para poder liberar la memoria despu�sito. :D
    Elemento *aux = tope;
    //El tope pasa a ser el elemento que ten�a antes de �ste mismo.
    tope = tope->siguiente;
    //Liberamos la memoria del tope mencionado anteriormente.
    delete aux;
    //Y restamos de uno en uno al n�mero de elemento. :)
    --numElem;
}

template <typename T>
const T & Pila<T>::ObtenerTope() const
{
    //Checamos si nuestra Pila no se encuentra vac�a, si es as�, s�lo le indicamos eso al
    //usuario y no hacemos nada.
    if(EstaVacia()) throw "Su pila est\240 vac\241a, no hay ning\243n valor en el tope. :(";
    //Sino, retornamos el valor que se encuentra en el tope. C:
    return tope->valor;
}

template <typename T>
bool Pila<T>::EstaVacia() const
{
    //Si no existe nada en el tope, entonces eso quiere decir que nuestra Pila se encuentra
    //vac�a. Esto es m�s seguro que numElemento ya que numElemento es m�s como un atributo
    //auxiliar y el tope es m�s seguro que determine si nuestra Pila se encuentra vac�a o no
    //entonces, eso es lo que retornamos.
    return (tope == NULL);
}

template <typename T>
void Pila<T>::Vaciar()
{
   //Mientras nuestra Pila no se encuentre vac�a, entonces pasamos a desapilar, es todo.
    while(!EstaVacia())
        Desapilar();
}

template <typename T>
unsigned Pila<T>::ObtenerTam() const
{
    //Retornamos el n�mero de elementos que se encuentran en nuestra Pila para que el usuario sepa el tama�o.
    return numElem;
}

template <typename T>
void Pila<T>::Imprimir() const
{
    //Si nuestra Pila se encuentra vac�a no hay necesidad de imprimir otro mensaje que no sea ese.
    if(EstaVacia()){
        std::cout << "\nSu pila est\240 vac\241a. :D" << std::endl << std::endl;
    }
    //Sino, pasamos a imprimir cada uno de los elementos que se encuentra en nuestra Pila.
    else{
        //Declaramos el puntero auxiliar igual al tope de nuestra Pila y que comenzar� en el mismo tope.
        Elemento *aux = tope;
        std::cout << "Tope = ";//Imprimimos el valor del tope
        //Y creamos un ciclo while, en donde mientras el auxiliar sea distinto
        //de NULL, entonces ir� imprimiendo cada uno de los valores que se encuentran
        //en nuestra Pila. Siguiendo por supuesto un formato de impresi�n. :)
        while (aux != NULL){
            //Flechita que nos va indicando elemento por elemento de abajo hacia arriba.
            std::cout << aux->valor << " <- ";
            //Auxiliar que ahora va siguiendo el siguiente valor.
            aux = aux->siguiente;
        }
        std::cout << "\b\b\b  " << std::endl << std::endl; //Imprimimos espacios, por simple est�tica.
    }
}

template <typename T>
void Pila<T>::ImprimeInformacion() const
{
    //Esto es para el formato de pruebas.
    std::cout << "N\243mero de elementos: " << numElem << std::endl;
    Imprimir();
}
