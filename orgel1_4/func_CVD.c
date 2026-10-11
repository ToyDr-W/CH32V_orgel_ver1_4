//CVDを評価する機能ﾓｼﾞｭｰﾙ
//
//CVDの構成を下記の例に倣って､呼出し元にて定義しておくこと｡
//
//CVDは複数個を実装可能｡CVD毎にﾎﾟｰﾄﾚｼﾞｽﾀが違ってもよい｡
//
//CVDのｵﾝとは､ﾀｯﾁした状態｡
//CVDのｵﾌとは､ﾀｯﾁしない状態｡
//
//CVDの評価は以下の2つのﾓｰﾄﾞがある｡
//・ﾘｱﾙﾓｰﾄﾞ
//　規定期間内のﾊﾞﾀﾂｷは無視する｡
//　状態が変化したときに変化の状況を返す｡
//　戻り値は､0=変化の検知なし､1=ｵﾌからｵﾝへの変化を検知､2=ｵﾝからｵﾌへの変化を検知｡
//・ﾀｲﾏｰﾓｰﾄﾞ
//　ｵﾝの継続時間が短ｵﾝ閾値になったら短ｵﾝ一致とする｡
//　ｵﾝの継続時間が長ｵﾝ閾値になったら長ｵﾝ一致とする｡
//　ｵﾝからｵﾌへ変化したときに､ｵﾝ状態であった時間が短ｵﾝ閾値超えのときは短ｵﾝ検知とする｡
//　戻り値は､0=検知なし､1=短ｵﾝ検知､2=長ｵﾝ一致､3=短ｵﾝ一致｡
//ﾘｱﾙﾓｰﾄﾞとﾀｲﾏｰﾓｰﾄﾞは排他的で､1つのCVDに対してどちらか1つのﾓｰﾄﾞを指定できる｡
//
//CVDを評価する場合は､このﾓｼﾞｭｰﾙを#includeする｡
//ﾘｱﾙﾓｰﾄﾞで評価するときは､CVD_REALを宣言する｡
//ﾀｲﾏｰﾓｰﾄﾞで評価するときは､CVD_TIMERを宣言する｡
//Sleep関連の処理にこのﾓｼﾞｭｰﾙは関与しない｡


//==============================================
//CVD構成の定義例
//==============================================
//#define	CVD_REAL			//CVDﾘｱﾙﾓｰﾄﾞを実装するときに宣言する
//#define	CVD_TIMER			//CVDﾀｲﾏｰﾓｰﾄﾞを実装するときに宣言する

//CVDの構成--------------------------------------
//static const struct CVD_CNF
//{
//	GPIO_TypeDef *gpio;			//GPIOｱﾄﾞﾚｽ
//	unsigned long cfglr;			//CFGLRﾏｽｸ
//	unsigned short msk;			//ﾋﾞｯﾄﾏｽｸ
//	unsigned char an;			//b7:SWのﾓｰﾄﾞ(0=ﾘｱﾙﾓｰﾄﾞ､1=ﾀｲﾏｰﾓｰﾄﾞ)
//						//b6-0:An番号
//} cvd_cnf[]=
//{
//CVD0の構成-------------------------------------
//	{CVD0_PORT,0xf<<CVD0_BIT*4,1<<CVD0_BIT,CVD0_MODE|CVD0_An},
//CVD1の構成-------------------------------------
//	{CVD1_PORT,0xf<<CVD1_BIT*4,1<<CVD1_BIT,CVD1_MODE|CVD1_An},
//CVD2の構成-------------------------------------
//	{CVD2_PORT,0xf<<CVD2_BIT*4,1<<CVD2_BIT,CVD2_MODE|CVD2_An},
//CVD3の構成-------------------------------------
//	{CVD3_PORT,0xf<<CVD3_BIT*4,1<<CVD3_BIT,CVD3_MODE|CVD3_An},
//};


//==============================================
//CVD評価の閾値等
//==============================================
#ifndef	CVD_CNT				//評価の回数が宣言されていないとき
#define	CVD_CNT		8			//　評価の回数を宣言する
#endif
#ifndef	CVD_THR1			//評価の閾値1が宣言されていないとき
#define	CVD_THR1	15			//　閾値1を宣言する
#endif
#ifndef	CVD_THR2			//評価の閾値2が宣言されていないとき
#define	CVD_THR2	30			//　閾値2を宣言する
#endif
#ifndef	CVD_INC				//移動平均計算の増分値が宣言されていないとき
#define	CVD_INC		2			//　増分値を宣言する
#endif

//ﾘｱﾙﾓｰﾄﾞの設定値
#ifndef	CVD_HST_BIT			//ﾊﾞﾀﾂｷ除去期間[評価周期](1～7の範囲)が
					//　宣言されていないとき
#define	CVD_HST_BIT	3			//　ﾊﾞﾀﾂｷ除去期間を宣言する
#endif
#define	CVD_HST_MSK	((1<<(CVD_HST_BIT+1))-1)//履歴判定ﾋﾞｯﾄﾏｽｸ
#define	CVD_HST_ON	((1<<CVD_HST_BIT)-1)	//履歴ｵﾝ変化判定値
#define	CVD_HST_OFF	((1<<(CVD_HST_BIT+1))-2)//履歴ｵﾌ変化判定値

