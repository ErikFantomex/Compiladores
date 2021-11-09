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
class Llave
{

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/


    //*************************************************************************************
    /** \brief imprime una ASintactico en un flujo de salida
    *
    * \param salida el flujo de salida
    * \return El mismo flujo de salida
    *
    */friend std::ostream & operator<<(std::ostream & salida,const Llave &x)
    {
        salida<<'['<<x.llave<<" , "<<x.valor<<']';
        return salida;
    };

public:

 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Constror por defecto
    *
    */Llave();

    //*************************************************************************************
    /** \brief Constror por defecto
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
    */void Set(const std::string & s, const int &v=0);

    //*************************************************************************************
    /** \brief Funcion Get para el valor
    *   \return El 'Valor'
    *
    */int GetValor() const;

private:
    std::string llave;
    int valor;
  /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/
};


#endif // LLAVE_H_INCLUDED
