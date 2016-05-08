/**
 * @file datos.h
 *Archivo de cabecera que define los archivos que seran importados,
 *las constantes para hacer referencia a los archivos de guardado,
 *se definen los tipos de dato y las declaraciones de funciones.
*/

//Lista de includes
#include <stdio.h> //Entrada y salida de datos
#include <stdint.h> /*Numeros enteros estandar independientes de la
                    arquitectura. Facilita el casteo*/
#include<stdbool.h> //Facilita el uso de valores booleanos
#include <stdlib.h> //calloc, realloc y system
#include <pthread.h> //Hilos posix
#include <string.h> //Manejo de cadenss
#include <unistd.h> //fork()
#include <time.h> //Genercion de la fecha
#include <signal.h> //Señal para cachar la señal SIGINT

//Constates de llamada para archivos
/**
 * @brief Constante del nombre del archivo que se usara para inventario
*/
#define INVENTARIO "inventario.txt"
/**
 * @brief Constante del nombre del archivo que se usara para servicios
*/
#define REGISTRO "registro.txt"

//Tipo de dato con los campos necesarios para un articulo del inventario
/**
 *@brief Tipo de dato con los campos necesarios para un articulo del inventario
*/
typedef struct inventario{
  char nombreProducto[20];
  char tienda[20];
  int32_t cantidadExistente;
  float precio;
  int32_t size;
}Inventario;

//Tipo de dato con los campos necesarios para registrar un servicio
/**
 *@brief Tipo de dato con los campos necesarios para registrar un servicio
*/
typedef struct servicio{
  char vendedor[20];
  char servicio[20];
  char tienda[20];
  float total;
  char fecha[10];
  int32_t size;
}Servicio;

//Declaracion de funciones usadas
void *cuentaInventario(void*);
void *cuentaRegistro(void*);
void *wInventario(void*);
void *wServicio(void*);
void menu(void);
int32_t pedirDato(void);
int32_t inicio(void);
void revisaInventario(Inventario*, int32_t);
void revisaRegistro(Servicio*, int32_t);
int32_t ingresaInventario(Inventario*, int32_t);
int32_t modificaInventario(Inventario*, int32_t);
int32_t quitaInventario(Inventario*,int32_t);
int32_t ingresaRegistro(Servicio*, int32_t);
int32_t escribirDatos(Inventario*, Servicio*);
void ctrlc(int); //Señal
