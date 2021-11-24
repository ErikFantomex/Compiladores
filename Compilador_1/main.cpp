

#include <iostream>
#include <fstream>
#include "ASintactico.h"
#include "Utileria.h"

using namespace std;

//******************************************************************************************
/** \brief Lee los caracteres de un archivo*
* \param entrada El archivo a leer
*
*/void Lectura(ifstream &entrada);

//******************************************************************************************


int main()
{
    std::ifstream entrada;

    entrada.open("stream.txt");
    if(!entrada)
    {
        std::cout<<"Catastrofe";
        entrada.close();
        return -1;
    }
    Lectura(entrada);



    entrada.close();
    return 0;
}


//******************************************************************************************
void Lectura(ifstream &entrada )
{
    char aux;
    //ASintactico();
    Buffer bufAL(300);

    if(entrada.get(aux)) bufAL.Meter(aux);
    else return;

    while(entrada.get(aux))
    {
        if(bufAL.EstaLleno())
        {
            cout<<bufAL[0];
            //esperate tantito al analizador sintactico
            bufAL.Sacar(bufAL.CantidadCaracteres());

        }
        bufAL.Meter(aux);
    }
    cout<<bufAL;
}
