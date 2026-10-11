//SW･CdS･CVDでCH32V電子ｵﾙｺﾞｰﾙを制御するｱﾌﾟﾘｹｰｼｮﾝの共通機能部

//これはapl_SW.cをﾍﾞｰｽにｷｰﾎﾞｰﾄﾞ操作に対応したｻﾝﾌﾟﾙ｡

//下記はｵﾘｼﾞﾅﾙのapl_SW.cの説明
//複数のSW･１個のCdS･複数のCVDを実装可能｡但しﾎﾟｰﾄ割当てが可能なもの｡
//それぞれをｵﾙｺﾞｰﾙ演奏･ﾌﾗｯｼｭ音声再生･ﾌﾟﾛｸﾞﾗﾑ音声再生の開始･中断に充てることができる｡
//短ｵﾝで開始､長ｵﾝで中断する｡
//曲･音声はﾗｳﾝﾄﾞﾛﾋﾞﾝ･ﾗﾝﾀﾞﾑが可能｡

//SWﾎﾟｰﾄの内部ﾌﾟﾙｱｯﾌﾟ/ﾀﾞｳﾝはこのｺｰﾄﾞ内で行っている｡
//CdSﾎﾟｰﾄの内部ﾌﾟﾙｱｯﾌﾟ/ﾀﾞｳﾝはfunc_CdS.cで行っている｡
//CVDﾎﾟｰﾄの内部ﾌﾟﾙﾀﾞｳﾝはfunc_CVD.cで行っている｡

//下記のｵﾌﾟｼｮﾝ設定を呼出し元で宣言しておくこと｡
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


//==============================================
//構成情報(個別ｱﾌﾟﾘｹｰｼｮﾝだけで使うもの)
//==============================================
#define	SLEEP_TMR	1000		//Sleepに入る前の時限[ms]
					//　操作の評価時間よりも長くすること


//==============================================
//操作のﾋﾞｯﾄ定義
//==============================================
#define	ORGEL_CNT	0x80		//ｵﾙｺﾞｰﾙ操作
#define	VOICEN_CNT	0x40		//音声0操作
#define	VOICEI_CNT	0x20		//音声I操作
#define	VOICEC_CNT	0x10		//音声C操作
#define	VOICES_CNT	0x08		//音声S操作
#define	NON_CNT		0x00		//操作無し


