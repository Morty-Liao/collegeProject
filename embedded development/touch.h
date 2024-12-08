#ifndef __TOUCH_H__
#define __TOUCH_H__

//触摸点结构体：保存了触摸点的横坐标和纵坐标
struct touch
{
    int x;
    int y;
};

struct touch get_touch_point();
int get_touch_way();
#endif