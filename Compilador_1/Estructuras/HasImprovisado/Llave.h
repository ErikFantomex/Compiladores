#ifndef LLAVE_H_INCLUDED
#define LLAVE_H_INCLUDED

/* Nombre: .h
   Autor:
   Fecha:
   Descripción:
*/

#include<iostream>
#include<stdexcept>

//*************************************************************************************
/** \brief Clase que representa una 'Llave'. cada valor se identifica por su string
 *              pero tiene un valor asociado a ese identificador
 */
template <typename T_1,typename T_2>
class Llave
{

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/

public:

 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Constror por defecto
    *
    */Llave();

    //*************************************************************************************
    /** \brief Constror de copias
    *
    */Llave(const Llave & ll2);


 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/


    //*************************************************************************************
    /** \brief Sobrecarga del operados =
    *
    *   \param ll2 La llave a copiar
    *   \return Una referencia a la llave actual
    *
    */Llave & operator= (const Llave & ll2);

    //*************************************************************************************
    /** \brief Sobrecarga del operados <
    *
    *   \param ll2 La llave con la que se va a comprarar
    *   \return True si el string es menor al string de ll2, false de lo contrario
    *
    */bool operator<(const Llave & ll2) const;

    //*************************************************************************************
    /** \brief Sobrecarga del operados >
    *
    *   \param ll2 La llave con la que se va a comprarar
    *   \return True si el string es mayor al string de ll2, false de lo contrario
    *
    */bool operator>(const Llave & ll2) const;

    //*************************************************************************************
    /** \brief Sobrecarga del operados ==
    *
    *   \param ll2 La llave con la que se va a comprarar
    *   \return True si el string es igual al string de ll2, false de lo contrario
    *
    */bool operator==(const Llave & ll2) const;

    //*************************************************************************************
    /** \brief Sobrecarga del operados >=
    *
    *   \param ll2 La llave con la que se va a comprarar
    *   \return True si el string es mayor o igual al string de ll2, false de lo contrario
    *
    */bool operator>=(const Llave & ll2) const;

    //*************************************************************************************
    /** \brief Sobrecarga del operados <=
    *
    *   \param ll2 La llave con la que se va a comprarar
    *   \return True si el string es menor o igual al string de ll2, False de lo contrario
    *
    */bool operator<=(const Llave & ll2) const;


 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Funcion set tanto para la llave como para el valor
    *
    *   \param llave El valor a asignar a 'llave'
    *   \param v El valor a asignar a 'valor'
    *
    */void Set(const T_1 & s, const T_2 &v);

    //*************************************************************************************
    /** \brief Sobrecarga para set, solo para la llave
    *
    *   \param llave El valor a asignar a 'llave'
    *   \param v El valor a asignar a 'valor'
    *
    */void Set(const T_1 & s);

    //*************************************************************************************
    /** \brief Funcion Get para el valor
    *   \return El 'Valor'
    *
    */T_2 GetValor() const;

private:
    T_1 llave;
    T_2 valor;
  /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/
};

#include "Llave.tpp"

#endif // LLAVE_H_INCLUDED
