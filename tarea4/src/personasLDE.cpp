#include "../include/personasLDE.h"

typedef struct nodoDoble *Nodo;

struct nodoDoble
{
    TPersona persona;
    Nodo sig;
    Nodo ant;
};

struct rep_personasLDE
{
    Nodo inicio;
    Nodo final;
    nat *length;
};

TPersonasLDE crearTPersonasLDE()
{
    TPersonasLDE newList = new rep_personasLDE;

    newList->inicio = NULL;
    newList->final = NULL;
    newList->length = new nat;
    *newList->length = 0;

    return newList;
}

void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos)
{
    Nodo newNode = new nodoDoble;
    newNode->persona = persona;
    *personas->length += 1;

    if (personas->inicio == NULL)
    {
        personas->inicio = newNode;
        personas->final = newNode;
        newNode->ant = NULL;
        newNode->sig = NULL;
    }
    else
    {
        if (pos == 1)
        {
            newNode->sig = personas->inicio;
            newNode->ant = NULL;
            personas->inicio = newNode;
        }
        else if (*personas->length <= pos)
        {
            personas->final->sig = newNode;
            newNode->ant = personas->final;
            newNode->sig = NULL;
            personas->final = newNode;
        }
        else
        {
            nat i = 1;
            Nodo ptr = personas->inicio;
            while (i < pos)
            {
                i++;
                ptr = ptr->sig;
            }
            newNode->ant = ptr->ant;
            ptr->ant->sig = newNode;
            newNode->sig = ptr;
            ptr->ant = newNode;
        }
    }
}

void liberarNodes(Nodo ptr)
{
    if (ptr != NULL)
    {
        liberarNodes(ptr->sig);
        liberarTPersona(ptr->persona);
        delete ptr;
    }
}

void liberarTPersonasLDE(TPersonasLDE &personasLDE)
{
    if (personasLDE != NULL)
    {
        liberarNodes(personasLDE->inicio);
        delete personasLDE->length;
        delete personasLDE;
        personasLDE = NULL;
    }
}

void imprimirNodo(Nodo nodo)
{
    if (nodo != NULL)
    {
        imprimirTPersona(nodo->persona);
        imprimirNodo(nodo->sig);
    }
}

void imprimirTPersonasLDE(TPersonasLDE personas)
{
    imprimirNodo(personas->inicio);
}

nat cantidadTPersonasLDE(TPersonasLDE personas)
{
    return *personas->length;
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas)
{
    if (personas->inicio != NULL)
    {
        Nodo inicio = personas->inicio;
        personas->inicio = personas->inicio->sig;
        if (personas->inicio != NULL)
            personas->inicio->ant = NULL;

        *personas->length -= 1;
        if (*personas->length == 0)
            personas->final = NULL;

        liberarTPersona(inicio->persona);
        delete inicio;
    }
}

void eliminarFinalTPersonasLDE(TPersonasLDE &personas)
{
    if (personas->inicio != NULL)
    {
        Nodo final = personas->final;
        personas->final = personas->final->ant;
        if (personas->final != NULL)
            personas->final->sig = NULL;

        *personas->length -= 1;
        if (*personas->length == 0)
            personas->inicio = NULL;

        liberarTPersona(final->persona);
        delete final;
    }
}

bool estaEnNodo(Nodo nodo, nat id)
{
    if (nodo == NULL)
        return false;
    if (idTPersona(nodo->persona) == id)
        return true;
    return estaEnNodo(nodo->sig, id);
}

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id)
{
    return estaEnNodo(personas->inicio, id);
}

TPersona obtenerDeNodo(Nodo nodo, nat id)
{
    if (nodo == NULL)
        return NULL;
    if (idTPersona(nodo->persona) == id)
        return nodo->persona;
    return obtenerDeNodo(nodo->sig, id);
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id)
{
    return obtenerDeNodo(personas->inicio, id);
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2)
{
    TPersonasLDE newList = crearTPersonasLDE();

    if (*personas1->length > 0 && *personas2->length > 0)
    {
        newList->inicio = personas1->inicio;
        newList->final = personas2->final;
        *newList->length = *personas1->length + *personas2->length;

        personas1->final->sig = personas2->inicio;
        personas2->inicio->ant = personas1->final;
    }
    else if (*personas1->length > 0)
    {
        newList->inicio = personas1->inicio;
        newList->final = personas1->final;
        *newList->length = *personas1->length;
    }
    else if (*personas2->length > 0)
    {
        newList->inicio = personas2->inicio;
        newList->final = personas2->final;
        *newList->length = *personas2->length;
    }

    delete personas1->length;
    delete personas1;
    delete personas2->length;
    delete personas2;

    return newList;
}

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void insertarInicioDeTPersonasLDE(TPersonasLDE &personas, TPersona persona)
{
    insertarTPersonasLDE(personas, persona, 1);
}

void insertarFinalDeTPersonasLDE(TPersonasLDE &personas, TPersona persona)
{
    insertarTPersonasLDE(personas, persona, cantidadTPersonasLDE(personas) + 1);
}

TPersona obtenerInicioDeTPersonasLDE(TPersonasLDE personas)
{
    if (personas->inicio == NULL)
        return NULL;
    return personas->inicio->persona;
}

TPersona obtenerFinalDeTPersonasLDE(TPersonasLDE personas)
{
    if (personas->final == NULL)
        return NULL;
    return personas->final->persona;
}

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void eliminarPersonaConNombreTPersonasLDE(TPersonasLDE &personas, const char nombre[100])
{
    *personas->length = *personas->length - 1;
    Nodo it = personas->inicio;
    Nodo prev = NULL;

    while (0 != strcmp(nombreTPersona(it->persona), nombre))
    {
        prev = it;
        it = it->sig;
    }

    if (prev == NULL)
    {
        personas->inicio = it->sig;
    }
    else
    {
        prev->sig = it->sig;
    }

    if (it->sig == NULL)
    {
        personas->final = prev;
    }

    liberarTPersona(it->persona);
    delete it;
}

bool estaPersonaConNombreEnTPersonasLDE(TPersonasLDE personas, const char nombre[100])
{
    if (personas == NULL)
        return false;

    Nodo it = personas->inicio;

    while (it != NULL && 0 != strcmp(nombreTPersona(it->persona), nombre))
    {
        it = it->sig;
    }

    return it != NULL;
}

TPersona obtenerPersonaConNombreTPersonasLDE(TPersonasLDE personas, const char nombre[100])
{
    if (personas == NULL)
        return NULL;

    Nodo it = personas->inicio;

    while (it != NULL && 0 != strcmp(nombreTPersona(it->persona), nombre))
    {
        it = it->sig;
    }

    if (it == NULL)
        return NULL;

    return it->persona;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
