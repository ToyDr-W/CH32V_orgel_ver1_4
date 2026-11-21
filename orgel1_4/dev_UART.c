#ifndef UARTBPS				//ﾎﾞｰﾚｰﾄが宣言されていないとき
#define	UARTBPS 38400				//38400bpsとする
#endif
#ifdef UART_SOFT			//UARTをｿﾌﾄ実装するとき
//==============================================
//UART出力の初期設定
//==============================================
static void uart_init(void)
{

	GPIO_H(UART_GPIO,UART_BIT);		//ｼﾘｱﾙ情報をH
	GPIO_OUT(UART_GPIO,UART_BIT);		//ｼﾘｱﾙ情報を出力
}


#ifdef UART_TX				//UART送信を実装するとき
//==============================================
//送信完了の同期
//==============================================
#define	uart_out_sync()


//==============================================
//1文字を送信(ｿﾌﾄUART)
//==============================================
static void uart_out(				//戻り値無し
	unsigned char c)			//送信する文字
{
	unsigned char n=8;

	GPIO_L(UART_GPIO,UART_BIT);		//ｽﾀｰﾄﾋﾞｯﾄ
	wait_us(1000000/UARTBPS);		//1ﾋﾞｯﾄ巾
	while(n--)				//8ﾋﾞｯﾄ分繰返す
	{
		if(c&1) GPIO_H(UART_GPIO,UART_BIT);
						//ﾃﾞｰﾀﾋﾞｯﾄ
		else GPIO_L(UART_GPIO,UART_BIT);
		wait_us(1000000/UARTBPS);	//1ﾋﾞｯﾄ巾
		c>>=1;				//次のﾃﾞｰﾀﾋﾞｯﾄへ進む
	}
	GPIO_H(UART_GPIO,UART_BIT);		//ｽﾄｯﾌﾟﾋﾞｯﾄ
	wait_us(2000000/UARTBPS-3);		//2ﾋﾞｯﾄ巾
}
#endif


#else					//内蔵UARTﾓｼﾞｭｰﾙを使うとき
//==============================================
//UARTの初期設定
//==============================================
static void uart_init(void)
{

	//交代ﾋﾟﾝ設定
#ifdef PCFR1_USART			//USARTの交代ﾋﾟﾝが宣言されていたら
	AFIO->PCFR1|=PCFR1_USART;		//交代ﾋﾟﾝを設定する
#endif

	//USART設定
//	USART1->CTLR2=0x00002000;		//ｽﾄｯﾌﾟ2
	USART1->BRR=(SYS_CLK*10000000/UARTBPS+5)/10-1;
						//ﾎﾞｰﾚｰﾄ設定
	USART1->CTLR1|=0x0000200c;		//USART有効､送信有効､受信有効
#ifdef UART_TX				//UART送信を実装するとき
	GPIO_AF(UART_GPIO,UART_BIT);		//USART出力を交代機能に設定
#endif
#ifdef UART_RX				//UART受信を実装するとき
	GPIO_AF(UART_IN_GPIO,UART_IN_BIT);	//USART入力を交代機能に設定
#endif
}


#ifdef UART_TX				//UART送信を実装するとき
//==============================================
//送信完了の同期
//==============================================
static void uart_sync(void)
{

	while(!(USART1->STATR&USART_STATR_TC));	//送信完了を待つ
}


//==============================================
//1文字を送信
//初期化をせずに送信しようとすると無限ﾙｰﾌﾟして戻らない?
//==============================================
static void uart_out(
	unsigned char c)			//送信する文字
{

	while(!(USART1->STATR&USART_STATR_TXE));//TDR空きを待つ
	USART1->DATAR=(unsigned long)c;		//ﾃﾞｰﾀを送信する
}
#endif


#ifdef UART_RX				//UART受信を実装するとき
//==============================================
//1文字を受信
//初期化をせずに受信しようとすると0x0000が返される
//==============================================
static short uart_in(void)			//受信完了時は受信ﾃﾞｰﾀを返す
						//未受信時は-1を返す
{

	if(USART1->STATR&USART_STATR_RXNE) return(USART1->DATAR);
						//受信完了していたら受信ﾃﾞｰﾀを返す
	return(-1);				//未受信を返す
}
#endif
#endif
