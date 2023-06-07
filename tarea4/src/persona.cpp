#include "../include/persona.h"
#include "../include/utils.h"
#include <string.h>

struct rep_persona
{
    nat id;
    nat edad;
    char nombre[MAX_DESCRIPCION];
    TAgendaLS agenda;
};

TPersona crearTPersona(nat id, nat edad, const char nombre[100], TAgendaLS agenda)
{
    TPersona newPerson = new rep_persona;
    newPerson->agenda = agenda;
    newPerson->edad = edad;
    newPerson->id = id;
    strcpy(newPerson->nombre, nombre);
    return newPerson;
}

void liberarTPersona(TPersona &persona)
{
    liberarAgendaLS(persona->agenda);
    delete persona;
}

// Imprime a la persona utilizando printf e imprimeAgendaLS
void imprimirTPersona(TPersona persona)
{
    printf("Persona %d: %s, %d años\n", persona->id, persona->nombre, persona->edad);
    imprimirAgendaLS(persona->agenda);
}

nat idTPersona(TPersona persona)
{
    return persona->id;
}

nat edadTPersona(TPersona persona)
{
    return persona->edad;
}

char *nombreTPersona(TPersona persona)
{
    return persona->nombre;
}

TAgendaLS agendaTPersona(TPersona persona)
{
    return persona->agenda;
}

void agregarEventoATPersona(TPersona &persona, TEvento evento)
{
    agregarEnAgendaLS(persona->agenda, evento);
}

void posponerEventoEnTPersona(TPersona &persona, int id, nat n)
{
    posponerEnAgendaLS(persona->agenda, id, n);
}

void removerEventoDeTPersona(TPersona &persona, int id)
{
    removerDeAgendaLS(persona->agenda, id);
}

bool estaEnAgendaDeTPersona(TPersona persona, int id)
{
    return estaEnAgendaLS(persona->agenda, id);
}

TEvento obtenerDeAgendaDeTPersona(TPersona persona, int id)
{
    return obtenerDeAgendaLS(persona->agenda, id);
}

TPersona copiarTPersona(TPersona persona)
{
    TPersona newPerson = new rep_persona;
    strcpy(newPerson->nombre, persona->nombre);
    newPerson->id = persona->id;
    newPerson->edad = persona->edad;
    newPerson->agenda = copiarAgendaLS(persona->agenda);

    return newPerson;
}

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

TEvento primerEventoDeTPersona(TPersona persona)
{
    return primerEventoAgendaLS(agendaTPersona(persona));
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
