#include <malloc.h>
#include <stdio.h>

#include "long_arithmetic.h"


long_num* ln_create(void) {
  // needs correction
  long_num *p;
  
  p = (long_num *)malloc(sizeof(long_num));
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
  
  p->size = (((len+1)>>1)+sizeof(unsigned int)-1)/sizeof(unsigned int);
  p->digits = malloc(p->size*sizeof(unsigned int));
  
  if(p->digits == NULL) {
    // no memory error
    free(p);
    return NULL;
  }
  
  high = p->digits+p->size-1;
  for(strptr = str+len-1, d = p->digits; d <= high; ++d) {
    digit = 0;
    for(i = 0; i < 8*sizeof(unsigned int) && strptr >= str; i += 4) {
      hex = *strptr-((*strptr >= '0' && *strptr <= '9') ? '0' : ('a'-10));
      digit = digit | (hex << i);
      --strptr;
    }
    *d = digit;
  }
  
  return p;
}

void ln_add(const long_num *f, const long_num *s, long_num *res) {
  // needs implementation
}
void ln_sub(const long_num *f, const long_num *s, long_num *res) {
  // needs implementation
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

void ln_print_hex(const long_num *num) {
  // needs correction
  unsigned int *d;
  register unsigned int digit;
  register unsigned int hex;
  
  char strhexbuf[2*sizeof(unsigned int)+1];
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
  
  for(d = &num->digits[num->size-1]; d >= num->digits; --d) {
    digit = *d;
    strptr = strhexbuf+2*sizeof(unsigned int);
    *strptr = '\0'; 
    while(digit != 0){
      --strptr;
      hex = digit%16;
      *strptr = (hex < 10 ? '0'+hex : 'a'+hex-10);
      digit >>= 4; 
    }
    printf("%s", strptr);
  }  
}

