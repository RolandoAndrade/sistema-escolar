/*
<----------------------------------------------------->
FUNCIONES PARA EL MANTENIMIENTO DE LA LISTA DE CURSOS
00. Declaracion de funciones
0. Encabezado.
I-MOSTRAR
	1. Mostrar los campos de la lista.
II- FUNCIONES DE VALIDACION
	2. Validar si existe el codigo del curso.
	3. Comparar parámetros de busqueda en la lista.
	4. Buscar la posición del curso.
	5. Parámetros de búsqueda.
III. FUNCIONES PARA AÑADIR A LA LISTA
	6. Insertar curso al final de la lista.
	7. Pedir codigo de materia.
	8. Pedir datos para agregar a la lista.
IV. FUNCIONES PARA ELIMINAR
	9. Eliminar los cursos.
	10. Pedir el codigo del curso.
V. MODIFICAR CURSO.
	10. Modificar curso.
VI- CONSULTAR CURSO
	11. Consultar completo o por parámetros
<----------------------------------------------------->*/

/*<--------------------0. MOSTRAR ENCABEZADO DE DATOS-------------------->*/

void encabezadoCur()
{
	system("cls");
	printf("\n____________________________________________________________________________________\n\n");
	printf("\tCodigo\t\tCodigo de Materia\t\t A%co  \t\t Lapso", 164);
	printf("\n_____________________________________________________________________________________\n");
}

/*<--------------------1. MOSTRAR LOS CAMPOS DE LA LISTA-------------------->*/

void leerCurso(curso*p)
{
	if (p)
	{
		printf("\t%d", p->codigo);
		printf("\t\t\t%d\t", p->cmateria);
		printf("\t\t%i\t", p->año);
		printf("\t%i\t\n", p->lapso);
	}
}

/*<--------------------2. VALIDAR EL CÓDIGO DEL CURSO-------------------->*/

int validarcur(curso*p, int cod,int i)
{
	if (p)
	{
		if (((p->codigo) == cod&&(i==0))||((p->cmateria)==cod&&(i==1)))
			return 1;		//Valida que el codigo de la materia no este repetido
		else
			validarcur(p->sig, cod,i);
	}
	else
		return 0;
}

/*<--------------------3. COMPARAR PARÁMETROS DE BÚSQUEDA-------------------->*/

int comparacionCurso(curso*p, curso*aux, int indicador)//FUNCIÓN RECURSIVA					
{//recibe la lista principal,una lista de un solo elemento con los parametros de busqueda y un indicador para imprimir la cabeza
	if (p)
	{

		int parametro, coincidencia, final;//parametro indica el numero de parametros utilizados, coincidencia las veces en el que ese parámetro se encuentra
		parametro = coincidencia = final = 0;

		//EVALUAR EL CODIGO

		if ((aux->codigo) != -1)
		{
			parametro++;
			if ((aux->codigo) == (p->codigo))
			{
				coincidencia++;//hubo una coincidencia
			}
		}

		//EVALUAR EL CODIGO DE MATERIA

		if ((aux->cmateria) != -1)
		{
			parametro++;
			if ((aux->cmateria) == (p->cmateria))
				coincidencia++;
		}

		//EVALUAR Año

		if ((aux->año) != -1)
		{
			parametro++;
			if ((aux->año) == (p->año))
				coincidencia++;
		}

		//EVALUAR EL LAPSO

		if ((aux->lapso) != -1)
		{
			parametro++;
			if ((aux->lapso) == (p->lapso))
				coincidencia++;
		}

		//EVALUAR SI HUBO LA MISMA CANTIDAD DE COINCIDENCIAS QUE DE PARAMETROS DADOS

		if ((parametro == coincidencia) && (parametro != 0))
		{// Si cada parametro buscado coincide con los datos de una de las materias coincidencias, sera igual a aux y se imprime los campos de esa materia

			final = 1;
			if (!indicador)
			{//Imprime la cabeza
				encabezadoCur();
				indicador = 1;
			}
			leerCurso(p);//Imprime los datos
		}
		return comparacionCurso(p->sig, aux, indicador) + final;//devuelve un numero diferente de 0 si encontro una materia con las especificaciones dadas
	}
	else
		return 0;
}

/*<--------------------4. ENCONTRAR LA POSICIÓN DEL CURSO-------------------->*/

curso * encontrarCurso(curso*p, int cod, int i)
{//encuentra la materia mediante el codigo (devuelve el puntero de la materia donde se encontro el codigo)
	while ((p&&p->codigo != cod&&i == 0) || (p&&p->cmateria != cod&&i == 1))
		p = p->sig;
	return p;
}

/*<--------------------5. SELECCIONAR LOS PARÁMETROS DE BÚSQUEDA-------------------->*/

