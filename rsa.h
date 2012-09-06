/************************************************************************************
This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.
作者：李恒林  henglinli@gmail.com
************************************************************************************/
#ifndef	   IN
#define	   IN
#endif

#ifndef	   OUT
#define	   OUT
#endif

#ifndef	   INOUT
#define	   INOUT
#endif
#ifndef    H_RSA_ENCRYPTION
#define    H_RSA_ENCRYPTION
#include "mpir.h" //MPIR头文件
//字符为ASCII编号.
//该函数将一个字符加密
int	RSA_encryption(	 IN    	int	 source,
		    	 IN    	int	 encryption,
			 IN   	mpz_t	 RSAn,
			 OUT    mpz_t	 secret)
{
	mpz_t	mpz_source;
	mpz_init(mpz_source);
	//int	encryption=0;
	//encryption=gen_key(RSAn,decryption);
	//gmp_printf("RSAn=%Zd\n",RSAn);
	//gmp_printf("decryption=%Zd\n",decryption);
	//printf("encryption=%d\n",encryption);
	mpz_set_ui(mpz_source,source);
	//void	mpz_powm_ui (mpz_t rop,mpz_t base,unsigned  long  int exp,mpz_t  mod)
	//Set rop to base^exp mod mod.
	mpz_powm_ui(secret,mpz_source,encryption,RSAn);
	//gmp_printf("secret=%Zd\n",secret);
	mpz_clear(mpz_source);
	return	0;
}
#endif

#ifndef H_RSA_DECRYPTION
#define H_RSA_DECRYPTION
#include "gen_key.h"
unsigned  long	RSA_decryption(	IN    mpz_t    secret,
				        IN    mpz_t    decryption,
				        IN    mpz_t    RSAn)
{
	unsigned long	result;
	mpz_t	real_secret;
	mpz_init(real_secret);
	mpz_powm(real_secret,secret,decryption,RSAn);
	result=mpz_get_ui(real_secret);
	mpz_clear(real_secret);
	return	result;
}
#endif
