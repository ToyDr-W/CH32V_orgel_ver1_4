//#define	SHDBS		//ﾃﾞﾊﾞｸﾞ信号を出力するときに宣言する
				//下記行は､ﾃﾞﾊﾞｸﾞ入力で制御するため有効にしておくこと
#define		SHDBG		//ﾃﾞﾊﾞｸﾞ情報を出力するときに宣言する
//#define	SHBPS	115200	//ﾃﾞﾊﾞｸﾞ情報のﾎﾞｰﾚｰﾄを宣言する(ﾃﾞﾌｫﾙﾄ値は38400bps)
//#define	SHDBG_SOFT	//ﾃﾞﾊﾞｸﾞ情報のUARTをｿﾌﾄ実装するときに宣言する		
//#define	SHDBG_IN	//ﾃﾞﾊﾞｸﾞ情報を入力するときに宣言する(UARTのｿﾌﾄ実装は不可)

//#define	I2C_SOFT	//I2Cをｿﾌﾄ実装するときに宣言する
//#define	SPI_SOFT	//SPIをｿﾌﾄ実装するときに宣言する
//#define	SHSPI2		//2線SPIのときに宣言する
//#define	SHSPI3		//3線SPIのときに宣言する
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

//#define	ISP_SPIFLASH_EN	//SPIﾌﾗｯｼｭをSPIするときに宣言する
				//(自動的に､ﾃﾞﾊﾞｸﾞ情報のUART内蔵ﾓｼﾞｭｰﾙを230400bpsで使用する)
				//(通常のｱﾌﾟﾘは実行されない)


