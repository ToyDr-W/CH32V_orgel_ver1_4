//#define	SHDBS		//ﾃﾞﾊﾞｸﾞ信号を出力するときに宣言する
				//下記行は､ﾃﾞﾊﾞｸﾞ入力で制御するため有効にしておくこと
#define		SHDBG		//ﾃﾞﾊﾞｸﾞ情報を出力するときに宣言する
//#define	SHBPS	115200	//ﾃﾞﾊﾞｸﾞ情報のﾎﾞｰﾚｰﾄを宣言する(ﾃﾞﾌｫﾙﾄ値は38400bps)
//#define	SHDBG_SOFT	//ﾃﾞﾊﾞｸﾞ情報のUARTをｿﾌﾄ実装するときに宣言する		
				//下記行は､ﾃﾞﾊﾞｸﾞ入力で制御するため有効にしておくこと
#define		SHDBG_IN	//ﾃﾞﾊﾞｸﾞ情報を入力するときに宣言する(UARTのｿﾌﾄ実装は不可)

//#define	I2C_SOFT	//I2Cをｿﾌﾄ実装するときに宣言する
//#define	SPI_SOFT	//SPIをｿﾌﾄ実装するときに宣言する
//#define	SPI2		//2線SPIのときに宣言する
//#define	SPI3		//3線SPIのときに宣言する
//#define	SLEEP_EN	//Sleep機能を実装するときに宣言する
//#define	KYOKU_AUTO	//ｵﾙｺﾞｰﾙ演奏を自動開始するときに宣言する
//#define	ONSEIN_AUTO	//音声0再生を自動開始するときに宣言する
//#define	ONSEII_AUTO	//音声I再生を自動開始するときに宣言する
//#define	ONSEIC_AUTO	//音声C再生を自動開始するときに宣言する
//#define	ONSEIS_AUTO	//音声S再生を自動開始するときに宣言する
//#define	RAND_An	7	//ﾗﾝﾀﾞﾏｲｽﾞの種にするAn番号(PD4:A7)
//#define	KYOKU_RAND	//曲番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIN_RAND	//音声N番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEII_RAND	//音声I番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIC_RAND	//音声C番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIS_RAND	//音声S番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	SW_EN		//SWを実装するときに宣言する
//#define	SW_PLNG		//SWをｲﾍﾞﾝﾄではなく､ﾎﾟｰﾘﾝｸﾞするときに宣言する
//#define	CdS_EN		//CdSを実装するときに宣言する
//#define	CVD_EN		//CVDを実装するときに宣言する

//ｵﾙｺﾞｰﾙ箱への応用では以下を宣言しておくこと
//#define	CdS_FUTA	//蓋を開ける(明)とｵﾝ判定する
//#define	CdS_THR	100	//判定閾値を固定の宣言値にする

#define		VOICEN_IMA	//音声NがIMA_ADPCMｴﾝｺｰﾄﾞのときに宣言する
#define		VOICEI_IMA	//音声IがIMA_ADPCMｴﾝｺｰﾄﾞのときに宣言する
#define		VOICES_IMA	//音声SがIMA_ADPCMｴﾝｺｰﾄﾞのときに宣言する


