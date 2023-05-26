#include <string>
#include "../include/aplicaciones.h"

/*
TPersonasLDE crearTPersonasLDE();
void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos);
void liberarTPersonasLDE(TPersonasLDE &personas);
void imprimirTPersonasLDE(TPersonasLDE personas);
nat cantidadTPersonasLDE(TPersonasLDE personas);
void eliminarInicioTPersonasLDE(TPersonasLDE &personas);
void eliminarFinalTPersonasLDE(TPersonasLDE &personas);
bool estaEnTPersonasLDE(TPersonasLDE personas, nat id);
TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id);
TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2);

void insertarInicioDeTPersonasLDE(TPersonasLDE &personas, TPersona persona);
void insertarFinalDeTPersonasLDE(TPersonasLDE &personas, TPersona persona);
TPersona obtenerInicioDeTPersonasLDE(TPersonasLDE personas);
TPersona obtenerFinalDeTPersonasLDE(TPersonasLDE personas);
*/

TPilaPersona menoresQueElResto(TPersonasLDE lista)
{
  if (lista == NULL)
    return NULL;

  TPersona aux, aux2;
  TPilaPersona result = crearTPilaPersona();

  while ((aux = obtenerInicioDeTPersonasLDE(lista)) != NULL)
  {
    while ((aux2 = cimaDeTPilaPersona(result)) != NULL && edadTPersona(aux) < edadTPersona(aux2))
    {
      desapilarDeTPilaPersona(result);
    }

    apilarEnTPilaPersona(result, aux);
    eliminarInicioTPersonasLDE(lista);
  }

  return result;
}

bool sumaPares(nat k, TConjuntoIds c)
{
  nat n = cantMaxTConjuntoIds(c);
  TConjuntoIds wishes = crearTConjuntoIds(n);
  int dif = k - cantMaxTConjuntoIds(c);

  for (nat i = 1; i <= n; i++)
  {
    if (perteneceTConjuntoIds(i, c))
    {
      if (perteneceTConjuntoIds(i - dif, wishes))
      {
        liberarTConjuntoIds(wishes);
        return true;
      }
      insertarTConjuntoIds(k - i - dif, wishes);
    }
  }

  liberarTConjuntoIds(wishes);
  return false;
}