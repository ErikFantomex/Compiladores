/*
Nombre:      ArbolBA.h
Autor(es):   Aguilar H, Escobar R, Velazquez L y Villalba J.
Fecha:       19/05/21
Descripción: Archivo de implementación de la clase 'ArbolBA'
*/

#include"ArbolBA.h"


 /*****************************************************************************************
 **********************************   Constructores    ************************************
 *****************************************************************************************/

//*************************************************************************************
template<typename T, unsigned G>
ArbolBA<T,G>::ArbolBA()
{
    if(G < 4) throw std::logic_error("No puede existir un arbol B con grado menor a 4...");
    nElementos = 0;
    raiz = NULL;
}

//*************************************************************************************
template<typename T, unsigned G>
ArbolBA<T,G>::ArbolBA(const ArbolBA & abl)
{
    if(G < 4) throw std::logic_error("No puede existir un arbol B con grado menor a 4...");
    nElementos = 0;
    raiz = NULL;
    *this = abl;
}

//*************************************************************************************
template<typename T, unsigned G>
ArbolBA<T,G>::~ArbolBA()
{
    Vaciar();
}


 /*****************************************************************************************
 ************************************    Operadores    ************************************
 *****************************************************************************************/
//*************************************************************************************
template<typename T, unsigned G>
ArbolBA<T,G> & ArbolBA<T,G>::operator= (const ArbolBA<T,G> & abl)
{
    if(this == & abl) return *this;
    Vaciar();
    Copiar(this->raiz,abl.raiz);
    this->nElementos = abl.nElementos;
    return *this;
}

 /*****************************************************************************************
 ********************************   Metodos y funciónes   *********************************
 *****************************************************************************************/

//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::Agregar(const T & emt)
{
    Agregar(emt,raiz);
    if(raiz->nE == 2*G)
    {
        unsigned i,tope;
        Nodo *aux1=new Nodo();
        Nodo *aux2=new Nodo();
        Nodo *aux3=new Nodo();

        tope=(2*G-2)/3;
        for(i=0; i<tope ;++i)
        {
            aux1->elemento[i]=raiz->elemento[i];
            aux1->hijo[i]=raiz->hijo[i];
        }
        aux1->hijo[tope]=raiz->hijo[i];
        aux1->nE=tope;

        raiz->elemento[0]=raiz->elemento[i];
        ++i;

        tope=(2*G-1)/3;
        for(unsigned k=0; k<tope ;++k,++i)
        {
            aux2->elemento[k]=raiz->elemento[i];
            aux2->hijo[k]=raiz->hijo[i];
        }
        aux2->hijo[tope]=raiz->hijo[i];
        aux2->nE=tope;

        raiz->elemento[1]=raiz->elemento[i];
        ++i;

        tope=(2*G)/3;
        for(unsigned k=0; k<tope ;++k,++i)
        {
            aux3->elemento[k]=raiz->elemento[i];
            aux3->hijo[k]=raiz->hijo[i];
        }
        aux3->hijo[tope]=raiz->hijo[i];
        aux3->nE=tope;

        raiz->hijo[0]=aux1;
        raiz->hijo[1]=aux2;
        raiz->hijo[2]=aux3;

        for(unsigned k=2;k<raiz->nE;++k)
        {
            raiz->elemento[k]=NULL;
            raiz->hijo[k+1]=NULL;
        }
        raiz->nE=2;
    }
}