/*
CH32V電子ｵﾙｺﾞｰﾙ演奏+音声再生ver1_4
これは根のｿｰｽｺｰﾄﾞ

・ﾀｰｹﾞｯﾄはCH32V002F4P6(内部48MHzｸﾛｯｸ)

・複数のSW･単数のCdS･複数のCVDを実装可能｡但しﾎﾟｰﾄ割当てが可能なもの｡
・それぞれをｵﾙｺﾞｰﾙ演奏･ﾌﾗｯｼｭ音声再生･ﾌﾟﾛｸﾞﾗﾑ音声再生の開始･中断に充てることができる｡
・短ｵﾝで開始､長ｵﾝで中断する｡
・曲･音声はﾗｳﾝﾄﾞﾛﾋﾞﾝ･ﾗﾝﾀﾞﾑが可能｡

・SWはﾎﾟｰﾄ-GND間に設置し､負論理(導通=L)で入力する｡

・CdSはﾎﾟｰﾄ-GND間に設置し､正論理(暗=H)で入力する｡

・CVDはCVDﾊﾟｯﾄﾞから10kΩの抵抗を介してﾎﾟｰﾄに入力する｡
　10kΩはﾎﾟｰﾄ保護のためであり､必須ではない｡

・xxxx_AUTOを宣言することで､自動的に曲を演奏開始､及び音声を再生開始する｡

・音声ﾃﾞｰﾀはﾌﾟﾛｸﾞﾗﾑﾒﾓﾘ､I2Cﾌﾗｯｼｭ､SDｶｰﾄﾞ､SPIﾌﾗｯｼｭに格納しておく｡


//==============================================
//I2Cﾌﾗｯｼｭﾒﾓﾘのﾋﾟﾝ接
//==============================================
1:A0(Vssに繋ぐ)
2:A1(Vssに繋ぐ)
3:A2(Vssに繋ぐ)
4:Vss
5:SDA(1.5kで外部ﾌﾟﾙｱｯﾌﾟ)
6:SCL(1.5kで外部ﾌﾟﾙｱｯﾌﾟ)
7:WP(Vccに繋ぐ)
8:Vcc


//==============================================
//SDCのﾋﾟﾝ接(SPIﾓｰﾄﾞ)
//==============================================
9:空き(不使用)
1:CS(2線SPIでは10k*220pの時定数回路を介してCLKに繋ぐ)
2:DI
3:Vss1
4:Vdd
5:CLK
6:Vss2
7:DO(2線SPI･3線SPIでは1.5kを介してDIに繋ぐ)
8:IRQ(不使用)


//==============================================
//SPIﾌﾗｯｼｭﾒﾓﾘのﾋﾟﾝ接
//==============================================
W25Qのﾋﾟﾝ接(標準SPIﾓｰﾄﾞ)
1:CS(2線SPIでは10k*220pの時定数回路を介してCLKに繋ぐ)
2:DO(2線SPI･3線SPIではDIに繋ぐ)
3:WP(GNDに接続)
4:GND
5:DI
6:CLK
7:HOLD(Vccに接続)
8:Vcc


//==============================================
//CH32Vのﾋﾟﾝ接
//==============================================
CH32V003F4P6のﾎﾟｰﾄの割当て
1:(PD4)LED1出力/(A7)CVD0入力
2:(PD5)/(UTX_)ﾃﾞﾊﾞｸﾞ情報出力
3:(PD6)/(URX_)ﾃﾞﾊﾞｸﾞ情報入力
4:(PD7)NRST
5:(PA1)SW0入力
6:(PA2)SW1入力
7:VSS
8:(PD0)SW3入力･ﾃﾞﾊﾞｸﾞ信号出力
9:VDD
10:(PC0)SS(SDCのCS･W25QのCSに繋ぐ､2線SPIのときは不使用)
11:(PC1)SDA/(I2C_SDA)(24FCのSDAに繋ぐ)
12:(PC2)SCL/(I2C_SCL)(24FCのSCLに繋ぐ)
13:(PC3)/(T1CH3)[ｼﾝｸﾞﾙ･ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ]正相出力/(T1CH1N)[ｺﾝﾌﾟﾘ]逆相出力
14:(PC4)/(T1CH1)[ｺﾝﾌﾟﾘ]正相出力/(T1CH4)[ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ]逆相出力
15:(PC5)SCK/(SPI_SCK)(SDCのCLK･W25QのCLKに繋ぐ)
16:(PC6)MOSI/(SPI_MOSI)(SDCのDI･W25QのDIに繋ぐ)
17:(PC7)MISO/(SPI_MISO)(SDCのDO･W25QのDOに繋ぐ､3線SPI･2線SPIのときは不使用)
18:(PD1)/(SWIO)
19:(PD2)LED0出力/(A3)CdS入力･CVD2入力
20:(PD3)SW2入力
*/


