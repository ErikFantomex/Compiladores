#ifndef ASINTACTICO_H_INCLUDED
#define ASINTACTICO_H_INCLUDED

/* Nombre: .h
   Autor:
   Fecha:
   Descripción:
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include <fstream>
#include "ArbolBA.h"



class ASintactico
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
    */friend std::ostream & operator<<(std::ostream & salida,const ASintactico &x);

    //*************************************************************************************
    /** \brief
     *
     * \param entrada el flujo de entrada
     * \return El mismo flujo de entrada
     *
     */friend std::istream & operator>>(std::istream & entrada, ASintactico &x);

public:

 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Constructor que "abre" la matriz en el documento 'dir'
    *
    *   \param dir La direccion del blog de notas dondé se guarda la matrizDireccionNula
    *   \exception std::bad_alloc::matrizDireccionNula No se encontro el blog
    *   \exception std::bad_alloc No hay memoria para las variables dinamicas
    *
    *
    */ASintactico(const char  *dir);


    //*************************************************************************************
    /** \brief Constructor de copias
    *   \param a2 El objeto a copiar
    */ASintactico(const ASintactico & a2);


    //*************************************************************************************
    /** \brief Destructor de la clase
    *
    */~ASintactico();



 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/


    //*************************************************************************************
    /** \brief Sobrecarga del operador '='
    *
    */ASintactico & operator= (const ASintactico & mtz);



 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Pone el estado en el estado inicial (El primero)
    *
    */void Reset();

    //*************************************************************************************
    /** \brief Mueve el automata usando la transicion 'c'
    *   \param c El caracter que se usara para la transicion
    *   \exception std::bad_alloc::CaracterFuera 'c' está fuera del alfabeto
    *
    */void Avanzar(const char c);

    //*************************************************************************************
    /** \brief Mueve el automata usando la transicion 'c'
    *   \return True si el estado actual es de aceptacion, false de lo contrario
    *
    */bool estadoAceptacion() const;

    //*************************************************************************************
    /** \brief Retorna el token del estado
    *   \return True si el estado actual es de aceptacion, false de lo contrario
    *   \exception std::bad_alloc::Grosero El estado actual no es de aceptacion
    *
    */std::string GetT() const;

 /*****************************************************************************************
 ************************************   Excepciónes   *************************************
 *****************************************************************************************/

    //*************************************************************************************
    class CaracterFuera: public std::exception
    {
        public:
            virtual const char * what() const throw();
        private:

    };

    //*************************************************************************************
    class DireccionNula: public std::exception
    {
        public:
            virtual const char * what() const throw();
        private:

    };

    //*************************************************************************************
    class Grosero: public std::exception
    {
        public:
            virtual const char * what() const throw();
        private:

    };

    //*************************************************************************************
    class TablaIncorrecta: public std::exception
    {
        public:
            virtual const char * what() const throw();
        private:

    };


private:
    int nEstados;
    int estActl;
    int **MatTrans;
    bool *eAcept;
    std::string *listTonken;

 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/
};

class Llave
{
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

    Llave();

    Llave(const Llave & ll2);

    void Set(const std::string & s, const int &v);

    int GetValor() const;

    Llave & operator= (const Llave & ll2);

    bool operator<(const Llave & ll2) const;

    bool operator>(const Llave & ll2) const;

    bool operator==(const Llave & ll2) const;

    bool operator>=(const Llave & ll2) const;

    bool operator<=(const Llave & ll2) const;

private:

    std::string llave;
    int valor;

};


#endif // ASINTACTICO_H_INCLUDED
