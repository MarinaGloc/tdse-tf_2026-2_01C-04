#include "task_led.h"

#define CANT_CANALES 4
#define REBOTE_MS 20 //Para evitar que haya presiones de boton falsas
#define TIEMPO_LIMITE_MS 30000
#define PERIODO_BLINK_MS 250

typedef struct{
	GPIO_TypeDef *port;
	uint16_t pin;
	uint8_t rebote_cnt;
	bool presionado;
	bool presionado_previo;
} boton_t;

typedef struct{
	GPIO_TypeDef *port;
	uint16_t pin;
} led_t;

typedef enum{
	DESAFIO_INACTIVO = 0,
	DESAFIO_ACTIVO
} desafio_state_t;


boton_t botones[CANT_CANALES] = {
		{GPIOC, GPIO_PIN_0, 0, false, false},
		{GPIOC, GPIO_PIN_1, 0, false, false},
		{GPIOC, GPIO_PIN_2, 0, false, false},
		{GPIOC, GPIO_PIN_3, 0, false, false},
};

led_t leds[CANT_CANALES] = {
		{GPIOC, GPIO_PIN_4},
		{GPIOC, GPIO_PIN_5},
		{GPIOC, GPIO_PIN_6},
		{GPIOC, GPIO_PIN_7}
};

desafio_state_t estado_desafio = DESAFIO_INACTIVO;
uint8_t canal_objetivo = 0;
uint32_t tiempo_restante_ms = 0;
uint32_t blink_cnt_ms = 0;

uint32_t aciertos = 0;
uint32_t errores = 0;

void task_led_init(){

	for (int i = 0; i < CANT_CANALES; i++){
		HAL_GPIO_WritePin(leds[i].port, leds[i].pin, GPIO_PIN_RESET);
		botones[i].rebote_cnt = 0;
		botones[i].presionado = false;
		botones[i].presionado_previo = false;
	}
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	estado_desafio = DESAFIO_INACTIVO;
}



uint32_t task_led_get_aciertos()
{
    return aciertos;
}

uint32_t task_led_get_errores()
{
    return errores;
}

void task_led_update(void){

    int8_t boton_presionado = -1;

    for (int i = 0; i < CANT_CANALES; i++){
        if (HAL_GPIO_ReadPin(botones[i].port, botones[i].pin) == GPIO_PIN_RESET){
            if (botones[i].rebote_cnt < REBOTE_MS)
                botones[i].rebote_cnt++;
            else
                botones[i].presionado = true;
        }
        else{
            botones[i].rebote_cnt = 0;
            botones[i].presionado = false;
        }


        if (botones[i].presionado && !botones[i].presionado_previo){
            boton_presionado = i;
        }
        botones[i].presionado_previo = botones[i].presionado;
    }

    switch (estado_desafio){
        case DESAFIO_INACTIVO:

            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET){
                canal_objetivo = HAL_GetTick() % CANT_CANALES;
                tiempo_restante_ms = TIEMPO_LIMITE_MS;
                blink_cnt_ms = 0;

                HAL_GPIO_WritePin(leds[canal_objetivo].port, leds[canal_objetivo].pin, GPIO_PIN_SET);
                estado_desafio = DESAFIO_ACTIVO;
            }
            break;

        case DESAFIO_ACTIVO:

            blink_cnt_ms++;
            if (blink_cnt_ms >= PERIODO_BLINK_MS){
                blink_cnt_ms = 0;
                HAL_GPIO_TogglePin(leds[canal_objetivo].port, leds[canal_objetivo].pin);
            }

            if (boton_presionado != -1){
                HAL_GPIO_WritePin(leds[canal_objetivo].port, leds[canal_objetivo].pin, GPIO_PIN_RESET);

                if (boton_presionado == canal_objetivo){

                    aciertos++;
                    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
                }
                else{

                    errores++;
                    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
                }

                estado_desafio = DESAFIO_INACTIVO;
                break;
            }


            if (tiempo_restante_ms > 0){
                tiempo_restante_ms--;
                if (tiempo_restante_ms == 0){

                    errores++;
                    HAL_GPIO_WritePin(leds[canal_objetivo].port, leds[canal_objetivo].pin, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
                    estado_desafio = DESAFIO_INACTIVO;
                }
            }
            break;
    }
}