#ifdef SW_EN				//SWを実装するとき
//==============================================
//SW構成の定義
//==============================================
#define	SW_MODE	0x80			//ﾓｰﾄﾞ設定ﾏｽｸ
#define	SW_POL	0x40			//極性設定ﾏｽｸ
static const struct SW_CNF
{
	GPIO_TypeDef *gpio;		//GPIOｱﾄﾞﾚｽ
	unsigned char mode;			//b7:ﾓｰﾄﾞ(0=ﾘｱﾙﾓｰﾄﾞ､1=ﾀｲﾏｰﾓｰﾄﾞ)
						//b6:入力極性(0=負論理､1=正論理)
	unsigned char msk;		//ﾋﾞｯﾄﾏｽｸ
}sw_cnf[]=
{

//SW0の構成-------------------------------------
#ifdef SW0_BIT
#ifdef SW0_TIMER
#define SW0_MODE SW_MODE
#define SW_TIMER
#endif
#ifdef SW0_REAL
#define SW0_MODE 0x00
#define SW_REAL
#endif
#ifdef SW0_INV
#define SW0_POL 0x00
#else
#define SW0_POL SW_POL
#endif
	{SW0_GPIO,SW0_MODE|SW0_POL,1<<SW0_BIT},
#define SW0_EXTICH	(SW0_EXTI_PORT<<SW0_BIT*2)
#define SW0_EXTIMSK	(1<<SW0_BIT)
#else
#define SW0_EXTICH	0x0000
#define SW0_EXTIMSK	0x00
#endif

//SW1の構成-------------------------------------
#ifdef SW1_BIT
#ifdef SW1_TIMER
#define SW1_MODE SW_MODE
#define SW_TIMER
#endif
#ifdef SW1_REAL
#define SW1_MODE 0x00
#define SW_REAL
#endif
#ifdef SW1_INV
#define SW1_POL 0x00
#else
#define SW1_POL SW_POL
#endif
	{SW1_GPIO,SW1_MODE|SW1_POL,1<<SW1_BIT},
#define SW1_EXTICH	(SW1_EXTI_PORT<<SW1_BIT*2)
#define SW1_EXTIMSK	(1<<SW1_BIT)
#else
#define SW1_EXTICH	0x0000
#define SW1_EXTIMSK	0x00
#endif

//SW2の構成-------------------------------------
#ifdef SW2_BIT
#ifdef SW2_TIMER
#define SW2_MODE SW_MODE
#define SW_TIMER
#endif
#ifdef SW2_REAL
#define SW2_MODE 0x00
#define SW_REAL
#endif
#ifdef SW2_INV
#define SW2_POL 0x00
#else
#define SW2_POL SW_POL
#endif
	{SW2_GPIO,SW2_MODE|SW2_POL,1<<SW2_BIT},
#define SW2_EXTICH	(SW2_EXTI_PORT<<SW2_BIT*2)
#define SW2_EXTIMSK	(1<<SW2_BIT)
#else
#define SW2_EXTICH	0x0000
#define SW2_EXTIMSK	0x00
#endif

//SW3の構成-------------------------------------
#ifdef SW3_BIT
#ifdef SW3_TIMER
#define SW3_MODE SW_MODE
#define SW_TIMER
#endif
#ifdef SW3_REAL
#define SW3_MODE 0x00
#define SW_REAL
#endif
#ifdef SW3_INV
#define SW3_POL 0x00
#else
#define SW3_POL SW_POL
#endif
	{SW3_GPIO,SW3_MODE|SW3_POL,1<<SW3_BIT},
#define SW3_EXTICH	(SW3_EXTI_PORT<<SW3_BIT*2)
#define SW3_EXTIMSK	(1<<SW3_BIT)
#else
#define SW3_EXTICH	0x0000
#define SW3_EXTIMSK	0x00
#endif

//SW4の構成-------------------------------------
#ifdef SW4_BIT
#ifdef SW4_TIMER
#define SW4_MODE SW_MODE
#define SW_TIMER
#endif
#ifdef SW4_REAL
#define SW4_MODE 0x00
#define SW_REAL
#endif
#ifdef SW4_INV
#define SW4_POL 0x00
#else
#define SW4_POL SW_POL
#endif
	{SW4_GPIO,SW4_MODE|SW4_POL,1<<SW4_BIT},
#define SW4_EXTICH	(SW4_EXTI_PORT<<SW4_BIT*2)
#define SW4_EXTIMSK	(1<<SW4_BIT)
#else
#define SW4_EXTICH	0x0000
#define SW4_EXTIMSK	0x00
#endif

//SW5の構成-------------------------------------
#ifdef SW5_BIT
#ifdef SW5_TIMER
#define SW5_MODE SW_MODE
#define SW_TIMER
#endif
#ifdef SW5_REAL
#define SW5_MODE 0x00
#define SW_REAL
#endif
#ifdef SW5_INV
#define SW5_POL 0x00
#else
#define SW5_POL SW_POL
#endif
	{SW5_GPIO,SW5_MODE|SW5_POL,1<<SW5_BIT},
#define SW5_EXTICH	(SW5_EXTI_PORT<<SW5_BIT*2)
#define SW5_EXTIMSK	(1<<SW5_BIT)
#else
#define SW5_EXTICH	0x0000
#define SW5_EXTIMSK	0x00
#endif

//SW6の構成-------------------------------------
#ifdef SW6_BIT
#ifdef SW6_TIMER
#define SW6_MODE SW_MODE
#define SW_TIMER
#endif
#ifdef SW6_REAL
#define SW6_MODE 0x00
#define SW_REAL
#endif
#ifdef SW6_INV
#define SW6_POL 0x00
#else
#define SW6_POL SW_POL
#endif
	{SW6_GPIO,SW6_MODE|SW6_POL,1<<SW6_BIT},
#define SW6_EXTICH	(SW6_EXTI_PORT<<SW6_BIT*2)
#define SW6_EXTIMSK	(1<<SW6_BIT)
#else
#define SW6_EXTICH	0x0000
#define SW6_EXTIMSK	0x00
#endif

//SW7の構成-------------------------------------
#ifdef SW7_BIT
#ifdef SW7_TIMER
#define SW7_MODE SW_MODE
#define SW_TIMER
#endif
#ifdef SW7_REAL
#define SW7_MODE 0x00
#define SW_REAL
#endif
#ifdef SW7_INV
#define SW7_POL 0x00
#else
#define SW7_POL SW_POL
#endif
	{SW7_GPIO,SW7_MODE|SW7_POL,1<<SW7_BIT},
#define SW7_EXTICH	(SW7_EXTI_PORT<<SW7_BIT*2)
#define SW7_EXTIMSK	(1<<SW7_BIT)
#else
#define SW7_EXTICH	0x0000
#define SW7_EXTIMSK	0x00
#endif
};

