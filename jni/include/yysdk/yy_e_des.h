#ifndef YY_E_DES_H
#define YY_E_DES_H

#include "yy_p_type.h"

//DES总是以8字节对齐
#define YY_E_DES_ALIGN(d) YY_P_ALIGN( d, 8 )

#ifdef  __cplusplus
extern "C" {
#endif

/* DES加密,秘钥key为8字节，同解密秘钥一样的 */
extern void yy_e_des_encode( const char * data_in, size_t len, char * data_out, char * key );

/* DES解密，秘钥key为8字节 */
extern void yy_e_des_decode( const char * data_in, size_t len, char * data_out, char * key );

/* 运用上面的加密解密，多次加密在解密，在加密 */
extern void yy_e_3des_encode( const char * data_in, size_t len, char * data_out, char * key );

/* 运用上面的加密解密，多次解密在加密，在解密 */
extern void yy_e_3des_decode( const char * data_in, size_t len, char * data_out, char * key );

//3DES加解密,key为16字节
extern int yy_e_des_validation_test( );

#ifdef  __cplusplus
}
#endif

#endif
