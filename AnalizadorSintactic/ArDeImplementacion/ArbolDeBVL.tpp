/* Nombre: ArbolDeBVL.tpp
   Autor: Luis Juventino Velasquez H.
   Fecha: 19/04/21
   Descripción: Archivo de implementación de la clase 'ArbolDeBVL'
*/

#include"../ArbolDeBVL.h"


 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

//*************************************************************************************
template<typename T>
ArbolDeBVL<T>::ArbolDeBVL() : raiz(NULL),nNodos(0){}


//*************************************************************************************
template<typename T>
ArbolDeBVL<T>::ArbolDeBVL(const ArbolDeBVL & abb) : raiz(NULL),nNodos(0)
{
    *this=abb;
}


//*************************************************************************************
template<typename T>
ArbolDeBVL<T>::~ArbolDeBVL()
{
    Vaciar();
}


 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/
//*************************************************************************************
template<typename T>
ArbolDeBVL<T> & ArbolDeBVL<T>::operator= (const ArbolDeBVL<T> & abb)
{
    if(this == & abb) return *this;
    Vaciar();

    if(abb.raiz != NULL)
    {
        Nodo * aux;
        ColaCircular< ArbolDeBVL<T>::Nodo* > cola;
        cola.Encolar(abb.raiz);
        while(!cola.EstaVacia())
        {

            aux= cola.PrimElemento();
            Agregar(aux->val);
            cola.Desencolar();

            if(aux->izq != NULL) cola.Encolar(aux->izq);
            if(aux->der != NULL) cola.Encolar(aux->der);
        }
    }


    return *this;
}

 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/

//*************************************************************************************
template<typename T>
bool ArbolDeBVL<T>::Agregar(const T & eNodo)
{
    return Agregar(raiz,eNodo);
}


//*************************************************************************************
template<typename T>
bool ArbolDeBVL<T>::Eliminar(const T & eNodo)
{
    return Eliminar(raiz,eNodo);
}


//*************************************************************************************
template<typename T>
T ArbolDeBVL<T>::Buscar(const T & eNodo) const
{
    Nodo *subArbol = raiz;
    while(subArbol != NULL)
    {
        if(subArbol->val == eNodo) return subArbol->val;
        else
        {
            if(subArbol->val > eNodo) subArbol = subArbol->izq;
            else subArbol = subArbol->der;
        }
    }
    throw NodoNoEncontrado();
}


//*************************************************************************************
template<typename T>
unsigned ArbolDeBVL<T>::NumeroDeNodos() const
{
    return nNodos;
}


//*************************************************************************************
template<typename T>
unsigned ArbolDeBVL<T>::ObtenerAltura() const
{
    if(raiz == NULL) return 0;
    else return raiz->tam;
}


//*************************************************************************************
template<typename T>
bool ArbolDeBVL<T>::PodarNodo(const T & eNodo)
{
    return PodarNodo(raiz,eNodo);
}


//*************************************************************************************
template<typename T>
bool ArbolDeBVL<T>::Vaciar()
{
    if(nNodos == 0) return false;
    PodarNodo(raiz,raiz->val);
    return true;
}


//*************************************************************************************
template<typename T>
void ArbolDeBVL<T>::Imprimir(Recorrido tipo /*=ASCENDENTE*/,std::ostream & salida/*=std::cout*/) const
{
    if(raiz == NULL) return;
    switch(tipo)
    {
        case ASCENDENTE:
            ImprAscendente(raiz,salida);
            break;
        case DESCENDENTE:
            ImprDescendente(raiz,salida);
            break;
        case PORNIVEL:
            ImprPorNivel(raiz,salida);
            break;
        case POSORDEN:
            ImprPosOrden(raiz,salida);
            break;
        case PREORDEN:
            ImprPreOrden(raiz,salida);
            break;
    }
    salida<<"\b,\b ";
}




/*****************************************************************************************
************************************   Excepciónes   *************************************
*****************************************************************************************/
//*************************************************************************************
template <typename T>
const char * ArbolDeBVL<T>::NodoNoEncontrado::what() const throw()
{
    return "No existe el nodo buscado...";
}


 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/
//*************************************************************************************
template<typename T>
ArbolDeBVL<T>::Nodo::Nodo(const T &e, Nodo * iz/*=NULL*/, Nodo * de/*=NULL*/) :
    val(e),tam(1),der(de),izq(iz){}


