#include "counter_tasks.h"
#include "console.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Static shared counter and mutex (private to this module) */
static uint32_t sharedCounter = 0;
static SemaphoreHandle_t xCounterMutex = NULL;

static void vTaskA(void *pvParameters);
static void vTaskB(void *pvParameters);

void counter_tasks_create(void)
{
    /* Create mutex */
    xCounterMutex = xSemaphoreCreateMutex();
    if (xCounterMutex == NULL) for(;;);

   /* Task A */
    xTaskCreate(
        vTaskA,
        "TaskA",
        configMINIMAL_STACK_SIZE + 128,
        NULL,
        tskIDLE_PRIORITY + 4,
        NULL
    );

    /* Task B */
    xTaskCreate(
        vTaskB,
        "TaskB",
        configMINIMAL_STACK_SIZE + 128,
        NULL,
        tskIDLE_PRIORITY + 3,
        NULL
    );
}

static void vTaskA(void *pvParameters)
{
    (void)pvParameters;
    uint32_t lVal;

    for (;;)
    {
        if (xSemaphoreTake(xCounterMutex, pdMS_TO_TICKS(10)) == pdTRUE) {
            sharedCounter += 1u;
            lVal = sharedCounter;
            xSemaphoreGive(xCounterMutex);
        }

        console_print("[Task A] SharedCounter = %d\n", lVal);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void vTaskB(void *pvParameters)
{
    (void)pvParameters;
    uint32_t lVal;

    for (;;)
    {
        if (xSemaphoreTake(xCounterMutex, pdMS_TO_TICKS(10)) == pdTRUE) {
            sharedCounter += 10u;
            lVal = sharedCounter;
            xSemaphoreGive(xCounterMutex);
        }

        console_print("[Task B] SharedCounter = %d\n", lVal);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
