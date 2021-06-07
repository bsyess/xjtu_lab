//
//  main.c
//  龙格-库特法
//
//  Created by 谭丽 on 2020/5/6.
//  Copyright © 2020 谭丽. All rights reserved.
//

#include <stdio.h>
#include <math.h>
double func1(double x,double y)
{
    return -0.9*y/(1+2*x);
    //这是被积函数，若计算其他函数积分则在此更换函数
}
int main()
{
    //输入基本条件，x0,xn,y0,h
    double x0;double xn;double y0;double h;
    printf("请依次输入区间起点x0、区间终点xn、及y0，步长h：");
    scanf("%lf%lf%lf%lf",&x0,&xn,&y0,&h);
    int n=(xn-x0)/h;//计算分点个数，n为分点的个数-1；
    //计算yi(i=0,1...n)，并将其储存到Y[1000]数组中
    double Y[1000];double X[1000];
    Y[0]=y0;X[0]=x0;
    for(int i=1;i<=n;i++)
    {
        X[i]=x0+h*i;
        double K1=h*func1(X[i-1],Y[i-1]);
        double K2=h*func1(X[i-1]+0.5*h,Y[i-1]+0.5*K1);
        double K3=h*func1(X[i-1]+0.5*h,Y[i-1]+0.5*K2);
        double K4=h*func1(X[i-1]+h,Y[i-1]+K3);
        Y[i]=Y[i-1]+(K1+2*K2+2*K3+K4)/6;
    }
    //输出yi(i=0,1...n)
    for(int i=0;i<=n;i++)
    {
        printf("y%d:%lf\n",i,Y[i]);
    }
    return 0;
}
