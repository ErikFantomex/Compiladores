/* Nombre: .h
   Autor:
   Fecha:
   Descripción:
*/
#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include<iostream>
#include<stdexcept>
#include<string.h>

/** \brief Estructura que simula un buffer
*/
class Buffer
{

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Imprime una Buffer en un flujo de salida
    *
    * \param salida El flujo de salida
    * \param buf El buffer a imprimir
    * \return El mismo flujo de salida
    *
    */ //T
    friend std::ostream & operator<<(std::ostream & salida, const Buffer & buf);

public:

 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Constructor Por defecto
    *
    * \param tam tamano del buffer
    * \param CALC Comando para apertura de linea de comentarios
    * \param CABC Comando para apertura de bloque de comentarios
    * \param CCBC Comando para cierre de bloque de comentarios
    * \exception std::bad_alloc No hay memoria para el buffer
    *
    */Buffer(const int tam = 256, const char *CALC="//",
                        const char *CABC="/*", const char *CCBC="*/");


    //*************************************************************************************
    /** \brief Constructor de copias
    * \exception std::bad_alloc No hay memoria para el buffer
    *
    */Buffer(const Buffer & buf);


    //*************************************************************************************
    /** \brief Destructor de la clase
    *
    */~Buffer();



 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/

    //*************************************************************************************
    /** \brief Operador igual
    *
    * \param buf El buffer a copiar
    * \return Una referencia al buffer al cual se le aplico la operación
    * \exception std::bad_alloc No hay memoria para el buffer
    *
    */Buffer & operator= (const Buffer & buf);

    //*************************************************************************************
    /** \brief Operador parentesis para L value
    *
    * \param i Indice al cual se quiere acceder
    * \return Una referencia al elemento número i empezando desde el primer elemento
    *               pendiente en el buffer
    * \exception std::out_of_range Esa posición no existe o no está siendo usada
    *
    */char & operator[] (const int i);

    //*************************************************************************************
    /** \brief Operador parentesis para R value
    *
    * \param i Indice al cual se quiere acceder
    * \return Una copia del elemento número i empezando desde el primer elemento
    *               pendiente en el buffer
    * \exception std::out_of_range Esa posición no existe o no está siendo usada
    *
    */char operator[] (const int i) const;


 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/

    //******************************************************************************************
    /** \brief Mete un caracter al buffer
    *
    * \param c El caracter a meter
    * \return False si el buffer está lleno(Y por ende C se perdio), true de lo contrario
    *
    */bool Meter(const char & c );

    //******************************************************************************************
    /** \brief Saca n elementos del buffer
    *
    * \param n El número de elementos a sacar del buffer
    * \return False si no es posible sacar n elementos, true de lo contrario
    *
    */bool Sacar(int n );

    //******************************************************************************************
    /** \brief Dice si el buffer está lleno
    * \return True si el buffer está lleno
    *
    */bool EstaLleno() const;

    //******************************************************************************************
    /** \brief Dice si el buffer está vacio
    * \return True si el buffer está lleno
    *
    */bool EstaVacio() const;

    //******************************************************************************************
    /** \brief Dice si el buffer está leyendo bloques de comentarios
    * \return La bandera de leyendoBC
    *
    */bool LeyendoBloqueComentario() const;

    //******************************************************************************************
    /** \brief Dice si el buffer está leyendo una linea de comentarios
    * \return La bandera 'leyendoLC'
    *
    */bool LeyendoLineaComentario() const;

    //******************************************************************************************
    /** \brief Devuelve el número de caracteres que hay en el buffer
    * \return El número de caracteres en el buffer
    *
    */int CantidadCaracteres() const;

    //******************************************************************************************
    /** \brief Devuelve la capacidad maxima del buffer
    * \return El atributo 'tamano'
    *
    */int Capacidad() const;

    //******************************************************************************************
    /** \brief Vacia el buffer
    *
    */void Vaciar();

    //******************************************************************************************
    /** \brief Función para debugiar, imprime el buffer
    *
    */void ImprimirBuffer(std::ostream & salida = std::cout) const;

private:

    char *caracteres;
    int tamano;
    int inBf; //Posición del primer caracter pendiente en el buffer
    int fnBf; //Posición de dondé va el siguiente caracter en el buffer
    bool leyendoBC;
    bool leyendoLC;
    bool lleno;
    char ABC[100];
    char CBC[100];
    char ALC[100];
    int tAB,tAL,tCB,posCBC;

 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/

    //******************************************************************************************
    /** \brief Compara el caracter de la entrada con el ultimo caracter del buffer
    *
    * \param ultC Ultimo caracter del buffer
    * \param lectura El caracter de la entrada
    * \return True si el caracter de la entrada no es "de relleno"
    *
    */bool CaracterValido(const char & ultC, const char & lectura) const;

    //******************************************************************************************
    /** \brief Dice si al final del bufer hay un comando para abrir el bloque de comentario
    * \return True si al final si termina en el comando
    *
    */bool IniciaEnLineaDeComentario();

    //******************************************************************************************
    /** \brief Dice si al final del bufer hay un comando para abrir el bloque de comentario
    * \return True si al final si termina en el comando
    *
    */bool IniciaEnBloqueDeComentario();

    //******************************************************************************************
    /** \brief Devuelve la posición del ultimo caracter del buffer
    * \return No leiste arriba?
    *
    */int IndiceUltimo() const;

    //******************************************************************************************
    /** \brief Devuelve true si el ultimo elemento del buffer forma un comando para un comentario
    * \return True Si lo forma
    *
    */bool VerificarComentario() const;

    //******************************************************************************************
    /** \brief Hace todo lo que deberia hacer los corchetes
    *
    * \param i Indice al cual se quiere acceder
    * \return Una referencia al elemento número i empezando desde el primer elemento
    *               pendiente en el buffer
    * \exception std::out_of_range Esa posición no existe o no está siendo usada
    *
    */char & ElementoI(const int i) const;
};


#endif // BUFFER_H_INCLUDED