//EXTI設定値
#define SW_EXTICH	(SW0_EXTICH|SW1_EXTICH|SW2_EXTICH|SW3_EXTICH|\
			SW4_EXTICH|SW5_EXTICH|SW6_EXTICH|SW7_EXTICH)
#define SW_EXTIMSK	(SW0_EXTIMSK|SW1_EXTIMSK|SW2_EXTIMSK|SW3_EXTIMSK|\
			SW4_EXTIMSK|SW5_EXTIMSK|SW6_EXTIMSK|SW7_EXTIMSK)

//SW数
#define	SW_SU	(sizeof(sw_cnf)/sizeof(sw_cnf[0]))
						//SWの実装数


//==============================================
//SW操作の定義
//==============================================
static const unsigned char sw_cnt[]=		//ｱﾌﾟﾘ制御情報
{

//SW0の操作-------------------------------------
#ifdef SW0_BIT
	SW0_CNT,
#endif

//SW1の操作-------------------------------------
#ifdef SW1_BIT
	SW1_CNT,
#endif

//SW2の操作-------------------------------------
#ifdef SW2_BIT
	SW2_CNT,
#endif

//SW3の操作-------------------------------------
#ifdef SW3_BIT
	SW3_CNT,
#endif

//SW4の操作-------------------------------------
#ifdef SW4_BIT
	SW4_CNT,
#endif

//SW5の操作-------------------------------------
#ifdef SW5_BIT
	SW5_CNT,
#endif

//SW6の操作-------------------------------------
#ifdef SW6_BIT
	SW6_CNT,
#endif

//SW7の操作-------------------------------------
#ifdef SW7_BIT
	SW7_CNT,
#endif
};

#include "func_SW.c"				//SW評価ﾓｼﾞｭｰﾙを呼込む
#endif


#ifdef CdS_EN				//CdSを実装するとき
//==============================================
//CdS構成の定義
//==============================================
#include "func_CdS.c"				//CdS評価ﾓｼﾞｭｰﾙを呼込む
#endif


#ifdef CVD_EN				//CVDを実装するとき
//==============================================
//CVD構成の定義
//==============================================
#define	CVD_MODE	0x80			//ﾓｰﾄﾞ設定ﾏｽｸ
static const struct CVD_CNF
{
	GPIO_TypeDef *gpio;			//GPIOｱﾄﾞﾚｽ
	unsigned long cfglr;			//CFGLRﾏｽｸ
	unsigned short msk;			//ﾋﾞｯﾄﾏｽｸ
	unsigned char an;			//b7:SWのﾓｰﾄﾞ(0=ﾘｱﾙﾓｰﾄﾞ､1=ﾀｲﾏｰﾓｰﾄﾞ)
						//b6-0:An番号
}cvd_cnf[]=
{

//CVD0の構成-------------------------------------
#ifdef CVD0_BIT
#ifdef CVD0_TIMER
#define CVD0_MODE CVD_MODE
#define CVD_TIMER
#endif
#ifdef CVD0_REAL
#define CVD0_MODE 0x00
#define CVD_REAL
#endif
	{CVD0_GPIO,0xf<<CVD0_BIT*4,1<<CVD0_BIT,CVD0_MODE|CVD0_An},
#endif

//CVD1の構成-------------------------------------
#ifdef CVD1_BIT
#ifdef CVD1_TIMER
#define CVD1_MODE CVD_MODE
#define CVD_TIMER
#endif
#ifdef CVD1_REAL
#define CVD1_MODE 0x00
#define CVD_REAL
#endif
	{CVD1_GPIO,0xf<<CVD1_BIT*4,1<<CVD1_BIT,CVD1_MODE|CVD1_An},
#endif

//CVD2の構成-------------------------------------
#ifdef CVD2_BIT
#ifdef CVD2_TIMER
#define CVD2_MODE CVD_MODE
#define CVD_TIMER
#endif
#ifdef CVD2_REAL
#define CVD2_MODE 0x00
#define CVD_REAL
#endif
	{CVD2_GPIO,0xf<<CVD2_BIT*4,1<<CVD2_BIT,CVD2_MODE|CVD2_An},
#endif

//CVD3の構成-------------------------------------
#ifdef CVD3_BIT
#ifdef CVD3_TIMER
#define CVD3_MODE CVD_MODE
#define CVD_TIMER
#endif
#ifdef CVD3_REAL
#define CVD3_MODE 0x00
#define CVD_REAL
#endif
	{CVD3_GPIO,0xf<<CVD3_BIT*4,1<<CVD3_BIT,CVD3_MODE|CVD3_An},
#endif

//CVD4の構成-------------------------------------
#ifdef CVD4_BIT
#ifdef CVD4_TIMER
#define CVD4_MODE CVD_MODE
#define CVD_TIMER
#endif
#ifdef CVD4_REAL
#define CVD4_MODE 0x00
#define CVD_REAL
#endif
	{CVD4_GPIO,0xf<<CVD4_BIT*4,1<<CVD4_BIT,CVD4_MODE|CVD4_An},
#endif

//CVD5の構成-------------------------------------
#ifdef CVD5_BIT
#ifdef CVD5_TIMER
#define CVD5_MODE CVD_MODE
#define CVD_TIMER
#endif
#ifdef CVD5_REAL
#define CVD5_MODE 0x00
#define CVD_REAL
#endif
	{CVD5_GPIO,0xf<<CVD5_BIT*4,1<<CVD5_BIT,CVD5_MODE|CVD5_An},
#endif
};