//*************************************************************************************
template<typename T, unsigned G>
bool ArbolBA<T,G>::Eliminar(const T & emt)
{
    bool res=Eliminar(emt,raiz);
    if(raiz->nE == 0)
    {
        delete raiz;
        raiz=NULL;
        return res;
    }
    if(!raiz->EsHoja() && raiz->nE == 1)
    {
        unsigned minimo = (2*G-2)/3;
        if(raiz->hijo[0]->nE == minimo && raiz->hijo[1]->nE==minimo)
        {
            unsigned i;
            T *aux=raiz->elemento[0];
            Nodo *hjoI =raiz->hijo[0];
            Nodo *hjoD =raiz->hijo[1];

            for(i=0;i<hjoI->nE ;++i)
            {
                raiz->elemento[i]= hjoI->elemento[i];
                raiz->hijo[i]= hjoI->hijo[i];
            }
            raiz->hijo[i]= hjoI->hijo[i],

            raiz->elemento[i]=aux;
            ++i;

            for(unsigned k=0;k<hjoD->nE ;++i,++k)
            {
                raiz->elemento[i]= hjoD->elemento[k];
                raiz->hijo[i]= hjoD->hijo[k];
            }
            raiz->hijo[i]= hjoD->hijo[hjoD->nE];
            raiz->nE=i;

            delete hjoI;
            delete hjoD;
        }
    }

    return res;
}


//*************************************************************************************
template<typename T, unsigned G>
T ArbolBA<T,G>::Buscar(const T & emt) const
{
    return Buscar(emt,raiz);
}


//*************************************************************************************
template<typename T, unsigned G>
unsigned ArbolBA<T,G>::NumeroDeElementos() const
{
    return nElementos;
}