//*************************************************************************************
template<typename T>
void ArbolDeBVL<T>::Nodo::ActAltura()
{
    unsigned subDer;
    unsigned subIzq;

    if(der == NULL) subDer = 0;
    else subDer = der->tam;
    if(izq == NULL ) subIzq = 0;
    else subIzq = izq->tam;

    tam = subDer > subIzq ? subDer+1 : subIzq+1;
}


//*************************************************************************************
template<typename T>
int ArbolDeBVL<T>::Nodo::Balance()
{
    unsigned subDer;
    unsigned subIzq;

    if(der == NULL) subDer = 0;
    else subDer = der->tam;
    if(izq == NULL ) subIzq = 0;
    else subIzq = izq->tam;

    return subDer - subIzq;
}


//*************************************************************************************
template<typename T>
 typename ArbolDeBVL<T>::Nodo *& ArbolDeBVL<T>::Mayor(Nodo *&subRaiz)
{
    if( subRaiz->der != NULL) return  Mayor(subRaiz->der);
    else return subRaiz;
}

//*************************************************************************************
template<typename T>
int ArbolDeBVL<T>::Nodo::TNodo()
{
    if(der != NULL)
    {
        if(izq != NULL) return 3;
        else return 2;
    }
    else
    {
        if(izq != NULL) return 1;
        else return 0;
    }
}


//*************************************************************************************
template<typename T>
bool ArbolDeBVL<T>::Agregar(Nodo *&subRaiz,const T & eNodo)
{
    bool resultado;
    if(subRaiz == NULL)
    {
        subRaiz = new Nodo(eNodo);
        ++nNodos;
        return true;
    }
    if(subRaiz->val == eNodo) return false;
    if(subRaiz->val > eNodo)
    {
        resultado=Agregar(subRaiz->izq,eNodo);
        if(resultado) Balancear(subRaiz,false);
    }
    else
    {
        resultado=Agregar(subRaiz->der,eNodo);
        if(resultado) Balancear(subRaiz,true);
    }
    subRaiz->ActAltura();
    return resultado;
}


//*************************************************************************************
template<typename T>
bool ArbolDeBVL<T>::Eliminar(Nodo *&subRaiz,const T& eNodo)
{
    bool resultado;
    if(subRaiz == NULL) return false;

    if(subRaiz->val == eNodo)
    {
        Nodo * porSalir=subRaiz;
        switch(subRaiz->TNodo())
        {
            case 0:
                subRaiz = NULL;
                break;

            case 1:
                subRaiz= subRaiz->izq;
                break;

            case 2:
                subRaiz= subRaiz->der;
                break;

            case 3:
                T auxMay = Mayor(subRaiz->izq)->val;

                Eliminar(subRaiz,auxMay);
                subRaiz->val = auxMay;

                subRaiz->ActAltura();
                Balancear(subRaiz,true);
                return true;
                break;
        }
        delete porSalir;
        --nNodos;
        return true;
    }
    else
    {
        if(subRaiz->val > eNodo)
        {
            resultado=Eliminar(subRaiz->izq,eNodo);
            if(resultado) Balancear(subRaiz,true);
        }
        else
        {
            resultado=Eliminar(subRaiz->der,eNodo);
            if(resultado) Balancear(subRaiz,false);
        }
    }

    subRaiz->ActAltura();
    return resultado;
}


//*************************************************************************************
template<typename T>
bool ArbolDeBVL<T>::PodarNodo(Nodo *&subRaiz,const T &eNodo)
{
    bool resultado;
    if(subRaiz == NULL) return false;

    if(subRaiz->val == eNodo)
    {
        if(subRaiz->der != NULL)PodarNodo(subRaiz->der,subRaiz->der->val);
        if(subRaiz->izq != NULL)PodarNodo(subRaiz->izq,subRaiz->izq->val);

        delete subRaiz;
        subRaiz=NULL;
        --nNodos;
        return true;
    }
    else
    {
        if(subRaiz->val > eNodo)
        {
            resultado=PodarNodo(subRaiz->izq,eNodo);
            if(resultado) Balancear(subRaiz,true);
        }
        else
        {
            resultado=PodarNodo(subRaiz->der,eNodo);
            if(resultado) Balancear(subRaiz,false);
        }
    }

    subRaiz->ActAltura();
    return resultado;
}


