/************************************************************************************
This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.
作者：李恒林  henglinli@gmail.com
************************************************************************************/
#ifndef H__GEN_KEY
#define H__GEN_KEY
#include "gen_primer.h"
//#include "gmpxx.h"
//该函数生成公钥(n,e)和私钥(n.d)。
//公钥为(RSAn,tmp_encryption),私钥为(RSAn,decryption)
int	gen_key(mpz_t	RSAn,mpz_t	decryption)
{
		int		random_primer_p=0,
				random_primer_q=0,
				encryption;//e
		mpz_t		primer_p,//p
					primer_q,//q
					coprime_encryption,//z
					primer_p_sub_1,//p-1
					primer_q_sub_1;//q-1

		mpz_init(primer_p); //大数t使用前要进行初始化，以便动态分配空间
		mpz_init(primer_q);
		mpz_init(primer_p_sub_1);
		mpz_init(primer_q_sub_1);
		mpz_init(coprime_encryption);

		random_primer_p=random_primer();
		//printf("random_primer_p=%d\n",random_primer_p);
		random_primer_q=random_primer_next();
		//printf("random_primer_q=%d\n",random_primer_q);
		//产生大素数
		gen_primer(primer_p,random_primer_p);
		//gmp_printf("primer_p=%Zd\n",primer_p);
		gen_primer(primer_q,random_primer_q);
		//gmp_printf("primer_q=%Zd\n",primer_q);
		mpz_mul(RSAn,primer_p,primer_q);//RSAn=primer_p*primer_q,得到RSAn
		mpz_sub_ui(primer_p_sub_1,primer_p,1);//primer_p-1
		mpz_sub_ui(primer_q_sub_1,primer_q,1);//primer_1-1
		mpz_mul(coprime_encryption,primer_p_sub_1,primer_q_sub_1);//coprime_encryption=(primer_p-1)*(primer_q-1)

		mpz_clear(primer_p_sub_1);//释放内存
		mpz_clear(primer_q_sub_1);
		mpz_clear(primer_p);
		mpz_clear(primer_q);
		/*************************************************
		//在98个素数中随机选一个作为encryption公钥。
		int	tmp_encryption=random_primer();	
		//判断encryption和coprime_encryption是否互素。	
		while	(1)
		{
			mpz_init_set_ui(encryption,tmp_encryption);
			//
			//int	mpz_invert (mpz t rop,mpz t op1,mpz t op2)
			//Computetheinverseof op1 modulo op2 andputtheresultin rop.Iftheinverseexists,the
			//returnvalueisnon-zeroand rop willsatisfy0 ≤ rop < op2.Ifaninversedoesn’texistthe
			//returnvalueiszeroand rop isundefned
			if		(mpz_invert (decryption, encryption,coprime_encryption) == 0)
			 //abort ();
				tmp_encryption=random_primer_next();
			else	
				break;
		}
		//计算decryption。
		//gmp_printf("公钥为(n,e)=(%Zd,%Zd)\n",RSAn,encryption);
		//gmp_printf("私钥为(n,d)=(%Zd,%Zd)\n",RSAn,decryption);
		*************************************************************/
		//判断tmp_encryption和coprime_encryption是否互素。
		encryption=random_primer();		
		while	(mpz_sgn(primer_p))
		{
			
			mpz_mod_ui(primer_p,coprime_encryption,encryption);//取模prmer_p=coprime_encryption MOD encryption
			if	(mpz_sgn(primer_p))//如果模为不为0，则退出循环，得到encyption.因为encryption本身就
								   //就是素数，只需判断模	prmer_p=coprime_encryption MOD encryption是否为0
								   //就可知道coprime_encryption和encryption是否互素。
				break;
			else	mpz_set_ui(primer_p,1);//如果模为0，则设置primer_p为1，使循环继续，以便重新得到encryption。
			//恰巧98个素数都能被coprime_encryption整除的概率几乎为0或者为0。本人未有严格证明。实际应用足矣。
		}
		
		//寻找decryption私钥。
		//encryption*decryption-1=n*coprime_encryption		--> decryption	= (n*coprime_encryption+1)/encryption且余数为0；
		int	n=1;
		mpz_t	tmp_nz;
		mpz_t	tmp_nz_add_1;
		mpz_t	tmp_mod;
		mpz_init(tmp_nz);
		mpz_init(tmp_nz_add_1);
		mpz_init(tmp_mod);
		while	(n)
		{
			mpz_mul_ui(tmp_nz,coprime_encryption,n);//n*coprime_encryption
			mpz_add_ui(tmp_nz_add_1,tmp_nz,1);//n*coprime_encryption+1
			mpz_mod_ui(tmp_mod,tmp_nz_add_1,encryption);//(n*coprime_encryption+1)/encryption
			if	mpz_sgn(tmp_mod)//如果tmp_mod不为0，则继续循环
			{
				n++;
				continue;
			}
			else	//如果tmp_mod为0，即n*coprime_encryption+1整除encryption,的到decryption.
			{
				mpz_cdiv_q_ui(decryption,tmp_nz_add_1,encryption);
				break;
			}
				
		}
		mpz_clear(tmp_nz);
		mpz_clear(tmp_nz_add_1);
		mpz_clear(tmp_mod);
		
		mpz_clear(coprime_encryption);
		return	encryption;
}

#endif