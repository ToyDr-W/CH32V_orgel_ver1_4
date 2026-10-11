//#define	SHDBG		//ﾃﾞﾊﾞｸﾞ情報を取得するときに宣言する
//#define	SHBPS	115200	//ﾃﾞﾊﾞｸﾞ情報のﾎﾞｰﾚｰﾄを宣言する(ﾃﾞﾌｫﾙﾄ値は38400bps)
//#define	SHDBS		//ﾃﾞﾊﾞｸﾞ信号を取得するときに宣言する

//#define	I2C_SOFT	//I2Cをｿﾌﾄ実装するときに宣言する
//#define	SPI2		//2線SPIのときに宣言する
//#define	SPI3		//3線SPIのときに宣言する
//#define	SPI_SOFT	//SPIをｿﾌﾄ実装するときに宣言する

//#define	MFRC_SPI3	//3線SPIのときに宣言する
#define		MFRC_SPI2	//2線SPIのときに宣言する


/*
CH32V電子ｵﾙｺﾞｰﾙ演奏+音声再生ver1_4
これは根のｿｰｽｺｰﾄﾞ

・ﾀｰｹﾞｯﾄはCH32V003F4P6(内部48MHzｸﾛｯｸ)

・RFIDﾀｸﾞのｼﾘｱﾙ番号を読込んで､対応する曲/音声を再生する｡

・音声ﾃﾞｰﾀはﾌﾟﾛｸﾞﾗﾑﾌﾗｯｼｭ､I2Cﾌﾗｯｼｭ､SDｶｰﾄﾞ､SPIﾌﾗｯｼｭに格納しておく｡


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
//RFID_RC522のﾋﾟﾝ接
//==============================================
1:NSS(基板ｼﾙｸはSDA)(SPIのSS)(2線SPIでは10k*220pの時定数回路を介してCLKに繋ぐ)
2:SCK(SPIのSCK)
3:MOSI(SPIのMOSI)
4:MISO(SPIのMISO)(3線SPIでは3.3kを介してMOSIに繋ぐ)
5:IRQ(このﾌｧｰﾑｳｪｱでは不使用)
6:GND
7:RST(このﾌｧｰﾑｳｪｱでは不使用)
8:3.3V


//==============================================
//CH32Vのﾋﾟﾝ接
//==============================================
CH32V003F4P6のﾎﾟｰﾄの割当て
1:(PD4)MFRC_MISO(RC522のMISOに繋ぐ3線SPI･2線SPIのときは不使用)
2:(PD5)MFRC_MOSI(RC522のMOSIに繋ぐ)
3:(PD6)MFRC_SCK(RC522のSCKに繋ぐ)
4:(PD7)NRST
5:(PA1)MFRC_NSS(RC522のNSSに繋ぐ､2線SPIのときは不使用)
6:(PA2)
7:VSS
8:(PD0)ﾃﾞﾊﾞｸﾞ信号出力/(UTX_)ﾃﾞﾊﾞｸﾞ情報出力
9:VDD
10:(PC0)SS(SDCのCS･W25QのCSに繋ぐ)
11:(PC1)SDA/(I2C_SDA)(24FCのSDAに繋ぐ)
12:(PC2)SCL/(I2C_SCL)(24FCのSCLに繋ぐ)
13:(PC3)/(T1CH3)[ｼﾝｸﾞﾙ･ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ]正相出力/(T1CH1N)[ｺﾝﾌﾟﾘ]逆相出力
14:(PC4)/(T1CH1)[ｺﾝﾌﾟﾘ]正相出力/(T1CH4)[ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ]逆相出力
15:(PC5)SCK/(SPI_SCK)(SDCのCLK･W25QのCLKに繋ぐ､2線SPIのときは不使用)
16:(PC6)MOSI/(SPI_MOSI)(SDCのDI･W25QのDIに繋ぐ)
17:(PC7)MISO/(SPI_MISO)(SDCのDO･W25QのDOに繋ぐ､3線SPI･2線SPIのときは不使用)
18:(PD1)/(SWIO)
19:(PD2)LED1出力
20:(PD3)LED0出力
*/


//==============================================
//ﾍｯﾀﾞﾌｧｲﾙの呼込み
//==============================================
#include <ch32v00x.h>				//ｼｽﾃﾑのﾍｯﾀﾞﾌｧｲﾙ
#include "orgel_cnf.h"				//ｵﾙｺﾞｰﾙ演奏処理と音声再生の構成を呼込む
#include "../../orgel.h"			//ｱﾌﾟﾘのﾍｯﾀﾞﾌｧｲﾙ


//==============================================
//ﾀｸﾞのｼﾘｱﾙ番号(5ﾊﾞｲﾄ目)
//==============================================
#define	TAG_NO0	0x33	//ﾀｸﾞ1(白ｶｰﾄﾞ)
#define	TAG_NO1	0x98	//ﾀｸﾞ2(赤ｺｲﾝ)
#define	TAG_NO2	0xa2	//ﾀｸﾞ3(青ｺｲﾝ)
#define	TAG_NO3	0x04	//ﾀｸﾞ4(黄ｺｲﾝ)


//==============================================
//構成情報(ｱﾌﾟﾘｹｰｼｮﾝとﾀｰｹﾞｯﾄﾃﾞﾊﾞｲｽに関わるもの)
//==============================================
//交代ﾋﾟﾝ設定
#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
#define	AFIO_PCFR1	0x040000c4		//SWIOﾋﾟﾝをPD1に戻す
						//UTXはPD0
						//T1CH1NはPC3､T1CH1はPC4
