#ifndef __SYS_SPI_H__
#define __SYS_SPI_H__


#ifdef __cplusplus
extern "C" {
#endif





#define SPI_S_IDLE				0
#define SPI_S_BUSY				1

#define SPI_MODE_0				0	/* CPOL = 0, CPHA = 0 */
#define SPI_MODE_1				1	/* CPOL = 0, CPHA = 1 */
#define SPI_MODE_2				2	/* CPOL = 1, CPHA = 0 */
#define SPI_MODE_3				3	/* CPOL = 1, CPHA = 1 */

#define SPI_ORDER_MSB			0
#define SPI_ORDER_LSB			0

#define SPI_SPEED_FAST			0
#define SPI_SPEED_HIGH			1
#define SPI_SPEED_NORMAL		2
#define SPI_SPEED_LOW			3

#define SPI_CSID_INVALID		0xFF


typedef const struct
{
	u8	id : 6,
		outmode : 1,
		nssvalid : 1;
	u8	sckport : 4,
		sckpin : 4;
	u8	mosiport : 4,
		mosipin : 4;
	u8	misoport : 4,
		misopin : 4;
	u8	nssport : 4,
		nsspin : 4;
} t_spi_def;


typedef struct
{
	struct dev	parent;
	u8	ste;
#if SPI_SEL_ENABLE
		u8	csid;
#endif
#if SPI_SOFTWARE
	u8	sckmode;
	u8	latchmode;
	u32	speed;
#else
	t_spi_def *	def;
#endif
} spi_t;



//External Variables
extern spi_t dev_Spi[];


//External Functions
spi_t *spi_Open(int nId, size_t nTmo);
sys_res spi_Close(spi_t *p);
sys_res spi_Config(spi_t *p, int nSckMode, int nLatch, int nSpeed);
void spi_CsSel(spi_t *p, int nId);
sys_res spi_Start(spi_t *p);
sys_res spi_SendChar(spi_t *p, u8 nData);
sys_res spi_End(spi_t *p);
sys_res spi_Send(spi_t *p, const void *pData, size_t nLen);
sys_res spi_Recv(spi_t *p, void *pRec, size_t nLen);
sys_res spi_Transce(spi_t *p, const void *pCmd, size_t nCmdLen, void *pRec, size_t nRecLen);
sys_res spi_TransChar(spi_t *p, u8 nSend, void *pRec);


#ifdef __cplusplus
}
#endif

#endif

