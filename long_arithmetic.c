#include <malloc.h>
#include <stdio.h>

#include "long_arithmetic.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define CLEAR_ALL  0
#define CLEAR_TAIL 1

long_num* ln_create(void) {
  // needs correction
  long_num *p;
  
  p = (long_num *) malloc(sizeof(long_num));
  if(p == NULL) {
    // no memory error
    return NULL;
  }
  
  p->flags = 0;
  
  p->digits = calloc(DEFAUL_DIGITS_SIZE, sizeof(unsigned int));
  if(p->digits == NULL) {
    // no memory error
    free(p);
    return NULL;
  }
  
  p->size = DEFAUL_DIGITS_SIZE;
  
  SET_NUM_FLG(p, FLG_ZERO);
  
  return p;
}

void ln_destroy(long_num *num) {
  // needs correction
  if(num == NULL) {
    // invalid argument error
    return;
  }
  
  if(num->digits != NULL) {
    free(num->digits);
  }
  free(num);
}

long_num* ln_create_from_hex_string(char *str, int len) {
  // needs correction
  long_num *p;
  char *strptr;
  
  unsigned int *d;
  unsigned int *high;
  
  register unsigned int digit = 0;
  register unsigned int hex = 0;
  
  int i = 0;
  
  p = (long_num *)malloc(sizeof(long_num));
  if(p == NULL) {
    // no memory error
    return NULL;
  }
  
  p->flags = 0;
  
  if(len > 0 && (str[0] == '-' || str[0] == '~')) {
    SET_NUM_FLG(p, FLG_NEGATIVE);
    --len;
    ++str; 
  }
  
  p->size = (((len + 1) >> 1) + sizeof(unsigned int) - 1)/sizeof(unsigned int);
  p->digits = malloc(p->size * sizeof(unsigned int));
  
  if(p->digits == NULL) {
    // no memory error
    free(p);
    return NULL;
  }
  
  high = p->digits + p->size - 1;
  for(strptr = str + len - 1, d = p->digits; d <= high; ++d) {
    digit = 0;
    for(i = 0; i < 8*sizeof(unsigned int) && strptr >= str; i += 4) {
      hex = *strptr - ((*strptr >= '0' && *strptr <= '9') ? '0' : ('a' - 10));
      digit = digit | (hex << i);
      --strptr;
    }
    *d = digit;
  }
  
  return p;
}

void ln_add(const long_num *f, const long_num *s, long_num *res) {
  // needs implementation

  // for test
  ln_low_add(f, s, res);
  UNSET_NUM_FLG(res, FLG_ZERO);
}

void ln_sub(const long_num *f, const long_num *s, long_num *res) {
  // needs implementation

  // for test
  ln_low_sub(f, s, res);
  UNSET_NUM_FLG(res, FLG_ZERO);
}

void ln_mult(const long_num *f, const long_num *s, long_num *res) {
  // needs implementation
}

void ln_div(const long_num *f, const long_num *s, long_num *res) {
  // needs implementation
}

void ln_mod(const long_num *f, const long_num *s, long_num *res) {
  // needs implementation
}

void ln_exp(const long_num *f, const long_num *s, long_num *res) {
  // needs implementation
}

void ln_low_add(const long_num *f, const long_num *s, long_num *res) {
  // needs correction
  unsigned long long int sum_digits;
  unsigned long long int carry;
  unsigned int *f_d, *s_d, *res_d, *d;
  unsigned int *high_min, *high_max, *high;
  
  ln_extend_num(res, MAX(f->size, s->size), CLEAR_TAIL);

  f_d = f->digits;
  s_d = s->digits;
  res_d = res->digits;

  high_min = res->digits + MIN(f->size, s->size) - 1;
  high_max = res->digits + MAX(f->size, s->size) - 1;
  high = res->digits + res->size - 1;
  
  carry = 0;
  while(res_d <= high_min) {
    sum_digits = (unsigned long long int) *f_d + (unsigned long long int) *s_d + carry;
    *res_d = (unsigned int) sum_digits;
   
    carry = (sum_digits >> 4*sizeof(unsigned long long int)) ? 1 : 0;
    ++f_d;
    ++s_d;
    ++res_d;
  }

  d = (f->size > s->size) ? f_d : s_d;
  while(res_d <= high_max) {
    sum_digits = (unsigned long long int) *d + carry;
    *res_d = (unsigned int) sum_digits;
	
    carry = (sum_digits >> 4*sizeof(unsigned long long int)) ? 1 : 0;
    ++d;
    ++res_d;
  }

  // process overflow
  if(carry) {
    if(res_d > high) {
      res->digits = (unsigned int*) realloc(res->digits, (res->size + 1) * sizeof(unsigned int));
      res_d = res->digits + res->size;
      ++res->size;
    }
    *res_d = 1;
  }
}

