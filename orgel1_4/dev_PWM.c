//==============================================
//PWM周期割込み処理
//==============================================
void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_UP_IRQHandler(void)
{
	short pcm;				//PCM値

//DBS_H;					//割込み処理開始を表示する
	TIM1->INTFR=0;				//全ｲﾍﾞﾝﾄをｸﾘｱする

	//PCM値を取得
	if(buf_read==buf_write) return;		//ﾃﾞｰﾀが無かったら飛ばす
	pcm=buf[buf_read];			//PCM値を取出す
	if(buf_read==(OUT_BUF_N-1)) buf_read=0;	//ﾊﾞｯﾌｧの後尾になったら先頭に戻す
	else buf_read++;			//ﾊﾞｯﾌｧを進める

	//ﾃﾞｭｰﾃｨｻｲｸﾙを設定
#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
	TIM1->CH3CVR=((long)pcm+32768)*PWM_STEP/65536;
						//正相を設定する
#endif
#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
	TIM1->CH1CVR=((long)pcm+32768)*PWM_STEP/65536;
						//正相･逆相を設定する
#endif
#if BTL>1				//ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
	if(pcm>0)				//正値のとき
	{
		TIM1->CH4CVR=0;			//逆相を止める
		TIM1->CH3CVR=(long)pcm*PWM_STEP/32768;
						//正相を設定する
	}
	else if(pcm<0)				/負値のとき
	{
		TIM1->CH3CVR=0;			//正相を止める
		TIM1->CH4CVR=(long)(-pcm)*PWM_STEP/32768;
						//逆相を設定する
	}
	else					//停止のとき
	{
		TIM1->CH3CVR=0;			//正相を止める
		TIM1->CH4CVR=0;			//逆相を止める
	}
#endif
//DBS_L;					//割込み処理終了を表示する
}


//==============================================
//PWM周期を待つ
//==============================================
static void wait_pwm(void)
{

	TIM1->INTFR=~TIM_IT_Update;		//更新ｲﾍﾞﾝﾄをｸﾘｱする
	while(!(TIM1->INTFR&TIM_IT_Update));	//更新ｲﾍﾞﾝﾄを待つ
}


#ifdef	SLEEP_EN			//Sleep機能を実装するとき
//==============================================
//PWMを停止
//==============================================
static void dev_pwm_stop(void)
{

//DBG_C('\n');
//DBG_C('s');
	//DC更新を待つ
//DBG_C('1');
	wait_ms(10);				//10ms間はPWM割込み処理を回す

	//PWMを停止
//DBG_C('2');
	TIM1->DMAINTENR=0x0000;			//PWM割込み禁止

#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
//DBG_C('3');
	//ﾗﾝﾌﾟ下降
	while(TIM1->CH3CVR)			//DCが0になるまで繰返す
	{
		TIM1->CH3CVR--;			//DCをﾃﾞｸﾘする
		wait_pwm();			//PWM周期を待つ
	}
#endif

#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
//DBG_C('4');
	TIM1->CH1CVR=PWM_STEP/2;		//DCを50%にする
	wait_pwm();				//PWM周期を待つ
	TIM1->CCER=0x0000;			//PWM出力を止める
#endif
//DBG_C('5');
#if BTL>1				//ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
	TIM1->CH3CVR=TIM1->CH4CVR=0;		//DCを0%にする
	wait_pwm();				//PWM周期を待つ
#if BTL==3				//ﾌﾞﾚｰｷ出力のとき
	TIM1->CCER=0x1100;			//CC3を非反転出力､CC4を非反転出力
#endif
#endif
//DBG_C('6');
}


