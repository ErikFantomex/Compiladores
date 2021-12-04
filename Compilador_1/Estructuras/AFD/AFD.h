#ifndef AFD_H_INCLUDED
#define AFD_H_INCLUDED

/* Nombre: AFD.h
   Autor: Luis Juventino Velasquez H.
   Fecha: 19/04/21
   Descripción: Archivo de cabecera de la clase AFD
*/

#include<iostream>

//*************************************************************************************
/** \brief Clase que representa a AFD
 * \param n Número de estados del AFD
 */
class AFD
{

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/


    //*************************************************************************************
    /** \brief Imprime una arbol en un flujo de salida
    *
    * \param afd El arbol a imprimir
    * \param salida El flujo de salida
    * \return El mismo flujo de salida
    *
    */
    friend std::ostream & operator<<(std::ostream & salida, const AFD &afd);

public:

 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Constructor por defecto
    *
    */AFD();


    //*************************************************************************************
    /** \brief Constructor de copias
    * \exception std::bad_alloc No hay memoria para el arbol
    *
    */AFD(const AFD & afd2);

    //*************************************************************************************
    /** \brief Constructor de dos parametros
    *
    * \param n El número de filas de la matriz (número de estados)
    * \param m El número de columnas de la matriz (tamaño del alfabeto)
    * \exception std::bad_alloc No hay memoria para el arbol
    *
    */AFD(const int & n, const int &m);


    //*************************************************************************************
    /** \brief Destructor de la clase
    *
    */~AFD();


 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/


    //*************************************************************************************
    /** \brief Sobrecarga de operador '='
    *
    * \param afd2 El arbol a copiar
    * \return Una referencia al arbol
    * \exception std::bad_alloc No hay memoria para el nodo
    *
    */AFD & operator= (const AFD & afd2);

    //*************************************************************************************
    /** \brief Sobrecarga de operador [] para LV
    *
    * \param i El número de la fila
    * \return El arreglo de la fila número i
    *
    */int * operator[] (const int &i);

    //*************************************************************************************
    /** \brief Sobrecarga de operador [] para RV
    *
    * \param i El número de la fila
    * \return El arreglo de la fila número i
    * \exception std::bad_alloc No hay memoria para el nodo
    *
    */const int * operator[] (const int &i) const;


 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Imprime el automata en un flujo de salida
    *
    */void Imprimir(std::ostream & salida=std::cout)const;

    //*************************************************************************************
    /** \brief Cambia un estado a un estado de aceptacion (O al revez)
    *
    * \param i La posicion del estado a cambiar
    * \param e Tue si se quiere establecer como estado es de aceptacion, false de otro modo
    *
    */void SetEstadosA(const int &i , const bool &e);

    //*************************************************************************************
    /** \brief Pone el estado en el estado inicial (El primero)
    *
    */void Reset();

    //*************************************************************************************
    /** \brief Mueve el automata usando la transicion 'c'
    *   \param c El caracter que se usara para la transicion
    *   \exception std::bad_alloc::CaracterFuera 'c' está fuera del alfabeto
    *
    */void Avanzar(const int &c);

    //*************************************************************************************
    /** \brief Crea una matriz con 'n' estados y 'm' caracteres en el alfabeto
    *           tambien inicializa 'nEstados','estadoActual' y 'tamAlf'
    *
    *   \param n El numero de filas de la matriz
    *   \param m El número de columnas del automata
    *   \param valIn El valor inicial de cada valor en la matriz
    *   \exception std::bad_alloc No hay memoria
    *
    */void Dimencionar(const int &n, const int &m, const int &valIn=-1);

    //*************************************************************************************
    /** \brief Funcion para saber si el estado actual es de aceptacion
    *   \return True si el estado actual es de aceptacion, false de lo contrario
    *
    */bool estadoAceptacion() const;

    //*************************************************************************************
    /** \brief Oblitera la matriz
    *
    */void Vaciar();

    //*************************************************************************************
    /** \brief Funcion Get para el número de estados
    *   \return El número de estados
    *
    */const int & GetEstadoAct() const;

    //*************************************************************************************
    /** \brief Funcion Get para el número de estados
    *   \return El número de estados
    *
    */const int & GetNEstados() const;

    //*************************************************************************************
    /** \brief Funcion Get para el tamaño del alfabeto
    *   \return El tamaño del alfabeto
    *
    */const int & GetTamAlfabeto() const;

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
    class EstadoInexistente: public std::exception
    {
        public:
            virtual const char * what() const throw();
        private:

    };

private:

    int nEstados;
    int **matTrans;
    bool *eAcept;
    int estActl;
    int tamAlf;


 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/

};

#endif // AFD_H_INCLUDED
