//Sensor MAX30100
//https://github.com/oxullo/Arduino-MAX30100

#ifndef _HAL_MAX30100_HEADER_SENTRY_
#define _HAL_MAX30100_HEADER_SENTRY_

#include "main.h"

//Registradores
#define MAX30100_I2C_ADDR						0xae //endereço do sensor I2C escrita (Por algum motivo ele também atende para leitura)
#define MAX30100_FIFO_WR_PTR				0x02 //ponteiro de escrita
#define MAX30100_OVF_COUNTER				0x03 //contador de overflow da fifo
#define MAX30100_FIFO_RD_PTR				0x04 //ponteiro de leitura da fifo
#define MAX30100_FIFO_DATA					0x05 //endereço dos dados do sensor

//Registradores de configuração
//Configuração de modo
#define MAX30100_MODE_CONFIG				0x06 //configuração dos modos de operação
#define MAX30100_MODE								0    //posição do bit

//Configurações de SpO2
#define MAX30100_SPO2_CONFIG				0x07
#define MAX30100_SPO2_SR						2    
#define MAX30100_LED_PW							0

//Configurações dos LEDS
#define MAX30100_LED_CONFIG					0x09
#define MAX30100_LED_RED_PA					4

//Valores de Sample Rate (taxa de amostragem)
typedef enum MAX30100_SpO2SR
{
	/*
	MAX30100_SPO2SR_50, MAX30100_SPO2SR_100,
	MAX30100_SPO2SR_167, MAX30100_SPO2SR_200,
	MAX30100_SPO2SR_400, MAX30100_SPO2SR_600,
	MAX30100_SPO2SR_800, MAX30100_SPO2SR_1000,
	*/
	MAX30100_SPO2SR_DEFAULT = 1,
} MAX30100_SpO2SR;

//Valores de Pulse Width (largura do pulso do LED)
typedef enum MAX30100_LEDPulseWidth
{
	/*
	MAX30100_LEDPW_200,
	MAX30100_LEDPW_400,
	MAX30100_LEDPW_800,
	MAX30100_LEDPW_1600,
	*/
	MAX30100_LEDPW_DEFAULT = 3,
} MAX30100_LEDPulseWidth;

//Valores de corrente nos leds do sensor
typedef enum MAX30100_LEDCurrent {
	/*
	MAX30100_LEDCURRENT_0_0, MAX30100_LEDCURRENT_4_4, MAX30100_LEDCURRENT_7_6, MAX30100_LEDCURRENT_11_0,
	MAX30100_LEDCURRENT_14_2, MAX30100_LEDCURRENT_17_4, MAX30100_LEDCURRENT_20_8, MAX30100_LEDCURRENT_24_0,
	MAX30100_LEDCURRENT_27_1, MAX30100_LEDCURRENT_30_6, MAX30100_LEDCURRENT_33_8, MAX30100_LEDCURRENT_37_0,
	MAX30100_LEDCURRENT_40_2, MAX30100_LEDCURRENT_43_6, MAX30100_LEDCURRENT_46_8, MAX30100_LEDCURRENT_50_0,
	*/
	MAX30100_LEDCURRENT_DEFAULT = 15,
} MAX30100_LEDCurrent;

//Modos de operação
typedef enum MAX30100_Mode
{
	MAX30100_IDLE_MODE = 0x00, 		//idle, baixo consumo
	MAX30100_HRONLY_MODE = 0x02, 	//somente batimentos
	MAX30100_SPO2_MODE = 0x03, 		//somente oxigenação sanguinea
} MAX30100_Mode;

void HAL_MAX30100_WriteReg(uint8_t regAddr, uint8_t byte);
uint8_t HAL_MAX30100_ReadReg(uint8_t regAddr);
void HAL_MAX30100_ClearFIFO();
void HAL_MAX30100_ReadFIFO();
void HAL_MAX30100_Init(I2C_HandleTypeDef *ui2c);
void HAL_MAX30100_SetSpO2SampleRate(enum MAX30100_SpO2SR sr);
void HAL_MAX30100_SetLEDPulseWidth(enum MAX30100_LEDPulseWidth pw);
void HAL_MAX30100_SetLEDCurrent(enum MAX30100_LEDCurrent redpa, enum MAX30100_LEDCurrent irpa);
void HAL_MAX30100_SetMode(enum MAX30100_Mode mode);

#endif
