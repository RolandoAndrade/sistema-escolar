/*
<----------------------------------------------------->
FUNCIONES PARA EL MANTENIMIENTO DE LA LISTA DE ESTUDIANTES
0. Encabezado de datos
I-MOSTRAR
	1. Mostrar los campos de la lista.
II- FUNCIONES DE VALIDACION
	2. Validar si existe la cédula de identidad.
	3. Comparar parámetros de busqueda en la lista.
	4. Buscar la posición de una cédula.
	5. Búsqueda del estudiante.
III. FUNCIONES PARA AÑADIR A LA LISTA
	6. Insertar estudiante al final de la lista.
	7. Pedir datos para agregar a la lista.
IV. FUNCIONES PARA ELIMINAR
	8. Eliminar las personas.
	9. Pedir la cédula a eliminar.
V. MODIFICAR LA ESTUDIANTE.
	10. Modificar persona.
VI- CONSULTAR ESTUDIANTE
	11. Consultar completo o por parámetros
<----------------------------------------------------->*/

/*<--------------------0. ENCABEZADO DE DATOS-------------------->*/

void encabezadoPer()
{
	printf("\n____________________________________________________________________________________________________________________________________________________________________________________________\n\n");
	gotox(4);
	printf("CEDULA");
	gotox(37);
	printf("NOMBRE");
	gotox(65);
	printf("FECHA DE NACIMIENTO");
	gotox(88);
	printf("DIRECCION");
	printf("\n___________________________________________________________________________________________________________________________________________________________________________________________\n");
}

/*<--------------------1. MOSTRAR EL CONTENIDO DE LOS CAMPOS-------------------->*/

void leerPersona(persona*p)
{
	if (p)
	{
		gotox(3);
		printf("%d", p->ci);
		gotox(40 - (int)(strlen(p->nombre) / 2));
		printf("%s", p->nombre);
		gotox(70);
		printf("%d\\%d\\%d", p->fecha->dia, p->fecha->mes, p->fecha->year);
		gotox(88);
		printf("%s\n", p->direccion);
	}
}


/*<--------------------2. VALIDAR SI LA CÉDULA DE IDENTIDAD EXISTE-------------------->*/

int validarci(persona*p, int x)
{
	if (p)
	{
		if ((p->ci) == x)
			return 1;		//La cédula fue encontrada
		else
			validarci(p->sig, x);
	}
	else
		return 0;
}

/*<--------------------3. COMPARAR LOS PARÁMETROS DE BÚSQUEDA-------------------->*/

int comparacionEstudiante(persona*p, persona*aux, int indicador)//FUNCIÓN RECURSIVA					
{//recibe la lista principal,una lista de un solo elemento con los parametros de busqueda y un indicador para imprimir la cabeza
	if (p)
	{

		int parametro, coincidencia, final;//parametro indica el numero de parametros utilizados, coincidencia las veces en el que ese parámetro se encuentra
		parametro = coincidencia = final = 0;

		//EVALUAR EL CODIGO

		if ((aux->ci) != -1)
		{
			parametro++;
			if ((aux->ci) == (p->ci))
			{
				coincidencia++;//hubo una coincidencia
			}
		}

		//EVALUAR EL NOMBRE

		if ((strstr((aux->nombre), "-1")) == NULL)
		{
			parametro++;
			if ((strstr(p->nombre, aux->nombre)) != NULL)
				coincidencia++;
		}

		//EVALUAR LA DIRECCION

		if ((strstr((aux->direccion), "-1")) == NULL)
		{
			parametro++;
			if ((strstr(p->direccion, aux->direccion)) != NULL)
				coincidencia++;
		}

		//EVALUAR EL DIA DE NACIMIENTO

		if (aux->fecha->dia!=-1)
		{
			parametro++;
			if (aux->fecha->dia== p->fecha->dia)
				coincidencia++;
		}

		//EVALUAR EL MES DE NACIMIENTO

		if (aux->fecha->mes != -1)
		{
			parametro++;
			if (aux->fecha->mes == p->fecha->mes)
				coincidencia++;
		}

		//EVALUAR EL AÑO DE NACIMIENTO

		if (aux->fecha->year != -1)
		{
			parametro++;
			if (aux->fecha->year == p->fecha->year)
				coincidencia++;
		}

		//EVALUAR SI HUBO LA MISMA CANTIDAD DE COINCIDENCIAS QUE DE PARAMETROS DADOS

		if ((parametro == coincidencia) && (parametro != 0))
		{// Si cada parametro buscado coincide con los datos de una de las materias coincidencias, sera igual a aux y se imprime los campos de esa materia

			final = 1;
			if (!indicador)
			{//Imprime la cabeza
				encabezadoPer();
				indicador = 1;
			}
			leerPersona(p);//Imprime los datos
		}
		return comparacionEstudiante(p->sig, aux, indicador) + final;//devuelve un numero diferente de 0 si encontro una materia con las especificaciones dadas
	}
	else
		return 0;
}

