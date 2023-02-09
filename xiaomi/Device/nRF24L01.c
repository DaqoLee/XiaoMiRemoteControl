#include "nRF24L01.h"
#include "spi.h"
#include "stdio.h"





//#include "nrf24L01.h"
//#include "spi.h"
// 
const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //接收地址
 
 
//针对NRF24L01修改SPI1驱动
void NRF24L01_SPI_Init(void)
{
    __HAL_SPI_DISABLE(&hspi1);               //先关闭SPI1
    hspi1.Init.CLKPolarity=SPI_POLARITY_LOW; //串行同步时钟的空闲状态为低电平
    hspi1.Init.CLKPhase=SPI_PHASE_1EDGE;     //串行同步时钟的第1个跳变沿（上升或下降）数据被采样
    HAL_SPI_Init(&hspi1);
    __HAL_SPI_ENABLE(&hspi1);                //使能SPI1
}
 
//初始化24L01的IO口
void NRF24L01_Init(void)
{		              			//初始化SPI1
		NRF24L01_SPI_Init();                			//针对NRF的特点修改SPI的设置
		NRF24L01_CE_LOW(); 			            			//使能24L01
		NRF24L01_SPI_CS_DISABLE();			    			//SPI片选取消	 		 	 
}
 
/**
	*SPI速度设置函数
  *SPI速度=fAPB1/分频系数
  *@ref SPI_BaudRate_Prescaler:SPI_BAUDRATEPRESCALER_2~SPI_BAUDRATEPRESCALER_2 256
	*fAPB1时钟一般为42Mhz：
	*/
static void SPI1_SetSpeed(uint8_t SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
    __HAL_SPI_DISABLE(&hspi1);            //关闭SPI
    hspi1.Instance->CR1&=0XFFC7;          //位3-5清零，用来设置波特率
    hspi1.Instance->CR1|=SPI_BaudRatePrescaler;//设置SPI速度
    __HAL_SPI_ENABLE(&hspi1);             //使能SPI
}
 
/**
  * 函数功能: 往串行Flash读取写入一个字节数据并接收一个字节数据
  * 输入参数: byte：待发送数据
  * 返 回 值: uint8_t：接收到的数据
  * 说    明：无
  */
uint8_t SPIx_ReadWriteByte(SPI_HandleTypeDef* hspi,uint8_t byte)
{
  uint8_t d_read,d_send=byte;
  if(HAL_SPI_TransmitReceive(hspi,&d_send,&d_read,1,0xFF)!=HAL_OK)
  {
    d_read=0xFF;
  }
  return d_read; 
}
 
/**
  * 函数功能: 检测24L01是否存在
  * 输入参数: 无
  * 返 回 值: 0，成功;1，失败
  * 说    明：无          
  */ 
uint8_t NRF24L01_Check(void)
{
	uint8_t buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uint8_t i;
  
	SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_4); //spi速度为8.0Mhz（（24L01的最大SPI时钟为10Mhz,这里大一点没关系）  
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //读出写入的地址  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//检测24L01错误	
	return 0;		 	//检测到24L01
}	
 
/**
  * 函数功能: SPI写寄存器
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：reg:指定寄存器地址
  *           
  */ 
uint8_t NRF24L01_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;	
  NRF24L01_SPI_CS_ENABLE();                 //使能SPI传输
  status =SPIx_ReadWriteByte(&hspi1,reg);   //发送寄存器号 
  SPIx_ReadWriteByte(&hspi1,value);         //写入寄存器的值
  NRF24L01_SPI_CS_DISABLE();                //禁止SPI传输	   
  return(status);       			//返回状态值
}
 
/**
  * 函数功能: 读取SPI寄存器值
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：reg:要读的寄存器
  *           
  */ 
uint8_t NRF24L01_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;	    
 	NRF24L01_SPI_CS_ENABLE();          //使能SPI传输		
  SPIx_ReadWriteByte(&hspi1,reg);   //发送寄存器号
  reg_val=SPIx_ReadWriteByte(&hspi1,0XFF);//读取寄存器内容
  NRF24L01_SPI_CS_DISABLE();          //禁止SPI传输		    
  return(reg_val);           //返回状态值
}		
 
