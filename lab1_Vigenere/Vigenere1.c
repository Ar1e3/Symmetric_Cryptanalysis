/*
ʹ���غ�ָ�������²���Կ�ĳ���
*/

#include<stdio.h>
#include<string.h>
#define MAXSTRING 1000
#define MAX_KEY_LENGTH 10 //��Կ����󳤶� 

int main() {
	FILE *fp;
	fp = fopen("m.txt", "r");
	if (fp == NULL)
	{
		printf("file open failed!");
		return 0;
	}

	char str[MAXSTRING];//������� 
	fgets(str, MAXSTRING, fp);
	//printf(str);

	int i, j, q, L, k;
	float IC=0;
	int count[26];//���������ĸ���ֵĴ��� 
	for (i = 1; i <= MAX_KEY_LENGTH; i++)//10�� 
	{
		//��Կ����Ϊi��һ����i������
		printf("key length is : %d\n", i);

		for (j = 0; j < i; j++)
		{
			//���� 
			L = 0;
			printf("��%d�����飺", j+1);
			for (q = 0; q < 26; q++)
			{
				count[q] = 0;
			}
			
			//����i�������е�ÿ������ 
			for (k = j; k < strlen(str); k = k + i)
			{
				L++;
				char cha;
				for (cha = 'a'; cha <= 'z'; cha++)
				{
					if (cha == str[k])
					{
						count[cha - 'a']++;
					}
				}
			}
			for (q = 0; q < 26; q++)
			{
				IC = IC + count[q] * (count[q] - 1)*1.0 / (L*(L - 1));
			}
			printf("IC : %f\n", IC);
		}
		printf("\n");
	}

}
