#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#include <os/rtt/rtconfig.h>

#if defined(RT_USING_NEWLIB) || defined(RT_USING_MINILIBC)
#define ERRNO                       1
#define LWIP_TIMEVAL_PRIVATE		1
#endif

#define LWIP_ERROR(...)
#define LWIP_NOASSERT

#define SO_REUSE					0

#define NO_SYS                      0
#define LWIP_SOCKET                 1
#define LWIP_NETCONN                1

#define LWIP_IGMP                   TCPPS_IGMP_ENABLE

#define LWIP_ICMP                   TCPPS_ICMP_ENABLE

#define LWIP_SNMP                   TCPPS_SNMP_ENABLE

#define LWIP_DNS                    TCPPS_DNS_ENABLE

#define LWIP_HAVE_LOOPIF            TCPPS_LOOPIF_ENABLE

#define LWIP_PLATFORM_BYTESWAP      0
#define BYTE_ORDER                  LITTLE_ENDIAN

/* Enable SO_RCVTIMEO processing.   */
#define LWIP_SO_RCVTIMEO            0

#if DEBUG_NET_ENABLE
#define LWIP_DEBUG
#endif

/* ---------- Debug options ---------- */
#ifdef LWIP_DEBUG
#define SYS_DEBUG                   LWIP_DBG_OFF
#define ETHARP_DEBUG                LWIP_DBG_OFF
#define PPP_DEBUG                   LWIP_DBG_OFF
#define MEM_DEBUG                   LWIP_DBG_OFF
#define MEMP_DEBUG                  LWIP_DBG_OFF
#define PBUF_DEBUG                  LWIP_DBG_OFF
#define API_LIB_DEBUG               LWIP_DBG_OFF
#define API_MSG_DEBUG               LWIP_DBG_OFF
#define TCPIP_DEBUG                 LWIP_DBG_OFF
#define NETIF_DEBUG                 LWIP_DBG_OFF
#define SOCKETS_DEBUG               LWIP_DBG_OFF
#define DNS_DEBUG                   LWIP_DBG_OFF
#define AUTOIP_DEBUG                LWIP_DBG_OFF
#define DHCP_DEBUG                  LWIP_DBG_OFF
#define IP_DEBUG                    LWIP_DBG_ON
#define IP_REASS_DEBUG              LWIP_DBG_OFF
#define ICMP_DEBUG                  LWIP_DBG_OFF
#define IGMP_DEBUG                  LWIP_DBG_OFF
#define UDP_DEBUG                   LWIP_DBG_ON
#define TCP_DEBUG                   LWIP_DBG_OFF
#define TCP_INPUT_DEBUG             LWIP_DBG_ON
#define TCP_OUTPUT_DEBUG            LWIP_DBG_ON
#define TCP_RTO_DEBUG               LWIP_DBG_OFF
#define TCP_CWND_DEBUG              LWIP_DBG_OFF
#define TCP_WND_DEBUG               LWIP_DBG_OFF
#define TCP_FR_DEBUG                LWIP_DBG_OFF
#define TCP_QLEN_DEBUG              LWIP_DBG_OFF
#define TCP_RST_DEBUG               LWIP_DBG_OFF
#endif

#define LWIP_DBG_TYPES_ON           (LWIP_DBG_ON|LWIP_DBG_TRACE|LWIP_DBG_STATE|LWIP_DBG_FRESH|LWIP_DBG_HALT)

/* ---------- Memory options ---------- */
#define MEM_ALIGNMENT               RT_ALIGN_SIZE

#define MEM_LIBC_MALLOC             1
#if MEM_LIBC_MALLOC
#define mem_malloc					mem_Malloc
#define mem_free					mem_Free
#define mem_calloc					mem_Calloc
#endif

/* ---------- Memory Pools options ---------- */
#define MEMP_MEM_MALLOC				TCPPS_MEMP_MALLOC

/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
#define MEMP_NUM_PBUF               32

