# Proyecto_III_Datos_II

TEC file system consiste en simular de un RAID donde los archivos a se almacenan en un disco (en este caso una carpeta) y se divide en partes para conseguir una paridad y poder recuperar la información si alguno de los discos llega a fallar.

Para el desarrollo de la aplicación se utilizaron varias bibliotecas en las cuales están json for modern donde se puede descargar de https://github.com/nlohmann/json, tinyxml2 para el uso del xml el cual la podemos descargar de https://github.com/leethomason/tinyxml2, además de usar gtkmm y gtk para el desarrollo de la GUI el cual se puede descargar e instalar en linux con los siguientes comandos sudo apt install libgtkmm-3.0-dev y sudo apt install libgstreamermm-1.0-dev, ejecutas directamente en la consola de comandos. 

Con el fin de ejecutar el programa en primer lugar deberemos ejecutar el servidor, donde se controlan la parte de los archivos y los nodos discos, posteriormente ejecutaremos el cliente donde se encuentra la interfaz de usuario.

El programa puede tener varias opciones las cuales son:

## Añadir archivos.

Esta opción la podemos hacer mediante un único archivo donde se mandará la información y el nombre con el cual queremos añadirlo o también podemos añadir los elementos o archivos .txt que estén en una carpeta.

## Eliminar archivos.

Para eliminar un archivo lo único que debemos hacer es indicar el nombre del archivo que queremos eliminar y dicho archivo se eliminará del RAID.

## Leer y buscar archivos.

Podemos hacerlo de 2 maneras, buscando un único archivo con su nombre o en su defecto podemos insetar una palabra y el node controller buscará cuales archivos contiene dicha palabra para poder leerlos.

## Desactivar discos.

La aplicación está diseñada para el soporte de errores por lo cual se implementó un sistema donde se pueden desconectar los discos, en dicho sistema si se desactiva algún disco se hará uso de la paridad almacenada en otro disco para poder recuperar información.

## Mostrar capacidad de los discos.

Se podrá observar la cantidad de espacio disponible, total y usado de los discos.
