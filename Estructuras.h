/*AQUÍ SE ENCUENTRAN LAS ESTRUCTURAS A UTILIZAR EN MEMORIA PRINCIPAL*/
struct materia
{
	int codigo;
	char nombre[31];
	char descripcion[101];
	char semestre[5];
	int creditos;
	materia * sig;
};

struct curso
{
	int codigo;
	int cmateria;
	int año;
	int lapso;
	curso *sig;
};
struct rfecha
{
	int dia;
	int mes;
	int year;
};
struct pasado
{
	int codigo;
	int nota;
	pasado *sig;
};
struct persona
{
	long ci;
	char nombre[256];
	rfecha *fecha;
	char direccion[256];
	pasado *cant;
	persona *sig;
};

