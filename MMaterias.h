/*
<----------------------------------------------------->
FUNCIONES PARA EL MANTENIMIENTO DE LA LISTA DE MATERIAS
00. Declaración de funciones.
0. Encabezado de datos
I-MOSTRAR
	1. Mostrar los campos de la lista.
II- FUNCIONES DE VALIDACION
	2. Validar si el código de materia existe.
	3. Comparar parámetros de busqueda en la lista.
	4. Buscar la posición de un código.
	5. Pedir los parámetros de búsqueda.
III. FUNCIONES PARA AÑADIR A LA LISTA
	6. Insertar materia al final de la lista.
	7. Pedir datos para agregar a la lista.
IV. FUNCIONES PARA ELIMINAR
	8. Eliminar las materias.
	9. Pedir el codigo a eliminar.
V. MODIFICAR LA MATERIA.
	10. Modificar materia.
VI- CONSULTAR MATERIA
	11. Elegir si mostrar lista completa o por parametros.
<----------------------------------------------------->
*/

/*<--------------------00. DECLARACION DE FUNCIONES Y PROCEDIMIENTOS-------------------->*/
void eliminarR(pasado **p, int cod);
void eliminarC(curso **p, int cod,persona **q);
curso* encontrarCurso(curso*p, int cod, int i);


/*<--------------------0. MOSTRAR ENCABEZADO DE DATOS-------------------->*/

void encabezadoMat()
{
	printf("\n____________________________________________________________________________________________________________________________________________________________________________________________\n\n");
	gotox(3);
	printf("CODIGO");
	gotox(24);
	printf("NOMBRE");
	gotox(91);
	printf("DESCRIPCION");
	gotox(150);
	printf("SEMESTRE");
	gotox(160);
	printf("CREDITOS");
	printf("\n___________________________________________________________________________________________________________________________________________________________________________________________\n");
}

/*<--------------------1. MOSTRAR EL CONTENIDO DE LOS CAMPOS-------------------->*/

void leer(materia*p)
{
	if (p)
	{
		gotox(4);
		printf("%d", p->codigo);
		gotox(27 - (int)(strlen(p->nombre) / 2));
		printf("%s", p->nombre);
		gotox(96-(int)(strlen(p->descripcion)/2));
		printf("%s", p->descripcion);
		gotox(152);
		printf("%s", p->semestre);
		gotox(162);
		printf("%d\n", p->creditos);
	}
}

/*<--------------------2. VALIDAR SI EXISTE EL CÓDIGO DE LA MATERIA-------------------->*/

int validarmat(materia*p, int cod)
{//Valida que el codigo de la materia este
	if (p)
	{
		if ((p->codigo) == cod)
			return 1;		   //fue encontrado el codifo de la materia
		else
			validarmat(p->sig, cod);
	}
	else
		return 0;
}

/*<--------------------3. COMPARAR LOS PARÁMETROS DE BÚSQUEDA CON LOS DATOS EXISTENTES-------------------->*/

int comparacionMateria(materia*p, materia*aux, int indicador)//FUNCIÓN RECURSIVA					
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

		//EVALUAR EL NOMBRE

		if ((strstr((aux->nombre), "-1")) == NULL)
		{
			parametro++;
			if ((strstr(p->nombre, aux->nombre)) != NULL)
				coincidencia++;
		}

		//EVALUAR LA DESCRIPCION

		if ((strstr((aux->descripcion), "-1")) == NULL)
		{
			parametro++;
			if ((strstr(p->descripcion, aux->descripcion)) != NULL)
				coincidencia++;
		}

		//EVALUAR EL SEMESTRE

		if ((strstr((aux->semestre), "-1")) == NULL)
		{
			parametro++;
			if ((strcmp(p->semestre, aux->semestre)) == 0)
				coincidencia++;
		}

		//EVALUAR LOS CRÉDITOS

		if ((aux->creditos) != -1)
		{
			parametro++;
			if ((aux->creditos) == (p->creditos))
				coincidencia++;
		}

		//EVALUAR SI HUBO LA MISMA CANTIDAD DE COINCIDENCIAS QUE DE PARAMETROS DADOS

		if ((parametro == coincidencia) && (parametro != 0))
		{// Si cada parametro buscado coincide con los datos de una de las materias coincidencias, sera igual a aux y se imprime los campos de esa materia
		
			final = 1;
			if (!indicador)
			{//Imprime la cabeza
				encabezadoMat();
				indicador = 1;
			}
			leer(p);//Imprime los datos
		}
		return comparacionMateria(p->sig, aux, indicador) + final;//devuelve un numero diferente de 0 si encontro una materia con las especificaciones dadas
	}
	else
		return 0;
}

