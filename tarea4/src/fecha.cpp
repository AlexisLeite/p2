#include "../include/fecha.h"

struct rep_fecha
{
    /************ Parte 2.1 ************/
    nat dia, mes, anio;

    /****** Fin de parte Parte 2.1 *****/
};

TFecha crearTFecha(nat dia, nat mes, nat anio)
{
    TFecha nuevaFecha = NULL;
    /************ Parte 3.1 ************/
    nuevaFecha = new rep_fecha;
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;

    /****** Fin de parte Parte 3.1 *****/
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha)
{
    /************ Parte 3.3 ************/
    delete fecha;
    fecha = NULL;

    /****** Fin de parte Parte 3.3 *****/
}
void imprimirTFecha(TFecha fecha)
{
    /************ Parte 3.5 ************/
    printf("%d/%d/%d\n", fecha->dia, fecha->mes, fecha->anio);

    /****** Fin de parte Parte 3.5 *****/
}

/************ Parte 3.9 ************/
/*Escriba el código a continuación */
/*Recuerde que las funciones auxiliares
  deben declararse antes de ser utilizadas*/

bool esBisiesto(nat anio)
{
    return (anio % 400 == 0) || (anio % 100 != 0 && anio % 4 == 0);
}

nat diasMes(nat mes, nat anio)
{
    // Febrero se trata aparte por bisiesto
    if (mes == 2)
    {
        if (esBisiesto(anio))
            return 29;
        else
            return 28;
    }

    // Desde enero a julio los meses impares tienen 31
    if (mes <= 7)
    {
        if (mes % 2 == 1)
            return 31;
        return 30;
    }

    // Desde agosto a diciembre los meses impares tienen 30
    if (mes % 2 == 0)
        return 31;
    return 30;
}

void aumentarTFecha(TFecha &fecha, nat dias)
{
    fecha->dia += dias;

    while (fecha->dia > diasMes(fecha->mes, fecha->anio))
    {
        fecha->dia -= diasMes(fecha->mes, fecha->anio);
        fecha->mes++;

        if (fecha->mes > 12)
        {
            fecha->mes = 1;
            fecha->anio++;
        }
    }
}

int compararTFechas(TFecha fecha1, TFecha fecha2)
{
    int res = 0;
    /************ Parte 3.10 ************/
    /*Escriba el código a continuación */

    // Comparación de años
    if (fecha1->anio > fecha2->anio)
        return 1;
    if (fecha1->anio < fecha2->anio)
        return -1;

    // Comparación de meses
    if (fecha1->mes > fecha2->mes)
        return 1;
    if (fecha1->mes < fecha2->mes)
        return -1;

    // Comparación de días
    if (fecha1->dia > fecha2->dia)
        return 1;
    if (fecha1->dia < fecha2->dia)
        return -1;

    // Son iguales
    return 0;
    /****** Fin de parte Parte 3.10 *****/
    return res;
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 1 //////
/////////////////////////////////

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia de la fecha
TFecha copiarTFecha(TFecha fecha)
{
    if (fecha == NULL)
        return NULL;

    TFecha newDate = new rep_fecha;
    newDate->anio = fecha->anio;
    newDate->dia = fecha->dia;
    newDate->mes = fecha->mes;
    return newDate;
}
