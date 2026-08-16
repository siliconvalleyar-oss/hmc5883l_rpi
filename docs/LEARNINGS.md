# LEARNINGS.md - Aprendizajes y Lecciones

## Lecciones Aprendidas

### 1. Librería BCM2835 en Raspberry Pi OS
- La librería BCM2835 requiere ejecución como root (`sudo`) para acceder a memoria mapeada de periféricos.
- En Raspberry Pi OS 64-bit, la librería funciona correctamente, pero asegurarse de que `/dev/mem` sea accesible.
- La versión de la librería debe coincidir con la versión del kernel para evitar conflictos.

### 2. Comunicación SPI con HMC5883L
- El HMC5883L requiere que el bit 7 de la dirección sea 1 para lecturas y 0 para escrituras.
- Las lecturas multi-byte deben mantener CS bajo durante toda la transferencia. Usar `bcm2835_spi_transfernb` en lugar de múltiples `bcm2835_spi_transfer` para evitar liberar CS entre bytes.
- El registro de estado (0x06) debe consultarse antes de leer datos. El bit 0 indica DRDY (Data Ready).

### 3. Calibración del Magnetómetro
- El HMC5883L tiene offsets fábrica que varían entre unidades. Es necesario calibrar en el entorno de uso.
- La calibración consiste en promediar múltiples lecturas mientras el sensor se orienta en todas las direcciones.
- Los offsets calculados deben restarse de las lecturas crudas antes de convertir a Gauss.

### 4. Makefile y Objetos en Directorios Separados
- Para generar objetos en `obj/` manteniendo la jerarquía de `src/`, es necesario usar `mkdir -p $(dir $@)` en la regla de compilación.
- Usar `-MMD -MP` genera archivos `.d` con dependencias automáticamente.
- La detección de arquitectura con `uname -m` es fiable para builds nativos, pero para cross-compilation debe especificarse manualmente.

### 5. Compilación Cruzada
- Para compilar en x86_64 y ejecutar en arm64, usar `make CROSS_COMPILE=aarch64-linux-gnu-`.
- El compilador cruzado debe tener sysroot configurado correctamente para encontrar librerías de destino.

### 6. Manejo de Señales
- Capturar SIGINT y SIGTERM permite un shutdown limpio (detener el engine, liberar SPI, cerrar BCM2835).
- Usar una variable global `g_app` es una solución simple pero efectiva para el handler de señales.

### 7. Estructura del Proyecto
- Mantener la misma jerarquía en `src/` y `obj/` simplifica la localización de archivos objeto.
- Separar `core/` (lógica de aplicación), `engine/` (lógica de dominio) y `drivers/` (acceso a hardware) facilita el testing y mantenimiento.

### 8. Troubleshooting Común

| Problema | Causa | Solución |
|----------|-------|----------|
| `bcm2835_init() failed` | No se ejecuta como root | Ejecutar con `sudo` |
| Sensor no detectado | SPI no habilitado | `sudo raspi-config` → Interface Options → SPI |
| Lecturas erráticas | CS no se mantiene bajo | Usar `transfernb` para multi-byte |
| Heading incorrecto | Sin calibración | Ejecutar `calibrate()` antes de usar |
| Binario no ejecuta en Pi diferente | Cross-compile sin sysroot | Configurar sysroot correctamente |

## Notas para el AI

- Siempre verificar que los directorios `obj/` y `bin/` existan antes de compilar.
- Los headers de nlohmann/json.hpp son un stub; reemplazar por la librería real en producción.
- El soporte para OLED (SSD1306) está como stub; puede expandirse según necesidad.
