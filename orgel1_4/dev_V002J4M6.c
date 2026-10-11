//==============================================
//ﾎﾟｰﾄｱｸｾｽのﾏｸﾛ定義
//==============================================
#define	GPIO_OUT(gpio,bit)	gpio->CFGLR=gpio->CFGLR&~(15<<bit*4)|1<<bit*4
#define	GPIO_OUTOD(gpio,bit)	gpio->CFGLR=gpio->CFGLR&~(15<<bit*4)|5<<bit*4
#define	GPIO_H(gpio,bit)	gpio->BSHR=1<<bit
#define	GPIO_L(gpio,bit)	gpio->BCR=1<<bit
#define	GPIO_IN(gpio,bit)	gpio->CFGLR=gpio->CFGLR&~(15<<bit*4)|4<<bit*4
#define	GPIO_INPU(gpio,bit)	gpio->CFGLR=gpio->CFGLR&~(15<<bit*4)|8<<bit*4,\
				gpio->BSHR=1<<bit
#define	GPIO_INPD(gpio,bit)	gpio->CFGLR=gpio->CFGLR&~(15<<bit*4)|8<<bit*4,\
				gpio->BCR=1<<bit
#define	GPIO_R(gpio,bit)	(gpio->INDR&1<<bit)
#define	GPIO_AF(gpio,bit)	gpio->CFGLR=gpio->CFGLR&~(15<<bit*4)|9<<bit*4
#define	GPIO_AFOD(gpio,bit)	gpio->CFGLR|=13<<bit*4


//==============================================
//ｼｽﾃﾑｸﾛｯｸ設定
//==============================================
void SystemInit(void)
{

#ifndef HSI_TRIM			//HSI校正値が指定されていないとき
#define HSI_TRIM 16				//HSI校正値を中央値にする
#endif
	FLASH->ACTLR=(uint32_t)FLASH_ACTLR_LATENCY_2;
						//FLASHﾚｲﾃﾝｼは2WAIT
	RCC->CTLR=RCC_HSION|HSI_TRIM<<3;	//HSIｵﾝ､HSI校正
	RCC->CFGR0=RCC_PLLSRC_HSI_Mul2;		//PLLｿｰｽはHSI､2xPLL､HBﾌﾟﾘｽｹ無し
	RCC->CTLR|=RCC_PLLON;			//PLLｵﾝ	
	while(!(RCC->CTLR&RCC_PLLRDY)){};	//PLLﾚﾃﾞｨを待つ
	RCC->CFGR0|=RCC_SW_PLL;			//ｼｽﾃﾑｸﾛｯｸをPLLに切替える
	while((RCC->CFGR0&RCC_SWS)!=(uint32_t)0x08){};
						//切替わるのを待つ
}


//==============================================
//共通ｺｰﾄﾞの呼込み
//==============================================
#include "common.c"				//共通ｺｰﾄﾞを呼込む

#if VOICE_I>0				//音声Iを使うとき
#include "dev_I2C.c"				//I2Cを呼込む
#endif

#if VOICE_C+VOICE_S>0			//音声Cか音声Sを使うとき
#include "dev_SPI.c"				//SPIを呼込む
#endif

#define	MounRiverStudio
#include "orgel.c"				//orgelｴﾝｼﾞﾝを呼込む

#include "dev_PWM_8.c"				//PWM(8ﾋﾟﾝ)を呼込む