//==============================================
//ﾍｯﾀﾞﾌｧｲﾙの呼込み
//==============================================
#include <ch32v00X.h>				//ｼｽﾃﾑのﾍｯﾀﾞﾌｧｲﾙ
#include "orgel_cnf.h"				//ｵﾙｺﾞｰﾙ演奏処理と音声再生の構成を呼込む
#include "../../orgel.h"			//ｱﾌﾟﾘのﾍｯﾀﾞﾌｧｲﾙ


//==============================================
//構成情報(ｱﾌﾟﾘｹｰｼｮﾝとﾀｰｹﾞｯﾄﾃﾞﾊﾞｲｽに関わるもの)
//==============================================
//交代ﾋﾟﾝ設定
#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
#define	AFIO_PCFR1	0x04000c00		//SWIOﾋﾟﾝをPD1に戻す
						//T1CH1NはPC3､T1CH1はPC4
						//UART_TXはPD5､UART_RXはPD6
#else					//ｼﾝｸﾞﾙ･ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
#define	AFIO_PCFR1	0x04000000		//SWIOﾋﾟﾝをPD1に戻す
						//T1CH3はPC3､T1CH4はPC4
						//UART_TXはPD5､UART_RXはPD6
#endif

//ﾃﾞﾊﾞｸﾞ信号のﾎﾟｰﾄ定義
#define	DBS_GPIO	GPIOD			//ﾃﾞﾊﾞｸﾞ信号出力のﾎﾟｰﾄ
#define	DBS_BIT		0			//ﾃﾞﾊﾞｸﾞ信号出力のﾋﾞｯﾄ

//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ定義
#define	DBG_GPIO	GPIOD			//ﾃﾞﾊﾞｸﾞ情報出力のﾎﾟｰﾄ
#define	DBG_BIT		5			//ﾃﾞﾊﾞｸﾞ情報出力のﾋﾞｯﾄ
#define	DBG_IN_GPIO	GPIOD			//ﾃﾞﾊﾞｸﾞ情報入力のﾎﾟｰﾄ
#define	DBG_IN_BIT	6			//ﾃﾞﾊﾞｸﾞ情報入力のﾋﾞｯﾄ

//PWMのﾎﾟｰﾄ定義
#define	PWM_F_GPIO	GPIOC			//PWM正相のﾎﾟｰﾄ
#define	PWM_F_BIT	3			//PWM正相のﾋﾞｯﾄ
#define	PWM_R_GPIO	GPIOC			//PWM逆相のﾎﾟｰﾄ
#define	PWM_R_BIT	4			//PWM逆相のﾋﾞｯﾄ
#define	PWM_C_GPIO	GPIOC			//PWM相補のﾎﾟｰﾄ
#define	PWM_C_BIT	4			//PWM相補のﾋﾞｯﾄ

//I2Cのﾎﾟｰﾄ定義
#define I2C_SCL_GPIO	GPIOC			//I2C_SCLのﾎﾟｰﾄ
#define I2C_SCL_BIT	2			//I2C_SCLのﾋﾞｯﾄ
#define I2C_SDA_GPIO	GPIOC			//I2C_SDAのﾎﾟｰﾄ
#define I2C_SDA_BIT	1			//I2C_SDAのﾋﾞｯﾄ