//ﾀｲﾏｰﾓｰﾄﾞの設定値
#ifndef	CVD_SHORT			//短ｵﾝ時間閾値[ms]が宣言されていないとき
#define	CVD_SHORT	200			//ﾃﾞﾌｫﾙﾄ値[ms]を設定する
#endif
#ifndef	CVD_LONG			//長ｵﾝ時間閾値[ms]が宣言されていないとき
#define	CVD_LONG	1000			//ﾃﾞﾌｫﾙﾄ値[ms]を設定する
#endif


//==============================================
//作業域
//==============================================
static struct HIST				//履歴情報
{
	unsigned char cvd_hst;			//CVDの検査履歴(記録)
						//ﾘｱﾙﾓｰﾄﾞではｵﾝ/ｵﾌ状態履歴(0=ｵﾌ､1=ｵﾝ)
						//　b0が最新状態で評価周期毎に左ｼﾌﾄ
						//ﾀｲﾏｰﾓｰﾄﾞではｵﾝ状態経過時間[評価周期]
	unsigned short cvd_ave;			//ADC移動平均(記録)
}cvd_hist[CVD_SU];


//==============================================
//CVDを評価する
//ﾊﾟﾗﾒｰﾀ
//　評価対象のCVD番号[0起算]
//　稼働状態(0=通常稼働中､1=Sleep中)
//戻り値
//　ﾘｱﾙﾓｰﾄﾞのとき W:評価結果(0=変化なし､1=ｵﾌからｵﾝへ変化検知､2=ｵﾝからｵﾌへ変化検知)
//　ﾀｲﾏｰﾓｰﾄﾞのとき W:評価結果(0=検知なし､1=短ｵﾝ検知､2=長ｵﾝ一致､3=短ｵﾝ一致)
//Sleep中の検査のときは､操作を検知しても履歴を保持する
//==============================================
unsigned char cvd_read(				//ﾀｯﾁ評価結果を返す
	unsigned char no,			//評価対象のCVD番号(0起算)
	unsigned char sleep)			//Sleep中の検査のときは1を指定する
{
	static unsigned char init_tmr;		//CVD安定ﾀｲﾏｰ
	unsigned short value;			//CVDのADC値
	unsigned char res;			//CVD評価戻り値
	const struct CVD_CNF *p;		//CVD構成表へのﾎﾟｲﾝﾀ
	struct HIST *q;				//履歴情報へのﾎﾟｲﾝ
	unsigned char n;


//DBG_C('\n');
//DBG_C('v');
//DBG_B(no);
//DBG_B(sleep);
	//構成表へのﾎﾟｲﾝﾀを設定
	if(no>=CVD_SU) return(0);
	p=cvd_cnf+no;
//DBG_L(p);
//DBG_D(p,12);

	//履歴情報へのﾎﾟｲﾝﾀ
	q=cvd_hist+no;
//DBG_L(q);
//DBG_D(q,4);

	//CVDのADC
	ADC1->RSQR3=p->an&0x7f;			//ｼｰｹﾝｽ1を設定
	value=0;
	p->gpio->BCR=p->msk;			//ﾎﾟｰﾄをL
	p->gpio->CFGLR|=0x11111111&p->cfglr;	//ﾎﾟｰﾄを出力
	for(n=0;n<CVD_CNT;n++)
	{
DBS_H;
DBG_C('\n');
DBG_B(no);
DBG_B(n);
		__disable_irq();		//割込み禁止
		p->gpio->CFGLR&=~p->cfglr;	//ﾎﾟｰﾄをｱﾅﾛｸﾞ入力
		p->gpio->CFGLR|=0x88888888&p->cfglr;
						//ﾎﾟｰﾄをﾌﾟﾙｱｯﾌﾟ入力
		p->gpio->BSHR=p->msk;		//ﾎﾟｰﾄをﾌﾟﾙｱｯﾌﾟ
		p->gpio->BSHR=p->msk;		//ﾎﾟｰﾄをﾌﾟﾙｱｯﾌﾟ(時間稼ぎ)
		p->gpio->BSHR=p->msk;		//ﾎﾟｰﾄをﾌﾟﾙｱｯﾌﾟ(時間稼ぎ)
		p->gpio->CFGLR&=~p->cfglr;	//ﾎﾟｰﾄをｱﾅﾛｸﾞ入力
DBS_L;
		ADC1->CTLR2|=ADC_ADON;		//変換開始
		__enable_irq();			//割込み許可
		while(!(ADC1->STATR&ADC_EOC));	//変換完了を待つ
		p->gpio->BCR=p->msk;		//ﾎﾟｰﾄをL
		p->gpio->CFGLR|=0x11111111&p->cfglr;
						//ﾎﾟｰﾄを出力
DBG_C('+');
DBG_S(ADC1->RDATAR);
		value+=1024-ADC1->RDATAR;	//変換結果を取込む
	}
DBG_C('=');
DBG_S(value);

	//定常動作待ち
	if(init_tmr<8)				//CVD安定ﾀｲﾏｰが未満了のときは
	{
		init_tmr++;			//CVD安定ﾀｲﾏｰをｲﾝｸﾘする
		return(0);			//何もせず戻る
	}

	//移動平均(簡易計算)
	if(q->cvd_ave)				//定常動作のとき
	{
		if(value>q->cvd_ave) q->cvd_ave+=CVD_INC;
						//ADC結果が移動平均を超えたら
						//　移動平均を増加させる
		else q->cvd_ave=value;		//超えてなければ
						//　ADC結果を移動平均とする
	}
	else					//初回動作のとき
	{
		q->cvd_ave=value;		//移動平均を初期化する
	}
//DBG_C('-');
//DBG_S(q->cvd_ave);

	//ﾀｲﾏｰﾓｰﾄﾞの処理
	if(p->an&CVD_MODE)			//ﾀｲﾏｰﾓｰﾄﾞのとき
	{
#ifdef CVD_TIMER			//ﾀｲﾏｰﾓｰﾄﾞを実装するとき
//DBG_C('t');

		//ｶﾚﾝﾄ値を判定
//DBG_B(q->cvd_hst);
		res=0;				//仮にｵﾌ判定にしておく
		if(q->cvd_hst)			//前回がｵﾝ判定だったとき
		{
			if(value>q->cvd_ave+CVD_THR1*CVD_CNT) res=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値1)のときｵﾝ判定
		}
		else				//前回がｵﾌ判定だったとき
		{
			if(value>q->cvd_ave+CVD_THR2*CVD_CNT) res=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値2)のときｵﾝ判定
		}
