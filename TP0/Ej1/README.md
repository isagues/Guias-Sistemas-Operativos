# listdir - Ignacio Sagues

Resolucion del ejercicio 1 del TP 0 de Sistemas Operativos.  

__Objetivo:__ Implementar una version simplificada de la funcion tree.  

## Compilacion 

Para compilar el archivo se utiliza el comando:
```
make all
```
## Ejecucion

Esta implementacion tiene dos formas posibles de ser utilizada: 
- Se puede llamar a la funcion sin ningun parametro. Se ejecutara usando la direccion actual como valor. __Ejemplo:__
```
./listdir
```
- Se puede llamar a la funcion pasando como primer y unico argumento una direccion, absoluta o relativa, valida. __Ejemplos:__
```
./listdir ./
./listdir $HOME
```

## Testeo

Agregue una forma de ejecutar valgrind, pvs_Studio y cppcheck automaticamente. Para correrlos basta con ejecutar:
```
 make test
``` 
Los resultados van a estar en los archivos .tasks. En el archivo Makefile se puede cambiar la variable **VALGRIND_PATH** que se utiliza para correr valgrind

## Extra

Se encuentra implementado en el archivo Makefile una opcion para borrar todos los archivos generados y una para comprimir la carpeta completa
```
make clean
```
```
make compress
```

## Mejoras posibles

- Verificar cual fue el error que sucedio y emitir un mensaje acorde. Esto permitiria informacion util a la hora de revisar el correcto funcionamiento del programa.
- Validar el argumento recibido para saber si tiene la forma de un path.
- Validar si printf tuvo algun error a la hora de imprimir? No estoy seguro si es algo necesario

## Observaciones

- strlen tiene tipo de retorno size_t, no int.
- algo similar ocurre con pathlen, donde usas un tipo con signo (int) como indice en un arreglo.
- en printline depth (int) se convierte implicitamente a size_t. depth debería sie size_t también
- no deberías definir vos los modes, sino no tiene sentido que definamos constantes en la librería. Estimo que quisiste usarlos como en el ejemplo de stat(2) y no te anduvo, sin embargo, unas líneas más abajo te explica que POSIX define macros que hacen que su uso sea más práctico. Reemplazando el switch por ifs y las macros anda bárbaro.
- que recursiveTree llame a aux... y viceversa es algo complicado de seguir, con una vuelta de tuerca más podés llegar a la versión recursiva elegante donde recursiveTree se llame a si misma directamente.
- el enum para ERROR y NO_ERROR se puede evitar. Básicamente todo el standar POSIX respeta ese enum. Es perfectamente legible usar las constantes "0" y "-1"

- hiciste bien en ignorar lo de los includes de cppcheck. No es un error, solo que cppcheck no es capaz de encontrar los includes
- es posible que solo por usar la version no acotada de strcpy en lugar de strncpy ya chille pvs-studio. Es importante visitar el sitio de pvs-studio con el codigo de error en mano, el código tiene esta pinta "V755"