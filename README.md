Sistema tienda de Tatuajes.

Autores:
	Rubi Rico Miguel, 
	Garcia Fierros Nicky

Programa que simula la implementacion de una tienda por medio de un programa en lenguaje C.
El programa intenta dar una respuesta rapida al usuario y busca cuidar de la mejor manera
los datos ingresados por el usuario. Se captura la señal SIGINT para no cerrar de forma 
violenta el programa y dar una mejor comprension al usuario de lo que ocurre.


El proyecto fue hecho con la version 5.3.1 de gcc y debe de usarse el siguiente comando:
gcc -lpthread principal.c.
Se generara un archivo a.out, el cual podra ser ejecutado normalmente ./a.out

El programa implementa varias medidas para conservar la integridad de la informacion, por 
ejemplo:

	El programa solo realiza una lectura del archivo contenedor de la informacion y todos 
	los cambios que realiza	los hace inicialmente en la memoria RAM, en caso de que no 
	hubiera ningun error, se escribe al disco duro.

	Se crea un respaldo por medio de una llamada al sistema operativo.

El programa busca facilitar el acceso al usuario y es por ello que se procura realizar las 
operaciones de escritura y lectura de forma transparente al usuario y solo notificar si ha
habido un error.
Entre las limitaciones del programa se tiene que, aunque se valida la informacion ingresada, 
solo se hace una validacion de tipo, mas no semantica, asi que en campos como tienda o 
vendedor, se podria ingresar informacion valida en cuanto a su tipo, pero completamente 
absurda.

Se incluyen 2 archivos .txt para probar el proyecto, igualmente se incluyen 2 archivos
.txt.bak. No son necesarios para la ejecucion del programa, ya que de no existir el programa
los generara automaticamente. Solo que estos estaran vacios.

Como punto final, se incluye un .tar.gz, que contiene una pagina web con el listado de las 
funciones, estructuras, variables y constantes en el programa. Tambien facilita la revision
del codigo ya que muestra un listado con los codigos. La pagina fue generada con la herramienta
doxygen. Se debe abrir desde el archivo index.html.
