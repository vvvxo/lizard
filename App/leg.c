/*************************
 	腿部移动对大狗XY轴的影响
     三角函数以弧度为单位
 *************************/
#include <math.h>
#include "leg.h"
#include "pid.h"
leg_num leg[2] = {
    {L, 0, 0, 0, 0, 0, 0, 0},
    {R, 0, 0, 0, 0, 0, 0, 0},
};

int rotation(int LEG, float ANGLE)
{
    return 0;
}
//腿部横向移动
void leg_x(int LEG, float LEG_X)
{
    //算出主电机到脚触地点的距离
    leg[LEG].leg_long = leg[LEG].thigh_angle - (leg[LEG].calf_long * cos(RADIAN_ANGL * (leg[LEG].calf_angle)));

    //算出横向移动需要多少
    leg[LEG].thigh_angle = acos(RADIAN_ANGL * (LEG_X / leg[LEG].leg_long));

    //得出横向移动时纵向移动了多少
    leg[LEG].leg_y = leg[LEG].thigh_angle * sin(RADIAN_ANGL * (leg[LEG].thigh_long));
}

//腿部纵向移动
void leg_y(int LEG, float LEG_Y)
{
    //算出主电机到脚触地点的距离
    leg[LEG].leg_long = leg[LEG].thigh_angle - (leg[LEG].calf_long * cos(RADIAN_ANGL * (leg[LEG].calf_angle)));

    //算出纵向移动需要多少
    leg[LEG].thigh_angle = asin(RADIAN_ANGL * (LEG_Y / leg[LEG].leg_long));

    //得出纵向移动时横向移动了多少
    leg[LEG].leg_y = leg[LEG].thigh_angle * cos(RADIAN_ANGL * (leg[LEG].thigh_long));
}

void move_forward(int DIRECTION, float DISTANCE)
{
    
}