#define	CVD_SU	(sizeof(cvd_cnf)/sizeof(cvd_cnf[0]))
						//CVDの実装数


//==============================================
//CVD操作の定義
//==============================================
static const unsigned char cvd_cnt[]=		//ｱﾌﾟﾘ制御情報
{

//CVD0の操作-------------------------------------
#ifdef CVD0_BIT
	CVD0_CNT,
#endif

//CVD1の操作-------------------------------------
#ifdef CVD1_BIT
	CVD1_CNT,
#endif

//CVD2の操作-------------------------------------
#ifdef CVD2_BIT
	CVD2_CNT,
#endif

//CVD3の操作-------------------------------------
#ifdef CVD3_BIT
	CVD3_CNT,
#endif

//CVD4の操作-------------------------------------
#ifdef CVD4_BIT
	CVD4_CNT,
#endif

//CVD5の操作-------------------------------------
#ifdef CVD5_BIT
	CVD5_CNT,
#endif
};

#include "func_CVD.c"				//CVD評価ﾓｼﾞｭｰﾙを呼込む
#endif


//==============================================
//固有の作業域
//==============================================
#if defined(KYOKU_RAND)||defined(ONSEIN_RAND)||defined(ONSEII_RAND)||defined(ONSEIC_RAND)||defined(ONSEIS_RAND)	//どれかでﾗﾝﾀﾞﾑが必要なとき
static unsigned char rand_x;			//ﾗﾝﾀﾞﾏｲｽﾞの種
#endif
#if PART_N>0
static unsigned char kyoku;
#ifdef KYOKU_RAND
static unsigned char kyoku_rand_msk;
#endif
#endif
#if VOICE_N>0
static unsigned char onseiN;
#ifdef ONSEIN_RAND
static unsigned char onseiN_rand_msk;
#endif
#endif
#if VOICE_I>0
static unsigned char onseiI;
#ifdef ONSEII_RAND
static unsigned char onseiI_rand_msk;
#endif
#endif
#if VOICE_C>0
static unsigned char onseiC;
#ifdef ONSEIC_RAND
static unsigned char onseiC_rand_msk;
#endif
#endif
#if VOICE_S>0
static unsigned char onseiS;
#ifdef ONSEIS_RAND
static unsigned char onseiS_rand_msk;
#endif
#endif


#if defined(KYOKU_RAND)||defined(ONSEIN_RAND)||defined(ONSEII_RAND)||defined(ONSEIC_RAND)||defined(ONSEIS_RAND)	//どれかでﾗﾝﾀﾞﾑが必要なとき
//==============================================
//ﾗﾝﾀﾞﾏｲｽﾞのﾋﾞｯﾄﾏｽｸﾊﾟﾀｰﾝを計算する
//==============================================
static unsigned char rand_msk(
	unsigned char no)			//実装数
{
//DBG_C('\n');
//DBG_C('p');
//DBG_B(no);
	if(no>127) return(0xff);
	if(no>63) return(0x7f);
	if(no>31) return(0x3f);
	if(no>15) return(0x1f);
	if(no>7) return(0x0f);
	if(no>3) return(0x07);
	return(0x03);
}


//==============================================
//ﾗﾝﾀﾞﾏｲｽﾞ
//==============================================
static unsigned char rand(void)
{

//DBG_C('r');
	rand_x=(rand_x<<2)+rand_x+1;
//DBG_B(rand_x);
	return(rand_x);
}
#endif


