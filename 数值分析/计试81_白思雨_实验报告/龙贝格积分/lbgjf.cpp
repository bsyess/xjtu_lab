#include<iostream>
#include<cmath>
using namespace std;

double a, b, fa, fb;
double T, T1, S, S1, C, C1, R, R1, e; 

double fx1(double x)
{
	double fx = 1/(1 + x);
	return fx; 
} 

double fx2(int t, double a, double b)//T 的高次迭代函数 
{
	double m = (1 << t), Tk = 0, Tkk, z;
	for(int i = 1;i <= m;++i)
	{
		z = a + (2 * i - 1) * (b - a) / (2 * m);
		Tk += fx1(z);
	}
	return Tkk = (b - a) * Tk / (m * 2);
}

int main()
{
	cout << "请输入积分下界 a：\n";	//输入 X 下界 
	cin >> a;
	cout << "请输入积分下上界 b：\n";//输入 X 下界 
	cin >> b;
	cout << "请输入计算精度 e：\n";
	cin >> e;
	//计算 f(x) 函数上下界的值 
	fa = fx1(a); 
	fb = fx1(b);
	//输出上下界函数值、上下界 fx 函数值、计算精度 e 
	cout << "a = " << a << "\nb = " << b << "\nfa = " << fa << "\nfb = " << fb << "\ne = " << e << "\n";
	T1 = (b - a) * (fa + fb) / 2;
	for(int i = 0;;++i)
	{
		double Tkk = fx2(i, a, b);
		//cout << Tkk;
		T = T1 / 2 + Tkk;
		T1 = T;
		S = T + (T - T1) / (4 - 1);
		S1 = S;
		if(i)
		{
			C = S + (S - S1) /(4 * 4 - 1);
			C1 = C; 
		}
		if(i > 1)
		{
			R = C + (C - C1) /(4 * 4 * 4 - 1);
			if(abs(R - R1) < pow(10,e))break;
			R1 = R; 
		}
	}
	cout << "积分计算数值为：" << T; 
	return 0;
} 
