# **Propuesta de Trabajo Final: Dispensador interactivo de premios para mascotas** 
<br/>Autores: Marina Gloc, Franco Schapira  
Padrones: 111698, 103462  
Fecha: 2do cuatrimestre 2026

## <br/>**_1\. Selección del proyecto a implementar_**

### **1.1 Objetivo del proyecto y resultados esperados**  
El objetivo de este proyecto es diseñar e implementar un Dispensador interactivo de premios para mascotas basado en un microcontrolador STM32, el mismo tambien funcionará como dispensador automático de comida. El sistema propone desafíos cognitivos simples para la mascota mediante secuencias de luces y sonidos. Cuando la mascota responde correctamente accionando el sensor o botón indicado dentro de un intervalo de tiempo se accionará un mecanismo donde la mascota recibirá una ración de comida como premio.  
El dispositivo previene la sobrealimentación mediante un control de premios por períodos, supervisa de forma continua la presencia de alimento en el depósito mediante un sensor y permite la consulta de estadísticas de rendimiento a través de una conexión Bluetooth con una aplicación móvil.  
### <br/>**1.2 Proyectos similares**  
Para definir el alcance adecuado del proyecto se evaluaron tres alternativas:

1. **Opción A (Dispensador básico temporizado):** Control del dispensador mediante intervalos de tiempos fijos sin sensores analógicos.
2. **Opción B (Dispensador interactivo con censado analógico y Bluetooth):** Sistema con lógica de juego mediante desafíos visuales y/o sonoros, censado del nivel del alimento, comunicación Bluetooth, recolección de datos de acuerdo a las respuestas de la mascota.
3. **Opción C (Dispensador remoto IoT):** Control a distancia por WiFi para activar al dispensador de alimento desde otra ubicación mediante una app.

Criterios de evaluación:

- **Disponibilidad de Hardware (9):** Facilidad de adquisición en el mercado local sin depender de importación de componentes.
- **Impacto en el proyecto (8):** Se pondera cuánto aporta al valor didáctico.
- **Costo (8):** Se evalúa el costo total requerido para adquirir los componentes.
- **Dificultad técnica (9):** Complejidad de implementación en firmware y tiempo necesario.
- **Interés personal (7):** Motivación del equipo para desarrollar e implementar el proyecto.

| **Criterio**                                 | **Proyecto Base** |                       | **Base + Bluetooth y censado analógico** |                       | **Base + IoT** |                       |
| -------------------------------------------- | ----------------- | --------------------- | ---------------------------------------- | --------------------- | -------------- | --------------------- |
|                                              | **Puntaje**       | **Puntaje Ponderado** | **Puntaje**                              | **Puntaje Ponderado** | **Puntaje**    | **Puntaje Ponderado** |
| ---                                          | ---               | ---                   | ---                                      | ---                   | ---            | ---                   |
| Disponibilidad de Hardware<br>(peso: 9)      | 10                | 90                    | 10                                       | 90                    | 5              | 45                    |
| Impacto en el proyecto<br>(peso: 8)          | 5                 | 40                    | 9                                        | 72                    | 8              | 64                    |
| Costo (peso: 8)                              | 8                 | 64                    | 7                                        | 56                    | 3              | 24                    |
| Dificultad técnica / Viabilidad<br>(peso: 9) | 10                | 90                    | 8                                        | 72                    | 4              | 36                    |
| Interés personal<br>(peso: 7)                | 7                 | 49                    | 9                                        | 63                    | 8              | 56                    |
| **Puntaje Total**                            | **\-**            | **333**               | **\-**                                   | **353**               | **\-**         | **225**               |

                    Tabla 1: Comparación de alternativas de proyecto

### <br/><br/>**1.3 Selección del proyecto**

Se seleccionó la Opción B. Esta alternativa ofrece el equilibrio ideal entre complejidad técnica, viabilidad de ejecución y valor didáctico para la materia. A diferencia del proyecto base o con IoT, introduce interacción en tiempo real, conectividad inalámbrica Bluetooth, procesamiento de datos y almacenamientos de estos en memoria no volátil.