/**
  * 函数功能: 在指定位置读出指定长度的数据
  * 输入参数: 无
  * 返 回 值: 此次读到的状态寄存器值 
  * 说    明：无
  *           
  */ 
uint8_t NRF24L01_Read_Buf(uint8_t reg,uint8_t *pBuf,uint8_t len)
{
	uint8_t status,uint8_t_ctr;	   
  
  NRF24L01_SPI_CS_ENABLE();           //使能SPI传输
  status=SPIx_ReadWriteByte(&hspi1,reg);//发送寄存器值(位置),并读取状态值   	   
 	for(uint8_t_ctr=0;uint8_t_ctr<len;uint8_t_ctr++)
  {
    pBuf[uint8_t_ctr]=SPIx_ReadWriteByte(&hspi1,0XFF);//读出数据
  }
  NRF24L01_SPI_CS_DISABLE();       //关闭SPI传输
  return status;        //返回读到的状态值
}
 
/**
  * 函数功能: 在指定位置写指定长度的数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：reg:寄存器(位置)  *pBuf:数据指针  len:数据长度
  *           
  */ 
uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t status,uint8_t_ctr;	    
 	NRF24L01_SPI_CS_ENABLE();          //使能SPI传输
  status = SPIx_ReadWriteByte(&hspi1,reg);//发送寄存器值(位置),并读取状态值
  for(uint8_t_ctr=0; uint8_t_ctr<len; uint8_t_ctr++)
  {
    SPIx_ReadWriteByte(&hspi1,*pBuf++); //写入数据	 
  }
  NRF24L01_SPI_CS_DISABLE();       //关闭SPI传输
  return status;          //返回读到的状态值
}		
 
/**
  * 函数功能: 启动NRF24L01发送一次数据
  * 输入参数: 无
  * 返 回 值: 发送完成状况
  * 说    明：txbuf:待发送数据首地址
  *           
  */ 
uint8_t NRF24L01_TxPacket(uint8_t *txbuf)
{
	uint8_t sta;
	SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //spi速度为4.0Mhz（24L01的最大SPI时钟为10Mhz） 
	NRF24L01_CE_LOW();
  NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
 	NRF24L01_CE_HIGH();//启动发送	 
  
	while(NRF24L01_IRQ_PIN_READ()!=0);//等待发送完成
  
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&MAX_TX)//达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(sta&TX_OK)//发送完成
	{
		return TX_OK;
	}
	return 0xff;//其他原因发送失败
}
 
/**
  * 函数功能:启动NRF24L01接收一次数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  *           
  */ 
uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
{
	uint8_t sta;		
  SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //spi速度为4.0Mhz（24L01的最大SPI时钟为10Mhz） 
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值    	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&RX_OK)//接收到数据
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//清除RX FIFO寄存器 
		return 0; 
	}	   
	return 1;//没收到任何数据
}			
 
/**
  * 函数功能: 该函数初始化NRF24L01到RX模式
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  *           
  */ 
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE_LOW();	  
  NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0F);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC 
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    //使能通道0的自动应答    
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);//使能通道0的接收地址  	 
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	     //设置RF通信频率		  
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  
  NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 	    
    
  NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
	
  NRF24L01_CE_HIGH(); //CE为高,进入接收模式 
  HAL_Delay(1);
}	
 
/**
  * 函数功能: 该函数初始化NRF24L01到TX模式
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  *           
  */ 
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE_LOW();	    
  NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址 
  NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  
 
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
  NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x15);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:5次
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //设置RF通道为40
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
 
  NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	NRF24L01_CE_HIGH();//CE为高,10us后启动发送
  HAL_Delay(1);
}
 
/**
  * 函数功能: 该函数NRF24L01进入低功耗模式
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  *           
  */
void NRF_LowPower_Mode(void)
{
	NRF24L01_CE_LOW();	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x00);		//配置工作模式:掉电模式
}


//NRF24L01 驱动函数
#if 0
unsigned char idel_mode_flag = 0;
unsigned char mode_time_counter = 0;

