/************************************************************************************
This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.
作者：李恒林  henglinli@gmail.com
************************************************************************************/
#ifndef H__IO
#define H__IO
#include <stdlib.h>
#include <errno.h>
//using namespace std;
FILE	*fp_read,
  *fp_write;
char	filename[20]={0};
//读取文件数据的函数
int	input_file()
{
  printf(">请输入要加密的文件.\n>");
  //char	one_char;
  scanf("%s",filename);
  // 打开文件,读取数据
  if((fp_read=fopen(filename, "r")) == NULL )
    {
      printf( ">文件%s没有找到.\n",filename );
      perror("fopen");
      exit(errno);
    }
  //one_char=getchar();
  return	0;
}
int read_file (char name[])
{
  // 读取文件
  if( (fp_read=fopen(name,"r")) == NULL )
    {
      printf(">文件%s创建失败.\n",filename );
      perror("fopen");
      exit(errno);
    }
  //one_char=getchar();
  return	0;
}
//写入文件数据的函数
int write_file (char	name[])
{
  //char	one_char;
  // 读取文件
  if( (fp_write=fopen( name,"w+")) == NULL )
    {
      printf(">文件%s创建失败.\n",filename );
      perror("fopen");
      exit(errno);
    }
  //one_char=getchar();
  return	0;
}

//关闭读取的文件
int	close_read_file()
{
  if( fp_read)
    {
      if ( fclose( fp_read ) )
	{
	  printf( ">有文件未正确关闭.\n" );
	}
    }
  return	0;
}
//关闭写入的文件
int	close_write_file()
{
  if( fp_write)
    {
      if ( fclose( fp_write) )
	{
	  printf( ">有文件未正确关闭.\n" );
	}
    }
  return	0;
}
#endif
