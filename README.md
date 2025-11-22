Informe – Tarea 3: Protección de Lectura en XV6

El objetivo de esta tarea era permitir que ciertas regiones de memoria quedaran como “solo escritura”, es decir, que el proceso pudiera escribir en ellas pero no leerlas.

Para lograr esto, primero agregué dos nuevas funciones dentro del kernel: mrdprotect y munrdprotect. La primera deshabilita la lectura en un rango de páginas, limpiando el bit de lectura en la tabla de páginas, mientras que la segunda revierte ese cambio, volviendo a habilitar la lectura. Ambas funciones validan el rango, revisan que las páginas correspondan a memoria de usuario y verifican que estén mapeadas correctamente.

Luego añadí dos nuevas llamadas al sistema (syscalls) para que los programas de usuario pudieran utilizar estas funciones. Esto implicó modificar varios archivos del kernel: agregar los prototipos, actualizar la tabla de syscalls, implementar las versiones de usuario y hacer que los parámetros (dirección y número de páginas) se pasaran correctamente desde espacio de usuario hacia el kernel.

Después modifiqué el archivo trap.c para detectar correctamente cuándo un proceso intenta leer una página protegida. XV6 produce un “page fault” en esos casos, y yo ajusté el manejo de ese evento para que el kernel mostrara un mensaje más claro indicando que se intentó acceder a memoria protegida y terminara el proceso de forma controlada.

Finalmente, implementé un programa de prueba llamado rdprotect_test.c. Este programa reserva una página de memoria, modifica un valor, aplica la protección de lectura y luego intenta leer la página protegida. Con esto, se confirma que la protección funciona porque el programa inmediatamente provoca un trap y el kernel muestra el mensaje correspondiente. La funcionalidad queda comprobada.

En resumen, logré incorporar un nuevo mecanismo de seguridad dentro de XV6, agregando correctamente las funciones del kernel, las llamadas al sistema, la modificación del manejo de traps y la creación de un programa de prueba que demuestra el correcto funcionamiento de la protección de lectura. El sistema ahora puede marcar regiones de memoria como ilegibles pero aún modificables, cumpliendo con lo que pedía la tarea.
