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

long_num* ln_create(void);
void ln_destroy(long_num*);

long_num* ln_create_from_hex_string(char *, int);

void ln_add(const long_num*, const long_num*, long_num*);
void ln_sub(const long_num*, const long_num*, long_num*);
void ln_mult(const long_num*, const long_num*, long_num*);
void ln_div(const long_num*, const long_num*, long_num*);
void ln_mod(const long_num*, const long_num*, long_num*);
void ln_exp(const long_num*, const long_num*, long_num*);

void ln_print_hex(const long_num*);

#endif /* #ifndef _LONG_ARITHMETIC_H_ */

