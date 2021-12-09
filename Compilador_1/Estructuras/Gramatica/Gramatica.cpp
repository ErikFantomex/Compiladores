/* Nombre: .cpp
   Autor:
   Fecha:
   Descripción:
*/
#include "Gramatica.h"


 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/
//*************************************************************************************
Gramatica::Gramatica()
{
    producciones = NULL;
    tamProducion = NULL;
    tablaProducciones=NULL;
}

//*************************************************************************************
Gramatica::Gramatica(const Gramatica & afd2)
{
    *this = afd2;
}

//*************************************************************************************
Gramatica::~Gramatica()
{
    Vaciar();
}


 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/
//*************************************************************************************
Gramatica & Gramatica::operator= (const Gramatica & afd2)
{
    if(this == &afd2) return *this;

    Vaciar();
    Parche();

    return *this;
}


 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/
//*************************************************************************************
std::string * Gramatica::GetProduccion(const std::string &i,
        const std::string &j,int & tam)
{

    std::string aux =NormalizarT(j);

    int prod = tablaProducciones[mapaProducciones.Buscar(i)][mapaTerminales.Buscar(aux)];
    if(prod == -1) prod=14;

    tam = tamProducion[prod];
    return producciones[prod];
}

//*************************************************************************************
void Gramatica::InicializarGram(const char *dir)
{
    Vaciar();
    LeerGramatica(dir);
}


 /*****************************************************************************************
 ************************************   Excepciónes   *************************************
 *****************************************************************************************/
//*************************************************************************************
const char * Gramatica::CaracterFuera::what() const throw()
{
    return "Se introdujo un caracter fuera del alfabeto...";
}

 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/
//*************************************************************************************
std::string Gramatica::NormalizarT(const std::string &t)
{
    std::string tAux="";
    for(int i=0,f=t.size() ; i<f &&t[i] != '*' ;++i)
        tAux+=t[i];

    return tAux;
}

//*************************************************************************************
void Gramatica::LeerGramatica(const char *dir )
{
    //Aqui hiria un memtodo que calculara el First y el Follow para una expresion ...
                                // Si tan solo tuviera una....
    Parche();
}

//*************************************************************************************
void Gramatica::Vaciar()
{

    if(tablaProducciones == NULL) return;

    for(int i=0;i<9;++i)
        delete [] tablaProducciones[i];
    delete [] tablaProducciones;
    delete [] tamProducion;

    for(int i=0;i<16;++i)
        delete [] producciones[i];
    delete [] producciones;
}

//*************************************************************************************
void Gramatica::Parche()
{

    mapaProducciones.Agregar("E",0);
    mapaProducciones.Agregar("S",1);
    mapaProducciones.Agregar("S\'",2);
    mapaProducciones.Agregar("A",3);
    mapaProducciones.Agregar("A\'",4);
    mapaProducciones.Agregar("B",5);
    mapaProducciones.Agregar("B\'",6);
    mapaProducciones.Agregar("C",7);

    mapaTerminales.Agregar("TCout",0);
    mapaTerminales.Agregar("TPlus",1);
    mapaTerminales.Agregar("TMinus",2);
    mapaTerminales.Agregar("TMult",3);
    mapaTerminales.Agregar("TDiv",4);
    mapaTerminales.Agregar("TPower",5);
    mapaTerminales.Agregar("TValue",6);
    mapaTerminales.Agregar("TParIzq",7);
    mapaTerminales.Agregar("TParDer",8);
    mapaTerminales.Agregar(FINCADENA,9);

    tablaProducciones = new int* [9];
    for(int i=0;i<9;++i)
    {
        tablaProducciones[i] = new int[10];
        for(int j=0; j<10;++j)
            tablaProducciones[i][j] =  -1;
    }
    tablaProducciones[0][0]=0;
    tablaProducciones[1][6]=1;
    tablaProducciones[1][7]=1;
    tablaProducciones[2][1]=2;
    tablaProducciones[2][2]=3;
    tablaProducciones[2][8]=4;
    tablaProducciones[2][9]=4;
    tablaProducciones[3][6]=5;
    tablaProducciones[3][7]=5;
    tablaProducciones[4][1]=8;
    tablaProducciones[4][2]=8;
    tablaProducciones[4][3]=6;
    tablaProducciones[4][4]=7;
    tablaProducciones[4][8]=8;
    tablaProducciones[4][9]=8;
    tablaProducciones[5][6]=9;
    tablaProducciones[5][7]=9;
    tablaProducciones[6][1]=11;
    tablaProducciones[6][2]=11;
    tablaProducciones[6][3]=11;
    tablaProducciones[6][4]=11;
    tablaProducciones[6][5]=10;
    tablaProducciones[6][8]=11;
    tablaProducciones[6][9]=11;
    tablaProducciones[7][6]=12;
    tablaProducciones[7][7]=13;


    producciones = new std::string*[16];
    for(int i=0;i<16;++i)
        producciones[i] = new std::string[5];


    //Tokens de producciones
    producciones[0][0] = "TCout";
    producciones[0][1] = "S";
    producciones[1][0] = "A";
    producciones[1][1] = "S\'";
    producciones[2][0] = "TPlus";
    producciones[2][1] = "A";
    producciones[2][2] = "S\'";
    producciones[3][0] = "TMinus";
    producciones[3][1] = "A";
    producciones[3][2] = "S\'";
    producciones[4][0] = EPSILON;
    producciones[5][0] = "B";
    producciones[5][1] = "A\'";
    producciones[6][0] = "TMult";
    producciones[6][1] = "B";
    producciones[6][2] = "A\'";
    producciones[7][0] = "TDiv";
    producciones[7][1] = "B";
    producciones[7][2] = "A\'";
    producciones[8][0] = EPSILON;
    producciones[9][0] = "C";
    producciones[9][1] = "B\'";
    producciones[10][0] = "TPower";
    producciones[10][1] = "C";
    producciones[10][2] = "B\'";
    producciones[11][0] = EPSILON;
    producciones[12][0] = "TValue";
    producciones[13][0] = "TParIzq";
    producciones[13][1] = "S";
    producciones[13][2] = "TParDer";
    producciones[14][0] = P_ERRONEA;

    //Numeros de tokens que tiene la produccion 'i'
    tamProducion = new int [16];
    tamProducion[0] = 2;
    tamProducion[1] = 2;
    tamProducion[2] = 3;
    tamProducion[3] = 3;
    tamProducion[4] = 1;
    tamProducion[5] = 2;
    tamProducion[6] = 3;
    tamProducion[7] = 3;
    tamProducion[8] = 1;
    tamProducion[9] = 2;
    tamProducion[10] = 3;
    tamProducion[11] = 1;
    tamProducion[12] = 1;
    tamProducion[13] = 3;
    tamProducion[14] = 1;

}

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/
