/* Nombre: HasImp.tpp
   Autor: Luis Juventino Velasquez H.
   Fecha: 19/04/21
   Descripción: Archivo de implementación de la clase 'HasImp'
*/

#include"HasImp.h"


 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

//*************************************************************************************
template <typename T_1,typename T_2>
HasImp<T_1,T_2>::HasImp() {}


//*************************************************************************************
template <typename T_1,typename T_2>
HasImp<T_1,T_2> ::HasImp(const HasImp & abb)
{
    *this=abb;
}


//*************************************************************************************
template <typename T_1,typename T_2>
HasImp<T_1,T_2> ::~HasImp()
{
    Vaciar();
}


 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/
//*************************************************************************************
template <typename T_1,typename T_2>
HasImp<T_1,T_2> & HasImp<T_1,T_2> ::operator= (const HasImp<T_1,T_2> & hast)
{
    if(this == & hast) return *this;
    Vaciar();

    mapa = hast.mapa;


    return *this;
}

 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/

//*************************************************************************************
template <typename T_1,typename T_2>
bool HasImp<T_1,T_2> ::Agregar(const T_1 & llave, const T_2 & valor)
{
    Llave<T_1,T_2> aux;
    aux.Set(llave,valor);

    return mapa.Agregar(aux);
}


//*************************************************************************************
template <typename T_1,typename T_2>
bool HasImp<T_1,T_2> ::Eliminar(const T_1 & llave)
{
    Llave<T_1,T_2> aux;
    aux.Set(llave);

    return mapa.Eliminar(aux);
}


//*************************************************************************************
template <typename T_1,typename T_2>
T_2 HasImp<T_1,T_2> ::Buscar(const T_1 & llave) const
{
    Llave<T_1,T_2> aux;
    aux.Set(llave);

    return mapa.Buscar(aux).GetValor();
}


//*************************************************************************************
template <typename T_1,typename T_2>
unsigned HasImp<T_1,T_2> ::NumeroDeNodos() const
{
    return mapa.NumeroDeNodos();
}


//*************************************************************************************
template <typename T_1,typename T_2>
bool HasImp<T_1,T_2> ::Vaciar()
{
    return mapa.Vaciar();
}


//*************************************************************************************
template <typename T_1,typename T_2>
void HasImp<T_1,T_2> ::Imprimir(std::ostream & salida/*=std::cout*/) const
{
    mapa.Imprimir(ASCENDENTE,salida);
}




/*****************************************************************************************
************************************   Excepciónes   *************************************
*****************************************************************************************/
//*************************************************************************************
template <typename T_1,typename T_2>
const char * HasImp<T_1,T_2> ::NodoNoEncontrado::what() const throw()
{
    return "No existe el nodo buscado...";
}

//*************************************************************************************
template<typename t1,typename t2>
std::ostream & operator<<(std::ostream & salida, const HasImp<t1,t2> &hasT)
{
    hasT.Imprimir(salida);
    return salida;
}

