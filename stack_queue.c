#include <stdio.h>
#include <stdlib.h>

#define _pcal(x, type, size) x = (type*) calloc(size, sizeof(type))
#define _cmax2(a, b) (a > b) ? a : b
#define _cmax3(a, b, c) (a > b) ? (a > c) ? a : c : (b > c) ? b : c
#define _cmin2(a, b) (a < b) ? a : b
#define _cmin3(a, b, c) (a < b) ? (a < c) ? a : c : (b < c) ? b : c

#define _sett(x, dat, nex) x->_Tdata = dat; x->next = nex

#define _Ttype int
#define _Tdata data

typedef struct _q
{
  _Ttype _Tdata;
  struct _q *next;
}_Tnode;

typedef _Tnode node;

void enqueue(_Tnode **q, _Ttype _Tdata)
{
  _Tnode *new, *curr;
  _pcal(new, _Tnode, 1);
  _sett(new, _Tdata, 0);
  if(!*q)
    {
      *q = new;
      return;
    }
  for(curr = *q; curr->next; curr = curr->next);
  curr->next = new;
}

int dequeue(_Tnode **q)
{
  _Tnode *tmp;
  _Ttype _Tdata;
  _Tdata = (tmp = *q)->_Tdata;
  *q = tmp->next;
  free(tmp);
  return _Tdata;
}

void push(_Tnode **s, _Ttype _Tdata)
{
  _Tnode *new;
  _pcal(new, _Tnode, 1);
  _sett(new, _Tdata, 0);
  new->next = (*s)->next;
  (*s)->next = new;
}

_Ttype pop(_Tnode **s)
{
  _Tnode *tmp;
  _Ttype _Tdata;
  _Tdata = (tmp = *s)->_Tdata;
  *s = tmp->next;
  free(tmp);
  return _Tdata;
}