void menuBusquedaCurso(curso*p)
{//aquí se hacen las validaciones para proceder a buscar por parametros
	if (p)
	{
		int i, j, cod, result;
		do
		{//Hacer la búsqueda repetidas veces
			curso*aux;
			i = cod = j = result = 0;
			//INICIALIZAR EL NUEVO CAMPO
			aux = new curso;
			aux->codigo = -1;
			aux->cmateria = -1;
			aux->año = -1;
			aux->lapso = -1;

			//LEER LOS PARÁMETROS

			do
			{//Leer parámetros hasta que no se desee agregar más
				do
				{//Pide los parámetros de búsqueda hasta que se seleccione algino
					printf("Indique un parametro de busqueda\n\n");
					printf("\t1. Codigo \n");
					printf("\t2. Codigo de materia \n");
					printf("\t3. A%co\n ",164);
					printf("\t4. Lapso\n\n ");
					printf("\tOpcion: ");
					scanf(" %d", &i);
					if ((i >= 1) && (i <= 4))
					{
						system("cls");
						printf("\n\t\t   Ingrese el parametro   \n\n");
					}
					switch (i)
					{
					case 1:
						printf("\t Codigo: ");
						scanf(" %d", &(aux->codigo));
						break;
					case 2:
						printf("\t Codigo de materia: ");
						scanf(" %d", &(aux->cmateria));
						break;
					case 3:
						printf("\t A%co: ", 164);
						scanf(" %d", &(aux->año));
						break;
					case 4:
						do
						{
							printf("\t Lapso: ");
							scanf(" %i", &(aux->lapso));
							if (aux->lapso < 1 || aux->lapso>3)
							{
								error(3, "no es un lapso valido");
							}
						} while (aux->lapso < 1 || aux->lapso>3);
						break;
					default:
						error(3, "la opcion no esta disponible");
						break;
					}
				} while ((i < 1) || (i > 5));
				if ((aux->codigo) == -1)//Si no se introdujo código
				{
					do
					{//Preguntar por nuevos parametros
						printf("\n\t\tDesea modificar o agregar otro parametro?\n");
						printf("\t\t\t\tSI (1) || NO(0)\n");
						printf("\tOpcion: ");
						scanf("%i", &j);
						if ((j != 0) && (j != 1))
						{
							error(3, "la opcion no esta disponible");
						}
					} while ((j != 0) && (j != 1));
				}
				else
				{
					break;
				}
			} while (j);

			//COMPARARLOS CON LOS DE LA LISTA

			result = comparacionCurso(p, aux, 0);
			if (!result)
			{
				error(3, "no se encontro ninguna materia con los parametros seleccionados");
			}

			//VOLVER A HACER LA BÚSQUEDA

			do
			{
				printf("\n\t\t\tDesea volver a realizar la busqueda?\n");
				printf("\t\t\t\t1: SI / 0: NO\n");
				printf("\tOpcion: ");
				scanf("%i", &j);
				if ((j != 0) && (j != 1))
				{
					error(3, "la opcion no esta disponible");
				}
				system("cls");
			} while ((j != 0) && (j != 1));

		} while (j);
	}
}

/*<--------------------6. INSERTAR CURSO EN LA LISTA------------------->*/

void añadirCurso(curso **p, curso *nuevo)
{
	if (*p)
	{
		curso*aux = *p;
		while (aux->sig)
		{
			aux = aux->sig;//Llega al final de la lista
		}
		aux->sig = nuevo;//Inserta lista
	}
	else
	{
		*p = nuevo;
	}

}

/*<--------------------7. PEDIR EL CODIGO DE MATERIA------------------->*/

void PideMateria(curso *p,materia *q,curso *nuevo,int *i)
{
	int aux=0;
	do
	{
		printf("\t2. Codigo de materia: ");
		scanf(" %d", &aux);
		/*if (!(*i = validarcur(p, aux, 1)))
		{*/
			if (!(*i = validarmat(q, aux)))//Asigna a i 1 o 0
			{
				error(4, "no existe una materia con ese codigo");
			}
		/*}
		else
		{
			error(4, "ya existe un curso con ese codigo de materia");
			k = 0;
		}*/
	} while (!(*i));
	nuevo->cmateria = aux;
}

/*<--------------------8. PEDIR DATOS A AGREGAR------------------->*/

