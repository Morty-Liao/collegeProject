#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

int lcd_fd;
int *plcd;

char liu[64*64/8] = {
/*--  文字:  刘  --*/
/*--  Verdana48;  此字体下对应的点阵为：宽x高=64x64   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x07,0x00,
0x00,0x01,0xE0,0x00,0x00,0x00,0x07,0xC0,0x00,0x01,0xF0,0x00,0x00,0x00,0x07,0xF0,
0x00,0x00,0xF8,0x00,0x00,0x00,0x07,0xF0,0x00,0x00,0x7C,0x00,0x00,0x00,0x07,0xE0,
0x00,0x00,0x7E,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x3F,0x00,0x00,0x00,0x07,0xC0,
0x00,0x00,0x3F,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x3F,0x00,0x00,0x00,0x07,0xC0,
0x00,0x00,0x1F,0x00,0x00,0x60,0x07,0xC0,0x00,0x00,0x1E,0x01,0xC0,0x7C,0x07,0xC0,
0x00,0x00,0x1C,0x03,0xE0,0x7F,0x07,0xC0,0x00,0x00,0x00,0x07,0xF0,0x7F,0x07,0xC0,
0x1F,0xFF,0xFF,0xFF,0xF8,0x7E,0x07,0xC0,0x0F,0xFF,0xFF,0xFF,0xFC,0x7C,0x07,0xC0,
0x07,0x80,0x00,0x38,0x00,0x7C,0x07,0xC0,0x00,0x00,0x00,0x3C,0x00,0x7C,0x07,0xC0,
0x00,0x00,0x00,0x3F,0x00,0x7C,0x07,0xC0,0x00,0x00,0x00,0x7F,0x80,0x7C,0x07,0xC0,
0x00,0x00,0x00,0x7F,0x00,0x7C,0x07,0xC0,0x00,0x00,0x00,0x7E,0x00,0x7C,0x07,0xC0,
0x00,0x00,0x00,0x7C,0x00,0x7C,0x07,0xC0,0x00,0x00,0x00,0xFC,0x00,0x7C,0x07,0xC0,
0x01,0xC0,0x00,0xF8,0x00,0x7C,0x07,0xC0,0x00,0xF0,0x00,0xF8,0x00,0x7C,0x07,0xC0,
0x00,0x78,0x01,0xF8,0x00,0x7C,0x07,0xC0,0x00,0x1E,0x01,0xF0,0x00,0x7C,0x07,0xC0,
0x00,0x0F,0x03,0xF0,0x00,0x7C,0x07,0xC0,0x00,0x07,0xC3,0xE0,0x00,0x7C,0x07,0xC0,
0x00,0x03,0xE7,0xE0,0x00,0x7C,0x07,0xC0,0x00,0x01,0xF7,0xC0,0x00,0x7C,0x07,0xC0,
0x00,0x00,0xFF,0xC0,0x00,0x7C,0x07,0xC0,0x00,0x00,0x7F,0x80,0x00,0x7C,0x07,0xC0,
0x00,0x00,0x3F,0x80,0x00,0x7C,0x07,0xC0,0x00,0x00,0x1F,0x80,0x00,0x7C,0x07,0xC0,
0x00,0x00,0x3F,0xE0,0x00,0x7C,0x07,0xC0,0x00,0x00,0x3F,0xF0,0x00,0x7C,0x07,0xC0,
0x00,0x00,0x7F,0xF8,0x00,0x7C,0x07,0xC0,0x00,0x00,0xFD,0xFC,0x00,0x7C,0x07,0xC0,
0x00,0x00,0xF8,0xFE,0x00,0x7C,0x07,0xC0,0x00,0x01,0xF0,0x7F,0x00,0x7C,0x07,0xC0,
0x00,0x03,0xE0,0x3F,0x80,0x7C,0x07,0xC0,0x00,0x03,0xC0,0x1F,0x80,0x7C,0x07,0xC0,
0x00,0x07,0xC0,0x1F,0xC0,0x7C,0x07,0xC0,0x00,0x0F,0x80,0x0F,0xC0,0x78,0x07,0xC0,
0x00,0x1F,0x00,0x0F,0xC0,0x00,0x07,0xC0,0x00,0x3E,0x00,0x07,0xC0,0x00,0x07,0xC0,
0x00,0x7C,0x00,0x03,0xC0,0x00,0x07,0xC0,0x00,0xF8,0x00,0x03,0xC0,0x00,0x07,0xC0,
0x01,0xE0,0x00,0x01,0x80,0x00,0x07,0xC0,0x03,0xC0,0x00,0x00,0x00,0x00,0x07,0xC0,
0x07,0x80,0x00,0x00,0x00,0x1F,0xFF,0xC0,0x1F,0x00,0x00,0x00,0x00,0x0F,0xFF,0xC0,
0x3C,0x00,0x00,0x00,0x00,0x01,0xFF,0xC0,0x38,0x00,0x00,0x00,0x00,0x00,0x7F,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

char de[64*64/8] = 
{
/*--  文字:  德  --*/
/*--  Verdana48;  此字体下对应的点阵为：宽x高=64x64   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,
0x00,0x03,0x80,0x00,0x07,0xE0,0x00,0x00,0x00,0x03,0xE0,0x00,0x07,0xF0,0x00,0x00,
0x00,0x03,0xF0,0x00,0x07,0xE0,0x00,0x00,0x00,0x07,0xF0,0x00,0x07,0xE0,0x00,0x00,
0x00,0x07,0xE0,0x00,0x07,0xC0,0x00,0x00,0x00,0x0F,0xC0,0x00,0x07,0xC0,0x03,0x00,
0x00,0x0F,0x80,0x00,0x0F,0x80,0x07,0x80,0x00,0x1F,0x00,0x00,0x0F,0x80,0x0F,0xC0,
0x00,0x3E,0x0F,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x3E,0x07,0xFF,0xFF,0xFF,0xFF,0xF0,
0x00,0x7C,0x03,0x00,0x0F,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x1F,0x00,0x00,0x00,
0x00,0xF0,0x60,0x00,0x1E,0x00,0x00,0x00,0x01,0xE0,0xF8,0x00,0x1E,0x00,0x0C,0x00,
0x03,0xC0,0xFC,0xF0,0x1E,0x00,0x1E,0x00,0x03,0x81,0xFE,0xFF,0xFF,0xFF,0xFF,0x00,
0x07,0x01,0xFC,0xFF,0xFF,0xFF,0xFF,0x80,0x0E,0x01,0xF8,0xF8,0x7C,0x3C,0x3F,0x00,
0x00,0x03,0xF0,0xF8,0x7C,0x3C,0x3E,0x00,0x00,0x03,0xE0,0xF8,0x7C,0x3C,0x3E,0x00,
0x00,0x07,0xE0,0xF8,0x7C,0x3C,0x3E,0x00,0x00,0x07,0xC0,0xF8,0x7C,0x3C,0x3E,0x00,
0x00,0x0F,0x80,0xF8,0x7C,0x3C,0x3E,0x00,0x00,0x0F,0x80,0xF8,0x7C,0x3C,0x3E,0x00,
0x00,0x1F,0x80,0xF8,0x7C,0x3C,0x3E,0x00,0x00,0x3F,0x80,0xF8,0x7C,0x3C,0x3E,0x00,
0x00,0x3F,0x80,0xF8,0x7C,0x3C,0x3E,0x00,0x00,0x7F,0x80,0xFF,0xFF,0xFF,0xFE,0x00,
0x00,0xFF,0x80,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0xFF,0x80,0xF8,0x00,0x00,0x3E,0x00,
0x01,0xEF,0x80,0xF8,0x00,0x00,0x38,0x00,0x03,0xCF,0x80,0xE0,0x00,0x00,0x01,0x80,
0x07,0x8F,0x80,0x00,0x00,0x00,0x03,0xC0,0x07,0x0F,0x80,0x00,0x00,0x00,0x07,0xE0,
0x0E,0x0F,0xBF,0xFF,0xFF,0xFF,0xFF,0xF0,0x1C,0x0F,0xBF,0xFF,0xFF,0xFF,0xFF,0xF8,
0x38,0x0F,0x9F,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x80,0x00,0x0C,0x00,0x00,0x00,
0x00,0x0F,0x80,0x00,0x0F,0x00,0x00,0x00,0x00,0x0F,0x80,0x0E,0x07,0x80,0x00,0x00,
0x00,0x0F,0x80,0x0F,0x87,0xE0,0x18,0x00,0x00,0x0F,0x81,0x8F,0xE3,0xF0,0x1E,0x00,
0x00,0x0F,0x83,0x8F,0xC1,0xF0,0x1F,0x00,0x00,0x0F,0x83,0x8F,0x81,0xF8,0x0F,0x80,
0x00,0x0F,0x83,0x8F,0x81,0xF8,0x87,0xE0,0x00,0x0F,0x83,0x8F,0x80,0xF9,0xC7,0xE0,
0x00,0x0F,0x87,0x8F,0x80,0xF1,0xC3,0xF0,0x00,0x0F,0x8F,0x8F,0x80,0x41,0xC1,0xF0,
0x00,0x0F,0x8F,0x8F,0x80,0x01,0xC1,0xF0,0x00,0x0F,0x9F,0x8F,0x80,0x01,0xE1,0xE0,
0x00,0x0F,0xBF,0x8F,0x80,0x01,0xE0,0xE0,0x00,0x0F,0xBF,0x07,0x80,0x01,0xF0,0x00,
0x00,0x0F,0xBE,0x07,0xC0,0x03,0xF8,0x00,0x00,0x0F,0x9C,0x07,0xFF,0xFF,0xF8,0x00,
0x00,0x0F,0x80,0x03,0xFF,0xFF,0xF0,0x00,0x00,0x0F,0x00,0x01,0xFF,0xFF,0xE0,0x00,
0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00  
};

char hua[64*64/8] = 
{
/*--  文字:  华  --*/
/*--  Verdana48;  此字体下对应的点阵为：宽x高=64x64   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0xE0,0x00,0x00,0x00,
0x00,0x00,0x3C,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0xFE,0x00,0x00,0x00,
0x00,0x00,0x7F,0x80,0xFC,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0xF8,0x00,0x08,0x00,
0x00,0x00,0xFC,0x00,0xF8,0x00,0x1C,0x00,0x00,0x00,0xF8,0x00,0xF8,0x00,0x3E,0x00,
0x00,0x01,0xF0,0x00,0xF8,0x00,0x7F,0x00,0x00,0x03,0xF0,0x00,0xF8,0x00,0xFF,0x80,
0x00,0x03,0xE0,0x00,0xF8,0x01,0xFF,0x80,0x00,0x07,0xC0,0x00,0xF8,0x07,0xF8,0x00,
0x00,0x07,0xC0,0x00,0xF8,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0xF8,0x1F,0xC0,0x00,
0x00,0x1F,0xF0,0x00,0xF8,0x7F,0x00,0x00,0x00,0x1F,0xE0,0x00,0xF8,0xFE,0x00,0x00,
0x00,0x3F,0xE0,0x00,0xFB,0xF8,0x00,0x00,0x00,0x7F,0xE0,0x00,0xFF,0xF0,0x00,0x00,
0x00,0xFB,0xE0,0x00,0xFF,0xC0,0x00,0xE0,0x00,0xF3,0xE0,0x00,0xFF,0x00,0x00,0xE0,
0x01,0xE3,0xE0,0x01,0xFC,0x00,0x00,0xE0,0x03,0x83,0xE0,0x07,0xF8,0x00,0x00,0xE0,
0x07,0x03,0xE0,0x1F,0xF8,0x00,0x01,0xE0,0x0E,0x03,0xE0,0xFE,0xF8,0x00,0x01,0xE0,
0x0C,0x03,0xE3,0xF0,0xF8,0x00,0x01,0xE0,0x00,0x03,0xEF,0xC0,0xF8,0x00,0x01,0xE0,
0x00,0x03,0xEC,0x00,0xF8,0x00,0x01,0xE0,0x00,0x03,0xE0,0x00,0xF8,0x00,0x01,0xF0,
0x00,0x03,0xE0,0x00,0xFC,0x00,0x03,0xF8,0x00,0x03,0xE0,0x00,0xFF,0xFF,0xFF,0xF8,
0x00,0x03,0xE0,0x00,0x7F,0xFF,0xFF,0xF0,0x00,0x03,0xE0,0x07,0x3F,0xFF,0xFF,0xE0,
0x00,0x03,0xE0,0x07,0xC0,0x00,0x00,0x00,0x00,0x03,0xE0,0x07,0xF0,0x00,0x00,0x00,
0x00,0x03,0xC0,0x07,0xE0,0x00,0x00,0x00,0x00,0x03,0x00,0x07,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,0x00,0x03,0xC0,
0x00,0x00,0x00,0x07,0xC0,0x00,0x07,0xE0,0x00,0x00,0x00,0x07,0xC0,0x00,0x0F,0xF0,
0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,
0x0F,0x80,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

int lcd_init()
{
    //1.打开屏幕文件
    lcd_fd = open("/dev/fb0",O_RDWR);
    if(lcd_fd == -1)
    {   //打开失败
        perror("open error");
        return -1;
    }
    //2.映射mmap
    plcd = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE,MAP_SHARED,lcd_fd,0);
    if(plcd == MAP_FAILED)
    {
        perror("mmap error");
        return -1;
    }
}

void lcd_uninit()
{
    //1.解除映射
    munmap(plcd,800*480*4);

    //2.关闭文件
    close(lcd_fd);
}

//设计一个函数将(x,y)像素点设置为color颜色
void draw_point(int x,int y,int color)
{
    //画点的范围800*480范围内
    if( x>=0 && x<=799 && y>=0 && y<=479)
    {
        *(plcd + y*800 + x) = color;
    }
}

//在(x0,y0)处将一个w*h大小的字符（传入该字符的字模信息）显示为color颜色
void draw_word(int x0,int y0,char *dat,int w,int h,int color)
{
    for(int i=0;i<w*h/8;i++) //一共有 w*h/8 个16进制
    {
        for(int k=0;k<8;k++) //一个16进制表示8位位代码
        {
            //判断dat[i]这个16进制数的每一个bit位
            if( dat[i]<<k & 0x80) 
            {	//该bit位为1就显示
                int x = x0+(i*8+k)%w;
                int y = y0+i/(w/8);
                draw_point( x,y,color );
            }
        }
    }
}

//在(x0,y0)处画一个w*h大小的color颜色的矩形
void draw_jx(int x0,int y0,int w,int h,int color)
{
    //1.列举出所有的点
    for(int i=0;i<800;i++)
    {
        for(int j=0;j<480;j++)
        {
            //2.判断该点(i,j)是否在矩形内部
            if( i>=x0 && i<x0+w && j>=y0 && j<=y0+h )
            {
                //3.画出改点
                draw_point( i,j,color);
            }
        }
    }
}

//在(x0,y0)处画一个w*h大小的color颜色的矩形
void draw_yuan(int x0,int y0,int r,int color)
{
    //1.列举出所有的点
    for(int i=0;i<800;i++)
    {
        for(int j=0;j<480;j++)
        {
            //2.判断该点(i,j)是否在圆内部
            if( (x0-i)*(x0-i)+(y0-j)*(y0-j) <= r*r )
            {
                //3.画出该点
                draw_point( i,j,color);
            }
        }
    }
}

//读取一张bmp图片的属性
void read_bmp(char * bmpname)
{
    //1.open
    int fd = open(bmpname,O_RDONLY);
    if(fd == -1)
    {
        perror("open error");
        return ;
    }

    int w,h;
    short d;
    lseek(fd,0x12,SEEK_SET);//偏移文件的读写光标,将文件读写光标偏移到位图宽度的位置
    read(fd,&w,4);

    lseek(fd,0x16,SEEK_SET);//偏移文件的读写光标,将文件读写光标偏移到位图高度的位置
    read(fd,&h,4);

    lseek(fd,0x1C,SEEK_SET);//偏移文件的读写光标,将文件读写光标偏移到位图色深的位置
    read(fd,&d,2);

    printf("bmp:w=%d h=%d d=%d\n",w,h,d);
}

/*showbmp： 在坐标(x0,y0)处显示bmpname指向的bmp图片*/
void showbmp(int x0,int y0,char *bmpname)
{
    //1.打开
    int fd = open( bmpname , O_RDWR );
    if(fd == 0)
    {
        perror("open error\n");
        return ;
    }
    //读取文件内容
    int hight ,width;
    short depth;
    //偏移后读取数据
    lseek(fd,0x12,SEEK_SET);
    read(fd,&width,4);

    lseek(fd,0x16,SEEK_SET);
    read(fd,&hight,4);

    lseek(fd, 0x1c, SEEK_SET);
    read(fd,&depth,2);
    //printf("%s:width=%d  height=%d  depth=%d\n",bmpname,width ,hight,depth);

    //计算并读出像素数组的大小
    //一行的字节数
    int line_bytes = width*(depth/8);
    //计算出癞子个数
    int laizi = 0;
	if( line_bytes%4  !=  0)
	{
	    laizi = 4 - (line_bytes%4);
    }

    //一行真正字节数
    int real_line_bytes = laizi +  line_bytes;
    //像素组的大小
    int total_bytes = real_line_bytes * hight;
    //读取像素数组
    unsigned char pixel[total_bytes];
    lseek(fd, 54, SEEK_SET);
    read(fd,pixel,total_bytes);

    //将数组里的数据写到屏幕文件里面去
    unsigned int a,r,g,b;
    int color;
	int m=0,n=0;
	int i = 0;
    //显示
    for(m = 0; m<hight; m++)
    {
        for(n = 0; n<width; n++)
        {
            b = pixel[i++];
            g = pixel[i++];
            r = pixel[i++];
            if(depth == 24)
            {
                a == 0;
            }
            else if(depth == 32)
            {
                a = pixel[i++];
            }
            color = a<<24 | r<<16 | g<<8 | b ;//按小端模式算出颜色

            draw_point( x0+n ,y0+hight -m-1 ,color);
        }

        i = i + laizi;
    }

    close(fd);
}

/*
    showbmp_v2:根据显示特效显示图片
    num:选择特效
        1.从左往右显示
        2.从右往左
        3.从上往下
        4.从下往上
        .....
    name:图片名字
*/
void showbmp_v2(int num,char*name)
{
    switch(num)
    {
        case 1:
            for(int i=-800;i<=0;i+=10)
            {
                showbmp(i,0,name);
            }
            break;
        case 2:
            for(int i=800;i>=0;i-=10)
            {
                showbmp(i,0,name);
            }
            break;
        case 3:
            for(int i=-480;i<=0;i+=10)
            {
                showbmp(0,i,name);
            }
            break;
        case 4:
            for(int i=480;i>=0;i-=10)
            {
                showbmp(0,i,name);
            }
            break;
    }
}





