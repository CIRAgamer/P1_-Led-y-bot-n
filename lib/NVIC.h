/*
 * NVIC.h
 *
 *  Created on: 19 sep. 2021
 *      Author: Richard
 */

#ifndef NVIC_NVIC_H_
#define NVIC_NVIC_H_

//La base de las interrupciones es 0xE000E000

typedef union {
    struct {
        uint32_t ST_CTRL;  //0xE000E010
        uint32_t ST_RELOAD_R;
        uint32_t ST_CURRENT_R[58]; //0x018 offset
        //+58 posiciones de 4 Bytes
        uint32_t EN0_R; //offset 0x100
        uint32_t EN1_R;
        uint32_t EN2_R;
        uint32_t EN3_R;
        uint32_t EN4_R[28]; //0x110 offset
        //+28 posiciones de 4 Bytes
        uint32_t DIS0_R; //offset 0x180
        uint32_t DIS1_R;
        uint32_t DIS2_R;
        uint32_t DIS3_R;
        uint32_t DIS4_R[28];//0x190 offset
        //+28 posiciones de 4 Bytes
        uint32_t PEND0_R; //offset 0x200
        uint32_t PEND1_R;
        uint32_t PEND2_R;
        uint32_t PEND3_R;
        uint32_t PEND4_R[28];//0x210 offset
        //+28 posiciones de 4 Bytes
        uint32_t UNPEND0_R; //offset 0x280
        uint32_t UNPEND1_R;
        uint32_t UNPEND2_R;
        uint32_t UNPEND3_R;
        uint32_t UNPEND4_R[28];//0x290 offset
        //+28 posiciones de 4 Bytes
        uint32_t ACTIVE0_R; //offset 0X300
        uint32_t ACTIVE1_R;
        uint32_t ACTIVE2_R;
        uint32_t ACTIVE3_R;
        uint32_t ACTIVE4_R[60];//0x310 offset
        //+60 posiciones de 4 Bytes
        uint32_t PRI0_R; //offset 0X400
        uint32_t PRI1_R;
        uint32_t PRI2_R;
        uint32_t PRI3_R;
        uint32_t PRI4_R;
        uint32_t PRI5_R;
        uint32_t PRI6_R;
        uint32_t PRI7_R;
        uint32_t PRI8_R;
        uint32_t PRI9_R;
        uint32_t PRI10_R;
        uint32_t PRI11_R;
        uint32_t PRI12_R;
        uint32_t PRI13_R;
        uint32_t PRI14_R;
        uint32_t PRI15_R;
        uint32_t PRI16_R;
        uint32_t PRI17_R;
        uint32_t PRI18_R;
        uint32_t PRI19_R;
        uint32_t PRI20_R;
        uint32_t PRI21_R;
        uint32_t PRI22_R;
        uint32_t PRI23_R;
        uint32_t PRI24_R;
        uint32_t PRI25_R;
        uint32_t PRI26_R;
        uint32_t PRI27_R;
        uint32_t PRI28_R;
        uint32_t PRI29_R;
        uint32_t PRI30_R;
        uint32_t PRI31_R;
        uint32_t PRI32_R;
        uint32_t PRI33_R;
        uint32_t PRI34_R;

    }NIVIC;
}REG_2;



#endif /* NVIC_NVIC_H_ */
