# Explicacion

Este programa esta compuesto por varias capas (modelo vista controlador):
* Console Line Interface
* Backend

# CLI (vista)
Esta capa se encarga de imprimir por pantalla o exportar a un fichero (CSV) los datos del sistema del backend<br>
Tambien gestiona tanto las acciones del usuario como los resultados de las opciones elegidas por este<br>

Cabe destacar que el exportador de datos a CSV añade los datos nuevos al fichero, manteniendo los antiguos formando asi una base de datos<br>
Ademas, cada vez que el sistema recibe una nueva temperatura que actualiza el sistema, la capa de vista mostrara por pantalla el estado actual del sistema y exportara los datos al fichero<br>

# Backend (Controlador)
Esta capa gestiona el sistema de temperatura, presion, y gestion de los subsistemas de fio y calor<br>
Actualmente el sistema gestiona los rangos de:
* Temperatura minimos y maximos (18.0 - 30.0)
* Presion en bares maximos y minimos (0.5 - 25.0)

Este sistema al recibir un cambio de temperatura regula el sistema llamando al subsistema correspondiente:
* Si se solicita frio llama al subsistema de enfriado
* Si se solicita calor llama al subsistema de calefaccion

Ademas, activa los vectiladores de las evaporadoras

Actualemte el sistema cuando recibe un cambio de temperatura ya sea subida o bajada, cambia la presion del sistema, donde en este caso he elegido que por cada grado subir o bajar 0.25 bares<br>
Por otro lado, el sistema al cominucar al subsistema correcpodiente el cambio de temperatura, le indica la temperatura a subir o bajar, donde el subsistema se encargara por si mismo de satisfacer la accion<br>

# Subsustema de frio
Este guarda los datos del sistema de enfriado que son:
* Velocidad del ventilador
* Estado del compresor
Por cada punto de temperatura, subirmos un punto al ventilador y por cada 4 subimos un punto al compresor hasta el maximo de potencia


# Subsustema de calor
Este guarda los datos del sistema de calefaccion que son:
* Bomba de agua
* Resistencia electrica

Por cada punto de temperatura, subirmos un punto a la bomba de agua y por cada 4 subimos un punto a la resistencia hasta el maximo de potencia
