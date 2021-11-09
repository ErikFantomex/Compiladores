/* Nombre: .cpp
   Autor:
   Fecha:
   Descripción:
*/

#include "../ASintactico.h"



 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

//*************************************************************************************
ASintactico::ASintactico(const char *direccion)
{
    InicializarAFD(direccion,autConst,&listTonken);
    std::cout<<autConst<<'\n';

}


//*************************************************************************************
ASintactico::~ASintactico()
{
    delete [] listTonken;
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
    autConst.Reset();
    autVar.Reset();
}

//*************************************************************************************
void ASintactico::Avanzar(const char &c)
{
    autConst.Avanzar(((int) c) + SANGRIA);
}

//*************************************************************************************
bool ASintactico::estadoAceptacion() const
{
    return autConst.estadoAceptacion();
}


//*************************************************************************************
std::string ASintactico::GetT() const
{
    if(!estadoAceptacion())throw Grosero();
    return listTonken[autConst.GetEstadoAct() ];
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
    return "Hay una funcion para saber si el estado es de aceptacion y no la usaste... Grosero...";
}

//*************************************************************************************
const char * ASintactico::TablaIncorrecta::what() const throw()
{
    return "Hay un error en el automata del archivo...";
}

 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/
//*************************************************************************************
void ASintactico::InicializarAFD(const char *dir, AFD & afd, std::string ** lTokens) const
{
    std::ifstream archivo(dir);
    ArbolDeBVL<Llave> mapa;
    int caracDeCol[TAMALFABETO+2];

    if(!archivo)
    {
        throw DireccionNula();
        archivo.close();
        throw DireccionNula();
    }


    //Leemos la primera linea para saber que caracter representa cada columna
    LigarColumnas(caracDeCol,archivo);

    //Le asignamos una fila a cada estado
    int e =NumerarEstados(mapa,archivo);

    //Dimencionar el automata y la lista de token
    DimencionarAFD(e,afd,lTokens);

    //llenamos la tabla, los estados de aceptacion y los T generados
    LlenarAFD(afd,lTokens,mapa,archivo,caracDeCol);

}

//*************************************************************************************
void ASintactico::LigarColumnas(int r[],std::ifstream &ent) const
{
    int i;
    char texto[2000];
    ent.getline(texto,2000);

    for( i=0; texto[i] != '\t' ; ++i);
    for(int col=0; texto[i] != '\0' ; ++i)
    {
        if(texto[i] == '\t') continue;
        //El blog de notas guarda los caracteres especiales de una manera 'especial'
            //¡Los guarda en tres partes¡ Hay que normalizarlos en uno
        r[col++]= ((int)NormalizarCaracter(texto,i))+SANGRIA;
        std::cout<<r[col-1]<<' '<<(char)(r[col-1]-SANGRIA)<<'\n';
    }
}


//*************************************************************************************
int ASintactico::NumerarEstados(ArbolDeBVL<Llave> &abl,std::ifstream &ent) const
{
    std::string sAux;
    char texto[2000];
    int nEstados;
    Llave aux;

    for(nEstados=0; !ent.eof() ; ++nEstados)
    {
        //Aqui no se debe normalizar el texto porque (A priori) los estados no tienen
            //carcteres especiales (Son de la forma q_0)
        ent.getline(texto,2000);

        sAux.clear();
        for(int j=0;texto[j]!='\t' && texto[j]!='*';++j)
            sAux+=texto[j];

        aux.Set(sAux,nEstados);
        abl.Agregar(aux);
    }
    return nEstados;
}

//*************************************************************************************
void ASintactico::DimencionarAFD(int &n,AFD &afd, std::string **lTokens) const
{
    //Nuestro alfabeto es de 68 elementos, pero para hacerlo más dinamico se declara de
        // 268 por el número de caracteres ascii
    afd.Dimencionar(n,TAMALFABETO+2,-1);
    (*lTokens) = new std::string[n];
}

//*************************************************************************************
void ASintactico::LlenarAFD(AFD & afd, std::string **lTokens, ArbolDeBVL<Llave> & mapa,
        std::ifstream &ent, int relCol[]) const
{
    bool esAcept;
    int indice;
    char texto[2000];
    ent.seekg(0, ent.beg);
    ent.getline(texto,2000);//Saltamos la primera linea(Los car. de las columnas)

    for(int fila=0; !ent.eof() ; ++fila)
    {
        indice=0;
        ent.getline(texto,2000);

        //Se lee el nombre del estado y se verifica si es de aceptacion o no
        esAcept = IdentificarEstado(texto,indice);

        if( esAcept ) (*lTokens)[fila] = GetTokenEstado(texto,indice);
        else (*lTokens)[fila] = NOACEPTACION;
        afd.SetEstadosA(fila, esAcept);

        //Se llena la matriz de transicion
        LeerEstado(afd,fila,mapa,indice,relCol,texto);
    }
}


//*************************************************************************************
bool ASintactico::IdentificarEstado(const char ent[], int &i) const
{

    for(i=0;ent[i]!='\t' && ent[i] != '*' ;++i) ;
    return ent[i]=='*';
}

//*************************************************************************************
std::string ASintactico::GetTokenEstado(const char ent[], int &i) const
{
    std::string tGen="";
    if(ent[i] != '*') throw Grosero();

    for(++i;ent[i]!='\t';++i)
        tGen+=ent[i];

    return tGen;
}


//*************************************************************************************
void ASintactico::LeerEstado(AFD & afd, int &estado, ArbolDeBVL<Llave> &mapa, int &i,
        int relCol[],const char ent[] ) const
{
    std::string sAux;
    Llave aBuscar;

    for(int colD=0,colR;ent[i]!='\0';)
    {
        if(ent[i] == '\t')
        {
            ++i;
            continue;
        }

        sAux.clear();
        while(ent[i]!='\t' && ent[i] != '\0')
            sAux+=ent[i++];

        aBuscar.Set(sAux);

        colR=relCol[colD++];
        afd[estado][colR]= mapa.Buscar(aBuscar).GetValor();
    }
}

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/