//SPIのﾎﾟｰﾄ定義
#define SPI_MOSI_GPIO	GPIOC			//SPI_MOSIのﾎﾟｰﾄ
#define SPI_MOSI_BIT	6			//SPI_MOSIのﾋﾞｯﾄ
#define SPI_SCK_GPIO	GPIOC			//SPI_SCKのﾎﾟｰﾄ
#define SPI_SCK_BIT	5			//SPI_SCKのﾋﾞｯﾄ
#ifdef SPI2				//2線SPIのとき
#define	SPI_SS_TIME	5			//SSﾈｹﾞｰﾄ待ち時間[us]
#define SPI_SS_GPIO	SPI_SCK_GPIO		//SPI_SSのﾎﾟｰﾄ
#define SPI_SS_BIT	SPI_SCK_BIT		//SPI_SSのﾋﾞｯﾄ
#else					//3線SPIまたは4線SPIのとき
#define SPI_SS_GPIO	GPIOC			//SPI_SSのﾎﾟｰﾄ
#define SPI_SS_BIT	0			//SPI_SSのﾋﾞｯﾄ
#endif
#if defined(SPI2)||defined(SPI3)	//2線SPIまたは3線SPIのとき
#define	SPI_SOFT				//SPIをｿﾌﾄ実装する
#define SPI_MISO_GPIO	SPI_MOSI_GPIO		//SPI_MISOのﾎﾟｰﾄ
#define SPI_MISO_BIT	SPI_MOSI_BIT		//SPI_MISOのﾋﾞｯﾄ
#else					//4線SPIのとき
#define SPI_MISO_GPIO	GPIOC			//SPI_MISOのﾎﾟｰﾄ
#define SPI_MISO_BIT	7			//SPI_MISOのﾋﾞｯﾄ
#endif

//SPIのﾌﾟﾙｱｯﾌﾟ/ﾀﾞｳﾝ定義			//SWのﾎﾟｰﾄ定義と合わせること
#define	SPI_SCK_PU				//SPI_SCKをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_SCK_PD			//SPI_SCKをﾌﾟﾙﾀﾞｳﾝする
#define	SPI_MOSI_PU				//SPI_MOSIをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_MOSI_PD			//SPI_MOSIをﾌﾟﾙﾀﾞｳﾝする
#define	SPI_MISO_PU				//SPI_MISOをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_MISO_PD			//SPI_MISOをﾌﾟﾙﾀﾞｳﾝする

//SW0のﾎﾟｰﾄ定義
#define	SW0_GPIO	GPIOA			//SW0のﾎﾟｰﾄ
#define	SW0_EXTI_PORT	0			//SW0のEXTIﾎﾟｰﾄ(0=PA､2=PC､3=PD)
#define	SW0_BIT		1			//SW0のﾋﾞｯﾄ
#define	SW0_INV					//SW0入力は負論理
					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define SW0_TIMER				//SW0はﾀｲﾏｰﾓｰﾄﾞ
//#define	SW0_REAL			//SW0はﾘｱﾙﾓｰﾄﾞ
#define	SW0_CNT		ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//SW0の操作対象

//SW1のﾎﾟｰﾄ定義
#define	SW1_GPIO	GPIOA			//SW1のﾎﾟｰﾄ
#define	SW1_EXTI_PORT	0			//SW1のEXTIﾎﾟｰﾄ(0=PA､2=PC､3=PD)
#define	SW1_BIT		2			//SW1のﾋﾞｯﾄ
#define	SW1_INV					//SW1入力は負論理
					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define SW1_TIMER				//SW1はﾀｲﾏｰﾓｰﾄﾞ
//#define	SW1_REAL			//SW1はﾘｱﾙﾓｰﾄﾞ
#define	SW1_CNT		ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//SW1の操作対象

//SW2のﾎﾟｰﾄ定義
#define	SW2_GPIO	GPIOD			//SW2のﾎﾟｰﾄ
#define	SW2_EXTI_PORT	3			//SW2のEXTIﾎﾟｰﾄ(0=PA､2=PC､3=PD)
#define	SW2_BIT		3			//SW2のﾋﾞｯﾄ
#define	SW2_INV					//SW2入力は負論理
//					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define SW2_TIMER				//SW2はﾀｲﾏｰﾓｰﾄﾞ
//#define	SW2_REAL			//SW2はﾘｱﾙﾓｰﾄﾞ
#define	SW2_CNT		ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//SW2の操作対象

