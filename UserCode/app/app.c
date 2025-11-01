/**
 * @file    app.h
 * @author  syhanjin
 * @date    2025-11-01
 */
#include "app.h"
#include "cmsis_os2.h"
#include "usart.h"

#include "drivers/HWT101CT.h"

HWT101CT_t sensor;

void Uart_RxCpltCallback(UART_HandleTypeDef* huart)
{
    if (huart == sensor.huart)
    {
        HWT101CT_RxCallback(&sensor);
    }
}

/**
 * @brief Function implementing the initTask thread.
 * @param argument: Not used
 * @retval None
 */
void Init(void* argument)
{
    /* 初始化代码 */
    HAL_UART_RegisterCallback(&huart2, HAL_UART_RX_COMPLETE_CB_ID, Uart_RxCpltCallback);
    HWT101CT_Init(&sensor, &huart2);

    HWT101CT_Calibrate(&sensor, 3000);

    osDelay(1000);
    HWT101CT_ResetYaw(&sensor);

    /* 初始化完成后退出线程 */
    osThreadExit();
}