//*************************************************************************************
template<typename T>
void ArbolDeBVL<T>::ImprAscendente(Nodo *subRaiz, std::ostream & salida/*=std::cout*/)const
{
    if(subRaiz == NULL) return;
    ImprAscendente(subRaiz->izq,salida);
    salida<<subRaiz->val<<" ,";
    ImprAscendente(subRaiz->der,salida);
}


//*************************************************************************************
template<typename T>
void ArbolDeBVL<T>::ImprDescendente(Nodo *subRaiz, std::ostream & salida/*=std::cout*/)const
{
    if(subRaiz == NULL) return;

    ImprDescendente(subRaiz->der,salida);
    salida<<subRaiz->val<<" ,";
    ImprDescendente(subRaiz->izq,salida);
}


//*************************************************************************************
template<typename T>
void ArbolDeBVL<T>::ImprPorNivel(Nodo *subRaiz, std::ostream & salida/*=std::cout*/)const
{
    Nodo * aux;
    ColaCircular< ArbolDeBVL<T>::Nodo* > cola;
    cola.Encolar(raiz);
    while(!cola.EstaVacia())
    {
        for(int i=cola.ObtenerTam(); i>0 ;--i)
        {
            aux= cola.PrimElemento();
            cola.Desencolar();
            salida<<aux->val<<" ,";
            if(aux->izq != NULL) cola.Encolar(aux->izq);
            if(aux->der != NULL) cola.Encolar(aux->der);
        }
        salida<<'\n';

    }
}


//*************************************************************************************
template<typename T>
void ArbolDeBVL<T>::ImprPosOrden(Nodo *subRaiz, std::ostream & salida/*=std::cout*/)const
{
    if(subRaiz == NULL) return;

    ImprPosOrden(subRaiz->izq,salida);
    ImprPosOrden(subRaiz->der,salida);
    salida<<subRaiz->val<<" ,";
}


//*************************************************************************************
template<typename T>
void ArbolDeBVL<T>::ImprPreOrden(Nodo *subRaiz, std::ostream & salida/*=std::cout*/)const
{
    if(subRaiz == NULL) return;

    salida<<subRaiz->val<<" ,";
    ImprPreOrden(subRaiz->izq,salida);
    ImprPreOrden(subRaiz->der,salida);
}


//*************************************************************************************
template<typename T>
bool ArbolDeBVL<T>::Balancear(Nodo *&subRaiz, bool derecho)
{
    int bal = subRaiz->Balance();
    int balHijo;

    if( !(bal >= -1 && bal <= 1) )
    {
        if(derecho) balHijo=subRaiz->der->Balance();
        else balHijo=subRaiz->izq->Balance();

        if(bal >= 2 && balHijo == -1)  RDI(subRaiz);
        else if(bal <= -2 && balHijo == 1) RDD(subRaiz);
        else if((bal >= 2 && balHijo == 1) || (bal >= 2 && balHijo == 0)) RSI(subRaiz);
        else if((bal <= -2 && balHijo == -1) || (bal <= -2 && balHijo == 0) ) RSD(subRaiz);

        return true;
    }
    return false;
}


//*************************************************************************************
template<typename T>
void ArbolDeBVL<T>::RSI(Nodo *&subRaiz)
{
    Nodo * subDer=subRaiz->der;
    subRaiz->der=subDer->izq;
    subDer->izq=subRaiz;
    subRaiz=subDer;

    subRaiz->izq->ActAltura();
    subRaiz->ActAltura();
}


//*************************************************************************************
template<typename T>
void ArbolDeBVL<T>::RSD(Nodo *&subRaiz)
{
    Nodo * subIzq=subRaiz->izq;
    subRaiz->izq=subIzq->der;
    subIzq->der=subRaiz;
    subRaiz=subIzq;

    subRaiz->der->ActAltura();
    subRaiz->ActAltura();
}


//*************************************************************************************
template<typename T>
void ArbolDeBVL<T>::RDD(Nodo *&subRaiz)
{
    RSI(subRaiz->izq);
    RSD(subRaiz);
}


//*************************************************************************************
template<typename T>
void ArbolDeBVL<T>::RDI(Nodo *&subRaiz)
{
    RSD(subRaiz->der);
    RSI(subRaiz);
}

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/
template <typename t>
std::ostream & operator<<(std::ostream & salida,const ArbolDeBVL<t> & abb)
{
    abb.Imprimir(POSORDEN,salida);
    return salida;
}
