
# Cómo ejecutar el ejemplo Ping Pong

- Hay que partir de la plantilla del proyecto TPV2.

- Vamos a suponer que tu proyecto está en la carpeta `C:\hlocal\TPV2`, y las carpetas `src`, `resources` y `bin` están directamente en `C:\hlocal\TPV2`.

- Copia las carpetas y archivos que están dentro de `asteroids/net` a tu proyecto, dentro de la carpeta `src`, y añade todos los archivos `.cpp` y `.h`` a tu proyecto.

# Ejecutar el juego desde consola


Para cada jugadord, abrimos una consola y:

```
  c:
  cd c:\hlocal\TPV2
  bin\TPV2Debug.exe
```

Notase que tenemos que estar en el directorio `c:\hlocal\TPV2` porque es el directorio que incluye `resources`, y el programa supone que `resources` está en el directorio de trabajo -- Cuando ejecutamos el programa desde Visual Studio esto se hace automáticamente porque en la configuración del proyecto hay una opción llamada *directorio de trabajo (working directory)* que ya está configurada con el valor `c:\hlocal\TPV2`.

# Ejecutar el juego usando un script


Otra posibilidad es usar un script `BAT` en lugar de abrir las consolas cada vez:

- Edita el archivos `ping_pong/pingpong.bat` y cambia `c:\hlocal\TPV2` por la ruta de tu directorio TPV2 (el que incluye `src`).

- Ahora,  puedes simplemente hacer clic sobre `pingpong.bat`  para cada cliente cliente (desde un `File Explorer` como cualquier otro programa)


# Cómo abrir una consola

- Pulsa la tecla ``Windows+R`` (o abre el menú ``Start`` y haz click en la opción ``Run``)
- Escribe en el recuadro ``cmd`` y haz clic en ``OK`` (o pulsar ``ENTER``)  


Mas información : [https://www.howtogeek.com/235101/10-ways-to-open-the-command-prompt-in-windows-10/](https://www.howtogeek.com/235101/10-ways-to-open-the-command-prompt-in-windows-10/).

