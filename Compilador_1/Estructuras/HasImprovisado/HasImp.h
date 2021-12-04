#ifndef HASIMP_H_INCLUDED
#define HASIMP_H_INCLUDED

/* Nombre: AFD.h
   Autor: Luis Juventino Velasquez H.
   Fecha: 19/04/21
   Descripción: Archivo de cabecera de la clase AFD
*/

#include<iostream>
#include<stdexcept>
#include "Llave.h"
#include "ArbolDeBVL.h"

//*************************************************************************************

/** \brief Clase que representa a una tabla Has
 * \param T_1 El tipo de la llave
 * \param T_2 El tipo de valor que guarda la llave
 */
template <typename T_1,typename T_2>
class HasImp
{

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/


    //*************************************************************************************
    /** \brief Imprime la tabla en un flujo de salida
    *
    * \param hasT La tabla a imprimir
    * \param salida El flujo de salida
    * \return El mismo flujo de salida
    *
    */
    template<typename t1,typename t2>
    friend std::ostream & operator<<(std::ostream & salida, const HasImp<t1,t2> &hasT);

public:

 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Constructor de copias
    *
    */HasImp();


    //*************************************************************************************
    /** \brief Constructor de copias
    * \exception std::bad_alloc No hay memoria para el arbol
    *
    */HasImp(const HasImp & abb);


    //*************************************************************************************
    /** \brief Destructor de la clase
    *
    */~HasImp();



 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/


    //*************************************************************************************
    /** \brief Sobrecarga de operador '='
    *
    * \param abb La tabla a copiar
    * \return Una referencia a la tabla
    * \exception std::bad_alloc No hay memoria para el nodo
    *
    */HasImp & operator= (const HasImp & abb);


 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/

 //*************************************************************************************
    /** \brief Agrega un valor a la tabla
    *
    * \param llave El valor de la llave (Esté valor es unico)
    * \param valor El valor que guarda la llave (Esté valor se puede repetir)
    * \return True si la llave no está repetido, false de lo contario
    * \exception std::bad_alloc No hay memoria para el nodo
    *
    */bool Agregar(const T_1 & llave, const T_2 & valor);

//*************************************************************************************
    /** \brief Elimina un elemento de la tabla
    *
    * \param llave La llave del valor a eliminar
    * \return True Sí la operación fue exitosa, false de lo contrario
    *
    */bool Eliminar(const T_1 & llave);

//*************************************************************************************
    /** \brief Busca un elemento de la tabla
    *
    * \param llave La llave del valor que se quiere buscar
    * \return El valor asociado a la llave
    *
    */T_2 Buscar(const T_1 & llave) const;

//*************************************************************************************
    /** \brief Devuelve el número de elementos en la tabla
    * \return El número de elementos en la tabla
    *
    */unsigned NumeroDeNodos()const;

//*************************************************************************************
    /** \brief Elimina todas los elementos de la tabla
    * \return True si elimino algo, false de lo contrario
    *
    */bool Vaciar();

//*************************************************************************************
    /** \brief Imprime la tabla en un flujo de salida
    * \param Salida El flujo de salida
    *
    */void Imprimir(std::ostream & salida=std::cout)const;


/*****************************************************************************************
 ************************************   Excepciónes   *************************************
 *****************************************************************************************/

    //*************************************************************************************
    class NodoNoEncontrado: public std::exception
    {
        public:
            virtual const char * what() const throw();
        private:
    };
private:

    ArbolDeBVL<Llave<T_1,T_2> > mapa;
 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/
};

#include "HasImp.tpp"

#endif // HASIMP_H_INCLUDED
