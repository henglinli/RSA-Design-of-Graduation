/************************************************************************************
This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.
作者：李恒林  henglinli@gmail.com
************************************************************************************/
// RSA_by_henglinli@gmail.com.cpp : 定义控制台应用程序的入口点。
//http://zh.wikipedia.org/wiki/%E5%8D%A2%E5%8D%A1%E6%96%AF-%E8%8E%B1%E9%BB%98%E6%A3%80%E9%AA%8C%E6%B3%95

#include <stdio.h>
#include "io.h"
#include "gen_key.h"
#include "rsa.h"
int encryptfile(char sourcefile[],
	     	char enfile[],
	        char pukfile[],
		char prkfile[])
{
	int	source,
		encryption;
	mpz_t	RSAn,
		decryption,
		secret;
	//初始化大数,分配内存空间
	mpz_init(RSAn);
	mpz_init(decryption);
	mpz_init(secret);
		//先生成公钥和私钥，并输出为两个文件，
		//分别为：pulic_key.txt和private_key.txt
		//
		//公钥为(RSAn,encryption)私钥为(RSAn,decryption)
		//
		encryption=gen_key(RSAn,decryption);
		//等加密完成输出加密后的文件,才生成秘钥文件.
		/*******************************************************/
		char		tmp_char;
		read_file_name(sourcefile);	
		write_file_name(enfile);
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
		//关闭访问的文件
		close_write_file(); 
		close_read_file();
		//在文件头/尾写入加密字符的个数
		//fseek(fp_write,0L,2);
		//rewind(fp_write);
		//fprintf(fp_write,"%d\n",character_couts);
		/*********************************************************/
		//该段生成公钥文件public_key.txt
		//格式为:
		//RSAn
		//encryption
		write_file_name(pukfile);
		//fprintf(fp_write,"\n");
		gmp_fprintf(fp_write,"%Zd\n",RSAn);
		fprintf(fp_write,"%d",encryption);
		//关闭访问的文件
		close_write_file(); 
		/*********************************************************/
		//该段生成私钥文件private_key.txt
		//格式为:
		//RSAn
		//decryption
		write_file_name(prkfile);
		gmp_fprintf(fp_write,"%Zd\n",RSAn);
		//fprintf(fp_write,"\n");
		gmp_fprintf(fp_write,"%Zd",decryption);
		//关闭访问的文件
		close_write_file(); 
		//销毁大数,释放内存空间
		mpz_clear(RSAn);
		mpz_clear(decryption);
		mpz_clear(secret);
		//system("pause");
		return	0;
}
int decryptfile(char sourcefile[],
	        char defile[],
	        char prkfile[])
{
	mpz_t	RSAn,
	        decryption,
		secret;
	//初始化大数,分配内存空间
	mpz_init(RSAn);
	mpz_init(decryption);
	mpz_init(secret);
	read_file_name(prkfile);
	//读取RSAn和dedecryption
		gmp_fscanf(fp_read,"%Zd",RSAn);
		//gmp_printf("RSAn=\n%Zd\n",RSAn);
		gmp_fscanf(fp_read,"%Zd",decryption);
		//gmp_printf("decryption=\n%Zd\n",decryption);
		//关闭访问的文件
		close_read_file();
		unsigned  long	 //character_couts,
				  result;
	read_file_name(sourcefile);
	write_file_name(defile);
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
