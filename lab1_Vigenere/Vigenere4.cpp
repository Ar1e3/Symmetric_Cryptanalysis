#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAXSTRING 1000

int main()
{
	
 
      char a[MAXSTRING];
      FILE *fp1,*fp2;
      fp1=fopen("dec.txt","w");
	  fp2=fopen("m.txt","r");
	  if(fp2==NULL)
	  {
	  	printf("file open failed");
	  }
	  fgets(a,MAXSTRING,fp2);
	  char My[]={"crypt"};//密钥 
	  int len1=strlen(My);
	  int len2=strlen(a);
	  int i,j;
	  j=0;
	 char c[1000];//存放解密后的内容
	// printf("%d\n",len2) ;
	  for(i=0;i<len2;i++)
	   {
		c[i]=(a[i]-My[j]+26)%26+'a';//解密 
		j++;
		if(j%len1==0&&j!=0) j=0;		
	   } 
	   //printf("%d\n",strlen(c));
	   fputs(c,fp1);

	return 0;

}


