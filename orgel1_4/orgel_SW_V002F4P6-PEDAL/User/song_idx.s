#include "orgel_cnf.h"
#if PART_N+KB_N>0			//ｵﾙｺﾞｰﾙ演奏･KB演奏を実装するとき
#include "../../orgel.inc"
	.text
	.align  2
	.globl	SONG_IDX
	.globl	song_idx_dmy

SONG_IDX:
	.hword	(song_idx_end-song_idx_bgn)/SONG_IDX_SZ	//ｴﾝﾄﾘ数
	.hword	0
song_idx_bgn:

#if PART_N>0				//ｵﾙｺﾞｰﾙ演奏を実装するとき

son_mac (song_AMBULANCE)		//1
#define song_AMBULANCE_DEF
son_mac (song_PATCAR)			//2
#define song_PATCAR_DEF
son_mac (song_FIRE)			//3
#define song_FIRE_DEF
son_mac (song_HORN)			//4
#define song_HORN_DEF
son_mac (song_ANPANMARCH)		//5
#define song_ANPANMARCH_DEF
son_mac (song_ANPANTAISO)		//6
#define song_ANPANTAISO_DEF
 
#endif

song_idx_end:
song_idx_dmy:
	ret


//==============================================
//ｿﾝｸﾞﾃﾞｰﾀの呼込み
//==============================================
#if PART_N>0					//ﾙｺﾞｰﾙ演奏を実装するとき
#include "../../song.inc"
#endif
#endif
