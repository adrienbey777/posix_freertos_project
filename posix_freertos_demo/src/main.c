#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* FreeRTOS kernel includes */
#include "FreeRTOS.h"
#include "task.h"

/* Thread-safe console */
#include "console.h"

/* Idle Hook: do nothing */
void vApplicationIdleHook(void)
{
    // Idle Task: short, non-blocking
}

/* Task prototypes */
static void vTaskA(void *pvParameters);
static void vTaskB(void *pvParameters);

int main(void)
{
    /* Initialize thread-safe console */
    console_init();

    console_print("=== FreeRTOS Startup ===\r\n");

    /* --- Create tasks --- */

    BaseType_t xReturned;

    /* Task A */
    xReturned = xTaskCreate(
                    vTaskA,
                    "TaskA",
                    configMINIMAL_STACK_SIZE + 128,
                    NULL,
                    tskIDLE_PRIORITY + 2,
                    NULL);

    if (xReturned != pdPASS) {
        console_print("Error: TaskA creation failed!\r\n");
        for(;;);
    }

    /* Task B */
    xReturned = xTaskCreate(
                    vTaskB,
                    "TaskB",
                    configMINIMAL_STACK_SIZE + 128,
                    NULL,
                    tskIDLE_PRIORITY + 1,
                    NULL);

    if (xReturned != pdPASS) {
        console_print("Error: TaskB creation failed!\r\n");
        for(;;);
    }

    /* Start the scheduler */
    console_print("Starting the scheduler...\r\n");
    vTaskStartScheduler();

    /* Should never reach here */
    console_print("Error: vTaskStartScheduler returned!\r\n");
    for(;;);
}

/* Task implementations */

static void vTaskA(void *pvParameters)
{
    (void) pvParameters;

    for (;;) {
        console_print("[Task A] Tick = %lu\r\n",
                      (unsigned long) xTaskGetTickCount());
        vTaskDelay(pdMS_TO_TICKS(700));   // Different periodicity
    }
}

static void vTaskB(void *pvParameters)
{
    (void) pvParameters;

    for (;;) {
        console_print(">> [Task B] Tick = %lu\r\n",
                      (unsigned long) xTaskGetTickCount());
        vTaskDelay(pdMS_TO_TICKS(1200));  // Different periodicity
    }
}
