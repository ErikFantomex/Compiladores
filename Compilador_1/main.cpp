
#include <iostream>
#include <fstream>
#include "Estructuras/AnalisadorLexico/ASintactico.h"
#include "Estructuras/Utileria/Utileria.h"
#include "Estructuras/Gramatica/Gramatica.h"
#include "Estructuras/Parser/ParserTD.h"

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
    ASintactico aLexico("Automatas/AutomataConstantes.txt","Automatas/AutomataVariables.txt");

    Buffer bufAL(300);
    char nexLinea[300];

    std::string cadenaTokens[10000];
    int numTokoens=0;
    std::string tAux;

    for(int linea = 0;!entrada.eof(); ++linea )
    {
        entrada.getline(nexLinea,300);
        NormalizarCadena(nexLinea);

        for(int i=0; nexLinea[i] != '\0'; ++i)
        {
            bufAL.Meter(nexLinea[i]);

            if(bufAL.CantidadCaracteres() > 50)
            {
                tAux = aLexico.LeerBuffer(bufAL,false);
                if(tAux == T_ERROR)
                {   //Puede que el primer caracter del buffer esté en otro renglon
                    cout<<"Hay un error lexico alrededor de la linea: "<<linea;
                    cout<<" columna: "<<i<<'\n';
                    return;
                }
                else
                    if(tAux != T_ESPACIO && tAux!=NOACEPTACION)
                        cadenaTokens[numTokoens++] = tAux;
            }
        }
        bufAL.Meter('\n');
    }

    while(!bufAL.EstaVacio())
    {
        tAux = aLexico.LeerBuffer(bufAL,true);
        if(tAux == T_ERROR || tAux == NOACEPTACION)
        {
            cout<<"Hay un error lexico casi al final del archivo";
            return;
        }
        else
            if(tAux != T_ESPACIO)
                cadenaTokens[numTokoens++] = tAux;
    }

    for(int i=0;i<numTokoens;++i)
    {
        std::cout<<cadenaTokens[i]<<'\n';
    }

    ParserTD par("Estructuras/Parser/Gramaticas/Gram1.txt");
    if(par.EvaluarCadena(cadenaTokens,numTokoens))
        cout<<"Si se acepta";
    else
        cout<<"No se acepta";
}
