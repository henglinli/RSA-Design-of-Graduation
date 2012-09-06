/************************************************************************************
 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.
 作者：李恒林  henglinli@gmail.com
************************************************************************************/
#include <stdio.h>
#include <errno.h>
#include "io.h"
#include "gen_key.h"
#include "rsa.h"
//主函数
int main(int argc, char* argv[])
{
  printf("***********************************\n");
  printf(">李恒林 hegnlinli@gmail.com\n");
  printf("***********************************\n");
  printf(">该软件为开源软件,遵循GPL.下载地址为:\n");
  printf("***********************************\n");
  fprintf (stderr,">用法:\n>加密:\n>rsa <inputfile.txt>,\n>inputfile.txt是要加密的文件,\n>生成3个文件,分别为:\n>加密后的文件encrypted_file.txt,\n>公钥文件public_key.txt,\n>私钥文件private_key.txt.\n");
  fprintf (stderr,">解密:\n>(1)rsa <private_key.txt> <encrypted_file.txt>,\n>公钥文件public_key.txt,\n>私钥文件private_key.txt.\n>(2)rsa d <encrypted_file.txt>,\n>公钥文件public_key.txt,\n>私钥文件private_key.txt,\n>private_key.txt为私钥文件,\n>使用参数d时默认私钥文件为private_key.txt,\n>输出解密后的文件为outputfile.txt.\n");
  int	source,
    encryption;
  mpz_t	RSAn,
    decryption,
    secret;
  //初始化大数,分配内存空间
  mpz_init(RSAn);
  mpz_init(decryption);
  mpz_init(secret);
  //没有指定要加密的文件
  //要求输入文件名
  if(argc == 1)
    {
      // 打开文件,读取数据
      input_file();
    }
  //指定了加密文件，则先生成公钥和私钥，
  //再加密文件并输出加密后的文件。
  else if	(argc==2)
    {
      // 打开文件,读取数据
      if ( ( fp_read=fopen ( argv[1] , "r" ) ) == NULL )
	{
	  printf( ">文件%s没有找到.\n",argv[1]);
	  perror("fopen");
	  exit(errno);
	}
    }
  else if	(argc==3)
    {
      //先读取私钥文件默认为private_key.txt
      // 打开文件,读取数据
      //printf("argv[1]=%s\n",argv[1]);
      //printf("argv[2]=%s\n",argv[2]);
      if(*argv[1]=='d')
	{
	  if((fp_read= fopen("private_key.txt", "r")) == NULL )
	    {
	      printf( ">文件private_key.txt没有找到.\n");
	      exit(errno);
	    }
	}
      else
	{
	  if  ( (fp_read=fopen(argv[1], "r")) == NULL )
	    {
	      printf( ">文件%s没有找到.\n",argv[1]);
	      perror("fopen");
	      exit(errno);
	    }
	}
      //读取RSAn和dedecryption
      gmp_fscanf(fp_read,"%Zd",RSAn);
      //gmp_printf("RSAn=\n%Zd\n",RSAn);
      gmp_fscanf(fp_read,"%Zd",decryption);
      //gmp_printf("decryption=\n%Zd\n",decryption);
      //关闭访问的文件
      close_read_file();
      /*********************************************************/
      //解密加密的文件默认为encrypted_file.txt
      // 打开文件,读取数据
      printf(">解密中......\n");
      if((fp_read= fopen(argv[2], "r")) == NULL )
	{
	  printf( ">文件%s没有找到.\n",argv[2] );
	  perror("fopen");
	  exit(errno);
	}
      unsigned  long	 //character_couts,
	result;
      char	outputfile_name[]={"outputfile.txt"};
      //fseek(fp_read,0L,2);
      //fscanf_s(fp_read,"%d",&character_cout);
      //gmp_fscanf(fp_read,"%Zd",secret);
      //character_couts=mpz_get_ui(secret);
      //rewind(fp_read); 
      //printf("character_couts=%d\n",character_couts);
      //gmp_fscanf(fp_read,"%Zd",secret);
      write_file(outputfile_name);
      while	(1)//character_couts);
	{
	  //character_couts--;
	  if	(gmp_fscanf(fp_read,"%Zd",secret)==EOF)
	    break;
	  //gmp_printf("secret=\n%Zd\n",secret);
	  result=RSA_decryption(secret,decryption,RSAn);
	  //printf("result=%d\n",result);
	  //printf("result mod 256=%d\n",result%256);
	  //printf("g=%d\n",'g');
	  fputc(result,fp_write);
	}
      //printf("%c\n",result);
      //关闭访问的文件
      close_read_file();
      close_write_file();
      //销毁大数,释放内存空间
      mpz_clear(RSAn);
      mpz_clear(decryption);
      mpz_clear(secret);
      //system("pause");
      return	0;
    }
  else
    //参数错误则提示用法
    {
      fprintf (stderr, "*******************************\n>出错啦!\n*******************************\n");
      //fprintf (stderr,">用法:\n>加密:\n>rsa <inputfile.txt>,\n>inputfile.txt是要加密的文件,\n>生成3个文件,分别为:\n>加密后的文件encrypted_file.txt,\n>公钥文件public_key.txt,\n>私钥文件private_key.txt.\n");
      //fprintf (stderr,">解密:\n>(1)rsa <private_key.txt> <encrypted_file.txt>,\n>公钥文件public_key.txt,\n>私钥文件private_key.txt.\n>(2)rsa d <encrypted_file.txt>,\n>公钥文件public_key.txt,\n>私钥文件private_key.txt,\n>private_key.txt为私钥文件,\n>使用参数d时默认私钥文件为private_key.txt,\n>输出解密后的文件为outputfile.txt.\n");   
      return errno;
    }
		   
  //先生成公钥和私钥，并输出为两个文件，
  //分别为：pulic_key.txt和private_key.txt
  //
  //公钥为(RSAn,encryption)私钥为(RSAn,decryption)
  //
  encryption=gen_key(RSAn,decryption);
  //等加密完成输出加密后的文件,才生成秘钥文件.
  /*******************************************************/
  //该段生成加密后的文件encrypted_file.txt
  //unsigned	long	character_couts;
  char		tmp_char,
    encrypted_file_name[]={"encrypted_file.txt"};
  write_file(encrypted_file_name);
  tmp_char=fgetc(fp_read);
  //character_couts=0;
  while	(tmp_char!=EOF)
    {
      //character_couts++;
      source=tmp_char;
      RSA_encryption(source,encryption,RSAn,secret);
      //写入文件
      // int		gmp_fprintf (FILE *fp,const char *fmt,... )
      //Print to the stream fp. Return the number of characters written,
      //or −1 if an error occurred.
      gmp_fprintf(fp_write,"%Zd\n",secret);
      /**************************************************
       //该方法为老版本的.
       //size_t	mpz_out_str (FILE	*stream,int base,mpz_t op)
       //Output op on stdio stream stream,as a string of digits in base base.
				if	((size=mpz_out_str(fp_write,62,secret))==0)
				{
				printf(">写入文件encrypted_file.txt出错.\n");
				exit(0);
				}
				//gmp_fprintf(fp_write,"%Zd",secret);
				//fprintf(fp_write,"\n");
				//printf("%d\n",size);
				/*************************************************/
      tmp_char=fgetc(fp_read);
    }
  //在文件头/尾写入加密字符的个数
  //fseek(fp_write,0L,2);
  //rewind(fp_write);
  //fprintf(fp_write,"%d\n",character_couts);
  /*********************************************************/
  //该段生成公钥文件public_key.txt
  //格式为:
  //RSAn
  //encryption
  char	public_key_name[]={"public_key.txt"};
  write_file(public_key_name);
  gmp_fprintf(fp_write,"%Zd\n",RSAn);
  //fprintf(fp_write,"\n");
  fprintf(fp_write,"%d",encryption);
  /*********************************************************/
  //该段生成私钥文件private_key.txt
  //格式为:
  //RSAn
  //decryption
  char	private_key_name[]={"private_key.txt"};
  write_file(private_key_name);
  gmp_fprintf(fp_write,"%Zd\n",RSAn);
  //fprintf(fp_write,"\n");
  gmp_fprintf(fp_write,"%Zd",decryption);
  //关闭访问的文件
  close_write_file(); 
  close_read_file();
  //销毁大数,释放内存空间
  mpz_clear(RSAn);
  mpz_clear(decryption);
  mpz_clear(secret);
  //system("pause");
  return	0;
}