//SW3のﾎﾟｰﾄ定義
#if (!defined(SGDBS))&&(!defined(SHDBG))
#define	SW3_GPIO	GPIOD			//SW3のﾎﾟｰﾄ
#define	SW3_EXTI_PORT	3			//SW3のEXTIﾎﾟｰﾄ(0=PA､2=PC､3=PD)
#define	SW3_BIT		0			//SW3のﾋﾞｯﾄ
#define	SW3_INV					//SW3入力は負論理
//					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define SW3_TIMER				//SW3はﾀｲﾏｰﾓｰﾄﾞ
//#define	SW3_REAL			//SW3はﾘｱﾙﾓｰﾄﾞ
#define	SW3_CNT		ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//SW3の操作対象
#endif

//CdSのﾎﾟｰﾄ定義
#define	CdS_GPIO	GPIOD			//CdSのﾎﾟｰﾄ
#define	CdS_BIT		2			//CdSのﾋﾞｯﾄ
#define	CdS_An		3			//CdSのAn
//#define	CdS_INV				//CdS入力は負論理(暗=L)
					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define CdS_TIMER				//CdSはﾀｲﾏｰﾓｰﾄﾞ
//#define	CdS_REAL			//CdSはﾘｱﾙﾓｰﾄﾞ
#define	CdS_CNT	ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//CdSの操作対象

//CVD0のﾎﾟｰﾄ定義
#define	CVD0_GPIO	GPIOD			//CVD0のﾎﾟｰﾄ
#define	CVD0_BIT	4			//CVD0のﾋﾞｯﾄ
#define	CVD0_An		7			//CVD0のAn
					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define CVD0_TIMER				//CVD0はﾀｲﾏｰﾓｰﾄﾞ
//#define	CVD0_REAL			//CVD0はﾘｱﾙﾓｰﾄﾞ
#define	CVD0_CNT	ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//CVD0の操作対象

//CVD1のﾎﾟｰﾄ定義
//#define	CVD1_GPIO	GPIOD		//CVD1のﾎﾟｰﾄ
//#define	CVD1_BIT	5		//CVD1のﾋﾞｯﾄ
//#define	CVD1_An		5		//CVD1のAn
//					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
//#define CVD1_TIMER				//CVD1はﾀｲﾏｰﾓｰﾄﾞ
//#define	CVD1_REAL			//CVD1はﾘｱﾙﾓｰﾄﾞ
//#define	CVD1_CNT	ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//CVD1の操作対象

//CVD2のﾎﾟｰﾄ定義
//#define	CVD2_GPIO	GPIOD		//CVD2のﾎﾟｰﾄ
//#define	CVD2_BIT	6		//CVD2のﾋﾞｯﾄ
//#define	CVD2_An		6		//CVD2のAn
//					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
//#define CVD2_TIMER				//CVD2はﾀｲﾏｰﾓｰﾄﾞ
//#define	CVD2_REAL			//CVD2はﾘｱﾙﾓｰﾄﾞ
//#define	CVD2_CNT	ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//CVD2の操作対象

//CVD3のﾎﾟｰﾄ定義
//#define	CVD3_GPIO	GPIOD		//CVD3のﾎﾟｰﾄ
//#define	CVD3_BIT	2		//CVD3のﾋﾞｯﾄ
//#define	CVD3_An		3		//CVD3のAn
//					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
//#define CVD3_TIMER				//CVD3はﾀｲﾏｰﾓｰﾄﾞ
//#define	CVD3_REAL			//CVD3はﾘｱﾙﾓｰﾄﾞ
//#define	CVD3_CNT	ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//CVD3の操作対象

//LED0のﾎﾟｰﾄ定義
#define	LED0_GPIO	GPIOD			//LED0のﾎﾟｰﾄ
//#define	LED0_BIT	6		//LED0のﾋﾞｯﾄ

