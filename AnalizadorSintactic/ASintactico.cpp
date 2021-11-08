/* Nombre: .cpp
   Autor:
   Fecha:
   Descripción:
*/

#include "ASintactico.h"



 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

//*************************************************************************************
ASintactico::ASintactico(const char *direccion)
{
    estActl=0;
    std::ifstream archivo(direccion);
    char transiciones[256];
    ArbolBA<Llave> mapa;
    std::string tGen;
    char texto[2000];
    Llave aux,abusc;
    int i;

    if(!archivo)
    {
        throw DireccionNula();
        archivo.close();
        return;
    }


    //Leemos la primera linea para saber que caracter tine cada columna
    archivo.getline(texto,2000);
    for(i=0; texto[i] != '\t' ; ++i);
    for(int col=0; texto[i] != '\0' ; ++i)
    {
        if(texto[i] == '\t') continue;
        transiciones[col++]= texto[i];
    }


    //Le asignamos una fila a cada estado
    int valAux;
    std::string sAux;
    for(nEstados=0; !archivo.eof() ; ++nEstados)
    {
        archivo.getline(texto,2000);

        valAux=nEstados;
        sAux.clear();
        for(int j=0;texto[j]!='\t' && texto[j]!='*';++j)
            sAux+=texto[j];

        aux.Set(sAux,valAux);
        mapa.Agregar(aux);
    }



    //Iniciamos los arreglos
    eAcept =new bool[nEstados];
    listTonken = new std::string[nEstados];
    MatTrans= new int*[nEstados];
    for(int i=0;i<nEstados;++i)
        MatTrans[i] = new int[257];
    for(int i=0;i<nEstados; ++i)
        for(int j=0;j<257;++j)
            MatTrans[i][j]=-1;


    //llenamos la tabla, los estados de aceptacion y los T generados
    int eTrans; //Variable aux, guardaa el valor que va en la pos [i][j]
                    // (Ese valor se interpreta como "Estando en el estado 'i' y usando 'j' vete a [i][j]")
    archivo.seekg(0, archivo.beg);
    archivo.getline(texto,2000);
    for(int fila=0; !archivo.eof() ; ++fila)
    {
        archivo.getline(texto,2000);

        //Se lee el nombre del estado y se verifica si es de aceptacion o no
        for(i=0;texto[i]!='\t' && texto[i] != '*' ;++i) ;
        if(texto[i] == '*')
        {
            eAcept[fila] = true;
            tGen.clear();
            for(++i;texto[i]!='\t';++i)
                tGen+=texto[i];
            listTonken[fila] =tGen;
        }
        else eAcept[fila] = false;

        //Se llena la matriz de transicion
        for(int colD=0,colR;texto[i]!='\0';)
        {

            if(texto[i] == '\t')
            {
                ++i;
                continue;
            }

            sAux.clear();
            while(texto[i]!='\t' && texto[i] != '\0')
                sAux+=texto[i++];
            abusc.Set(sAux,8);
            aux = mapa.Buscar(abusc);

            eTrans = aux.GetValor();
            colR=(int)transiciones[colD++];
            MatTrans[fila][colR]=eTrans;

            if(texto[i] != '\0') ++i;
        }
    }

}


//*************************************************************************************
ASintactico::~ASintactico()
{
    delete [] eAcept;
    delete [] listTonken;

    for(int i=0;i<nEstados;++i)
        delete [] MatTrans;
    delete [] MatTrans;
}

//*************************************************************************************
ASintactico::ASintactico(const ASintactico & a2)
{
    (*this) = a2;
}

 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/
//*************************************************************************************
ASintactico & ASintactico::operator= (const ASintactico & a2)
{
    return *this;
}


 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/
//*************************************************************************************
void ASintactico::Reset()
{
    estActl=0;
}

//*************************************************************************************
void ASintactico::Avanzar(const char c)
{
    if(MatTrans[estActl][(int)c] == -1) throw CaracterFuera();
    estActl = MatTrans[estActl][(int)c];
}

//*************************************************************************************
bool ASintactico::estadoAceptacion() const
{
    return eAcept[estActl];
}


//*************************************************************************************
std::string ASintactico::GetT() const
{
    if(!estadoAceptacion())throw Grosero();
    return listTonken[estActl];
}

 /*****************************************************************************************
 ************************************   Excepciónes   *************************************
 *****************************************************************************************/
//*************************************************************************************
const char * ASintactico::DireccionNula::what() const throw()
{
    return "No se encontr\242 la el archivo...";
}

//*************************************************************************************
const char * ASintactico::Grosero::what() const throw()
{
    return "Hay una funcion para saber si el estado es de aaceptacion y no la usaste... Grosero...";
}

//*************************************************************************************
const char * ASintactico::CaracterFuera::what() const throw()
{
    return "Se introdujo un caracter fuera del alfabeto...";
}

//*************************************************************************************
const char * ASintactico::TablaIncorrecta::what() const throw()
{
    return "Hay un error en el automata del archivo...";
}

 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/
 Llave::Llave()
{
    this->llave= "";
    this->valor = -6;
}


void Llave::Set(const std::string & s, const int &v)
{
    llave=s;
    valor=v;
}

int Llave::GetValor() const
{
    return valor;
}

Llave & Llave::operator= (const Llave & ll2)
{
    if(this == &ll2) return *this;

    this->llave = ll2.llave;
    this->valor = ll2.valor;

    return *this;
}

Llave::Llave(const Llave & ll2)
{
    (*this) = ll2;
}

bool Llave::operator<(const Llave & ll2) const
{
    return this->llave < ll2.llave;
}

bool Llave::operator>(const Llave & ll2) const
{
    return this->llave > ll2.llave;
}

bool Llave::operator==(const Llave & ll2) const
{
    return this->llave == ll2.llave;
}

bool Llave::operator>=(const Llave & ll2) const
{
    return this->llave >= ll2.llave;
}

bool Llave::operator<=(const Llave & ll2) const
{
    return this->llave <= ll2.llave;
}