<img width="887" height="562" alt="me" src="https://github.com/user-attachments/assets/6cb28888-4404-44e9-8417-4c9123d7b926" />


                    Figura 1: Diagrama en bloques del sistema

## _2\. Elicitación de requisitos y casos de uso_

En el mercado argentino existen diversas soluciones para la alimentación automática de mascotas, desde comederos temporizados básicos hasta dispensadores comerciales importados. Sin embargo, la oferta local presenta limitaciones claras: los dispositivos económicos se limitan a temporizadores rígidos sin estímulo dinámico, mientras que las opciones inteligentes importadas resultan costosas, carecen de soporte técnico local y no ofrecen mecánicas de interacción cognitiva para la mascota.  
Un segundo competidor son los dispensadores automáticos con conectividad Wi-Fi/App de marcas importadas. Si bien permiten la activación remota y la configuración de horarios desde un Smartphone cuentan con un costo elevado. Además no incluyen módulos de juego o desafíos cognitivos con luces y sonidos que estimulen a la mascota antes de entregar su alimento  
En conclusión, no existe en el mercado local una solución integral de costo accesible que combine: juegos interactivos con indicadores luminosos y sonoros para entrenar a la mascota, interrupciones externas para la detección física, censado analógico del depósito de alimento, modos de bajo consumo y conectividad Bluetooth en un único sistema embebido. La implementación propuesta mediante componentes de stock local como STM32, sensores de presión, etc. reduce significativamente los costos de desarrollo y garantizan la disponibilidad de repuestos de manera inmediata.

### 2.1 Requisitos del proyecto

En la Tabla 2.1 se detallan los principales requisitos funcionales del sistema.

| **Grupo**                   | **ID** | **Descripción**                                                                                                                                     |
| --------------------------- | ------ | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| Entrenamiento e interacción | 1.1    | El sistema generará desafíos educativos iluminando un indicador LED e indicando el objetivo mediante un tono en el buzzer.                          |
|                             | 1.2    | El sistema registrará la respuesta física de la mascota mediante botones grandes.                                                                   |
|                             | 1.3    | El sistema evaluará si la mascota presionó el botón correcto dentro de un tiempo límite (timeout) programable.                                      |
|                             | 1.4    | El sistema reproducirá un tono sonoro diferencial de acierto cuando la mascota responda correctamente, o de error si se equivoca.                   |
| Dispenser de alimento       | 2.1    | El sistema activará un servomotor mediante señal PWM para girar la rueda dosificadora y liberar un premio al validar un acierto.                    |
|                             | 2.2    | El sistema limitará la cantidad máxima de premios entregados por ventana de tiempo para evitar la sobrealimentación de la mascota.                  |
| Sensado del depósito        | 3.1    | El sistema medirá el nivel de alimento disponible en el depósito mediante un sensor analógico.                                                      |
|                             | 3.2    | El sistema medirá también la humedad del alimento para indicar si está en buen estado.                                                              |
| Bluetooth                   | 4.1    | El sistema establecerá comunicación inalámbrica mediante una interfaz UART conectada a un módulo Bluetooth.                                         |
|                             | 4.2    | El usuario podrá configurar desde la app móvil los parámetros del juego (tiempo límite de respuesta, dificultad y límite de premios).               |
|                             | 4.3    | El usuario podrá consultar desde la app las estadísticas de entrenamiento de la mascota (aciertos, fallos, raciones consumidas).                    |
| Almacenamiento              | 5.1    | El sistema guardará la configuración de juego y límites en la memoria Flash interna no volátil del STM32.                                           |
|                             | 5.2    | El sistema recuperará la configuración persistida inmediatamente después de un reinicio o encendido.                                                |
| Gestión y seguridad         | 6.1    | El sistema organizará su firmware en una Máquina de Estados Finitos (FSM) con los modos: NORMAL, SET_UP, PAUSA, SIN_ALIMENTO, FALLA y BAJO_CONSUMO. |
|                             | 6.2    | El sistema pasará a modo BAJO_CONSUMO (Sleep) tras un tiempo de inactividad, despertando mediante interrupción EXTI al toque inicial de la mascota. |

                    Tabla 2: Requisitos del proyecto