void ln_low_sub(const long_num *f, const long_num *s, long_num *res) {
  // needs correction
  unsigned int carry, carry_tmp;
  unsigned int *f_d, *s_d, *res_d;
  unsigned int *high_min, *high_max;

  ln_extend_num(res, f->size, CLEAR_TAIL);

  f_d = f->digits;
  s_d = s->digits;
  res_d = res->digits;

  high_min = res->digits + s->size - 1;
  high_max = res->digits + f->size - 1;

  carry = 0;
  while(res_d <= high_max) {
    carry_tmp = (*f_d < carry) ? 1 : 0;
    *res_d = *f_d - carry;
    
    if(res_d <= high_min) {
      carry_tmp = (carry_tmp || (*res_d < *s_d)) ? 1 : 0;
      *res_d -= *s_d;
    }
    
    carry = carry_tmp;
    ++f_d;
    ++s_d;
    ++res_d;
  }
}

void ln_extend_num(long_num *num, int size, int flag) {
  // needs implementation
  unsigned int *d;
  unsigned int *high;
  
  if(flag == CLEAR_ALL) {
    high = num->digits + num->size - 1;
    for(d = num->digits; d <= high; ++d) {
      *d = 0;
    }
  }
  
  if(num->size < size) {
    num->digits = (unsigned int*) realloc(num->digits, size * sizeof(unsigned int));
    d = num->digits + num->size;
    high = num->digits + size - 1;
    num->size = size;
    while(d <= high) {
      *d = 0;
      ++d;
    }
  }
}

void ln_print_hex(const long_num *num) {
  // needs correction
  unsigned int *d;
  unsigned int *high;
  register unsigned int digit;
  register unsigned int hex;
  
  char strhexbuf[2*sizeof(unsigned int) + 1];
  char *strptr;
  
  if(num == NULL) {
    // invalid argument error
    return;
  }
  
  if(ISSET_NUM_FLG(num, FLG_NEGATIVE)) {
    printf("-");
  }
  
  if(ISSET_NUM_FLG(num, FLG_ZERO)) {
    printf("0");
    return;
  }

  high = num->digits + num->size - 1;
  for(d = high; d >= num->digits; --d) {
    digit = *d;
    strptr = strhexbuf + 2*sizeof(unsigned int);
    *strptr = '\0'; 
    while(digit != 0){
      --strptr;
      hex = digit%16;
      *strptr = (hex < 10 ? '0' + hex : 'a' + hex - 10);
      digit >>= 4;
    }
    if(d != high) {
      while(strptr > strhexbuf) {
        --strptr;
        *strptr = '0';
      }
    }
    printf("%s", strptr);
  }  
}

int ln_cmp(const long_num *f, const long_num *s) {
  // needs correction
  int res = 0;
  
  if(ln_sign(f) == ln_sign(s)) {
    res = (ln_sign(f) == 0) ? 0 : (ln_low_cmp(f, s) * ln_sign(f));
  } else {
    res ((ln_sign(f) == 1) || (ln_sign(s) == -1)) ? 1 : -1;
  }
  
  return res;
}

int ln_low_cmp(const long_num *f, const long_num *s) {
  // needs correction
  long_num *p
  unsigned int *f_d, *s_d, *d;
  unsigned int high;
  
  if(f->size != s->size) {
    p = (f->size > s->size) ? f : s;
    d = p->digits + p->size - 1;
    high = p->digits + MIN(f->size, s->size);
    
    while(d >= high) {
      if(*d) {
        return (p == f) ? 1 : -1;
      }
      --d;
    }
  }
  
  f_d = f->digits + MIN(f->size, s->size) - 1;
  s_d = s->digits + MIN(f->size, s->size) - 1;
  
  while(f_d >= f->digits) {
    if(*f_d != *s_d) {
	    return (*f_d > *s_d) ? 1 : -1;
	  }
	  --f_d;
	  --s_d;
  }
  
  return 0;
}

int ln_sign(const long_num* num) {
  // needs correction
  return (ISSET_NUM_FLG(num, FLG_ZERO) ? 0 : (ISSET_NUM_FLG(num, FLG_NEGATIVE) ? -1 : 1));
}
