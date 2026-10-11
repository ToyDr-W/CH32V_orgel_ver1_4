//==============================================
//構成情報(ｵﾙｺﾞｰﾙ演奏+音声再生処理に関わるもの)
//==============================================
#define	SYS_CLK		48			//ｼｽﾃﾑｸﾛｯｸ周波数[MHz]
#define	BTL 		0			//BTL出力指定
						//　0=ｼﾝｸﾞﾙ出力
						//　1=ｺﾝﾌﾟﾘ出力
						//　2=ﾌﾞﾘｯｼﾞ出力
						//　3=ﾌﾞﾚｰｷ出力
#define	PWM_STEP	1024
#define	PWM_FRQ		(SYS_CLK*1000/PWM_STEP)	//PWM周波数=46.875[kHz]
#define	PWM_PR		(PWM_STEP/SYS_CLK)	//PWM周期=21.333[us]
#define	PWM_DB_CMP	0x10			//PWMﾃﾞｯﾄﾞﾊﾞﾝﾄﾞ(ｺﾝﾌﾟﾘ出力時)[PWMｽﾃｯﾌﾟ]
#define	PWM_DB_BRG	10			//PWMﾃﾞｯﾄﾞﾊﾞﾝﾄﾞ(ﾌﾞﾘｯｼﾞ出力時)[PWMｽﾃｯﾌﾟ]
#define	OUT_BUF_N	50			//出力ﾊﾞｯﾌｧｻｲｽﾞ
#define	SPI_BUF_N	8			//SPIﾊﾞｯﾌｧｻｲｽﾞ
#define	SONG_PS		2			//演奏処理ﾌﾟﾘｽｹｰﾙ値
						//　演奏処理周期=PWM_PR*SONG_PS
#define	KOYUU_PR	32			//固有処理のｺｰﾙﾊﾞｯｸ周期[ms]
#define	VOICEN0_VOL	100			//音声N0のﾎﾞﾘｭｰﾑ配分[%]
#define	VOICEN1_VOL	100			//音声N1のﾎﾞﾘｭｰﾑ配分[%]
#define	VOICEN2_VOL	100			//音声N2のﾎﾞﾘｭｰﾑ配分[%]
#define	VOICEI_VOL	100			//音声Iのﾎﾞﾘｭｰﾑ配分[%]
#define	VOICEC_VOL	100			//音声Cのﾎﾞﾘｭｰﾑ配分[%]
#define	VOICES0_VOL	100			//音声S0のﾎﾞﾘｭｰﾑ配分[%]
#define	VOICES1_VOL	100			//音声S1のﾎﾞﾘｭｰﾑ配分[%]
#define	VOICES2_VOL	100			//音声S2のﾎﾞﾘｭｰﾑ配分[%]
#define	ORGEL_VOL	100			//ｵﾙｺﾞｰﾙ演奏のﾎﾞﾘｭｰﾑ配分[%]
#define	VOICE_N		0			//音声N発声数の最大値(最大値3､
						//　0のときは音声再生機能を実装しない)
#define	VOICE_I		0			//音声I発声数の最大値(最大値1､
						//　0のときは音声再生機能を実装しない)
#define	VOICE_C		0			//音声C発声数の最大値(最大値1､
						//　(0のときは音声再生機能を実装しない)
#define	VOICE_S		0			//音声S発声数の最大値(
						//　0のときは音声再生機能を実装しない)
#define	PART_N		4			//演奏ﾊﾟｰﾄ数の最大値(最大値4､
						//　0のときはｵﾙｺﾞｰﾙ演奏機能を実装しない)
#define	KB_N		0			//KB演奏有効ﾊﾟｰﾄ数の最大値
						//　(0のときはKB演奏機能を実装しない)