void agregar_cursos(curso **p,materia **q)
{
	curso * nuevo = new curso;
	int i = 0;
	do
	{
		printf("\n\n\t\t   Agregar Curso   \n\n");
		printf("\t1. Codigo: ");
		scanf(" %d", &(nuevo->codigo));
		//Valida que el codigo de curso no este repetido
		if (i = validarcur(*p, nuevo->codigo,0))//Asigna a i 1 o 0
		{
			error(4, "ya existe un curso con ese codigo");
		}
		if (nuevo->codigo < 1000 || nuevo->codigo>9999)
		{
			i = 1;
			error(4, "codigo no valido, por favor introduzca valores entre 1000-9999");
		}
	} while (i);//Mientras i==1
	i = 0;
	PideMateria(*p, *q, nuevo, &i);
	if (i)
	{
		printf("\t3. A%co: ",164);
		scanf(" %i", &(nuevo->año));
		do
		{
			printf("\t4. Lapso: ");
			scanf(" %i", &(nuevo->lapso));
			if (nuevo->lapso < 1 || nuevo->lapso>3)
			{
				error(3, "no es un lapso valido");
			}
		} while (nuevo->lapso < 1 || nuevo->lapso>3);
		nuevo->sig = NULL;
		añadirCurso(p, nuevo);
		system("cls");
	}

}

/*<--------------------9. QUITAR DE LA LISTA------------------->*/

void eliminarC(curso **p, int cod,persona **q)
{
	curso *t = *p, *aux=NULL;
	persona *ax = *q;
	while (ax)
	{
		eliminarR(&(ax->cant), cod);
		ax = ax->sig;
	}
	if (*p&&(*p)->codigo == cod)
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

/*<--------------------10. INTRODUCIR CÓDIGO A ELIMINAR-------------------->*/

void eliminar_cursos(curso **p,persona **q)
{//elimina cursos
	int i = 0, cod = 0;
	if (*p)
	{
		system("cls");
		do
		{
			printf("\n\t\t   Eliminar Curso   \n\n");
			printf("\t Indique el codigo del curso a eliminar\n\n");			//Pide el codigo de la materia que se quiere eliminar
			printf("\t Codigo: ");
			scanf(" %d", &(cod));
			if (!(i = validarcur(*p, cod,0)))
			{
				error(4, "no existe el codigo de materia :(");	//valida primero que la materia a modificar exista
			}

		} while (!i);
		eliminarC(p, cod,q);
	}
	else
	{
		error(4, "no existen materias");
	}
}

/*<--------------------11. MODIFICAR CURSOS-------------------->*/

void modificar_cursos(curso*p,materia *q)
{//modifica cualquier campo de los cursos
	int i = 0, cod = 0; curso*aux = NULL;
	if (p)
	{
		system("cls");
		do
		{
			printf("\n\t\t   Modificar Curso   \n\n");
			printf("\t Indique el codigo de curso a modificar\n\n");	//Pide el codigo del curso que se quiere modificar
			printf("\t Codigo: ");
			scanf(" %d", &(cod));
			if (!(i = validarcur(p, cod,0))) 
			{
				error(3, "no existe curso con ese codigo");
			}
		} while (!i);

		aux = encontrarCurso(p, cod,0);					//encuentra el curso mediante su codigo
		do {
			printf("\n\t Indique el campo de la materia a modificar\n\n");
			printf("\t1. Codigo de materia \n");
			printf("\t2. A%co\n ",164);
			printf("\t3. Lapso\n\n ");		//Pide el campo que quiere modificar
			printf("\tOpcion: ");
			scanf(" %d", &i);
			if ((i >= 1) && (i <= 4))
			{
				system("cls");
				printf("\n\t\t   Ingrese el nuevo dato   \n\n");
			}
			switch (i) 
			{
				case 1:
					cod = 0;
					PideMateria(p, q, aux, &cod);
					break;
				case 2:
					printf("\t A%co: ",164);
					scanf(" %d", &(aux->año));
					break;
				case 3:
					do
					{
						printf("\t Lapso: ");
						scanf(" %i", &(aux->lapso));
						if (aux->lapso < 1 || aux->lapso>3)
						{
							error(3, "no es un lapso valido");
						}
					} while (aux->lapso < 1 || aux->lapso>3);
					break;
				default:
					error(3, "la opcion no esta disponible");
					break;
			};
		} while ((i<1) || (i>3));
	}
	else
	{
		error(4, "No existen materias");
	}
}

/*<--------------------12. CONSULTAR CURSO-------------------->*/

void consultarCurso(curso*p)
{
	system("cls");
	if (p)
	{
		int i = 0;
		do
		{
			printf("\n\n\t\tConsultar Cursos\n\n");
			printf("\t1. Visualizar todos los cursos\n\n");
			printf("\t2. Visualizar por codigo \n\n");
			printf("\tOpcion: ");
			scanf(" %d", &i);
			switch (i)
			{
			case 1:
				system("cls");
				encabezadoCur();
				while (p)
				{
					leerCurso(p);
					p = p->sig;
				}
				system("pause");
				break;
			case 2:
				system("cls");
				menuBusquedaCurso(p);
				break;
			default:
				error(3, "la opcion no esta disponible");
				break;
			};
		} while ((i != 1) && (i != 2));
	}
	else
	{
		error(4, "no existen materias");
	}

}
