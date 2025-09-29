El trabajo consistió en agregar dos nuevas llamadas al sistema en xv6, una llamada getppid para obtener el PID del proceso padre y otra llamada getancestor para consultar los ancestros de un proceso. También se pedía crear un programa de usuario llamado YoSoyTuPadre que usara esas funciones y mostrara los valores en pantalla.  

Durante el desarrollo fui editando los archivos del kernel para asignar los números de syscall y vincular las funciones. Apareció un problema en el archivo de cabecera syscall.h porque había definiciones duplicadas y mal numeradas, lo que generaba conflictos al compilar. Esto lo solucioné eliminando las líneas repetidas y dejando definidos correctamente los números 22 para getppid y 23 para getancestor.  

Otro problema apareció en el Makefile, porque al inicio no se estaba incluyendo el ejecutable yosoytupadre en la lista UPROGS, lo que causaba errores de compilación del tipo “no hay regla para _yosoytupadre”. Esto se solucionó agregando esa línea en el lugar correcto de UPROGS.  

Una vez corregidos esos detalles, recompilé el sistema y probé dentro de QEMU. El resultado que obtuve al ejecutar el programa yosoytupadre fue: Mi PID=3, PPID=2, ancestor(0)=3, ancestor(1)=2, ancestor(2)=1.  

Esto confirma que getppid entrega el identificador del proceso padre y que getancestor funciona para obtener los ancestros en diferentes niveles. De esta forma se cumple lo que pedía la tarea y el programa se ejecuta correctamente mostrando la información solicitada.  

En conclusión, la tarea queda realizada con éxito: se implementaron las nuevas llamadas al sistema, se resolvieron los problemas de duplicados y de inclusión del programa en el Makefile, se compiló el sistema y el programa YoSoyTuPadre mostró en la práctica los resultados esperados.  
