//快速相关攻击
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define N 4000000 //密钥流长度
#define k 60  //级数
//#define p 0.75  //相关概率
#define t 8   //该反馈多项式的抽头数


double cal(int m, int n);
int N1[N];
char N2[4 * N], N3[2 * N];//必须全局变量  否则出现异常

int I0[N],I1[N],I2[k];
int G[k][N], H[k][k];
int N4[N];

int main()
{
	FILE *fp;
	double p;//从文件中读入的相关概率
	int len, j = 0;
	fp = fopen("data-1.txt", "r+");
	if (fp == NULL)
	{
		printf("文件打开错误！！");
		return 0;
	}
	//把第一行的相关概率放入N3
	fgets(N3, N, fp);
	p = atof(N3);//字符串转换为double型
	fgets(N2, 2 * N + 1, fp);
	len = strlen(N2);
	for (int i = 0; i < len; i++)
	{
		if ((N2[i] == '0') || (N2[i] == '1'))
		{
			N3[j] = N2[i];//N3存放的是密钥流的字符形式
			N1[j] = N2[i] - 48;//N1存放的是密钥流的整型形式
			j++;
		}
	}
	//N1存放密钥流的整型形式
	int m, hmax, a;
	double sum, s;
	double aaa[200];
	//step1  计算每个比特涉及关系式的数目m  s
	m = (int)floor(log2(N / (2 * k)))*(t + 1);//注意取整
	s = 0.5 + pow(2, t - 1)*pow(0.25, t);
	printf("所计算的m为：%d\n", m);
	//step2 寻找hmax
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
	printf("找到的最大h为：%d\n", hmax);
	/*
	for (int i = 0; i < m; i++)
	{
		printf("%d %.17f\n",i,aaa[i]);
	}
	*/
	a = (int)ceil(log2(N / k));//校验方程组的个数
	//printf("\n%d", a);
	int column, row, check[200][200];
	row = a * (t + 1);
	column = t + 1;
	int fx[9] = { 60, 57, 51, 44, 25, 23, 13, 4, 0 };//存放的是检验方程的初始下标
	int fy[9];


	//寻找校验方程
	int y[9];
	for (int i = 0, q = 0; i < row; i++)
	{
		for (int x = 0; x < t + 1; x++)//由于不同的校验方程组  次数不同  fy[]存放的是第i个方程的角标
		{

			fy[x] = fx[x] * pow(2, i / (t + 1));
		}
		for (int j = 0; j < column; j++)
		{
			//check[i][j] = fy[i] - fy[j];
			//计算各个方程的角标
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


	//将密钥流对应的位置带入
	int flag1, sum2, count, count_bit = 0, flag2, w=0;
	for (int i = 0; i < N; i++)
	{
		 count = 0;
		for (int j = 0; j < row; j++)
		{
			flag1 = 1, flag2 = 1;
			for (int l = 0; l < column; l++)
			{
				if ((i + check[j][l]) < 0)//如果角标为负
				{
					flag1 = 0;
					break;//这行不算合理的方程式
				}
				if ((i + check[j][l]) >= N)//如果角标超过密钥流最大值
				{
					flag2 = 0;
					break;//这行不算合理的方程式
				}
			}
			//

			if ((flag1 == 1) && (flag2 == 1))//加上i之后角标  >=0&&<N；
			{
				sum2 = 0;//表示校验方程的和；
				for (int l = 0; l < column; l++)
				{
					sum2 = sum2 + N1[i + check[j][l]];

				}
				//printf("%d %d\n", i, sum2);

				if ((sum2 % 2) == 0)
				{
					count++;//表示比特i  在17*9=153个校验方程中等于零的个数
				}

			}
		}
		//	printf("\n %d %d", i, count);

		if (count >= hmax)
		{
			count_bit++;

			//printf("%d %d\n", i, count);
			I0[w] = i;//I存放那些至少有92个校验式成立的比特的位置
			I1[w] = count;
			w++;
		}

	}
	printf("共有%dbit使得校验方程至少有%d个成立\n", count_bit,hmax);

	//找到的比特直接输出
	/*
	for (int i = 0; i < w; i++)
	{
		printf("%d ", I0[i]);
		printf("%d\n", I1[i]);
	}
	*/
	//printf("%d ",w);//w为i0元素个数
	//冒泡排序  将校验式成立最多的比特位置  和h找出来
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
	//将排序的i1 i0 输出
	printf("\n");
	for (int i = 0; i < w; i++)
	{
		printf("%d ", I0[i]);
		printf("%d\n", I1[i]);
	}
	printf("\n");
	*/

	//输出  从满足h>hmax的那些比特中找出来h最多的60比特的位置和h
	for (int i = 0; i < k; i++)
	{
		printf("%d ", I0[i]);
		printf("%d\n", I1[i]);
	}
	
	int q;
	//生成矩阵G
	for (int i = 0; i < k; i++)//K 行
	{
		//先生成前面的单位阵
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

		//生成矩阵的后半部分
		for (int j = k; j < N; j++)
		{
			G[i][j] = (G[i][j - 60] + G[i][j - 56] + G[i][j - 47] + G[i][j - 37] + G[i][j - 35] + G[i][j - 16] + G[i][j - 9] + G[i][j - 3]) % 2;
		}
	}

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (I0[i] == j)//如果G的列为选中的比特的位置
			{
				//printf("运行到这！！！\n");
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
	printf("\n矩阵H为\n");
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
	printf("选择的密钥流为\n");
	for (int i = 0; i < k; i++)
	{
		printf("%d ", N1[i]);
	}



	//利用猜测的a'  去生成他的序列  并于已知密钥流序列进行比较
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
	printf("\n共有%d位相同 相关概率为：%lf", sum3, sum3*1.0 / N);
	if (((sum3*1.0 / N) >= 0.7) && ((sum3 * 1.0 / N) <= 0.8))
	{
		printf("\n成功！！\n");
	}
	else
	{
		printf("需要修正！\n");
	}

	
	int flag = 0;

	//一位修正
	printf("\n汉明距离为1的修正\n");
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
			printf("\n修正一位成功！！");
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
		printf("\n修正一位失败");
	}
	return 0;

}

//计算二项式
double cal(int m, int n)
{
	double c = 1;
	for (int i = 0; i < n; i++)
	{
		c = c * ((m - i) / ((n - i)*1.0));//注意浮点型
	}
	return c;
}
