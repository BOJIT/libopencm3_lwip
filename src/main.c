/**
 * @file
 * @brief Main entry point for the program
 *
 */

#include <string.h>

#include <lwip/api.h>

/* Inclue FreeRTOS headers */
#include <FreeRTOS.h>
#include <task.h>

/* Configuration includes */
#include <globalConfig.h>

/* Port functions */
#include <port/portCore.h>
#include <port/portEthernet.h>
#include <port/portSerial.h>

/* Task 1 */
static void startTask1(void *args __attribute((unused)))
{

    for (;;) {
        vTaskDelay(1000);
    }
}

/* Task 3 - Blink Warning LED */
static void startTask3(void *args __attribute((unused)))
{

    portEthInit(); // Configure Ethernet GPIOs and registers

    struct netconn *conn;
    char msg[] = "alpha";
    struct netbuf *buf;
    char * data;

    conn = netconn_new(NETCONN_UDP);
    netconn_bind(conn, IP_ADDR_ANY, 80); //local port

    netconn_connect(conn, IP_ADDR_BROADCAST, 8080);

    for (;;) {
        buf = netbuf_new();
        data = netbuf_alloc(buf, sizeof(msg));
        memcpy(data, msg, sizeof(msg));
        netconn_send(conn, buf);
        netbuf_delete(buf); // De-allocate packet buffer
        vTaskDelay(10000);
    }
}

/**
 * @brief This is the main entry point to the program
*/
int main(void)
{

    portClockInit();  // Configure RCC, System Clock Tree, PLL, etc...

    xTaskCreate(startTask1, "task1", 350, NULL, 5, NULL);
    xTaskCreate(startTask3, "task3", 1024, NULL, FREERTOS_PRIORITIES-3, NULL);

    vTaskStartScheduler();

    /* This point is never reached, as the scheduler is blocking! */
    for (;;);
    return 0;
}
