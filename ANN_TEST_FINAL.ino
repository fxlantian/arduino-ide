#include "/home/archer/ppulib/testANN.h"
#include "malloc.h"

#include "OLED.h"
#include "CAM.h"
#include "ANN.h"

int* Dst_Addr;
unsigned char image_sampled[28*28];
unsigned char image_normal[28*28];

void setup(){
  OLED.Init();
  OLED.Clear(BLACK);
  OLED.Draw_Rectangle(49, 49, 106, 106); 
  Dst_Addr = (int*)malloc(sizeof(int) * NPU_DATAOUT_DEPTH0);
  Isr_Type = 0;
  CAM.Init();  
  ANN.Init(IM_DEPTH0, WEIGTH_DEPTH0, BIAS_DEPTH0, (int)&Ann_Config, DMA_BLOCK_INFO0);
  CAM.Open();
}

void loop(){ 
    if(Isr_Type != 0)
      {
        if(Isr_Type == 1)
            ANN.Image_Sample((volatile unsigned char*)FRAME1_ADDR,image_sampled);
        else if(Isr_Type == 2)
            ANN.Image_Sample((volatile unsigned char*)FRAME2_ADDR,image_sampled);
        else if(Isr_Type == 3)
            ANN.Image_Sample((volatile unsigned char*)FRAME3_ADDR,image_sampled);

        if(Isr_Type == 1 || Isr_Type == 2 || Isr_Type == 3){
          ANN.Image_Normalization(image_sampled);
          ANN.Image_Qfix(image_sampled, (unsigned char*)&data_input);
          ANN.Proc(NPU_DATAIN_DEPTH0, NPU_DATAOUT_DEPTH0, (int)&data_input,  (int)Dst_Addr, NPU_DMA_BLOCK_INFO0 ); 
          ANN.Check_Result((char*)Dst_Addr);
        }
        Isr_Type = 0;
        CAM.Open();
    }
}

