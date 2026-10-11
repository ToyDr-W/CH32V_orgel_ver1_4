#ifdef I2C_SOFT				//I2Cをｿﾌﾄ実装するとき
#include "dev_I2C_SOFT.c"			//ｿﾌﾄ実装ｺｰﾄﾞを呼込む

#else					//内蔵I2Cﾓｼﾞｭｰﾙを使うとき
//==============================================
//I2Cｽﾃｰﾀｽﾘｰﾄﾞ
//==============================================
static unsigned long i2c_status(void)
{
	unsigned long s;

	s=I2C1->STAR1;
	s|=(unsigned long)I2C1->STAR2<<16;
//DBG_C('\n');
//DBG_L(s);
	return(s);
}


//==============================================
//I2Cｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ
//==============================================
static void i2c_start(void)
{

//DBG_C('\n');
//DBG_C('s');
	I2C1->CTLR1|=0x0100;			//ｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ
	while((i2c_status()&0x00030001)!=0x00030001);
						//BUSY･MSL･SBのｾｯﾄを待つ
}


//==============================================
//I2Cｽﾄｯﾌﾟｺﾝﾃﾞｨｼｮﾝ
//==============================================
static void i2c_stop(void)
{

//DBG_C('\n');
//DBG_C('p');
	I2C1->CTLR1|=0x0200;			//ｽﾄｯﾌﾟｺﾝﾃﾞｨｼｮﾝ
	while((i2c_status()&0x00030044)!=0x00030044);
						//BUSY･MSL･RxNA･BTFのｾｯﾄを待つ
}


//==============================================
//I2Cｱﾄﾞﾚｽ送信
//==============================================
static void i2c_addr(
	unsigned char data)			//送信ｱﾄﾞﾚｽ
{

//DBG_C('\n');
//DBG_C('a');
//DBG_B(data);
	I2C1->DATAR=data;			//ﾃﾞｰﾀ送信
	if(data&1)				//読込み設定のとき
	{
		I2C1->CTLR1|=0x0400;		//ACK応答を有効
//DBS_H;
		while((i2c_status()&0x00030002)!=0x00030002);
						//BUSY･MSL･ADDRのｾｯﾄを待つ
	}
	else					//書込み設定のとき
	{
		while((i2c_status()&0x00070082)!=0x00070082);
						//TRA･BUSY･MSL･TxE･ADDRのｾｯﾄを待つ
	}
}


//==============================================
//I2Cﾃﾞｰﾀ送信
//==============================================
static void i2c_send(
	unsigned char data)			//送信ﾃﾞｰﾀ
{

//DBG_C('\n');
//DBG_C('d');
//DBG_B(data);
	I2C1->DATAR=data;			//ﾃﾞｰﾀ送信
	while((i2c_status()&0x00070084)!=0x00070084);
						//TRA･BUSY･MSL･TXE･BTFのｾｯﾄを待つ
}


//==============================================
//I2C受信+ACK応答
//==============================================
static unsigned char i2c_recv_ack(void)		//受信ﾃﾞｰﾀを返す
{
	unsigned data;

//DBG_C('\n');
//DBG_C('r');
	while(!(i2c_status()&0x00000040));	//RxNEのｾｯﾄを待つ
	data=I2C1->DATAR;			//受信ﾃﾞｰﾀを取出す
//DBG_B(data);
	return(data);				//受信ﾃﾞｰﾀを返す
}


//==============================================
//I2C受信+NOACK応答
//==============================================
static unsigned char i2c_recv_noack(void)	//受信ﾃﾞｰﾀを返す
{
	unsigned data;

//DBG_C('\n');
//DBG_C('n');
	I2C1->CTLR1&=~0x0400;			//ACK設定を無効
//DBS_L;
	while(!(i2c_status()&0x00000040));	//RxNEのｾｯﾄを待つ
	while(!(i2c_status()&0x00000004));	//BTFのｾｯﾄを待つ
	data=I2C1->DATAR;			//受信ﾃﾞｰﾀを取出す
//DBG_B(data);
	return(data);				//受信ﾃﾞｰﾀを返す
}
#endif


//==============================================
//I2Cﾌﾗｯｼｭ開始
//==============================================
static void i2c_begin(
	unsigned char s_ad,
	unsigned short r_ad)
{

//DBG_C('b');
	i2c_start();				//ｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ
	i2c_addr(s_ad);				//ｽﾚｰﾌﾞｱﾄﾞﾚｽ+書込み指定送信
	i2c_send(r_ad>>8);			//ｱﾄﾞﾚｽ上位送信
	i2c_send(r_ad);				//ｱﾄﾞﾚｽ下位送信
	i2c_start();				//ｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ
	i2c_addr(s_ad|1);			//ｽﾚｰﾌﾞｱﾄﾞﾚｽ+読込み指定送信
}


//==============================================
//I2Cﾌﾗｯｼｭ読込み
//==============================================
#define	i2c_read()	i2c_recv_ack()


//==============================================
//I2Cﾌﾗｯｼｭ読込み(最後のﾃﾞｰﾀ)
//==============================================
#define	i2c_read_last()	i2c_recv_noack()


//==============================================
//I2Cﾌﾗｯｼｭ終了
//==============================================
#define	i2c_end()	i2c_stop()


//==============================================
//I2C初期設定
//==============================================
static void i2c_init(void)
{

	GPIO_H(I2C_SCL_GPIO,I2C_SCL_BIT);	//SCLをH
	GPIO_OUTOD(I2C_SCL_GPIO,I2C_SCL_BIT);	//SCLをOD出力
	GPIO_H(I2C_SDA_GPIO,I2C_SDA_BIT);	//SDAをH
	GPIO_OUTOD(I2C_SDA_GPIO,I2C_SDA_BIT);	//SDAをOD出力
	for(;;)					//I2Cｽﾚｰﾌﾞを同期する
	{
		wait_us(1);
		if(GPIO_R(I2C_SDA_GPIO,I2C_SDA_BIT)) break;
						//SDAがHになったら抜ける
		GPIO_H(I2C_SCL_GPIO,I2C_SCL_BIT);
						//SCLをH
		wait_us(1);
		GPIO_L(I2C_SCL_GPIO,I2C_SCL_BIT);
						//SCLをL
	}
	wait_us(1);
	GPIO_L(I2C_SDA_GPIO,I2C_SDA_BIT);	//SDAをL
	wait_us(1);
	GPIO_H(I2C_SCL_GPIO,I2C_SCL_BIT);	//SCLをH
	wait_us(1);
	GPIO_H(I2C_SDA_GPIO,I2C_SDA_BIT);	//SDAをH
	wait_us(1);
#ifndef I2C_SOFT			//内蔵I2Cﾓｼﾞｭｰﾙを使うとき
	GPIO_AFOD(I2C_SCL_GPIO,I2C_SCL_BIT);	//SCLを交代機能に設定
	GPIO_AFOD(I2C_SDA_GPIO,I2C_SDA_BIT);	//SDAを交代機能に設定
	I2C1->CTLR1=0x0401;			//ACK有効､I2C有効
	I2C1->CTLR2=0x0018;			//ｸﾛｯｸは24MHz
	I2C1->CKCFGR=60;			//400kbps
#endif
}
