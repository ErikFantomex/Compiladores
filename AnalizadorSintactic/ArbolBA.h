/*
Nombre:      ArbolBA.h
Autor(es):   Aguilar H, Escobar R, Velazquez L y Villalba J.
Fecha:       19/05/21
Descripción: Archivo de cabecera de la clase 'ArbolBA'.
*/

#ifndef ArbolBA_H_INCLUDED
#define ArbolBA_H_INCLUDED

#include<iostream>
#include<stdexcept>
#include"ColaCircular.h"

//*************************************************************************************
enum Recorrido
{
    ASCENDENTE,
    DESCENDENTE,
    PORNIVEL,
};


//****************************************************************************************
/** \brief Clase que representa a una arbolB*.
 *
 * \param T El tipo de los elementos.
 * \param G el grado del arbol (No debe ser menor a 4).
 *
 */
template<typename T= int , unsigned G= 5 >
class ArbolBA
{

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/


    //*************************************************************************************
    /** \brief Imprime un ArbolBA en un flujo de salida.
    *
    * \param arb    El arbol a imprimir.
    * \param Salida El flujo de salida.
    * \return El mismo flujo de salida.
    *
    */
    template <typename t,unsigned g>
    friend std::ostream & operator<<(std::ostream & salida,const ArbolBA<t,g> & arb);

public:

 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Constructor por default.
    *  \exception std::logic_error  No se puede crear un arbol con grado menor a 4.
    *
    */
    ArbolBA();


    //*************************************************************************************
    /** \brief Constructor de copias.
    *
    * \param arb El arbol a copiar
    * \exception std::bad_alloc     No hay memoria para el ArbolBA.
    * \exception std::logic_error   No se puede crear un arbol con grado menor a 4.
    *
    */
    ArbolBA(const ArbolBA & arb);


    //*************************************************************************************
    /** \brief Destructor de la clase.
    *
    */
    ~ArbolBA();



 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/


    //*************************************************************************************
    /** \brief Sobrecarga de operador '='.
    *
    * \param abb    El arbol a copiar.
    * \return Una referencia al ArbolBA.
    * \exception std::bad_alloc No hay memoria para el nodo.
    *
    */
    ArbolBA & operator= (const ArbolBA & arb);

 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Agrega una elemento al arbol.
    *
    * \param emt    El elemento a agregar.
    * \exception std::bad_alloc No hay memoria para el nodo.
    *
    */
    void Agregar(const T & emt);

    //*************************************************************************************
    /** \brief Elimina un elemento del arbol.
    *
    * \param emt    El elemento a eliminar.
    * \return True  Sí borro algo, false de lo contrario.
    * \exception std::bad_alloc     No hay memoria para las operaciones.
    *
    */
    bool Eliminar(const T & emt);

    //*************************************************************************************
    /** \brief Busca un elemento en el arbol.
    *
    * \param emt El elemento a buscar.
    * \return True Sí el elemento se encuentra en el arbol, false de lo contrario.
    *
    */
    T Buscar(const T & emt)const;

    //*************************************************************************************
    /** \brief Devuelve el número de elementos en el arbol.
    * \return El número de elementos en el arbol.
    */
    unsigned NumeroDeElementos()const;

    //*************************************************************************************
    /** \brief Limpia el arbol
    * \return True si elimino algo, false de lo contrario
    *
    */
    bool Vaciar();

    //*************************************************************************************
    /** \brief Imprime un ArbolBA en un flujo de salida.
    * \param Salida El flujo de salida.
    *
    */
    void Imprimir(Recorrido r=PORNIVEL,std::ostream & salida=std::cout)const;
    //*************************************************************************************
    /** \brief Metodo que permite capturar los elementos de un arbol mediante un archivo de texto.
    *
    * \param   nombreArchivo[56] const char    Nombre del archivo (con extensi&oacute;n).
    * \return  bool                            Verdadero si la captura se ha hecho correctamente.
    *
    */
    bool CapturarXArchivo(const char nombreArchivo[56]);

    //*************************************************************************************
    class NodoNoEnc: public std::exception
    {
        public:
            virtual const char * what() const throw();
        private:

    };

private:

    struct Nodo
    {
        /*****************************************************************************************
        **********************************   Constructores    ************************************
        *****************************************************************************************/
        //*************************************************************************************
        /** \brief Constructor por defecto.
        *
        */
        Nodo();

        /*****************************************************************************************
        *********************************   Metodos privados   ***********************************
        *****************************************************************************************/
        //*************************************************************************************
        /** \brief Busca la posici&oacute;n de un elemento.
        *
        * \param emt El elemento.
        * \return El indice del primer elemento mayor o igual a 'emt', si el elemento es mayor
        *           a todos los elementos del nodo, regresa el numero de elementos.
        *
        */
        unsigned BuscarLugar(const T &emt) const;

        //*************************************************************************************
        /** \brief Mete un elemento(Esto solo sucede en las hojas).
        *
        * \param emt El elemento.
        * \param i El indice en dondé se insertará el nodo.
        *
        */
        void Insertar(const T &emt, unsigned i);

        //*************************************************************************************
        /** \brief Elimina un elemento(Esto solo sucede en las hojas).
        * \param i El indice del elemento a eliminar.
        *
        */
        void Eliminar(unsigned i);

        //*************************************************************************************
        /** \brief Función para saber si un nodo es hoja o no.
        * \return i True si el nodo es hoja, false de lo contrario.
        *
        */
        bool EsHoja();

        /*****************************************************************************************
        **************************************   Atributos   *************************************
        *****************************************************************************************/
        T *elemento[2*G];
        Nodo *hijo[2*G+1];
        unsigned nE;
    };

