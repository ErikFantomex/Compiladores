#ifndef ASINTACTICO_H_INCLUDED
#define ASINTACTICO_H_INCLUDED

/* Nombre: .h
   Autor:
   Fecha:
   Descripción:
   NOTA: Los estados de aceptacion estan marcados en el AFD con un *, el token generado
            es la cadena que le sigue justo despues
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include <fstream>

#include "ArbolDeBVL.h"
#include "AFD.h"
#include "Utileria.h"
#include "Llave.h"

//C++ representa algunos caracteres(Como á) con un valor negativo en el ascii
    //para volverlos positivos les sumaremos la sangria
const int SANGRIA = 128;
const int TAMALFABETO= 256;
const std::string NOACEPTACION = "";

//*************************************************************************************
/** \brief Clase de Analisadorr sintactico con 2
 *
 */
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
    *   \param dir La direccion del blog de notas dondé se guarda el AFD
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
    */void Avanzar(const char &c);

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

    AFD autConst;
    AFD autVar;
    std::string *listTonken;

 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Función que inicializa un automata
    *
    *   \param dir La direccion del blog de notas con el automata.
    *   \param afd El automata a inicializar
    *   \param lTokens Lissta de tokens asociada al afd
    *   \param relCol Los car. de las columnas (Responde ¿Que car. está en la columna x?)
    *
    */void InicializarAFD(const char *dir, AFD & afd,std::string **lTokens) const ;

    //*************************************************************************************
    /** \brief Función que guarda el caracter ligado a la columna número 'i'
    *               NOTA: Está funcion lee la pimera fila del automata
    *
    *   \param r El arreglo donde se guardara la relacion de las columnas con los caract.
    *   \param ent La direccion del blog de notas con el automata
    *
    */void LigarColumnas(int r[], std::ifstream &ent) const;

    //*************************************************************************************
    /** \brief Función que númera los estados
    *
    *   \param mapa La estructura dondé se van a guardar los estados.
    *   \param ent El archivo a leer
    *   \return El número de estados en el archivo
    *
    */int NumerarEstados( ArbolDeBVL<Llave> & abvl, std::ifstream &ent) const;

    //*************************************************************************************
    /** \brief Dimenciona el AFN para tener 'n' estados
    *
    *   \param n El número de estados
    *   \param afb El automata al cual se le va a aplicar la operacion
    *   \param lTokens Lissta de tokens asociada al afd
    *
    */void DimencionarAFD(int &n, AFD & afd, std::string **lTokens ) const;

    //*************************************************************************************
    /** \brief Asigna valores al AFD y a la lista de tokens generados
    *
    *   \param afb El automata al cual se le va a aplicar la operacion
    *   \param lTokens Lissta de tokens asociada al afd
    *   \param mapa La relación de estados - filas (Responde ¿En que fila está q_x?)
    *   \param ent La direccion del blog de notas con el automata
    *   \param relCol Los car. de las columnas (Responde ¿Que car. está en la columna x?)
    *
    */void LlenarAFD(AFD & afd, std::string **lTokens, ArbolDeBVL<Llave> &mapa,
            std::ifstream & ent, int relCol[]) const;

    //*************************************************************************************
    /** \brief Identifica si un estado es de aceptacion
    *
    *   \param ent El texto todo el renglon del estado
    *   \param El indice del caracter por leer en 'ent'
    *   \return Si es de aceptacion, false de lo contrario si no
    *
    */bool IdentificarEstado(const char ent[], int &i) const;

    //*************************************************************************************
    /** \brief Identifica el token del estado
    *
    *   \param ent El texto todo el renglon del estado
    *   \param El indice del caracter por leer en 'ent'
    *   \return El token generado
    *   \exception std::exception::Grosero ...Grosero...
    *
    */std::string GetTokenEstado(const char ent[], int &i) const;

    //*************************************************************************************
    /** \brief Lee todas las transiciones de un estado
    *
    *   \param afd El automata donde está el estado a leer
    *   \param estado El indice del etado a leer
    *   \param mapa La relación de estados - filas (Responde ¿En que fila está q_x?)
    *   \param El indice del caracter por leer en 'ent'
    *   \param relCol Los car. de las columnas (Responde ¿Que car. está en la columna x?)
    *   \param ent El texto todo el renglon del estado
    *
    */void LeerEstado(AFD & afd, int &estado, ArbolDeBVL<Llave> &mapa, int &i,
            int relCol[], const char ent[])const;

};




#endif // ASINTACTICO_H_INCLUDED
