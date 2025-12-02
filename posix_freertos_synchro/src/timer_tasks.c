#include "timer_tasks.h"
#include "console.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* External timer semaphore from main.c */
extern SemaphoreHandle_t xTimerSemaphore;

/* Task D handle */
TaskHandle_t xTaskDHandle = NULL;

static void vTaskC(void *pvParameters);
static void vTaskD(void *pvParameters);

void createTimerTasks(void)
{
    /* Task C */
    xTaskCreate(
        vTaskC,
         "TaskC", 
         configMINIMAL_STACK_SIZE + 128, 
         NULL, 
         tskIDLE_PRIORITY + 2, 
         NULL
    );

    /* Task D (suspended at start) */
    xTaskCreate(
        vTaskD, 
        "TaskD", 
        configMINIMAL_STACK_SIZE + 128, 
        NULL, 
        tskIDLE_PRIORITY + 1, 
        &xTaskDHandle
    );

    vTaskSuspend(xTaskDHandle);
}

static void vTaskC(void *pvParameters)
{
    (void)pvParameters;
    uint8_t lFirst_call = 1u;
    for (;;) 
    {
        if (xSemaphoreTake(xTimerSemaphore, portMAX_DELAY) == pdTRUE)
        {
            if(lFirst_call == 1u)
            {
                console_print("[Task C] Timer triggered, starting Task D...\n");
                vTaskResume(xTaskDHandle);
                lFirst_call = 0u;
            }
            else
            {
                console_print("[Task C] Timer triggered\n");
            }
        }
    }
}

static void vTaskD(void *pvParameters)
{
    (void)pvParameters;

    console_print("[Task D] Started!\n");

    for (;;)
    {
        console_print("[Task D] Running...\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