const unsigned char INIT_ADDR0[5]= {0x02,0x3A,0xB1,0xB1,0x01};
const unsigned char INIT_ADDR1[5]= {0x02,0x3A,0x01,0x01,0x01};
const unsigned char INIT_ADDR2[5]= {0x03,0x3A,0x01,0x01,0x01};
const unsigned char INIT_ADDR3[5]= {0x04,0x3A,0x01,0x01,0x01};
const unsigned char INIT_ADDR4[5]= {0x05,0x3A,0x01,0x01,0x01};
const unsigned char INIT_ADDR5[5]= {0x06,0x3A,0x01,0x01,0x01};

#define CH_Num	120
#define debug_out(fmt,args...)  printf(fmt,##args)
//#define debug_out(fmt,args...) 

void delay_us(uint32_t n)
{
	unsigned char i;

	while(n--)
	{
		i = 8;
		while(i--);
	}
}
//初始化24L01的IO口
void NRF24L01_Init(void)
{
	//spi init
	//gpio init
	Clr_NRF24L01_CE;    // chip enable
	Set_NRF24L01_CSN;   // Spi disable
	delay_us(100);
}

//封装spi读写函数
unsigned char nRF24_SPI_Send_Byte(unsigned char txdata)
{
	unsigned char rxdata;
	HAL_SPI_TransmitReceive(&hspi1, &txdata, &rxdata, 1, 0x10);
	return(rxdata);							// return read unsigned char
}


//通过SPI写寄存器
unsigned char NRF24L01_Write_Reg(unsigned char regaddr,unsigned char data)
{
	unsigned char status;
	Clr_NRF24L01_CSN;                    //使能SPI传输
	status =nRF24_SPI_Send_Byte(regaddr); //发送寄存器号
	nRF24_SPI_Send_Byte(data);            //写入寄存器的值
	Set_NRF24L01_CSN;                    //禁止SPI传输
	return(status);       		         //返回状态值
}
//读取SPI寄存器值 ，regaddr:要读的寄存器
unsigned char NRF24L01_Read_Reg(unsigned char regaddr)
{
	unsigned char reg_val;
	Clr_NRF24L01_CSN;                //使能SPI传输
	nRF24_SPI_Send_Byte(regaddr);     //发送寄存器号
	reg_val=nRF24_SPI_Send_Byte(0XFF);//读取寄存器内容
	Set_NRF24L01_CSN;                //禁止SPI传输
	return(reg_val);                 //返回状态值
}
//在指定位置读出指定长度的数据
//*pBuf:数据指针
//返回值,此次读到的状态寄存器值
unsigned char NRF24L01_Read_Buf(unsigned char regaddr,unsigned char *pBuf,unsigned char datalen)
{
	unsigned char status,u8_ctr;
	Clr_NRF24L01_CSN;                     //使能SPI传输
	status=nRF24_SPI_Send_Byte(regaddr);   //发送寄存器值(位置),并读取状态值
	//for(u8_ctr=0;u8_ctr<datalen;u8_ctr++)pBuf[u8_ctr]=SPI_ReadWriteByte(0XFF);//读出数据
	HAL_SPI_Receive(&hspi1, pBuf, datalen, 0x10);
	Set_NRF24L01_CSN;                     //关闭SPI传输
	return status;                        //返回读到的状态值
}
//在指定位置写指定长度的数据
//*pBuf:数据指针
//返回值,此次读到的状态寄存器值
unsigned char NRF24L01_Write_Buf(unsigned char regaddr, unsigned char *pBuf, unsigned char datalen)
{
	unsigned char status,u8_ctr;
	Clr_NRF24L01_CSN;                                    //使能SPI传输
	status = nRF24_SPI_Send_Byte(regaddr);                //发送寄存器值(位置),并读取状态值
	//for(u8_ctr=0; u8_ctr<datalen; u8_ctr++)SPI_ReadWriteByte(*pBuf++); //写入数据
	HAL_SPI_Transmit(&hspi1, pBuf, datalen, 0x10);
	Set_NRF24L01_CSN;                                    //关闭SPI传输
	return status;                                       //返回读到的状态值
}
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:发送完成状况
unsigned char NRF24L01_TxPacket(unsigned char *txbuf)
{
	unsigned char state;
	Clr_NRF24L01_CE;
	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
	Set_NRF24L01_CE;                                     //启动发送
	while(READ_NRF24L01_IRQ!=0);                         //等待发送完成
	state=NRF24L01_Read_Reg(STATUS);                     //读取状态寄存器的值
	NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,state);      //清除TX_DS或MAX_RT中断标志
	if(state&MAX_TX)                                     //达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);               //清除TX FIFO寄存器
		debug_out("TX MAX_TX error!\r\n");
		return MAX_TX;
	}
	if(state&TX_OK)                                      //发送完成
	{
		debug_out("TX OK!\r\n");
		return TX_OK;
	}
	debug_out("TX other error!\r\n");
	return 0xff;                                         //其他原因发送失败
}

