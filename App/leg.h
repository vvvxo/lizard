#ifndef _LEG_H
#define _LEG_H
#define L 0
#define R 2
#define X 3
#define Y 4
#define LEFT -1
#define RIGHT 1
#define RADIAN_ANGL 3.14159265358979323846 / 180 //乘上这个数,你就可以变成角度值
typedef struct //thigh大腿，calf小腿
{
    float leg_long;
    unsigned char leg_num;
    float thigh_long;
    float thigh_angle;
    float calf_long;
    float calf_angle;
    float leg_x;
    float leg_y;
    int direction;
} leg_num;

#endif
