#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"miracl.h"

int main()
{
	printf("****************使用共模攻击攻击算法****************\n");
	miracl *mip = mirsys(5000, 16);
	mip->IOBASE = 16;
	FILE *fp1, *fp2;
	char fname1[][25] = { "Frame0.txt" ,"Frame1.txt","Frame2.txt","Frame3.txt","Frame4.txt","Frame5.txt", "Frame6.txt" ,"Frame7.txt","Frame8.txt","Frame9.txt","Frame10.txt","Frame11.txt" ,"Frame12.txt","Frame13.txt","Frame14.txt","Frame15.txt","Frame16.txt", "Frame17.txt" ,"Frame18.txt","Frame19.txt","Frame20.txt" };

	char N2[300]; char e2[300];
	for (int i = 0; i < 21; i++)
	{
		fp1 = fopen(fname1[i], "r");
		fgets(N2, 257, fp1);
		//fgets(e2, 257, fp);
		printf("%s的N：", fname1[i]);
		puts(N2);
		printf("\n");
	}

	for (int i = 0; i < 21; i++)
	{
		fp1 = fopen(fname1[i], "r");
		fgets(N2, 257, fp1);
		fgets(e2, 257, fp1);
		
		printf("%s的e：", fname1[i]);
		puts(e2);
		printf("\n");
	}
	
	char fname[100];
	printf("请输入要攻击的文件名1: ");
	scanf("%s", fname);
	fp1 = fopen(fname, "r");
	if (fp1 == NULL)
	{
		printf("文件名输入错误");
		return 0;
	}
	printf("请输入要攻击的文件名2: ");
	scanf("%s", fname);
	fp2 = fopen(fname, "r");
	if (fp2 == NULL)
	{
		printf("文件名输入错误");
		return 0;
	}

	char N1[300],e1[300], c1[300], c2[300];//存放字符形式的N、e、c
	fgets(N1, 257, fp1);
	fgets(e1, 257, fp1);
	fgets(c1, 257, fp1);
	fgets(N2, 257, fp2);
	fgets(e2, 257, fp2);
	fgets(c2, 257, fp2);

	big N3, N4, e3, e4, c3, c4, r, s, z, zero, m, m1, one, test;//N3,e3,c3是第一个数据的信息，N4,e4,c4是第一个数据的信息
	N3 = mirvar(0);
	N4 = mirvar(0);
	e3 = mirvar(0);
	e4 = mirvar(0);
	c3 = mirvar(0);
	c4 = mirvar(0);
	r = mirvar(0);
	s = mirvar(0);
	z = mirvar(0);
	m = mirvar(0);
	m1 = mirvar(0);
	zero = mirvar(0);
	one = mirvar(1);
	test = mirvar(0);
	cinstr(N3, N1);
	cinstr(e3, e1);
	cinstr(c3, c1);
	cinstr(N4, N2);
	cinstr(e4, e2);
	cinstr(c4, c2);

	printf("file1:\n");
	printf("N1 = ");
	cotnum(N3, stdout);
	printf("e1 = ");
	cotnum(e3, stdout);
	printf("c1 = ");
	cotnum(c3, stdout);
	printf("\nfile2:\n");
	printf("N2 = ");
	cotnum(N4, stdout);
	printf("e2 = ");
	cotnum(e4, stdout);
	printf("c2 = ");
	cotnum(c4, stdout);
	printf("\n");

	//使用欧几里得算法
	//cotnum(e3, stdout);
	//cotnum(e4, stdout);
	xgcd(e3, e4, r, s, z);
	printf("r = ");
	cotnum(r, stdout);
	printf("s = ");
	cotnum(s, stdout);
	//cotnum(z, stdout);


	if (mr_compare(zero,r)==1)//r<0
	{
		//printf("1\n");
		negify(r, r);//r=-r
		xgcd(c3, N3, c3, c3, c3);//c3=c3^-1 mod N
	}
	else if (mr_compare(zero, s) == 1)//s<0
	{
		//printf("2\n");
		negify(s, s);//s=-s
		xgcd(c4, N4, c4, c4, c4);//c4=c4^-1 mod N
	}


	//cotnum(s, stdout);
	powmod(c3, r, N3, m);
	powmod(c4, s, N4, m1);
	multiply(m, m1, m);
	powmod(m, one, N3, m);
	printf("\n");
	printf("m = ");
	cotnum(m, stdout);


}