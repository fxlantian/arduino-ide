#ifndef _CAM_H
#define _CAM_H

#include <Arduino.h>

#include "int.h"
extern "C"{
	#include "camctl.h"
	#include "event.h"
	#include "sccb_bsp.h"
}

class CAMCLASS{
public:
	CAMCLASS();
	void Init(void);
	void Open(void);
	void Stop(void);

private:

};

extern volatile int Isr_Type;

void ISR_CAM(void)
{
  int val;
  camctl_stop();  //close the camera
  ICP = (1 << INT_CAM);
  val = *(volatile int*) (CAMCTL_STATUS);

  if(DATAOK_FRAME1(val) == 1) {
    Isr_Type = 1;
    val = CLR_FRAME1_INT(val);
  }

  if(DATAOK_FRAME2(val) == 1) {
    Isr_Type = 2;
    val = CLR_FRAME2_INT(val);
  }

  if(DATAOK_FRAME3(val) == 1) {
    Isr_Type = 3;
    val = CLR_FRAME3_INT(val);
  }

  if(RQ_FUL(val) == 1) {
    Isr_Type = 4;
    val = CLR_RQFUL_INT(val);
  }

  if(RQ_OVF(val) == 1) {
    Isr_Type = 5;
    val = CLR_RQOVF_INT(val);
  }

  if(PROTOCAL_ERR0(val) == 1) {
    Isr_Type = 6;
    val = CLR_PROERR0_INT(val);
  }

  if(PROTOCAL_ERR1(val) == 1) {
    Isr_Type = 7;
    val = CLR_PROERR1_INT(val);
  }
  *(volatile int*) (CAMCTL_STATUS) = val;
}

extern CAMCLASS CAM;

#endif