/*
 * SYSCTL.h
 *

 */

#ifndef SYSCTL_SYSCTL_H_
#define SYSCTL_SYSCTL_H_

typedef union {     //0x400FE000
    struct
    {
        //uint32_t DIDO[384];//0x400FE000
        uint32_t CWD_R; //0x400FE600
        uint32_t TIMER_R; //0x400FE604
        uint32_t GPIO_R; //0x400FE608
        uint32_t DMA_R;
    }RCGC;
}REG_1;


#endif /* SYSCTL_SYSCTL_H_ */
