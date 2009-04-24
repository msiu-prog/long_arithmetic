#ifndef _LONG_ARITHMETIC_H_
#define _LONG_ARITHMETIC_H_

#define FLG_NEGATIVE 0x01
#define FLG_ZERO     0x02

typedef struct long_num
{
  int flags;
  int size;
  unsigned int *digits;
} long_num;

long_num* lncreate(void);
void lndestroy(long_num*);
void lnadd(const long_num*, const long_num*, long_num*);
void lnsub(const long_num*, const long_num*, long_num*);

#endif /* #ifndef _LONG_ARITHMETIC_H_ */

