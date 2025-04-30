# Un ejemplo de programa cliente/servidor

Este es un ejemplo de servidor/cliente en el que el servidor recibe mensajes, los imprime y responde al cliente correspondiente con un mensaje `"Received"`. Los clientes piden un mensaje al usuario, lo envían al servidor, imprimen la respuesta y salen.


# Cómo ejecutar estos ejemplos

Asumiremos que tu proyecto se llama `TPV2` y está ubicado en `C:\hlocal\TPV2`. Añade un ejemplo a tu proyecto (como todos tienen un método `main`, sólo puedes incluir uno a la vez).


- Para ejecutar el servidor, abra una consola y escriba

```
  cd c:
  cd c:\hlocal\TPV2
  bin\DebugTPV2.exe server 2000
```

- Para ejecutar el cliente, abra una consola y escriba

```
  cd c:
  cd c:\hlocal\TPV2
  bin\DebugTPV2.exe client localhost 2000
```
  
- Para obtener información de uso ejecute:

```
  cd c:
  cd c:\hlocal\TPV2
  bin\DebugTPV2.exe
```


# Cómo abrir una consola

- Pulsa `Windows+R` (o abre el menú `Inicio` y selecciona `Ejecutar`)
- Escribe `cmd` en el campo de texto y haz clic en `OK` (o pulsa `ENTER`)  


Mas información : [https://www.howtogeek.com/235101/10-ways-to-open-the-command-prompt-in-windows-10/](https://www.howtogeek.com/235101/10-ways-to-open-the-command-prompt-in-windows-10/).

