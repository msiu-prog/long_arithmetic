#include <malloc.h>

#include "stack.h"

struct mp_stack *mp_stack_create(int length) {
  struct mp_stack *st;

  st = (struct mp_stack *)malloc(sizeof(struct mp_stack));
  if(st == NULL) {
    // no memory error
    return NULL;
  }

  st->array = NULL;
  st->alength = 0;
  st->size = 0;
  st->head = (-1);

  return st;
}

void mp_stack_destroy(struct mp_stack *st) {
  if(st != NULL) {
    if(st->array != NULL){
      free(st->array);
      // st->alength = 0;
      // st->size = 0;
      // st->head = (-1);
    }
    free(st);
  }
}

void mp_stack_initialize(struct mp_stack *st) {
  if(st != NULL) {
    st->array = NULL;
    st->alength = 0;
    st->size = 0;
    st->head = (-1);
  }
}

int mp_stack_is_empty(struct mp_stack *st) {
  if(st != NULL) {
    return (st->size == 0);
  }
  return 1;
}

void mp_stack_clear(struct mp_stack *st) {
  if(st != NULL) {
    st->size = 0;
    st->head = (-1);
    st->array = realloc(st->array, STACK_LENGTH*sizeof(void *));
  }
}

void mp_stack_push(struct mp_stack *st, void *obj) {
  if(st != NULL) {
    if(st->size == st->alength){
      st->array = realloc(st->array, 
                          (st->alength+STACK_INCREMENT)*sizeof(void *));
      if(st->array == NULL) {
        // no memory error
      }
    }
    st->array[st->head+1] = obj;
    st->head += 1;
  } else {
    // must generate some error
  }
}

void *mp_stack_pop(struct mp_stack *st) {
  if(st != NULL && st->size != 0) {
    st->size -= 1;
    st->head -= 1;
    return (st->array)[st->head+1];
  }
  return NULL;
}

void *mp_stack_top(struct mp_stack *st) {
  if(st != NULL && st->size != 0) {
    return (st->array)[st->head];
  }
  return NULL;
}

int mp_stack_size(struct mp_stack *st) {
  if(st != NULL) {
    return st->size;
  }
  return 0;
}