//DBG_B(res);

		//履歴を評価
		if(res)				//ｵﾝ判定のとき
		{
//DBG_C('+');
			if((++(q->cvd_hst)==0)) q->cvd_hst--;
						//ｵﾝ継続時間をｲﾝｸﾘして
						//　ｵｰﾊﾞﾌﾛｰしたら戻す
//DBG_B(q->cvd_hst);
			if(q->cvd_hst==CVD_LONG/KOYUU_PR)
						//長ｵﾝ閾値に一致したら
			{
				res=2;		//　｢2｣を返す
				if(sleep) q->cvd_hst--;
						//　Sleep中は履歴を巻戻す
			}
			else if(q->cvd_hst==CVD_SHORT/KOYUU_PR)
						//短ｵﾝ閾値に一致したら
			{
				res=3;		//　｢3｣を返す
				if(sleep) q->cvd_hst--;
						//　Sleep中は履歴を巻戻す
			}
			else res=0;		//その他は｢0｣を返す
		}
		else				//ｵﾌ判定のとき
		{
//DBG_C('-');
//DBG_B(q->cvd_hst);
			if(q->cvd_hst>CVD_LONG/KOYUU_PR) res=0;
						//長ｵﾝ閾値を超えていたら｢0｣を返す
			else if(q->cvd_hst>CVD_SHORT/KOYUU_PR) res=1;
						//短ｵﾝ閾値を超えていたら｢1｣を返す
			else res=0;		//その他は｢0｣を返す
			if(!sleep||!res) q->cvd_hst=0;
						//稼働中か検知無しのときは履歴をｸﾘｱする
		}

//DBG_B(res);
#else					//ﾀｲﾏｰﾓｰﾄﾞを実装しないとき
		return(0);
#endif
	}

	//ﾘｱﾙﾓｰﾄﾞの処理
	else
	{
#ifdef CVD_REAL				//ﾘｱﾙﾓｰﾄﾞを実装するとき
//DBG_C('r');
		q->cvd_hst<<=1;			//履歴をｼﾌﾄしておく
//DBG_B(q->cvd_hst);
//DBG_B(value);
		if(q->cvd_hst&0x02)		//前回がｵﾝ判定だったとき
		{
			if(value>(short)q->cvd_ave+CVD_THR1*CVD_CNT) q->cvd_hst|=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値1)のときｵﾝ判定
		}
		else				//前回がｵﾌ判定だったとき
		{
			if(value>(short)q->cvd_ave+CVD_THR2*CVD_CNT) q->cvd_hst|=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値1)のときｵﾝ判定
		}
//DBG_B(q->cvd_hst);
		switch(q->cvd_hst&CVD_HST_MSK)	//履歴で判定する
		{
		case CVD_HST_ON:		//ｵﾝ判定ﾊﾟﾀｰﾝのときは
			res=1;			//　｢1｣を返す
			break;
		case CVD_HST_OFF:		//ｵﾌ判定ﾊﾟﾀｰﾝのときは
			res=2;			//　｢2｣を返す
			break;
		default:
			res=0;			//その他は｢0｣を返す
		}
//DBG_B(res);
		if(res&&sleep) q->cvd_hst>>=1;	//Sleep中に操作を検知したら履歴を巻戻す
#else					//ﾘｱﾙﾓｰﾄﾞを実装しないとき
		return(0);
#endif
	}

//DBG_B(res);
	return(res);				//評価結果を返す
}
