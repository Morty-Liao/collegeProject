#include "touch.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>
#include <stdlib.h>

//获取触摸点的坐标
struct touch get_touch_point()
{
    struct touch tp;
    tp.x=tp.y=-1;

    // 	1.open
    int fd = open("/dev/input/event0",O_RDONLY);
    if(fd == -1)
    {   //如果打开失败返回(-1,-1)
        perror("open input error");
        return tp;
    }

    // 2.read
    while(1)
    {   //一直读取文件直到读取到一对坐标为止
        struct input_event ie;
        read(fd,&ie,sizeof(ie));

        if(ie.type == EV_ABS && ie.code == ABS_X) //触摸屏是事件，并且code为ABS_X
        {
            tp.x = ie.value * (1.0*800/1024);//横坐标
        }
        if(ie.type == EV_ABS && ie.code == ABS_Y) //触摸屏是事件，并且code为ABS_Y
        {
            tp.y = ie.value * (1.0*480/600);//纵坐标
        }

        if(tp.x != -1 && tp.y != -1)
        {   //读取到了一对坐标
            break;
        }
    }
    // 3.close
    close(fd);

    return tp;
}

//获取一次手指滑动的方向
//1:上   2:下  3:左  4:右  0:失败
int get_touch_way()
{
    struct touch sa; //保存起始点的坐标
    sa.x=sa.y=-1;

    struct touch la; //保存终点的坐标
    la.x=la.y=-1;

    // 	1.open
    int fd = open("/dev/input/event0",O_RDONLY);
    if(fd == -1)
    {   //如果打开失败返回(-1,-1)
        perror("open input error");
        return 0;
    }

    // 2.read
    while(1)
    {   //一直读取文件直到读取到一对坐标为止
        struct input_event ie;
        read(fd,&ie,sizeof(ie));

        if(ie.type == EV_ABS && ie.code == ABS_X) //触摸屏是事件，并且code为ABS_X
        {
            if(sa.x == -1) //说明这个坐标是第一次获取到的横坐标，就是起始点的横坐标
            {
                sa.x = ie.value * (1.0*800/1024);//横坐标
            }
            //la始终保存最新的坐标
            la.x = ie.value * (1.0*800/1024);//横坐标
        }
        if(ie.type == EV_ABS && ie.code == ABS_Y) //触摸屏是事件，并且code为ABS_Y
        {
            if(sa.y == -1) //说明这个坐标是第一次获取到的纵坐标，就是起始点的纵坐标
            {
                sa.y = ie.value * (1.0*480/600);//纵坐标
            }
            //la始终保存最新的坐标
            la.y = ie.value * (1.0*480/600);//纵坐标
        }

        //当手指离开屏幕，la结构体中就是保存的终点坐标
        if( ie.type == EV_KEY && ie.code == BTN_TOUCH && ie.value == 0)
        { //当输入事件属于按键事件并且按键为触摸屏按键并且value==0说明手指离开了屏幕
            break;
        }
    }
    // 3.close
    close(fd);

    //判断手指的滑动方向
    if( abs(sa.x-la.x) > abs(sa.y-la.y) ) //判断哪个方向移动的距离大
    {   //x轴滑动
        if(sa.x > la.x && (sa.x-la.x > 50) )
        {   //左
            return 3;
        }
        else if(sa.x < la.x && (la.x-sa.x > 50) )
        {   //右
            return 4;
        }
        else
        {
            return 0;
        }
    }
    else if( abs(sa.x-la.x) <=  abs(sa.y-la.y) ) //判断哪个方向移动的距离大
    {   //y轴滑动
        if(sa.y > la.y && (sa.y-la.y > 50) )
        {   //上
            return 1;
        }
        else if(sa.y < la.y && (la.y-sa.y > 50) )
        {   //下
            return 2;
        }
        else
        {
            return 0;
        }
    }
}