
#ifndef __OLED_H
#define __OLED_H			  	 	   
#define LCD_W 480
#define LCD_H 320
#define	u8 unsigned char
#define	u16 unsigned int
#define	u32 unsigned long

#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
					   
#define OLED_CS_Clr()  set_gpio_pin_value(5, 0)//CS
#define OLED_CS_Set()  set_gpio_pin_value(5, 1)

#define OLED_RST_Clr() set_gpio_pin_value(3, 0)//RES
#define OLED_RST_Set() set_gpio_pin_value(3, 1)

#define OLED_DC_Clr() set_gpio_pin_value(2, 0)//DC
#define OLED_DC_Set() set_gpio_pin_value(2, 1)

#define OLED_SCLK_Clr() set_gpio_pin_value(0, 0)//CLK
#define OLED_SCLK_Set() set_gpio_pin_value(0, 1)

#define OLED_SDIN_Clr() set_gpio_pin_value(1, 0)//DIN
#define OLED_SDIN_Set() set_gpio_pin_value(1, 1)
 		     
#define OLED_CMD  0	
#define OLED_DATA 1


    void LCD_Init(void); 
	void LCD_Clear(u32 color);
	void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
	void LCD_WR_DATA8(char da);
	void LCD_WR_DATA(u32 da);
	void LCD_WR_REG(char da);
	void LCD_DrawPoint(u16 x,u16 y);
	void LCD_DrawPoint_big(u16 x,u16 y);
	void Draw_Circle(u16 x0,u16 y0,u8 r);
	void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
	void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
	void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
	void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode);
	void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);
	void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len);
	void LCD_ShowString(u16 x,u16 y,const u8 *p);
	void LCD_Showhanzi(unsigned int x,unsigned int y,unsigned char index);
	void delay_ms(int delay);
	void display_cam(volatile unsigned char* image_addr);
	void display_image(u16 x1, u16 y1, u16 x2, u16 y2, volatile unsigned char* image_addr);
	void display_image_sl(u16 x1, u16 y1, u16 x2, u16 y2, volatile unsigned char* image_addr);
	void display_shade(u16 x1);
	void printf_lcd(const char* image_addr);
	void printf_lcd_sl(const char* image_addr);

	extern u16 BACK_COLOR, POINT_COLOR, dis_line;



#define WHITE         	 0xFCFCFC
#define BLACK         	 0x000000	  
#define BLUE         	 0xFC0000  
#define RED           	 0x0000FC
#define GREEN         	 0x00FC00
#define BRED             0XF81F
#define GRED 	         0XFFE0
#define GBLUE	         0X07FF
#define MAGENTA       	 0xF81F
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 
#define BRRED 			 0XFC07 
#define GRAY  			 0X8430 

#define DARKBLUE      	 0X01CF	
#define LIGHTBLUE      	 0X7D7C	 
#define GRAYBLUE       	 0X5458 
 
#define LIGHTGREEN     	 0X841F
#define LGRAY 			 0XC618

#define LGRAYBLUE        0XA651
#define LBBLUE           0X2B12

#endif  
	 
	 