/*<--------------------4. BUSCAR LA CÉDULA DE UNA PERSONA-------------------->*/

persona * encontrarPersona(persona*p, int x)
{//encuentra la cedula (devuelve el puntero de la persona justo antes de donde se encontro la cedula)
	while (p&&p->ci != x)
		p = p->sig;
	return p;
}

/*<--------------------5. BUSCAR A LA PERSONA-------------------->*/

void menuBusquedaPersona(persona*p)
{//aquí se hacen las validaciones para proceder a buscar por parametros
	if (p)
	{
		int i, j, cod, result;
		do
		{//Hacer la búsqueda repetidas veces
			persona*aux;
			i = cod = j = result = 0;
			//INICIALIZAR EL NUEVO CAMPO
			aux = new persona;
			aux->ci = -1;
			strcpy(aux->nombre, "-1");
			aux->fecha = new rfecha;
			aux->fecha->dia = -1;
			aux->fecha->mes = -1;
			aux->fecha->year = -1;
			strcpy(aux->direccion, "-1");
			//LEER LOS PARÁMETROS

			do
			{//Leer parámetros hasta que no se desee agregar más
				do
				{//Pide los parámetros de búsqueda hasta que se seleccione algino
					printf("Indique un parametro de busqueda\n\n");
					printf("\t1. Cedula de identidad \n");
					printf("\t2. Nombre \n");
					printf("\t3. Dia de nacimiento\n ");
					printf("\t4. Mes de nacimiento\n ");
					printf("\t5. A%co de nacimiento\n", 164);
					printf("\t6. Direccion\n\n");
					printf("\tOpcion: ");
					scanf(" %d", &i);
					if ((i >= 1) && (i <= 6))
					{
						system("cls");
						printf("\n\t\t   Ingrese el parametro   \n\n");
					}
					switch (i)
					{
					case 1:
						printf("\t Cedula de identidad: ");
						scanf(" %d", &(aux->ci));
						break;
					case 2:
						printf("\t Nombre: ");
						scanf(" %[^\n]", &(aux->nombre));
						break;
					case 6:
						printf("\t Descripcion: ");
						scanf(" %[^\n]", &(aux->direccion));
						break;
					case 3:
						printf("\t Dia de nacimiento: ");
						scanf(" %d", &(aux->fecha->dia));
						break;
					case 4:
						printf("\t Mes de nacimiento: ");
						scanf(" %d", &(aux->fecha->mes));
						break;
					case 5:
						printf("\t A%co de nacimiento: ", 164);
						scanf(" %d", &(aux->fecha->year));
						break;
					default:
						error(3, "la opcion no esta disponible");
						break;
					}
				} while ((i < 1) || (i > 6));
				if ((aux->ci) == -1)//Si no se introdujo cedula
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

			result = comparacionEstudiante(p, aux, 0);
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

/*<--------------------6. INSERTAR PERSONA AL FINAL DE LA LISTA-------------------->*/

void añadirEstudiante(persona **p,persona *nueva)
{
	if (*p)
	{
		persona*aux = *p;
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

/*<--------------------7. CREAR NUEVO REGISTRO A INSERTAR-------------------->*/

void agregar_estudiante(persona **p)
{
	persona * nueva = new persona;
	int i = 0;
	do
	{
		printf("\n\n\t\t   Agregar Estudiante   \n\n");
		printf("\t1. Cedula de identidad: ");
		scanf(" %d", &(nueva->ci));
		//Valida que el codigo de la materia no este repetido
		if (i = validarci(*p, nueva->ci))//Asigna a i 1 o 0
		{
			error(3, "el alumno ya esta en el sistema");
		}
	} while (i);//Mientras i==1
	printf("\t2. Nombre completo: ");
	scanf(" %[^\n]", &(nueva->nombre));
	//comprobar fechas()
	nueva->fecha = new rfecha;
		printf("\t3.1. Dia de nacimiento (1-31): ");
		scanf(" %d", &(nueva->fecha->dia));
		printf("\t3.2. Mes de nacimiento (1-12): ");
		scanf(" %d", &(nueva->fecha->mes));
		printf("\t3.3. A%co de nacimiento (1-12): ",164);
		scanf(" %d", &(nueva->fecha->year));
	printf("\t4. Direccion: ");
	scanf(" %[^\n]", &(nueva->direccion));
	nueva->sig = NULL;
	nueva->cant = NULL;
	añadirEstudiante(p, nueva);
}

/*<--------------------8. ELIMINAR A LA PERSONA-------------------->*/

void eliminarP(persona **p, int c)
{
	persona *t = *p, *aux = NULL;
	if (*p && (*p)->ci == c)
	{
		*p = (*p)->sig;
		delete t;
	}
	else
	{
		while (t&&t->sig&&t->sig->ci != c)
			t = t->sig;
		if (t->sig)
		{
			aux = t->sig;
			t->sig = t->sig->sig;
			delete aux;
		}
	}
}

/*<--------------------9. INTRODUCIR CEDULA A ELIMINAR-------------------->*/

void eliminar_estudiantes(persona**p)
{//elimina personas
	int i = 0, ced = 0; persona*aux = NULL;
	if (*p)
	{
		system("cls");
		do
		{
			printf("\n\t\t   Eliminar Persona   \n\n");
			printf("\t Indique la cedula de la persona a eliminar\n\n");//Pide la cédula que se quiere eliminar
			printf("\t CI: ");
			scanf(" %d", &(ced));
			if (!(i = validarci(*p, ced)))
			{
				error(4, "la persona no esta inscrita");//valida primero que la cédula exista
			}

		} while (!i);
		eliminarP(p, ced);
	}
	else
	{
		error(4, "no hay personas inscritas");
	}
}

/*<--------------------10. MODIFICAR PERSONAS-------------------->*/

void modificar_personas(persona*p)
{//modifica cualquier campo de la persona
	int i = 0, ced = 0, t = 0; persona*aux = NULL;
	if (p)
	{
		system("cls");
		do
		{
			printf("\n\t\t   Modificar Materia   \n\n");
			printf("\t Indique la cedula de identidad de la persona modificar\n\n");//Pide la cedula de la persona que se quiere modificar
			printf("\t CI: ");
			scanf(" %d", &(ced));
			if (!(i = validarci(p, ced))) 
			{
				error(4,"no hay personas incritas con esa cedula de identidad\n");//valida primero que la persona a modificar exista
			}
		} while (!i);

		aux = encontrarPersona(p, ced);											 //encuentra la cedula y se ubica en posición
		do
		{
			printf("\n\t Indique el campo de la materia a modificar\n\n");
			printf("\t1. Nombre \n");
			printf("\t2. Fecha \n");
			printf("\t3. Direccion\n ");									//Pide el campo que quiere modificar
			printf("\tOpcion: ");
			scanf(" %d", &i);
			if ((i >= 1) && (i <= 3))
			{
				system("cls");
				printf("\n\t\t   Ingrese el nuevo dato   \n\n");
			}
			switch (i) {
			case 1:
				printf("\t Nombre completo: ");
				scanf(" %[^\n]", &(aux->nombre));
				break;
			case 2:
				//comprobar fechas()
				printf("\t3.1. Dia de nacimiento (1-31): ");
				scanf(" %d", &(aux->fecha->dia));
				printf("\t3.2. Mes de nacimiento (1-12): ");
				scanf(" %d", &(aux->fecha->mes));
				printf("\t3.3. A%co de nacimiento (1-12): ", 164);
				scanf(" %d", &(aux->fecha->year));
				break;
			case 3:
				printf("\t4. Direccion: ");
				scanf(" %[^\n]", &(aux->direccion));
				break;
			default:
				error(3, "la opcion no esta disponible");
				break;
			};
		} while ((i<1) || (i>5));
	}
	else
	{
		error(4, "no existen estudiantes inscritos");
	}
}

/*<--------------------11. CONSULTAR ESTUDIANTE-------------------->*/

void consultarEstudiante(persona*p)
{
	system("cls");
	if (p)
	{
		int i = 0, cod = 0;
		do
		{
			printf("\n\n\t\tConsultar Estudiantes\n\n");
			printf("\t1. Visualizar todos los estudiantes\n\n");
			printf("\t2. Visualizar por parametro de busqueda\n\n");
			printf("\tOpcion: ");
			scanf(" %d", &i);
			switch (i)
			{
			case 1:
				system("cls");
				encabezadoPer();
				while (p)
				{
					leerPersona(p);
					p = p->sig;
				}
				system("pause");
				break;
			case 2:
				system("cls");
				menuBusquedaPersona(p);
				break;
			default:
				error(3, "la opcion no esta disponible");
				break;
			};
		} while ((i != 1) && (i != 2));
	}
	else
	{
		error(4, "no existen estudiantes");
	}

}

