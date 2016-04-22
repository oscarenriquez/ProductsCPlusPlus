// Proyecto Seccion A
#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>

/**
**  INICIA PROGRAMA DE CONTROL DE PRODUCTOS, MANEJO DE INVENTARIOS
**  INICIALIZACION DE COSTANTES

SE DEFINE COMO CONSTANTE LOS NOMBRES DE LOS FICHEROS BINARIOS A GUARDAR

**/
const char FACTURAS[] = "facturas.dat", DEVOLUCIONES[] = "devoluciones.dat", OFERTAS[] = "ofertas.dat", INVENTARIOS[] = "inventario.dat";
const char CREAR[] = "wb", AGREGAR[] = "ab", CONSULTAR[] = "rb";
// Primero estableceremos los menus estos fueron los que son mas necesarios dado que la consulta de precio puede ir en invetario
// se los dejo a su criterio
/**
** FUNCIONES DE APLICACION
**/
void menu ();
void facturacion (FILE *facfichero);
void devolucion (FILE *devfichero);
void ofertas (FILE *offichero);
void invetario (FILE *invfichero);

/**
** FUNCION DE FICHERO
**/
FILE *abrirFichero(const char fichero[],const char tipo[]){
    FILE *x = fopen(fichero, tipo);
    if(x == NULL || !fichero){
        x = fopen(fichero, CREAR);
    }
    return x;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//ESTRUCTURA
//Ahora se crea cada una de las estructuras en base a la info que envio oscar
//revisenla por si hace falta algo
struct producto
	{
	int producto_id [15];
	char nombre_producto [50];
	char descripcion [200];
	int unidades [50];
	int estado [1];
	};
//Algunas estructuras no creo que necesitan tanta informacion solo la mas ensencial
struct inventario
	{
	int inventario_id [15];
	int producto_id [15];
	float precio_costo;
	int cantidad [15];
	};
struct oferta
	{
	int oferta_id [15];
	char nombre_oferta [50];
	char descripcion [200];
	float porcentaje;
	int estado;
	};
//Lo deje comentariado porque pienso que solo deberiamos manejar un inventario y no tener dos
//struct inventario_oferta
//	{
//	int invetario_oferta [15];
//	int oferta [15];
//	};
struct transaccion
	{
	int transaccion_id [15];
//con que ingresen el codigo de vendedor nos ahorramos otra estructura y ademas es valido
	int codigo_vendedor [10];
	double cliente_id [25];
	int empleado_id [15];
//tambien creo que no es necesaria la estructura de forma de pago lo dejo a su eleccion
	int tipo_pago [15];
	float monto_total;
	};
struct cliente
	{
	double cliente_id [25];
	char nombre [100];
	char apellidos [100];
	int telefono [14];
	char direccion [100];
	};
//tambien creo que esta estructura tambien puede ir unida a transacion asi de una vez se llenan ambos
struct fac_detalle
	{
	int fac_det_id [15];
	int inventario [15];
	int cantidad [15];
	int sub_total [15];
	};
struct devoluciones
	{
	int devolucion_id [15];
	int transaccion_id [15];
	int inventario_id [15];
	int cantidad [15];
	float total;
	};
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//MENU
int main()
{
        //Ficheros
        FILE *devfichero;// Devoluciones
        FILE *facfichero;// Facturas
        FILE *offichero;// Ofertas
        FILE *invfichero;// Inventarios
        int opcion;
        int exit = 0;
        while (!exit)
        {
                menu();
                cout <<" \nOpcion: ";
                cin >>opcion;
                switch(opcion)
                {
                        case 1:
                        facturacion(facfichero);
                        break;
                        case 2:
                        devolucion(devfichero);
                        break;
                        case 3:
                        ofertas(offichero);
                        break;
                        case 5:
                        invetario(invfichero);
                        break;
                        case 6:
                        exit = 1;
                        default:
                        cout <<"\n Opcion no valida!!!";
                }
        }
        return 0;
}
void menu()
{
        cout <<"\nMenu:";
        cout <<"\n\t1. Facturacion";
        cout <<"\n\t2. Devoluciones";
        cout <<"\n\t3. Ofertas";
        cout <<"\n\t4. Inventario";
        cout <<"\n\t5. Salir";
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//FACTURACION
void facturacion (FILE *facfichero)
{//Priemro seria crear el fichero luego empezar el proceso de facturacion
    facfichero = abrirFichero(FACTURAS, AGREGAR);

    fclose(facfichero);
}

void devolucion (FILE *devfichero){
    devfichero = abrirFichero(DEVOLUCIONES, AGREGAR);

    fclose(devfichero);
}

void ofertas (FILE *offichero) {
    offichero = abrirFichero(OFERTAS, AGREGAR);

    fclose(offichero);
}

void invetario (FILE *invfichero) {
    invfichero = abrirFichero(INVENTARIOS, AGREGAR);

    fclose(invfichero);
}