//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
unsigned char NRF24L01_RxPacket(unsigned char *rxbuf)
{
	unsigned char state;
	state=NRF24L01_Read_Reg(STATUS);                //读取状态寄存器的值
	NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,state); //清除TX_DS或MAX_RT中断标志
	if(state&TX_OK)
	{
		debug_out("RX send ack!\r\n"); //成功发送ACK
	}
	if(state&RX_OK)                                 //接收到数据
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);          //清除RX FIFO寄存器
	//	debug_out("RX read data!\r\n");
		return 0;
	}
	return 1;                                      //没收到任何数据
}

//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了
void RX_Mode(void)
{
	Clr_NRF24L01_CE;
	//写RX节点地址
	NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(unsigned char*)INIT_ADDR0,RX_ADR_WIDTH);

	//使能通道0的自动应答
	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);
	//使能通道0的接收地址
	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01);
	//设置RF通信频率
	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,CH_Num);
	//选择通道0的有效数据宽度
	NRF24L01_Write_Reg(SPI_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);
	//设置TX发射参数,0db增益,2Mbps,低噪声增益开启
	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f);
	//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,PRIM_RX接收模式
	NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG, 0x0f);
	//CE为高,进入接收模式
	Set_NRF24L01_CE;
}

//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,
//选择RF频道,波特率和LNA HCURR PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了
//CE为高大于10us,则启动发送.
void TX_Mode(void)
{
	Clr_NRF24L01_CE;
	//写TX节点地址
	NRF24L01_Write_Buf(SPI_WRITE_REG+CONFIG,(unsigned char*)INIT_ADDR0,TX_ADR_WIDTH);
	//设置TX节点地址,主要为了使能ACK
	NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(unsigned char*)INIT_ADDR0,RX_ADR_WIDTH);

	//使能通道0的自动应答
	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);
	//使能通道0的接收地址
	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01);
	//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
	NRF24L01_Write_Reg(SPI_WRITE_REG+SETUP_RETR,0x1a);
	//设置RF通道为40
	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,CH_Num);
	//设置TX发射参数,0db增益,2Mbps,低噪声增益开启
	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f);
	//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,PRIM_RX发送模式,开启所有中断
	NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG,0x0e);
	// CE为高,10us后启动发送
	Set_NRF24L01_CE;
}

//上电检测NRF24L01是否在位
//写5个数据然后再读回来进行比较，
//相同时返回值:0，表示在位;否则返回1，表示不在位

unsigned char NRF24L01_Check(void)
{
	unsigned char buf[5]= {0XA5,0XA5,0XA5,0XA5,0XA5};
	unsigned char buf1[5];
	unsigned char i;
	NRF24L01_Write_Buf(SPI_WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.
	NRF24L01_Read_Buf(TX_ADDR,buf1,5);              //读出写入的地址
	for(i=0; i<5; i++)if(buf1[i]!=0XA5)break;
	if(i!=5)
	{
		debug_out(("nRF24L01 TEST FAIL\r\n"));
		return 1;                               //NRF24L01不在位
	}
	debug_out(("nRF24L01 TEST OK\r\n"));
	return 0;		                           //NRF24L01在位
}

#endif