//LED1のﾎﾟｰﾄ定義
#define	LED1_GPIO	GPIOD			//LED1のﾎﾟｰﾄ
//#define	LED1_BIT	5		//LED1のﾋﾞｯﾄ

//LED2のﾎﾟｰﾄ定義
#define	LED2_GPIO	GPIOD			//LED2のﾎﾟｰﾄ
//#define	LED2_BIT	4		//LED2のﾋﾞｯﾄ

//LED3のﾎﾟｰﾄ定義
#define	LED3_GPIO	GPIOD			//LED3のﾎﾟｰﾄ
//#define	LED3_BIT	2		//LED3のﾋﾞｯﾄ


#if	KB_N>0
//==============================================
//KB演奏で使う音源波形とｴﾝﾍﾞﾛｰﾌﾟ波形のextern
//song_idx.sで実体をincludeしておくこと
//==============================================
extern const struct ENVE_HDR enve_EXP;
extern const struct ENVE_HDR enve_RSN;
extern const struct ENVE_HDR enve_VIB;
extern const struct ENVE_HDR enve_TREMOLO;
extern const struct ENVE_HDR enve_ELEGANTE;
extern const struct WAVE_HDR wave_SIN14;
extern const struct WAVE_HDR wave_SHEPARD;
extern const struct WAVE_HDR wave_RING4;
#endif


#if	PART_N+KB_N>0
//==============================================
//ｿﾝｸﾞﾃﾞｰﾀのｲﾝﾃﾞｯｸｽ
//==============================================
extern const struct SONG_IDX SONG_IDX;		//曲ｲﾝﾃﾞｯｸｽ実体
#endif


#if	VOICE_N>0
#ifdef VOICEN_IMA			//IMA-ADPCMのとき
//==============================================
//音声ﾃﾞｰﾀ
//==============================================
#include	"../../voice_WAN_IMA.c"
#include	"../../voice_DAME_IMA.c"
#include	"../../voice_CHIKO_IMA.c"

#else					//8ﾋﾞｯﾄPCMのとき
//==============================================
//音声ﾃﾞｰﾀ
//==============================================
#include	"../../voice_WAN.c"
#include	"../../voice_DAME.c"
#include	"../../voice_CHIKO.c"

#endif
//==============================================
//音声ﾃﾞｰﾀ(ﾌﾟﾛｸﾞﾗﾑﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEN_HDR voiceN_idx[]=
{
	von_mac(voice_WAN,sizeof(voice_WAN),8000)
	von_mac(voice_DAME,sizeof(voice_DAME),8000)
	von_mac(voice_CHIKO,sizeof(voice_CHIKO),8000)
};
#define VOICEN_SU	(sizeof(voiceN_idx)/sizeof(voiceN_idx[0]))
#endif


#if	VOICE_I>0
//==============================================
//音声ﾃﾞｰﾀ(I2Cﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEI_HDR voiceI_idx[]=
{

#ifdef VOICEI_IMA			//IMA-ADPCMのとき
	//voice_DAMEのW25Q_IMAを使う
	voi_mac(0x000000,0x0007df,8000,0xa0)	//1:WAN_1ch16bit16ksps.wav
	voi_mac(0x0007df,0x000797,8000,0xa0)	//2:DAME_1ch16bit16ksps.wav
	voi_mac(0x000f76,0x001d0b,8000,0xa0)	//3:CHIKO_1ch16bit16ksps.wav

#else					//8ﾋﾞｯﾄPCMのとき
	//voice_DAMEのW25Qを使う
	voi_mac(0x000000,0x000fbe,8000,0xa0)	//1:WAN_1ch16bit16ksps.wav
	voi_mac(0x000fbe,0x000f2f,8000,0xa0)	//2:DAME_1ch16bit16ksps.wav
	voi_mac(0x001eed,0x003a17,8000,0xa0)	//3:CHIKO_1ch16bit16ksps.wav
#endif

/*
	//｢ｷﾃｨﾐﾗｰﾅ｣の音声ﾃﾞｰﾀvoice_Mirrorna\W25Q16.hex)を使う
	voi_mac(0x000000,0x002401,8000,0xa0)	//1:sharin.wav
	voi_mac(0x002401,0x004575,8000,0xa0)	//2:kirakiraomeme.wav
	voi_mac(0x006976,0x001956,8000,0xa0)	//3:aidorumitai.wav
	voi_mac(0x0082cc,0x002b18,8000,0xa0)	//4:kyounooshare.wav
	voi_mac(0x00ade4,0x001d61,8000,0xa0)	//5:egaogasuteki.wav
	voi_mac(0x00cb45,0x0033a5,8000,0xa0)	//6:kirarin.wav
*/
};
#define VOICEI_SU	(sizeof(voiceI_idx)/sizeof(voiceI_idx[0]))
#endif


