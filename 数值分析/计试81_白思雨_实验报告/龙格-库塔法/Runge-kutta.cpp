#include<iostream>
#include<cmath>
using namespace std;
double func1(double x,double y)
{
    return (-0.9 * y / (1 + 2 * x)); //这是被积函数，若计算其他函数积分则在此更换函数
} 
double Y[1000],X[1000]; 
double x0, xn, yo, h;
int main()
{
    //输入基本条件，x0,xn,yo,h
   
	cout << "Please input x0,xn,yo and h:";
	cin >> x0 >> xn >> yo >> h;
    int n = (xn - x0) / h;//计算分点个数，n为分点的个数-1；
	Y[0] = yo; 
	X[0] = x0;
    for(int i = 1;i <= n; ++i) //计算yi(i=0,1...n)，并将其储存到Y[1000]数组中
    {
        X[i] = x0 + h * i;
        double K1 = h * func1(X[i - 1], Y[i - 1]);
        double K2 = h * func1(X[i - 1] + 0.5 * h, Y[i - 1] + 0.5 * K1);
        double K3 = h * func1(X[i - 1] + 0.5 * h, Y[i - 1] + 0.5 * K2);
        double K4 = h * func1(X[i - 1] + h, Y[i - 1] + K3);
        Y[i] = Y[i - 1] + (K1 + 2 * K2 + 2 * K3 + K4) / 6;
    }
    //输出yi(i = 0,1...n)
    for(int i = 0;i <= n; ++i)
    {
        cout << "y" << i << ':' << Y[i] <<endl;
    }
    return 0;
}
