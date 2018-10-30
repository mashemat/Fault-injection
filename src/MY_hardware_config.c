#include "MY_hardware_config.h"
#include "MY_global_handlers.h"
#include "MY_fault_injector.h"

/* Discovery headers */
#include "stm32f3xx.h"
#include "stm32f3_discovery.h"
#include "stm32f3_discovery_gyroscope.h"
#include "stm32f3_discovery_accelerometer.h"

/* GLOBALS */
extern TIM_HandleTypeDef TIM2_HANDLE;
extern UART_HandleTypeDef UART1_HANDLE;
extern int MEMS_GYRO_enabled;
extern int MEMS_ACCELERO_enabled;


/* ****** FUNCTIONS DEFINITION ************************************************************/

void HC_SystemClock_Config (void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;	// Select external oscillator
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;		// Select external prescaler
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;					// Enable external oscillator
	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;					// Disable internal oscillator
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;				// Enable PLL
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;		// Select PLL clock source
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;				// Select PLL multiplier
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);							// Select the clock to configure
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;	// Select system clock source
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;			// AMBA HighPerformance clock divider
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;			// AMBA Peripheral 1 clock divider
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;			// AMBA Peripheral 2 clock divider
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}
void HC_TIM2_Config(void)
{
	TIM_OC_InitTypeDef TIM2_Config;
	TIM2_Config.OCMode = TIM_OCMODE_TIMING;
	TIM2_Config.Pulse = HC_TIM_PERIOD;
	TIM2_Config.OCPolarity = TIM_OCPOLARITY_LOW;

	TIM2_HANDLE.Instance = TIM2;								// Select timer to use
	TIM2_HANDLE.Init.Prescaler = 1000;							// Choose the prescaler value
	TIM2_HANDLE.Init.CounterMode = TIM_COUNTERMODE_UP;			// Counting mode
	TIM2_HANDLE.Init.Period = HC_TIM_PERIOD;					// Timer period
	TIM2_HANDLE.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;	// Divisor for the timer

	 HAL_TIM_OC_Init(&TIM2_HANDLE);
	 __HAL_TIM_CLEAR_FLAG(&TIM2_HANDLE, TIM_FLAG_UPDATE);
	 HAL_TIM_OC_ConfigChannel(&TIM2_HANDLE,&TIM2_Config,TIM_CHANNEL_2);
	 HAL_TIM_OC_Start_IT(&TIM2_HANDLE,TIM_CHANNEL_2);
}
void HC_LED3_Config(void)
{
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.Pin = LED3_PIN;
	gpio_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_struct.Speed = GPIO_SPEED_HIGH;
	gpio_struct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOE,&gpio_struct);
	HAL_GPIO_WritePin(GPIOE, LED3_PIN,GPIO_PIN_RESET);
}
void HC_UART1_Config(void)
{
	UART1_HANDLE.Instance = USART1;									// Select USART1
	UART1_HANDLE.Init.BaudRate = 115200;  							// Baudrate setting
	UART1_HANDLE.Init.WordLength = UART_WORDLENGTH_8B;				// Words of 8 bits
	UART1_HANDLE.Init.StopBits = UART_STOPBITS_1;					// 1 Stopbit
	UART1_HANDLE.Init.Parity = UART_PARITY_NONE;					// No parity
	UART1_HANDLE.Init.Mode = UART_MODE_TX;							// Only TX
	UART1_HANDLE.Init.HwFlowCtl = UART_HWCONTROL_NONE;				// No HW control
	UART1_HANDLE.Init.OverSampling = UART_OVERSAMPLING_8;			// Oversampling 8 bits
	UART1_HANDLE.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;	// Disable single bit sampling
	HAL_UART_Init(&UART1_HANDLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5; 	// PC5 = TX  ;  PC4 = RX on the board
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;			// Select alternate function PushPull
	GPIO_InitStruct.Pull = GPIO_NOPULL;				// No pulldown nor pullup activated
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;	// Use at high frequencies
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;	// USART1 functionality of those pins is used
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
void HC_GYRO_Config(void)
{
	if(BSP_GYRO_Init()==GYRO_OK)
	{
		MEMS_GYRO_enabled = 1;
	}
	else
	{
		MEMS_GYRO_enabled = 0;
	}
}
void HC_ACCELERO_Config(void)
{
	if(BSP_ACCELERO_Init()==ACCELERO_OK)
		{
			MEMS_ACCELERO_enabled = 1;
		}
		else
		{
			MEMS_ACCELERO_enabled = 0;
		}
}
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM2_HANDLE);
}
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	FI_exec();
}

