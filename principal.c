/**
 * @file principal.c
 *Archivo que incluye la funcion main que inicia el menu y recibe los
 *posibles errores del resto del programa, asi como el manejo de la señal
 *SIGINT.
*/

//Includes de los archivos locales
#include "datos.h"
#include "hilos.c"
#include "inventario.c"
#include "registro.c"
#include "salida.c"
#include "menu.c"

/*
  Parametros: (int32_t sign) Recibe el identificador de la señal
  Retorno: (void) No regresa algun valor
*/
/**
 *Funcion que maneja el comportamiento de la aplicacion cuando se
 *presiona en el teclado ctl + c. Señal SIGINT.
 *
 *@brief Se captura la señal SIGINT y se cierra el programa.
 *@param sign Recibe el identificador de la señal.
 *@return void.
*/
void ctrlc(int32_t sign){
  printf("\n\n\nDetiniendo la ejecucion con status de error...\n\n");
  printf("Presione una tecla para salir... ");
  getchar();
  exit(EXIT_FAILURE);
}

/*
  Parametros: (int32_t argc) Recibe el conteo de argumentos de la linea
                             de comandos.
              (char* argv[]) Arreglo de cadenas que contienen las cadenas
                             que se reciberieron desde la linea de
                             comandos

  Retorno: (int32_t) La funcion regresa el estado final de ejecucion, ayuda
                     a definir el estado de la terminacion del programa.
*/
/**
 *@brief Funcion main(), se inicia el menu a traves de la función inicia() y
         se toma el estado que regresa tras su ejecución para saber como se
         debera finalizar el programa.
 *@param argc Contador de parametros de la linea de comandos.
 *@param argv Arreglo de cadenas que contiene los parametros ingresados desde
         la linea de comandos.
 *@return int32_t Regresa el estado final del programa.
*/
int32_t main(int32_t argc, char* argv[]){
  if(argc != 1){
    printf("Este programa no necesita parametros adiconales\n");
    return EXIT_FAILURE; //Se usa EXIT_FAILURE ya que se termina el programa
  }else{
    signal(SIGINT,ctrlc);
    if(inicio() == false){
      printf("Ha ocurrido un error, contacte al administrador\n");
      return EXIT_FAILURE;
    }else
      return EXIT_SUCCESS;
  }
}
