/*
 * FREERTOS_V9.0.0_atmega32_Z_SecondShoot.c
 *
 * Created: 03/12/2018 21:59:08
 * Author : Mahmoud
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include "FREERTOS.h"
#include "task.h"
#include "queue.h"

void task1(void * pv);
void task2(void * pv);

typedef struct tasks_info 
{
	char px_data_byte;
}tasks_info_t;
void main(void)
{
	tasks_info_t obj_1;
	DDRA=0xff;		DDRB=0xff;		DDRC=0xff;		DDRD=0xff;
	char msa=0xff;
	xQueueHandle queue_1_handle=xQueueCreate( 5, sizeof(int*));
	if (queue_1_handle != NULL)
	{
		obj_1.px_data_byte= msa;
		xTaskCreate(task1,NULL,configMINIMAL_STACK_SIZE,(void *)&obj_1,1,NULL);
		xTaskCreate(task2,NULL,configMINIMAL_STACK_SIZE,(void *)&obj_1,2,NULL);
		vTaskStartScheduler();
	} 
	else //couldn't create a queue
	{
		PORTA=PORTB=PORTC=PORTD=0x55;
	}
	
}
void task1(void * pv)
{
	while(1)
	{
		PORTA=(((tasks_info_t *)pv)->px_data_byte++);
		xQueueSendToBack(queue_1_handle,( ( (tasks_info_t *)pv )->px_data_byte ),10);
		vTaskDelay(100);
	}
}

void task2(void * pv)
{
	portBASE_TYPE rx_buff=0;
	while(1)
	{
		xQueueReceive(queue_1_handle,&rx_buff,10);
		PORTA= rx_buff;
		vTaskDelay(100);
	}
}


//testing the running of v9.0.0
/*
void task4(void * pv)
{
	while(1)
	{
		//for (uint16_t a=1;a>0;a++);
		PORTD ^= (1<<3);
		(*(char *)pv)--;
		vTaskDelay(20);
	}
}

void task5(void * pv)
{
	while(1)
	{
// 		xTaskCreate(task1,NULL,configMINIMAL_STACK_SIZE,pv,1,NULL);//&A it would be better if a structure and you r the user and know hot it'll be used
// 		xTaskCreate(task2,NULL,configMINIMAL_STACK_SIZE,pv,2,NULL);//&A it would be better if a structure and you r the user and know hot it'll be used
// 		xTaskCreate(task3,NULL,configMINIMAL_STACK_SIZE,pv,3,NULL);//&A it would be better if a structure and you r the user and know hot it'll be used
		xTaskCreate(task4,NULL,configMINIMAL_STACK_SIZE,pv,4,NULL);//&A it would be better if a structure and you r the user and know hot it'll be used
		vTaskDelete(NULL);
		PORTD=0xff;
	}
}

int main(void)
{
	
	DDRA=0xff;
	DDRB=0xff;
	DDRC=0xff;
	DDRD=0xff;
	char msa=0xff;

	xTaskCreate(task5,NULL,configMINIMAL_STACK_SIZE,(void *)&msa,5,NULL);//&A it would be better if a structure and you r the user and know hot it'll be used
	vTaskStartScheduler();
}
*/

