/*
Horacio Araiza Gonzalez
Tarea 3 Estructura de Datos
*/

#ifndef PILA_H
#define PILA_H

#include <iostream>

template <typename T>
class Pila
{
    public:

        /**************************
        *      CONSTRUCTORES:     *
        ***************************/

        /** \brief Constructor por Default de nuestra Pila.
         *
         *
         */
        Pila();

        /** \brief Constructor de copias para nuestra Pila.
         *
         * \tparam p const Pila<T>& Nuestra Pila para copiar.
         *
         */
        Pila(const Pila<T> &p);

        /**************************
        *        OPERADOR =       *
        *      SOBRECARGADO:      *
        ***************************/

        /** \brief Sobrecarga del operador =. Esto con el fin de no sobrecargar nuestra memoria.
         *
         * \tparam p const Pila<T>&  Nuestra Pila a copiar.
         * \return Pila<T>&         Nuestra Pila ya copiada.
         *
         */
        Pila<T> & operator=(const Pila<T> &p);

        /**************************
        *       DESTRUCTOR:       *
        ***************************/

        /** \brief Destructor por default de nuestra clase Pila, para liberar espacio en la memoria.
         *
         */
        virtual ~Pila();

        /******************************************
        *             M�TODOS P�BLICOS            *
        ******************************************/
        /** \brief Funci�n que se encarga de apilar nuestra Pila, la cual da un nuevo elemento al tope de nuestra Pila.
         *
         * \tparam valor const T& Valor del elemento a apilar
         *
         */
        void Apilar(const T & valor);

        /** \brief Funci�n para desapilar a nuestra Pila, el cual se encarga de eliminar el elemento que se encuentra en el tope.
         *
         * \pre Nuestra Pila no debe de estar vac�a.
         */
        void Desapilar();

        /** \brief Funcion que obtiene el elemento que se encuentra al tope de nuestra Pila.
         *
         * \return const T& El elemento que se encuentra al tope de nuestra Pila.
         *
         * \pre Nuestra Pila no debe de estar vac�a.
         */
        const T & ObtenerTope() const;

        /** \brief Funci�n que se encarga de verificar si nuestra Pila se encuentra vac�a.
         *
         * \return bool El valor de verdad de si la pila est� vac�a o no, el tope apunta a algo
         *
         */
        bool EstaVacia() const;

        /** \brief Vac�a la pila, quit�ndole todos los elementos y liberando memoria
         *
         */
        void Vaciar();

        /** \brief Obtiene la cantidad de elementos que se encuentran en la pila
         *
         * \return unsigned Cantidad de elementos que se encuentran en la pila
         *
         */
        unsigned ObtenerTam() const;

        /******************************************
        *         FUNCIONES PARA NUESTROS         *
        *            TIPOS DE PRUEBAS:            *
        ******************************************/

        /** \brief Funci�n que se encarga de imprimir nuestra Pila con un formato determinado.
         *
         *
         */
        void Imprimir() const;

        /** \brief Funci�n que se encarga de imprimir nuestra Pila con el n�mero de elementos con un formato determinado.
         *
         *
         */
        void ImprimeInformacion() const;

    private:
        /******************************************
        *         ATRIBUTOS DE LA CLASE:          *
        ******************************************/
        //Estructura de nuestra clase Pila llamada Elemento
        //que se encarga de guardar un valor en la pila y la direcci�n del elemento que sigue.
        struct Elemento{
            T valor;
            Elemento *siguiente;
            //Nuestro constructor con inicializadores. :D
            Elemento(T val, Elemento *sig = NULL): valor(val), siguiente(sig){}
        } *tope;
        unsigned numElem; //Atributo de tipo unsigned para el n�mero de elementos.
};

#include "Pila.tpp"

#endif // PILA_H
