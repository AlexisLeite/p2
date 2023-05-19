#include "../include/colaPersonasABB.h"
#include "../include/personasLDE.h"

struct rep_queueNode
{
  TPersonasABB tree;
  rep_queueNode *next;
};

typedef rep_queueNode *TQueueNode;

struct rep_colaPersonasABB
{
  TQueueNode first;
  TQueueNode last;
  nat length;
};

TColaPersonasABB crearTColaPersonasABB()
{
  TColaPersonasABB newQueue = new rep_colaPersonasABB;
  newQueue->first = newQueue->last = NULL;
  newQueue->length = 0;
  return newQueue;
}

void liberarTColaPersonasABBaux(TQueueNode node)
{
  if (node != NULL)
  {
    liberarTColaPersonasABBaux(node->next);
    delete node;
  }
}

void liberarTColaPersonasABB(TColaPersonasABB &c)
{
  liberarTColaPersonasABBaux(c->first);
  delete c;
  c = NULL;
}

nat cantidadEnTColaPersonasABB(TColaPersonasABB c)
{
  return c == NULL ? 0 : c->length;
}

void encolarEnTColaPersonasABB(TPersonasABB t, TColaPersonasABB &c)
{
  TQueueNode newNode = new rep_queueNode;
  newNode->next = NULL;
  newNode->tree = t;
  c->length++;

  if (c->last == NULL)
  {
    c->first = c->last = newNode;
  }
  else
  {
    c->last->next = newNode;
    c->last = newNode;
  }
}

TPersonasABB frenteDeTColaPersonasABB(TColaPersonasABB c)
{
  if (c == NULL || c->first == NULL)
  {
    return NULL;
  }
  return c->first->tree;
}

void desencolarDeTColaPersonasABB(TColaPersonasABB &c)
{
  if (c != NULL && c->first != NULL)
  {
    c->length--;
    TQueueNode aux = c->first;
    c->first = c->first->next;

    if (c->first == NULL)
      c->last = NULL;

    delete aux;
  }
}
