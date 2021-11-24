/* Nombre: .cpp
   Autor:
   Fecha:
   Descripción:
*/
#include "Buffer.h"

 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

//*************************************************************************************
//T
Buffer::Buffer(const int tam, const char *CALC, const char *CABC, const char *CCBC)
    :caracteres(NULL),tamano(tam),inBf(0),fnBf(0),leyendoBC(false),leyendoLC(false),lleno(false),posCBC(0)
{

    int i;
    for(i=0; CABC[i]!='\0' ; ++i) ABC[i]=CABC[i];
    tAB=i;
    ABC[i]='\0';

    for(i=0; CALC[i]!='\0' ; ++i) ALC[i]=CALC[i];
    tAL=i;
    ALC[i]='\0';

    for(i=0; CCBC[i]!='\0' ; ++i) CBC[i]=CCBC[i];
    tCB=i;
    CBC[i]='\0';

    caracteres = new char[tam];
}

//*************************************************************************************
//T
Buffer::Buffer(const Buffer & buf)
    :caracteres(NULL),tamano(0),inBf(0),fnBf(0),leyendoBC(false),leyendoLC(false),lleno(false),posCBC(0)
{
    *this = buf;
}

//*************************************************************************************
//T
Buffer::~Buffer()
{
    delete [] caracteres;
}


 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/

//*************************************************************************************
//T
Buffer & Buffer::operator= (const Buffer & buf)
{
    if(&buf == this) return *this;
    delete [] caracteres;

    caracteres = new char [buf.tamano];
    inBf = buf.inBf;
    fnBf = buf.fnBf;

    for(int i=inBf, fin = IndiceUltimo() ; i!= fin ;++i)
    {
        if(i >= tamano) i = 0;
        caracteres[i] = buf.caracteres[i];
    }


    return *this;
}

//*************************************************************************************
//T
char & Buffer::operator[] (const int i)
{
    return ElementoI(i);
}


//*************************************************************************************
//T
char Buffer::operator[] (const int i) const
{
    return ElementoI(i);
}


 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/
//******************************************************************************************
//T
bool Buffer::Meter(const char & c )
{
    if(leyendoLC && c=='\n')
    {
        leyendoLC = false;
        return true;
    }

    if(leyendoBC)
    {
        if(c == CBC[posCBC]) ++posCBC;
        else
        {
            if(c == CBC[0]) posCBC = 1;
            else posCBC=0;
        }

        if(CBC[posCBC] == '\0')
        {
            leyendoBC = false;
            posCBC = 0;
        }
        return true;
    }

    if(leyendoLC || leyendoBC) return true;

    if(lleno) return false;

    if(CaracterValido( caracteres[ IndiceUltimo() ] ,c ))
    {
        caracteres[fnBf++]=c;

        if(fnBf >= tamano) fnBf = 0; //Vuelta de carro
        if(fnBf == inBf) lleno = true;

        leyendoBC = IniciaEnBloqueDeComentario();
        leyendoLC = IniciaEnLineaDeComentario();
    }
    return true;
}

//******************************************************************************************
//T
bool Buffer::Sacar(int n )
{
    if(n > CantidadCaracteres() ) return false;

    int resultado = (inBf+n) % tamano;

    inBf=resultado;
    lleno=false;
    return true;
}

//******************************************************************************************
//T
bool Buffer::EstaLleno() const
{
    return lleno;
}

//******************************************************************************************
//T
bool Buffer::EstaVacio() const
{
    if(!lleno && fnBf == inBf) return true;
    else return false;
}

//******************************************************************************************
//T
bool Buffer::LeyendoBloqueComentario() const
{
    return leyendoBC;
}

//******************************************************************************************
//T
bool Buffer::LeyendoLineaComentario() const
{
    return leyendoLC;
}

//******************************************************************************************
//T
int Buffer::CantidadCaracteres() const
{
    if(fnBf == inBf)
        return (lleno ? tamano : 0);

    if(inBf > fnBf)
    {
        return tamano-(inBf-fnBf);
    }

    return fnBf-inBf;
}

//******************************************************************************************
//T
int Buffer::Capacidad() const
{
    return tamano;
}


//******************************************************************************************
//T
void Buffer::Vaciar()
{
    inBf=fnBf=0;
    lleno=false;
    leyendoBC=false;
    leyendoLC=false;
    posCBC=0;
}

//******************************************************************************************
//T
void Buffer::ImprimirBuffer(std::ostream & salida) const
{
    for(int i=inBf, fin = IndiceUltimo(); i!= fin ;++i)
    {
        if(i >= tamano) i = 0;
        salida<<caracteres[i];
    }
    salida<<caracteres[IndiceUltimo()];
}
 /*****************************************************************************************
 ************************************   Excepciónes   *************************************
 *****************************************************************************************/


 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/

//******************************************************************************************
//T
bool Buffer::CaracterValido(const char &ultC,const char &lectura) const
{
    if(lectura == '\t' || lectura == '\n') return false;
    if(ultC == '\40' && lectura == '\40') return false;
    return true;
}

//******************************************************************************************
//T
bool Buffer::IniciaEnBloqueDeComentario()
{

    if(CantidadCaracteres() < tAB) return false;

    int aux;
    for(int i = 0  ; i<tAB; ++i)
    {
        aux = fnBf-tAB+i;
        if(aux <0 ) aux = tamano+aux;
        if(caracteres[aux] != ABC[i])
            return false;
    }

    fnBf -= tAB;
    if(fnBf < 0) fnBf = tamano + fnBf;
    lleno=false;
    return true;
}

//******************************************************************************************
//T
bool Buffer::IniciaEnLineaDeComentario()
{

    if(CantidadCaracteres() < tAL) return false;

    int aux;
    for(int i = 0  ; i<tAL; ++i)
    {
        aux = fnBf-tAL+i;
        if(aux < 0) aux = tamano+aux ;

        if(caracteres[aux] != ALC[i])
            return false;
    }

    fnBf -= tAL;
    if(fnBf < 0) fnBf = tamano + fnBf;
    lleno=false;
    return true;
}

//******************************************************************************************
//T
int Buffer::IndiceUltimo() const
{
    return (fnBf == 0 ? tamano-1 : fnBf-1);
}

//******************************************************************************************
//T
char & Buffer::ElementoI(const int i) const
{
    if(i > CantidadCaracteres() || i < 0)
        throw std::out_of_range("Está posicion no existe o est\240 vacia");

    int aux = inBf+i;
    if(aux >= tamano) aux -= tamano; //Vuelta de carro

    return caracteres[aux];
}

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/
//******************************************************************************************
//T
std::ostream & operator<<(std::ostream & salida, const Buffer & buf)
{
    buf.ImprimirBuffer(salida);
    return salida;
}
