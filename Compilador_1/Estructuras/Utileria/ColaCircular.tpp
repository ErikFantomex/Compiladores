/* Nombre: ColaCircular.tpp
   Autor: Luis Juventino Velasquez H.
   Fecha: 2/03/2020
   Descripción: Archivo de implementación de la clase ColaCircular
*/

#include "ColaCircular.h"

 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

//*************************************************************************************
template <typename T>
ColaCircular<T>::ColaCircular()
{
    ultimo = NULL;
    tam= 0;
}


//*************************************************************************************
template <typename T>
ColaCircular<T>::ColaCircular(const ColaCircular & cc)
{
    ultimo = NULL;
    tam= 0;
    *this = cc;
}


//*************************************************************************************
template <typename T>
ColaCircular<T>::~ColaCircular()
{
    Vaciar();
}


 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/

//*************************************************************************************
template <typename T>
ColaCircular<T> & ColaCircular<T>::operator= (const ColaCircular<T> & cc)
{
    if(this == &cc) return *this;
    Vaciar();

    if(!cc.EstaVacia() )
    {
        Elemento *aux = cc.ultimo ->siguiente ;
        do
        {
            Encolar(aux->val);
            aux = aux->siguiente;
        }while(aux != cc.ultimo->siguiente);
    }

    return *this;
}

 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/
//*************************************************************************************
template <typename T>
void ColaCircular<T>::Encolar (const T & val)
{
    if(EstaVacia() )
    {
        ultimo = new Elemento(val,NULL);
        ultimo -> siguiente = ultimo;
    }
    else
    {

        Elemento *nuevo = new Elemento(val,ultimo->siguiente);
        ultimo->siguiente = nuevo;
        ultimo=nuevo;
    }
    tam++;
}


//*************************************************************************************
template <typename T>
void ColaCircular<T>::Desencolar()
{

    if(EstaVacia() ) throw ColaVacia();


    Elemento* prim = ultimo->siguiente;
    ultimo->siguiente = prim ->siguiente;

    delete prim;
    --tam;
    if(EstaVacia() )
    {
        ultimo=NULL;
    }
}


//*************************************************************************************
template <typename T>
const T & ColaCircular<T>::PrimElemento() const
{

    if(EstaVacia() ) throw ColaVacia();

    return ultimo->siguiente->val;
}


//*************************************************************************************
template <typename T>
const T &  ColaCircular<T>::UltElemento() const
{
    if(EstaVacia() ) throw ColaVacia();
    return ultimo->val;
}

//*************************************************************************************
template <typename T>
bool ColaCircular<T>::EstaVacia() const
{
    return tam==0;
}


//*************************************************************************************
template <typename T>
void ColaCircular<T>::Imprimir() const
{
    std::cout<<'{';

    if(!EstaVacia() )
    {
        Elemento *aux = ultimo ->siguiente ;
        do
        {
            std::cout<< aux->val <<" ,";
            aux = aux->siguiente;
        }while(aux != ultimo->siguiente);
    }
    if(!EstaVacia())  std::cout<<"\b\b ";
    std::cout<<'}';
}


//*************************************************************************************
template <typename T>
void ColaCircular<T>::Vaciar()
{
    while(!EstaVacia() ) Desencolar();
}


//*************************************************************************************
template <typename T>
unsigned int ColaCircular<T>::ObtenerTam() const
{
    return tam;
}


 /*****************************************************************************************
 ************************************   Excepciónes   *************************************
 *****************************************************************************************/

//*************************************************************************************
template <typename T>
const char * ColaCircular<T>::ColaVacia::what() const throw()
{
    return "Cola vac\24a";
}

 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/
template <typename T>
ColaCircular<T>::Elemento::Elemento(T v, Elemento * sig) : val(v), siguiente(sig)
{

}

 /*****************************************************************************************
 *********************************   Funciones Amigas  ************************************
 *****************************************************************************************/
//*************************************************************************************
template <typename t>
std::ostream & operator<<(std::ostream & salida ,const ColaCircular<t> & cc )
{
    cc.Imprimir();
    return salida;

}
