/*
使用重合指数法来猜测密钥的长度
*/

#include<stdio.h>
#include<string.h>
#define MAXSTRING 1000
#define MAX_KEY_LENGTH 10 //密钥的最大长度 

int main() {
	FILE *fp;
	fp = fopen("m.txt", "r");
	if (fp == NULL)
	{
		printf("file open failed!");
		return 0;
	}

	char str[MAXSTRING];//存放密文 
	fgets(str, MAXSTRING, fp);
	//printf(str);

	int i, j, q, L, k;
	float IC=0;
	int count[26];//用来存放字母出现的次数 
	for (i = 1; i <= MAX_KEY_LENGTH; i++)//10组 
	{
		//密钥长度为i，一共有i个分组
		printf("key length is : %d\n", i);

		for (j = 0; j < i; j++)
		{
			//清零 
			L = 0;
			printf("第%d个分组：", j+1);
			for (q = 0; q < 26; q++)
			{
				count[q] = 0;
			}
			
			//对于i个分组中的每个分组 
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
