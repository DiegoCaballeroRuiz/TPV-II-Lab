# Un ejemplo de un programa cliente/servidor

Un ejemplo de program con servidor y clientes. El servidor recibe un mensaje de un cliente, lo escribe y responde al cliente con un mensaje ``"Received"``. El cliente pide al usuario un mensaje, en un bucle, lo envía al servidor y escribe la respuesta (si el usuario escribe el mensaje es ``"exit"`` sale del programa).

El ejemplo ``client_server_2_udp_with_serialize.cpp`` es una modificación en la que el servidor recibe números y una operación aritmética, calcula el resultado y lo envia la cliente. También puede recibir una solicitud de un número aleatorio, en ese caso elige uno y lo envia al cliente.

# Cómo jecutar los ejemplos de client/server

Vamos a suponer que tu proyecto se llama ``TPV2`` y que está en la carpeta ``C:\hlocal\TPV2``. Añade un ejemplo a tu proyecto (se puede añadir sólo uno a la vez poruqe todos tienen un método ``main``).

- Para ejecutar el servidor, abre una consola (ver abajo cómo) y escribe las siguientes instrucciones

```
  cd c:
  cd c:\hlocal\TPV2
  bin\DebugTPV2.exe server 2000
```

- Para ejecutar el cliente, abre una consola (ver abajo cómo) y escribe las siguientes instrucciones
  
```
  cd c:
  cd c:\hlocal\TPV2
  bin\DebugTPV2.exe client localhost 2000
```
  
- Para más información sobre cómo ejecutar el programa, abre una consola (ver abajo cómo) y escribe las siguientes instrucciones

```
  cd c:
  cd c:\hlocal\TPV2
  bin\DebugTPV2.exe client localhost 2000
```


# Cómo abrir una consola

- Pulsa la tecla ``Windows+R`` (o abre el menú ``Start`` y haz click en la opción ``Run``)
- Escribe en el recuadro ``cmd`` y haz clic en ``OK`` (o pulsar ``ENTER``)  


Mas información : [https://www.howtogeek.com/235101/10-ways-to-open-the-command-prompt-in-windows-10/](https://www.howtogeek.com/235101/10-ways-to-open-the-command-prompt-in-windows-10/).

