/*
 * main.c
 *
 * Created: 4/23/2024 10:40:01 PM
 *  Author: angel
 */ 
#define F_CPU 16000000
#include <xc.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "ADC/ADC.h"
#include "UART/UART.h"

volatile uint8_t buffer = 0;
volatile uint8_t valor=0;


uint8_t menu(void){
	uint8_t opcion=0;
	char mensaje[]="Hola bienvenido al programa\nIngrese el número correspondiente:\n1. Leer pot\n2. Enviar ASCII\n";
	writeUART_Text(mensaje);
	opcion=receivedChar();
	return opcion;
}

int main(void)
{
	//Puertos de salida de las LEDS
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	DDRB |= (1<<DDB0)|(1<<DDB1);
	
	//A6 Como entrada
	DDRC &= ~(1 << DDC6);
	PORTC |= (1 << PORTC6);
	
	init_ADC(0,0,128);
	initUART(9600,0,0,0,0,1,8,103);
	
	uint8_t modo=0;
	uint8_t valorADC=0;
	char bufferTX[10];
	char ASCII_P[255];
	
	
    while(1)
    {
		
	
		modo=menu();
		
		if (modo==0b0110001){
			//MODO 1 LEER POT
			
			valorADC=readADC(6);
			snprintf(bufferTX, sizeof(bufferTX), "%d\n", valorADC);
			for (int i = 0; bufferTX[i] != '\0'; i++) {
				writeUART_car(bufferTX[i]);
			}
			writeUART_car('\n');
			} else if (modo==0b0110010){
				
				snprintf(ASCII_P, sizeof(ASCII_P), "Ingrese el carácter a enviar:\n");
				writeUART_Text(ASCII_P);
				
				PORTB=0;
				PORTD=0;
				buffer=receivedChar();
				valor = (buffer & 0b00111111);
				valor <<=2;
				PORTD |= valor;
				valor = (buffer & 0b11000000);
				valor >>=6;
				PORTB |= valor;
				
				
				} else{
					writeUART_car('\n');
					writeUART_car('\n');
					snprintf(ASCII_P, sizeof(ASCII_P), "Ingrese un número válido en las opciones\n");
					writeUART_Text(ASCII_P);
					writeUART_car('\n');
				}
		
		
	
		_delay_ms(10);
    }
}


/*
		*/

		
        //TODO:: Please write your application code 