#if	VOICE_C>0
//==============================================
//音声ﾃﾞｰﾀ(SDｶｰﾄﾞ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEC_HDR voiceC_idx[]=
{

	//｢ｱﾝﾊﾟﾝﾏﾝｼｮｰ｣の音声ﾃﾞｰﾀ(SDのANPANMAN.wav)を使う
	voc_mac(0x00029e,0x00e367,8000)		//anpan
	voc_mac(0x002000,0x000080,8000)		//anpanの一部(ﾃｽﾄ用)
	voc_mac(0x004000,0x000080,8000)		//anpanの一部(ﾃｽﾄ用)

};
#define VOICEC_SU	(sizeof(voiceC_idx)/sizeof(voiceC_idx[0]))
#endif


#if	VOICE_S>0
//==============================================
//音声ﾃﾞｰﾀ(SPIﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICES_HDR voiceS_idx[]=
{

#ifdef VOICES_IMA			//IMA-ADPCMのとき
	//｢ｷﾃｨﾐﾗｰﾅ｣の音声ﾃﾞｰﾀ(voice_Mirrorna\W25Q_IMA.hex)を使う
	vos_mac(0x000000,0x001200,8000)	//1:sharin.wav
	vos_mac(0x001200,0x0022ba,8000)	//2:kirakiraomeme.wav
	vos_mac(0x0034ba,0x000cab,8000)	//3:aidorumitai.wav
	vos_mac(0x004165,0x00158c,8000)	//4:kyounooshare.wav
	vos_mac(0x0056f1,0x000eb0,8000)	//5:egaogasuteki.wav
	vos_mac(0x0065a1,0x0019d2,8000)	//6:kirarin.wav

#else
	//｢ｷﾃｨﾐﾗｰﾅ｣の音声ﾃﾞｰﾀ(voice_Mirrorna\W25Q.hex)を使う
	vos_mac(0x000000,0x002401,8000)		//sharin.wav
	vos_mac(0x002401,0x004575,8000)		//kirakiraomeme.wav
	vos_mac(0x006976,0x001956,8000)		//aidorumitai.wav
	vos_mac(0x0082cc,0x002b18,8000)		//kyounooshare.wav
	vos_mac(0x00ade4,0x001d61,8000)		//egaogasuteki.wav
	vos_mac(0x00cb45,0x0033a5,8000)		//kirarin.wav
#endif

/*
	//voice_ToyStory\W25Q16_12ksps8bit.hexを使う
	vos_mac(0x000000,0x0afc83,12000)	//ToyStory_12ksps8bit
*/

};
#define VOICES_SU	(sizeof(voiceS_idx)/sizeof(voiceS_idx[0]))
#endif


//==============================================
//共通ｺｰﾄﾞの呼込み
//==============================================
#include "../../dev_V002F4P6.c"			//V002F4P6ﾃﾞﾊﾞｲｽｺｰﾄﾞ
#include "../../apl_KB.c"			//KB操作ｱﾌﾟﾘｹｰｼｮﾝ