 /*****************************************************************************************
 **************************************   Atributos   *************************************
 *****************************************************************************************/
    Nodo *raiz;
    unsigned nElementos;

 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/
    //*************************************************************************************
    /** \brief Une a dos hijos para partirlos en 3.
    *
    * \param subRaiz    El padre del nodo a partir.
    * \param i          Indice del hijo con el mayor número de elementos.
    * \exception std::bad_alloc No hay memoria para las operaciones.
    *
    */
    void Partir(Nodo *&subRaiz, unsigned i);

    //*************************************************************************************
    /** \brief Parte a 2 hijos, donde el hijo izquierdo es el que tiene más elementos.
    *
    * \param subRaiz El padre del nodo a partir.
    * \param hjoI El hijo más a la izquierda.
    * \param hjoD El hijo más a la derecha.
    * \param i Indice del elemento con los hijos a partir.
    * \exception std::bad_alloc No hay memoria para las operaciones.
    *
    */
    void PartirEnTres(Nodo *&subRaiz, Nodo *hjoI, Nodo *hjoD, unsigned i);

    //*************************************************************************************
    /** \brief Une a 3 hijos para mezclarlos en 2.
    *
    * \param subRaiz El padre del nodo a partir.
    * \param i Indice del hijo con el menor número de elementos.
    * \exception std::bad_alloc No hay memoria para las operaciones.
    *
    */
    void Mezclar(Nodo *&subRaiz, unsigned i);

    //*************************************************************************************
    /** \brief Mezcla 3 hijos, donde el hijo más a la izquierda es quien tiene menos elementos.
    *
    * \param subRaiz    El padre del nodo a partir.
    * \param hjoI       El hijo más a la izquierda.
    * \param hjoM      El hijo del medio.
    * \param hjoD       El hijo más a la derecha.
    * \param i          Indice del hijo con el menor número de elementos
    * \exception std::bad_alloc No hay memoria para las operaciones.
    *
    */
    void MezclarEnDos(Nodo *&subRaiz, Nodo *hjoI, Nodo *hjoM, Nodo *hjoD, unsigned i);

    //*************************************************************************************
    /** \brief Un hijo le comparte un elemento a su hermano a la derecho.
    *
    * \param subRaiz    El padre de los hijos.
    * \param hjoI       El hijo a prestar.
    * \param hjoD       El hijo a recibir.
    * \param i          Indice de hjoI.
    * \exception std::bad_alloc No hay memoria para las operaciones.
    *
    */
    void CompartirD(Nodo *&subRaiz, Nodo *hjoI, Nodo *hjoD, unsigned i);

    //*************************************************************************************
    /** \brief Un hijo le comparte un elemento a su hermano a la izquierda.
    *
    * \param subRaiz    El padre de los hijos.
    * \param hjoI       El hijo a recibir.
    * \param hjoD       El hijo a prestar.
    * \param i          Indice de hjoI.
    * \exception std::bad_alloc No hay memoria para las operaciones.
    *
    */
    void CompartirI(Nodo *&subRaiz, Nodo *hjoI, Nodo *hjoD, unsigned i);


    //*************************************************************************************
    /** \brief Copia un arbol de forma recursiva.
    *
    * \param copia      El arbol donde se copiará el arbol.
    * \param original   El arbol original.
    * \exception std::bad_alloc No hay memoria para las operaciones.
    *
    */
    void Copiar(Nodo *&copia,const Nodo *original);

    //*************************************************************************************
    /** \brief Agrega un elemento al &aacute;rbol.
    *
    * \param emt        El elemento a agregar.
    * \param subRaiz    la sub raiz en donde se agregará la clave.
    * \exception std::bad_alloc No hay memoria para el nodo.
    *
    */
    void Agregar(const T &emt, Nodo *&subRaiz);

    //*************************************************************************************
    /** \brief Elimina un elemento del &aacute;rbol.
    *
    * \param emt        El elemento a eliminar.
    * \param subRaiz    La sub raiz en donde se eliminará la clave.
    * \return True Sí borro algo, false de lo contrario.
    * \exception std::bad_alloc No hay memoria para el nodo.
    *
    */
    bool Eliminar(const T &emt,  Nodo *&subRaiz);

    //*************************************************************************************
    /** \brief Busca un elemento en un subArbol.
    *
    * \param emt        El elemento a buscar.
    * \param subRaiz    La raiz del subArbol.
    * \return True si se encontro el elemento, false de lo contrario.
    *
    */
    const T & Buscar(const T & emt,Nodo *subRaiz) const;

    //*************************************************************************************
    /** \brief Busca el mayor de todos los elementos en un subArbol.
    *
    * \param subRaiz    La raiz del subArbol.
    * \return Una referencia al valor del mayor elemento en el subArbol.
    *
    */
    T *& Mayor(Nodo *subRaiz) const;

    //*************************************************************************************
    /** \brief Busca el menor de todos los elementos en un subArbol.
    *
    * \param subRaiz la raiz del subArbol.
    * \return Una referencia a el valor del menor elemento en el subArbol.
    *
    */
    T *& Menor(Nodo *subRaiz) const;

    //*************************************************************************************
    /** \brief Imprime una subraiz de forma ascendente.
    * \param subRaiz La subRaiz a imprimir.
    *
    */
    void ImprimirA(Nodo *subRaiz,std::ostream & salida) const;

    //*************************************************************************************
    /** \brief Imprime una subraiz de forma descendente.
    * \param subRaiz La subRaiz a imprimir.
    *
    */
    void ImprimirD(Nodo *subRaiz,std::ostream & salida) const;

    //*************************************************************************************
    /** \brief Imprime el arbol por niveles.
    *
    */
    void ImprimirPN(std::ostream & salida) const;

};
#include"ArbolBA.tpp"

#endif // ArbolBA_H_INCLUDED
