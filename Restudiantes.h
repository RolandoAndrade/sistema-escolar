/*
<----------------------------------------------------->
FUNCIONES PARA EL REGISTRO DE ESTUDIANTES
I- FUNCIONES DE VALIDACIÓN
	1. Veces que se ha cursado la materia
	2. Encontrar casilla.
II- AGREGAR REGISTROS
	3. Insertar registro en lista secundaria.
	4. Pedir datos a agregar.
II- MODIFICAR NOTAS
	5. Modificar.
III- ELIMINAR
	6. Eliminar registro.
	7. Pedir datos a eliminar.
<----------------------------------------------------->
	*/

/*<--------------------1. CONTAR VECES QUE SE CURSA LA MISMA MATERIA-------------------->*/

int vecesCursadas(pasado *p, int cod,curso *q)
{
	if (!p)
		return 0;
	curso *aux = encontrarCurso(q, p->codigo, 0);
	if (aux->cmateria == cod&&p->nota >= 10)
		return 42;
	return (aux->cmateria == cod)&&(p->nota>0) ? vecesCursadas(p->sig, cod,q) + 1 : vecesCursadas(p->sig, cod,q);
}

/*<--------------------2. ENCONTRAR EL REGISTRO-------------------->*/

pasado * encontrarRegistro(pasado *p, int cod)
{
	while (p&&p->codigo != cod)
		p = p->sig;
	return p;
}

/*<--------------------3. INSERTAR EN LISTA SECUNDARIA-------------------->*/

void insertarRegistro(pasado **p,pasado*nueva)
{
	if (*p)
	{
		pasado*aux = *p;
		while (aux->sig)
		{
			aux = aux->sig;//Llega al final de la lista
		}
		aux->sig = nueva;//Inserta lista
	}
	else
	{
		*p = nueva;
	}
}

/*<--------------------4. PEDIR LOS DATOS A INSERTAR-------------------->*/

void agregar_registro(persona *p,curso *q)
{
	int ci = 0,i=0;
	persona *t = NULL;
	pasado *ax = new pasado;
	curso *aux = NULL;
	do
	{
		system("cls");
		printf("\n\t\t   Agregar registros a estudiante  \n\n");
		printf("\t Indique la cedula del estudiante\n\n");				//Pide la cédula
		printf("\t Cedula de identidad: ");
		scanf(" %i", &ci);
		if (!(i = validarci(p, ci)))
		{
			error(4, "la persona que busca no esta inscrita en el sistema");
		}
	} while (!i);
	t = encontrarPersona(p, ci);
	do
	{ 
		printf("\n\t Introduzca el codigo de curso:\n\n");
		printf("\t Codigo de curso: ");
		scanf(" %i", &ci);
		if (!(i=validarcur(q, ci, 0)))
			error(4, "no existe el curso");
		else if (encontrarRegistro(t->cant, ci))
		{
			error(4, "el curso ya fue inscrito anteriormente");
			i = 0;
		}
		else
		{
			aux = encontrarCurso(q, ci, 0);
			if (t->cant&&vecesCursadas(t->cant, aux->cmateria,q) > 3)
			{
				i = 0;
				error(3, "el estudiante ya no puede cursar esta materia");
			}
		}
	} while (!i);
	ax->codigo = ci;
	do
	{
		printf("\n\t Introduzca la nota del curso: (0-20 donde 0 es retirado)\n\n");
		printf("\t Nota de curso: ");
		scanf(" %i", &ci);
		if (ci > 20 || ci < 0)
			error(3, "nota no valida");
	} while (ci > 20 || ci < 0);
	ax->nota = ci;
	ax->sig = NULL;
	insertarRegistro(&(t->cant), ax);
	system("pause");
}

/*<--------------------5. MODIFICAR-------------------->*/

void modificar_registro(persona *p, curso *q)
{
	int ci = 0, i = 0;
	persona *t = NULL;
	pasado *aux = NULL;
	if(p->cant)
	{ 
		do
		{
			system("cls");
			printf("\n\t\t   Agregar registros a estudiante  \n\n");
			printf("\t Indique la cedula del estudiante\n\n");				//Pide la cédula
			printf("\t Cedula de identidad: ");
			scanf(" %i", &ci);
			if (!(i = validarci(p, ci)))
			{
				error(4, "la persona que busca no esta inscrita en el sistema");
			}
		} while (!i);
		t = encontrarPersona(p, ci);
		do
		{
			printf("\t\n\n Indique el codigo del curso a modificar\n\n");				//Pide la cédula
			printf("\t Codigo de curso: ");
			scanf(" %i", &ci);
			aux = (encontrarRegistro(t->cant, ci));
			if (!aux)
				error(3, "no hay cursos asociados al estudiante con ese codigo");
		} while (!aux);
		do
		{
			printf("\n\t Introduzca la nota del curso: (0-20 donde 0 es retirado)\n\n");
			printf("\t Nota de curso: ");
			scanf(" %i", &ci);
			if (ci > 20 || ci < 0)
				error(3, "nota no valida");
		} while (ci > 20 || ci < 0);
		aux->nota = ci;
	}
	else
	{
		error(3, "el estudiante no esta inscrito en ningun curso");
	}
}

/*<--------------------6. ELIMINAR DE LA LISTA SECUNDARIA-------------------->*/

void eliminarR(pasado **p, int cod)
{
	pasado *t = *p, *aux = NULL;
	if (*p && (*p)->codigo == cod)
	{
		*p = (*p)->sig;
		delete t;
	}
	else
	{
		while (t&&t->sig&&t->sig->codigo != cod)
			t = t->sig;
		if (t->sig)
		{
			aux = t->sig;
			t->sig = t->sig->sig;
			delete aux;
		}
	}

}

/*<--------------------7. PEDIR LOS DATOS A ELIMINAR-------------------->*/

void eliminar_registro(persona **p)
{//elimina cursos
	int i = 0, ci = 0; persona *t = NULL; 
	if (*p)
	{
		do
		{
			system("cls");
			printf("\n\t\t   Agregar registros a estudiante  \n\n");
			printf("\t Indique la cedula del estudiante\n\n");				//Pide la cédula
			printf("\t Cedula de identidad: ");
			scanf(" %i", &ci);
			if (!(i = validarci(*p, ci)))
			{
				error(4, "la persona que busca no esta inscrita en el sistema");
			}
		} while (!i);
		t = encontrarPersona(*p, ci);
		do
		{
			i = 1;
			printf("\n\t\t   Eliminar Curso   \n\n");
			printf("\t Indique el codigo del curso a eliminar\n\n");			//Pide el codigo de la materia que se quiere eliminar
			printf("\t Codigo: ");
			scanf(" %d", &(ci));
			if (!encontrarRegistro(t->cant,ci))
			{
				error(4, "no existe el codigo de curso:(");	//valida primero que la materia a modificar exista
				i = 0;
			}

		} while (!i);
		eliminarR(&(t->cant), ci);
	}
	else
	{
		error(4, "no existen materias");
	}
	t = *p;
}