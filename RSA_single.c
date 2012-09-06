#include <stdio.h>
#include "gen_key.h"
#include "rsa.h"
int	main()
{
      	int	//source,
	       	result,
	       	encryption;
	mpz_t	RSAn,
		decryption,
		secret;
	//初始化大数,分配内存空间
	mpz_init(RSAn);
	mpz_init(decryption);
	mpz_init(secret);

	encryption=gen_key(RSAn,decryption);
	RSA_encryption('g',encryption,RSAn,secret);
	result=RSA_decryption(secret,decryption,RSAn);
        printf("%d   %c\n",result,result);
	gmp_printf("RSAn=%Zd\n",
		   //  "encryption=%Zd\n",
		   //  "decryption=%Zd\n",
		   RSAn
		   // encryption,
		   //decryption
		   );
       	//销毁大数,释放内存空间
       	mpz_clear(RSAn);
	mpz_clear(decryption);
       	mpz_clear(secret);
	//system("pause");
	return	0;

}
