/*
<----------------------------------------------------->
FUNCIONES ESPECIALES DEL PROGRAMA
I- APARIENCIA
	1.Cambiar los colores de la consola
II- FUNCIONES ABANDONADAS DE LA LIBRERÍA CONIO,
	2. Posición horizontal del cursor.
	3. Posición vertical del cursor.
	4. Mover el cursor en consola.
III. MODIFICACIONES DE LAS FUNCIONES ORIGINALES.
	5. Mover el cursor horizontalmente.
	6. Mover el cursor verticalmente.
IV. ERRORES
	7. Mostrar mensaje de error.
V- FUNCIONES DE VALIDACIÓN
	8. Validar el semestre.
<----------------------------------------------------->	*/

/*<--------------------1. CAMBIAR COLORES-------------------->*/

void color(int c)
{
	switch (c)
	{
	case 1:
		system("color F8");//fondo blanco letras negras
		break;
	case 2:
		system("color F5");//morado
		break;
	case 3:
		system("color F3");//azul
		break;
	case 4:
		system("color F4");//rojo
		break;
	default:
		break;
	}
}

/*<--------------------2. POSICIÓN HORIZONTAL DEL CURSOR (whereX())-------------------->*/

int POSX()
{
	CONSOLE_SCREEN_BUFFER_INFO sbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbi);
	return sbi.dwCursorPosition.X;
}

/*<--------------------3. POSICIÓN VERTICAL DEL CURSOR (whereY())-------------------->*/

int POSY()
{
	CONSOLE_SCREEN_BUFFER_INFO sbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbi);
	return sbi.dwCursorPosition.Y;
}

/*<--------------------4. MOVER EL CURSOR A LA POSICIÓN (x,y)------------------->*/

void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}

/*<--------------------5. MOVER EL CURSOR HORIZONTALMENTE------------------->*/

void gotox(int x)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD pos;
	pos.X = x;
	pos.Y = POSY();
	SetConsoleCursorPosition(hConsole, pos);
}

/*<--------------------6. MOVER EL CURSOR VERTICALMENTE------------------->*/

void gotoy(int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD pos;
	pos.X = POSX();
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}

/*<--------------------7. MENSAJE DE ERROR------------------->*/

void error(int c, char s[])
{
	color(c);
	gotoxy(10, 30);
	printf("\n\n\t\tERROR: %s :(\n", s);
	system("PAUSE");
	color(1);
	system("cls");
}


/*<--------------------8. VALIDAR EL SEMESTRE-------------------->*/

int validasem(char c[])
{
	if (strcmp(c, "I") != 0 && strcmp(c, "II") != 0 && strcmp(c, "III") != 0 && strcmp(c, "IV") != 0 && strcmp(c, "V") != 0 && strcmp(c, "VI") != 0 && strcmp(c, "VII") != 0 && strcmp(c, "VIII") != 0 && strcmp(c, "IX") != 0 && strcmp(c, "X") != 0)
	{
		printf("No existe tal semestre\n");
		color(3);
		return 0;
	}
	return 1;
}
