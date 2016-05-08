/**
 * @file menu.c
 *Archivo que contiene la funcion que genera el menu con el que interactuara
 *el usuario y lee los datos necesarios para comenzar el funcionamiento del
 *programa.
*/

/*
  Parametros: (void)
  returno: (void)

  Funcion que imprime el menu inicial al usuario
*/
/**
 *@brief Funcion que imprime el menu que se muestra al usuario durante el
 *       inicio del programa
 *@param void
 *@return void
*/
void menu(void){
  printf("\n\n1. Revisar inventario\n");
  printf("2. Registro de servicios proporcionados\n");
  printf("3. Venta de material(es)\n");
  printf("4. Adquisicion de nuevo material\n");
  printf("5. Borrar material del inventario\n");
  printf("6. Registrar servicio\n");
  printf("7. Volver a leer la informacion de los archivos\n");
  printf("8. Salir del programa\n\n> ");

  return;
}

/*
  Parametros: (void)
  returno: (int32_t) Se retorna el valor obtenido del usuario

  Funcion que toma un valor valido del usuario y se procura cierta
  integridad en el mismo.
  Se usa la siguiente linea: while((basuraTeclado= getchar()) != '\n');
  esta linea quita todos los valores ingresados por el usuario del
  buffer de teclado, se detiene hasta encontrar un salto de linea.
  Es una forma de sustituir a fflush(stdin).
*/
/**
 * @brief Función que lee y valida los datos ingresados por el usuario desde
 *        el teclado.
 * @param void
 * @return int32_t Regresa el dato ingresado por el usuario.
*/
int32_t pedirDato(void){
  char basuraTeclado;
  bool isError= false;
  int32_t numErrores= 0, opcion= 0;

  isError= scanf("%d", &opcion); //Se toma el retorno de scanf para validar
                                //el dato, regresa la cantidad de datos leidos
  while((basuraTeclado= getchar()) != '\n');

  while(isError != true){
    numErrores++;
    printf("Error de asignacion, ingrese una nueva opcion, porfavor\n> ");
    isError= scanf("%d", &opcion);
    while((basuraTeclado= getchar()) != '\n');
    if(numErrores == 3){
      numErrores= 0;
      printf("Porfavor ingrese una de las opciones siguientes: \n");
      menu();
    }
  }

  return opcion;
}

/*
  Parametros: (void)
  Retorno: (int32_t) Regresa el estado final de ejecucion de la funcion

  Esta funcion crea 2 hilos que reciben un parametro por referencia
  de tipo entero, donde se almacenara la cantidad de lineas existentes
  en el archivo inventario.txt
  Dentro de estos hilos se genera un arreglo que va contener la informacion
  con la que trabajara el programa.
  La informacion reciba no se escribira hasta que el usuario elija la opcion
  7, en ese momento se creara un proceso hijo que escribira la informacion
  a los archivos correspondientes de forma transparente al usuario.
*/
/**
 * @brief Función que muestra el menu que se muestra al usuario, igualmente
          por medio de 2 hilos se leen los datos desde los archivos y se
          guardan en arreglos que estaran disponibles durante el resto de la
          ejecución.
 * @param void
 * @return int32_t Regresa el estado final de la ejecución y la regresa
 *         al main().
*/
int32_t inicio(void){
  char basuraTeclado;
  int32_t opcion= 0, *noProduct, *noService, i= 0;
  int32_t product, service, ret= 0;
  pthread_t contarP, contarS;
  pid_t pid;
  void *castP, *castS;
  Inventario *invent;
  Servicio *serv;

  //Creacion y puesta en marcha de los hilos
  pthread_create(&contarP,NULL,(void*)cuentaInventario,(void*)&noProduct);
  pthread_create(&contarS,NULL,(void*)cuentaRegistro,(void*)&noService);
  //Se espera el termino de ejecucion de los hilos y se recibe el arreglo
  //que retornaron
  pthread_join(contarP,&castP);
  pthread_join(contarS,&castS);

  //Se verifica la integridad de los archivos mientras se lee
  if(castP == NULL){
    printf("\n\nEl archivo inventario.txt esta corrupto\n\n");
    return -1;
  }

  if(castS == NULL){
    printf("\n\nEl archivo registros.txt esta corrupto\n\n");
    return -1;
  }

  //El aputador al arreglo recibido por el hilo es casteado al tipo de
  //dato correspondiente
  product= (intptr_t)noProduct;
  service= (intptr_t)noService;
  invent= (Inventario*)castP;
  serv= (Servicio*)castS;

  printf("\n\nSistema de control de productos\n");
  printf("Seleccione la opcion que desea utilizar:");

  while(1){
    if(opcion != -1)
      menu();

    opcion= pedirDato();

    switch(opcion){
      case 1:
        revisaInventario(invent,product);
      break;

      case 2:
        revisaRegistro(serv,service);
      break;

      case 3:
        ret= modificaInventario(invent,product);
      break;

      case 4:
        ret= ingresaInventario(invent,product);
        if(ret == 1)
          product++;
        else if(ret == -1)
          return -1; //Se termina el programa si hay un fallo de lectura
      break;

      case 5:
        ret= quitaInventario(invent,product);
      break;

      case 6:
        ret= ingresaRegistro(serv,service);
        service++;
      break;

      case 7:
        /*Se usa recursividad para releer la informacion de los archivos si
        fueron modificados manualmente*/
        ret= inicio();
        if(ret == -1)
          return ret;
        else
          return ret;
      break;

      case 8:
        /*Se asigna el valor a uno solo los elementos para poder ser
        usado dentro del hilo que escribira la informacion*/
        invent[0].size= product;
        serv[0].size= service;
        printf("\nHasta la proxima\n");

        /*Se crea un proceso hijo el cual seguira ejecutandose apesar de la
        terminacion del proceso padre. Su funcion sera escribir los datos
        generados por el usuario*/
        pid= fork();
        if(pid > 0){
          //Se libera la memoria en el proceso padre
          free(invent);
          free(serv);
          return ret;
        }else
          ret= escribirDatos(invent,serv);
          if(ret == 0)
            exit(EXIT_SUCCESS);
          //Se finaliza la ejecucion del hijo si fue exitoso el proceso
      break;

      default:
        printf("\nOpcion incorrecta, porfavor ingrese una opcion valida\n> ");
        opcion= -1;
      break;
    }
  }
}
