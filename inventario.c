/*
  Este archivo contiene todas las operaciones relacionadas con el
  manejo del inventario de productos, tanto del listado, la modificacion
  y creacion de informacion.
*/

/*
  Parametros: (Inventario *inv, int32_t p) Se recibe como parametros al
              apuntador del arreglo que contiene la informacion del usuario
              y a un entero que contiene la cantidad total de registros que
              tiene el archivo para imprimirlos.
  Retorno: (void)

  Esta funcion imprime en pantalla el contenido del arreglo que tiene la
  informacion del usuario.
*/
void revisaInventario(Inventario *inv,int32_t p){
  int32_t i= 0;

  printf("\nEl inventario actual es: \n\n");
  printf("Productos:\n");
  printf("Producto Tienda Cantidad Precio\n");

  for(i=0; i<p; i++){
    if(strcmp(inv[i].nombreProducto,"borrado") == 0)
      continue;
    else
      printf("%s %s %d %.2f\n",inv[i].nombreProducto,inv[i].tienda,
        inv[i].cantidadExistente,inv[i].precio);
  }

  return;
}

/*
  Parametros: (Inventario *inv, int32_t p) Se recibe de parametro el apuntador
              al arreglo que contiene la informacion del usuario y un entero
              que tiene la cantidad de registros existentes.
  Retorno: (int32_t) La funcion regresa el estado del programa despues de
           modificar la informa que contenia.

  La funcion modifica el contenido del arreglo relacionado con el inventario,
  esta funcion permite al usuario modificar o crear los registros de
  inventario que existen. Si el registro ingresado ya existe, el programa
  permitira modificar los campos del mismo, si no, el programa le permitira al
  usuario ingresar un nuevo registro. No se realiza ningun cambio al disco duro.
*/
int32_t ingresaInventario(Inventario *inv,int32_t p){
  char basuraTeclado;
  int32_t i= 0,existe,opcion= 0,isError= 0;
  Inventario compra;

  printf("\n\nIngresa el nombre del producto que deseas modificar/ingresar\n> ");
  isError= scanf("%s", compra.nombreProducto);
  while(isError == 0){
    printf("Datos invalidos, ingresesa un nuevo valor");
    isError= scanf("%s", compra.nombreProducto);
    while((basuraTeclado= getchar()) != '\n');
  }

  //Se encuetra si el registro existe
  for(i=0; i<p; i++){
    existe= strcmp(compra.nombreProducto,inv[i].nombreProducto);
    if(existe == 0)
      break;
  }

  //Si existe entra en esta seccion
  if(existe == 0){
    printf("%s ya esta en el inventario, ingresa la opcion que deseas modificar:\n\n");
    printf("1. Modificar cantidad\n");
    printf("2. Modificar tienda\n");
    printf("3. Modificar precio\n");
    printf("4. No modificar nada y regresar al menu principal\n> ");

    scanf("%d",&opcion);
    while((basuraTeclado= getchar()) != '\n');

    switch(opcion){
      case 1:
        printf("\n(Valor anterior: %d)Ingresa la nueva cantidad de producto\n> ",
          inv[i].cantidadExistente);
        isError= scanf("%d",&inv[i].cantidadExistente);
        while((basuraTeclado= getchar()) != '\n');

        while(isError == 0){
          printf("Datos invalidos, ingresesa un nuevo valor");
          isError= scanf("%d",&inv[i].cantidadExistente);
          while((basuraTeclado= getchar()) != '\n');
        }
      break;

      case 2:
        printf("\n(Valor anterior: %s)Ingresa la tienda donde esta disponible\n> ",
          inv[i].tienda);
        isError= scanf("%s",inv[i].tienda);
        while((basuraTeclado= getchar()) != '\n');

        while(isError == 0){
          printf("Datos invalidos, ingresesa un nuevo valor");
          isError= scanf("%s",inv[i].tienda);
          while((basuraTeclado= getchar()) != '\n');
        }
      break;

      case 3:
        printf("\n(Valor anterior: %.2f)Ingresa el nuevo precio\n> ",
          inv[i].precio);
        isError= scanf("%f",&inv[i].precio);
        while((basuraTeclado= getchar()) != '\n');

        while(isError == 0){
          printf("Datos invalidos, ingresesa un nuevo valor");
          isError= scanf("%f",&inv[i].precio);
          while((basuraTeclado= getchar()) != '\n');
        }
      break;

      case 4:
        printf("\nRegresando al menu...\n");
      break;

      default:
        printf("\nOpcion no valida\n");
      break;

      return 0;
    } //Si no existe
  }else{
    printf("Es un producto nuevo, ingresa los datos para inventariarlo\n\n");
    printf("Ingresa la cantidad disponible\n> ");
    isError= scanf("%d",&compra.cantidadExistente);
    while((basuraTeclado= getchar()) != '\n');

    while(isError == 0){
      printf("Datos invalidos, ingresesa un nuevo valor");
      isError= scanf("%d",&compra.cantidadExistente);
      while((basuraTeclado= getchar()) != '\n');
    }

    printf("\nIngresa la tienda donde estara disponible\n> ");
    isError= scanf("%s",compra.tienda);
    while((basuraTeclado= getchar()) != '\n');

    while(isError == 0){
      printf("Datos invalidos, ingresesa un nuevo valor");
      isError= scanf("%s",compra.tienda);
      while((basuraTeclado= getchar()) != '\n');
    }

    printf("\nIngresa el precio de compra\n> ");
    isError= scanf("%f",&compra.precio);
    while((basuraTeclado= getchar()) != '\n');

    while(isError == 0){
      printf("Datos invalidos, ingresesa un nuevo valor");
      isError= scanf("%f",&compra.precio);
      while((basuraTeclado= getchar()) != '\n');
    }

    //Se usa realloc para asignar espacio al nuevo registro del inventario
    Inventario *tmp= (Inventario*)realloc(inv,(p+1)*sizeof(Inventario));
    inv= tmp;

    if(inv == NULL){
      perror("\nError: memoria corrupta, cerrando el programa\n\n");

      return -1;
    }else{
      strcpy(inv[p].nombreProducto,compra.nombreProducto);
      inv[p].cantidadExistente= compra.cantidadExistente;
      strcpy(inv[p].tienda,compra.tienda);
      inv[p].precio= compra.precio;

      return 1;
    }
  }
}

