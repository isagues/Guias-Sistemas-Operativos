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