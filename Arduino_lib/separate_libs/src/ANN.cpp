#include "ANN.h"
#include <stdio.h>

ANNCLASS ANN;
volatile int count = 0;

ANNCLASS::ANNCLASS(){
}

void ANNCLASS::Image_Sample(volatile unsigned char* image_addr, unsigned char* image_sampled)
{
    u16 i,j;
    u16 k=0;      
    //image_addr->320*240 yuv 4:2:2
    volatile unsigned char* image_addr_ver = image_addr + 2 * 640;
    for(i=0;i<28;i++)
    {
      image_addr_ver = image_addr + i * 640 * 8 + 2 * 10; //pick a pixel every 8 line
      for(j=0;j<28;j++)
      {
        image_sampled[i*28 + j] = *image_addr_ver;
        image_addr_ver += 16;
      }
    }
}

void ANNCLASS::Image_Normalization(volatile unsigned char* image_sampled)
{
    volatile int i,j,ver;
    unsigned char max=0;
    unsigned char min=255; 
    float temp[28*28];
    ver=0;
    
    for(i=0;i<28;i++)
    {
      for(j=0;j<28;j++)
      {
        if(max<image_sampled[ver])
          max = image_sampled[ver];
        if(min>image_sampled[ver])
          min = image_sampled[ver];
        ver++;
      }
    }
    ver=0;
    unsigned int max_dif = max - min;
    for(i=0;i<28;i++)
    {
      for(j=0;j<28;j++)
      {
        //image_sampled[ver] = ((max - image_sampled[ver]) * 255) / max_dif;
        if(image_sampled[ver]>90)
            image_sampled[ver] = 0;
        else
            image_sampled[ver] = 255;
        ver++;
      }
    }
    Address_set(50, 50, 106 - 1, 106 - 1);
    OLED_DC_Set();
    unsigned char* image_addr_ver = (unsigned char*)image_sampled;
    unsigned char* image_addr_ver1 = (unsigned char*)image_sampled;
    for(i=0;i<28;i++)
    {
      for(j=0;j<28;j++)
      {
        LCD_WR_DATA8(*(image_addr_ver));
        LCD_WR_DATA8(*(image_addr_ver));
        LCD_WR_DATA8(*(image_addr_ver));

        LCD_WR_DATA8(*(image_addr_ver));
        LCD_WR_DATA8(*(image_addr_ver));
        LCD_WR_DATA8(*(image_addr_ver));
        image_addr_ver++;
      }

      for(j=0;j<28;j++)
      {
        LCD_WR_DATA8(*(image_addr_ver1));
        LCD_WR_DATA8(*(image_addr_ver1));
        LCD_WR_DATA8(*(image_addr_ver1));

        LCD_WR_DATA8(*(image_addr_ver1));
        LCD_WR_DATA8(*(image_addr_ver1));
        LCD_WR_DATA8(*(image_addr_ver1));
        image_addr_ver1++;
      }
    }
}

void ANNCLASS::Image_Qfix(volatile unsigned char* image_addr, unsigned char* dst_image)
{
 
    int i,j;
    int ver = 0;  
     for(i=0;i<28;i++)
    {
      for(j=0;j<28;j++)
      {
          dst_image[ver] = image_addr[ver] >> 1;
          ver++;
      }
    }
    
}

void ANNCLASS::Check_Result(char* Dst_Addr)
{
    int test_i;
    signed char res=0;
    signed char big_last=0;
    signed char big_num=0;
    
    for(test_i=0;test_i<10;test_i++)
    {
      res = *(Dst_Addr + test_i);
      printf("%02x ",res);

      if(res > big_last){
        big_num = test_i;
        big_last = res;
      }
    }

    printf("big_num:%x\n",big_num);
    if(big_num==0)
      printf_lcd_sl("NUMBER: 0");
    else if(big_num==1)
      printf_lcd_sl("NUMBER: 1");
    else if(big_num==2)
      printf_lcd_sl("NUMBER: 2");
    else if(big_num==3)
      printf_lcd_sl("NUMBER: 3");
    else if(big_num==4)
      printf_lcd_sl("NUMBER: 4");
    else if(big_num==5)
      printf_lcd_sl("NUMBER: 5");
    else if(big_num==6)
      printf_lcd_sl("NUMBER: 6");
    else if(big_num==7)
      printf_lcd_sl("NUMBER: 7");
    else if(big_num==8)
      printf_lcd_sl("NUMBER: 8");
    else if(big_num==9)
      printf_lcd_sl("NUMBER: 9");
}

void ANNCLASS::Init(int im_depth, 
              int weight_depth, 
              int bias_depth, 
              int DMA_src_addr, 
              int block_size)
{
  int_enable();
  IER |= (1<<16);
  init_pro(im_depth, weight_depth, bias_depth, DMA_src_addr, block_size);
  while(!count);
  count = 0;
}

void ANNCLASS::Proc(int npu_datain_depth, 
             int npu_detaout_depth, 
             int DMA_src_addr, 
             int DMA_dst_addr,          
             int block_size )
{
  npu_pro(npu_datain_depth, npu_detaout_depth, DMA_src_addr, DMA_dst_addr, block_size);
  while(count!=2);
  count=0;
}

