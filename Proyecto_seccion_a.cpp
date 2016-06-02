// Proyecto Seccion A
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <cctype>
#include <fstream>

using namespace std;

/**
**  INICIA PROGRAMA DE CONTROL DE PRODUCTOS, MANEJO DE INVENTARIOS
**  INICIALIZACION DE COSTANTES

SE DEFINE COMO CONSTANTE LOS NOMBRES DE LOS FICHEROS BINARIOS A GUARDAR

**/
char FACTURAS[] = "facturas.dat",
	 FACTURAS_DET[] = "facturasDetalle.dat",
	 DEVOLUCIONES[] = "devoluciones.dat",
	 OFERTAS[] = "ofertas.dat",
	 INVENTARIOS[] = "inventario.dat",
	 PRODUCTOS[] = "productos.dat",
	 CLIENTES[] = "clientes.dat";

char CREAR[] = "wb",
     AGREGAR[] = "ab",
     CONSULTAR[] = "rb",
     ELIMINAR[] = "rb+";

char auxiliar[2];

// Primero estableceremos los menus estos fueron los que son mas necesarios dado que la consulta de precio puede ir en invetario
// se los dejo a su criterio
/**
 ** FUNCIONES DE APLICACION
 **/
void menu();
void sub_menu_pago();
void sub_menu_devolucion();
void sub_menu_crud();
void sub_menu_default();

void leer_comando_devolucion();
void leer_comando_crud(int tipo);

void crear_oferta();
void consultar_oferta();
void eliminar_oferta();

void crear_inventario();
void consultar_inventario();
void eliminar_inventario();

void crear_producto();
void consultar_producto();
void eliminar_producto();

void crear_cliente();
void consultar_cliente();
void eliminar_cliente();

void crear_pago();
void crear_devolucion();
void consultar_devolucion();

int generarNuevoId(char nombre_fichero[], long int size_bytes);
void mostrar_reporte_pagos();

/**
 ** FUNCION DE FICHERO abrirFichero
 **/
FILE *abrirFichero(char fichero[]) {
    FILE *x = fopen(fichero, AGREGAR);
    if (x == NULL || !x) {
        x = fopen(fichero, CREAR);
    }
    return x;
}

/**
 ** FUNCION DE FICHERO consultarFichero
 **/
FILE *consultarFichero(char fichero[]) {
    FILE *x = fopen(fichero, CONSULTAR);
    if (x == NULL || !x) {
        x = fopen(fichero, CREAR);
        fclose(x);
        x = fopen(fichero, CONSULTAR);
    }
    return x;
}

/**
 ** FUNCION DE FICHERO eliminarFichero
 **/
