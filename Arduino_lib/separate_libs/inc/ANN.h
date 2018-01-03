#ifndef _ANN_H_INCLUDED
#define _ANN_H_INCLUDED

#include "int.h"
extern "C"{
	#include "ann.h"
	#include "gpio.h"
	#include "event.h"
	#include "oled.h"
}

class ANNCLASS{
public:
	ANNCLASS();
	void Image_Sample(volatile unsigned char* image_addr, unsigned char* image_sampled);
	void Image_Normalization(volatile unsigned char* image_sampled);
	void Image_Qfix(volatile unsigned char* image_addr, unsigned char* dst_image);
	void Check_Result(char* Dst_Addr);
	void Init(int im_depth, int weight_depth, int bias_depth, int DMA_src_addr,  int block_size);
 	void Proc(int npu_datain_depth, int npu_detain_depth, int DMA_src_addr, int DMA_dst_addr,  int block_size );
};

extern volatile int count;

void ISR_ANN_INT (void){   
  int a=0;
  int npu_on=0;
  a = *(volatile int*)(ANN_REG_STATUS_END);
  clear_int();
  ICP |= (1<<16); 
  if(a==1){    //init_ram is complete
      IER |= (1<< INT_CAM); //enable camera interrupt
      EER |= (1<< INT_CAM); //enable camera interrupt
      count++;  
    }
    else if(a==2){ //computing is complete
      count=2; 
    }
}
extern ANNCLASS ANN;

#endif