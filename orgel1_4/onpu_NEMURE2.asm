#ifndef def_onpu_NEMURE2
#define def_onpu_NEMURE2

//Ø‘Ö‚¦‚é”gŒ`‚ğŒÄ‚Ş
//#include	"enve_EXP.asm"	//´İÍŞÛ°ÌßÃŞ°À¤w”Œ¸Š‹Èü
//#include	"enve_RSN.asm"	//ÏØİÊŞ•—´İÍŞÛ°ÌßÃŞ°À¤±À¯¸Š´‚Æ‚Æ‚à‚É–L‚©‚È—]‰C‚à
#include	"enve_VIB.asm"	//ËŞÌŞ×Ì«İ•—´İÍŞÛ°ÌßÃŞ°À¤—h‚ç‚¬Œø‰Ê
//#include	"enve_TREMOLO.asm"	//ÏİÄŞØİ•—´İÍŞÛ°ÌßÃŞ°À¤ÄÚÓÛŒø‰Ê
//#include	"wave_SIN14.asm"	//‰¹Œ¹ÃŞ°À¤³Œ·”giŠî–{{‚SŸ‚’²”gj‰¹Œ¹
//#include	"wave_SQUAR.asm"	//‰¹Œ¹ÃŞ°À¤‹éŒ`”gi‚TŸ‚’²”g‚Ü‚Åj‰¹Œ¹
//#include	"wave_RING4.asm"	//‰¹Œ¹ÃŞ°À¤³Œ·”gŠî–{‚Æ‚SŸ‚’²”g‚Æ‚ÌØİ¸Ş•Ï’²‰¹Œ¹
//#include	"wave_SHEPARD.asm"	//‰¹Œ¹ÃŞ°À¤µ¸À°ÌŞ”{‰¹‚ğ‘½‚­ŠÜ‚Ş‰¹Œ¹

bgn_mac
//==============================================
//qç‰Ì(¼­°ÍŞÙÄì‹È)
//==============================================

//
//Êß°Ä0‚Ì‰¹•„ÃŞ°ÀÃ°ÌŞÙ
//
NEMURE20_onpu_tbl:
	vel_mac(140)	//ÍŞÛ¼Ã¨İ’è
	env_mac(50)	//´İÍŞÛ°ÌßÀ²Ñİ’è

	rp1_mac(2)	//ØËß°Ä1 ‰ñ”İ’è
NEMURE20_onpu_tbl_1_1:
//1-1	ĞĞ¿°
	onp_mac(0,kP4,3,Mi)
	onp_mac(0,kK8,3,Mi)
	onp_mac(0,kK2,3,So)
//1-2	ÚĞÌ§°
	onp_mac(0,kP4,3,Re)
	onp_mac(0,kK8,3,Mi)
	onp_mac(0,kK2,3,Fa)
//1-3	ĞĞÚÄŞ¼ÄŞ
	onp_mac(0,kK4,3,Mi)
	onp_mac(0,kK4,3,Mi)
	onp_mac(0,kK8,3,Re)
	onp_mac(0,kK8,3,Do)
	onp_mac(0,kK8,2,Si)
	onp_mac(0,kK8,3,Do)
//1-4	Ú°¿°
	onp_mac(0,kK2,3,Re)
	onp_mac(0,kK2,2,So)
//2-1	ĞĞ¿°
	onp_mac(0,kP4,3,Mi)
	onp_mac(0,kK8,3,Mi)
	onp_mac(0,kK2,3,So)
//2-2	ÚĞÌ§°
	onp_mac(0,kP4,3,Re)
	onp_mac(0,kK8,3,Mi)
	onp_mac(0,kK2,3,Fa)
//2-3	ĞĞÚĞÌ§Ú
	onp_mac(0,kK4,3,Mi)
	onp_mac(0,kK4,3,Mi)
	onp_mac(0,kK8,3,Re)
	onp_mac(0,kK8,3,Mi)
	onp_mac(0,kK8,3,Fa)
	onp_mac(0,kK8,3,Re)
//2-4	ÄŞ°
	onp_mac(0,kK1,3,Do)
//3-1	Ú°ÚÚ
	onp_mac(0,kK2,3,Re)
	onp_mac(0,kK4,3,Re)
	onp_mac(0,kK4,3,Re)
//3-2	ĞÚÄŞ°
	onp_mac(0,kP4,3,Mi)
	onp_mac(0,kK8,3,Re)
	onp_mac(0,kK2,3,Do)
//3-3	¿×¿Ì§Ğ
	onp_mac(0,kP4,3,So)
	onp_mac(0,kK16,3,La)
	onp_mac(0,kK16,3,So)
	onp_mac(0,kK4,3,Fa)
	onp_mac(0,kK4,3,Mi)
//3-4	Ú°¿°
	onp_mac(0,kK2,3,Re)
	onp_mac(0,kK2,2,So)
