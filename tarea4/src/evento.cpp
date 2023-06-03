#include "../include/evento.h"
#include "../include/utils.h"
#include <string.h>

struct rep_evento
{
    /************ Parte 4.1 ************/
    /*Escriba el código a continuación */
    int id;
    char descripcion[MAX_DESCRIPCION];
    TFecha fecha;

    /****** Fin de parte Parte 4.1 *****/
};

TEvento crearTEvento(int id, const char descripcion[MAX_DESCRIPCION], TFecha fecha)
{
    TEvento nuevoEvento = NULL;
    /************ Parte 4.2 ************/
    nuevoEvento = new rep_evento;
    nuevoEvento->id = id;
    strcpy(nuevoEvento->descripcion, descripcion);
    nuevoEvento->fecha = fecha;

    /****** Fin de parte Parte 4.2 *****/
    return nuevoEvento;
}

void imprimirTEvento(TEvento evento)
{
    /************ Parte 4.3 ************/
    /*Escriba el código a continuación */
    printf("Evento %d: %s\nFecha: ", evento->id, evento->descripcion);
    imprimirTFecha(evento->fecha);

    /****** Fin de parte Parte 4.3 *****/
}

void liberarTEvento(TEvento &evento)
{
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    liberarTFecha(evento->fecha);

    delete evento;
    evento = NULL;

    /****** Fin de parte Parte 4.4 *****/
}

int idTEvento(TEvento evento)
{
    int res = 0;
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    if (evento != NULL)
        res = evento->id;

    /****** Fin de parte Parte 4.4 *****/
    return res;
}

TFecha fechaTEvento(TEvento evento)
{
    TFecha fecha = NULL;
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */

    if (evento != NULL)
        fecha = evento->fecha;

    /****** Fin de parte Parte 4.4 *****/
    return fecha;
}

void posponerTEvento(TEvento &evento, int dias)
{
    /************ Parte 4.5 ************/
    /*Escriba el código a continuación */
    if (evento != NULL)
        aumentarTFecha(evento->fecha, dias);

    /****** Fin de parte Parte 4.5 *****/
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 1 //////
/////////////////////////////////

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia del evento
TEvento copiarTEvento(TEvento evento)
{
    if (evento == NULL)
        return NULL;

    TEvento newEvent = new rep_evento;
    strcpy(newEvent->descripcion, evento->descripcion);
    newEvent->fecha = copiarTFecha(evento->fecha);
    newEvent->id = evento->id;
    return newEvent;
}
