#include "../include/pilaPersona.h"
#include "../include/personasLDE.h"

struct rep_pilaNodo
{
  TPersona person;
  rep_pilaNodo *next;
};

struct rep_pilaPersona
{
  rep_pilaNodo *first;
  nat length;
};

TPilaPersona crearTPilaPersona()
{
  TPilaPersona newStack = new rep_pilaPersona;

  newStack->first = NULL;
  newStack->length = 0;

  return newStack;
}

void liberarTPilaPersonaAux(rep_pilaNodo *node)
{
  if (node != NULL)
  {
    liberarTPilaPersonaAux(node->next);
    liberarTPersona(node->person);
    delete node;
  }
}

void liberarTPilaPersona(TPilaPersona &p)
{
  liberarTPilaPersonaAux(p->first);

  delete p;
}

nat cantidadEnTPilaPersona(TPilaPersona p)
{
  if (p == NULL)
    return 0;
  return p->length;
}

void apilarEnTPilaPersona(TPilaPersona &p, TPersona persona)
{
  if (persona != NULL)
  {
    rep_pilaNodo *newNode = new rep_pilaNodo;
    newNode->person = copiarTPersona(persona);
    newNode->next = p->first;
    p->length++;
    p->first = newNode;
  }
}

TPersona cimaDeTPilaPersona(TPilaPersona p)
{
  if (p == NULL)
    return NULL;
  return p->first->person;
}

void desapilarDeTPilaPersona(TPilaPersona &p)
{
  if (p != NULL)
  {
    rep_pilaNodo *firstNode = p->first;

    if (p->first != NULL)
      p->first = p->first->next;
    p->length--;

    liberarTPersona(firstNode->person);
    delete firstNode;
  }
}
