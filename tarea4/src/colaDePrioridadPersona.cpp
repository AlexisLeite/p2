#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct rep_colaDePrioridadPersona
{
  TPersona *data;
  bool isReverse;
  nat length;
  nat max;
  TPersona *people;
};

/**
 * Given two positions in the people array, returns true if the person in position a is higher in priority than person in position b
 */
bool isAHigherPriorityThanB(TColaDePrioridadPersona cp, nat a, nat b)
{
  int comparator = cp->isReverse ? 1 : -1;
  return compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->data[a])), fechaTEvento(primerEventoDeTPersona(cp->data[b]))) == comparator;
}

void iterateDown(nat i, TColaDePrioridadPersona &cp)
{
  bool isAHigherThanCurrent = cp->max > i * 2 && isAHigherPriorityThanB(cp, i * 2, i);
  bool isBHigherThanCurrent = cp->max > i * 2 + 1 && isAHigherPriorityThanB(cp, i * 2 + 1, i);

  if (isAHigherThanCurrent && isBHigherThanCurrent)
  {
    if (isAHigherPriorityThanB(cp, i * 2, i * 2 + 1))
    {
      isBHigherThanCurrent = false;
    }
    else
    {
      isAHigherThanCurrent = false;
    }
  }

  if (isAHigherThanCurrent)
  {
    TPersona swap = cp->data[i];
    cp->data[i] = cp->data[i * 2];
    cp->data[i * 2] = swap;
    iterateDown(i * 2, cp);
  }
  if (isBHigherThanCurrent)
  {
    TPersona swap = cp->data[i];
    cp->data[i] = cp->data[i * 2 + 1];
    cp->data[i * 2 + 1] = swap;
    iterateDown(i * 2 + 1, cp);
  }
}

void iterateUp(nat n, TColaDePrioridadPersona &cp)
{
  if (n > 1)
  {
    if (isAHigherPriorityThanB(cp, n, n / 2))
    {
      TPersona swap = cp->data[n];
      cp->data[n] = cp->data[n / 2];
      cp->data[n / 2] = swap;

      iterateUp(n / 2, cp);
    }
  }
}

TColaDePrioridadPersona crearCP(nat N)
{
  TColaDePrioridadPersona newCp = new rep_colaDePrioridadPersona;

  // Arrays inicialization
  newCp->data = new TPersona[N + 1];
  newCp->people = new TPersona[N + 1];
  for (nat i = 0; i <= N; i++)
    newCp->people[i] = NULL;

  // Other data
  newCp->isReverse = false;
  newCp->length = N + 1;
  newCp->max = 1;

  return newCp;
}

void invertirPrioridad(TColaDePrioridadPersona &cp)
{
  cp->isReverse = !cp->isReverse;
  for (nat i = cp->max - 1; i >= 1; i--)
  {
    iterateUp(i, cp);
  }
}

void liberarCP(TColaDePrioridadPersona &cp)
{
  for (nat i = 1; i < cp->max; i++)
    liberarTPersona(cp->data[i]);
  delete[] cp->data;
  delete[] cp->people;
  delete cp;
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp)
{
  cp->data[cp->max] = persona;
  cp->people[idTPersona(persona)] = persona;
  iterateUp(cp->max, cp);
  cp->max++;
}

bool estaVaciaCP(TColaDePrioridadPersona cp)
{
  return cp->max == 1;
}

TPersona prioritaria(TColaDePrioridadPersona cp)
{
  return cp->data[1];
}

TFecha obtenerFechaPrioridad(TPersona persona)
{
  return fechaTEvento(primerEventoDeTPersona(persona));
}

void eliminarPrioritaria(TColaDePrioridadPersona &cp)
{
  if (cp->max > 1)
  {
    cp->people[idTPersona(cp->data[1])] = NULL;
    liberarTPersona(cp->data[1]);
    cp->data[1] = NULL;
    cp->data[1] = cp->data[--cp->max];

    if (cp->max > 2)
    {
      iterateDown(1, cp);
    }
  }
}

bool estaEnCP(nat id, TColaDePrioridadPersona cp)
{
  return cp->people[id] != NULL;
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp)
{
  return fechaTEvento(primerEventoDeTPersona(cp->people[id]));
}