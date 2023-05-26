#include <string>
#include "../include/aplicaciones.h"

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