void Timers_Init(void)
{
//	Timer0
		TCCR0A = 0xC3;
		TCCR0B = 0x01;
		OCR0A = 0x00;
		TIMSK0 = 0x00;
//	Timer1
		TCCR1A = 0x00;		//0x81;
		TCCR1B = 0x09;
		TCCR1C = 0x00;
		OCR1A = 0x0000;
		TIMSK1 = 0x00;
//	Timer2
		TCCR2A=0x00;		//Disable code comparators
		TCCR2B=0x06;		//Choose clock frequency
		TIMSK2=0x01;		//Set interrupt mask
		ASSR=0x00;		//Clear asinchronous mode control register
}

void IO_Ports_Init(void)
{
		PORTB=0x00;		//Set out pins to 0
		DDRB=0x3F;		//PortB(6,7) are inputs

		PORTC=0x00;		//Set out pins to 0
		DDRC=0xF8;		//PortC(0..2) are analog inputs

		PORTD=0x00;		//Set out pins to 0
		DDRD=0xFE;		//All pins are outputs
                
   	PORTD|=0x10;                   
}

void ADC_Init(void)
{
		DIDR0=0x1F;		//Disable digital outputs
		ACSR=0x80;		//Disable analog comparator
		ADCSRA=0x83;		//0;		//Enable ADC on maximum clock frequency
		ADCSRB=0x00;		//Set free running mode for ADC
		ADMUX=0x42;		//Initial position, connect to Pot 
}

void MMA7361_Init(void)
{
	PORTC|=MMA7361_EN;		//Enable MMA7361
}

unsigned int Get_ADC	(unsigned char Channel, unsigned char Sample)
{
unsigned int Result;
	ADMUX=Channel_Tbl[Channel];
	  for (Temp1=0; Temp1<50; Temp1++);			//Delay
	  SumReg = 0;								//Preparing to start ADC
	  SampCnt = Sample;							//Set a number of samples
	  ADC_Done=0;								//Clear flag
	  ADCSRA = 0xCb;	//8;       						//Start ADC
	
    while (ADC_Done == 0){};
		
		Result=SumReg/Sample;
		return Result;
		
}

void SW_UART_Tx(unsigned char Data)       //BaudRate=115200, when system clock is 4M
{   
unsigned int TxBuf,i;
unsigned char j;
	TxBuf=Data;
	TxBuf=(TxBuf<<1)|0x0200;
	for(i=0x01;i!=0x400;)
	{
          if((TxBuf&i)==0)
            PORTD&=0xfd;			//PD1=0
          else
            PORTD|=0x02;			//PD1=1
          for(j=0;j<10;j++);
          i=i<<1;
	}
}

void Show_Hex(unsigned int Hex)
{
unsigned char buf,i;
  for(i=16;i>0;)
  {
    i-=4;
    buf=(Hex>>i)&0x0f;
    if(buf>9)
      buf+=7;
    SW_UART_Tx(buf+0x30);
  }
}

void Put_Axis (unsigned int Data)
{
unsigned char buf[4],i;
	buf[0]=(Data/1000);
	buf[1]=(Data%1000/100);
	buf[2]=(Data%1000%100/10);
	buf[3]=(Data%1000%100%10);
  
  for(i=0;i<4;i++)
  	SW_UART_Tx(buf[i]+0x30);
	
}

void UART_Init (void)
{
	UCSR0B=0x00;
	UCSR0A=0x02;
	UCSR0C=0x06;
	UBRR0L=0x67;
	UBRR0H=0x00;
	UCSR0B=0x18;
}

void UART_Tx (unsigned char Data)
{
	while(!(UCSR0A&(1<<5)));
	UDR0=Data;
}

unsigned char UART_Rx (void)
{
	while(!(UCSR0A&(1<<7)));
	return UDR0;
}
