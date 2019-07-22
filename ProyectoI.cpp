#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <windows.h> 
#include"Estructuras.h"
#include"Funciones.h"
#include"MMaterias.h"
#include"MCursos.h"
#include"Mestudiantes.h"
#include"Consultas.h"
#include"Restudiantes.h"

/*Menu*/
void menuMat(int i,materia **p,curso **q,persona **r)						//menu para todos los casos de agregar, consultar, modificar y eliminar de las materias, cursos y personas
{
	int j;
	do
	{
		color(1);
		switch (i) {
		case 1:
			printf("\n\tMaterias\t\n\n");
			break;
		case 2:
			printf("\n\tCursos\t\n\n");
			break;
		case 3:
			printf("\n\tPersonas\t\n\n");
			break;
		};
		printf("\t1. Agregar\n");
		printf("\t2. Modificar\n");
		printf("\t3. Consultar\n");
		printf("\t4. Eliminar\n\n");
		printf("\t0. Volver al menu\n\n");
		printf("\tOpcion: ");
		scanf(" %d", &j);
		switch (j) 
		{
			case 1:system("cls");
				switch (i) 
				{
					case 1: agregar_materias(p); break;
					case 2: if ((*p))
								agregar_cursos(q, p);
							else if(!*p)
								error(3, "no hay materias a las cuales asignar curso");
							else
								error(3, "no hay estudiantes suficientes para abrir un curso");
					break;
					case 3:agregar_estudiante(r); break;
				};
				break;
			case 2:
				switch (i) {
				case 1: modificar_materias(*p); break;
				case 2: modificar_cursos(*q, *p); break;
				case 3: modificar_personas(*r); break;
				};
				break;
			case 3:
				switch (i) {
				case 1:consultarMateria(*p); break;
				case 2: consultarCurso(*q); break;
				case 3:consultarEstudiante(*r); break;
				};
				break;
			case 4:
				switch (i) {
				case 1: eliminar_materias(p,q,r); break;
				case 2: eliminar_cursos(q,r); break;
				case 3: eliminar_estudiantes(r); break;
				};
				break;
			case 0: break;
			default:
				error(3,"la opcion no esta disponible");
				system("PAUSE");
				break;
		};
		system("cls");

	} while (j);
}

void menu1(materia **p,curso **q,persona **r)
{
	int i, j;
	do
	{
		color(1);
		printf("\n\n\t\tMANTENIMIENTO\n\n");
		printf("\t1. Materias\n");
		printf("\t2. Cursos\n");
		printf("\t3. Personas\n");
		printf("\t0. Volver al menu\n\n");
		printf("\tOpcion: ");
		scanf(" %d", &i);
		system("cls");
		printf("\n   Opcion %i\n\n", i);
		if (i > 0 && i < 4)
			menuMat(i, p, q,r);
		else if(i!=0)
			error(4, "opcion no disponible");
	} while (i);
}
void menu2(materia **p,curso **q,persona **r)
{
	int i, j;
	do
	{
		system("cls");
		color(1);
		printf("\n\n\t\tREGISTRO DE ESTUDIANTE\n\n");
		printf("\t1. Agregar a un curso\n");
		printf("\t2. Modificar curso inscrito\n");
		printf("\t3. Eliminar registros de cursos anteriores\n");
		printf("\t0. Volver al menu\n\n");
		printf("\tOpcion: ");
		scanf(" %d", &i);
		system("cls");
		printf("\n   Opcion %i\n\n", i);
		if (i < 0 || i > 3)
			error(4, "opcion no disponible");
	} while (i < 0 || i > 3);
	system("cls");
	switch (i)
	{
		case 1:
			agregar_registro(*r, *q);
			break;
		case 2:
			modificar_registro(*r, *q);
			break;
		case 3:
			eliminar_registro(r);
			break;
		default:
			break;
	}
}
void menu3(materia **p, curso **q, persona **r)
{
	int i, j;
	do
	{
		system("cls");
		color(1);
		printf("\n\n\t\tCONSULTAS\n\n");
		printf("\t1. Ver las notas del estudiante\n");
		printf("\t2. \n");
		printf("\t3. \n");
		printf("\t0. Volver al menu\n\n");
		printf("\tOpcion: ");
		scanf(" %d", &i);
		system("cls");
		printf("\n   Opcion %i\n\n", i);
		if (i < 0 || i > 3)
			error(4, "opcion no disponible");
	} while (i < 0 || i > 3);
	system("cls");
	switch (i)
	{
	case 1:
		mostrar_notas(*r);
		break;
	case 2:
		
		break;
	case 3:
		
		break;
	default:
		break;
	}
}
void menup()
{
	materia*p = NULL;
	curso *q = NULL;
	persona  *r = NULL;
	int i;
	do
	{
		color(1);
		printf("\n\n\t\t%c%c%cEL MEJOR CONTROL DE CENTRO EDUCATIVO%c%c%c\n\n", 3, 3, 3, 3, 3, 3);
		printf("\t1. Mantenimiento\n");
		printf("\t2. Registro de estudiante\n");
		printf("\t3. Consultas\n");
		printf("\t0. Salir\n\n");
		printf("\tOpcion: ");
		scanf(" %d", &i);
		switch (i) {
		case 1:
			system("cls");
			menu1(&p,&q,&r);
			break;
		case 2:
			if(p&&q&&r)menu2(&p, &q, &r);
			break;
		case 3:
			if (p&&q&&r)menu3(&p, &q, &r);
			break;
		case 0:break;
		default:
			error(3, "la opcion no esta disponible");
			break;
		};
		system("cls");
	} while (i);
}
void main()
{
	menup();
	system("PAUSE");
}