/*
  Archivo que incluye la funcion main que inicia el menu y recibe los
  posibles errores.
  Se importan los archivos que contienen al resto de programa.
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

  Funcion que maneja el comportamiento de la aplicacion cuando se
  presiona en el teclado ctl + c. Señal SIGINT
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
int32_t main(int32_t argc, char* argv[]){
  if(argc != 1){
    printf("Este programa no necesita parametros adiconales\n");
    return EXIT_FAILURE; //Se usa EXIT_FAILURE ya que se termina el programa
  }else{
    signal(SIGINT,ctrlc);
    if(inicio() == -1){
      printf("Ha ocurrido un error, contacte al administrador\n");
      return EXIT_FAILURE;
    }else
      return EXIT_SUCCESS;
  }
}
