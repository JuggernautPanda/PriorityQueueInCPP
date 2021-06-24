# PriorityQueueInCPP
This is an implementation of priority queue in CPP using OOPS concepts.

Structure of the input:

struct InPut {
	int priority;
	string value;
};

Output:

4, Access is granted.
4, Access is denied.
3, Access is granted.
2, Access is granted.

![alt text](https://raw.githubusercontent.com/JuggernautPanda/PriorityQueueInCPP/main/Screenshot%20from%202021-06-24%2016-14-24.png)

Edge case:

Same priority 

How the edge case was handled:

Based on the value  - Accept or Decline
precedence is given to values of Accept.

How to use the code:

Clone the directory
Compile for g++ 
Compile: g++ -Wall -c "%f" 
Link: g++ -Wall -o "%e" "%f" 
Execute: "./%e" \n
Refer the attached screenshot. 
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Use case relating to STM32 :

Priority queues are used in FreeRTOS pre emptive mode.

Threads are created with multiple priorities.

They can create priority inversion and priority inheritance.

Let us try to understand this by considering 3 tasks - one with high priority, one with medium and the other with the least priority.

===================================================================================================================

SemaphoreHandle_t SimpleMutex;
SemaphoreHandle_t BinSemaphore;


TaskHandle_t HPT_Handler;
TaskHandle_t MPT_Handler;
TaskHandle_t LPT_Handler;


void HPT_Task (void *argument);
void MPT_Task (void *argument);
void LPT_Task (void *argument);


void Send_Uart (uint8_t *str)
{
	xSemaphoreTake(BinSemaphore, portMAX_DELAY);
	HAL_Delay(5000);
	HAL_UART_Transmit(&huart2, str, strlen (str), HAL_MAX_DELAY);
	xSemaphoreGive(BinSemaphore);
}

void HPT_Task (void *argument)
{
	uint8_t *strtosend = "IN HPT===========================\n";
	while (1)
	{
		char *str = "Entered HPT and About to take Semaphore\n";
		HAL_UART_Transmit(&huart2, str, strlen (str), HAL_MAX_DELAY);

		Send_Uart(strtosend);

		char *str2 = "Leaving HPT\n\n";
		HAL_UART_Transmit(&huart2, str2, strlen (str2), HAL_MAX_DELAY);

		vTaskDelay(750);
	}
}


void MPT_Task (void *argument)
{
	while (1)
	{
		char *str = "IN MPT****************************\n\n";
		HAL_UART_Transmit(&huart2, str, strlen (str), HAL_MAX_DELAY);
		vTaskDelay(2000);
	}
}

void LPT_Task (void *argument)
{
	uint8_t *strtosend = "IN LPT...........................\n";
	while (1)
	{
		char *str = "Entered LPT and About to take Semaphore\n";
		HAL_UART_Transmit(&huart2, str, strlen (str), HAL_MAX_DELAY);

		Send_Uart(strtosend);

		char *str2 = "Leaving LPT\n\n";
		HAL_UART_Transmit(&huart2, str2, strlen (str2), HAL_MAX_DELAY);

		vTaskDelay(1000);
	}
}

===================================================================================================================


Inside the main function, let us create 3 threads in FreeRTOS

int main()
{

SimpleMutex = xSemaphoreCreateMutex();

  if (SimpleMutex != NULL)
  {
	  HAL_UART_Transmit(&huart2, "Mutex Created\n\n", 15, 1000);
  }

  BinSemaphore = xSemaphoreCreateBinary();
  if (BinSemaphore != NULL)
  {
	  HAL_UART_Transmit(&huart2, "Semaphore Created\n\n", 19, 1000);
  }

  xSemaphoreGive(BinSemaphore);

  /// create tasks

  xTaskCreate(HPT_Task, "HPT", 128, NULL, 3, &HPT_Handler);
  xTaskCreate(MPT_Task, "MPT", 128, NULL, 2, &MPT_Handler);
  xTaskCreate(LPT_Task, "LPT", 128, NULL, 1, &LPT_Handler);

  vTaskStartScheduler();
  
  }
  
  =========================================================================================================
  
The MPT can preempt the LPT, and therefore it delays the execution of the HPT also.

HPT even being the Highest priority Task, have to wait for the MPT to finish. This scenario is termed as PRIORITY INVERSION

References:

1 ) FreeRTOS PRIORITY INVERSION article - https://controllerstech.com/freertos-tutorial-7-using-mutex/
