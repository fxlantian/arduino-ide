#include "CAM.h"

#include <stdio.h>
CAMCLASS CAM;
volatile int Isr_Type = 0;

CAMCLASS::CAMCLASS(){

}

void CAMCLASS::Init(void){
	SCCB1_init();
    SCCB1_WriteByte(0x12, 0x80);
    SCCB1_WriteByte(0x11, 0x01); //2/ pre-scale
    SCCB1_WriteByte(0x0d, 0x00); //PLL 0xs
    SCCB1_WriteByte(0x12, 0x40); //QVGA,YUV
    camctl_init();
}

void CAMCLASS::Open(void){
	camctl_start();
}

void CAMCLASS::Stop(void){
	camctl_stop();
}
