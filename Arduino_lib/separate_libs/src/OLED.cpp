#include "OLED.h"

OLEDCLASS OLED;

OLEDCLASS::OLEDCLASS(){

}

void OLEDCLASS::Init(void){
	LCD_Init();
	SetBackColor(BLACK);
	SetPointColor(WHITE);
}
void OLEDCLASS::Clear(u16 color){
	LCD_Clear(color);
}
void OLEDCLASS::Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color){
	LCD_Fill(xsta,ysta,xend,yend,color);
}
void OLEDCLASS::Draw_Point(u16 x,u16 y){
	LCD_DrawPoint(x,y);
}

void OLEDCLASS::Draw_BigPoint(u16 x,u16 y){
	LCD_DrawPoint_big(x,y);
}

void OLEDCLASS::Draw_Circle(u16 x0,u16 y0,u8 r){
	Draw_Circle(x0,y0,r);
}

void OLEDCLASS::Draw_Line(u16 x1, u16 y1, u16 x2, u16 y2){
	LCD_DrawLine(x1,y1,x2,y2);
}
void OLEDCLASS::Draw_Rectangle(u16 x1, u16 y1, u16 x2, u16 y2){
	LCD_DrawRectangle(x1,y1,x2,y2);
}	   
void OLEDCLASS::Show_Char(u16 x,u16 y,u8 num,u8 mode){
	LCD_ShowChar(x,y,num,mode);
}

void OLEDCLASS::Show_Num(u16 x,u16 y,u32 num,u8 len){
	LCD_ShowNum(x,y,num,len);
}
void OLEDCLASS::Show_2Num(u16 x,u16 y,u16 num,u8 len){
	LCD_Show2Num(x,y,num,len);
}

void OLEDCLASS::Show_String(u16 x,u16 y,const u8 *p){
	LCD_ShowString(x,y,p);
}

void OLEDCLASS::Show_Hanzi(unsigned int x,unsigned int y,unsigned char index){
	LCD_Showhanzi(x,y,index);
}
void OLEDCLASS::Display_Shade(u16 x1){
	display_shade(x1);
}

void OLEDCLASS::Display_Image(u16 x1, u16 y1, u16 x2, u16 y2, volatile unsigned char* image_addr, u8 mode){
	if(mode == 0){
		display_image(x1,y1,x2,y2,image_addr);
	}else if(mode == 1){
		display_image_sl(x1,y1,x2,y2,image_addr);
	}
}

void OLEDCLASS::Print(u16 x1, u16 add, const char* image_addr){
	if(dis_line > 300)
	{	
		LCD_Fill(x1,0,479,319,WHITE);
		dis_line = 15;
	}
	LCD_ShowString(x1,dis_line,(const unsigned char*)image_addr);
	dis_line += add;
}



void OLEDCLASS::SetBackColor(u16 color){
	BACK_COLOR = color;
}

void OLEDCLASS::SetPointColor(u16 color){
	POINT_COLOR = color;
}

u16 OLEDCLASS::GetBackColor(){
	return BACK_COLOR;
}

u16 OLEDCLASS::GetPointColor(){
	return POINT_COLOR;
}
