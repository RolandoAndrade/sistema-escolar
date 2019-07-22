/*<--------------------0. ENCABEZADO DE DATOS-------------------->*/

void encabezadoConsultaNotas()
{
	printf("\n____________________________________________________________________________________________________________________________________________________________________________________________\n\n");
	gotox(4);
	printf("CEDULA");
	gotox(37);
	printf("CODIGO");
	gotox(65);
	printf("NOTA");
	printf("\n___________________________________________________________________________________________________________________________________________________________________________________________\n");
}

/*<--------------------1. MOSTRAR EL CONTENIDO DE LOS CAMPOS-------------------->*/

void leerNotasPersona(pasado*p)
{
	if (p)
	{
		gotox(38);
		printf("\t%d", p->codigo);
		gotox(66);
		printf("\t%d\n", p->nota);
		leerNotasPersona(p->sig);
	}

}

void mostrar_notas(persona *p)
{
	int ci = 0;
	persona *t = NULL;
	do
	{
		printf("\n\n\t\t   Consultar notas del estudiante   \n\n");
		printf("\t1. Cedula de identidad: ");
		scanf(" %i", &ci);
		t = encontrarPersona(p, ci);
	} while (!t);
	gotox(5);
	printf("%i", ci);
	encabezadoConsultaNotas();
	leerNotasPersona(t->cant);
	system("pause");
}