//==============================================
//PWMを再開
//==============================================
static void dev_pwm_start(void)
{

//DBG_C('\n');
//DBG_C('r');
	//ﾗﾝﾌﾟ上昇
#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
//DBG_C('1');
	while(TIM1->CH3CVR++<PWM_STEP/2)	//DCが50%になるまでｲﾝｸﾘする
	{
		wait_pwm();			//PWM周期を待つ
	}
#endif
#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
//DBG_C('2');
	TIM1->CCER=0x0005;			//CC1を非反転出力､CC1Nを非反転出力
#endif
#if BTL==3				//ﾌﾞﾚｰｷ出力のとき
//DBG_C('3');
	TIM1->CCER=0x3300;			//CC3を反転出力､CC4を反転出力
#endif

	//PWMを再開
//DBG_C('4');
	TIM1->DMAINTENR=TIM_IT_Update;		//更新ｲﾍﾞﾝﾄ割込み許可
//DBG_C('5');
}
#endif


//==============================================
//PWM初期設定
//==============================================
static void pwm_init(void)
{

//DBG_C('p');

	//PWM設定(TIM1)
#if BTL==2				//ﾌﾞﾘｯｼﾞ出力のとき
	TIM1->ATRLR=PWM_STEP+PWM_DB_BRG;	//自動ﾘﾛｰﾄﾞ値(PWM周期)ﾃﾞｯﾄﾞﾊﾞﾝﾄﾞを考慮
#else					//ｼﾝｸﾞﾙ･ｺﾝﾌﾟﾘ･ﾌﾞﾚｰｷ出力のとき
	TIM1->ATRLR=PWM_STEP;			//自動ﾘﾛｰﾄﾞ値(PWM周期)
#endif
	TIM1->SWEVGR=0x0001;			//更新ｲﾍﾞﾝﾄを発生させる
	TIM1->CHCTLR1=0x0068;			//CH1をPWMﾓｰﾄﾞ1､ﾌﾟﾘﾛｰﾄﾞ有効
	TIM1->CHCTLR2=0x6868;			//CH3とCH4をPWMﾓｰﾄﾞ1､ﾌﾟﾘﾛｰﾄﾞ有効
	TIM1->BDTR=TIM_MOE;			//出力有効
	TIM1->CTLR1=TIM_ARPE|TIM_CEN;		//自動ﾘﾛｰﾄﾞﾌﾟﾘﾛｰﾄﾞ有効､TMR有効
#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
	TIM1->CH1CVR=PWM_STEP/2;		//初期出力を50%ﾃﾞｭｰﾃｨにする
#endif
	wait_pwm();				//PWM周期を待つ
	GPIO_AF(PWM_F_GPIO,PWM_F_BIT);		//正相を交代機能に設定
#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
	TIM1->CCER=0x0100;			//CC3を非反転出力
#endif
#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
	TIM1->CCER=0x0005;			//CC1を非反転出力､CC1Nを非反転出力
	TIM1->BDTR|=PWM_DB_CMP;			//ﾃﾞｯﾄﾞﾊﾞﾝﾄﾞを設定する
	GPIO_AF(PWM_C_GPIO,PWM_C_BIT);		//相補を交代機能に設定
#endif
#if BTL==2				//ﾌﾞﾘｯｼﾞ出力のとき
	TIM1->CCER=0x1100;			//CC3を非反転出力､CC4を非反転出力
	GPIO_AF(PWM_R_GPIO,PWM_R_BIT);		//逆相を交代機能に設定
#endif
#if BTL==3				//ﾌﾞﾚｰｷ出力のとき
	TIM1->CCER=0x3300;			//CC3を反転出力､CC4を反転出力
	GPIO_AF(PWM_R_GPIO,PWM_R_BIT);		//逆相を交代機能に設定
#endif
//DBG_C('a');
#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
	while(TIM1->CH3CVR++<PWM_STEP/2)	//DCが50%になるまでｲﾝｸﾘする
	{
		wait_pwm();			//PWM周期を待つ
	}
#endif
//DBG_C('b');

	//PWM割込み設定
	NVIC_EnableIRQ(TIM1_UP_IRQn);		//TIM1更新ｲﾍﾞﾝﾄ割込み許可(Coreﾏｸﾛ)
	TIM1->DMAINTENR=TIM_IT_Update;		//更新ｲﾍﾞﾝﾄ割込み許可
//DBG_C('c');
}