//==============================================
//ｱﾌﾟﾘの初期設定
//==============================================
static void apl_init(void)
{

//DBG_C('\n');
//DBG_C('$');

	//ﾗﾝﾀﾞﾏｲｽﾞの種
#if defined(KYOKU_RAND)||defined(ONSEIN_RAND)||defined(ONSEII_RAND)||defined(ONSEIC_RAND)||defined(ONSEIS_RAND)	//どれかでﾗﾝﾀﾞﾑが必要なとき
//DBG_C('r');
	ADC1->RSQR3=RAND_An;			//ｼｰｹﾝｽ1を設定する
	ADC1->CTLR2|=ADC_ADON;			//変換開始
	while(!(ADC1->STATR&ADC_EOC));		//変換完了を待つ
	rand_x=ADC1->RDATAR;			//変換結果の下位8ﾋﾞｯﾄを種にする
#endif

	//ﾗﾝﾀﾞﾏｲｽﾞのﾋﾞｯﾄﾏｽｸﾊﾟﾀｰﾝ設定
#if (PART_N>0)&&defined(KYOKU_RAND)
	kyoku_rand_msk=rand_msk(song_idx->no);
//DBG_B(kyoku_rand_msk);
#endif
#if (VOICE_N>0)&&defined(ONSEIN_RAND)
	onseiN_rand_msk=rand_msk(VOICEN_SU);
//DBG_B(onseiN_rand_msk);
#endif
#if (VOICE_I>0)&&defined(ONSEII_RAND)
	onseiI_rand_msk=rand_msk(VOICEI_SU);
//DBG_B(onseiI_rand_msk);
#endif
#if (VOICE_C>0)&&defined(ONSEIC_RAND)
	onseiC_rand_msk=rand_msk(VOICEC_SU);
//DBG_B(onseiC_rand_msk);
#endif
#if (VOICE_S>0)&&defined(ONSEIS_RAND)
	onseiS_rand_msk=rand_msk(VOICES_SU);
//DBG_B(onseiS_rand_msk);
#endif

	//LEDﾎﾟｰﾄ設定
#ifdef LED0_BIT				//LED0を実装するとき
	GPIO_OUT(LED0_GPIO,LED0_BIT);		//出力ﾓｰﾄﾞ
#endif
#ifdef LED1_BIT				//LED1を実装するとき
	GPIO_OUT(LED1_GPIO,LED1_BIT);		//出力ﾓｰﾄﾞ
#endif
#ifdef LED2_BIT				//LED2を実装するとき
	GPIO_OUT(LED2_GPIO,LED2_BIT);		//出力ﾓｰﾄﾞ
#endif
#ifdef LED3_BIT				//LED3を実装するとき
	GPIO_OUT(LED3_GPIO,LED3_BIT);		//出力ﾓｰﾄﾞ
#endif
#ifdef LED4_BIT				//LED4を実装するとき
	GPIO_OUT(LED4_GPIO,LED5_BIT);		//出力ﾓｰﾄﾞ
#endif
#ifdef LED5_BIT				//LED5を実装するとき
	GPIO_OUT(LED5_GPIO,LED5_BIT);		//出力ﾓｰﾄﾞ
#endif
#ifdef LED6_BIT				//LED6を実装するとき
	GPIO_OUT(LED6_GPIO,LED6_BIT);		//出力ﾓｰﾄﾞ
#endif

	//SWﾎﾟｰﾄ設定
#ifdef SW_EN				//SWを実装するとき
#ifdef SW0_BIT				//SW0を実装するとき
#ifdef SW0_INV				//負論理のとき
	GPIO_INPU(SW0_GPIO,SW0_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙｱｯﾌﾟ
#else					//正論理のとき
	GPIO_INPD(SW0_GPIO,SW0_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙﾀﾞｳﾝ
#endif
#endif
#ifdef SW1_BIT				//SW1を実装するとき
#ifdef SW1_INV				//負論理のとき
	GPIO_INPU(SW1_GPIO,SW1_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙｱｯﾌﾟ
#else					//正論理のとき
	GPIO_INPD(SW1_GPIO,SW1_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙﾀﾞｳﾝ
#endif
#endif
#ifdef SW2_BIT				//SW2を実装するとき
#ifdef SW2_INV				//負論理のとき
	GPIO_INPU(SW2_GPIO,SW2_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙｱｯﾌﾟ
#else					//正論理のとき
	GPIO_INPD(SW2_GPIO,SW2_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙﾀﾞｳﾝ
#endif
#endif
#ifdef SW3_BIT				//SW3を実装するとき
#ifdef SW3_INV				//負論理のとき
	GPIO_INPU(SW3_GPIO,SW3_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙｱｯﾌﾟ
#else					//正論理のとき
	GPIO_INPD(SW3_GPIO,SW3_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙﾀﾞｳﾝ
#endif
#endif
#ifdef SW4_BIT				//SW4を実装するとき
#ifdef SW4_INV				//負論理のとき
	GPIO_INPU(SW4_GPIO,SW4_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙｱｯﾌﾟ
#else					//正論理のとき
	GPIO_INPD(SW4_GPIO,SW4_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙﾀﾞｳﾝ
#endif
#endif
#ifdef SW5_BIT				//SW5を実装するとき
#ifdef SW5_INV				//負論理のとき
	GPIO_INPU(SW5_GPIO,SW5_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙｱｯﾌﾟ
#else					//正論理のとき
	GPIO_INPD(SW5_GPIO,SW5_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙﾀﾞｳﾝ
#endif
#endif
#ifdef SW6_BIT				//SW6を実装するとき
#ifdef SW6_INV				//負論理のとき
	GPIO_INPU(SW6_GPIO,SW6_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙｱｯﾌﾟ
#else					//正論理のとき
	GPIO_INPD(SW6_GPIO,SW6_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙﾀﾞｳﾝ
#endif
#endif
#ifdef SW7_BIT				//SW7を実装するとき
#ifdef SW7_INV				//負論理のとき
	GPIO_INPU(SW7_GPIO,SW7_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙｱｯﾌﾟ
#else					//正論理のとき
	GPIO_INPD(SW7_GPIO,SW7_BIT);		//入力ﾓｰﾄﾞﾌﾟﾙﾀﾞｳﾝ
#endif
#endif
#endif

	//CdSﾎﾟｰﾄ設定
#ifdef CdS_EN				//CdSを実装するとき
	GPIO_IN(CdS_GPIO,CdS_BIT);		//入力ﾓｰﾄﾞ
#endif

	//KB演奏の初期設定
	//KB演奏で使う音源波形とｴﾝﾍﾞﾛｰﾌﾟ波形はmain.cで宣言しておくこと
//DBG_C('k');
	KB_START(0,&wave_SIN14,&enve_EXP,0);
DBG_C('\n');
}


#ifdef	SLEEP_EN			//Sleep機能を実装するとき
//==============================================
//Sleep処理
//==============================================
static void apl_sleep(void)
{
#if defined(CdS_EN)||defined(CVD_EN)||defined(SW_PLNG)
					//CdSかCVDを実装するとき､
					//　SWをﾎﾟｰﾘﾝｸﾞするとき
	unsigned char n;
#endif

//DBG_C('\n');
//DBG_C('<');
	//LED消灯
#ifdef LED0_BIT				//LED0を実装するとき
	GPIO_L(LED0_GPIO,LED0_BIT);		//消灯する
#endif
#ifdef LED1_BIT				//LED1を実装するとき
	GPIO_L(LED1_GPIO,LED1_BIT);		//消灯する
#endif
#ifdef LED2_BIT				//LED2を実装するとき
	GPIO_L(LED2_GPIO,LED2_BIT);		//消灯する
#endif
#ifdef LED3_BIT				//LED3を実装するとき
	GPIO_L(LED3_GPIO,LED3_BIT);		//消灯する
#endif
#ifdef LED4_BIT				//LED4を実装するとき
	GPIO_L(LED4_GPIO,LED4_BIT);		//消灯する
#endif
#ifdef LED5_BIT				//LED5を実装するとき
	GPIO_L(LED5,GPIO,LED5_BIT);		//消灯する
#endif
#ifdef LED6_BIT				//LED6を実装するとき
	GPIO_L(LED6_GPIO,LED6_BIT);		//消灯する
#endif

#if VOICE_S>0				//音声S再生を実装するとき
	//W25をﾊﾟﾜｰﾀﾞｳﾝ
//DBG_C('a');
	W25_PWR_DOWN();				//W25をﾊﾟﾜｰﾀﾞｳﾝする
#endif

	//SPIをﾘｾｯﾄ
#if VOICE_C+VOICE_S>0			//SPIを使うとき
//DBG_C('b');
	spi_reset();				//SPIﾎﾟｰﾄをﾘｾｯﾄする
#endif

	//PWMを停止
//DBG_C('c');
	dev_pwm_stop();				//PWMを停止する

	//Sleep処理
#if defined(CdS_EN)||defined(CVD_EN)||defined(SW_PLNG)
					//CdSかCVDを実装するとき､
					//　SWをﾎﾟｰﾘﾝｸﾞするときは
					//　AWUでWakeupする
	for(;;)
	{
		//SLEEPDEEPﾓｰﾄﾞへ移行
//DBG_C('d');
//DBG_SYNC();
//DBS_H;
		if(ADC1->CTLR2&ADC_ADON)	//ADCが有効だったら
		{
			ADC1->CTLR2=0x00000000;	//ADC無効
		}
		PWR->AWUCSR&=~0x00000002;	//AWUENをﾘｾｯﾄ
		PWR->AWUCSR|=0x00000002;	//AWUENをｾｯﾄ
		PWR->CTLR|=0x00000002;		//PDDSをｾｯﾄ
		NVIC->SCTLR|=0x04;		//SLEEPDEEPをｾｯﾄ
		__WFE();			//StandbyModeへ移行する
		SystemInit();			//ｼｽﾃﾑｸﾛｯｸを回復する

		//ADC設定
#if defined(CdS_EN)||defined(CVD_EN)	//CdSかCVDを実装するとき
		ADC1->CTLR2=ADC_ADON|ADC_SWSTART;	//ADC有効､ｿﾌﾄﾄﾘｶﾞでruleﾁｬﾈﾙ変換
		while(!(ADC1->CTLR2&ADC_ADON));		//ADC有効を待つ
#endif
//DBS_L;
//DBG_C('e');

#ifdef SW_EN				//SWを実装するとき
		//SWを評価する
//DBG_C('f');
		for(n=0;n<SW_SU;n++)
		{
			if(sw_read(n,1)) break;	//操作を検知したら抜ける
		}
		if(n<SW_SU) break;
#endif

#ifdef CdS_EN				//CdSを実装するとき
		//CdSを評価する
//DBG_C('g');
		if(cds_read(1)) break;		//操作を検知したら抜ける
#endif

#ifdef CVD_EN				//CVDを実装するとき
		//CVDを評価する
//DBG_C('h');
		for(n=0;n<CVD_SU;n++)
		{
			if(cvd_read(n,1)) break;//操作を検知したら抜ける
		}
		if(n<CVD_SU) break;
#endif
	}

#else					//CdSもCVDも実装しないとき､
					//　SWのｲﾍﾞﾝﾄでWakeupするときは
					//　ﾋﾟﾝｲﾍﾞﾝﾄでWakeupする
	//ﾋﾟﾝｲﾍﾞﾝﾄ設定
#ifdef SW_EN				//SWを実装するとき
//DBG_C('\n');
//DBG_C('i');
	AFIO->EXTICR=SW_EXTICH;			//EXTIﾎﾟｰﾄ指定
//DBG_L(AFIO->EXTICR);
	EXTI->RTENR=SW_EXTIMSK;			//EXTI立上り許可設定
//DBG_C('-');
//DBG_L(EXTI->RTENR);
	EXTI->FTENR=SW_EXTIMSK;			//EXTI立下り許可設定
//DBG_C('-');
//DBG_L(EXTI->FTENR);
	EXTI->EVENR=SW_EXTIMSK;			//EXTI許可設定
//DBG_C('-');
//DBG_L(EXTI->EVENR);
#endif

	//SLEEPDEEPﾓｰﾄﾞへ移行
//DBG_C('j');
//DBG_SYNC();
	if(ADC1->CTLR2&ADC_ADON)	//ADCが有効だったら
	{
		ADC1->CTLR2=0x00000000;	//ADC無効
	}
	PWR->CTLR|=0x00000002;			//PDDSをｾｯﾄ
	NVIC->SCTLR|=0x04;			//SLEEPDEEPをｾｯﾄ
	__WFE();				//StandbyModeへ移行する
	SystemInit();				//ｼｽﾃﾑｸﾛｯｸを回復する

	//ADC設定
#if defined(CdS_EN)||defined(CVD_EN)	//CdSかCVDを実装するとき
	ADC1->CTLR2=ADC_ADON|ADC_SWSTART;	//ADC有効､ｿﾌﾄﾄﾘｶﾞでruleﾁｬﾈﾙ変換
	while(!(ADC1->CTLR2&ADC_ADON));		//ADC有効を待つ
#endif
//DBG_C('k');

	//ﾋﾟﾝｲﾍﾞﾝﾄ解除
//DBG_C('l');
	EXTI->EVENR=0x00000000;			//EXTI禁止設定
#endif

	//PWMを再稼働
//DBG_C('m');
	dev_pwm_start();			//PWMを開始する

	//SPIをｾｯﾄ
#if VOICE_C+VOICE_S>0			//SPIを使うとき
//DBG_C('n');
	spi_set();				//SPIﾎﾟｰﾄをｾｯﾄする
#endif

	//SDを初期化
#if VOICE_C>0				//音声C再生を実装するとき
//DBG_C('o');
	mmsd_init();				//SDCを初期化する
#endif

	//W25をﾊﾟﾜｰｱｯﾌﾟ
#if VOICE_S>0				//音声S再生を実装するとき
//DBG_C('p');
	W25_PWR_UP();				//W25をﾊﾟﾜｰｱｯﾌﾟする
#endif
//DBG_C('>');
}
#endif


//==============================================
//固有の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_KOYUU(void)
{
#ifdef SLEEP_EN				//Sleep機能を実装するとき
	static unsigned short sleep_tmr=0;	//Sleepﾀｲﾏｰ
#endif
	unsigned char res;
	unsigned short onpu;

//DBG_C('a');

	//稼働ﾁｪｯｸ
#ifdef SLEEP_EN				//Sleep機能を実装するとき
//DBG_C('e');
	res=0;					//仮に非稼働にしておく
#if PART_N>0				//ｵﾙｺﾞｰﾙ演奏を実装するとき
	res|=song.no;				//稼働しているときは稼働中の設定
#endif
#if VOICE_N>0				//音声N再生を実装するとき
	res|=voiceN[0].no;			//稼働しているときは稼働中の設定
#endif
#if VOICE_I>0				//音声I再生を実装するとき
	res|=voiceI.no;				//稼働しているときは稼働中の設定
#endif
#if VOICE_C>0				//音声C再生を実装するとき
	res|=voiceC.no;				//稼働しているときは稼働中の設定
#endif
#if VOICE_S>0				//音声S再生を実装するとき
	res|=voiceS[0].no;			//稼働しているときは稼働中の設定
#endif
//DBG_B(res);
	if(res)					//稼働しているときは
	{
		sleep_tmr=0;			//　Sleep時限をｸﾘｱする
	}
	else					//稼働していないときは
	{
//DBG_C('X');
//DBG_S(sleep_tmr);
		if(++sleep_tmr>SLEEP_TMR/KOYUU_PR)
						//　Sleep時限を超えたら
		{
			apl_sleep();		//　Sleepする
			sleep_tmr=0;		//　Sleep時限をｸﾘｱする
		}
	}
#endif

	//KB演奏
	res=DBG_IN();				//動作指示を受信する
	if(('0'<=res)&&(res<='9'))		//'0'～'9'のとき
	{
DBG_C('o');
DBG_S(res-'0');
		SONG_SEL(res-'0');		//ｵﾙｺﾞｰﾙ演奏の曲選択
DBG_C('\n');
	}
	else if(('a'<=res)&&(res<='g'))		//'a'～'g'のとき
	{
DBG_C('k');
		switch(res-'a')
		{
		case 0:				//ﾗ
			onpu=0x0815;
			break;
		case 1:				//ｼ
			onpu=0x0817;
			break;
		case 2:				//ﾄﾞ
			onpu=0x0818;
			break;
		case 3:				//ﾚ
			onpu=0x081a;
			break;
		case 4:				//ﾐ
			onpu=0x081c;
			break;
		case 5:				//ﾌｧ
			onpu=0x081d;
			break;
		case 6:				//ｿ
			onpu=0x081f;
			break;
		}
		KB_ONPU(0,onpu);		//KB演奏の音符設定
DBG_S(onpu);
DBG_C('\n');
	}
	else if(('A'<=res)&&(res<='G'))		//'A'～'G'のとき
	{
DBG_C('k');
		switch(res-'A')
		{
		case 0:				//ﾗ
			onpu=0x0821;
			break;
		case 1:				//ｼ
			onpu=0x0823;
			break;
		case 2:				//ﾄﾞ
			onpu=0x0824;
			break;
		case 3:				//ﾚ
			onpu=0x0826;
			break;
		case 4:				//ﾐ
			onpu=0x0828;
			break;
		case 5:				//ﾌｧ
			onpu=0x0829;
			break;
		case 6:				//ｿ
			onpu=0x082b;
			break;
		}
		KB_ONPU(0,onpu);		//KB演奏の音符設定
DBG_S(onpu);
DBG_C('\n');
	}
	else if(res==' ')
	{
DBG_C('s');
		KB_ONPU(0,0);			//KB演奏の音符終了
DBG_C('\n');
	}
}


#if	PART_N>0			//ｵﾙｺﾞｰﾙ演奏を実装するとき
//==============================================
//演奏終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_SONG_END(void)
{
}
#endif


#if	VOICE_N>0			//音声N再生を実装するとき
//==============================================
//音声0再生終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_VOICEN_END(
	unsigned char ch)			//音声Nのch番号
{
}
#endif


#if	VOICE_I>0			//音声I再生を実装するとき
//==============================================
//音声I再生終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_VOICEI_END(void)
{
}
#endif


#if	VOICE_C>0			//音声C再生を実装するとき
//==============================================
//音声C再生終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_VOICEC_END(void)
{
}
#endif


#if	VOICE_S>0			//音声S再生を実装するとき
//==============================================
//音声S再生終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_VOICES_END(
	unsigned char ch)			//音声Sのch番号
{
}
#endif
