#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"miracl.h"

int main()
{
	printf("****************ʹ�÷���ֽ��㷨****************\n");
	miracl *mip = mirsys(5000, 16);
	mip->IOBASE = 16;
	FILE *fp;
	//char fname[][25] = { "Frame0.txt" ,"Frame1.txt","Frame2.txt","Frame3.txt","Frame4.txt","Frame5.txt", "Frame6.txt" ,"Frame7.txt","Frame8.txt","Frame9.txt","Frame9.txt","Frame10.txt" };
	char fname[100];
	printf("������Ҫ�������ļ���: ");
	scanf("%s", fname);
	fp = fopen(fname, "r");
	if (fp==NULL)
	{
		printf("�ļ����������");
		return 0;
	}
	
	char N1[300]; char e1[300], c1[300];//����ַ���ʽ��N��e��c
	fgets(N1, 257, fp);
	fgets(e1, 257, fp);
	fgets(c1, 257, fp);
	
	/*
	puts(N1);
	puts(e1);
	puts(c1);
	*/
	big N, e, c, k, y, d, y1,  x, a, b, p, q, p1, q1, fn, m, f;
	BOOL flag;
	N = mirvar(0);
	e = mirvar(0);
	c = mirvar(0);
	k = mirvar(0);
	y = mirvar(0);
	d = mirvar(1);
	y1 = mirvar(0);
	x = mirvar(0);
	a = mirvar(0);
	b = mirvar(0);
	p = mirvar(0);
	q = mirvar(0);
	fn = mirvar(0);
	p1 = mirvar(0);
	q1 = mirvar(0);
	m = mirvar(0);
	f = mirvar(0);
	//���ַ���N e cת��Ϊbig��
	cinstr(N, N1);
	cinstr(e, e1);
	cinstr(c, c1);
	
	printf("N = ");
	cotnum(N,stdout);
	printf("e = ");
	cotnum(e,stdout);
	printf("c = ");
	cotnum(c, stdout);
	
	nroot(N, 2, x);
	negify(N, b);
	copy(x, a);//a=x=N^1/2
	flag = 0;
	while (flag!=1||mr_compare(y,b)==0)//flag=0����y=0����ѭ��
	{
		incr(a, 1, a);
		multiply(a, a, f);
		add(f, b, y1);//y1=a^2-N
		flag=nroot(y1, 2, y);
		if (flag==1)
		{
			break;
		}
		
	}
	printf("\n");
	if (flag==1)
	{
		printf("****************����ֽ�ɹ�****************\n");
		add(a, y, p);
		negify(y, b);
		add(a, b, q);
		printf("\n");
		printf("p = ");
		cotnum(p, stdout);
		printf("\n");
		printf("q = ");
		cotnum(q, stdout);

		//����

		decr(p, 1, p1);
		decr(q, 1, q1);
		multiply(p1, q1, fn);//fn=(p-1)(q-1)
		//����d
		xgcd(e, fn, d, d, d);//d=e^-1 mod (p-1)(q-1)
		printf("\n");
		printf("d = ");
		cotnum(d, stdout);
		//��������
		powmod(c, d, N,m);
		printf("\n");
		printf("m = ");
		cotnum(m, stdout);


	}
	else
	{
		printf("�ֽ�ʧ��");
	}

	return 0;
}