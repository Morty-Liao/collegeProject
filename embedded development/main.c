#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "lcd.h"
#include "touch.h"//屏幕滑动的头文件

char bname[][64] = {"11.bmp","12.bmp","13.bmp","14.bmp"};
char bname2[][64] = {"21.bmp","22.bmp","23.bmp","24.bmp"};
char bname3[][64] = {"31.bmp","32.bmp","33.bmp","34.bmp"};
char bname4[][64] = {"5.bmp","42.bmp","43.bmp","44.bmp"};
char bname5[][64] = {"52.bmp","51.bmp","53.bmp","54.bmp"};

void show_pic1()
{
    int i=0;
    showbmp_v2(i%4+1,bname[i]);
    while(1)
    {
        printf("while2\n");
        int dir = get_touch_way();
        if(dir==1){
            printf("--------up---------\n");
            return;
        }
        switch (dir)
        {

            case 2:
                printf("--------down---------\n");
                i--;
                if(i==-1){
                    i=3;
                }
                showbmp_v2(i%4+1,bname[i]);
                break;
            case 3:
                printf("--------left---------\n");
                i++;
                if(i==4){
                    i=0;
                }
                showbmp_v2(i%4+1,bname[i]);
                break;
            case 4:
                printf("--------right---------\n");
                i--;
                if(i==-1){
                    i=3;
                }
                showbmp_v2(i%4+1,bname[i]);
                break;
            default:
                printf("--------error---------\n");
                break;
        }
    }
}

void show_pic2()
{
    int i=0;
    showbmp_v2(i%4+1,bname2[i]);
    while(1)
    {
        printf("while2\n");
        int dir = get_touch_way();
        if(dir==1){
            printf("--------up---------\n");
            return;
        }
        switch (dir)
        {

            case 2:
                printf("--------down---------\n");
                i--;
                if(i==-1){
                    i=3;
                }
                showbmp_v2(i%4+1,bname2[i]);
                break;
            case 3:
                printf("--------left---------\n");
                i++;
                if(i==4){
                    i=0;
                }
                showbmp_v2(i%4+1,bname2[i]);
                break;
            case 4:
                printf("--------right---------\n");
                i--;
                if(i==-1){
                    i=3;
                }
                showbmp_v2(i%4+1,bname2[i]);
                break;
            default:
                printf("--------error---------\n");
                break;
        }
    }
}

void show_pic3()
{
    int i=0;
    showbmp_v2(i%4+1,bname3[i]);
    while(1)
    {
        printf("while2\n");
        int dir = get_touch_way();
        if(dir==1){
            printf("--------up---------\n");
            return;
        }
        switch (dir)
        {

            case 2:
                printf("--------down---------\n");
                i--;
                if(i==-1){
                    i=3;
                }
                showbmp_v2(i%4+1,bname3[i]);
                break;
            case 3:
                printf("--------left---------\n");
                i++;
                if(i==4){
                    i=0;
                }
                showbmp_v2(i%4+1,bname3[i]);
                break;
            case 4:
                printf("--------right---------\n");
                i--;
                if(i==-1){
                    i=3;
                }
                showbmp_v2(i%4+1,bname3[i]);
                break;
            default:
                printf("--------error---------\n");
                break;
        }
    }
}

void show_pic4()
{
    int i=0;
    showbmp_v2(i%4+1,bname4[i]);
    while(1)
    {
        printf("while2\n");
        int dir = get_touch_way();
        if(dir==1){
            printf("--------up---------\n");
            return;
        }
        switch (dir)
        {

            case 2:
                printf("--------down---------\n");
                i--;
                if(i==-1){
                    i=3;
                }
                showbmp_v2(i%4+1,bname4[i]);
                break;
            case 3:
                printf("--------left---------\n");
                i++;
                if(i==4){
                    i=0;
                }
                showbmp_v2(i%4+1,bname4[i]);
                break;
            case 4:
                printf("--------right---------\n");
                i--;
                if(i==-1){
                    i=3;
                }
                showbmp_v2(i%4+1,bname4[i]);
                break;
            default:
                printf("--------error---------\n");
                break;
        }
    }
}

void show_pic5()
{
    int i=0;
    showbmp_v2(i%4+1,bname5[1]);
    while(1)
    {
        printf("while2\n");
        int dir = get_touch_way();
        if(dir==1){
            printf("--------up---------\n");
            return;
        }
        switch (dir)
        {

            case 2:
                printf("--------down---------\n");
                i--;
                if(i==-1){
                    i=3;
                }
                showbmp_v2(i%4+1,bname5[i]);
                break;
            case 3:
                printf("--------left---------\n");
                i++;
                if(i==4){
                    i=0;
                }
                showbmp_v2(i%4+1,bname5[i]);
                break;
            case 4:
                printf("--------right---------\n");
                i--;
                if(i==-1){
                    i=3;
                }
                showbmp_v2(i%4+1,bname5[i]);
                break;
            default:
                printf("--------error---------\n");
                break;
        }
    }
}

void star(){
     while(1){  
        draw_jx(0,0,800,480,0xffffff);//白色屏幕
        printf("welcome~\n");
        showbmp(100,60,"fj.bmp");
        showbmp(500,60,"ms.bmp");
        showbmp(100,300,"jz.bmp");
        showbmp(500,300,"rw.bmp");

 
        printf("while1\n");
        struct touch po = get_touch_point(); //获取屏幕触摸的坐标(800*480)
        if(po.x>100&&po.x<300&&po.y>60&&po.y<180){
            show_pic1();
        }
        if(po.x>500&&po.x<700&&po.y>60&&po.y<180){
            show_pic2();
        }
        if(po.x>100&&po.x<300&&po.y>300&&po.y<420){
            show_pic3();
        }
        if(po.x>500&&po.x<700&&po.y>300&&po.y<420){
            show_pic4();
        }
        else if (po.x>350&&po.x<450&&po.y>200&&po.y<280)
        {
             show_pic5();/* code */
        }
    }
}

int main()
{
    //1.初始化lcd
    if( lcd_init() == -1)
    {
        return -1;
    }
    //2.操作屏幕
    //开始界面
    star();
    //3.解除初始化
    lcd_uninit();
}