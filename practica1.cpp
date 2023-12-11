/***************************
*                                                                            *
*      NOMBRE:      Práctica 1.1.                                            *
*      FECHA:       04 de marzo de 2022.                                     *
*      VERSIÓN:     2.0.                                                     *
*                                                                            *
*      AUTOR:       Amauri David Sotomayor Castañón                     *
*                                                                            *
*      E-MAIL:      asotomayor4@ucol.mx.                                      *
*      COMPAÑÍA:    Universidad de Colima - Facultad de Telemática.          *
*                                                                            *
*      
*                                                                              *
*                                                                            *
**************************
*                                                                            *
*      DESCRIPCIÓN DEL PROGRAMA: Arquitectura de software encargada de analizar una trama de recepción de
        16 bits para el protocolo de comunicaciones especializado en redes de sensores - IEEE 802.15.4.   *  
*                                                                            *
**************************/

#include <iostream> //libreria para controlar el flujo de la información
#include <cstdint>  //librería para utilizar tipos de datos específicos
#include <string.h> //librería empleada para la implementacion de tipos de datos String
using std::cout;    //Instancia para el uso de la salida de datos por consola
using std::string;  //Instancia para la integracion del flujo de información con String
using std::cin;
using std::endl;
#include "IEEE_802_15_4.h" //libreria propia para la gestion de tramas de recepcion de 16 bits

factory_frame Frame;
int option = 0;
int main(){

    
    do{
        cout << "1.- Mostrar direccion mac"<<endl;
        cout << "2.- Mostrar la longitud del mensaje"<<endl;
        cout << "3.- Mostrar el tipo de trama "<< endl;
        cout << "4.- Mostrar intesidad de la senal del mensaje de recepcion"<<endl;
        cout << "5.- Mostrar mensaje oculto:" <<endl;
        cout << "6.- Mostrar si la trama esta corrupta"<<endl;
        cout << "0.- Salir " <<endl;
        cin >> option;

        switch (option){

        
        
        case 1:
            Frame.data.MAC = Frame.GET_MAC();
            printf("La dirección mac es %X \n", Frame.GET_MAC());
            break;
        case 2:
            Frame.data.LENGHT = Frame.GET_LENGHT();
            printf("La longitud del mensaje es de : %d bytes \n", Frame.GET_LENGHT());
            break;
        case 3: 
            Frame.data.FRAME_TYPE = Frame.FRAME_TYPE();
                if(Frame.FRAME_TYPE()== RX_16BITS)
                printf ("La trama es un mensaje de recepción de 16 bits \n");
            break;
        case 4:
            Frame.data.RSSI = Frame.GET_RSSI();

            printf("La intesidad de la señal con la que llega el mensaje fue: -%d dbm \n", Frame.GET_RSSI());
        break;
        case 5:
            Frame.data.PAYLOAD = Frame.GET_PAYLOAD();
            printf("El mensaje oculto es: %s");
             cout<<Frame.data.PAYLOAD<<endl;

        break;
        case 6:
        Frame.data.CHECKSUM = Frame.GET_CHECKSUM();
        if (!Frame.GET_CHECKSUM())
        {
        cout<<"La trama está corrupta"<<endl;
        }else{
        cout<<"La trama no está corrupta"<<endl;
        }
        break;

        default:
            break;
        }


    }while (option!=0);
    
    //cout<<"hello world";
    //printf("0x%X",Frame.GET_MAC());
   //printf("la longitud del mensaje es %d bytes",Frame.GET_LENGHT());
   /*if(Frame.GET_FRAME_TYPE() == RX_16BITS)
   printf("la trama es un mensaje de recepcion de 16 bits");*/
    
    return 0;
}

