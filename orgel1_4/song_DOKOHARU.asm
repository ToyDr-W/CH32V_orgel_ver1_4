#ifndef def_song_DOKOHARU
#define def_song_DOKOHARU

//====================================
//‚Ç‚±‚©‚Åt‚ªiSHEPARDj
//====================================
//#include	"enve_EXP.asm"	//´İÍŞÛ°ÌßÃŞ°À¤w”Œ¸Š‹Èü
#include	"enve_RSN.asm"	//ÏØİÊŞ•—´İÍŞÛ°ÌßÃŞ°À¤±À¯¸Š´‚Æ‚Æ‚à‚É–L‚©‚È—]‰C‚à
//#include	"enve_VIB.asm"	//ËŞÌŞ×Ì«İ•—´İÍŞÛ°ÌßÃŞ°À¤—h‚ç‚¬Œø‰Ê
//#include	"enve_TREMOLO.asm"	//ÏİÄŞØİ•—´İÍŞÛ°ÌßÃŞ°À¤ÄÚÓÛŒø‰Ê
#include	"enve_ELEGANTE.asm"	//—D‰ë‚Å‰¹—Ê–L‚©‚È´İÍŞÛ°ÌßÃŞ°À¤—h‚ç‚¬Œø‰Ê
//#include	"wave_SIN14.asm"	//‰¹Œ¹ÃŞ°À¤³Œ·”giŠî–{{‚SŸ‚’²”gj‰¹Œ¹
//#include	"wave_SQUARE.asm"	//‰¹Œ¹ÃŞ°À¤‹éŒ`”gi‚TŸ‚’²”g‚Ü‚Åj‰¹Œ¹
//#include	"wave_RING4.asm"	//‰¹Œ¹ÃŞ°À¤³Œ·”gŠî–{‚Æ‚SŸ‚’²”g‚Æ‚ÌØİ¸Ş•Ï’²‰¹Œ¹
#include	"wave_SHEPARD.asm"	//‰¹Œ¹ÃŞ°À¤µ¸À°ÌŞ”{‰¹‚ğ‘½‚­ŠÜ‚Ş‰¹Œ¹
#include	"onpu_DOKOHARU.asm"	//‰¹•„ÃŞ°À

bgn_mac
song_DOKOHARU:
	ptr_mac(NULL)	//’P‹È‰‰‘t
	ops_mac(88)	//ÃİÎß[4•ª‰¹•„/•ª]
	kys_mac(1)	//ˆÚ’²“x[”¼‰¹ŠK]
	pns_mac(2)	//À‘•Êß°Ä”
	ptr_mac(DOKOHARU0_onpu_tbl)	//Êß°Ä0‰¹•„Ã°ÌŞÙÎß²İÀ
	ptr_mac(wave_SHEPARD)	//Êß°Ä0‰¹Œ¹Ã°ÌŞÙÎß²İÀ
	eps_mac(864)	//Êß°Ä0´İÍŞÛ°ÌßÀ²Ñ(ÃİÎß=100Šî€)[us/value/step]
	ptr_mac(enve_ELEGANTE)	//Êß°Ä0´İÍŞÛ°ÌßÃ°ÌŞÙÎß²İÀ
	pps_mac(0)	//Êß°Ä0Ëß¯ÁÍŞİÄŞÀ²Ñ(ÃİÎß=100Šî€)[us/value/step]
	ptr_mac(NULL)	//Êß°Ä0Ëß¯ÁÍŞİÄŞÃ°ÌŞÙÎß²İÀ
	ptr_mac(DOKOHARU1_onpu_tbl)	//Êß°Ä1‰¹•„Ã°ÌŞÙÎß²İÀ
	ptr_mac(wave_SHEPARD)	//Êß°Ä1‰¹Œ¹Ã°ÌŞÙÎß²İÀ
	eps_mac(800)	//Êß°Ä1´İÍŞÛ°ÌßÀ²Ñ(ÃİÎß=100Šî€)[us/value/step]
	ptr_mac(enve_RSN)	//Êß°Ä1´İÍŞÛ°ÌßÃ°ÌŞÙÎß²İÀ
	pps_mac(0)	//Êß°Ä1Ëß¯ÁÍŞİÄŞÀ²Ñ(ÃİÎß=100Šî€)[us/value/step]
	ptr_mac(NULL)	//Êß°Ä1Ëß¯ÁÍŞİÄŞÃ°ÌŞÙÎß²İÀ

end_mac
#endif
