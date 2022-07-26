#include "HAL_MAX30100.h"

I2C_HandleTypeDef *MAX30100_ui2c;
extern uint8_t MAX30100_ir_sample[16];
extern uint8_t MAX30100_red_sample[16];
uint8_t MAX30100_ir_current;
uint8_t MAX30100_red_current;
uint8_t MAX30100_mode;

//Escreve em um registrador do sensor via I2C
void HAL_MAX30100_WriteReg(uint8_t regAddr, uint8_t byte){
	uint8_t reg[2] = { regAddr, byte };
	HAL_I2C_Master_Transmit(MAX30100_ui2c, MAX30100_I2C_ADDR, reg, 2, 10);
}
//Le um registrador do sensor via I2C
uint8_t HAL_MAX30100_ReadReg(uint8_t regAddr){
	uint8_t reg = regAddr, result;
	HAL_I2C_Master_Transmit(MAX30100_ui2c, MAX30100_I2C_ADDR, &reg, 1, 10);
	HAL_I2C_Master_Receive(MAX30100_ui2c, MAX30100_I2C_ADDR, &result, 1, 10);
	
	return result;
}
//Limpa a FIFO do sensor (Fila de dados lidos)
void HAL_MAX30100_ClearFIFO()
{
	HAL_MAX30100_WriteReg(MAX30100_FIFO_WR_PTR, 0x00);
	HAL_MAX30100_WriteReg(MAX30100_FIFO_RD_PTR, 0x00);
	HAL_MAX30100_WriteReg(MAX30100_OVF_COUNTER, 0x00);
}
//Le a FIFO do sensor
void HAL_MAX30100_ReadFIFO()
{
	uint8_t num_sample = 64;
	uint8_t fifo_data[64] = { 0 };
	uint8_t reg = MAX30100_FIFO_DATA;
	HAL_I2C_Master_Transmit(MAX30100_ui2c, MAX30100_I2C_ADDR, &reg, 1, 10); 							//Requisição de leitura
	HAL_I2C_Master_Receive(MAX30100_ui2c, MAX30100_I2C_ADDR, fifo_data, num_sample, 10); 	//Recebimento dos dados
	for(uint8_t i = 0; i < num_sample; i += 4) //separando os dados de cada led em seus devidos arrays
	{
		MAX30100_ir_sample[i/4] = (fifo_data[i] << 8) | fifo_data[i + 1];
		MAX30100_red_sample[i/4] = (fifo_data[i + 2] << 8) | fifo_data[i + 3];
	}

}
//Inicializa a instancia do I2C do sensor e limpa a FIFO
void HAL_MAX30100_Init(I2C_HandleTypeDef *ui2c)
{
	MAX30100_ui2c = ui2c;
	HAL_MAX30100_ClearFIFO();
}
//Configura a taxa de amostragem de SpO2 do sensor
void HAL_MAX30100_SetSpO2SampleRate(enum MAX30100_SpO2SR sr)
{
	uint8_t spo2Reg = HAL_MAX30100_ReadReg(MAX30100_SPO2_CONFIG);
	spo2Reg = ((sr << MAX30100_SPO2_SR) & 0x1c) | (spo2Reg & ~0x1c);
	HAL_MAX30100_WriteReg(MAX30100_SPO2_CONFIG, spo2Reg);
}
//Configura a largura de pulso do led do sensor (IR e RED leds)
void HAL_MAX30100_SetLEDPulseWidth(enum MAX30100_LEDPulseWidth pw)
{
	uint8_t spo2Reg = HAL_MAX30100_ReadReg(MAX30100_SPO2_CONFIG);
	spo2Reg = ((pw << MAX30100_LED_PW) & 0x03) | (spo2Reg & ~0x03);
	HAL_MAX30100_WriteReg(MAX30100_SPO2_CONFIG, spo2Reg);
}
//Configura a corrente elétrica que passa nos leds do sensor
void HAL_MAX30100_SetLEDCurrent(enum MAX30100_LEDCurrent redpa, enum MAX30100_LEDCurrent irpa)
{
	MAX30100_red_current = redpa;
	MAX30100_ir_current = irpa;
	HAL_MAX30100_WriteReg(MAX30100_LED_CONFIG, (redpa << MAX30100_LED_RED_PA) | irpa);
}
//Configura o modo de operação do sensor
void HAL_MAX30100_SetMode(enum MAX30100_Mode mode)
{
	MAX30100_mode = mode;
	uint8_t modeReg = (HAL_MAX30100_ReadReg(MAX30100_MODE_CONFIG) & ~(0x07)) | ((mode << MAX30100_MODE) & 0x07);
	if(mode == MAX30100_SPO2_MODE)
		modeReg |= 0x08;
	else
		modeReg &= ~0x08;
	HAL_MAX30100_WriteReg(MAX30100_MODE_CONFIG, modeReg);
}
