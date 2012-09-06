/************************************************************************************
This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.
作者：李恒林  henglinli@gmail.com
************************************************************************************/
#ifndef H_GEN_PRIMER
#define H_GEN_PRIMER

#include <stdlib.h>
//#include <ctime>
//#include <iostream>
//#pragma comment(lib, "gmp.lib") //windows中使用
#include "mpir.h" //MPIR的头文件
//using namespace std;
//98个素数数组，作为梅森数的指数p，MP=2^p-1
int primer[]={383,	389,	397,	401,	409,
419,	421,	431,	433,	439,	443,	449,	457,	461,	463,	467,	479,	487,	491,	499,	503,	509,	521,	523,	541,
547,	557,	563,	569,	571,	577,	587,	593,	599,	601,	607,	613,	617,	619,	631,	641,	643,	647,	653,	659,
661,	673,	677,	683,	691,	701,	709,	719,	727,	733,	739,	743,	751,	757,	761,	769,	773,	787,	797,	809,
811,	821,	823,	827,	829,	839,	853,	857,	859,	863,	877,	881,	883,	887,	907,	911,	919,	929,	937,	941,
947,	953,	967,	971,	977,	983,	991,	997,	1009,	1013,	1019,	1021,	1031	};
//随机选一个作为指数
//srand((unsigned)time(NULL));
//int	n=rand()%98;
int   n=9;
//该函数随机选一个作为梅森数的指数p
int	random_primer()
{
	return	primer[n];
}
//该函数选素数数组中的下一个素数作为梅森数的指数p
int	random_primer_next()
{
	n++;
	return	primer[n%98];
}
//该函数将参数 mpz_t	Mersenne_number 赋值为大于梅森数2^p-1的素数
//使用的gmp的voidmpz_nextprime (mpz t rop,mpz t op)函数
//Set rop tothenextprimegreaterthan op.
//Thisfunctionusesaprobabilisticalgorithmtoidentifyprimes.Forpracticalpurposesit’s
//adequate,thechanceofacompositepassingwillbeextremelysmall.
int	gen_primer(mpz_t  Mersenne_number,int	random_primer)
{
		//int   p=random_primer();
		//cout	<<"random_primer="<<p<<endl;
		//mpz_t	Mersenne_number; //mpz_t 为GMP内置大数类型
		mpz_ui_pow_ui(Mersenne_number,2,random_primer); //GMP所有函数基本都是以mpz打头 
		//gmp_printf("2^p=%Zd\n",Mersenne_number);
		mpz_sub_ui(Mersenne_number,Mersenne_number,2);//2^p-2
		//gmp_printf("2^p-2=%Zd\n",Mersenne_number);
		//void mpz_nextprime	(mpz t rop, mpz t op )
		//Set rop to the next prime greater than op.
		//This function uses a probabilistic algorithm to identify primes. For practical purposes it’s
		//adequate, the chance of a composite passing will be extremely small.
		mpz_nextprime(Mersenne_number,Mersenne_number);
		//gmp_printf("大于2^p-2的素数=%Zd\n",Mersenne_number);
		//mpz_clear(Mersenne_number);
		return 0;
}
#endif
