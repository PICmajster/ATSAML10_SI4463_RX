/*
    File Name:        :  si4463.c
    Device            :  PIC32MM0256GPM048
    Compiler          :  XC32 2.15
    MPLAB             :  MPLAB X 5.15
    Created by        :  http://strefapic.blogspot.com
*/
#include "si4463.h"
#include "radio_config_Si4463.h"
#include "delay.h"

uint8_t inter_buff[8] ; //interrupt bufor for GET_INT_STATUS
uint8_t switch_CTS = 0; // switch software/hardware CTS
//------------------------------- SI4463_Read_Buffor ------------------------------
void SI4463_Read_Buffor( uint8_t *rd_buff, uint8_t len )
{
	uint8_t cts_val = 0;
        uint8_t i;
                 
    while( cts_val != 0xFF )
	{
		SI4463_nSEL_LOW;
      
		SPI_Exchange8bit(0x44);
             		
		cts_val = SPI_Exchange8bit( 0x00 );
                
		if( cts_val != 0xFF) SI4463_nSEL_HIGH ;
	} 
        
	for ( i = 0 ; i < len ; i++)
	{
		*( rd_buff + i ) = SPI_Exchange8bit(0x00);
        }
	SI4463_nSEL_HIGH ;
}


//------------------------------- SI4463_Wait_CTS ------------------------------
void SI4463_Wait_CTS( void )
{
	uint8_t cts_val = 0;
    
	while(cts_val != 0xFF) 
    {
		 
        SI4463_nSEL_LOW ;

		SPI_Exchange8bit( 0x44 );
	
		cts_val = SPI_Exchange8bit(0x00);

        SI4463_nSEL_HIGH ;
             
	} 
 
}

//------------------------------- SI4463_Wait_GPIO_CTS ------------------------------
void SI4463_Wait_GPIO_CTS( void )
{
	while(!CTS_GPIO0);
}

//------------------------------- SI4463_Send_Without_CTS ----------------------
void SI4463_Send_Without_CTS( uint8_t *get_buff, uint8_t len )
{
	uint8_t i;
    SI4463_nSEL_LOW ;
	for (i = 0 ; i < len ; i++)
	{
		SPI_Exchange8bit( *(get_buff+i) );
	}
	SI4463_nSEL_HIGH ;
    
}

//------------------------------- SI4463_Send_With_CTS -------------------------
void SI4463_Send_With_CTS( uint8_t *set_buff, uint8_t len )
{
	uint8_t i;
    SI4463_nSEL_LOW;
	for (i = 0 ; i < len ; i++)
	{
		SPI_Exchange8bit( *(set_buff+i) );
	}
	SI4463_nSEL_HIGH ;
   
      if(!switch_CTS) {SI4463_Wait_CTS();} //software CTS
      else SI4463_Wait_GPIO_CTS(); // hardware CTS
}

//------------------------------- SI4463_Get_Interrupt ------------------------------
void SI4463_Get_Interrupt( uint8_t *inter_buff )
{
	uint8_t send_stream[] = { SI4463_CMD_GET_INT_STATUS };
	SI4463_Send_With_CTS( send_stream, 1 );
	SI4463_Read_Buffor( inter_buff, 8 );
}

//------------------------------- SI4463_Get_Chip_Status ----------------------------
void SI4463_Get_Chip_Status( uint8_t *inter_buff )
{
	uint8_t send_stream[] = { SI4463_CMD_GET_CHIP_STATUS, 0x00 };
	SI4463_Send_With_CTS( send_stream, 2 );
	SI4463_Read_Buffor( inter_buff, 4 );
}

//------------------------------- SI4463_Get_PH_Status ----------------------------
void SI4463_Get_PH_Status( uint8_t *inter_buff )
{
	uint8_t send_stream[] = { SI4463_CMD_GET_PH_STATUS };
	SI4463_Send_With_CTS( send_stream, 1 );
	SI4463_Read_Buffor( inter_buff, 2 );
}

//------------------------------- SI4463_Get_Packet_Info ----------------------------
uint8_t SI4463_Get_Packet_Info( void )
{
	uint8_t send_stream[] = { SI4463_CMD_PACKET_INFO, 0x01, 0x00, 0x00, 0x00, 0x00 };
        uint8_t reply_stream[2];
	SI4463_Send_With_CTS( send_stream, 6 );
	SI4463_Read_Buffor( reply_stream, 2 );
    return reply_stream[1];
}



//------------------------------- SI4463_TX_Start ------------------------------
void SI4463_TX_Start( uint8_t channel_tx, uint8_t size )
{
	uint8_t send_stream[] = { SI4463_CMD_START_TX, channel_tx, 0x00, 0x00, size };
	SI4463_Send_With_CTS( send_stream, 5 );
}

//------------------------------- SI4463_RX_Start ------------------------------
void SI4463_RX_Start( uint8_t channel_rx, uint8_t size )
{
	uint8_t send_stream[] = { SI4463_CMD_START_RX, channel_rx , 0x00, 0x00, size, 0x00, 0x00, 0x00 };
	SI4463_Get_Interrupt(inter_buff); //get interrupt status and clear
        SI4463_Send_With_CTS( send_stream, 8 ); 
}

