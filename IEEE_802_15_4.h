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
*      uC:          ESP8266
*      Nombre:      ESP8266MOD                                                 *
*                                                                            *
**************************
*                                                                            *
*      DESCRIPCIÓN DEL PROGRAMA: Arquitectura de software encargada de analizar una trama de recepción de
        16 bits para el protocolo de comunicaciones especializado en redes de sensores - IEEE 802.15.4.   *  
*                                                                            *
**************************/
#include <iostream>
#include <cstdint>
#include <cstring>
using std::cout;
using std::string;



#define HEADER 0x03         //Bytes fijos de la trama, es decir no cuentan como payload
#define RX_16BITS 0X81       // Trama de recepcion de 16bits

class factory_frame{

    public:
    // Trama de recepcion de 16bits que simula una trama real
        uint8_t frame_rx [200] = {0x7E, 0x00, 0x39, 0x81, 0x33, 0x33, 0x39, 0x01, 0x45, 0x73, 0x74, 0x65, 0x20, 0x65, 0x73, 0x20, 0x65, 0x6C, 0x20, 0x65, 0x71, 0x75, 0x69, 0x70, 0x6F, 0x20, 0x33, 0x20,
0x64, 0x65, 0x20, 0x35, 0x44, 0x20, 0x79, 0x20, 0x73, 0x61, 0x62, 0x65, 0x6D, 0x6F, 0x73, 0x20, 0x70, 0x72, 0x6F, 0x67, 0x72, 0x61, 0x6D, 0x61, 0x72, 0x20, 0x65, 0x6E,
0x20, 0x43, 0x2B, 0x2B, 0xA2};
    //Estructura de datos para almacenar la informacion que retorna los metodos
            struct 
            {
                uint16_t MAC = 0;       //Se almacena la direccion MAC de 16 bits, ejemplos: 0x1111
                uint8_t LENGHT = 0;     //Longitud total del mensaje
                uint8_t FRAME_TYPE = 0; //Tipo de mensaje
                uint8_t RSSI = 0;       //RSSI Received Signal Strength Indicator, indica potencia de recepcion
                string PAYLOAD = "";    //Mensaje comunicatica de importancia
                bool CHECKSUM = false;  //Indica si la trama esta completa es decirm que no esta corrupta
            }data;                       //Instancia u objeto de la estructura
            

        public: 
        uint16_t GET_MAC (void);        //funcion que retorna la direccion mac de 16 bits
        uint8_t GET_LENGHT (void);      //funcion que retorna la longitud de la trama
        uint8_t FRAME_TYPE (void);      //funcion que retorna el tipo de trama
        uint8_t GET_RSSI (void);        //funcion que retorna la calidad de la señal del mensaje
        string GET_PAYLOAD (void);      //funcion que retorna el mensaje de la trama (stringe)
        bool GET_CHECKSUM (void);       //funcion que retorna esta corrupta o no (booleana)




};

        uint16_t factory_frame::GET_MAC(){

            return (frame_rx[4]*256 + frame_rx[5]);
        };
        uint8_t factory_frame::GET_LENGHT (void){
            return (frame_rx[1]*256+frame_rx[2]);
        };
        uint8_t factory_frame::FRAME_TYPE (void){
            return frame_rx[3];
        };
        uint8_t factory_frame::GET_RSSI (void){
            return (frame_rx[6]);
        };

        string factory_frame::GET_PAYLOAD (void){

            string temp_frame="";

            for (uint16_t i = 8; i <GET_LENGHT()+HEADER; i++){
            temp_frame+= frame_rx[i];
            }
            return temp_frame;
        };


        bool factory_frame::GET_CHECKSUM (void){
            uint8_t suma = 0;
            
            for (uint8_t i = HEADER; i <GET_LENGHT()+HEADER; i++)
            suma += frame_rx[i];

            if ((0xff-suma) == frame_rx[GET_LENGHT()+HEADER])
            {
                return true;
            }else{
                return false;
            }

        };