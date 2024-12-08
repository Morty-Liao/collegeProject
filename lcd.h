#ifndef __LCD_H__
#define __LCD_H__

//函数的声明
int lcd_init();

void lcd_uninit();

//设计一个函数将(x,y)像素点设置为color颜色
void draw_point(int x,int y,int color);

//在(x0,y0)处将一个w*h大小的字符（传入该字符的字模信息）显示为color颜色
void draw_word(int x0,int y0,char *dat,int w,int h,int color);

//在(x0,y0)处画一个w*h大小的color颜色的矩形
void draw_jx(int x0,int y0,int w,int h,int color);

//在(x0,y0)处画一个w*h大小的color颜色的矩形
void draw_yuan(int x0,int y0,int r,int color);

//读取一张bmp图片的属性
void read_bmp(char * bmpname);

/*showbmp： 在坐标(x0,y0)处显示bmpname指向的bmp图片*/
void showbmp(int x0,int y0,char *bmpname);

void showbmp_v2(int num,char*name);

#endif