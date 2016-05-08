/**
 * @file hilos.c
 *Este archivo contiene los hilos que seran creados. Se ha optado por la
 *creacion de hilos para realizar operaciones durante "los tiempos muertos"
 *mientras el usuario elige una opcion para ejecutar y asi mejorar la
 *experiencia del usuario.
*/

/*
  Parametros: (void* p) Argumentos que recibe durante la creacion del mismo.
                        Se recibe la direccion de la variable y se modificar
                        el valor desde el hilo.
  Retorno: (void*) El hilo regresa el apuntador al arreglo que se genero y lo
                   deja listo para su uso en el resto del programa.

  El hilo generado tiene como funcion principal encontrar la cantidad de
  registros contenidos en el archivo txt y generar un arreglo de estructuras
  capaz de contener los datos y mostrarlos.
*/
/**
 * @brief Hilo que lee el archivo inventario.txt, cuenta la cantidad de
 *        registros que contiene, genera el arreglo que contendra la
 *        informacion y finalmente lee la informacion al arreglo.
 * @param *p Parametro recibido por referencia que guardara el numero de
 *        registros que contiene el archivo.
 * @return void* Regresa el apuntador del arreglo que contiene la información
 *               obtenida los archivos para su uso fuera del hilo.
*/
void *cuentaInventario(void* p){
  char c;
  intptr_t entradas= 0,*valor= (intptr_t*)p;
  int32_t i= 0,isError= 0,lectura;
  Inventario *inv;
  FILE *arch;

  arch= fopen(INVENTARIO,"r");

  if(arch==NULL){ //Se considera si el archivo existe o no
    arch= fopen(INVENTARIO,"w");
    fclose(arch);
    *valor= 0; //En caso de un archivo se genera un arreglo de un espacio
    inv= (Inventario*)calloc(1,sizeof(Inventario));
  }else{ //Se cuenta el numero de registros
    while(!feof(arch)){
      c= getc(arch);
      if(c == '\n')
        entradas++;
    }

    *valor= entradas;
    inv= (Inventario*)calloc(entradas,sizeof(Inventario));

    rewind(arch);
    for(i=0; i<entradas; i++){
      lectura= fscanf(arch,"%s %s %d %f",inv[i].nombreProducto,
        inv[i].tienda,&inv[i].cantidadExistente,&inv[i].precio);

      //Se usa el retorno de fscanf para verificar la informacion
      if(lectura != 4){
        fclose(arch);
        return (void*)(NULL);
      }
    }

    fclose(arch);
  }

  return (void*)inv;
}

/*
  Parametros: (void* r) Argumentos que recibe durante la creacion del mismo.
                      Se recibe la direccion de la variable y se modificar
                      el valor desde el hilo.
  Retorno: (void*) El hilo regresa el apuntador al arreglo que se genero y lo
                   deja listo para su uso en el resto del programa.

  Este hilo tiene la misma funcion que el anterior, pero en un archivo
  diferente (registro.txt).
*/
/**
 * @brief Hilo que lee el archivo registro.txt, cuenta la cantidad de
 *        registros que contiene, genera el arreglo que contendra la
 *        informacion y finalmente lee la informacion al arreglo.
 * @param *r Parametro recibido por referencia que guardara el numero de
 *        registros que contiene el archivo.
 * @return void* Regresa el apuntador del arreglo que contiene la información
 *               obtenida los archivos para su uso fuera del hilo.
*/
void *cuentaRegistro(void* r){
  char c;
  intptr_t entradas= 0,*valor= (intptr_t*)r;
  int32_t i= 0,isError= 0,lectura;
  Servicio *serv;
  FILE *arch;

  arch= fopen(REGISTRO, "r");
  //Se verifica la existencia del archivo
  if(arch==NULL){
    arch= fopen(REGISTRO,"w");
    fclose(arch);
    *valor= 0; //En caso de un archivo se genera un arreglo de un espacio
    serv= (Servicio*)calloc(1,sizeof(Servicio));
  }else{ //Se cuenta el numero de registros
    while(!feof(arch)){
      c= getc(arch);
      if(c == '\n')
        entradas++;
    }
    //Se genera el arreglo que guardara la informacion
    *valor= entradas;
    serv= (Servicio*)calloc(entradas,sizeof(Servicio));
    //Se regresa el puntero de flujo
    rewind(arch);
    for(i=0; i<entradas; i++){
      lectura= fscanf(arch,"%s %s %s %s %f ",serv[i].fecha,serv[i].vendedor,
        serv[i].servicio,serv[i].tienda,&serv[i].total);
      //Se usa el retorno de fscanf para verificar la informacion
      if(lectura != 5){
        fclose(arch);
        return (void*)(NULL);
      }
    }//Se retorna un nulo en caso de error

    fclose(arch);
  }

  return (void*)serv;
}