### 2.2 Caso de uso 1: Dispensación Automática por Intervalo Fijo

| **Elemento**        | **Definición**                                                                                                                                                                                                                                                                                          |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Disparador          | El temporizador interno del sistema alcanza el intervalo de tiempo fijo programado (ej. cada 8 horas).                                                                                                                                                                                                  |
| Precondiciones      | El sistema está alimentado y con la temporización activa. No hay sensores de nivel ni interacción con la mascota.                                                                                                                                                                                       |
| Flujo principal     | 1\. El temporizador del microcontrolador llega a cero.<br><br>2\. El firmware activa la salida para accionar el servomotor/motor.<br><br>3\. El motor gira durante un tiempo fijo para liberar la ración.<br><br>4\. El motor se detiene y se reinicia la cuenta regresiva para el siguiente intervalo. |
| Flujos alternativos | **a. Depósito vacío o motor trabado:** El sistema intenta girar el motor de todas formas, ya que no cuenta con sensores analógicos (ADC) ni detección de fallas para detener la marcha.                                                                                                                 |

                    Tabla 3: Caso de uso 1

### 2.3 Caso de uso 2: Entrenamiento Interactivo con Sensado y Bluetooth

| **Elemento**        | **Definición**                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Disparador          | El sistema inicia un ciclo de desafío encendiendo un LED indicador y emitiendo un tono de estímulo en el buzzer.                                                                                                                                                                                                                                                                                                                                                                                        |
| Precondiciones      | El sensor analógico (ADC) confirma alimento en el depósito. La FSM está en modo NORMAL y no se superó el límite de raciones.                                                                                                                                                                                                                                                                                                                                                                            |
| Flujo principal     | 1\. El STM32 presenta el desafío visual y sonoro.<br><br>2\. La mascota presiona el botón físico, generando una interrupción externa<br><br>3\. El firmware valido el acierto dentro del tiempo límite, emite tono de premio y activa el servomotor (PWM) para liberar la ración.<br><br>4\. El sensor analógico (ADC) actualiza el nivel de alimento del depósito.<br><br>5\. El microcontrolador guarda las métricas de acierto/tiempo en memoria y transmite los datos por UART al módulo Bluetooth. |
| Flujos alternativos | **a. Fallo de la mascota o timeout:** El sistema registra el error, no acciona el servomotor y notifica la estadística por Bluetooth.<br><br>**b. Depósito vacío**: El ADC detecta falta de alimento y bloquea la dispensación entrando en modo SIN_ALIMENTO.                                                                                                                                                                                                                                           |

                    Tabla 4: Caso de uso 2

### 2.4 Caso de uso 3: Dispensación Remota

| **Elemento**        | **Definición**                                                                                                                                                                                                                                                                                                                                                                                                                          |
| ------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Disparador          | El usuario presiona el botón "Alimentar Ahora" desde la aplicación móvil estando fuera de su casa.                                                                                                                                                                                                                                                                                                                                      |
| Precondiciones      | El módulo Wi-Fi está conectado a la red local y enlazada con un broker/servidor en la nube (HTTP).                                                                                                                                                                                                                                                                                                                                      |
| Flujo principal     | 1\. La aplicación móvil envía la orden de disparo al servidor en la nube.<br><br>2\. El servidor retransmite el comando por Internet hacia el módulo WiFi del dispensador.<br><br>3\. El módulo WiFi pasa la orden al microcontrolador.<br><br>4\. El microcontrolador activa el servomotor para liberar la ración.<br><br>5\. El sistema envía un mensaje de confirmación de vuelta a la nube para notificar al usuario en su celular. |
| Flujos alternativos | **a. Fallo de conexión a Internet o WiFi caído:** La orden enviada desde la app no llega al dispositivo, la dispensación no se ejecuta y la aplicación muestra un error de tiempo de espera (_timeout_ de red).                                                                                                                                                                                                                         |

                      Tabla 5: Caso de uso 3
