#ifndef GRAMATICA_H_INCLUDED
#define GRAMATICA_H_INCLUDED

/* Nombre: Gramatica.h
   Autor: Luis Juventino Velasquez H.
   Fecha: 06/12/21
   Descripción: Archivo de cabecera de la clase Gramatica
*/

#include<iostream>
#include "../HasImprovisado/HasImp.h"

//Constante para todas las producciones erroneas o que no llevan a ningun lado
const std::string P_ERRONEA = "";
const std::string EPSILON ="\'e";
const std::string FINCADENA = "$";

//*************************************************************************************
/** \brief Clase que representa a Gramatica
 */
class Gramatica
{

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/


    //*************************************************************************************
    /** \brief Imprime una gramatica en un flujo de salida
    *
    * \param grm La gramatica a imprimir
    * \param salida El flujo de salida
    * \return El mismo flujo de salida
    *
    */
    friend std::ostream & operator<<(std::ostream & salida, const Gramatica &grm);

public:

 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Constructor que lee la gramtica de un lenguaje
    *
    */explicit Gramatica(const char *dir);


    //*************************************************************************************
    /** \brief Constructor de copias
    * \exception std::bad_alloc No hay memoria para la matriz
    *
    */Gramatica(const Gramatica & grm2);


    //*************************************************************************************
    /** \brief Destructor de la clase
    *
    */~Gramatica();

 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/


    //*************************************************************************************
    /** \brief Sobrecarga de operador '='
    *
    * \param grm2 El arbol a copiar
    * \return Una referencia al arbol
    * \exception std::bad_alloc No hay memoria para el nodo
    *
    */Gramatica & operator= (const Gramatica & grm2);

 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Funcion para obtener las producciones del alfabeto
    *
    *   \param i La regla en la que se está
    *   \param j El token que se está leuendo
    *   \param i El número de tokens que tiene la produccion correspondiente a i,j
    *   \return  Un arreglo de strings con las producciones correspondientes
    *
    */std::string * GetProduccion(const std::string &i,
                            const std::string &j,int & tam) ;

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

private:
    HasImp<std::string,int> mapaTerminales;
    HasImp<std::string,int> mapaProducciones;
    std::string **producciones;
    int *tamProducion;
    int **tablaProducciones; //La que se llena usando First y folow


 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Crea una matriz de 'n' X 'm'
    *
    *   \param n El numero de filas de la matriz
    *   \param m El número de columnas del automata
    *   \exception std::bad_alloc No hay memoria
    *
    */void Dimencionar(const int &n, const int &m);

    //*************************************************************************************
    /** \brief Le quita el "valor" a los tokens
    *
    *   \param t El token a normalizar
    *   \return El token normalizado
    *
    */std::string NormalizarT(const std::string &t);

    //*************************************************************************************
    /** \brief Libera la memoria reservada
    *
    */void Vaciar();

    //*************************************************************************************
    /** \brief Lee la gramatica y pobla todos los atributos
    *
    *   \param dir La dirreccion de la gramatica
    *   \exception std::bad_alloc No hay memoria
    **/
    void LeerGramatica(const char *dir);

    //*************************************************************************************
    /** \brief Parche
    *
    */void Parche();

};

#endif // GRAMATICA_H_INCLUDED
