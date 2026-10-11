//#define	SHDBS		//ﾃﾞﾊﾞｸﾞ信号を出力するときに宣言する
//#define	SHDBG		//ﾃﾞﾊﾞｸﾞ情報を出力するときに宣言する
//#define	SHBPS	115200	//ﾃﾞﾊﾞｸﾞ情報のﾎﾞｰﾚｰﾄを宣言する(ﾃﾞﾌｫﾙﾄ値は38400bps)
//#define	SHDBG_SOFT	//ﾃﾞﾊﾞｸﾞ情報のUARTをｿﾌﾄ実装するときに宣言する		

//#define		SLEEP_EN	//Sleep機能を実装するときに宣言する


/*
CH32V電子ｵﾙｺﾞｰﾙ演奏+音声再生ver1_4
これは根のｿｰｽｺｰﾄﾞ

・ﾀｰｹﾞｯﾄはCH32V002F4P6(内部48MHzｸﾛｯｸ)

・ｱｸｾﾙﾍﾟﾀﾞﾙSWでｴﾝｼﾞﾝ音を低速～高速に変える｡｡


//==============================================
//CH32Vのﾋﾟﾝ接
//==============================================
CH32V002F4P6のﾎﾟｰﾄの割当て
1:(PD4)LED2出力/(A7)CVD0入力
2:(PD5)LED1出力/(A5)CVD1入力
3:(PD6)LED0出力/(A6)CVD2入力
4:(PD7)RST
5:(PA1)SW0入力
6:(PA2)SW1入力
7:VSS
8:(PD0)SW3入力･ﾃﾞﾊﾞｸﾞ信号出力/(USART1_TX_2)ﾃﾞﾊﾞｸﾞ情報出力
9:VDD
10:(PC0)SW6入力･SS(SDCのCS･W25QのCSに繋ぐ､2線SPIのときは不使用)
11:(PC1)SDA/(I2C_SDA)(24FCのSDAに繋ぐ)
12:(PC2)SCL/(I2C_SCL)(24FCのSCLに繋ぐ)
13:(PC3)/(T1CH3)[ｼﾝｸﾞﾙ･ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ]正相出力/(T1CH1N)[ｺﾝﾌﾟﾘ]逆相出力
14:(PC4)/(T1CH1)[ｺﾝﾌﾟﾘ]正相出力/(T1CH4)[ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ]逆相出力
15:(PC5)SCK/(SPI_SCK)(SDCのCLK･W25QのCLKに繋ぐ)
16:(PC6)MOSI/(SPI_MOSI)(SDCのDI･W25QのDIに繋ぐ)
17:(PC7)MISO/(SPI_MISO)(SDCのDO･W25QのDOに繋ぐ､3線SPI･2線SPIのときは不使用)
18:(PD1)/(SWIO)
19:(PD2)LED3出力/(A3)CdS入力･CVD3入力
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
#define	AFIO_PCFR1	0x04000c80		//SWIOﾋﾟﾝをPD1に戻す
						//UTXはPD0
						//T1CH1NはPC3､T1CH1はPC4
#else					//ｼﾝｸﾞﾙ･ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
#define	AFIO_PCFR1	0x04000080		//SWIOﾋﾟﾝをPD1に戻す
						//UTXはPD0
						//T1CH3はPC3､T1CH4はPC4
#endif

//ﾃﾞﾊﾞｸﾞ信号のﾎﾟｰﾄ定義
#define	DBS_GPIO	GPIOD			//ﾃﾞﾊﾞｸﾞ信号のﾎﾟｰﾄ
#define	DBS_BIT		0			//ﾃﾞﾊﾞｸﾞ信号のﾋﾞｯﾄ

//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ定義
#define	DBG_GPIO	GPIOD			//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ
#define	DBG_BIT		0			//ﾃﾞﾊﾞｸﾞ情報のﾋﾞｯﾄ

//PWMのﾎﾟｰﾄ定義
#define	PWM_F_GPIO	GPIOC			//PWM正相のﾎﾟｰﾄ
#define	PWM_F_BIT	3			//PWM正相のﾋﾞｯﾄ
#define	PWM_R_GPIO	GPIOC			//PWM逆相のﾎﾟｰﾄ
#define	PWM_R_BIT	4			//PWM逆相のﾋﾞｯﾄ
#define	PWM_C_GPIO	GPIOC			//PWM相補のﾎﾟｰﾄ
#define	PWM_C_BIT	4			//PWM相補のﾋﾞｯﾄ

//SWのﾎﾟｰﾄ定義
#define	SW0_GPIO	GPIOA			//SW0のﾎﾟｰﾄ
#define	SW0_BIT		1			//SW0のﾋﾞｯﾄ


#if	PART_N>0
//==============================================
//ｿﾝｸﾞﾃﾞｰﾀのｲﾝﾃﾞｯｸｽ
//==============================================
extern const struct SONG_IDX SONG_IDX;		//曲ｲﾝﾃﾞｯｸｽ実体
#endif


#if	VOICE_N>0
//==============================================
//音声ﾃﾞｰﾀ
//==============================================
#include	"..\..\voice_ENGINE2.c"


//==============================================
//音声ﾃﾞｰﾀ(ﾌﾟﾛｸﾞﾗﾑﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEN_HDR voiceN_idx[]=
{
	von_mac(voice_ENGINE2,sizeof(voice_ENGINE2),4000)
};
#define VOICEN_SU	(sizeof(voiceN_idx)/sizeof(voiceN_idx[0]))
#endif


//==============================================
//共通ｺｰﾄﾞの呼込み
//==============================================
#include "..\..\dev_V002F4P6.c"			//F002A_16ﾋﾟﾝﾃﾞﾊﾞｲｽｺｰﾄﾞ
#include "..\..\apl_SW-PEDAL.c"			//ﾄﾞﾗｲﾌﾞﾊﾝﾄﾞﾙのｱﾌﾟﾘｹｰｼｮﾝ
