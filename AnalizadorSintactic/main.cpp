#include <iostream>
#include "ASintactico.h"

using namespace std;

int main()
{
    try{
        ASintactico aS("Ejemplo.txt");
        char mov;
        string t;
        do
        {
            cout<<"Ingrese el movimiento del automata: ";
            cin>>mov;
            if(mov != '¡')
            {
                aS.Avanzar(mov);
                if(aS.estadoAceptacion() )
                {
                    t=aS.GetT();
                    if(t == "ERROR")
                    {
                        cout<<"No es aceptado... ADIOS";
                        return 0;
                    }
                    cout<<"!Es de aceptacion... \t Token generado: "<<t<<'\n';
                }
                else cout<<"No es de aceptacion :(\n";

                system("pause");
                system("cls");
            }
        }while(mov != '¡');

    }
    catch(exception &e)
    {
        cout<<e.what();
    }



    return 0;
}