/* the number of UDP protocol control blocks. One per active RAW "connection". */
#define MEMP_NUM_RAW_PCB            TCPPS_RAW_PCB_NUM

/* the number of UDP protocol control blocks. One per active UDP "connection". */
#define MEMP_NUM_UDP_PCB            TCPPS_UDP_PCB_NUM

/* the number of simulatenously active TCP connections. */
#define MEMP_NUM_TCP_PCB            TCPPS_TCP_PCB_NUM

/* the number of simultaneously queued TCP */
#define MEMP_NUM_TCP_SEG            TCPPS_TCP_SEG_NUM

/* The following four are used only with the sequential API and can be
   set to 0 if the application only will use the raw API. */
/* MEMP_NUM_NETBUF: the number of struct netbufs. */
#define MEMP_NUM_NETBUF             4
/* MEMP_NUM_NETCONN: the number of struct netconns. */
#define MEMP_NUM_NETCONN            8
/* MEMP_NUM_TCPIP_MSG_*: the number of struct tcpip_msg, which is used
   for sequential API communication and incoming packets. Used in
   src/api/tcpip.c. */
#define MEMP_NUM_TCPIP_MSG_API      16
#define MEMP_NUM_TCPIP_MSG_INPKT    16

/* ---------- Pbuf options ---------- */
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#define PBUF_POOL_SIZE              TCPPS_PBUF_NUM

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE			1500

/* PBUF_LINK_HLEN: the number of bytes that should be allocated for a
   link level header. */
#define PBUF_LINK_HLEN				16

#define ETH_PAD_SIZE				TCPPS_ETH_PAD_SIZE

/** SYS_LIGHTWEIGHT_PROT
 * define SYS_LIGHTWEIGHT_PROT in lwipopts.h if you want inter-task protection
 * for certain critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */
#define SYS_LIGHTWEIGHT_PROT        (NO_SYS==0)

/* ---------- TCP options ---------- */
#define LWIP_TCP                    TCPPS_TCP_ENABLE

#define TCP_TTL                     255

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ             1

/* TCP Maximum segment size. */
#define TCP_MSS                     (1500 - 40)

/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF                 (2 * TCP_MSS)

/* TCP sender buffer space (pbufs). This must be at least = 2 *
   TCP_SND_BUF/TCP_MSS for things to work. */
#define TCP_SND_QUEUELEN            ((4 * (TCP_SND_BUF) + (TCP_MSS - 1))/(TCP_MSS))

/* TCP writable space (bytes). This must be less than or equal
   to TCP_SND_BUF. It is the amount of space which must be
   available in the tcp snd_buf for select to return writable */
#define TCP_SNDLOWAT                LWIP_MIN(LWIP_MAX(((TCP_SND_BUF)/2), (2 * TCP_MSS) + 1), (TCP_SND_BUF) - 1)

/* TCP receive window. */
#define TCP_WND                     (2 * TCP_MSS)

/* Maximum number of retransmissions of data segments. */
#define TCP_MAXRTX                  4

/* Maximum number of retransmissions of SYN segments. */
#define TCP_SYNMAXRTX               2

/* tcpip thread options */
#define TCPIP_MBOX_SIZE             TCPPS_THREAD_MBOXSIZE
#define TCPIP_THREAD_PRIO           TCPPS_THREAD_PRIORITY
#define TCPIP_THREAD_STACKSIZE      TCPPS_THREAD_STACKSIZE
#define TCPIP_THREAD_NAME           "tcpip"
#define DEFAULT_TCP_RECVMBOX_SIZE   10

/* ---------- ARP options ---------- */
#define LWIP_ARP                    TCPPS_ETH_ENABLE
#define ARP_TABLE_SIZE              10
#define ARP_QUEUEING                0

/* ---------- IP options ---------- */
/* Define IP_FORWARD to 1 if you wish to have the ability to forward
   IP packets across network interfaces. If you are going to run lwIP
   on a device with only one network interface, define this to 0. */
#define IP_FORWARD                  0

