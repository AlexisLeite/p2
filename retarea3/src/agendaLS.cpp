#include "../include/agendaLS.h"

struct rep_agendaLS
{
  TEvento evento;
  TAgendaLS sig;
};

TAgendaLS crearAgendaLS()
{
  TAgendaLS newAgenda = NULL;

  return newAgenda;
}

void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento)
{
  TAgendaLS newEntry = new rep_agendaLS;
  newEntry->evento = evento;
  newEntry->sig = NULL;

  if (agenda == NULL)
  {
    agenda = newEntry;
  }
  else
  {
    TFecha dateToAdd = fechaTEvento(evento);
    TAgendaLS ptr = agenda;
    TAgendaLS prev = NULL;
    /**
     * Iterando en la agenda
     * compararTFechas(fechaTEvento(fechaTEvento(ptr->evento)), dateToAdd)
     * Cuando esta expresión sea >= 0 debo hacer la inserción
     */

    while (ptr != NULL && compararTFechas(fechaTEvento(ptr->evento), dateToAdd) < 0)
    {
      prev = ptr;
      ptr = ptr->sig;
    }

    if (prev == NULL)
    {
      newEntry->sig = agenda;
      agenda = newEntry;
    }
    else
    {
      newEntry->sig = ptr;
      prev->sig = newEntry;
    }
  }
}

void imprimirAgendaLS(TAgendaLS agenda)
{
  if (agenda != NULL)
  {
    imprimirTEvento(agenda->evento);
    imprimirAgendaLS(agenda->sig);
  }
}

void liberarAgendaLS(TAgendaLS &agenda)
{
  if (agenda != NULL)
  {
    liberarAgendaLS(agenda->sig);
    liberarTEvento(agenda->evento);
    delete agenda;
    agenda = NULL;
  }
}

bool esVaciaAgendaLS(TAgendaLS agenda)
{
  return agenda == NULL;
}

TAgendaLS copiarAgendaLS(TAgendaLS agenda)
{
  if (agenda == NULL)
    return NULL;

  TAgendaLS newAgenda = new rep_agendaLS;
  newAgenda->evento = copiarTEvento(agenda->evento);
  newAgenda->sig = copiarAgendaLS(agenda->sig);

  return newAgenda;
}

bool estaEnAgendaLS(TAgendaLS agenda, int id)
{
  if (agenda == NULL)
    return false;

  if (idTEvento(agenda->evento) == id)
    return true;

  return estaEnAgendaLS(agenda->sig, id);
}

TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id)
{
  if (idTEvento(agenda->evento) == id)
    return agenda->evento;
  return obtenerDeAgendaLS(agenda->sig, id);
}

void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n)
{
  TAgendaLS prev = NULL;
  TAgendaLS ptr = agenda;

  while (idTEvento(ptr->evento) != id)
  {
    prev = ptr;
    ptr = ptr->sig;
  }

  if (prev == NULL)
  {
    agenda = agenda->sig;
  }
  else
  {
    prev->sig = ptr->sig;
  }

  posponerTEvento(ptr->evento, n);
  agregarEnAgendaLS(agenda, ptr->evento);
  delete ptr;
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha)
{
  if (agenda == NULL)
    return;

  int comparisson = compararTFechas(fechaTEvento(agenda->evento), fecha);

  if (comparisson == 0)
    imprimirTEvento(agenda->evento);
  if (comparisson <= 0)
    imprimirEventosFechaLS(agenda->sig, fecha);
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha)
{
  if (agenda == NULL)
    return false;

  int comparisson = compararTFechas(fechaTEvento(agenda->evento), fecha);

  if (comparisson == 0)
    return true;
  if (comparisson < 0)
    return hayEventosFechaLS(agenda->sig, fecha);

  return false;
}

void removerDeAgendaLS(TAgendaLS &agenda, int id)
{
  TAgendaLS prev = NULL;
  TAgendaLS ptr = agenda;

  while (idTEvento(ptr->evento) != id)
  {
    prev = ptr;
    ptr = ptr->sig;
  }

  if (prev == NULL)
  {
    agenda = agenda->sig;
  }
  else
  {
    prev->sig = ptr->sig;
  }

  liberarTEvento(ptr->evento);
  delete ptr;
}