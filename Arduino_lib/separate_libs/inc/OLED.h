#ifndef _OLED_H_INCLUDED
#define _OLED_H_INCLUDED

extern "C"{
	#include "oled.h"
	#include "bmp.h"
}

class OLEDCLASS
{
public:
	OLEDCLASS();
	void Init(void);
	void Clear(u16 color);
	void Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
	void Draw_Point(u16 x,u16 y);
	void Draw_BigPoint(u16 x,u16 y);
	void Draw_Circle(u16 x0,u16 y0,u8 r);
	void Draw_Line(u16 x1, u16 y1, u16 x2, u16 y2);
	void Draw_Rectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
	void Show_Char(u16 x,u16 y,u8 num,u8 mode);
	void Show_Num(u16 x,u16 y,u32 num,u8 len);
	void Show_2Num(u16 x,u16 y,u16 num,u8 len);
	void Show_String(u16 x,u16 y,const u8 *p);
	void Show_Hanzi(unsigned int x,unsigned int y,unsigned char index);
	void Display_Shade(u16 x1);
	void Display_Image(u16 x1, u16 y1, u16 x2, u16 y2, volatile unsigned char* image_addr, u8 mode);
	void Print(u16 x1, u16 add,const char* image_addr);
	void SetBackColor(u16 color);
	void SetPointColor(u16 color);
	u16  GetBackColor(void);
	u16  GetPointColor(void);
};

void ISR_CAM(void);

extern OLEDCLASS OLED;

#endif  






