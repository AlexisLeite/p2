#include "../include/conjuntoIds.h"

struct rep_conjuntoIds
{
	bool *values;
	nat length;
	nat size;
};

TConjuntoIds crearTConjuntoIds(nat cantMax)
{
	TConjuntoIds newSet = new rep_conjuntoIds;
	newSet->values = new bool[cantMax + 1];
	newSet->length = 0;
	newSet->size = cantMax;

	for (nat i = 0; i <= cantMax; i++)
		newSet->values[i] = false;

	return newSet;
};

bool esVacioTConjuntoIds(TConjuntoIds c)
{
	return c->length == 0;
};

void insertarTConjuntoIds(nat id, TConjuntoIds &c)
{
	if (id < 1 || id > c->size)
		return;
	if (!c->values[id])
		c->length++;
	c->values[id] = true;
};

void borrarTConjuntoIds(nat id, TConjuntoIds &c)
{
	if (c->values[id])
		c->length--;
	c->values[id] = false;
};

bool perteneceTConjuntoIds(nat id, TConjuntoIds c)
{
	return id >= 1 && id <= c->size && c->values[id];
};

nat cardinalTConjuntoIds(TConjuntoIds c)
{
	return c->length;
};

nat cantMaxTConjuntoIds(TConjuntoIds c)
{
	return c->size;
};

void imprimirTConjuntoIds(TConjuntoIds c)
{
	for (nat i = 1; i <= c->size; i++)
	{
		if (c->values[i])
		{
			printf("%i ", i);
		}
	}
	printf("\n");
};

void liberarTConjuntoIds(TConjuntoIds &c)
{
	delete[] c->values;
	delete c;
	c = NULL;
};

TConjuntoIds unionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2)
{
	TConjuntoIds result = crearTConjuntoIds(c1->size);
	for (nat i = 1; i <= c1->size; i++)
	{
		if (c1->values[i] || c2->values[i])
			insertarTConjuntoIds(i, result);
	}

	return result;
};

TConjuntoIds interseccionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2)
{
	TConjuntoIds result = crearTConjuntoIds(c1->size);
	for (nat i = 1; i <= c1->size; i++)
	{
		if (c1->values[i] && c2->values[i])
			insertarTConjuntoIds(i, result);
	}

	return result;
};

TConjuntoIds diferenciaTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2)
{
	TConjuntoIds result = crearTConjuntoIds(c1->size);
	for (nat i = 1; i <= c1->size; i++)
	{
		if (c1->values[i] && !c2->values[i])
			insertarTConjuntoIds(i, result);
	}

	return result;
};
