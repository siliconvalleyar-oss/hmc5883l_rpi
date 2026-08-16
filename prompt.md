================================================================================
PROMPT PARA GENERAR CÓDIGO C++ PARA RASPBERRY PI CON BCM2835
================================================================================

OBJETIVO:
---------
Desarrollar una aplicación en C++ para Raspberry Pi que utilice la librería
BCM2835, con la siguiente estructura de directorios y archivos.
Para una raspberry pi 2w y pi 4  con el modilo HCM5883L


ESTRUCTURA DE DIRECTORIOS Y ARCHIVOS:
--------------------------------------
├── bin/
│   └── App                     (ejecutable final, nombre = App)
├── config/
│   ├── config.cfg              (archivo de configuración)
│   └── hardware.cfg            (configuración de hardware)
├── docs/
│   ├── ACTIVITY.md
│   ├── API.md
│   ├── ARCHITECTURE.md
│   ├── ARQUITECTURA.md
│   ├── BLUETOOTH.md
│   ├── BUILD.md
│   ├── CHANGELOG.md
│   ├── CONTRIBUTING.md
│   ├── DEPLOY.md
│   ├── DESING.md              (nota: posible typo, pero se mantiene)
│   ├── DIAGRAMS.md
│   ├── doxygen/               (directorio para documentación generada)
│   ├── HARDWARE.md
│   ├── INSTALL.md
│   ├── LEARNINGS.md           (debe ser completado por el AI)
│   ├── MEMORY_MAP.md
│   ├── PROMPT.md
│   ├── REPORT.md
│   ├── ROADMAP.md
│   ├── RULES.md
│   ├── SECURITY.md
│   ├── SETUP.md
│   ├── SKILLS.md
│   ├── TESTING.md
│   ├── TODO.md
│   ├── TROUBLESHOOTING.md
│   ├── USAGE.md
│   └── WORKFLOW.md            (debe ser completado por el AI)
├── examples/                   (ejemplos de uso)
├── include/
│   ├── core/                  (cabeceras del núcleo)
│   ├── drivers/               (cabeceras de drivers)
│   ├── engine/                (cabeceras del motor)
│   ├── HMC5883L.hpp           (cabecera del sensor)
│   ├── libraries/             (bibliotecas adicionales)
│   ├── nlohmann/
│   │   └── json.hpp           (biblioteca JSON)
│   ├── oled/
│   │   ├── SSD1306_OLED.hpp
│   │   ├── SSD1306_OLED_font.hpp
│   │   ├── SSD1306_OLED_graphics.hpp
│   │   └── SSD1306_OLED_Print.hpp
│   └── security/              (cabeceras de seguridad)
├── LICENSE                     (archivo de licencia)
├── Makefile                    (Makefile para compilación)
├── obj/                        (directorio para objetos, con subdirectorios)
├── README.md                   (debe ser completado)
├── scripts/
│   └── install_deps.sh        (script de instalación de dependencias)
├── src/
│   ├── engine/                (código fuente del motor)
│   ├── main.cpp               (punto de entrada)
│   └── oled/
│       ├── SSD1306_OLED.cpp
│       ├── SSD1306_OLED_font.cpp
│       ├── SSD1306_OLED_graphics.cpp
│       └── SSD1306_OLED_Print.cpp
└── VERSION                     (archivo de versión)

REQUISITOS ESPECÍFICOS:
-----------------------
1. El código debe ser escrito en C++ y hacer uso de la librería BCM2835 para
   el control de periféricos (GPIO, I2C, SPI, etc.).

2. El script de instalación de dependencias (scripts/install_deps.sh) debe
   instalar todas las librerías necesarias, incluyendo bcm2835, nlohmann-json,
   y cualquier otra que se requiera.

3. El AI que procese este prompt DEBE leer y completar los siguientes archivos
   Markdown con contenido relevante y detallado:
   - docs/LEARNINGS.md   (aprendizajes, lecciones, troubleshooting)
   - docs/WORKFLOW.md    (flujo de trabajo, procesos, metodología)

4. Además, el AI debe completar el archivo README.md con información completa
   del proyecto, incluyendo:
   - Descripción del proyecto.
   - Requisitos de hardware y software.
   - Instrucciones de compilación e instalación.
   - Uso básico.
   - Notas sobre compatibilidad (32 y 64 bits).

5. Los archivos objeto (.o) deben generarse dentro del directorio obj/,
   manteniendo la misma estructura de subdirectorios que en src/ (por ejemplo,
   obj/oled/SSD1306_OLED.o, obj/engine/... etc.).

6. El binario final se llamará "App" (coincidiendo con el nombre en bin/) y
   debe ser generado en el directorio bin/. Debe ser compatible con sistemas
   de 32 y 64 bits (compilación con -m32 y -m64 o mediante detección).

7. El Makefile debe estar correctamente configurado para:
   - Compilar todos los archivos .cpp de src/ y sus subdirectorios.
   - Generar los objetos en obj/ con la misma jerarquía.
   - Enlazar con la librería bcm2835 (y otras necesarias).
   - Incluir reglas para clean, all, y distclean.
   - Permitir compilación cruzada o nativa, con detección de arquitectura.

8. La aplicación debe ser funcional y demostrar el uso de la librería BCM2835
   (por ejemplo, encender un LED, leer un sensor, o comunicarse por I2C/SPI).

INSTRUCCIONES ADICIONALES PARA EL AI:
-------------------------------------
- Generar el código fuente completo de los archivos .cpp y .hpp necesarios
  para cumplir con la funcionalidad descrita.
- Completar todos los archivos .md mencionados con información coherente y útil.
- Asegurar que el script install_deps.sh funcione en Raspberry Pi OS (Debian).
- El Makefile debe ser robusto y bien comentado.
- Incluir ejemplos de uso en el directorio examples/ (si es relevante).

FORMATO DE SALIDA ESPERADO:
---------------------------
El AI debe proporcionar el contenido de cada archivo (código, scripts,
documentación) de manera organizada, preferiblemente mostrando el nombre del
archivo y su contenido completo.

================================================================================
FIN DEL PROMPT
================================================================================
