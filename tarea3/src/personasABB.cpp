#include <limits.h>
#include <cmath>
#include "../include/personasABB.h"

struct rep_personasAbb
{
  TPersona persona;
  TPersonasABB left, right;
};

TPersonasABB crearTPersonasABB()
{
  return NULL;
}

bool esVacioTPersonasABB(TPersonasABB personasABB)
{
  return personasABB == NULL;
}

void insertarTPersonasABB(TPersonasABB &personasABB, TPersona p)
{
  if (personasABB == NULL)
  {
    TPersonasABB newNode = new rep_personasAbb;
    newNode->persona = p;
    newNode->left = newNode->right = NULL;
    personasABB = newNode;
  }
  else
  {
    if (idTPersona(p) < idTPersona(personasABB->persona))
    {
      insertarTPersonasABB(personasABB->left, p);
    }
    else
    {
      insertarTPersonasABB(personasABB->right, p);
    }
  }
}

void liberarTPersonasABB(TPersonasABB &personasABB)
{
  if (personasABB != NULL)
  {
    liberarTPersonasABB(personasABB->left);
    liberarTPersonasABB(personasABB->right);
    liberarTPersona(personasABB->persona);
    delete personasABB;
  }
}

void imprimirTPersonasABB(TPersonasABB personasABB)
{
  if (personasABB != NULL)
  {
    imprimirTPersonasABB(personasABB->left);
    imprimirTPersona(personasABB->persona);
    imprimirTPersonasABB(personasABB->right);
  }
}

nat cantidadTPersonasABB(TPersonasABB personasABB)
{
  if (personasABB == NULL)
    return 0;
  return 1 + cantidadTPersonasABB(personasABB->left) + cantidadTPersonasABB(personasABB->right);
}

TPersona maxIdPersona(TPersonasABB personasABB)
{
  if (personasABB->right != NULL)
    return maxIdPersona(personasABB->right);
  return personasABB->persona;
}

void removerTPersonasABB(TPersonasABB &personasABB, nat id)
{
  if (idTPersona(personasABB->persona) > id)
    removerTPersonasABB(personasABB->left, id);
  else if (idTPersona(personasABB->persona) < id)
    removerTPersonasABB(personasABB->right, id);
  else
  {
    liberarTPersona(personasABB->persona);

    if (personasABB->left == NULL)
    {
      TPersonasABB aBorrar = personasABB;
      personasABB = personasABB->right;
      delete aBorrar;
    }
    else if (personasABB->right == NULL)
    {
      TPersonasABB aBorrar = personasABB;
      personasABB = personasABB->left;
      delete aBorrar;
    }
    else
    {
      TPersona max = copiarTPersona(maxIdPersona(personasABB->left));
      removerTPersonasABB(personasABB->left, idTPersona(max));
      personasABB->persona = max;
    }
  }
}

void printTab(int size)
{
  for (int i = 0; i < size; i++)
  {
    printf(" ");
  }
}

void imprimirArbol(TPersonasABB a, int tab)
{
  if (a == NULL)
    return;

  printTab(tab);
  printf("Nodo actual: %s, edad: %d\n", nombreTPersona(a->persona), edadTPersona(a->persona));
  printTab(tab);
  printf("{\n");
  printTab(tab);
  printf("  left: \n");
  imprimirArbol(a->left, tab + 4);
  printTab(tab);
  printf("  right: \n");
  imprimirArbol(a->right, tab + 4);
  printTab(tab);
  printf("},\n");
}

bool estaTPersonasABB(TPersonasABB personasABB, nat id)
{
  if (personasABB == NULL)
    return false;
  if (idTPersona(personasABB->persona) == id)
    return true;
  if (idTPersona(personasABB->persona) < id)
    return estaTPersonasABB(personasABB->right, id);
  return estaTPersonasABB(personasABB->left, id);
}

TPersona obtenerDeTPersonasABB(TPersonasABB personasABB, nat id)
{
  if (idTPersona(personasABB->persona) == id)
    return personasABB->persona;
  if (idTPersona(personasABB->persona) < id)
    return obtenerDeTPersonasABB(personasABB->right, id);
  return obtenerDeTPersonasABB(personasABB->left, id);
}

nat alturaTPersonasABB(TPersonasABB personasABB)
{
  if (personasABB == NULL)
    return 0;
  nat leftHeight = alturaTPersonasABB(personasABB->left);
  nat rightHeight = alturaTPersonasABB(personasABB->right);

  if (leftHeight > rightHeight)
    return 1 + leftHeight;
  return 1 + rightHeight;
}

bool esPerfectoTPersonasABB(TPersonasABB personasABB)
{
  if (personasABB == NULL)
  {
    return true;
  }

  nat height = alturaTPersonasABB(personasABB);
  double formula = pow(2, height) - 1;
  bool result = cantidadTPersonasABB(personasABB) == formula;

  return result;
}

TPersonasABB copiarTree(TPersonasABB a)
{
  if (a == NULL)
    return NULL;

  TPersonasABB newTree = new rep_personasAbb;
  newTree->persona = copiarTPersona(a->persona);
  newTree->left = copiarTree(a->left);
  newTree->right = copiarTree(a->right);

  return newTree;
}

TPersonasABB mayoresTPersonasABB(TPersonasABB personasABB, nat edad)
{
  if (personasABB == NULL)
    return NULL;

  if (edadTPersona(personasABB->persona) >= edad)
  {
    TPersonasABB newTree = new rep_personasAbb;
    newTree->persona = copiarTPersona(personasABB->persona);
    if (edadTPersona(personasABB->persona) > edad)
    {
      newTree->left = mayoresTPersonasABB(personasABB->left, edad);
    }
    else
      newTree->left = NULL;
    newTree->right = copiarTree(personasABB->right);
    return newTree;
  }
  else
    return mayoresTPersonasABB(personasABB->right, edad);
}

void makeList(TPersonasABB t, TPersonasLDE &list)
{
  if (t == NULL)
    return;

  makeList(t->left, list);

  insertarTPersonasLDE(list, copiarTPersona(t->persona), UINT_MAX);

  makeList(t->right, list);
}

TPersonasLDE aTPersonasLDE(TPersonasABB personasABB)
{
  TPersonasLDE newList = crearTPersonasLDE();
  makeList(personasABB, newList);
  return newList;
}


///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

nat amplitudTPersonasABB(TPersonasABB personasABB) {
    return 0;
}

TPilaPersona serializarTPersonasABB(TPersonasABB personasABB) {
    return NULL;
}

TPersonasABB deserializarTPersonasABB(TPilaPersona &pilaPersonas) {
    return NULL;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

