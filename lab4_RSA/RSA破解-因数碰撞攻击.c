#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"miracl.h"

int main()
{
	printf("****************使用因数碰撞攻击算法****************\n");
	miracl *mip = mirsys(5000, 16);
	mip->IOBASE = 16;
	FILE *fp;
	char fname1[][25] = { "Frame0.txt" ,"Frame1.txt","Frame2.txt","Frame3.txt","Frame4.txt","Frame5.txt", "Frame6.txt" ,"Frame7.txt","Frame8.txt","Frame9.txt","Frame10.txt","Frame11.txt" ,"Frame12.txt","Frame13.txt","Frame14.txt","Frame15.txt","Frame16.txt", "Frame17.txt" ,"Frame18.txt","Frame19.txt","Frame20.txt" };
	
	big N[30], e[30], c[30];
	char N1[300], e1[300], c1[300];
	//初始化数组
	for (int i = 0; i < 30; i++)
	{
		N[i] = mirvar(0);
		e[i] = mirvar(0); 
		c[i] = mirvar(0);
	}

	for (int i = 0; i < 21; i++)
	{
		fp = fopen(fname1[i], "r");
		fgets(N1, 257, fp);
		fgets(e1, 257, fp);
		fgets(c1, 257, fp);
		cinstr(N[i], N1);
		cinstr(e[i], e1);
		cinstr(c[i], c1);
	}

	int flag = 0;
	big z, one, b;
	z = mirvar(0);
	one = mirvar(1);
	b = mirvar(0);

	//寻找有公因数的N
	printf("数据帧号1  数据帧号2   最大公约数  \n");
	for (int i = 0; i < 20; i++)
	{
		for (int j = i+1; j < 21; j++)
		{
			if (mr_compare(N[i], N[j]) == 0)//N相等
			{
				continue;
			}
			egcd(N[i], N[j],z);
			if (mr_compare(z, one) == 0)//N互素
			{
				continue;
			}
			else
			{
				
				printf("%d          %d           ", i, j);
				cotnum(z, stdout);
				copy(z, b);
			}
		}
	}

	//
	big N2, N3, e2, e3, c2, c3, p2, q2, p3, q3, m2, m3, p2_, p3_, q2_, q3_, f1n, f2n, d2, d3;
	N2 = mirvar(0);
	N3 = mirvar(0);
	e2 = mirvar(0);
	e3 = mirvar(0);
	c2 = mirvar(0);
	c3 = mirvar(0);
	p2 = mirvar(0);
	q2 = mirvar(0);
	p3 = mirvar(0);
	q3 = mirvar(0);
	m2 = mirvar(0);
	m3 = mirvar(0);
	p2_ = mirvar(0);
	q2_ = mirvar(0);
	p3_ = mirvar(0);
	q3_ = mirvar(0);
	f1n = mirvar(0);
	f2n = mirvar(0);
	d2 = mirvar(0);
	d3 = mirvar(0);

	FILE *fp1, *fp2;
	char fname[100];
	printf("请输入要攻击的文件名1: ");
	scanf("%s", fname);
	fp1 = fopen(fname, "r");
	if (fp1 == NULL)
	{
		printf("文件名输入错误");
		return 0;
	}

	fgets(N1, 257, fp1);
	fgets(e1, 257, fp1);
	fgets(c1, 257, fp1);
	cinstr(N2, N1);
	cinstr(e2, e1);
	cinstr(c2, c1);

	printf("请输入要攻击的文件名2: ");
	scanf("%s", fname);
	fp2 = fopen(fname, "r");
	if (fp2 == NULL)
	{
		printf("文件名输入错误");
		return 0;
	}

	fgets(N1, 257, fp2);
	fgets(e1, 257, fp2);
	fgets(c1, 257, fp2);
	cinstr(N3, N1);
	cinstr(e3, e1);
	cinstr(c3, c1);
	printf("\n****************file1的初始参数****************\n");
	printf("N1 = ");
	cotnum(N2, stdout);
	printf("e1 = ");
	cotnum(e2, stdout);
	printf("c1 = ");
	cotnum(c2, stdout);
	printf("\n");
	printf("****************file2的初始参数****************\n");
	printf("N2 = ");
	cotnum(N3, stdout);
	printf("e2 = ");
	cotnum(e3, stdout);
	printf("c2 = ");
	cotnum(c3, stdout);
	printf("\n****************最大公约数为****************:");
	cotnum(b, stdout);

	//计算p和q
	printf("\n****************破译的参数****************\n");
	copy(b, p2);
	copy(b, p3);
	copy(N2, m2);//此处m2和m3仅为中间变量  防止除法时将N2 N3变为零
	copy(N3, m3);
	divide(m2, p2, q2);
	divide(m3, p3, q3);
	printf("p1 = ");
	cotnum(p2, stdout);
	printf("q1 = ");
	cotnum(q2, stdout);
	printf("\n");
	printf("p2 = ");
	cotnum(p3, stdout);
	printf("q2 = ");
	cotnum(q3, stdout);

	//计算m2
	decr(p2, 1, p2_);//p2_=p2-1
	decr(q2, 1, q2_);//q2_=q2-1
	multiply(p2_, q2_, f1n);//f1n=(p2-1)(q2-1)
	xgcd(e2, f1n, d2, d2, d2);

	printf("\nd1 = ");
	cotnum(d2, stdout);
	//cotnum(N2, stdout);
	powmod(c2, d2, N2, m2);
	printf("m1 = ");
	cotnum(m2, stdout);

	printf("\n");
	//计算m3
	decr(p3, 1, p3_);
	decr(q3, 1, q3_);
	multiply(p3_, q3_, f2n);
	xgcd(e3, f2n, d3, d3, d3);

	printf("\nd2 = ");
	cotnum(d3, stdout);

	powmod(c3, d3, N3, m3);
	printf("m2 = ");
	cotnum(m3, stdout);
	return 0;
}