/*
  Parametros: (Inventario *inv, int32_t) Se reciben el apuntador al inventario
              y el entero que contiene la cantidad de registros existentes.
  Retorno: (int32_t) regresa el estado final de ejecucion

  Esta funcion solo permite al usuario modificar la cantidade producto
  existente, no permite más operaciones, es un acceso rapido para cuando
  se vende un producto.
*/
int32_t modificaInventario(Inventario *inv,int32_t p){
  char aMod[20], basuraTeclado;
  int32_t i,existe, cantidad, tmp;

  printf("\nIngresa el nombre del producto vendido\n");
  scanf("%s",aMod);
  while((basuraTeclado= getchar()) != '\n');

  for(i=0; i<p; i++){
    existe= strcmp(aMod,inv[i].nombreProducto);
    if(existe == 0)
      break;
  }

  if(existe == 0){
    printf("\nIngresa la cantidad vendida\n> ");
    scanf("%d",&cantidad);
    while((basuraTeclado= getchar()) != '\n');
    tmp= inv[i].cantidadExistente-cantidad;

    if(tmp >= 0)
      inv[i].cantidadExistente= tmp;
    else
      printf("\nLa cantidad vendida no puede ser mayor que la existente\n\n");
  }else
    printf("\nEl registro no existe en la base\n");

  return 0;
}

/*
  Parametros: (Inventario *inv, int32_t) Se reciben el apuntador al inventario
              y el entero que contiene la cantidad de registros existentes.
  Retorno: (int32_t) regresa el estado final de ejecucion

  Esta funcion de "borrado", cambia el nombre del producto por la palabra
  "borrado", esto lo reconoce el resto del programa como una etiqueta que
  permita ignorar el contenido del registro y finalmente no lo vacia en el
  archivo.
*/
int32_t quitaInventario(Inventario *inv,int32_t p){
  char aBorrar[20], basuraTeclado;
  int32_t i,existe,isError= 0;

  printf("Ingresa el registro que deseas eliminar\n");
  isError= scanf("%s",aBorrar);
  while((basuraTeclado= getchar()) != '\n');

  for(i=0; i<p; i++){
    existe= strcmp(aBorrar,inv[i].nombreProducto);
    if(existe == 0)
      break;
  }

  if(existe == 0){
    strcpy(inv[i].nombreProducto,"borrado");
    printf("\nEl registro se ha borrado de la lista\n\n");
  }else
    printf("\nEl registro no existe en la base\n");

  return 0;
}
