#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadPersona.h"

void listarEnOrden(TTablaPersonas t, char **nombres, nat n)
{
  TColaDePrioridadPersona aux = crearCP(n);
  for (nat i = 0; i < n; i++)
  {
    TPersona current = obtenerPersonaDeTTablaPersonas(t, nombres[i]);
    if (current != NULL)
      insertarEnCP(current, aux);
  }

  TPersona aux2;
  while ((aux2 = prioritaria(aux)) != NULL)
  {
    imprimirTPersona(aux2);
    eliminarPrioritaria(aux);
  }

  liberarCP(aux);
}