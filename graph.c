#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define _pcal(x, type, size) x = (type*) calloc(size, sizeof(type))
#define _cmax2(a, b) (a > b) ? a : b
#define _cmax3(a, b, c) (a > b) ? (a > c) ? a : c : (b > c) ? b : c
#define _cmin2(a, b) (a < b) ? a : b
#define _cmin3(a, b, c) (a < b) ? (a < c) ? a : c : (b < c) ? b : c

#define _sett(x, dat, nex) x->_Tdata = dat; x->next = nex

#define _Ttype int
#define _Tdata vertex

typedef struct _list
{
  _Ttype _Tdata;
  struct _list *next;
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

_Ttype dequeue(_Tnode **q)
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

typedef struct
{
  int level;
  int visited;
  node *list;
}graph;

void bfs(graph *g, int rootver)
{
  node *queue = 0, *neigh;
  int v, neighv;
  g[rootver].visited = 1;
  g[rootver].level = 0;
  enqueue(&queue, rootver);
  for(; queue; )
    {
      v = dequeue(&queue);
      for(neigh = g[v].list; neigh; neigh = neigh->next)
        {
          if(g[neighv = neigh->vertex].visited)
            continue;
          g[neighv].level = g[v].level + 1;
          g[neighv].visited = 1;
          enqueue(&queue, neighv);
        }
    }
}
void dfs(graph *g, int rootver, int dist)
{
  node *curr;
  g[rootver].visited = 1;
  g[rootver].level = dist;
  printf("--%d-- ", rootver);
  for(curr = g[rootver].list; curr; curr = curr->next)
    {
      if(!g[curr->vertex].visited)
        {
          dfs(g, curr->vertex, dist + 1);
        }
    }
}
int main(int argc, char *argv[])
{
  int i, st, fl, vertices, edges;
  graph *gr1, *gr2;
  node *new;
  scanf("%d %d", &vertices, &edges);
  _pcal(gr1, graph, vertices);
  _pcal(gr2, graph, vertices);
  for(i = 0; i < vertices; i++)
    {
      gr1[i].visited = 0;
      gr1[i].level = INT_MAX;
      gr1[i].list = 0;
      gr2[i].visited = 0;
      gr2[i].level = INT_MAX;
      gr2[i].list = 0;
    }
  for(i = 0; i < edges; i++)
    {
      scanf("%d %d", &st, &fl);
      enqueue(&(gr1[st].list), fl);
      enqueue(&(gr1[fl].list), st);
      enqueue(&(gr2[st].list), fl);
      enqueue(&(gr2[fl].list), st);
    }
  for(i = 0; i < vertices; i++)
    {
      printf("%d : ", i);
      for(new = gr1[i].list; new; new = new->next)
        printf("%d --> ", new->vertex);
      printf("NULL\n");
    }
  bfs(gr1, 0);
  dfs(gr2, 0, 0);
  printf("\n");
  for(i = 0; i < vertices; i++)
    {
      printf("%d : %d\n", i, gr1[i].level);
    }
  for(i = 0; i < vertices; i++)
    {
      printf("%d : %d\n", i, gr2[i].level);
    }
  return 0;
}