/*<--------------------4. BUSCAR LA POSICION DE UN CODIGO-------------------->*/

materia * encontrar(materia*p, int cod)
{//encuentra la materia mediante el codigo (devuelve el puntero de la materia donde se encontro el codigo)
	while (p&&p->codigo != cod)
		p = p->sig;
	return p;
}

/*<--------------------5. BÚSQUEDA EN LA LISTA CON PARÁMETROS ESPECÍFICOS-------------------->*/

void menuBusquedaMateria(materia*p)
{//aquí se hacen las validaciones para proceder a buscar por parametros
	if (p)
	{
		int i, j, cod,result;
		do
		{//Hacer la búsqueda repetidas veces
			materia*aux;
			i = cod = j = result = 0;
			//INICIALIZAR EL NUEVO CAMPO
			aux = new materia;
			aux->codigo = -1;
			strcpy(aux->nombre, "-1");
			strcpy(aux->descripcion, "-1");
			strcpy(aux->semestre, "-1");
			aux->creditos = -1;

			//LEER LOS PARÁMETROS

			do
			{//Leer parámetros hasta que no se desee agregar más
				do
				{//Pide los parámetros de búsqueda hasta que se seleccione algino
					printf("Indique un parametro de busqueda\n\n");
					printf("\t1. Codigo \n");
					printf("\t2. Nombre \n");
					printf("\t3. Descripcion\n ");
					printf("\t4. Semestre\n ");
					printf("\t5. Creditos\n\n");											
					printf("\tOpcion: ");
					scanf(" %d", &i);
					if ((i >= 1) && (i <= 5))
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
							printf("\t Nombre: ");
							scanf(" %[^\n]", &(aux->nombre));
							break;
						case 3:
							printf("\t Descripcion: ");
							scanf(" %[^\n]", &(aux->descripcion));
							break;
						case 4:
							do
							{//Valida semestre
								system("cls");
								printf("\n\t\t   Ingrese el parametro   \n\n");
								printf("\t Semestre: ");
								scanf(" %s", &(aux->semestre));
								if (!validasem(aux->semestre))
									error(3, "la opcion no esta disponible");
							} while (!validasem(aux->semestre));
							break;
						case 5:
							printf("\t Creditos: ");
							scanf(" %d", &(aux->creditos));
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

			result = comparacionMateria(p, aux, 0);
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

/*<--------------------6. AÑADIR NUEVA MATERIA-------------------->*/

void añadirMateria(materia**p, materia*nueva)
{
	if (*p)
	{
		materia*aux = *p;
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

/*<--------------------7. PEDIR DATOS PARA AGREGAR MATERIA-------------------->*/

void agregar_materias(materia**p)
{//Agrega las materias a la lista
	materia * nueva = new materia;
	int i = 0;
	do
	{
		printf("\n\n\t\t   Agregar Materia   \n\n");
		printf("\t1. Codigo: ");
		scanf(" %d", &(nueva->codigo));
		//Valida que el codigo de la materia no este repetido
		if (i = validarmat(*p, nueva->codigo))//Asigna a i 1 o 0
		{
			error(4, "ya existe una materia con ese codigo");
		}
		if (nueva->codigo < 1000||nueva->codigo>9999)
		{
			i = 1;
			error(4, "codigo no valido, por favor introduzca valores entre 1000-9999");
		}
	} while (i);//Mientras i==1
	printf("\t2. Nombre: ");
	scanf(" %[^\n]", &(nueva->nombre));
	printf("\t3. Descripcion: ");
	scanf(" %[^\n]", &(nueva->descripcion));	//pide al usuario los campos de la nueva materia
	do
	{
		printf("\t4. Semestre: ");
		scanf(" %s", &(nueva->semestre));
	} while (!validasem(nueva->semestre));
	color(1);
	printf("\t5. Creditos: ");
	scanf(" %d", &(nueva->creditos));
	nueva->sig = NULL;
	añadirMateria(p, nueva);
	system("cls");
}

/*<--------------------8. ELIMINAR LA MATERIA-------------------->*/

void eliminarM(materia **p, int cod)
{
	materia *t = *p, *aux = NULL;
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

/*<--------------------9. INTRODUCIR CÓDIGO A ELIMINAR-------------------->*/

void eliminar_materias(materia**p,curso **q,persona **r)
{								//elimina materias
	int i = 0, cod = 0; materia*aux = NULL; curso *t = NULL;
	if (*p) 
	{
		system("cls");
		do
		{
			printf("\n\t\t   Eliminar Materia   \n\n");
			printf("\t Indique el codigo de la materia a eliminar\n\n");			//Pide el codigo de la materia que se quiere eliminar
			printf("\t Codigo: ");
			scanf(" %d", &(cod));
			if (!(i = validarmat(*p, cod)))
			{
				error(4, "no existe el codigo de materia :(");	//valida primero que la materia a modificar exista
			}

		} while (!i);
		while (t = encontrarCurso(*q, cod, 1))
			eliminarC(q, t->codigo,r);
		eliminarM(p, cod);
	}
	else
	{
		error(4, "no existen materias");
	}
}

/*<--------------------10. MODIFICAR LA MATERIA-------------------->*/

void modificar_materias(materia*p)
{//modifica cualquier campo de las materias
	int i = 0, cod = 0; materia*aux = NULL;
	if (p)
	{
		system("cls");
		do {
			printf("\n\t\t   Modificar Materia   \n\n");
			printf("\t Indique el codigo de la materia a modificar\n\n");//Pide el codigo de la materia que se quiere modificar
			printf("\t Codigo: ");
			scanf(" %d", &(cod));
			if (!(i = validarmat(p, cod)))
				error(4,"no existe ninguna materia con ese codigo\n");//valida primero que la materia a modificar exista
		} while (!i);
		aux = encontrar(p, cod);//encuentra el campo donde se encuentre materia mediante su codigo
		do {//Pide el campo que quiere modificar
			printf("\n\n\t La materia fue encontrada, por favor indique el campo de la materia a modificar\n\n");
			printf("\t1. Nombre \n");
			printf("\t2. Descripcion\n ");
			printf("\t3. Semestre\n ");
			printf("\t4. Creditos \n\n");											
			printf("\tOpcion: ");
			scanf(" %d", &i);
			if ((i >= 1) && (i <= 5))
			{
				system("cls");
				printf("\n\t\t   Ingrese el nuevo dato   \n\n");
			}
			switch (i) 
			{
				case 1:
					printf("\t Nombre: ");
					scanf(" %[^\n]", &(aux->nombre));
					break;
				case 2:printf("\t Descripcion: ");
					scanf(" %[^\n]", &(aux->descripcion));
					break;
				case 3:printf("\t Semestre: ");
					scanf(" %s", &(aux->semestre));
					break;
				case 4:printf("\t Creditos: ");
					scanf(" %d", &(aux->creditos));
					break;
				default:
					error(3, "la opcion no esta disponible");
					break;
			};
		} while ((i<1) || (i>5));
	}
	else
	{
		error(4, "No existen materias");
	}
}

/*<--------------------11. CONSULTAR LA MATERIA-------------------->*/

void consultarMateria(materia*p)
{
	system("cls");
	if (p)
	{
		int vali = 0, i = 0, cod = 0;
		do
		{
			printf("\n\n\t\tConsultar materias\n\n");
			printf("\t1. Visualizar todas las materias\n\n");
			printf("\t2. Visualizar por parametro de busqueda \n\n");
			printf("\tOpcion: ");
			scanf(" %d", &i);
			switch (i)
			{
			case 1:
				system("cls"); 
				encabezadoMat();
				while (p)
				{
					leer(p);
					p = p->sig;
				}
				system("pause");
				break;
			case 2:
				system("cls");
				menuBusquedaMateria(p);
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

