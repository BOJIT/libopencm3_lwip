#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/**
 * @file
 * @brief lwIP application configuration
 *
 * @author @htmlonly &copy; @endhtmlonly 2020 James Bennion-Pedley
 *
 * @date 7 June 2020
 */

/* Configuration includes */
#include <globalConfig.h>
#include <portConfig.h>

/*------------------------ Architecture Configuration ------------------------*/

#define MEM_ALIGNMENT 4             ///< Architecture is 32-bit
#define MEM_SIZE      (32*1024)     ///< Set lwIP heap size

#define TCP_SND_BUF (8*TCP_MSS)     ///< Allocate more TCP buffer space

#define PBUF_POOL_SIZE 32           ///< Number pbufs allocated to lwIP

/** Optional Memory Pool Reconfiguration */
//#define TCP_WND     (10*TCP_MSS)
#define MEMP_NUM_TCP_SEG TCP_SND_QUEUELEN   ///< Required for sanity checks!
//#define MEMP_NUM_PBUF 32
//#define MEMP_NUM_TCP_PCB 10


/*--------------------------- Thread Configuration ---------------------------*/

/** FreeRTOS-specific definitions */
#define TCPIP_THREAD_STACKSIZE 1024
#define TCPIP_THREAD_PRIO FREERTOS_PRIORITIES-2 ///< High priority thread
#define TCPIP_MBOX_SIZE 6
#define TCPIP_THREAD_NAME       "ETH_lwip"  ///< Consistent with other threads

/** Template definitions for other lwIP threads */
#define DEFAULT_THREAD_STACKSIZE 1024
#define DEFAULT_THREAD_PRIO 3
#define DEFAULT_UDP_RECVMBOX_SIZE 6
#define DEFAULT_TCP_RECVMBOX_SIZE 6
#define DEFAULT_ACCEPTMBOX_SIZE 6

#if LWIP_FREERTOS_CHECK_CORE_LOCKING
#ifndef LWIP_PTP_CONTEXT// Bodge to stop multiple redundant declarations
    /** Core locking functions (defined in sys_arch.c) */
    void sys_check_core_locking(void);
    void sys_mark_tcpip_thread(void);
    void sys_lock_tcpip_core(void);
    void sys_unlock_tcpip_core(void);
    ///< For some reason, it is advised to declare these functions here rather
    ///< than in sys_arch.h

    #define LWIP_ASSERT_CORE_LOCKED()   sys_check_core_locking()
    #define LWIP_MARK_TCPIP_THREAD()    sys_mark_tcpip_thread()
    #define LOCK_TCPIP_CORE()           sys_lock_tcpip_core()
    #define UNLOCK_TCPIP_CORE()         sys_unlock_tcpip_core()
#endif /* LWIP_HDR_OPT_H */
#endif /* LWIP_FREERTOS_CHECK_CORE_LOCKING */


/*--------------------------- Netif Configuration ----------------------------*/

/** Checksum disable (calculated in hardware) */
#define CHECKSUM_GEN_IP     0
#define CHECKSUM_GEN_UDP    0
#define CHECKSUM_GEN_TCP    0
#define CHECKSUM_GEN_ICMP   0
#define CHECKSUM_CHECK_IP   0
#define CHECKSUM_CHECK_UDP  0
#define CHECKSUM_CHECK_TCP  0
#define CHECKSUM_CHECK_ICMP 0

/** Allow <i>netif</i> functions to be called from another thread */
#define LWIP_NETIF_API                  1
#define LWIP_NETIF_STATUS_CALLBACK      1
#define LWIP_NETIF_LINK_CALLBACK        1


/*---------------------------- lwIP Applications -----------------------------*/

/** API configuration */
#define LWIP_SOCKET  0      ///< Do not include the Socket API
#define LWIP_NETCONN 1      ///< Application uses Netconn API exclusively

/** If DHCP is used, fall back on link-local address */
#if LWIP_DHCP
    #define LWIP_AUTOIP                 1
    #define LWIP_DHCP_AUTOIP_COOP       1
    #define LWIP_DHCP_AUTOIP_COOP_TRIES 3
#endif /* LWIP_DHCP */

/** If hostname is given in global_config.h, initialise netif with hostname */
#ifdef LWIP_HOSTNAME
    #define LWIP_NETIF_HOSTNAME         1
#endif /* LWIP_HOSTNAME */

/** Use IGMP - required for PTP and RTP */
#define LWIP_IGMP                       1


/*-------------------------- LWIP_PTP Configuration --------------------------*/

#define LWIP_PTP                        1

#if LWIP_PTP
    /* PTP system time functions */
    #define LWIP_PTP_GET_TIME           ptp_get_time
    #define LWIP_PTP_SET_TIME           ptp_set_time
    #define LWIP_PTP_UPDATE_COARSE      ptp_update_coarse
    #define LWIP_PTP_UPDATE_FINE        ptp_update_fine

    /* PTP stack timer functions */
    #define LWIP_PTP_INIT_TIMERS        ptp_init_timers
    #define LWIP_PTP_START_TIMER        ptp_start_timer
    #define LWIP_PTP_STOP_TIMER         ptp_stop_timer
    #define LWIP_PTP_CHECK_TIMER        ptp_check_timer

    #define LWIP_PBUF_CUSTOM_DATA \
                    u32_t tv_sec; \
                    u32_t tv_nsec;    ///< Add timestamp fields to pbuf
#endif /* LWIP_PTP */

/*----------------------------------------------------------------------------*/

#endif /* __LWIPOPTS_H__ */
