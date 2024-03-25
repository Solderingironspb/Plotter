/**
 ******************************************************************************
 *  @file Plotter.h
 *  @brief Библиотека для легкой работы с программой Serial port Plotter by Solderingiron v1.0.0
 *  @author Волков Олег
 *  @date 15.03.2024
 *
 ******************************************************************************
 * @attention
 *
 * О Serial port Plotter by Solderingiron:
 * Данная программа предназначена для отрисовки графиков, используя данные с микроконтроллера, при отладке приложений.
 * Для работы требуется связь по UART.
 * С микроконтроллера должны лететь char массивы с числовыми данными.
 * Начало сообщения начинается с символа '$', далее идет число в обычном формате,
 * например '3.14159'. Разделяются числа пробелом. Заканчивается посылка символом ';'
 *
 * Чтоб было совсем понятно, вот пример передачи с микроконтроллера одного числа для отладки:
 * $3.14159;
 * А вот передача четырех чисел:
 * $3.14159 60 125.625 14.259;
 *
 *
 * Пример работы с библиотекой:
 *
 * 		//Создаем переменные
 *      float A = 3.14159f;
 *      float B = 4.81516f;
 *      int32_t C = 54223;
 *      uint8_t D = 25;
 *      int8_t E = -15;
 *
 * 		//Экстерним нужные структуры
 * 		extern struct USART_name husart1; //Объявляем структуру по USART.(см. stm32f103xx_CMSIS.h)
 *      extern Plotter_struct Plotter; //Структура для работы с программой Serial port Plotter
 *
 * 		//Отправка данных
 *		Plotter_open();
 *		Plotter_add_float((float*)&A);
 *		Plotter_add_float((float*)&B);
 *		Plotter_add_unsigned((uint32_t*)&C);
 *		Plotter_add_unsigned((uint32_t*)&D);
 *		Plotter_add_signed((int32_t*)&E);
 *		Plotter_close();
 *		CMSIS_USART_Transmit(USART1, (uint8_t*) Plotter.Buffer, strlen((char*) Plotter.Buffer), 1000); //Отправляем собранный массив данных, Тут уже хоть CMSIS, хоть HAL, хоть что-то еще...
 ******************************************************************************
 */

#ifndef INC_Plotter_H_
#define INC_Plotter_H_

#include <stdio.h>
#include <string.h>
#include "Float_transform.h"

//Структура для работы с программой Serial port Plotter
typedef struct {
	char Buffer[256]; //Общий буфер на отправку данных
	char Temp_buffer[32]; //Временный буфер для формирования данных
}Plotter_struct;

void Plotter_open(void);
void Plotter_close(void);
void Plotter_add_signed(int32_t *Data);
void Plotter_add_unsigned(uint32_t *Data);
void Plotter_add_float(float *Data);
//static void Plotter_add_Temp_Data(void);

#endif /* INC_Plotter_H_ */
