//������ع���
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define N 4000000 //��Կ������
#define k 60  //����
//#define p 0.75  //��ظ���
#define t 8   //�÷�������ʽ�ĳ�ͷ��


double cal(int m, int n);
int N1[N];
char N2[4 * N], N3[2 * N];//����ȫ�ֱ���  ��������쳣

int I0[N],I1[N],I2[k];
int G[k][N], H[k][k];
int N4[N];

int main()
{
	FILE *fp;
	double p;//���ļ��ж������ظ���
	int len, j = 0;
	fp = fopen("data-1.txt", "r+");
	if (fp == NULL)
	{
		printf("�ļ��򿪴��󣡣�");
		return 0;
	}
	//�ѵ�һ�е���ظ��ʷ���N3
	fgets(N3, N, fp);
	p = atof(N3);//�ַ���ת��Ϊdouble��
	fgets(N2, 2 * N + 1, fp);
	len = strlen(N2);
	for (int i = 0; i < len; i++)
	{
		if ((N2[i] == '0') || (N2[i] == '1'))
		{
			N3[j] = N2[i];//N3��ŵ�����Կ�����ַ���ʽ
			N1[j] = N2[i] - 48;//N1��ŵ�����Կ����������ʽ
			j++;
		}
	}
	//N1�����Կ����������ʽ
	int m, hmax, a;
	double sum, s;
	double aaa[200];
	//step1  ����ÿ�������漰��ϵʽ����Ŀm  s
	m = (int)floor(log2(N / (2 * k)))*(t + 1);//ע��ȡ��
	s = 0.5 + pow(2, t - 1)*pow(0.25, t);
	printf("�������mΪ��%d\n", m);
	//step2 Ѱ��hmax
	for (int i = 0; i <= m; i++)
	{
		sum = 0;
		for (int j = i; j <= m; j++)
		{
			sum = sum + cal(m, j)*(p*pow(s, j)*pow(1 - s, m - j) + (1 - p)*pow(1 - s, j)*pow(s, m - j));
		}
		aaa[i] = sum;
		if (sum*N >= k)
		{
			hmax = i;
		}
	}
	printf("�ҵ������hΪ��%d\n", hmax);
	/*
	for (int i = 0; i < m; i++)
	{
		printf("%d %.17f\n",i,aaa[i]);
	}
	*/
	a = (int)ceil(log2(N / k));//У�鷽����ĸ���
	//printf("\n%d", a);
	int column, row, check[200][200];
	row = a * (t + 1);
	column = t + 1;
	int fx[9] = { 60, 57, 51, 44, 25, 23, 13, 4, 0 };//��ŵ��Ǽ��鷽�̵ĳ�ʼ�±�
	int fy[9];


	//Ѱ��У�鷽��
	int y[9];
	for (int i = 0, q = 0; i < row; i++)
	{
		for (int x = 0; x < t + 1; x++)//���ڲ�ͬ��У�鷽����  ������ͬ  fy[]��ŵ��ǵ�i�����̵ĽǱ�
		{

			fy[x] = fx[x] * pow(2, i / (t + 1));
		}
		for (int j = 0; j < column; j++)
		{
			//check[i][j] = fy[i] - fy[j];
			//����������̵ĽǱ�
			check[i][j] = fy[j] - fy[q];
		}
		q++;
		q = q % (t + 1);
		/*printf("%d ", i / (t + 1));
		for (int x = 0; x < 9; x++)
		{
			printf("%d ",  fy[x]);
		}
		printf("\n");*/
	}


	//����Կ����Ӧ��λ�ô���
	int flag1, sum2, count, count_bit = 0, flag2, w=0;
	for (int i = 0; i < N; i++)
	{
		 count = 0;
		for (int j = 0; j < row; j++)
		{
			flag1 = 1, flag2 = 1;
			for (int l = 0; l < column; l++)
			{
				if ((i + check[j][l]) < 0)//����Ǳ�Ϊ��
				{
					flag1 = 0;
					break;//���в������ķ���ʽ
				}
				if ((i + check[j][l]) >= N)//����Ǳ곬����Կ�����ֵ
				{
					flag2 = 0;
					break;//���в������ķ���ʽ
				}
			}
			//

			if ((flag1 == 1) && (flag2 == 1))//����i֮��Ǳ�  >=0&&<N��
			{
				sum2 = 0;//��ʾУ�鷽�̵ĺͣ�
				for (int l = 0; l < column; l++)
				{
					sum2 = sum2 + N1[i + check[j][l]];

				}
				//printf("%d %d\n", i, sum2);

				if ((sum2 % 2) == 0)
				{
					count++;//��ʾ����i  ��17*9=153��У�鷽���е�����ĸ���
				}

			}
		}
		//	printf("\n %d %d", i, count);

		if (count >= hmax)
		{
			count_bit++;

			//printf("%d %d\n", i, count);
			I0[w] = i;//I�����Щ������92��У��ʽ�����ı��ص�λ��
			I1[w] = count;
			w++;
		}

	}
	printf("����%dbitʹ��У�鷽��������%d������\n", count_bit,hmax);

	//�ҵ��ı���ֱ�����
	/*
	for (int i = 0; i < w; i++)
	{
		printf("%d ", I0[i]);
		printf("%d\n", I1[i]);
	}
	*/
	//printf("%d ",w);//wΪi0Ԫ�ظ���
	//ð������  ��У��ʽ�������ı���λ��  ��h�ҳ���
	int temp;
	for (int i = 0; i < w-1; i++)
	{
		for (int j= 0; j < w-1-i; j++)
		{
			if (I1[j]< I1[j+1])
			{
				temp = I1[j];
				I1[j] = I1[j + 1];
				I1[j + 1] = temp;

				temp = I0[j];
				I0[j] = I0[j + 1];
				I0[j + 1] = temp;
			}
		}
	}
	/*
	//�������i1 i0 ���
	printf("\n");
	for (int i = 0; i < w; i++)
	{
		printf("%d ", I0[i]);
		printf("%d\n", I1[i]);
	}
	printf("\n");
	*/

	//���  ������h>hmax����Щ�������ҳ���h����60���ص�λ�ú�h
	for (int i = 0; i < k; i++)
	{
		printf("%d ", I0[i]);
		printf("%d\n", I1[i]);
	}
	
	int q;
	//���ɾ���G
	for (int i = 0; i < k; i++)//K ��
	{
		//������ǰ��ĵ�λ��
		for (int j = 0; j < k; j++)
		{
			if (i == j)
			{
				G[i][j] = 1;
			}
			else
			{
				G[i][j] = 0;
			}
		}

		//���ɾ���ĺ�벿��
		for (int j = k; j < N; j++)
		{
			G[i][j] = (G[i][j - 60] + G[i][j - 56] + G[i][j - 47] + G[i][j - 37] + G[i][j - 35] + G[i][j - 16] + G[i][j - 9] + G[i][j - 3]) % 2;
		}
	}

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (I0[i] == j)//���G����Ϊѡ�еı��ص�λ��
			{
				//printf("���е��⣡����\n");
				//printf("%d %d \n", i, I0[i]);
				for (int l = 0; l < k; l++)
				{
					//printf("%d ", G[l][j]);
					H[l][i] = G[l][j];
				}
				//printf("\n");
			}
			
		}
	}

	//printf("%d ",k);
	printf("\n����HΪ\n");
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			printf("%d ", H[i][j]);
		}
		printf("\n");
	}
	/*
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}*/
	printf("ѡ�����Կ��Ϊ\n");
	for (int i = 0; i < k; i++)
	{
		printf("%d ", N1[i]);
	}



	//���ò²��a'  ȥ������������  ������֪��Կ�����н��бȽ�
	int N3[] = { 0,1,0,0,0,1,0,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1,1,1 };
	//int N3[] = { 0  ,   1,     0,     0,     0,     0,     0,     0,     1,     0,     0,     0,     0,     0,     1,     0 ,    1,     1,     1,     1,     0,     0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0,     1,     1 ,    0 ,    1  ,   1  ,    0  ,   0  ,   0  ,   1  ,   0  ,   1  ,   0  ,   0  ,   0 ,    1 ,    1,     1 ,    1   ,  0   ,  0    , 1   ,  0  ,   0   ,  0  ,   0   ,  0   ,  1   ,  0   ,  0    , 0  ,   0
	//};
	int sum3 = 0;
	
	for (int i = 0; i < k; i++)
	{
		N4[i] = N3[i];
	}
	for (int j = k; j < N; j++)
	{
		N4[j]= (N4[j - 60] + N4[j - 56] + N4[j - 47] + N4[j - 37] + N4[j - 35] + N4[j - 16] + N4[j - 9] + N4[j - 3]) % 2;
	}
	for (int i = 0; i < N; i++)
	{
		if (N1[i]==N4[i])
		{
			sum3++;
		}
	}
	printf("\n����%dλ��ͬ ��ظ���Ϊ��%lf", sum3, sum3*1.0 / N);
	if (((sum3*1.0 / N) >= 0.7) && ((sum3 * 1.0 / N) <= 0.8))
	{
		printf("\n�ɹ�����\n");
	}
	else
	{
		printf("��Ҫ������\n");
	}

	
	int flag = 0;

	//һλ����
	printf("\n��������Ϊ1������\n");
	for (int i = 0; i < k; i++)
	{
		sum3= 0;
		N3[i] = N3[i] ^ 1;
		for (int i = 0; i < k; i++)
		{
			N4[i] = N3[i];
		}
		for (int j = k; j < N; j++)
		{
			N4[j] = (N4[j - 60] + N4[j - 56] + N4[j - 47] + N4[j - 37] + N4[j - 35] + N4[j - 16] + N4[j - 9] + N4[j - 3]) % 2;
		}
		for (int i = 0; i < N; i++)
		{
			if (N1[i] == N4[i])
			{
				sum3++;
			}
		}
		printf("\n%d %lf", sum3,sum3*1.0/N);
		if (((sum3*1.0 / N) >= 0.7) &&((sum3 * 1.0 / N) <= 0.8))
		{
			printf("\n����һλ�ɹ�����");
			flag = 1;
			break;
		}
		else
		{
			N3[i] = N3[i] ^ 1;
		}
	}
	if (flag==0)
	{
		printf("\n����һλʧ��");
	}
	return 0;

}

//�������ʽ
double cal(int m, int n)
{
	double c = 1;
	for (int i = 0; i < n; i++)
	{
		c = c * ((m - i) / ((n - i)*1.0));//ע�⸡����
	}
	return c;
}