//==============================================
//固有の初期設定
//==============================================
static void CB_INIT(void)
{

	//ｸﾛｯｸ設定
	//system_ch32v00x.cで #define SYSCLK_FREQ_48MHZ_HSI 48000000 を選択すること
	RCC->RSTSCKR=0x00000001;		//128KHzOSC有効
	while(!(RCC->RSTSCKR&0x02));		//128KHzOSCﾚﾃﾞｨを待つ

	//GPIO設定
	RCC->PB2PCENR=RCC_PB2Periph_GPIOA|
			RCC_PB2Periph_GPIOC|
			RCC_PB2Periph_GPIOD|
			RCC_PB2Periph_TIM1|
			RCC_PB2Periph_ADC1|
			RCC_PB2Periph_AFIO|
			RCC_PB2Periph_USART1;
	RCC->PB1PCENR=RCC_PB1Periph_PWR|
			RCC_PB1Periph_I2C1;

	//PD1(SWIO)ﾁｪｯｸ
	AFIO->PCFR1=0x04000000;			//PD1をGPIOにする
	GPIO_INPD(GPIOD,1);			//PD1をﾌﾟﾙﾀﾞｳﾝ入力ﾓｰﾄﾞ
	wait_ms(1);				//電圧安定時間
	if(GPIO_R(GPIOD,1))			//PD1がHだったら
	{
		AFIO->PCFR1=0x00000000;		//PD1をSWIOに戻す
		wait_ms(2000);			//2秒待つ(この間にﾃﾞﾊﾞｶﾞを繋ぐ)
	}

	//GPIO設定の続き
	GPIOA->CFGLR=GPIOC->CFGLR=GPIOD->CFGLR=0x00000000;
						//全ﾎﾟｰﾄをｱﾅﾛｸﾞ入力にしておく
	AFIO->PCFR1=AFIO_PCFR1;			//交代ﾋﾟﾝを設定する

	//ﾃﾞﾊﾞｸﾞ信号設定
#ifdef SHDBS				//ﾃﾞﾊﾞｸﾞ信号を出力するとき
	dbs_init();				//ﾃﾞﾊﾞｸﾞ情報を初期化する
//待ち時間のﾃｽﾄ
//for(;;){wait_us(10);DBS_H;wait_us(10);DBS_L;}
#endif

	//ﾃﾞﾊﾞｸﾞ情報設定
#if defined(SHDBG)||defined(SHDBG_IN)	//ﾃﾞﾊﾞｸﾞ情報出力か入力するとき
	dbg_init();				//ﾃﾞﾊﾞｸﾞ情報を初期化する
#ifdef SHDBG				//ﾃﾞﾊﾞｸﾞ情報を出力するとき
//ﾃﾞﾊﾞｸﾞ情報出力のﾃｽﾄ
//for(;;){DBG_C('U');}
#endif
#endif

//DBG_C('\n');
//DBG_C('i');

	//I2Cﾎﾟｰﾄ設定
#if VOICE_I>0
	i2c_init();				//I2C初期設定
#endif

	//SPIﾎﾟｰﾄ設定
#if VOICE_C+VOICE_S>0
	spi_init();				//SPI初期設定
#endif

	//PWM設定
	pwm_init();				//PWM初期設定

	//song_idxのﾘﾝｸ
#if PART_N>0				//ｵﾙｺﾞｰﾙ演奏を実装するとき
	//song_idxをﾘﾝｸするためのおまじない
	void song_idx_dmy(void);		//song_idxのｴﾝﾄﾘ
	song_idx_dmy();				//ﾀﾞﾐｰｺｰﾙする
#endif

	//ADCの実装要否
#if defined(CdS_EN)||defined(CVD_EN)	//CdSかCVDを実装するとき
#define	ADC_EN					//ADCを実装が必要
#endif
#if defined(KYOKU_RAND)||defined(ONSEIN_RAND)||defined(ONSEII_RAND)||defined(ONSEIC_RAND)||defined(ONSEIS_RAND)
					//どれかでﾗﾝﾀﾞﾑが必要なとき
#define	ADC_EN					//ADCを実装が必要
#endif

#ifdef ADC_EN				//ADCの実装が必要なとき
	//ADC設定
	ADC1->CTLR2=ADC_ADON|ADC_SWSTART;	//ADC有効､ｿﾌﾄﾄﾘｶﾞでruleﾁｬﾈﾙ変換
	while(!(ADC1->CTLR2&ADC_ADON));		//ADC有効を待つ
	ADC1->SAMPTR2=0x00000000;		//CH0のｻﾝﾌﾟﾙﾀｲﾑは3ｻｲｸﾙ
//DBG_C('a');
#endif

	//ｱﾌﾟﾘの初期設定(LED設定はｱﾌﾟﾘの初期化で実施)
	apl_init();

//DBG_C('j');
}
