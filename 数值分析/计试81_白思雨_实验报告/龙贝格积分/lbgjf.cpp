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

double fx2(int t, double a, double b)//T �ĸߴε������� 
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
	cout << "����������½� a��\n";	//���� X �½� 
	cin >> a;
	cout << "������������Ͻ� b��\n";//���� X �½� 
	cin >> b;
	cout << "��������㾫�� e��\n";
	cin >> e;
	//���� f(x) �������½��ֵ 
	fa = fx1(a); 
	fb = fx1(b);
	//������½纯��ֵ�����½� fx ����ֵ�����㾫�� e 
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
	cout << "���ּ�����ֵΪ��" << T; 
	return 0;
} 
