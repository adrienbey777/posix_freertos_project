#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "console.h"
#include "counter_tasks.h"
#include "timer_tasks.h"

/* Timer semaphore for Task C */
SemaphoreHandle_t xTimerSemaphore = NULL;

/* Timer callback */
void vTimerCallback(TimerHandle_t xTimer)
{
    (void)xTimer;
    console_print(">> [Timer] Callback executed\n");
    xSemaphoreGive(xTimerSemaphore);
}

int main(void)
{
    console_init();
    /* Create timer semaphore */
    xTimerSemaphore = xSemaphoreCreateBinary();
    if (xTimerSemaphore == NULL) for(;;);

    /* Create periodic timer */
    TimerHandle_t xTimer = xTimerCreate(
        "Timer1",
        pdMS_TO_TICKS(1000),
        pdTRUE,
        NULL,
        vTimerCallback
    );
    if (xTimer == NULL) for(;;);
    xTimerStart(xTimer, 0);

    /* Create tasks */
    createCounterTasks();  /* Task A + B */
    createTimerTasks();    /* Task C + D */

    /* Start scheduler */
    vTaskStartScheduler();

    for (;;);
}
