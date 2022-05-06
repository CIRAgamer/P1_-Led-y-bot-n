/*
 * GPIO.c
 *
 *  Created on: 19 sep. 2021
 *      Author: Richard
 *       GPIO Port A (APB): 0x4000.4000
        GPIO Port B (APB): 0x4000.5000
        GPIO Port C (APB): 0x4000.6000
        GPIO Port D (APB): 0x4000.7000
        GPIO Port E (APB): 0x4002.4000
        GPIO Port F (APB): 0x4002.5000


 */
#include "../include.h"

volatile REG_2 * const ISR = (REG_2 *)0xE000E010;
volatile REG_1 * const SYSCTL = (REG_1 *)0x400FE600;
volatile REG_ * const PORTF = (REG_ *)0x40025000; //5

extern void Configurar_GPIO(void){
    //Encender el periferico Run Clock Control del GPIO
    SYSCTL->RCGC.GPIO_R |= (1<<5); //habilita puerto F
    // si es necesario desbloquear algun puerto
    PORTF->GPIO.LOCK_R = 0x4C4F434B; //desbloquea el puerto F
    PORTF->GPIO.CR_R = (1<<0);  //el pin 0 desbloquealo
    //Configurar entradas y salidas
    PORTF->GPIO.DIR_R |= (0<<4)|(1<<3)|(1<<2)|(1<<1)|(0<<0); //Entradas 1 y salidas 0
                      // BTON1   LEDV  LEDA    LEDR  BTON2
                      //   0      1      1       1     0
    //Desactivar funci�n alternativa
    PORTF->GPIO.AFSEL_R[0] |= 0x00; //quiero que all el puerto f sea configurado con el gpio para habiliar las resisntancias internas
    PORTF->GPIO.PUR_R = (1<<4) | (1<<0); // BTON1&2 resistencias pull up
    //Activamos el funcionamiento digital
    PORTF->GPIO.DEN_R = (1<<4) | (1<<3) | (1<<1) |(1<<0);
    //desactivamos la funcion analogica
    PORTF->GPIO.AMSEL_R |= 0x00;
    //Vinculamos los pines al gpio
    PORTF->GPIO.PCTL_R |= 0x00;
}

//metodo para inciar interrupciones //

extern void Iniciar_interrup(void){
    //ver la tabla de vectores de interrupci�n (Registros NVIC
    //el numero de interrupci�n del GPIOF es: 30
    //Cada registro PRI configura 4 vectores
    //La prioridad es 30/4 = 7
    //NIVIC_PRI7_R
    //Ademas acepta 8 niveles (0 m�s, 7 menos)
    //:V
    ISR->NIVIC.PRI7_R = (ISR->NIVIC.PRI7_R& 0xff00ffff) | (0x00800000);
    //Para habilitar el n�mero de interrupcion se cuenta con 4 registros
    //registros de 32 bits, como es el numero 30 necesitamos 1 registro
    //para poder decirle al micro que es la numero 30
    ISR->NIVIC.EN0_R = 0x40000000; //(Prende 1 el bit 30) si se excede, restar la cantidad que se exceden
    //Configuraci�n del modo de interrupcion del gpio
    //usar registros IS,IBE,IEV,RIS(son el tipo de interrupci�n)
    //IS: Interrupt Sense // 0 = Edge Interrupt // 1 = Level Interrupt
    //IBE: Interrupt Both Edge //
    //0 = El borde de interrupci�n es controlado por IEV //
    //1 = La interrupcion detecta borde de subida y borde de bajada
    //IEV: Interrup Event
    //0 = borde de bajada o nivel bajo
    //1 = borde de subida o nivel alto
    //Fuente de la interrupci�n, se limpia el registro
    PORTF->GPIO.IM_R |= (0<<4) | (0<<0);
    PORTF->GPIO.IS_R |= (0<<4) | (0<<0);
    PORTF->GPIO.IBE_R |= (0<<4) | (0<<0);
    PORTF->GPIO.IEV_R |= (1<<4) | (1<<0); //(detecta los bordes de subida
    PORTF->GPIO.RIS_R |= (0<<4) | (0<<0);   //registro de estado
    PORTF->GPIO.IM_R |= (1<<4) | (1<<0);    //Se le ordena enviar la interrupci�n
    //desde los pines fuente  de la misma
}

extern void Parpadeo_R(void){
    uint32_t i;
    PORTF->GPIO.DATA_R[255] |= (1<<1);
    for(i=0;i<100000;i++){}
    PORTF->GPIO.DATA_R[255] &= ~(1<<1);
    for(i=0;i<100000;i++){}
}

extern void Parpadeo_V(void){
    uint32_t i;
    PORTF->GPIO.DATA_R[255] |= (1<<3);
    for(i=0;i<100000;i++){}
    PORTF->GPIO.DATA_R[255] &= ~(1<<3);
    for(i=0;i<100000;i++){}
}

//Metodo para ejecutar interrupciones

extern void GPIOF_INT_ISR(void){
    if(PORTF->GPIO.RIS_R == (1<<0)){ //PF0 el 0 representa el estado de cambio
        Parpadeo_R();
    }
    if(PORTF->GPIO.RIS_R == (1<<4)){
        Parpadeo_V();
    }
    PORTF->GPIO.ICR_R |= (1<<4)| (1<<3) | (1<<1) |(1<<0); //Limpiamos interrupciones
            //Si no se pone solo interumpe 1 vez
}

