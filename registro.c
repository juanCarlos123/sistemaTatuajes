/**
 * @file registro.c
 *Este archivo contiene todas las operaciones relacionadas con el
 *manejo del registros de servicios, tanto del listado y la creacion
 *de informacion.
*/

/*
  Parametros: (Servicio *serv, int32_t s) Se recibe de parametro el apuntador
              al arreglo que contiene la informacion de los servicios y un
              entero con la cantidad de entradas existentes.
  Retorno: (void)

  Esta funcion muestra al usuario el registro de servicios que se han realizado
  con la informacion necesaria para identificar un trabajo realizado de otro.
*/
/**
 * @brief Esta funcion muestra al usuario el registro de servicios que se han
 * realizado con la informacion necesaria para identificar un trabajo realizado
 * de otro.
 * @param *serv Se recibe de parametro el apuntador al arreglo que contiene la
 *        informacion de los servicios
 * @param s Entero con la cantidad de entradas existentes.
 * @return void
*/
void revisaRegistro(Servicio *serv,int32_t s){
  int32_t i= 0;

  printf("\nEl registro actual es:");
  printf("\n\nServicios:\n");
  printf("Fecha Vendedor Servicio Tienda Total\n");
  for(i=0; i<s; i++)
    printf("%s %s %s %s %.2f\n",serv[i].fecha,serv[i].vendedor,
      serv[i].servicio,serv[i].tienda,serv[i].total);

  return;
}

/*
  Parametros: (Servicio *serv, int32_t s) Se recibe de parametro el apuntador
            al arreglo que contiene la informacion de los servicios y un
            entero con la cantidad de entradas existentes.
  Retorno: (int32_t) Se retorna el estado de escritura de la funcion, si ha
           ha habido a algun problema se detiene la ejecucion del programa.

  Esta funcion permite al usuario ingresar el registro de un servicio que
  fue hecho por algun trabajador de la tienda. Se usan funciones de la
  biblioteca time.h que permiten generar de forma automatica la fecha actual
  y guardarla en la estructura correspondiente.
*/
/**
 * @brief Esta funcion permite al usuario ingresar el registro de un servicio
 *        que fue hecho por algun trabajador de la tienda, se usan funciones
 *        de la biblioteca time.h que permiten generar de forma automatica la
 *        fecha actual y guardarla en la estructura correspondiente.
 * @param *serv Se recibe de parametro el apuntador al arreglo que contiene la
 *        informacion de los servicios
 * @param s Entero con la cantidad de entradas existentes.
 * @return void
*/
int32_t ingresaRegistro(Servicio *serv, int32_t s){
  char basuraTeclado;
  int32_t isError= 0;
  time_t tiempocrudo;
  struct tm *infotiempo;
  Servicio *tmp= (Servicio*)realloc(serv,(s+1)*sizeof(Servicio));
  serv= tmp;

  if(serv == NULL){
    perror("\nError: memoria corrupta, cerrando el programa\n\n");

    return -1;
  }else{
    //Aqui se toma la hora del sistema
    time(&tiempocrudo);
    infotiempo= localtime(&tiempocrudo);
    //Se genera una cadena que contiene la hora en un determinado formato
    strftime(serv[s].fecha, 10,"%D",infotiempo);

    printf("Ingresa el nombre del empleado\n> ");
    isError= scanf("%s",serv[s].vendedor);
    while((basuraTeclado= getchar()) != '\n');

    while(isError == 0){
      printf("\nDatos incorrectos, ingresa un dato valido\n");
      isError= scanf("%s",serv[s].vendedor);
      while((basuraTeclado= getchar()) != '\n');
    }

    printf("Ingresa el tipo de servicio\n> ");
    isError= scanf("%s",serv[s].servicio);
    while((basuraTeclado= getchar()) != '\n');

    while(isError == 0){
      printf("\nDatos incorrectos, ingresa un dato valido\n");
      isError= scanf("%s",serv[s].servicio);
      while((basuraTeclado= getchar()) != '\n');
    }

    printf("Ingresa la tienda donde se hizo el servicio\n> ");
    isError= scanf("%s",serv[s].tienda);
    while((basuraTeclado= getchar()) != '\n');

    while(isError == 0){
      printf("\nDatos incorrectos, ingresa un dato valido\n");
      isError= scanf("%s",serv[s].tienda);
      while((basuraTeclado= getchar()) != '\n');
    }

    printf("Ingresa la cantidad cobrada por el servicio\n> ");
    isError= scanf("%f",&serv[s].total);
    while((basuraTeclado= getchar()) != '\n');

    while(isError == 0){
      printf("\nDatos incorrectos, ingresa un dato valido\n");
      isError= scanf("%f",&serv[s].total);
      while((basuraTeclado= getchar()) != '\n');
    }

    return 0;
  }
}
