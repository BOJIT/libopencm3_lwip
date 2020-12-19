/**
 * @file
 * @brief Port-specific application configuration (put things here that may
 * be required by non-driver code).
 *
 * @author @htmlonly &copy; @endhtmlonly 2020 James Bennion-Pedley
 *
 * @date 7 June 2020
 */

#ifndef __PORT_CONFIG__
#define __PORT_CONFIG__

/* Configuration includes */
#include <globalConfig.h>

/*----------------------------------------------------------------------------*/

/* Clock configuration */
#define HSE_FREQ         8000000    ///< MCU input oscillator frequency
#define SYSCLK_FREQ      96000000   ///< Core MCU system frequency


/*----------------------------------------------------------------------------*/

/* LED configuration */
#define SYSTEM_LED_PORT     GPIOB       ///< GPIO Port for System LED
#define SYSTEM_LED_PIN      GPIO0       ///< GPIO Pin for System LED
#define SYSTEM_LED_RCC      RCC_GPIOB   ///< RCC (clock enable) for System LED
#define STATUS_LED_PORT     GPIOB       ///< GPIO Port for Status LED
#define STATUS_LED_PIN      GPIO7       ///< GPIO Pin for StatusLED
#define STATUS_LED_RCC      RCC_GPIOB   ///< RCC (clock enable) for Status LED
#define WARNING_LED_PORT    GPIOB       ///< GPIO Port for Warning LED
#define WARNING_LED_PIN     GPIO14      ///< GPIO Pin for Status LED
#define WARNING_LED_RCC     RCC_GPIOB   ///< RCC (clock enable) for Warning LED


/*----------------------------------------------------------------------------*/

#if DEBUG_LEVEL >= DEBUG_ERRORS
    /* Serial configuration */
    #define DEBUG_UART_PORT     GPIOD     ///< GPIO Port for UART Rx and Tx
    #define DEBUG_UART_TX       GPIO8     ///< GPIO Pin for Tx Pin
    #define DEBUG_UART_RX       GPIO9     ///< GPIO Pin for Rx Pin
    #define DEBUG_UART_RCC      RCC_GPIOD ///< RCC (clock enable) for UART
#endif /* DEBUG_LEVEL >= DEBUG_ERRORS */


/*----------------------------------------------------------------------------*/

/* Ethernet configuration */
#define LWIP_PHY_ADDRESS         PHY0        ///< PHY Address for SMI bus
#define LWIP_PHY_LAN8742A    ///< PHY chipset

/* Configure PPS pin to show on output */
#define LWIP_PTP_PPS                1

/*----------------------------------------------------------------------------*/

#endif /* __PORT_CONFIG__ */