/*
CH32V電子ｵﾙｺﾞｰﾙ演奏+音声再生ver1_4
これは根のｿｰｽｺｰﾄﾞ

・ISP形態でSPIﾌﾗｯｼｭを書替える機能(ISP_SPIFLASH)に対応している｡
　但し､ﾋﾟﾝ割当てによっては機能できない場合がある｡

・ﾀｰｹﾞｯﾄはCH32V002J4M6(内部48MHzｸﾛｯｸ)

・UARTから受信したKB演奏ﾃﾞｰﾀに従って､orgelｴﾝｼﾞﾝへ音符ｺｰﾄﾞを送って演奏させる｡

・白鍵と黒鍵をPCのｷｰﾎﾞｰﾄﾞ上に配置して演奏する｡

・UARTから受信したｵﾙｺﾞｰﾙ演奏､或いはSPI音声再生の指示ﾃﾞｰﾀに従って､それらを起動する｡

・その他の音声再生機能は､このｻﾝﾌﾟﾙｱﾌﾟﾘでは実装していない


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
3:WP(GNDに接続､ISPを利用する場合はVccに接続)
4:GND
5:DI
6:CLK
7:HOLD(Vccに接続)
8:Vcc


//==============================================
//CH32Vのﾋﾟﾝ接
//ﾋﾟﾝ数が足りないためI2Cを非ｻﾎﾟｰﾄとする
//内蔵SPIがﾋﾟﾝに出ていないので3線SPIでｿﾌﾄ実装する
//==============================================
CH32V002J4M6のﾎﾟｰﾄの割当て
1:(PA1)
1:(PD6)/(USART1_RX)UART入力
2:VSS
3:(PA2)[ｼﾝｸﾞﾙ]SW2入力､LED0出力､ﾃﾞﾊﾞｸﾞ情報出力/
	[ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ](TIM1_CH2N)逆相出力
4:VDD
5:(PC1)SCK(SDCのCLK･W25QのCLKに繋ぐ)､
	SW1入力
6:(PC2)SS(SDCのCS･W25QのCSに繋ぐ)
7:(PC4)MOSI(SDCのDI･W25QのDIに繋ぐ)､
	SW0入力/
	(ADC_IN2)CdS入力､CVD0入力
8:(PD1)/(TIM1_CH3N)正相出力/(SWIO)
8:(PD4)
8:(PD5)(USART1_TX)UART出力
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
///SWIO交代ﾋﾟﾝ設定
#define	AFIO_PCFR1	0x04000000		//SWIOﾋﾟﾝをPD1に戻す

//UARTのﾎﾟｰﾄ定義
#define	UART_GPIO	GPIOD			//UART出力のﾎﾟｰﾄ
#define	UART_BIT	5			//UART出力のﾋﾞｯﾄ
#define	UART_IN_GPIO	GPIOD			//UART入力のﾎﾟｰﾄ
#define	UART_IN_BIT	6			//UART入力のﾋﾞｯﾄ

//ﾃﾞﾊﾞｸﾞ信号のﾎﾟｰﾄ定義
#define	DBS_GPIO	GPIOA			//ﾃﾞﾊﾞｸﾞ信号のﾎﾟｰﾄ
#define	DBS_BIT		2			//ﾃﾞﾊﾞｸﾞ信号のﾋﾞｯﾄ

//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ定義
#define	SHDBG_SOFT				//ﾃﾞﾊﾞｸﾞ情報のUARTをｿﾌﾄ実装する
#define	DBG_GPIO	GPIOA			//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ
#define	DBG_BIT		2			//ﾃﾞﾊﾞｸﾞ情報のﾋﾞｯﾄ

//PWMのﾎﾟｰﾄ定義
#define	PWM_3N				//CH3Nを正相とする
#define	PWM_F_GPIO	GPIOD			//PWM正相のﾎﾟｰﾄ
#define	PWM_F_BIT	1			//PWM正相のﾋﾞｯﾄ
#if !defined(SHDBG)&&!defined(SHDBS)	//ﾃﾞﾊﾞｸﾞ信号･ﾃﾞﾊﾞｸﾞ情報を出力しないとき
#define	PWM_R_GPIO	GPIOA			//PWM逆相のﾎﾟｰﾄ
#define	PWM_R_BIT	2			//PWM逆相のﾋﾞｯﾄ
#endif

//SPIのﾎﾟｰﾄ定義
#define	SPI_SOFT				//SPIをｿﾌﾄ実装する
#define	SHSPI3					//3線SPIで繋ぐ
#define	SPI_SS_TIME	10			//SSﾈｹﾞｰﾄ待ち時間[us]
#define SPI_SCK_GPIO	GPIOC			//SPI_SCKのﾎﾟｰﾄ
#define SPI_SCK_BIT	1			//SPI_SCKのﾋﾞｯﾄ
#define SPI_MOSI_GPIO	GPIOC			//SPI_MOSIのﾎﾟｰﾄ
#define SPI_MOSI_BIT	4			//SPI_MOSIのﾋﾞｯﾄ
#define SPI_SS_GPIO	GPIOC			//SPI_SSのﾎﾟｰﾄ
#define SPI_SS_BIT	2			//SPI_SSのﾋﾞｯﾄ
#define SPI_MISO_GPIO	SPI_MOSI_GPIO		//SPI_MISOのﾎﾟｰﾄ
#define SPI_MISO_BIT	SPI_MOSI_BIT		//SPI_MISOのﾋﾞｯﾄ

//SPIのﾌﾟﾙｱｯﾌﾟ/ﾀﾞｳﾝ定義			//SWの論理極性と合わせること
#define	SPI_SCK_PU				//SPI_SCKをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_SCK_PD			//SPI_SCKをﾌﾟﾙﾀﾞｳﾝする
#define	SPI_MOSI_PU				//SPI_MOSIをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_MOSI_PD			//SPI_MOSIをﾌﾟﾙﾀﾞｳﾝする
#define	SPI_MISO_PU				//SPI_MISOをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_MISO_PD			//SPI_MISOをﾌﾟﾙﾀﾞｳﾝする

//SW0のﾎﾟｰﾄ定義
#define	SW0_GPIO	GPIOC			//SW0のﾎﾟｰﾄ
#define	SW0_EXTI_PORT	2			//SW0のEXTIﾎﾟｰﾄ(0=PA､2=PC､3=PD)
#define	SW0_BIT		4			//SW0のﾋﾞｯﾄ
#define	SW0_INV					//SW0入力は負論理
//					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define SW0_TIMER				//SW0はﾀｲﾏｰﾓｰﾄﾞ
//#define	SW0_REAL			//SW0はﾘｱﾙﾓｰﾄﾞ
#define	SW0_CNT		ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//SW0の操作対象

//SW1のﾎﾟｰﾄ定義
#define	SW1_GPIO	GPIOC			//SW1のﾎﾟｰﾄ
#define	SW1_EXTI_PORT	2			//SW1のEXTIﾎﾟｰﾄ(0=PA､2=PC､3=PD)
#define	SW1_BIT		1			//SW1のﾋﾞｯﾄ
#define	SW1_INV					//SW1入力は負論理
//					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define SW1_TIMER				//SW1はﾀｲﾏｰﾓｰﾄﾞ
//#define	SW1_REAL			//SW1はﾘｱﾙﾓｰﾄﾞ
#define	SW1_CNT		ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//SW1の操作対象

//SW2のﾎﾟｰﾄ定義
#if !defined(SHDBG)&&!defined(SHDBS)	//ﾃﾞﾊﾞｸﾞ信号･ﾃﾞﾊﾞｸﾞ情報を出力しないとき
#if BTL==1				//ｼﾝｸﾞﾙのとき
#define	SW2_GPIO	GPIOA			//SW2のﾎﾟｰﾄ
#define	SW2_EXTI_PORT	0			//SW2のEXTIﾎﾟｰﾄ(0=PA､2=PC､3=PD)
#define	SW2_BIT		2			//SW2のﾋﾞｯﾄ
#define	SW2_INV					//SW2入力は負論理
//					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define SW2_TIMER				//SW2はﾀｲﾏｰﾓｰﾄﾞ
//#define	SW2_REAL			//SW2はﾘｱﾙﾓｰﾄﾞ
#define	SW2_CNT		ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//SW2の操作対象
#endif
#endif

//CdSのﾎﾟｰﾄ定義
#define	CdS_GPIO	GPIOC			//CdSのﾎﾟｰﾄ
#define	CdS_BIT		4			//CdSのﾋﾞｯﾄ
#define	CdS_An		2			//CdSのAn
//#define	CdS_INV				//CdS入力は負論理(暗=L)
//					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define CdS_TIMER				//CdSはﾀｲﾏｰﾓｰﾄﾞ
//#define	CdS_REAL			//CdSはﾘｱﾙﾓｰﾄﾞ
#define	CdS_CNT		ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//CdSの操作対象

//CVD0のﾎﾟｰﾄ定義
#if BTL!=1				//ｺﾝﾌﾟﾘ以外のとき
#define	CVD0_GPIO	GPIOC			//CVD0のﾎﾟｰﾄ
#define	CVD0_BIT	4			//CVD0のﾋﾞｯﾄ
#define	CVD0_An		2			//CVD0のAn
//					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define CVD0_TIMER				//CVD0はﾀｲﾏｰﾓｰﾄﾞ
//#define	CVD0_REAL			//CVD0はﾘｱﾙﾓｰﾄﾞ
#define	CVD0_CNT	ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//CVD0の操作対象
#endif

//CVD1のﾎﾟｰﾄ定義
#if BTL==1				//ｼﾝｸﾞﾙ･ｺﾝﾌﾟﾘのとき
#define	CVD1_GPIO	GPIOA			//CVD1のﾎﾟｰﾄ
#define	CVD1_BIT	2			//CVD1のﾋﾞｯﾄ
#define	CVD1_An		0			//CVD1のAn
//					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define CVD1_TIMER				//CVD1はﾀｲﾏｰﾓｰﾄﾞ
//#define	CVD1_REAL			//CVD1はﾘｱﾙﾓｰﾄﾞ
#define	CVD1_CNT	ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//CVD1の操作対象
#endif

//LED0のﾎﾟｰﾄ定義
#if BTL==1				//ｺﾝﾌﾟﾘのとき
//#define	LED0_GPIO	GPIOA		//LED0のﾎﾟｰﾄ
//#define	LED0_BIT	2		//LED0のﾋﾞｯﾄ
#endif


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
#ifdef ISP_SPIFLASH_EN			//ISP環境でSPIﾌﾗｯｼｭを書替えるとき
#define	UARTBPS	230400				//UARTは230400bps
#define	UART_TX					//UART送信を使う
#define	UART_RX					//UART受信を使う
#include "../../dev_V002J4M6.c"			//V002J4M6ﾃﾞﾊﾞｲｽｺｰﾄﾞ
#include "../../apl_ISP_SPIFLASH.c"		//ISP実行ｱﾌﾟﾘｹｰｼｮﾝ
#else					//KB演奏のとき
#define	UARTBPS	38400				//UARTは38400bps
#define	UART_RX					//UART受信を使う
#include "../../dev_V002J4M6.c"			//V002J4M6ﾃﾞﾊﾞｲｽｺｰﾄﾞ
#include "../../apl_KB.c"			//KB操作ｱﾌﾟﾘｹｰｼｮﾝ
#endif