//*************************************************************************************
template<typename T, unsigned G>
bool ArbolBA<T,G>::Vaciar()
{
    if(raiz == NULL) return false;
    while(raiz!= NULL) Eliminar(*(raiz->elemento[0]));
    return true;
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::Imprimir(Recorrido r/*=ASCENDENTE*/,std::ostream & salida/*=std::cout*/) const
{
    switch(r)
    {
        case PORNIVEL:
            ImprimirPN(salida);
            return;
            break;

        case ASCENDENTE:
            if(nElementos > 0)
            {
                salida<<'{';
                ImprimirA(raiz,salida);
                if(nElementos != 0) salida<<"\b\b";
                salida<<'}';
            }
            break;

        case DESCENDENTE:
            if(nElementos > 0)
            {
                salida<<'{';
                ImprimirD(raiz,salida);
                if(nElementos != 0) salida<<"\b\b";
                salida<<'}';
            }
            break;
    }
}

 /****************************************************************************************
 *************************************   Exceptions   ************************************
 *****************************************************************************************/

//*************************************************************************************
template<typename T, unsigned G>
const char * ArbolBA<T,G>::NodoNoEnc::what() const throw()
{
    return "No nodo...";
}

 /*****************************************************************************************
 *********************************   Metodos privados   ***********************************
 *****************************************************************************************/
//*************************************************************************************
template<typename T, unsigned G>
ArbolBA<T,G>::Nodo::Nodo():nE(0)
{

    hijo[2*G] = NULL;
    for(int i = 2*G - 1; i >= 0; --i){
        elemento[i] = NULL;
        hijo[i] = NULL;
    }
}


//*************************************************************************************
template<typename T, unsigned G>
unsigned ArbolBA<T,G>::Nodo::BuscarLugar(const T &emt) const
{
    for(unsigned i=0;i<nE;++i)
        if(emt<=*(elemento[i])) return i;

    return nE;
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::Nodo::Insertar(const T &emt, unsigned i)
{
    T *nuevo= new T;
    (*nuevo)=emt;
    unsigned j = BuscarLugar(emt);
    for ( unsigned i = nE ; i > j ; --i )
        elemento[i] = elemento[i-1];
    elemento[j] = nuevo;
    ++nE;
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::Nodo::Eliminar(unsigned i)
{
    delete elemento[i];
    for ( unsigned j = i ; j < nE ; ++j )
        elemento[j] = elemento[j+1];
    elemento[nE] = NULL;
    --nE;
}

//*************************************************************************************
template<typename T, unsigned G>
bool ArbolBA<T,G>::Nodo::EsHoja()
{
    return (hijo[0] == NULL && hijo[1] == NULL);
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::Agregar(const T & emt, Nodo *&subRaiz)
{
    if(subRaiz == NULL){
        raiz = new Nodo();
        raiz->Insertar(emt,0);
        ++nElementos;
        return;
    }

    unsigned i = subRaiz->BuscarLugar(emt);

    if(subRaiz->EsHoja()){
        subRaiz->Insertar(emt, i);
        ++nElementos;
        return;
    }else{
        Agregar(emt, subRaiz->hijo[i]);
        if(subRaiz->hijo[i]->nE == G) Partir(subRaiz,i);
    }
}


//*************************************************************************************
template<typename T, unsigned G>
bool ArbolBA<T,G>::Eliminar(const T & emt, Nodo *&subRaiz)
{
    if ( subRaiz == NULL ) return false;
    bool res;
    unsigned i = subRaiz->BuscarLugar(emt);
    if ( subRaiz->elemento[i] != NULL && emt == *(subRaiz -> elemento[i]) ){
        if ( subRaiz -> EsHoja() ){
            subRaiz ->Eliminar(i);
            --nElementos;
            return true;
        } else {
            T *mayorDeMenores = Mayor(subRaiz->hijo[i]);
            *(subRaiz -> elemento[i]) = *mayorDeMenores;
            Eliminar(*mayorDeMenores,subRaiz->hijo[i]);
            if ( subRaiz->hijo[i] != NULL && subRaiz->hijo[i]->nE < (2 * G - 2)/3 )
                Mezclar(subRaiz,i);
            return true;
        }
    } else {
        res = Eliminar( emt, subRaiz->hijo[i] );
        if ( subRaiz->hijo[i] != NULL && subRaiz->hijo[i]->nE < (2 * G - 2)/3 )
            Mezclar(subRaiz,i);
        return res;
    }
}


//*************************************************************************************
template<typename T, unsigned G>
const T & ArbolBA<T,G>::Buscar(const T & emt,Nodo *subRaiz) const
{
    if ( subRaiz == NULL ) throw NodoNoEnc();

    unsigned i = subRaiz->BuscarLugar(emt);
    T *_ =(subRaiz -> elemento[i]);
    if ( i != subRaiz->nE && emt == *_ ) return *_;
    else return Buscar( emt, subRaiz->hijo[i] );
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::Partir(Nodo *&subRaiz, unsigned i)
{
    //Preferiblemente se parte con la derecha

    if(i != subRaiz->nE)
    {
        if(subRaiz->hijo[i+1]->nE < G-1) CompartirD(subRaiz,subRaiz->hijo[i],subRaiz->hijo[i+1],i);
        else PartirEnTres(subRaiz, subRaiz->hijo[i],subRaiz->hijo[i+1],i);
    }
    else
    {
        --i;
        if(subRaiz->hijo[i]->nE < G-1) CompartirI(subRaiz,subRaiz->hijo[i],subRaiz->hijo[i+1],i);
        else PartirEnTres(subRaiz,subRaiz->hijo[i],subRaiz->hijo[i+1],i);
    }
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::PartirEnTres(Nodo *&subRaiz, Nodo *hjoI, Nodo *hjoD, unsigned i)
{
    T *aux;
    unsigned tope,topeAux,j,k;
    Nodo *aux1 =new Nodo();
    Nodo *aux2 =new Nodo();
    Nodo *aux3 =new Nodo();

    aux = subRaiz->elemento[i];
    for(j=subRaiz->nE ; j > i ;--j)
    {
        subRaiz->elemento[j]=subRaiz->elemento[j-1];
        subRaiz->hijo[j+1]=subRaiz->hijo[j];
    }

    //Inicio del armado del primer hijo
    tope= (2*G-2)/3;
    for(j=0;j<tope;++j)
    {
        aux1->elemento[j] = hjoI->elemento[j];
        aux1->hijo[j] = hjoI->hijo[j];
    }
    aux1->hijo[tope] = hjoI->hijo[tope];
    //Fin del armado del primer hijo

    subRaiz->elemento[i]=hjoI->elemento[tope];

    //Inicio del armado del segundo hijo
    j=0;
    topeAux = hjoI->nE-tope-1;
    for(j=0; j<topeAux ;++j)
    {
        aux2->elemento[j] = hjoI->elemento[tope+j+1];
        aux2->hijo[j] = hjoI->hijo[tope+j+1];
    }
    aux2->elemento[j]=aux;
    aux2->hijo[j] = hjoI->hijo[hjoI->nE];

    ++j;
    tope=(G*2-1)/3;
    for(k=0 ; j<tope;++j,++k)
    {
        aux2->elemento[j] = hjoD->elemento[k];
        aux2->hijo[j] = hjoD->hijo[k];
    }
    aux2->hijo[j] = hjoD->hijo[k];
    //Fin del armado del segundo hijo

    subRaiz->elemento[i+1]=hjoD->elemento[k];
    ++k;

    //Inicio del armado del tercer hijo
    tope= (2*G)/3;
    for(j=0;j<tope;++k,++j)
    {
        aux3->elemento[j] = hjoD->elemento[k];
        aux3->hijo[j] = hjoD->hijo[k];
    }
    aux1->hijo[j] = hjoD->hijo[tope];
    //Fin del armado del tercer hijo

    ++subRaiz->nE;
    subRaiz->hijo[i]=aux1;
    subRaiz->hijo[i+1]=aux2;
    subRaiz->hijo[i+2]=aux3;
    aux1->nE=(2*G-2)/3;
    aux2->nE=(2*G-1)/3;
    aux3->nE=(2*G)/3;
    delete hjoI;
    delete hjoD;
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::Mezclar(Nodo *&subRaiz, unsigned i)
{
    unsigned minimo=(2*G-2)/3;
    if(i==0)
    {
        if(subRaiz->hijo[1]->nE > minimo)
            CompartirI(subRaiz,subRaiz->hijo[0],subRaiz->hijo[1],0);
        else
        {
            if(subRaiz->hijo[2]->nE > minimo)
            {
                CompartirI(subRaiz,subRaiz->hijo[0],subRaiz->hijo[1],0);
                CompartirI(subRaiz,subRaiz->hijo[1],subRaiz->hijo[2],1);
            }
            else
            {
                MezclarEnDos(subRaiz,subRaiz->hijo[0],subRaiz->hijo[1],subRaiz->hijo[2],0);
            }
        }
        return;
    }
    if(i==1)
    {
        if(subRaiz->hijo[0]->nE > minimo)
            CompartirD(subRaiz,subRaiz->hijo[0],subRaiz->hijo[1],0);
        else
        {
            if(subRaiz->hijo[2]->nE > minimo)
                CompartirI(subRaiz,subRaiz->hijo[1],subRaiz->hijo[2],1);
            else
            {
                MezclarEnDos(subRaiz,subRaiz->hijo[0],subRaiz->hijo[1],subRaiz->hijo[2],0);
            }
        }
        return;
    }
    if(subRaiz->hijo[i-1]->nE > minimo)
        CompartirD(subRaiz,subRaiz->hijo[i-1],subRaiz->hijo[i],i-1);
    else
    {
        if(subRaiz->hijo[i-2]->nE > minimo)
        {
            CompartirD(subRaiz,subRaiz->hijo[i-1],subRaiz->hijo[i],i-1);
            CompartirD(subRaiz,subRaiz->hijo[i-2],subRaiz->hijo[i-1],i-2);
        }
        else
        {
            MezclarEnDos(subRaiz,subRaiz->hijo[i-2],subRaiz->hijo[i-1],subRaiz->hijo[i],i-2);
        }
    }

}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::MezclarEnDos(Nodo *&subRaiz, Nodo *hjoI, Nodo *hjoM, Nodo *hjoD, unsigned i)
{
    Nodo *todos =new Nodo();
    Nodo *aux1=new Nodo();
    Nodo *aux2=new Nodo();
    unsigned k=0,mitad;

    for(unsigned j=0;j<hjoI->nE;++j,++k)
    {
        todos->elemento[k]=hjoI->elemento[j];
        todos->hijo[k]=hjoI->hijo[j];
    }
    todos->elemento[k]=subRaiz->elemento[i];
    todos->hijo[k]=hjoI->hijo[hjoI->nE];
    ++k;

    for(unsigned j=0;j<hjoM->nE;++j,++k)
    {
        todos->elemento[k]=hjoM->elemento[j];
        todos->hijo[k]=hjoM->hijo[j];
    }
    todos->elemento[k]=subRaiz->elemento[i+1];
    todos->hijo[k]=hjoM->hijo[hjoM->nE];
    ++k;

    for(unsigned j=0;j<hjoD->nE;++j,++k)
    {
        todos->elemento[k]=hjoD->elemento[j];
        todos->hijo[k]=hjoD->hijo[j];
    }
    todos->hijo[k]=hjoD->hijo[hjoD->nE];


    mitad=k/2;
    for(unsigned j =0;j<mitad;++j)
    {
        aux1->elemento[j]=todos->elemento[j];
        aux1->hijo[j]=todos->hijo[j];
    }
    aux1->hijo[mitad]=todos->hijo[mitad];

    subRaiz->elemento[i]=todos->elemento[mitad];



    for(unsigned j=mitad+1; j<k;++j)
    {
        aux2->elemento[j-mitad-1]=todos->elemento[j];
        aux2->hijo[j-mitad-1]=todos->hijo[j];
    }
    aux2->hijo[k-mitad-1]=todos->hijo[k];

    std::cout<<"Presta atencion aqui: \n";
    for(unsigned j=i+1;j<subRaiz->nE;++j)
    {
        std::cout<<subRaiz->elemento[j];

        subRaiz->elemento[j]=subRaiz->elemento[j+1];
        subRaiz->hijo[j+1]=subRaiz->hijo[j+2];
    }

    for(unsigned j=0;j<subRaiz->nE;++j)
    {
        std::cout<<subRaiz->elemento[j]<<' ';
        std::cout<<subRaiz->hijo[j]<<' ';
    }
    std::cout<<subRaiz->hijo[subRaiz->nE]<<' ';

    subRaiz->hijo[i]=aux1;
    subRaiz->hijo[i+1]=aux2;


    --subRaiz->nE;
    aux1->nE=mitad;
    aux2->nE=k-mitad-1;

    /*
    delete hjoI;
    delete hjoM;
    delete hjoD;
    delete todos;*/
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::CompartirD(Nodo *&subRaiz, Nodo *hjoI, Nodo *hjoD, unsigned i)
{
    T *aux = subRaiz->elemento[i];
    subRaiz->elemento[i] = hjoI->elemento[hjoI->nE - 1];
    for(unsigned j = hjoD->nE; j > 0; --j) hjoD->elemento[j] = hjoD->elemento[j-1];
    hjoD->elemento[0] = aux;

    for(unsigned j = hjoD->nE+1; j > hjoD->nE; --j) hjoD->hijo[j] = hjoD->hijo[j-1];
    hjoD->hijo[0] = hjoI->hijo[hjoI->nE];
    hjoI->hijo[hjoI->nE] = NULL;

    hjoI->nE--;
    hjoD->nE++;
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::CompartirI(Nodo *&subRaiz, Nodo *hjoI, Nodo *hjoD, unsigned i)
{
    T *aux = subRaiz->elemento[i];
    subRaiz->elemento[i] = hjoD->elemento[0];
    for(unsigned j = 0; j < hjoD->nE; ++j) hjoD->elemento[j] = hjoD->elemento[j+1];
    hjoI->elemento[hjoI->nE] = aux;

    hjoI->hijo[hjoI->nE+1] = hjoD->hijo[0];
    for(unsigned j = 0; j < hjoD->nE; ++j) hjoD->hijo[j] = hjoD->hijo[j+1];
    hjoD->hijo[hjoD->nE] = NULL;

    hjoD->nE--;
    hjoI->nE++;
}


//*************************************************************************************
template<typename T, unsigned G>
T *& ArbolBA<T,G>::Mayor(Nodo *subRaiz) const
{
    if(subRaiz->EsHoja()){
        return subRaiz->elemento[subRaiz->nE-1];
    }
    else{
        return Mayor(subRaiz->hijo[subRaiz->nE]);
    }
}


//*************************************************************************************
template<typename T, unsigned G>
T *& ArbolBA<T,G>::Menor(Nodo *subRaiz) const
{
    if(subRaiz->EsHoja()){
        return subRaiz->elemento[0];
    }
    else{
        return Menor(subRaiz->Hijo[0]);
    }
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::ImprimirA(Nodo *subRaiz,std::ostream & salida) const
{
    if(subRaiz == NULL) return;
    for(unsigned i = 0; i < subRaiz->nE ; ++i){
        ImprimirA(subRaiz->hijo[i],salida);
        salida << *(subRaiz->elemento[i]) << ", ";
    }
    ImprimirA(subRaiz->hijo[subRaiz->nE],salida);
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::ImprimirD(Nodo *subRaiz,std::ostream & salida) const
{
    if(subRaiz == NULL) return;
    for(int i = (int) subRaiz->nE; i > 0; --i){
        ImprimirD(subRaiz->hijo[i],salida);
        salida << *(subRaiz->elemento[i-1]) << ", ";
    }
    ImprimirD(subRaiz->hijo[0],salida);
}


//*************************************************************************************
template<typename T, unsigned G>
void ArbolBA<T,G>::ImprimirPN(std::ostream & salida) const
{
    if(nElementos == 0) return;

    ColaCircular<Nodo*>cola;
    cola.Encolar(raiz);
    Nodo *aux;
    while(!cola.EstaVacia())
    {
        for(unsigned i=cola.ObtenerTam();i>0;--i)
        {
            aux=cola.PrimElemento();
            cola.Desencolar();
            if(aux == NULL) continue;

            salida<<'{';
            for(unsigned j=0;j<aux->nE;++j)
            {
                salida<<*(aux->elemento[j])<<", ";
                cola.Encolar(aux->hijo[j]);
            }
            cola.Encolar(aux->hijo[aux->nE]);
            if(aux->nE >= 1) salida<<"\b\b";
            salida<<"} :"<<aux->nE<<"\t  ";

        }
        salida << "\n\n";

    }
}


//*************************************************************************************
template<typename T, unsigned G>
void  ArbolBA<T,G>::Copiar(Nodo *&copia,const Nodo *original)
{
    if(original == NULL) return;

    copia = new Nodo();
    for(unsigned i=0;i<original->nE;++i)
    {
        copia->elemento[i]=new T(*original->elemento[i]);
        Copiar(copia->hijo[i],original->hijo[i]);
    }
    Copiar(copia->hijo[original->nE],original->hijo[original->nE]);
    copia->nE=original->nE;
}
//*************************************************************************************
#include <fstream>
#include <cstdlib>
//Función encargada de capturar un arbol mediante un archivo.
template<typename T, unsigned G>
bool ArbolBA<T,G>::CapturarXArchivo(const char nombreArchivo[56])
{
    std::ifstream flujo(nombreArchivo);
    if(!flujo){
        std::cout << "Error, el archivo " << nombreArchivo << " no pudo ser abierto..." << std::endl;
        system("pause");
        flujo.close();
        return false;
    }
    T elemento;
    while (flujo >> elemento) {
        std::cout << "\nElemento a ingresar: " << elemento << "\n\n";
        Agregar(elemento);
        std::cout << *this << "Ascendente: ";
        Imprimir(ASCENDENTE);
        std::cout << "\n\n";
        system("pause");
        system("cls");
    }
    flujo.close();
    return true;
}

 /*****************************************************************************************
 ***************************   Funciones externas y amigas   ******************************
 *****************************************************************************************/
template <typename t,unsigned g>
std::ostream & operator<<(std::ostream & salida,const ArbolBA<t,g> & abl)
{
    abl.Imprimir(PORNIVEL,salida);
    return salida;
}
