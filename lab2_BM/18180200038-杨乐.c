#include<stdio.h>
#include<string.h>
#define MAX 100
int a[MAX], f[MAX][MAX], l[MAX],d[MAX];
void B_M(int a[], int len);

int main()
{
	char a1[MAX];//��������01���ش�
	int len;//��Ž����ش�ת�����01ֵ
	printf("��������������У�");
	gets(a1);
	//puts(a);
	len = strlen(a1);
	for (int i = 0; i < len; i++)
	{
		a[i] = a1[i]-48;//���ַ�ת��Ϊ����  �ַ�0��asc��Ϊ48
	}
	//��ʼ��
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			f[i][j] = 0;
		}
	}
	f[0][0] = 1;
	l[0] = 0;
	B_M(a, len);
	return 0;
}

void B_M(int a[], int length)
{

	for (int i = 0; i < length; i++)
	{
		int flag = 0, n, m,tag;
		int p = 0;
		int q = 0;
		//����d[i]
		d[i] = a[i];
		for (int j = 1; j <= l[i]; j++)
		{
			d[i] += f[i][l[i] - j]*a[i-j];
			
		}
		d[i] = d[i] % 2;
		if (d[i] == 0)//fn(x)�������ɵ�n+1λ
		{
			for (int k = 0; k < length; k++)
			{
				f[i + 1][k] = f[i][k];
			}
			l[i + 1] = l[i];
		}
		else//fn(x)�������ɵ�n+1λ
		{
			for (int k = i; k >= 1; k--)
			{
				if (l[k]==l[k-1])
				{
					flag = 0;
				}
				if (l[k]>l[k-1])
				{
					flag = 1;
					m = k - 1;
					n = i;
					break;
				}
			}
			if (flag==0)
			{
				f[i + 1][i + 1] = 1, f[i + 1][0] = 1;
				l[i + 1] = i + 1;
			}
			else if (flag==1)
			{
				p = m - l[m];
				q = n - l[n];
				if (p>=q)
				{
					
					int y[MAX] = {0};
					for (int t = 0; t < length; t++)
					{
						y[t] = f[m][t];
					}
					for (int t = length; t >= 0; t--)
					{
						y[t + p - q] = y[t];//���ƣ�m-lm��-(n-ln)
					}
					for (int t = 0; t < p - q; t++)
					{
						y[t] = 0;
					}
					for (int s = 0; s < length; s++)
					{
						f[i + 1][s] = f[i][s] - y[s];
						f[i + 1][s] =( f[i + 1][s]+2) % 2;//Ϊ�˳���-1 mod 2=-1
						if (f[i + 1][s] == 1)
						{
							tag = s;
						}
					}
					l[i + 1] = tag;
				}
				else
				{
					int y[MAX] = { 0 };
					for (int t = 0; t < length; t++)
					{
						y[t] = f[n][t];
					}
					for (int t = length; t >= 0; t--)
					{
						y[t + q - p] = y[t];//����(n-ln)-��m-lm��
					}
					for (int t = 0; t < q-p; t++)
					{
						y[t] = 0;
					}
					for (int s = 0; s < length; s++)
					{
						f[i + 1][s] = y[s] - f[m][s];
						f[i + 1][s] = (f[i + 1][s]+2) % 2;
						if (f[i + 1][s] == 1)
						{
							tag = s;
						}
					}
					l[i + 1] = tag;
					
				}
			}
		}
	}
    //���
	/*
	for (int i = 0; i <= length; i++)
	{
		for (int j = 0; j <= length; j++)
		{
			printf("%d ", f[i][j]);
		}
		printf("\n");
	}
	*/
	printf("\n���ɸö��������е����LFSR����������ʽf(x)=");
	int tag = 0;
	for (int k = 0; k <= length; k++)
	{
		if (f[length][k] == 1)
		{
			tag = k;//��¼��һ��Ϊ1��λ��
			break;
		}
	}	
		for (int k = length; k >tag ; k--)//���蹲n��1  ���ǰn-1��
		{
			if(f[length][k] != 0)
			{
				printf("x^%d+", k);
			}
		}
		if (tag == 0)
		{
			printf("%d\n", 1);
		}
		else
		{
			printf("x^%d\n", tag);
		}
}