/* IP reassembly and segmentation.These are orthogonal even
 * if they both deal with IP fragments */
#define IP_REASSEMBLY               1
#define IP_REASS_MAX_PBUFS          10
#define MEMP_NUM_REASSDATA          10
#define IP_FRAG                     1

/* ---------- ICMP options ---------- */
#define ICMP_TTL                    255

/* ---------- DHCP options ---------- */
/* Define LWIP_DHCP to 1 if you want DHCP configuration of
   interfaces. */
#define LWIP_UDP                    TCPPS_UDP_ENABLE

/* 1 if you want to do an ARP check on the offered address
   (recommended). */
#define DHCP_DOES_ARP_CHECK         (LWIP_DHCP)

/* ---------- AUTOIP options ------- */
#define LWIP_AUTOIP                 0
#define LWIP_DHCP_AUTOIP_COOP       (LWIP_DHCP && LWIP_AUTOIP)

/* ---------- UDP options ---------- */
#define LWIP_UDP                    TCPPS_UDP_ENABLE

#define LWIP_UDPLITE                TCPPS_UDP_ENABLE
#define UDP_TTL                     255
#define DEFAULT_UDP_RECVMBOX_SIZE   2

/* ---------- RAW options ---------- */
#define DEFAULT_RAW_RECVMBOX_SIZE   2
#define DEFAULT_ACCEPTMBOX_SIZE     10

/* ---------- Statistics options ---------- */
#define LWIP_STATS                  0

#if LWIP_STATS
#define LWIP_STATS_DISPLAY          1

#define LINK_STATS                  1
#define IP_STATS                    1
#define ICMP_STATS                  1
#define IGMP_STATS                  1
#define IPFRAG_STATS                1
#define UDP_STATS                   1
#define TCP_STATS                   1
#define MEM_STATS                   1
#define MEMP_STATS                  1
#define PBUF_STATS                  1
#define SYS_STATS                   1
#endif /* LWIP_STATS */

/* ---------- PPP options ---------- */
#define PPP_SUPPORT                 TCPPS_PPP_ENABLE      /* Set > 0 for PPP */

#if PPP_SUPPORT

#define PPP_INPROC_OWNTHREAD		(OS_TYPE != OS_T_CHNIL)
#define PPP_THREAD_STACKSIZE		TCPPS_PPP_STACKSIZE
#define PPP_THREAD_PRIO				TCPPS_PPP_PRIORITY
#define PPP_MAXIDLEFLAG				5000

#define NUM_PPP                     1      /* Max PPP sessions. */

/* Select modules to enable.  Ideally these would be set in the makefile but
 * we're limited by the command line length so you need to modify the settings
 * in this file.
 */
#define PPPOE_SUPPORT               0
#define PPPOS_SUPPORT               1

#define PAP_SUPPORT                 1      /* Set > 0 for PAP. */
#define CHAP_SUPPORT                1      /* Set > 0 for CHAP. */
#define MSCHAP_SUPPORT              0      /* Set > 0 for MSCHAP (NOT FUNCTIONAL!) */
#define CBCP_SUPPORT                0      /* Set > 0 for CBCP (NOT FUNCTIONAL!) */
#define CCP_SUPPORT                 0      /* Set > 0 for CCP (NOT FUNCTIONAL!) */
#define VJ_SUPPORT                  1      /* Set > 0 for VJ header compression. */
#define MD5_SUPPORT                 1      /* Set > 0 for MD5 (see also CHAP) */

#define MAXNAMELEN                  32     /* max length of hostname or name for auth */
#define MAXSECRETLEN                32     /* max length of password or secret */

#endif /* PPP_SUPPORT */

/* no read/write/close for socket */
#define LWIP_POSIX_SOCKETS_IO_NAMES	0
#define LWIP_NETIF_API				0

#ifdef LWIP_IGMP
#include <stdlib.h>
#define LWIP_RAND                  rand
#endif

#endif /* __LWIPOPTS_H__ */