FILE *eliminarFichero(char fichero[]) {
    FILE *x = fopen(fichero, ELIMINAR);
    if (x == NULL || !x) {
        x = fopen(fichero, CREAR);
        fclose(x);
        x = fopen(fichero, ELIMINAR);
    }
    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//ESTRUCTURA
//Ahora se crea cada una de las estructuras en base a la info que envio oscar
//revisenla por si hace falta algo
struct producto {
    int producto_id;
    char nombre_producto[50];
    char descripcion[50];    
    int estado;
} pro;

typedef struct producto PR;

struct inventario {
    int inventario_id;
    PR producto;// ESTRUCTURA ANIDADA
    float precio_costo;
    int estado;
    int cantidad;
}inv;

typedef struct inventario IV;

struct oferta {
    int oferta_id;
    IV inventario;// ESTRUCTURA ANIDADA
    char nombre_oferta[50];
    char descripcion[50];
    float porcentaje;
    int estado;
}ofe;

typedef struct oferta OF;

struct fac_detalle {
    int fac_det_id;
    IV inventario;// ESTRUCTURA ANIDADA
    int cantidad;
    float sub_total;    
}fad;

typedef struct fac_detalle FD;

struct NodeFacDetalle {
	fac_detalle valor;
	NodeFacDetalle *siguiente;
} nodo;

struct ListaFacDetalle {
    NodeFacDetalle *inicio;
    NodeFacDetalle *fin;
    int tamanio;
} lista;

typedef struct ListaFacDetalle LIST;

struct cliente {
    int cliente_id;
    char nombres[100];
    char apellidos[100];
    int telefono;
    char direccion[100];
}cli;

typedef struct cliente CL;

struct referencia {
    	int detalle_id;
    	int tamanio;
} ref;

typedef struct referencia RF;

struct transaccion {
    int transaccion_id;
    int codigo_vendedor;
    CL cliente; // ESTRUCTURA ANIDADA
    int tipo_pago;
    int cod_trx;
    float monto_total;
    RF detalles;
}tra;

typedef struct transaccion TR;

struct devoluciones {
    int devolucion_id;
    int transaccion_id;
    IV inventario;
    int cantidad;
    float total;
}dev;

typedef struct devoluciones DV;

void crear_detalle(int num_art);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//MENU
int main() {
    //Ficheros
    system("color 1B");

    int opcion;
    int exit = 0;
    while (!exit) {
        menu();
        cin >> opcion;

		system("cls"); // limpiamos la pantalla

		switch (opcion) {
            case 1:
            	cout << "\n\t=======// FACTURACION //=======";
                sub_menu_pago();
				sub_menu_default();
                crear_pago();
                break;
            case 2:
            	cout << "\n\t=======// REPORTE PAGOS //=======";
            	mostrar_reporte_pagos();
            	break;
			case 3:
            	cout << "\n\t=======// DEVOLUCIONES //=======";
                sub_menu_devolucion();
                sub_menu_default();
                leer_comando_devolucion();
                break;
            case 4:            	
                cout << "\n\t=======// CLIENTE //=======";
                sub_menu_crud();
                sub_menu_default();
                leer_comando_crud(opcion);
                break;
            case 5:
            	cout << "\n\t=======// PRODUCTOS //=======";
                sub_menu_crud();
                sub_menu_default();
                leer_comando_crud(opcion);
                break;
            case 6:
            	cout << "\n\t=======// INVENTARIO //=======";
                sub_menu_crud();
                sub_menu_default();
                leer_comando_crud(opcion);
                break;
            case 7:
            	cout << "\n\t=======// OFERTAS //=======";
                sub_menu_crud();
                sub_menu_default();
                leer_comando_crud(opcion);
                break;
            case 8:
                exit = 1;                
                break;
            default:
                cout << "\n Opcion no valida!!!";
                system("pause");
        }
    }
    return 0;
}
void menu() {
    system("cls");
    cout << "\nMENU:";
    cout << "\n\t1. Facturacion";
    cout << "\n\t2. Reporte de Ventas";
    cout << "\n\t3. Devoluciones";
    cout << "\n\t4. Cliente";
    cout << "\n\t5. Productos";        
    cout << "\n\t6. Inventario";
    cout << "\n\t7. Ofertas";
    cout << "\n\t8. Salir";
    cout << "\n\n   OPCION: ";
}

void sub_menu_default(){
	cout << "\n\n\t-------------------------------";
	cout << "\n\t0.\t<-- Volver a menu!";
	cout << "\n\n\t\t    OPCION: ";
}

void sub_menu_pago(){
	cout << "\n\t1.\tPago efectivo";
	cout << "\n\t2.\tPago tarjeta";
	cout << "\n\t3.\tPago cheque";
}

void sub_menu_devolucion(){
	cout << "\n\t1.\tRealizar reversa o devolucion";
	cout << "\n\t2.\tConsultar devolucion";
}

void sub_menu_crud(){
	cout << "\n\t1.\tCrear";
	cout << "\n\t2.\tConsultar";
	cout << "\n\t3.\tEliminar";
}

void leer_comando_devolucion(){
	int comando;
	cin >> comando;
	cout << "\n\n";
	
	switch(comando) {
		case 1:
			crear_devolucion();
			break;
		case 2:
			consultar_devolucion();
			break;
	}
}

void leer_comando_crud(int tipo){
	int comando;
	cin >> comando;

	cout << "\n\n";

	switch(comando){
		case 1:
			switch(tipo){				
				case 4:
					crear_cliente();
					break;
				case 5:
					crear_producto();
					break;
				case 6:
					crear_inventario();
					break;
				case 7:
					crear_oferta();
					break;	
			}
			break;
		case 2:
			switch(tipo){
				case 4:
					consultar_cliente();
					break;
				case 5:
					consultar_producto();
					break;
				case 6:
					consultar_inventario();
					break;
				case 7:
					consultar_oferta();
					break;
			}
			break;
		case 3:
			switch(tipo){
				case 4:
					eliminar_cliente();
					break;
				case 5:
					eliminar_producto();
					break;
				case 6:
					eliminar_inventario();
					break;
				case 7:
					eliminar_oferta();
					break;
			}
			break;
	}
}

int generarNuevoId(char nombre_fichero[], long int dir_fisica) {
	FILE *consultar = consultarFichero(nombre_fichero);
    fseek(consultar, 0, SEEK_END);
    int nuevo_id = ftell(consultar) / dir_fisica;
    nuevo_id++;
    fclose(consultar);
    return nuevo_id;
}

// Metodos para el CRUD de oferta
void crear_oferta(){  
    int num_inv = generarNuevoId(OFERTAS, sizeof(OF));// Se crea nuevo id para el documento        
    int inventario_id = 0;	
	cout << "Ingrese el numero de inventario: "; cin >> inventario_id;
	
	FILE *inventarios = consultarFichero(INVENTARIOS);
	long int dir_fisica = (inventario_id - 1)*sizeof(IV);
	fseek(inventarios, dir_fisica, SEEK_SET);
	fread(&inv, sizeof(IV), 1, inventarios);
	fclose(inventarios);
	
	if(inv.inventario_id == inventario_id) {
		cout << "Ingrese el nombre de la oferta: "; cin.ignore(); gets(ofe.nombre_oferta);
	    cout << "Ingrese la descripcion de la oferta: "; gets(ofe.descripcion);
	    cout << "Ingrese el porcentaje de descuento: "; cin >> ofe.porcentaje;
	    ofe.inventario = inv;
	    ofe.estado = 1;
	    ofe.oferta_id = num_inv;
	    cout << "\n\nID creado " << num_inv << endl;
	
		FILE *archivo = abrirFichero(OFERTAS);
	    dir_fisica = num_inv*sizeof(OF);
	    fseek(archivo, dir_fisica, SEEK_SET);
	    fwrite(&ofe, sizeof(OF), 1, archivo);
	    fclose(archivo);
	
	    cin.clear();
	    cout << "----------- REGISTRO GUARDADO -----------!!" << endl;
	} else {
		cout << "\t!!!!!!! Este inventario no existe, verifique y vuelva a intentar  !!!!!  " << endl;
	}
	
    system("pause");
}
void consultar_oferta(){
    char r;
    int id;
    long int dir_fisica;
    cout << "¿Desea consultar una Oferta en especifico? [S/N]: "; cin >> r;

    FILE *archivo = consultarFichero(OFERTAS);
    if(tolower(r)=='s'){
        cout << "Ingrese el numero de oferta: "; cin >> id;
        if(id > 0){
            dir_fisica = (id - 1)*sizeof(OF);
            fseek(archivo, dir_fisica, SEEK_SET);
            fread(&ofe, sizeof(OF), 1, archivo);
            if(ofe.oferta_id == id){
                printf("\n\r%4s\t%10s\t%-15s\t%-25s\t%9s\t%6s", "ID", "INVENTARIO", "NOMBRE", "DESCRIPCION", "DESCUENTO", "ESTADO");
                printf("\n\r%4d\t%10d\t%-15s\t%-25s\t%9.2f\t%6d", ofe.oferta_id, ofe.inventario.inventario_id, ofe.nombre_oferta, ofe.descripcion, ofe.porcentaje, ofe.estado);
            } else {
                cout << "\nOferta no existe verifique!!";
            }
        } else {
            cout << "\nNumero de oferta invalido!!";
        }
    } else {
        printf("\n\r%4s\t%10s\t%-15s\t%-25s\t%9s\t%6s", "ID", "INVENTARIO", "NOMBRE", "DESCRIPCION", "DESCUENTO", "ESTADO");
        fread(&ofe, sizeof(OF), 1, archivo);
        while(!feof(archivo)){
            if(ofe.oferta_id > 0)
                printf("\n\r%4d\t%10d\t%-15s\t%-25s\t%9.2f\t%6d", ofe.oferta_id, ofe.inventario.inventario_id, ofe.nombre_oferta, ofe.descripcion, ofe.porcentaje, ofe.estado);

            fread(&ofe, sizeof(OF), 1, archivo);
        }
    }

    fclose(archivo);
    cout << "\n\n<<<<<<<<<< ultima linea de consulta >>>>>>>>>!!"<<endl;
    system("pause");
}
void eliminar_oferta(){
    char r;
    int id;
    long int dir_fisica;
    cout << "\n\rBAJA LOGICA DE REGISTRO DE OFERTA" << endl;
    cout << "\n\rIngrese el numero de oferta: "; cin >> id;
    if(id > 0){
        FILE *archivo = eliminarFichero(OFERTAS);
        dir_fisica = (id - 1)*sizeof(OF);
        fseek(archivo, dir_fisica, SEEK_SET);
        fread(&ofe, sizeof(OF), 1, archivo);
        if(ofe.oferta_id == id){
            printf("\n\r%4s\t%10s\t%-15s\t%-25s\t%9s\t%6s", "ID", "INVENTARIO", "NOMBRE", "DESCRIPCION", "DESCUENTO", "ESTADO");
            printf("\n\r%4d\t%10d\t%-15s\t%-25s\t9.2f%\t%6d", ofe.oferta_id, ofe.inventario.inventario_id, ofe.nombre_oferta, ofe.descripcion, ofe.porcentaje, ofe.estado);
            cout << "\n\n¿Esta seguro de eliminar este registro? [S/N] "; cin >> r;
            if(tolower(r) == 's'){
                ofe.oferta_id = 0;                
                ofe.estado = 0;
                ofe.porcentaje = 0.0;
                strcpy(ofe.nombre_oferta, "");
                strcpy(ofe.descripcion, "");

                rewind(archivo);

                fseek(archivo, dir_fisica, SEEK_SET);
                fwrite(&ofe, sizeof(OF), 1, archivo);

                cout << "\n\t===== REGISTRO ELIMINADO =========="<<endl;
                system("pause");
            }
        } else {
            cout << "\nOferta no existe verifique!!";
        }

        fclose(archivo);
    } else {
        cout << "\nNumero de oferta invalido!!";
    }
}
// Metodos para el CRUD de inventario
void crear_inventario(){
    int num_inv = generarNuevoId(INVENTARIOS, sizeof(IV));// Se crea nuevo id para el documento
	int producto_id = 0;
	
	cout << "Ingrese el numero de producto: "; cin >> producto_id;
	
	// se inicia busqueda para el producto ACCESO DIRECTO
	FILE *productos = consultarFichero(PRODUCTOS);
	long int dir_fisica = (producto_id - 1)*sizeof(PR);
    fseek(productos, dir_fisica, SEEK_SET);
    fread(&pro, sizeof(PR), 1, productos);
    fclose(productos);
    
    if(pro.producto_id == producto_id) {
    	cout << "Ingrese el precio del producto: "; cin >> inv.precio_costo;
	    cout << "Ingrese la cantidad de articulos: "; cin >> inv.cantidad;
	    inv.producto = pro;
	    inv.inventario_id = num_inv;
	    inv.estado = 1;
	    cout << "\n\nID creado " << num_inv << endl;
	
		FILE *archivo = abrirFichero(INVENTARIOS);// Se abre el archivo en modo escritura
	    dir_fisica = num_inv*sizeof(IV);// Se obtiene la nueva direccion de memoria
	    fseek(archivo, dir_fisica, SEEK_SET);// Se direcciona el puntero
	    fwrite(&inv, sizeof(IV), 1, archivo);// Se escribe en el archivo
	    fclose(archivo);

    	cout << "----------- REGISTRO GUARDADO -----------!!" << endl;
    } else {
    	cout << "\t!!!!!!! Este producto no existe, verifique y vuelva a intentar  !!!!!  " << endl;
    }	    
    system("pause");
}
void consultar_inventario(){
	char r;
    int id;
    long int dir_fisica;
    cout << "¿Desea consultar un Inventario en especifico? [S/N]: "; cin >> r;

    FILE *archivo = consultarFichero(INVENTARIOS);
    if(tolower(r)=='s'){
        cout << "Ingrese el numero de inventario: "; cin >> id;
        if(id > 0){
            dir_fisica = (id - 1)*sizeof(IV);
            fseek(archivo, dir_fisica, SEEK_SET);
            fread(&inv, sizeof(IV), 1, archivo);
            if(inv.inventario_id == id){
            	char estado[12] = "DISPONIBLE";
            	if(inv.estado==0)
            		strcpy(estado, "AGOTADO");
            		
                printf("\n\r%4s\t%-15s\t%9s\t%8s\t%-10s", "ID", "PRODUCTO", "PRECIO", "CANTIDAD", "ESTADO");
                printf("\n\r%4d\t%-15s\t%9.2f\t%8d\t%-10s", inv.inventario_id, inv.producto.nombre_producto, inv.precio_costo, inv.cantidad, estado);
            } else {
                cout << "\Inventario no existe verifique!!";
            }
        } else {
            cout << "\nNumero de inventario invalido!!";
        }
    } else {
        printf("\n\r%4s\t%-15s\t%9s\t%8s\t%-10s", "ID", "PRODUCTO", "PRECIO", "CANTIDAD", "ESTADO");
        fread(&inv, sizeof(IV), 1, archivo);
        while(!feof(archivo)){
        	char estado[12] = "DISPONIBLE";
        	if(inv.estado==0)
        		strcpy(estado, "AGOTADO");
            		
            if(inv.inventario_id > 0)
                printf("\n\r%4d\t%-15s\t%9.2f\t%8d\t%-10s", inv.inventario_id, inv.producto.nombre_producto, inv.precio_costo, inv.cantidad, estado);

            fread(&inv, sizeof(IV), 1, archivo);
        }
    }

    fclose(archivo);
    cout << "\n\n<<<<<<<<<< ultima linea de consulta >>>>>>>>>!!"<<endl;
    system("pause");
}
void eliminar_inventario(){
    char r;
    int id;
    long int dir_fisica;
    cout << "\n\rBAJA LOGICA DE REGISTRO DE INVENTARIO" << endl;
    cout << "\n\rIngrese el numero de inventario: "; cin >> id;
    if(id > 0){
        FILE *archivo = eliminarFichero(INVENTARIOS);
        dir_fisica = (id - 1)*sizeof(IV);
        fseek(archivo, dir_fisica, SEEK_SET);
        fread(&inv, sizeof(IV), 1, archivo);
        if(inv.inventario_id == id){
            printf("\n\r%4s\t%-15s\t%9s\t%8s", "ID", "PRODUCTO", "PRECIO", "CANTIDAD");
            printf("\n\r%4d\t%-15s\t%9.2f\t%8d", inv.inventario_id, inv.producto.nombre_producto, inv.precio_costo, inv.cantidad);
            cout << "\n\n¿Esta seguro de eliminar este registro? [S/N] "; cin >> r;
            if(tolower(r) == 's'){
                inv.inventario_id = 0;
                inv.cantidad = 0;
                inv.precio_costo = 0;

                rewind(archivo);

                fseek(archivo, dir_fisica, SEEK_SET);
                fwrite(&inv, sizeof(IV), 1, archivo);

                cout << "\n\t===== REGISTRO ELIMINADO =========="<<endl;
                system("pause");
            }
        } else {
            cout << "\Inventario no existe verifique!!";
        }

        fclose(archivo);
    } else {
        cout << "\nNumero de inventario invalido!!";
    }
}
// Metodos para el CRUD de producto
void crear_producto(){
    int num_inv = generarNuevoId(PRODUCTOS, sizeof(PR));// Se crea nuevo id para el documento

	FILE *archivo = abrirFichero(PRODUCTOS);

	cout << "Ingrese el nombre del producto: "; cin.ignore(); gets(pro.nombre_producto);
    cout << "Ingrese la descripcion del producto: "; gets(pro.descripcion);    
    pro.estado = 1;
    pro.producto_id = num_inv;
    cout << "\n\nID creado " << num_inv << endl;

    long int dir_fisica = num_inv*sizeof(PR);
    fseek(archivo, dir_fisica, SEEK_SET);
    fwrite(&pro, sizeof(PR), 1, archivo);
    fclose(archivo);

    cin.clear();
    cout << "----------- REGISTRO GUARDADO -----------!!" << endl;
    system("pause");
}
void consultar_producto(){
	char r;
    int id;
    long int dir_fisica;
    cout << "¿Desea consultar un Producto en especifico? [S/N]: "; cin >> r;

    FILE *archivo = consultarFichero(PRODUCTOS);
    if(tolower(r)=='s'){
        cout << "Ingrese el numero de producto: "; cin >> id;
        if(id > 0){
            dir_fisica = (id - 1)*sizeof(PR);
            fseek(archivo, dir_fisica, SEEK_SET);
            fread(&pro, sizeof(PR), 1, archivo);
            if(pro.producto_id == id){
                printf("\n\r%4s\t%-20s\t%-35s\t%6s", "ID", "NOMBRE", "DESCRIPCION", "ESTADO");
                printf("\n\r%4d\t%-20s\t%-35s\t%6d", pro.producto_id, pro.nombre_producto, pro.descripcion, pro.estado);
            } else {
                cout << "\nProducto no existe verifique!!";
            }
        } else {
            cout << "\nNumero de producto invalido!!";
        }
    } else {
        printf("\n\r%4s\t%-20s\t%-35s\t%6s", "ID", "NOMBRE", "DESCRIPCION", "ESTADO");
        fread(&pro, sizeof(PR), 1, archivo);
        while(!feof(archivo)){
            if(pro.producto_id > 0)
                printf("\n\r%4d\t%-20s\t%-35s\t%6d", pro.producto_id, pro.nombre_producto, pro.descripcion, pro.estado);

            fread(&pro, sizeof(PR), 1, archivo);
        }
    }

    fclose(archivo);
    cout << "\n\n<<<<<<<<<< ultima linea de consulta >>>>>>>>>!!"<<endl;
    system("pause");
}
void eliminar_producto(){
    char r;
    int id;
    long int dir_fisica;
    cout << "\n\rBAJA LOGICA DE REGISTRO DE PRODUCTO" << endl;
    cout << "\n\rIngrese el numero de producto: "; cin >> id;
    if(id > 0){
        FILE *archivo = eliminarFichero(PRODUCTOS);
        dir_fisica = (id - 1)*sizeof(PR);
        fseek(archivo, dir_fisica, SEEK_SET);
        fread(&pro, sizeof(PR), 1, archivo);
        if(pro.producto_id == id){
            printf("\n\r%4s\t%-20s\t%-35s\t%6s", "ID", "NOMBRE", "DESCRIPCION", "ESTADO");
            printf("\n\r%4d\t%-20s\t%-35s\t%6d", pro.producto_id, pro.nombre_producto, pro.descripcion, pro.estado);
            cout << "\n\n¿Esta seguro de eliminar este registro? [S/N] "; cin >> r;
            if(tolower(r) == 's'){
                pro.producto_id = 0;                
                pro.estado = 0;
                strcpy(pro.nombre_producto, "");
                strcpy(pro.descripcion, "");

                rewind(archivo);

                fseek(archivo, dir_fisica, SEEK_SET);
                fwrite(&pro, sizeof(PR), 1, archivo);

                cout << "\n\t===== REGISTRO ELIMINADO =========="<<endl;
                system("pause");
            }
        } else {
            cout << "\nProducto no existe verifique!!";
        }

        fclose(archivo);
    } else {
        cout << "\nNumero de producto invalido!!";
    }
}
// Metodos para el CRUD de cliente
void crear_cliente(){
    int num_inv = generarNuevoId(CLIENTES, sizeof(CL));// Se crea nuevo id para el documento

	FILE *archivo = abrirFichero(CLIENTES);

	cout << "Ingrese los nombre del cliente: ";cin.ignore(); gets(cli.nombres);
    cout << "Ingrese los apellidos del cliente: "; gets(cli.apellidos);
	cout << "Ingrese el numero de telefono: "; cin >> cli.telefono;
    cout << "Ingrese la direccion: ";cin.ignore(); gets(cli.direccion);
    cli.cliente_id = num_inv;
    cout << "\n\nID creado " << num_inv << endl;

    long int dir_fisica = num_inv*sizeof(CL);
    fseek(archivo, dir_fisica, SEEK_SET);
    fwrite(&cli, sizeof(CL), 1, archivo);
    fclose(archivo);

    cin.clear();
    cout << "----------- REGISTRO GUARDADO -----------!!" << endl;
    system("pause");
}
void consultar_cliente(){
	char r;
    int id;
    long int dir_fisica;
    cout << "¿Desea consultar un Cliente en especifico? [S/N]: "; cin >> r;

    FILE *archivo = consultarFichero(CLIENTES);
    if(tolower(r)=='s'){
        cout << "Ingrese el numero de cliente: "; cin >> id;
        if(id > 0){
            dir_fisica = (id - 1)*sizeof(CL);
            fseek(archivo, dir_fisica, SEEK_SET);
            fread(&cli, sizeof(CL), 1, archivo);
            if(cli.cliente_id == id){
                printf("\n\r%4s\t%-20s\t%-20s\t%-10s\t%-20s", "ID", "NOMBRES", "APELLIDOS", "TELEFONO", "DIRECCION");
                printf("\n\r%4d\t%-20s\t%-20s\t%-10d\t%-20s", cli.cliente_id, cli.nombres, cli.apellidos, cli.telefono, cli.direccion);
            } else {
                cout << "\nCliente no existe verifique!!";
            }
        } else {
            cout << "\nNumero de cliente invalido!!";
        }
    } else {
        printf("\n\r%4s\t%-20s\t%-20s\t%-10s\t%-20s", "ID", "NOMBRES", "APELLIDOS", "TELEFONO", "DIRECCION");
        fread(&cli, sizeof(CL), 1, archivo);
        while(!feof(archivo)){
            if(cli.cliente_id > 0)
                printf("\n\r%4d\t%-20s\t%-20s\t%-10d\t%-20s", cli.cliente_id, cli.nombres, cli.apellidos, cli.telefono, cli.direccion);

            fread(&cli, sizeof(CL), 1, archivo);
        }
    }

    fclose(archivo);
    cout << "\n\n<<<<<<<<<< ultima linea de consulta >>>>>>>>>!!"<<endl;
    system("pause");
}
void eliminar_cliente(){
    char r;
    int id;
    long int dir_fisica;
    cout << "\n\rBAJA LOGICA DE REGISTRO DE CLIENTE" << endl;
    cout << "\n\rIngrese el numero de cliente: "; cin >> id;
    if(id > 0){
        FILE *archivo = eliminarFichero(CLIENTES);
        dir_fisica = (id - 1)*sizeof(CL);
        fseek(archivo, dir_fisica, SEEK_SET);
        fread(&cli, sizeof(CL), 1, archivo);
        if(cli.cliente_id == id){
            printf("\n\r%-4s\t%-20s\t%-20s\t%-10s\t%-20s", "ID", "NOMBRES", "APELLIDOS", "TELEFONO", "DIRECCION");
            printf("\n\r%4d\t%-20s\t%-20s\t%-10d\t%-20s", cli.cliente_id, cli.nombres, cli.apellidos, cli.telefono, cli.direccion);
            cout << "\n\n¿Esta seguro de eliminar este registro? [S/N] "; cin >> r;
            if(tolower(r) == 's'){
                cli.cliente_id = 0;
                cli.telefono = 0;
                strcpy(cli.nombres, "");
                strcpy(cli.apellidos, "");
                strcpy(cli.direccion, "");

                rewind(archivo);

                fseek(archivo, dir_fisica, SEEK_SET);
                fwrite(&cli, sizeof(CL), 1, archivo);
                cout << "\n\t===== REGISTRO ELIMINADO =========="<<endl;
                system("pause");
            }
        } else {
            cout << "\nCliente no existe verifique!!";
        }

        fclose(archivo);
    } else {
        cout << "\nNumero de cliente invalido!!";
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//FACTURACION
void crear_pago() {//Priemro seria crear el fichero luego empezar el proceso de facturac
	int num_inv = generarNuevoId(FACTURAS, sizeof(TR));// Se crea nuevo id para el documento

    float monto_total = 0.0;
    int tipo_pago = 0, num_art= 0, producto_id = 0, cliente_id;

    cin >> tipo_pago;
	tra.tipo_pago = tipo_pago;
	tra.cod_trx = 1;
	cout << "\n\n\t<============INICIA FACTURACION===========>" << endl;
	cout << "\n\tIngrese el cod. de cliente: "; cin >> cliente_id;
	
	FILE *clientes = consultarFichero(CLIENTES);
	long int dir_fisica = (cliente_id - 1)*sizeof(CL);
	fseek(clientes, dir_fisica, SEEK_SET);
	fread(&cli, sizeof(CL), 1, clientes);
	fclose(clientes);
	
	if(cli.cliente_id == cliente_id){
		
		cout << "\t==> " << cli.nombres << " " << cli.apellidos;
	
		cout << "\n\tIngrese el codigo de vendedor: "; cin >> tra.codigo_vendedor;	
		cout << "\n\n\tDETALLE DE LA TRANSACCION ";
		cout << "\n\n\t===>>> POR FAVOR INGRESE EL NUMERO DE ARTICULOS: "; cin >> num_art;
		cout << "\t===================================================== " << endl << endl;
	
	    crear_detalle(num_art);
	
	    if(lista.tamanio > 0){
	        NodeFacDetalle *cursor;
	        cursor = lista.inicio;
	        monto_total += cursor->valor.sub_total;
	        
	        int detalle_id = 0, fac_det_id = 0;
			detalle_id = fac_det_id = generarNuevoId(FACTURAS_DET, sizeof(FD));	        
	        FILE *facdetalles = abrirFichero(FACTURAS_DET);
	        fseek(facdetalles, (fac_det_id * sizeof(FD)), SEEK_SET);
	        fwrite(&(cursor->valor), sizeof(FD), 1, facdetalles);
	        fac_det_id++;
	        while(cursor->siguiente != NULL){
	            cursor = cursor->siguiente;
	            monto_total += cursor->valor.sub_total;
	            fseek(facdetalles, (fac_det_id * sizeof(FD)), SEEK_SET);
	            fwrite(&cursor->valor, sizeof(FD), 1, facdetalles);
	            fac_det_id++;
	        }
	        fclose(facdetalles);
	        char r;
	        printf("\n\n\t===>>> EL TOTAL DE LA FACTURA ES DE Q. %4.2f, Desea continuar? [S/N] : ", monto_total); cin >> r;
	
	        if(tolower(r) == 's'){
	            tra.detalles.tamanio = lista.tamanio;
				tra.detalles.detalle_id = detalle_id;	        
	            tra.monto_total = monto_total;
	            tra.transaccion_id = num_inv;
	            tra.cliente = cli;
	            
	            FILE *facfichero = abrirFichero(FACTURAS);
	            fseek(facfichero, (num_inv*sizeof(TR)), SEEK_SET);
	            fwrite(&tra, sizeof(TR), 1, facfichero);
	            fclose(facfichero);
	            
	            cout << "\n\n\tID creado " << num_inv << endl;
	            cout << "\n\n\tTransaccion exitosa!!" << endl;	            
	        }
	    }
	} else {
		cout << "\t!!!!!!! Este Cliente no existe, verifique y vuelva a intentar  !!!!!  " << endl;
	}
	system("pause");
}
void crear_detalle(int num_art){
    lista.tamanio = 0;
    FILE *inventarios = consultarFichero(INVENTARIOS);

    NodeFacDetalle *root;
	NodeFacDetalle *conductor;

	root = NULL;
	conductor = NULL;

    int index = 1, producto_id;
    bool existe = false;

	cout << "\nNo. " << index << "\n\t===>>> Ingrese el numero de producto: "; cin >> producto_id;

    rewind(inventarios);
	fread(&inv, sizeof(IV), 1, inventarios);

	while(!feof(inventarios)){
        if(inv.producto.producto_id == producto_id){
            existe = true;
            cout << "\t==> " << inv.producto.nombre_producto << ", Precio: " << inv.precio_costo;
            break;
        }
        fread(&inv, sizeof(IV), 1, inventarios);
	}

	while(!existe){
        cout << "\t!!!!!!! Este producto no existe en el inventario, Ingrese nuevamente o \"0\" para salir: "; cin >> producto_id;
        if(producto_id == 0){
            break;
        }

        rewind(inventarios);
        fread(&inv, sizeof(IV), 1, inventarios);

        while(!feof(inventarios)){
            if(inv.producto.producto_id == producto_id){
                existe = true;
                cout << "\t==> " << inv.producto.nombre_producto << ", Precio: " << inv.precio_costo;
                break;
            }
            fread(&inv, sizeof(IV), 1, inventarios);
        }
	}

    if(existe){        
        cout << "\n\t===>>> Ingrese el total de articulos: "; cin >> fad.cantidad;
        fad.sub_total = inv.precio_costo * fad.cantidad;
        fad.fac_det_id = index;
        fad.inventario = inv;
        
        root = new NodeFacDetalle;
		root->valor = fad;       
        root->siguiente = NULL;
        
        lista.inicio = root;
        lista.fin = root;
        lista.tamanio++;
        index++;

        for(int i = 0; i < (num_art - 1); i++){
            existe = false;

            cout << "\nNo. " << index << "\n\t===>>> Ingrese el numero de producto: "; cin >> producto_id;

            rewind(inventarios);
            fread(&inv, sizeof(IV), 1, inventarios);

            while(!feof(inventarios)){
                if(inv.producto.producto_id == producto_id){
                    existe = true;
                    cout << "\t==> " << inv.producto.nombre_producto << ", Precio: " << inv.precio_costo;
                    break;
                }
                fread(&inv, sizeof(IV), 1, inventarios);
            }

            while(!existe){
                cout << "\t!!!!!!! Este producto no existe en el inventario, Ingrese nuevamente o \"0\" para salir: "; cin >> producto_id;
                if(producto_id == 0){
                    break;
                }

                rewind(inventarios);
                fread(&inv, sizeof(IV), 1, inventarios);

                while(!feof(inventarios)){
                    if(inv.producto.producto_id == producto_id){
                        existe = true;
                        cout << "\t==> " << inv.producto.nombre_producto << ", Precio: " << inv.precio_costo;
                        break;
                    }
                    fread(&inv, sizeof(IV), 1, inventarios);
                }
            }

            if(existe){                
                cout << "\n\t===>>> Ingrese el total de articulos: "; cin >> fad.cantidad;
                fad.sub_total = inv.precio_costo * fad.cantidad;
                fad.fac_det_id = index;
                fad.inventario = inv;
                
                conductor = new NodeFacDetalle;
                conductor->valor = fad;
                conductor->siguiente = NULL;
                
                root->siguiente = conductor;                            
                root = conductor;

				lista.fin = conductor;
                lista.tamanio++;
                index++;
            } else {
                break;
            }
        }
    }

    fclose(inventarios);
}

void crear_devolucion() {
	int num_inv = generarNuevoId(DEVOLUCIONES, sizeof(DV));// Se crea nuevo id para el documento       
    
    int producto_id = 0;
    cout << "Ingrese numero de la transaccion: "; cin >> dev.transaccion_id;
    cout << "Ingrese el codigo de producto: "; cin >> producto_id;
   	cout << "Ingrese la cantidad de articulos de la devolucion: "; cin >> dev.cantidad;
	
	FILE *facfichero = consultarFichero(FACTURAS);
	long int dir_fisica = (dev.transaccion_id - 1) * sizeof(TR);
	fseek(facfichero, dir_fisica, SEEK_SET);
	fread(&tra, sizeof(TR), 1, facfichero);
	
	if(tra.transaccion_id == dev.transaccion_id){		
		FILE *facdetalles = consultarFichero(FACTURAS_DET);		
		dev.inventario.inventario_id = 0;
		int detalle_id = tra.detalles.detalle_id;
		for(int i = detalle_id; i < (detalle_id + tra.detalles.tamanio); i++) {
			dir_fisica = (i - 1) * sizeof(FD);
			fseek(facdetalles, dir_fisica, SEEK_SET);
			fread(&fad, sizeof(FD), 1, facdetalles);
			if(fad.inventario.producto.producto_id == producto_id) {
				dev.inventario = fad.inventario;
				fclose(facdetalles);
				break;
			}						
		}
		fclose(facdetalles);
		
		if(dev.inventario.inventario_id > 0){
					
			FILE *invfichero = consultarFichero(INVENTARIOS);
			dir_fisica = (dev.inventario.inventario_id - 1) * sizeof(IV); 
			fseek(invfichero, dir_fisica, SEEK_SET);
			fread(&inv, sizeof(IV), 1, invfichero);
			
			
			if(inv.inventario_id == dev.inventario.inventario_id){
				dev.total = dev.cantidad * inv.precio_costo;
				dev.devolucion_id = num_inv;
				FILE *archivo = abrirFichero(DEVOLUCIONES);
				dir_fisica = (num_inv * sizeof(DV));
				fseek(archivo, dir_fisica, SEEK_SET);
				fwrite(&dev, sizeof(DV), 1, archivo);
				fclose(archivo);
				
				cout << "\n\n\tID creado " << num_inv << endl;
	            cout << "\n\n\tTransaccion exitosa!!" << endl;
	            system("pause");
			} else {
				cout << "\n\nEl inventario ya no existe y no tiene el producto especificado!!" << endl;
				system("pause");
			}
			fclose(invfichero);						
		} else {
			cout << "\n\nLa transaccion no tiene el producto especificado!!" << endl;
			system("pause");
		}			 		
	} else {
		cout << "\n\nLa transaccion no existe, por favor verifique y vuelva a intentar!!" << endl;
		system("pause");
	}
	fclose(facfichero);				
}

void consultar_devolucion () {
	FILE *devoluciones = consultarFichero(DEVOLUCIONES);
	fread(&dev, sizeof(DV), 1, devoluciones);
	printf("\n%10s\t%11s\t%-15s\t%8s\t%9s", "DEVOLUCION", "TRANSACCION", "PRODUCTO", "CANTIDAD", "TOTAL");
	while(!feof(devoluciones)){
		printf("\n%10d\t%11d\t%-15s\t%8d\t%9.2f", dev.devolucion_id, dev.transaccion_id, dev.inventario.producto.nombre_producto, dev.cantidad, dev.total);
		fread(&dev, sizeof(DV), 1, devoluciones);
	}
	fclose(devoluciones);
	cout << "\n\n<<<<<<<<<< ultima linea de consulta >>>>>>>>>!!"<<endl;
    system("pause");
}

void mostrar_reporte_pagos() {
	FILE *transacciones = consultarFichero(FACTURAS);
	fread(&tra, sizeof(TR), 1, transacciones);	
	while(!feof(transacciones)) {
		printf("\n\n%5s\t%8s\t%13s", "ID", "VENDEDOR", "TOTAL_FACTURA");
		printf("\n----------------------------------------------------------------------------");
		printf("\n%5d\t%8d\t%13.2f", tra.transaccion_id, tra.codigo_vendedor, tra.monto_total);		
		printf("\n----------------------------------------------------------------------------");				
		printf("\n\n\t%-20s\t%10s\t%8s\t%7s", "PRODUCTO", "P_UNITARIO", "CANTIDAD", "P_TOTAL");
		printf("\n\t--------------------------------------------------------------------");
		
		FILE *facdetalles = consultarFichero(FACTURAS_DET);		
		dev.inventario.inventario_id = 0;
		int detalle_id = tra.detalles.detalle_id;
		for(int i = detalle_id; i < (detalle_id + tra.detalles.tamanio); i++) {
			long int dir_fisica = (i - 1) * sizeof(FD);
			fseek(facdetalles, dir_fisica, SEEK_SET);
			fread(&fad, sizeof(FD), 1, facdetalles);
			printf("\n\t%-20s\t%10.2f\t%8d\t%7.2f", fad.inventario.producto.nombre_producto, 
												  fad.inventario.precio_costo, 
												  fad.cantidad, 
												  fad.sub_total);							
		}
		fclose(facdetalles);				
		printf("\n\n\t_______________________fin de detalle______________________________\n");						
		fread(&tra, sizeof(TR), 1, transacciones);		
	}
	fclose(transacciones);
	cout << "\n\n<<<<<<<<<< ultima linea de consulta >>>>>>>>>!!"<<endl;
    system("pause");
}
