# **Dispensador interactivo de premios para mascotas**
## **Informe de Avance**

**Autores**

**Schapira Franco - Padrón 103462**  
**Gloc Marina - Padrón 111698**

**Fecha: 13/11/2026**

**2do cuatrimestre 2026**

Este informe presenta el avance del Trabajo Final de acuerdo con la propuesta seleccionada: un dispensador interactivo de premios para mascotas con desafíos visuales y sonoros, censado del alimento y comunicación Bluetooth. Los estados consignados son preliminares y deberán actualizarse según las pruebas de implementación e integración del prototipo.

| Estado | Descripción |
|-----|---------------------|
| 🟢 | Implementado y verificado |
| 🟡 | En proceso de implementación o validación |
| 🔴 | No se implementará |

#### **Entrenamiento e interacción**

| Req ID | Descripción | Estado |
|--------|-------------|--------|
| 1.1 | El sistema presentará desafíos mediante un indicador LED | 🟡 |
| 1.2 | El sistema presentará un tono de estímulo emitido por el buzzer para llamar la atención de la mascota.  | 🔴 |
| 1.3 | El sistema registrará la respuesta física de la mascota mediante botones. | 🟡 |
| 1.4 | El sistema evaluará si la mascota presionó el botón indicado dentro de un tiempo límite configurable. | 🟡 |
| 1.5 | El sistema reproducirá tonos diferentes para indicar una respuesta correcta o incorrecta. | 🔴 |

#### **Dispensador de alimento**

| Req ID | Descripción | Estado |
|--------|-------------|--------|
| 2.1 | El sistema accionará un servomotor mediante una señal PWM para liberar una porción de alimento cuando se valide una respuesta correcta o cuando se cumpla el horario de alimento establecido por el usuario mediante la app. | 🟡 |
| 2.2 | El sistema limitará la cantidad de premios entregados en una ventana de tiempo para evitar la sobrealimentación. | 🟡 |

#### **Sensado del depósito**

| Req ID | Descripción | Estado |
|--------|-------------|--------|
| 3.1 | El sistema medirá el nivel de alimento disponible en el depósito mediante un sensor analógico. | 🟡 |
| 3.2 | El sistema medirá la humedad del alimento para indicar si se encuentra en buen estado. | 🟡 |

#### **Comunicación Bluetooth**

| Req ID | Descripción | Estado |
|--------|-------------|--------|
| 4.1 | El sistema establecerá comunicación inalámbrica mediante una interfaz UART conectada a un módulo Bluetooth. | 🟡 |

#### **Aplicación móvil**

| Req ID | Descripción | Estado |
|--------|-------------|--------|
| 5.1 | La aplicación permitirá configurar el tiempo límite de respuesta, la dificultad del juego y el límite de premios. | 🟡 |
| 5.2 | La aplicación permitirá consultar las estadísticas de entrenamiento: aciertos, errores y porciones dispensadas. | 🟡 |

#### **Almacenamiento**

| Req ID | Descripción | Estado |
|--------|-------------|--------|
| 6.1 | El sistema guardará la configuración del juego y los límites de premios en la memoria Flash no volátil del STM32. | 🟡 |
| 6.2 | El sistema recuperará la configuración guardada después de un reinicio o encendido. | 🟡 |

#### **Gestión y seguridad**

| Req ID | Descripción | Estado |
|--------|-------------|--------|
| 7.1 | El firmware se organizará mediante una máquina de estados finitos con los modos DISPENSER_DIARIO, DISPENSER_ENTRENAMIENTO, SET_UP, PAUSA, SIN_ALIMENTO, FALLA y BAJO_CONSUMO. | 🟡 |
| 7.2 | Tras un período de inactividad, el sistema entrará en modo de bajo consumo y despertará mediante una interrupción EXIT ante la interacción inicial de la mascota. | 🟡 |

El alcance de este informe corresponde a la opción seleccionada en la propuesta: dispensador interactivo con censado analógico y Bluetooth.
