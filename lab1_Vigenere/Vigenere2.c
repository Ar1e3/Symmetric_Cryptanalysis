/*
֮ǰ�ĳ����Ѿ��ж���Կ����Ϊ5����ʹ�û��غ�ָ������ȷ����Կ
*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAXSTRING 1000
#define KEYLENGTH 5


int main()
{
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
	int i, j, k, fre1[26], fre2[26], L1, L2,m,n;
	char cha;
	double MIc=0,z=0;
	for (i = 0; i < KEYLENGTH - 1; i++)//0 1 2 3
	{
		for (j = 0; j < KEYLENGTH; j++) //0 1 2 3 4 
		{
			if (j <= i)
			{
				continue;
			}
			//0-1  0-2 0-3 0-4 1-2 1-3 1-4 2-3 2-4 3-4   ��10��

			printf("k%d and k%d\n", i + 1, j + 1);

			for ( m = 0; m < 26; m++)
			{
				fre1[m] = 0;
				fre2[m] = 0;
			}
			L1 = 0;
			L2 = 0;
			for (k = i; k < strlen(str); k = k + KEYLENGTH)//������ki���ܵķ���
			{
				L1++;//��¼���鳤��
				for ( cha = "a"; cha <= "z"; cha++)
				{
					if (cha == str[k])
					{
						fre1[cha - 'a']++;

					}
				}
			}

			for (k = j; k < strlen(str); k = k + KEYLENGTH)//������kj���ܵķ���
			{
				L2++;
				for ( cha = 'a"'; cha <= 'z'; cha++)
				{
					if (cha == str[k])
					{
						fre2[cha - 'a']++;

					}
				}
			}

			/*for ( q = 0; q < 26; q++)
			{
				printf("%d",fre1[q]);
			}
			*/
			//fre1[]              fre2[]
			//���㲻ͬ���λ���µ��غ�ָ��
			printf("kj-ki\t\tMIC\t\tabs(MIC-0.065)\n");
			for ( k = 0; k < 26; k++)
			{
				MIc = 0;
				for ( m = 0; m < 26; m++)
				{
					n = (m + k) % 26;
					MIc = MIc + fre2[n] * fre1[m] * 1.0 / (L1*L2);

				}	
				if (fabs(MIc-0.065)<=0.01)
				{
				printf("%d\t\t%f\t%f !!!!!!\n", k, MIc, fabs(MIc - 0.065));
				}
				printf("%d\t\t%f\t%f\n", k, MIc, fabs(MIc - 0.065));
			}
		}
	}

	return 0;
}