//4-1	ĞĞ¿°
	onp_mac(0,kP4,3,Mi)
	onp_mac(0,kK8,3,Mi)
	onp_mac(0,kK2,3,So)
//4-2	ÚĞÌ§°
	onp_mac(0,kP4,3,Re)
	onp_mac(0,kK8,3,Mi)
	onp_mac(0,kK2,3,Fa)
//4-3	ĞĞÚĞÌ§Ú
	onp_mac(0,kK4,3,Mi)
	onp_mac(0,kK4,3,Mi)
	onp_mac(0,kK8,3,Re)
	onp_mac(0,kK8,3,Mi)
	onp_mac(0,kK8,3,Fa)
	onp_mac(0,kK8,3,Re)
//4-4	ÄŞ°
	onp_mac(0,kK1,3,Do)
	env_mac(36)	//´İÍŞÛ°ÌßÀ²Ñİ’è
	enw_mac(enve_VIB)	//´İÍŞÛ°Ìß”gŒ`İ’è
	ena_mac(enve_VIB)	//´İÍŞÛ°Ìß”gŒ`İ’è
	jp1_mac(NEMURE20_onpu_tbl_1_1-NEMURE20_onpu_tbl)
		//ØËß°Ä1 •ªŠò
	onp_end

//
//Êß°Ä1‚Ì‰¹•„ÃŞ°ÀÃ°ÌŞÙ
//
NEMURE21_onpu_tbl:
	vel_mac(115)	//ÍŞÛ¼Ã¨İ’è
	env_mac(50)	//´İÍŞÛ°ÌßÀ²Ñİ’è

	rp1_mac(2)	//ØËß°Ä1 ‰ñ”İ’è
NEMURE21_onpu_tbl_1_0:
	rp2_mac(3)	//ØËß°Ä2 ‰ñ”İ’è
NEMURE21_onpu_tbl_1_1:
//1-1	ÄŞ°¿°
	onp_mac(0,kK2,2,Do)
	onp_mac(0,kK2,1,So)
//1-2	¼°¼°
	onp_mac(0,kK2,1,Si)
	onp_mac(0,kK2,1,Si)
	jp2_mac(NEMURE21_onpu_tbl_1_1-NEMURE21_onpu_tbl)
		//ØËß°Ä2 •ªŠò
//2-3	ÄŞ°¼°
	onp_mac(0,kK2,2,Do)
	onp_mac(0,kK2,1,Si)
//2-4	ÄŞĞÄŞ°
	onp_mac(0,kK4,2,Do)
	onp_mac(0,kK4,2,Mi)
	onp_mac(0,kK2,2,Do)
//3-1	¼°¼°
	onp_mac(0,kK2,1,Si)
	onp_mac(0,kK2,1,Si)
//3-2	ÄŞ°
	onp_mac(0,kK1,2,Do)
//3-3	Ğ°ÚÄŞ
	onp_mac(0,kK2,2,Mi)
	onp_mac(0,kK4,2,Re)
	onp_mac(0,kK4,2,Do)
//3-4	¼°¼°
	onp_mac(0,kK2,1,Si)
	onp_mac(0,kK2,1,Si)
//4-1	ÄŞ°¿°
	onp_mac(0,kK2,2,Do)
	onp_mac(0,kK2,1,So)
//4-2	¼°¿°
	onp_mac(0,kK2,1,Si)
	onp_mac(0,kK2,1,So)
//4-3	ÄŞ°¼°
	onp_mac(0,kK2,2,Do)
	onp_mac(0,kK2,1,Si)
	jp1_mac(NEMURE21_onpu_tbl_4_4-NEMURE21_onpu_tbl)
		//ØËß°Ä1 •ªŠò
	jmp_mac(NEMURE21_onpu_tbl_4_5-NEMURE21_onpu_tbl)
		//–³ğŒ•ªŠò
NEMURE21_onpu_tbl_4_4:
//4-4	ÄŞĞÄŞ¿
	onp_mac(0,kK4,2,Do)
	onp_mac(0,kK4,2,Mi)
	onp_mac(0,kK4,2,Do)
	onp_mac(0,kK4,1,So)
	env_mac(36)	//´İÍŞÛ°ÌßÀ²Ñİ’è
	enw_mac(enve_VIB)	//´İÍŞÛ°Ìß”gŒ`İ’è
	ena_mac(enve_VIB)	//´İÍŞÛ°Ìß”gŒ`İ’è
	jmp_mac(NEMURE21_onpu_tbl_1_0-NEMURE21_onpu_tbl)
		//–³ğŒ•ªŠò
NEMURE21_onpu_tbl_4_5:
//4-5	ÄŞĞÄŞ
	onp_mac(0,kK4,2,Do)
	onp_mac(0,kK4,2,Mi)
	onp_mac(0,kK2,2,Do)
	onp_end

//
//@iCj 2017-2023 MASARU WATANABE
//

end_mac
#endif
