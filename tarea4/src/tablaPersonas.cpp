#include "../include/tablaPersonas.h"

struct rep_tablaPersonas
{
    int max;
    TPersonasLDE *list;
};

nat funcionDeDispersion(const char nombre[100])
{
    nat res = 0;
    int i = 0;
    while (i < 100 && nombre[i] != '\0')
    {
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaPersonas crearTTablaPersonas(int max)
{
    TTablaPersonas newTable = new rep_tablaPersonas;
    newTable->max = max;
    newTable->list = new TPersonasLDE[max];

    for (int i = 0; i < max; i++)
        newTable->list[i] = NULL;

    return newTable;
}

void insertarPersonaEnTabla(TTablaPersonas &tabla, TPersona persona)
{
    nat hash = funcionDeDispersion(nombreTPersona(persona));
    if (tabla->list[hash % tabla->max] == NULL)
    {
        tabla->list[hash % tabla->max] = crearTPersonasLDE();
    }

    insertarTPersonasLDE(tabla->list[hash % tabla->max], persona, 1);
}

void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100])
{
    nat hash = funcionDeDispersion(nombre);

    eliminarPersonaConNombreTPersonasLDE(tabla->list[hash % tabla->max], nombre);
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100])
{
    nat hash = funcionDeDispersion(nombre);

    return estaPersonaConNombreEnTPersonasLDE(tabla->list[hash % tabla->max], nombre);
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100])
{
    nat hash = funcionDeDispersion(nombre);

    return obtenerPersonaConNombreTPersonasLDE(tabla->list[hash % tabla->max], nombre);
}

void liberarTTablaPersonas(TTablaPersonas &tabla)
{
    if (tabla != NULL)
    {
        for (int i = 0; i < tabla->max; i++)
        {
            liberarTPersonasLDE(tabla->list[i]);
        }

        delete[] tabla->list;
        delete tabla;
        tabla = NULL;
    }
}

void imprimirTTablaPersonas(TTablaPersonas tabla)
{
    for (int i = 0; i < tabla->max; i++)
    {
        if (tabla->list[i] != NULL)
            imprimirTPersonasLDE(tabla->list[i]);
    }
}