#else					//ｼﾝｸﾞﾙ･ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
#define	AFIO_PCFR1	0x04000004		//SWIOﾋﾟﾝをPD1に戻す
						//UTXはPD0
						//T1CH3はPC3､T1CH4はPC4
#endif

//ﾃﾞﾊﾞｸﾞ信号のﾎﾟｰﾄ定義
#define	DBS_GPIO	GPIOD			//ﾃﾞﾊﾞｸﾞ信号のﾎﾟｰﾄ
#define	DBS_BIT		0			//ﾃﾞﾊﾞｸﾞ信号のﾋﾞｯﾄ

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
#define SPI_SS_GPIO	GSPI_SCK_GPIO		//SPI_SSのﾎﾟｰﾄ
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

//MFRCのﾎﾟｰﾄ定義
#define MFRC_SCK_GPIO	GPIOD			//RC522_SCKのﾎﾟｰﾄ
#define MFRC_SCK_BIT	6			//RC522_SCKのﾋﾞｯﾄ
#define MFRC_MOSI_GPIO	GPIOD			//RC522_MOSIのﾎﾟｰﾄ
#define MFRC_MOSI_BIT	5			//RC522_MOSIのﾋﾞｯﾄ
#if defined(MFRC_SPI3)||defined(MFRC_SPI2)
					//3線SPIか2線SPIのとき
#define MFRC_MISO_GPIO	MFRC_MOSI_GPIO		//RC522_MISOのﾎﾟｰﾄ
#define MFRC_MISO_BIT	MFRC_MOSI_BIT		//RC522_MISOのﾋﾞｯﾄ
#else					//4線SPIのとき
#define MFRC_MISO_GPIO	GPIOD			//RC522_MISOのﾎﾟｰﾄ
#define MFRC_MISO_BIT	4			//RC522_MISOのﾋﾞｯﾄ
#endif
#ifdef  MFRC_SPI2			//2線SPIのとき
#define MFRC_SS_TIME	5			//SSﾈｹﾞｰﾄ待ち時間[us]
#define MFRC_NSS_GPIO	MFRC_SCK_GPIO		//RC522_NSSのﾎﾟｰﾄ
#define MFRC_NSS_BIT	MFRC_SCK_BIT		//RC522_NSSのﾋﾞｯﾄ
#else					//4線SPIか3線SPIのとき
#define MFRC_NSS_GPIO	GPIOA			//RC522_NSSのﾎﾟｰﾄ
#define MFRC_NSS_BIT	1			//RC522_NSSのﾋﾞｯﾄ
#endif


#if	PART_N+KB_N>0
//==============================================
//ｿﾝｸﾞﾃﾞｰﾀのｲﾝﾃﾞｯｸｽ
//==============================================
extern const struct SONG_IDX SONG_IDX;		//曲ｲﾝﾃﾞｯｸｽ実体
#endif


#if	VOICE_N>0
//==============================================
//音声ﾃﾞｰﾀ
//==============================================
#include	"../../voice_AKA.c"
#include	"../../voice_AO.c"
#include	"../../voice_KIIRO.c"


//==============================================
//音声ﾃﾞｰﾀ(ﾌﾟﾛｸﾞﾗﾑﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEN_HDR voiceN_idx[]=
{
	von_mac(voice_AKA,sizeof(voice_AKA),8000)
	von_mac(voice_AO,sizeof(voice_AO),8000)
	von_mac(voice_KIIRO,sizeof(voice_KIIRO),8000)
};
#define VOICEN_SU	(sizeof(voiceN_idx)/sizeof(voiceN_idx[0]))
#endif


#if	VOICE_I>0
//==============================================
//音声ﾃﾞｰﾀ(I2Cﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEI_HDR voiceI_idx[]=
{

	//｢ｷﾃｨﾐﾗｰﾅ｣の音声ﾃﾞｰﾀ(Mirrorna_24FC512.XのMirrorna_24FC512.X)を使う
	voi_mac(0x4B88,0x1B8A,8000,0xa0)	//AIDORUMITAI
	voi_mac(0x97C2,0x2076,8000,0xa0)	//EGAOGASUTEKI
	voi_mac(0x0000,0x4B88,8000,0xa0)	//KIRAKIRAOMEME
	voi_mac(0xB838,0x3626,8000,0xa0)	//KIRARIN
	voi_mac(0x6712,0x30B0,8000,0xa0)	//KYOUNOOSHARE

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

	//voice_ToyStory\W25Q16_12ksps8bit.hexを使う
//	vos_mac(0x000000,0x0afc83,12000)	//ToyStory_12ksps8bit

	//｢ｷﾃｨﾐﾗｰﾅ｣の音声ﾃﾞｰﾀ(voice_Mirrorna\W25Q16.hex)を使う
	vos_mac(0x000000,0x002401,8000)		//sharin.wav
	vos_mac(0x002401,0x004575,8000)		//kirakiraomeme.wav
	vos_mac(0x006976,0x001956,8000)		//aidorumitai.wav
	vos_mac(0x0082cc,0x002b18,8000)		//kyounooshare.wav
	vos_mac(0x00ade4,0x001d61,8000)		//egaogasuteki.wav
	vos_mac(0x00cb45,0x0033a5,8000)		//kirarin.wav

};
#define VOICES_SU	(sizeof(voiceS_idx)/sizeof(voiceS_idx[0]))
#endif


//==============================================
//共通ｺｰﾄﾞの呼込み
//==============================================
#include "../../dev_V003F4P6.c"			//V003F4P6ﾃﾞﾊﾞｲｽｺｰﾄﾞ
#include "../../apl_RFID.c"			//RFID操作ｱﾌﾟﾘｹｰｼｮﾝ