//------------------------------- SI4463_TX_FIFO ------------------------------
void SI4463_TX_FIFO ( uint8_t *buff_tx, uint8_t len )
{
	uint8_t buff[len+1], i;
    buff[0] = SI4463_CMD_WRITE_TX_FIFO;

	for(i = 0 ; i < len ; i++)
	{
		buff[i+1] = *(buff_tx + i);
	}

	SI4463_nSEL_LOW ;
	for (i = 0 ; i < sizeof(buff)/sizeof(uint8_t) ; i++)
	{
		SPI_Exchange8bit( buff[i] );
	}
	SI4463_nSEL_HIGH ;
}

//------------------------------- SI4463_RX_FIFO -------------------------------
void SI4463_RX_FIFO ( uint8_t *buff_rx, uint8_t len )
{
	SI4463_nSEL_LOW ;
        uint8_t i;
	SPI_Exchange8bit( SI4463_CMD_READ_RX_FIFO );

	for (i = 0 ; i < len ; i++)
	{
        *(buff_rx+i) = SPI_Exchange8bit(0x00);
	}
	SI4463_nSEL_HIGH ;
}

//------------------------------- SI4463_Clear_TX_FIFO -------------------------
void SI4463_Clear_TX_FIFO( void )
{
	uint8_t send_stream[] = { SI4463_CMD_FIFO_INFO, 0x01 };
	SI4463_Send_With_CTS( send_stream, 2 );
}

//------------------------------- SI4463_Clear_RX_FIFO -------------------------
void SI4463_Clear_RX_FIFO( void )
{
	uint8_t send_stream[] = { SI4463_CMD_FIFO_INFO, 0x02 };
	SI4463_Send_With_CTS( send_stream, 2 );
}

//------------------------------- SI4463_Part_Info -----------------------------
void SI4463_Part_Info( uint8_t *inter_buff )
{
	uint8_t send_stream = SI4463_CMD_PART_INFO;
        SI4463_Send_With_CTS( &send_stream, 1 );
	SI4463_Read_Buffor( inter_buff, 8 );
}

//------------------------------- SI4463_Send_Data ------------------------------
void SI4463_Send_Data( uint8_t *send_dt, uint8_t size, uint8_t channel )
{
	// Red diode SENDING -> ON
         //REG_PORT_OUTSET0 = PORT_PA16;
    SI4463_nSEL_LOW ;									
	
	        SI4463_Clear_TX_FIFO( );
	    	SI4463_TX_FIFO ( send_dt, size );
		SI4463_TX_Start( channel, size );
	 
    SI4463_nSEL_HIGH ;
    // Red diode SENDING -> OFF
    //REG_PORT_OUTCLR0 = PORT_PA16;
}
//------------------------------- SI4463_Read_Data -----------------------------

void SI4463_Read_Data( uint8_t *read_dt, uint8_t size, uint8_t channel )
{
	// Green diode RECIEVING -> ON
	//REG_PORT_OUTSET0 = PORT_PA09;
	SI4463_Get_Interrupt( inter_buff );
	if( ( inter_buff[2] & 0x10) )
		{
			SI4463_RX_FIFO ( read_dt, size );
		}

	SI4463_Clear_RX_FIFO();

	// Green diode RECIEVING -> OFF
        //REG_PORT_OUTCLR0 = PORT_PA09;
}

//------------------------------- SI4463_Init ----------------------------------
void SI4463_Init( )
{
	uint8_t Radio_Conf_Array[] = RADIO_CONFIGURATION_DATA_ARRAY;
	uint16_t place = 0;
    /*SDN Pulse must be*/
    SI4463_SDN_LOW ;
    _delay_us(20);
    SI4463_SDN_HIGH ;
    _delay_us(12);
    SI4463_SDN_LOW ;
    /*Wait for delay of POR, max 6 ms typisal 1 ms*/
    _delay_ms(6);
   
	while( *(Radio_Conf_Array + place) != 0x00 )
	{
		SI4463_Send_With_CTS( (Radio_Conf_Array + place + 1), *(Radio_Conf_Array + place) );

		place += *(Radio_Conf_Array + place) + 1;
	}
switch_CTS = 1; // hardware CTS ON
}

//------------------------------- SI4463_getRSSI -------------------------------
int16_t SI4463_getRSSI()
{
    uint8_t send_stream[] = { SI4463_CMD_GET_MODEM_STATUS, 0x00};
    uint8_t reply_stream[8] ;
    SI4463_Send_With_CTS(send_stream, 2);
    SI4463_Read_Buffor(reply_stream, 8);
    int16_t rssi = reply_stream[2];
	return rssi;
}

//------------------------------- SI4463_Power_TX -------------------------
void SI4463_Set_Power_TX( uint8_t power )
{
	//value power see datasheet page 36, Figure 11
        uint8_t send_stream[] = { SI4463_CMD_SET_PROPERTY, 0x22, 0x01, 0x00, power };
	SI4463_Send_With_CTS( send_stream, 5 );
}
 
//------------------------------- SI4463_Patch ------------------------------
//void SI4463_Patch( void )
//{
//	uint8_t Radio_Patch_Array[][8] = { SI446X_PATCH_CMDS };
//	uint8_t buff_patch[8];
//	uint16_t size = sizeof( Radio_Patch_Array ) / 8*sizeof( uint8_t );
//
//	for (uint16_t row = 0 ; row < size; row++)
//	{
//		for( uint8_t col = 0 ; col < 8 ; col++)
//		{
//			buff_patch[col] = Radio_Patch_Array[row][col];
//		}
//		SI4463_Send_With_CTS( buff_patch, 8 );
//	}
//}
