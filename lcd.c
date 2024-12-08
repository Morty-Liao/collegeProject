#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

int lcd_fd;
int *plcd;

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