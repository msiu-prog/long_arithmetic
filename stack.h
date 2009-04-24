#ifndef _MSIU_PROG_STACK_H_
#define _MSIU_PROG_STACK_H_

#define STACK_LENGTH 256

#define STACK_INCREMENT 16

struct mp_stack {
  int size;      /* кол-во элементов в стеке */
  int head;      /* индекс головы стека */
  int alength;   /* длина массива указателей */
  void **array;  /* массив указателей */
};

struct mp_stack *mp_stack_create(int length);
void mp_stack_destroy(struct mp_stack *st);

int mp_stack_is_empty(struct mp_stack *st);
void mp_stack_clear(struct mp_stack *st);
void mp_stack_push(struct mp_stack *st, void *obj);
void *mp_stack_pop(struct mp_stack *st);
void *mp_stack_top(struct mp_stack *st);

int mp_stack_size(struct mp_stack *st);

#endif /* _MSIU_PROG_STACK_H_ */