/*
  Parametros: (void* args) El programa recibe como parametro el apuntador al
                           arreglo generado y lo imprime al archivo para
                           proporcionar persistencia a la informacion en
                           memoria.
  Retorno: (void*) Se regresa el estado de la ejecucion del programa e indicar
                   si la escritura fue exitosa

  Este hilo escribe la informacion modificada a los archivos y genera un
  archivo de respaldo. Si hubiera un problema al escribir los datos, se
  retorna un valor que permite al programa tomar medidas para recuperar la
  informacion.
*/
/**
 * @brief Este hilo escribe la informacion modificada a los archivos y genera un
 *        archivo de respaldo.
 * @param *args Apuntador que recibe el apuntador del arreglo que contiene la
 *        la información que se escribira al archivo.
 * @return void* Se regresa el estado final del proceso de escritura.
*/
void* wInventario(void *args){
  int32_t i;
  intptr_t isError= 0;
  FILE *arch;
  Inventario *inv= (Inventario*)args;

  /*Se llama al S.O para que haga una copia del archivo inventario
  antes de escribir en el*/
  isError= system("cp inventario.txt inventario.txt.bak");
  arch= fopen(INVENTARIO,"w");
  if(arch == NULL)
    isError= -1;
  else{ //Se verifica que el archivo no este "borrado"
    for(i=0; i<inv[0].size; i++){
      if(strcmp(inv[i].nombreProducto,"borrado") == 0)
        continue;
      else
        fprintf(arch,"%s %s %d %.2f\n",inv[i].nombreProducto,inv[i].tienda,
          inv[i].cantidadExistente,inv[i].precio);
    }

    fclose(arch);
  }
  return (void*)isError;
}

/*
  Parametros: (void* args) El programa recibe como parametro el apuntador al
                          arreglo generado y lo imprime al archivo para
                          proporcionar persistencia a la informacion en
                          memoria.
  Retorno: (void*) Se regresa el estado de la ejecucion del programa e indicar
                   si la escritura fue exitosa

  Este hilo tiene una funcion igual al anterior, pero lo hace a un archivo
  diferente (registro.txt)
*/
/**
 * @brief Este hilo escribe la informacion modificada a los archivos y genera un
 *        archivo de respaldo.
 * @param *args Apuntador que recibe el apuntador del arreglo que contiene la
 *        la información que se escribira al archivo.
 * @return void* Se regresa el estado final del proceso de escritura.
*/
void* wServicio(void *args){
  int32_t i;
  intptr_t isError= 0;
  FILE *arch;
  Servicio *serv= (Servicio*)args;

  system("cp registro.txt registro.txt.bak");
  arch= fopen(REGISTRO,"w");
  if(arch == NULL)
    isError= -1;
  else{
    for(i=0; i<serv[0].size; i++)
      fprintf(arch,"%s %s %s %s %.2f\n",serv[i].fecha,serv[i].vendedor,
        serv[i].servicio,serv[i].tienda,serv[i].total);

    fclose(arch);
  }
  return (void*)isError;
}
