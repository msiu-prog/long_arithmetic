#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "long_arithmetic.h"
#include "stack.h"


#define EXITCMD 'q'

#define ADDCMD '+'
#define SUBCMD '-'
#define MULTCMD '*'
#define DIVCMD '/'
#define MODCMD '%'

#define TOPCMD 't'
#define POPCMD 'p'

#define SPLITCMD1 ' '
#define SPLITCMD2 '\n'
#define SPLITCMD3 '\t'


#define NUMLEN 128
#define NUMINCR 16

struct mp_stack *stack; /* стек вычислений */

char *number_str; /* текущая строка с числом */
int number_size; /* кол-во символов в строке являющихся числом */
int number_length; /* длинна массива <number_str> */

void init_calc() {
  stack = mp_stack_create(0);
  number_str = (char *)malloc(NUMLEN*sizeof(char));
  if(stack == NULL || number_str == NULL) {
    printf("Error: no memory\n");
    exit(1);
  }
  number_size = 0;
  number_length = NUMLEN;
}

void concatenate_char_to_number(char c) {
  if(number_size+1 == number_length) {
    number_str = (char *)realloc(number_str, (number_length+NUMINCR)*sizeof(char));
    number_length += NUMINCR;
    if(number_str == NULL) {
      printf("ERROR: no memory\n");
      exit(1);
    }
  }
  
  number_str[number_size] = c;
  number_size += 1;
  number_str[number_size] = '\0';
}

void clear_number() {
  number_size = 0;
  number_str[0] = '\0';
}

void calc_add(void) {
  struct long_num *first, *second, *res;
  // printf("add\n");
  second = mp_stack_pop(stack);
  first = mp_stack_pop(stack);
  res = ln_create();
  if(first == NULL || second == NULL || res == NULL) {
    printf("Error : missing numbers\n");
    exit(1);
  }
  ln_add(first, second, res);
  mp_stack_push(stack, res);
  ln_destroy(first);
  ln_destroy(second);
}

void calc_sub(void) {
  struct long_num *first, *second, *res;
  // printf("sub");
  second = mp_stack_pop(stack);
  first = mp_stack_pop(stack);
  res = ln_create();
  if(first == NULL || second == NULL || res == NULL) {
    printf("Error : missing numbers\n");
    exit(1);
  }
  ln_sub(first, second, res);
  mp_stack_push(stack, res);
  ln_destroy(first);
  ln_destroy(second);
}

void calc_mult(void) {
  struct long_num *first, *second, *res;
  // printf("mult\n");
  second = mp_stack_pop(stack);
  first = mp_stack_pop(stack);
  res = ln_create();
  if(first == NULL || second == NULL || res == NULL) {
    printf("Error : missing numbers\n");
    exit(1);
  }
  ln_mult(first, second, res);
  mp_stack_push(stack, res);
  ln_destroy(first);
  ln_destroy(second);
}

void calc_div(void) {
  struct long_num *first, *second, *res;
  // printf("div\n");
  second = mp_stack_pop(stack);
  first = mp_stack_pop(stack);
  res = ln_create();
  if(first == NULL || second == NULL || res == NULL) {
    printf("Error : missing numbers\n");
    exit(1);
  }
  ln_div(first, second, res);
  mp_stack_push(stack, res);
  ln_destroy(first);
  ln_destroy(second);
}

void calc_mod(void) {
  struct long_num *first, *second, *res;
  // printf("mod\n");
  second = mp_stack_pop(stack);
  first = mp_stack_pop(stack);
  res = ln_create();
  if(first == NULL || second == NULL || res == NULL) {
    printf("Error : missing numbers\n");
    exit(1);
  }
  ln_mod(first, second, res);
  mp_stack_push(stack, res);
  ln_destroy(first);
  ln_destroy(second);
}

void calc_top(void) {
  // printf("top\n");
  struct long_num *p = mp_stack_top(stack);
  if(p != NULL){
    ln_print_hex(p);
  }
  printf("\n");
}

void calc_pop(void) {
  // printf("pop\n");
  struct long_num *p = mp_stack_pop(stack);
  if(p != NULL) {
    ln_print_hex(p);
  }
  printf("\n");
}

void calc_push(void) {
  // printf("push\n");
  struct long_num *p;
  if(number_size != 0) {
    p = ln_create_from_hex_string(number_str, number_size);
    mp_stack_push(stack, p);
    clear_number();
  }
}

void other_char(int c) {
  c = tolower(c);
  if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')) {
    // printf("concatenate\n");
    concatenate_char_to_number((char)c);
  } else {
    // printf("other character\n");
  }
}

int main(int argc, char *argv[]) {
  int retval = 0;

  init_calc();
  
  while(1) {
    retval = getchar();
    
    if(retval == EOF) {
      printf("End of stream\n");
      exit(0);
    }
    
    switch((char)retval) {
      case EXITCMD :
        // printf("exit\n");
        exit(0);
        break;
      case ADDCMD :
        calc_add();
        break;
      case SUBCMD :
        calc_sub();
        break;
      case MULTCMD :
        calc_mult();
        break;
      case DIVCMD :
        calc_div();
        break;
      case MODCMD :
        calc_mod();
        break;
      case TOPCMD :
        calc_top();
        break;
      case POPCMD : 
        calc_pop();
        break;
      case SPLITCMD1 :
      case SPLITCMD2 :
      case SPLITCMD3 :
        // printf("split character\n");
        calc_push();
        break;
      default :
        other_char((char)retval);
    }
  }
  
  return 0;
}

