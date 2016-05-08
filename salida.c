/*
  Parametros: (Inventario *inv, Servicio *serv) Se reciben los apuntadores
              de los arreglos que contienen la informacion tanto del inventario
              como del registro de servicios.
  Retorno: (int32_t) Se retorna el estado final de ejecucion de la funcion,
           que permite conocer si el guardado fue existoso y que medidas se
           deben tomar.

  El programa escribe los datos al disco duro. Esta funcion esta planeada
  para funcionar dentro de un proceso hijo. Se realiza la escritura a los
  archivos a traves de hilos de ejecucion que se encargan de respaldar la
  informacion y de realizar la escritura. Si la informacion no fuera
  guardada correctamente, se intenta restaurar el ultimo respaldo existente.
*/
int32_t escribirDatos(Inventario *inv, Servicio *serv){
  pthread_t escribeInv, escribeServ;
  void *ret1, *ret2;
  int32_t isError= 0;
  intptr_t err1, err2;

  pthread_create(&escribeInv,NULL,(void*)wInventario,(void*)inv);
  pthread_create(&escribeServ,NULL,(void*)wServicio,(void*)serv);

  pthread_join(escribeInv,&ret1);
  pthread_join(escribeServ,&ret2);

  //Se castean los retornos de los hilos
  err1= (intptr_t)ret1;
  err2= (intptr_t)ret2;

  //Se libera la memoria de los apuntadores en el proceso hijo
  free(inv);
  free(serv);

  if(err1 == -1){
    perror("\nError al escribir datos al disco duro, recuperando respaldos\n\n");
    isError= system("rm informacion.txt");
    if(isError != -1)
      isError= system("cp informacion.txt.bak informacion.txt");
    else
      perror("\n\nNo hay respaldos disponibles\n\n");

  }

  if(err2 == -1){
    perror("\nError al escribir datos al disco duro, recuperando respaldos\n\n");
    isError= system("rm registro.txt");
    if(isError != -1)
      isError= system("cp registro.txt.bak registro.txt");
    else
      perror("\n\nNo hay respaldos disponibles\n\n");
  }

  //Se finaliza al hijo si hubo algun error
  if(err1 == -1 || err2 == -1)
    exit(EXIT_FAILURE);
  else
    return 0;
}
