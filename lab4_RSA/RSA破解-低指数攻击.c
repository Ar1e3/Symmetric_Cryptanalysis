#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"miracl.h"
#define NUM 3


int CRT(big c[5], big d[5]);


int main()
{
	printf("****************使用低指数广播攻击攻击算法****************\n");
	miracl *mip = mirsys(5000, 16);
	mip->IOBASE = 16;
	FILE *fp;
	char fname1[][25] = { "Frame0.txt" ,"Frame1.txt","Frame2.txt","Frame3.txt","Frame4.txt","Frame5.txt", "Frame6.txt" ,"Frame7.txt","Frame8.txt","Frame9.txt","Frame10.txt","Frame11.txt" ,"Frame12.txt","Frame13.txt","Frame14.txt","Frame15.txt","Frame16.txt", "Frame17.txt" ,"Frame18.txt","Frame19.txt","Frame20.txt"};
	//char fname2[][25] = { "Frame7.txt","Frame11.txt" ,"Frame15.txt"  };
	char N2[300]; char e2[300], c2[300];
	big N[5], c[5], e[5], m, g;
	m = mirvar(0);
	g = mirvar(0);
	for (int i = 0; i <	NUM; i++)
	{
		N[i] = mirvar(0);
		c[i] = mirvar(0);
		e[i] = mirvar(0);
	}

	for (int i = 0; i < 21; i++)
	{
		fp = fopen(fname1[i], "r");
		fgets(N2, 257, fp);
		fgets(e2, 257, fp);
		printf("%s的e：", fname1[i]);
		puts(e2);
		printf("\n");
	}

	char fname[100];
	for (int i = 0; i < NUM; i++)
	{
		printf("请输入要攻击的文件名%d: ",i);
		scanf("%s", fname);
		fp = fopen(fname, "r");
		if (fp == NULL)
		{
			printf("文件名输入错误");
			return 0;
		}
		fgets(N2, 257, fp);
		fgets(e2, 257, fp);
		fgets(c2, 257, fp);
		cinstr(N[i], N2);
		cinstr(e[i], e2);
		cinstr(c[i], c2);

		printf("N = ");
		cotnum(N[i], stdout);
		printf("e = ");
		cotnum(e[i], stdout);
		printf("c = ");
		cotnum(c[i], stdout);
		printf("\n");
		
	}

	m=CRT(c, N);
	nroot(m, NUM, g);
	cotnum(g, stdout);
	



	return 0;

}


int CRT(big c[5],big d[5])
{

		miracl *mip = mirsys(5000, 16);
		mip->IOBASE = 16;

		int i = 0, j = 0;

		big m[NUM], a[NUM], x;
		big g, l, M_1[NUM], M[NUM], n;

		for (i = 0; i < NUM; i++) {
			m[i] = mirvar(0);
			M[i] = mirvar(0);
			M_1[i] = mirvar(0);
			a[i] = mirvar(0);
		}
		g = mirvar(0);
		x = mirvar(0);
		l = mirvar(1);
		n = mirvar(1);
		/*printf("\n111---------------------------");
		for (int i = 0; i < NUM; i++)
		{
			cotnum(c[i], stdout);
			cotnum(d[i], stdout);
		}
		printf("\n---------------------------\n");*/
		for (i = 0; i < NUM; i++) {
			copy(c[i], a[i]);
		}
		for (i = 0; i < NUM; i++) {
			copy(d[i], m[i]);
		}
		/*printf("\n---------------------------");
		for ( i = 0; i < NUM; i++)
		{
			cotnum(a[i], stdout);
			cotnum(m[i], stdout);
		}
		printf("\n---------------------------\n");*/

		for (i = 0; i < NUM; i++) {
			for (j = i + 1; j < NUM; j++) {
				egcd(m[i], m[j], g);
				if (mr_compare(g, l)) {
					printf("Can't use Chinese Remainder Theorem directly\n");
					return -1;
				}
			}
		}


		for (i = 0; i < NUM; i++) {
			fft_mult(n, m[i], n);//calculate m saved in n
		}
		for (i = 0; i < NUM; i++) {

			//calculate M[j] saved in M[i]
			copy(n, g);
			divide(g, m[i], M[i]);
			//calculate M[j]^-1(mod m[j]) saved in M_1[i]
			invmodp(M[i], m[i], M_1[i]);
			//calculate Xj saved in a[i]
			fft_mult(a[i], M[i], a[i]);
			fft_mult(a[i], M_1[i], a[i]);
			divide(a[i], n, n);
			//calculate X
			add(a[i], x, x);

		}
		//calculate X mod m
		divide(x, n, n);
		//cotnum(x, stdout);

		
		return x;
	}



