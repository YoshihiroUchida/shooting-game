<<<<<<< HEAD
#include <iostream> // namespace ‚ğg—p
#include <memory> // ƒXƒ}[ƒgƒ|ƒCƒ“ƒ^i©“®ƒfƒXƒgƒ‰ƒNƒ^•tj‚ğg—p
#include <list> // ƒRƒ“ƒeƒiilistj‚ğg—p
#include <algorithm> // for_each ‚ğg—p
#include <cmath> // pow()i‚×‚«æ‚ÌŒvZj‚ğg—p
#include "DxLib.h" // DXƒ‰ƒCƒuƒ‰ƒŠ‚ğg—p

using namespace std; // std::`‚Ì\•¶‚ğ—ª‚·

//-------------------------------------------------------------------------------------

// —ñ‹“Œ^@ŠÖ”‚ÌƒXƒCƒbƒ`‚Æ‚µ‚Äg—p
// ‰æ‘œ
=======
// Visual Studio C++
#include <iostream> // namespace ã‚’ä½¿ç”¨ã™ã‚‹
#include <memory> // ã‚¹ãƒãƒ¼ãƒˆãƒã‚¤ãƒ³ã‚¿ï¼ˆè‡ªå‹•ãƒ‡ã‚¹ãƒˆãƒ©ã‚¯ã‚¿ä»˜ï¼‰ã‚’ä½¿ç”¨ã™ã‚‹
#include <list> // ã‚³ãƒ³ãƒ†ãƒŠï¼ˆlistï¼‰ã‚’ä½¿ç”¨ã™ã‚‹
#include <algorithm> // for_each ã‚’ä½¿ç”¨ã™ã‚‹
#include <cmath> // pow()ï¼ˆã¹ãä¹—ã®è¨ˆç®—ï¼‰ã‚’ä½¿ç”¨ã™ã‚‹
#include "DxLib.h" // DXãƒ©ã‚¤ãƒ–ãƒ©ãƒªã‚’ä½¿ç”¨ã™ã‚‹

using namespace std; // std::ï½ã®æ§‹æ–‡ã‚’ç•¥ã™

// åˆ—æŒ™å‹ã€€é–¢æ•°ã®ã‚¹ã‚¤ãƒƒãƒã¨ã—ã¦ä½¿ç”¨ã™ã‚‹
// ç”»åƒ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
enum ThingType {

	TYPE_NONE, // NONE
	TYPE_PLAYER, // PLAYER
	TYPE_SHOT1, // SHOT1
	TYPE_SHOT2, // SHOT2
	TYPE_SHOT3, // SHOT3 
	TYPE_SHOT4, // SHOT4
	TYPE_CHARGE_SHOT, // CHARGE SHOT
	TYPE_ENEMY_SHOT, // ENEMY SHOT
	TYPE_BEAM, // BEAM
	TYPE_ENEMY1, // ENEMY1
	TYPE_ENEMY2, // ENEMY2
	TYPE_ENEMY3, // ENEMY3
	TYPE_ENEMY4, // ENEMY4
	TYPE_ENEMY5, // ENEMY5
	TYPE_ENEMY6, // ENEMY6
	TYPE_ENEMY_BOSS1, // ENEMY BOSS1
	TYPE_ENEMY_BOSS2, // ENEMY_BOSS2
	TYPE_ENEMY_BOSS3, // ENEMY_BOSS3
	TYPE_ENEMY_BOSS4, // ENEMY_BOSS4
	TYPE_HEAL1, // HEAL1
	TYPE_HEAL2, // HEAL2
	TYPE_LIFE, // LIFE
	TYPE_EMPTY, // EMPTY
	TYPE_HEART, // HEART
	TYPE_ENERGY, // ENERGY
	TYPE_BURN, // BURN
	TYPE_NUM, // åˆ—æŒ™å¯¾ã®æ•°
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// ‰¹Šy
=======
// éŸ³æ¥½
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
enum Sound {

	SOUND_SHOT1, // SHOT1 éŸ³
	SOUND_SHOT2, // SHOT2 éŸ³
	SOUND_CHARGE, // CHARGE ä¸­ã®éŸ³
	SOUND_CHARGE_SHOT, // CHARGE SHOTã®éŸ³
	SOUND_ENEMY_SHOT, // ENEMY SHOTã®éŸ³
	SOUND_BEAM, // BEAM éŸ³
	SOUND_E_ATTACK, // ENEMY ã®ã‚¢ã‚¿ãƒƒã‚¯éŸ³
	SOUND_P_ATTACK, // PLAYER ã®ã‚¢ã‚¿ãƒƒã‚¯éŸ³
	SOUND_HEAL, // å›å¾©éŸ³
	SOUND_BREAK, // ç ´å£ŠéŸ³
	SOUND_NUM, // åˆ—æŒ™å¯¾ã®æ•°
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

class Thing; // ƒXƒ}[ƒgƒ|ƒCƒ“ƒ^i©“®ƒfƒXƒgƒ‰ƒNƒ^•tj‚Ì Thing ƒNƒ‰ƒX‚ğì‚éˆ×‚ÉéŒ¾

// Thing ƒNƒ‰ƒX@ƒXƒ}[ƒgƒ|ƒCƒ“ƒ^ishared_ptr ‚Å Thing Œ^jThingPointa
// Game ƒNƒ‰ƒX‚ÅƒRƒ“ƒeƒiilistj‚ÌŒ^‚ğg—p
// new ‚ÅŠm•Û‚µ‚½ƒƒ‚ƒŠ‚ğ©“®“I‚É delete ‚·‚é
// typedef ‚Íƒf[ƒ^Œ^‚Ö•Ê–¼‚ğ•t‚¯‚é
typedef shared_ptr <Thing> ThingPointa;

//-------------------------------------------------------------------------------------

// ƒOƒ[ƒoƒ‹•Ï”iƒR[ƒh‘S‘Ì‚ÉŠÖ˜A‚·‚é•Ï”j
int scene; // ‰æ–Ê
int stage; // STAGE
int score; // ƒXƒRƒA
int shot_count = 0; // ’e‚ÌŠÔŠu’²®@‰Šú‰»
int enemy_x; // “G‚Ì x À•W‚É
int enemy_y; // “G‚Ì y À•W‚É
int enemy_num = 0; // ‰æ–Êã‚Ì“G@‰Šú‰»
int enemy_s; // “G‚Ì‘¬“x
bool pause_flag; // ƒ|[ƒYi‹x~jƒtƒ‰ƒO

int loaded_picture[TYPE_NUM]; // ‰æ‘œ”z—ñ
int loaded_sound[SOUND_NUM]; // ‰¹”z—ñ

// ‰¹ƒtƒ@ƒCƒ‹Ši”[—p•Ï”iGame ƒNƒ‰ƒXj
int Title_m; // ƒ^ƒCƒgƒ‹‰æ–Ê
int Play_m; // ƒvƒŒƒC‰æ–Ê
int Over_m; // ƒI[ƒo[‰æ–Ê
int Clear_m; // ƒNƒŠƒA‰æ–Ê
int Pause_m; // ƒ|[ƒYi‹x~j‰æ–Ê
int Boss_m; // ƒ{ƒX‰æ–Ê

//-------------------------------------------------------------------------------------

// Thing ƒNƒ‰ƒXiŒp³ƒNƒ‰ƒXj
class Thing {

protected: // qƒNƒ‰ƒX‚ÉŒp³

	float m_x; // x À•W
	float m_y; // y À•W
	int m_w; // ‰¡•
	int m_h; // c•
	int m_s; // ‘¬“x

	// “–‚½‚è”»’è—p•Ï”
	float hit_x; // x À•W
	float hit_y; // y À•W
	float hit_w; // ‰¡•
	float hit_h; // c•

	int life_max; // İ’è‘Ì—Í
	int life_now; // ¡‚Ì‘Ì—Í
	int energy_max; // İ’è“Áê—Ê
	int energy_now; // ¡‚Ì“Áê—Ê
	int damage; // ‘¹ŠQ—Ê
	int energy; // “Áê—Ê
	bool remove_flag; // íœƒtƒ‰ƒO
	void remove(); // íœƒtƒ‰ƒO‚ğ true ‚É

public:

	Thing(); // ƒRƒ“ƒXƒgƒ‰ƒNƒ^iíœƒtƒ‰ƒO‚ğ false ‚Éj
	void SET_picture(const char* file_name, ThingType thing); // const char* ‚É@ƒNƒ‰ƒX—p@‰æ‘œ
	virtual void SET_sound(const char* file_name, Sound sound); // const char* ‚É@ƒNƒ‰ƒX—p@‰¹
	virtual void SET_position(int, int); // À•W‚ğİ’è
	virtual void SET_hitarea(int, int, int, int); // “–‚½‚è”»’è‚ğİ’è
	bool GET_remove(); // íœƒtƒ‰ƒO‚ğ“¾‚é
	bool HIT_test(ThingPointa&); // “–‚½‚è”»’è

	virtual ThingType GET_TYPE() = 0; // ©•ª‚Ìƒ^ƒCƒv‚ğ“¾‚éiƒˆ‰¼‘zj
	virtual ThingType HIT_TYPE(); // “–‚½‚éƒ^ƒCƒv‚ğ NONE ‚Éi‰¼‘zj

	int GET_damage(); // ‘¹ŠQ—Ê‚Ìˆ—
	int GET_energy(); // “Áê—Ê‚Ìˆ—

	virtual void SET_angle(float a) {}; // Šp“x‚ğİ’è
	virtual void SET_sign(int s) {}; // •„†‚ğİ’è
	virtual void move() = 0; // “®ìiƒˆ‰¼‘zj
	virtual void draw(); // ‰æ‘œ‚ğ•`‰æ
	virtual void life_draw(); // ‘Ì—Í‚ğ•`‰æ
	virtual void hit(int damage, int energy) = 0; // “–‚½‚è”»’è true ‚Ìê‡@ˆ—iƒˆ‰¼‘zj
};

//-------------------------------------------------------------------------------------

// Player ƒNƒ‰ƒX
=======
class Thing; // ã‚¹ãƒãƒ¼ãƒˆãƒã‚¤ãƒ³ã‚¿ï¼ˆè‡ªå‹•ãƒ‡ã‚¹ãƒˆãƒ©ã‚¯ã‚¿ä»˜ï¼‰ã® Thing ã‚¯ãƒ©ã‚¹ã‚’ä½œã‚‹ç‚ºã«å®£è¨€ã™ã‚‹

// Thing ã‚¯ãƒ©ã‚¹ã®ã‚¹ãƒãƒ¼ãƒˆãƒã‚¤ãƒ³ã‚¿ï¼ˆshared_ptr ã§ Thing å‹ï¼‰ThingPointa ã‚’å®šç¾©ã™ã‚‹
// Game ã‚¯ãƒ©ã‚¹ã§ã‚³ãƒ³ãƒ†ãƒŠï¼ˆlistï¼‰ã®å‹ã«ä½¿ç”¨ã™ã‚‹
// ã‚¹ãƒãƒ¼ãƒˆãƒã‚¤ãƒ³ã‚¿ã¯ new ã§ç¢ºä¿ã—ãŸãƒ¡ãƒ¢ãƒªã‚’è‡ªå‹•çš„ã« delete ã™ã‚‹
// typedef ã¯å…ƒã€…ã®ãƒ‡ãƒ¼ã‚¿å‹ã¸åˆ¥åã‚’ä»˜ã‘ã‚‹
typedef shared_ptr <Thing> ThingPointa;

// ã‚°ãƒ­ãƒ¼ãƒãƒ«å¤‰æ•°ï¼ˆå…¨ä½“ã«é–¢é€£ã™ã‚‹å¤‰æ•°ï¼‰
int scene; // ç”»é¢
int stage; // STAGE
int score; // ã‚¹ã‚³ã‚¢
int shot_count = 0; // å¼¾ã®é–“éš”èª¿æ•´ã€€ï¼ã«è¨­å®šã™ã‚‹
int enemy_x; // æ•µã® x åº§æ¨™ã«ç½®ã
int enemy_y; // æ•µã® y åº§æ¨™ã«ç½®ã
int enemy_num = 0; // ç”»é¢ä¸Šã®æ•µã€€ï¼ã«è¨­å®šã™ã‚‹
int enemy_s; // æ•µã®é€Ÿåº¦
bool pause_flag; // ãƒãƒ¼ã‚ºï¼ˆä¼‘æ­¢ï¼‰ãƒ•ãƒ©ã‚°

int loaded_picture[TYPE_NUM]; // ç”»åƒé…åˆ—
int loaded_sound[SOUND_NUM]; // éŸ³é…åˆ—

// éŸ³æ¥½ãƒ•ã‚¡ã‚¤ãƒ«æ ¼ç´ç”¨å¤‰æ•°ï¼ˆGame ã‚¯ãƒ©ã‚¹ã«ã¦è¨­å®šã™ã‚‹ï¼‰
int Title_m; // ã‚¿ã‚¤ãƒˆãƒ«ä¸­
int Play_m; // ãƒ—ãƒ¬ã‚¤ä¸­
int Over_m; // ã‚ªãƒ¼ãƒãƒ¼ä¸­
int Clear_m; // ã‚¯ãƒªã‚¢ä¸­
int Pause_m; // ãƒãƒ¼ã‚ºï¼ˆä¼‘æ­¢ï¼‰ç”»é¢
int Boss_m; // ãƒœã‚¹ä¸­

// Thing ã‚¯ãƒ©ã‚¹ï¼ˆç¶™æ‰¿ã‚¯ãƒ©ã‚¹ï¼‰
class Thing {

protected: // å­ã‚¯ãƒ©ã‚¹ã«ç¶™æ‰¿ã™ã‚‹

	float m_x; // x åº§æ¨™
	float m_y; // y åº§æ¨™
	int m_w; // æ¨ªå¹…
	int m_h; // ç¸¦å¹…
	int m_s; // é€Ÿåº¦

	// å½“ãŸã‚Šåˆ¤å®šå¤‰æ•°
	float hit_x; // x åº§æ¨™
	float hit_y; // y åº§æ¨™
	float hit_w; // æ¨ªå¹…
	float hit_h; // ç¸¦å¹…

	int life_max; // è¨­å®šä½“åŠ›
	int life_now; // ä»Šã®ä½“åŠ›
	int energy_max; // è¨­å®šç‰¹æ®Šé‡
	int energy_now; // ä»Šã®ç‰¹æ®Šé‡
	int damage; // æå®³é‡
	int energy; // ç‰¹æ®Šé‡
	bool remove_flag; // å‰Šé™¤ãƒ•ãƒ©ã‚°
	void remove(); // å‰Šé™¤ãƒ•ãƒ©ã‚°ã‚’ true ã«ã™ã‚‹

public:

	Thing(); // ã‚³ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚¿ï¼ˆå‰Šé™¤ãƒ•ãƒ©ã‚°ã‚’ false ã«ï¼‰
	void SET_picture(const char* file_name, ThingType thing); // const char* ã«ã™ã‚‹ã€€ã‚¯ãƒ©ã‚¹ã«ç”»åƒã‚’ç½®ã
	virtual void SET_sound(const char* file_name, Sound sound); // const char* ã«ã™ã‚‹ã€€ã‚¯ãƒ©ã‚¹ã«éŸ³ã‚’ç½®ã
	virtual void SET_position(int, int); // åˆæœŸåº§æ¨™ã‚’è¨­å®šã™ã‚‹
	virtual void SET_hitarea(int, int, int, int); // å½“ãŸã‚Šåˆ¤å®šã‚’è¨­å®šã™ã‚‹
	bool GET_remove(); // å‰Šé™¤ãƒ•ãƒ©ã‚°ã‚’å¾—ã‚‹
	bool HIT_test(ThingPointa&); // å½“ãŸã‚Šåˆ¤å®šã®é–¢æ•°

	virtual ThingType GET_TYPE() = 0; // è‡ªåˆ†ã®ã‚¿ã‚¤ãƒ—ã‚’å¾—ã‚‹ï¼ˆç´”ç²‹ä»®æƒ³ï¼‰
	virtual ThingType HIT_TYPE(); // å½“ãŸã‚‹ã‚¿ã‚¤ãƒ—ã‚’ NONE ã«ã™ã‚‹ï¼ˆä»®æƒ³ï¼‰

	int GET_damage(); // æå®³é‡ã®å‡¦ç†ã‚’ã™ã‚‹
	int GET_energy(); // ç‰¹æ®Šé‡ã®å‡¦ç†ã‚’ã™ã‚‹

	virtual void SET_angle(float a) {}; // è§’åº¦è¨­å®šã™ã‚‹
	virtual void SET_sign(int s) {}; // ç¬¦å·è¨­å®šã™ã‚‹
	virtual void move() = 0; // è¡Œå‹•ç¯„å›²ï¼ˆç´”ç²‹ä»®æƒ³ï¼‰
	virtual void draw(); // ç”»åƒæç”»ã‚’ã™ã‚‹
	virtual void life_draw(); // ä½“åŠ›æç”»ã‚’ã™ã‚‹
	virtual void hit(int damage, int energy) = 0; // å½“ãŸã‚Šåˆ¤å®š true ã®æ™‚ã€€å‡¦ç†ã‚’ã™ã‚‹ï¼ˆç´”ç²‹ä»®æƒ³ï¼‰
};

// Player ã‚¯ãƒ©ã‚¹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Player : public Thing {

private:

<<<<<<< HEAD
	int charge_time; // charge Œv‘ªiŠg‘å’e—pj
	int dead_time; // dead Œv‘ªi“_–Å—pj
	bool beam_flag; // beam ƒtƒ‰ƒO
	bool shot_flag; // shot ƒtƒ‰ƒO

public:

	Player(); // ƒRƒ“ƒXƒgƒ‰ƒNƒ^iİ’èj
	ThingType GET_TYPE(); // ©•ª‚ğ PLAYER ƒ^ƒCƒv‚Å•Ô‚·
	ThingType HIT_TYPE(); // “–‚½‚éƒ^ƒCƒv‚ğ ENEMY1 ƒ^ƒCƒv‚Å•Ô‚·
	void move(); // ©‹@‚Ì“®ì@’e‘€ì@‰æ–Ê‚Ì“–‚½‚è”»’è
	void heart_draw(); // ‘Ì—Í‚Ì•`‰æ
	void energy_draw(); // “Áê—Ê‚Ì•`‰æ
	void draw(); // dead_time ‚Ì’l‚Å“_–Å
	void hit(int damage, int energy); // dead_time ‚ğ‚T‚O‚É
};

//-------------------------------------------------------------------------------------

// Shot ƒNƒ‰ƒXi’Êí’ej
=======
	int charge_time; // charge ã‚«ã‚¦ãƒ³ãƒˆ
	int dead_time; // dead ã‚«ã‚¦ãƒ³ãƒˆï¼ˆç‚¹æ»…ï¼‰
	bool beam_flag; // beam ãƒ•ãƒ©ã‚°
	bool shot_flag; // shot ãƒ•ãƒ©ã‚°

public:

	Player(); // ã‚³ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚¿ï¼ˆåˆæœŸè¨­å®šï¼‰
	ThingType GET_TYPE(); // è‡ªåˆ†ã‚’ PLAYER ã‚¿ã‚¤ãƒ—ã§è¿”ã™
	ThingType HIT_TYPE(); // å½“ãŸã‚‹ã‚¿ã‚¤ãƒ—ã‚’ ENEMY1 ã‚¿ã‚¤ãƒ—ã§è¿”ã™
	void move(); // è¡Œå‹•ç¯„å›²ãƒ»ã‚¢ã‚¿ãƒƒã‚¯ãƒ»ç”»é¢ã®å½“ãŸã‚Šåˆ¤å®š
	void heart_draw(); // ä½“åŠ›ã®æç”»ã‚’ã™ã‚‹
	void energy_draw(); // ç‰¹æ®Šé‡ã®æç”»ã‚’ã™ã‚‹
	void draw(); // æå®³é‡ã«å¯¾ã—ã¦ç‚¹æ»…ã™ã‚‹
	void hit(int damage, int energy); // ç‚¹æ»…ã‚’ï¼•ï¼ã«ã™ã‚‹
};

// Shot ã‚¯ãƒ©ã‚¹ï¼ˆé€šå¸¸å¼¾ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Shot : public Thing {

protected:

	float angle; // å††ã®è§’åº¦
	float center_x; // ä¸­å¿ƒ x åº§æ¨™
	float center_y; // ä¸­å¿ƒ y åº§æ¨™
	float shot_s; // å¼¾ã®é€Ÿåº¦

public:

<<<<<<< HEAD
	Shot(); // ƒRƒ“ƒXƒgƒ‰ƒNƒ^iİ’èj
	ThingType GET_TYPE(); // ©•ª‚ğ SHOT1 ƒ^ƒCƒv‚Å•Ô‚·
	ThingType HIT_TYPE(); // “–‚½‚é“G‚ğ ENEMY1 ƒ^ƒCƒv‚Å•Ô‚·
	void move(); // ‰E•ûŒü‚Ö@‰æ–Ê’[‚Åíœ
	void draw(); // •`‰æ
	void hit(int damage, int energy); // ˆ—@íœ
};

//-------------------------------------------------------------------------------------

// Through Shot ƒNƒ‰ƒXiŠÑ’Ê’ej
=======
	Shot(); // ã‚³ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚¿ï¼ˆåˆæœŸè¨­å®šï¼‰
	ThingType GET_TYPE(); // è‡ªåˆ†ã‚’ SHOT1 ã‚¿ã‚¤ãƒ—ã§è¿”ã™
	ThingType HIT_TYPE(); // å½“ãŸã‚‹æ•µã‚’ ENEMY1 ã‚¿ã‚¤ãƒ—ã§è¿”ã™
	void move(); // å³æ–¹å‘ã¸ã€€ç”»é¢ã®ç«¯ã§å‰Šé™¤ã™ã‚‹
	void draw(); // æç”»ã™ã‚‹
	void hit(int damage, int energy); // å‡¦ç†ãƒ»å‰Šé™¤ã™ã‚‹
};

// Through Shot ã‚¯ãƒ©ã‚¹ï¼ˆè²«é€šå¼¾ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Through_Shot : public Shot {

public:

	Through_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Beam ƒNƒ‰ƒXiŒõüj
=======
// Beam ã‚¯ãƒ©ã‚¹ï¼ˆå…‰ç·šï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Beam : public Shot {

public:

	Beam();
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Vortex Shot ƒNƒ‰ƒXi‰Q’ej
=======
// Vortex Shot ã‚¯ãƒ©ã‚¹ï¼ˆæ¸¦å¼¾ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Vortex_Shot : public Through_Shot {

private:

	float rad; // åŠå¾„

public:

	Vortex_Shot();
<<<<<<< HEAD
	void SET_position(int, int); // À•W‚ğİ’è
=======
	void SET_position(int, int); // åˆæœŸä½ç½®ã‚’è¨­å®šã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Spray Shot ƒNƒ‰ƒXiU•z’ej
=======
// Spray Shot ã‚¯ãƒ©ã‚¹ï¼ˆæ•£å¸ƒå¼¾ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Spray_Shot : public Through_Shot {

public:

	Spray_Shot();
	void SET_angle(float a); // Šp“x‚ğİ’è
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Rasen Shot ƒNƒ‰ƒXi—†ù’ej
=======
// Rasen Shot ã‚¯ãƒ©ã‚¹ï¼ˆèºæ—‹å¼¾ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Rasen_Shot : public Shot {

private:

	int sign; // 1 or -1ï¼ˆç¬¦å·æ ¼ç´ï¼‰

public:

	Rasen_Shot();
	void SET_position(int, int);
	void SET_sign(int s); // •„†‚ğİ’è
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Charge Shot ƒNƒ‰ƒXiŠg‘å’ej
=======
// Charge Shot ã‚¯ãƒ©ã‚¹ï¼ˆæ‹¡å¤§å¼¾ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Charge_Shot : public Shot {

private:

	bool charge_flag; // charge ãƒ•ãƒ©ã‚°

public:

	Charge_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot1 ƒNƒ‰ƒXiŒÀ’ej
=======
// Period Shot1 ã‚¯ãƒ©ã‚¹ï¼ˆæ™‚é™å¼¾ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Period_Shot1 : public Thing {

private:

	int shot_time; // ç™ºå°„ã¾ã§ã®æ™‚é–“
	int shot_count; // ç™ºå°„ã™ã‚‹æ•°

public:

	Period_Shot1();
	// å½“ãŸã‚Šåˆ¤å®šÃ—ã€€ã‚¿ã‚¤ãƒ—ã‚’ NONE ã§è¿”ã™
	ThingType GET_TYPE();
	ThingType HIT_TYPE();
	void move();
	void draw();
	void hit(int damage, int energy) {};
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot2 ƒNƒ‰ƒXiãE‰ºj
=======
// Period Shot2 ã‚¯ãƒ©ã‚¹ï¼ˆä¸Šãƒ»ä¸‹ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Period_Shot2 : public Through_Shot {

protected:

	int sign; // •„†

public:

	Period_Shot2();
	void SET_sign(int s);
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot3 ƒNƒ‰ƒXi¶E‰Ej
=======
// Period Shot3 ã‚¯ãƒ©ã‚¹ï¼ˆå·¦ãƒ»å³ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Period_Shot3 : public Period_Shot2 {

public:

	Period_Shot3();
	void SET_sign(int s);
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Homing Shot ƒNƒ‰ƒXi’Ç”ö’ej
=======
// Homing Shot ã‚¯ãƒ©ã‚¹ï¼ˆè¿½å°¾å¼¾ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Homing_Shot : public Shot {

public:

	Homing_Shot();
<<<<<<< HEAD
	void move(); // “G‚ğ’Ç”ö
=======
	void move(); // æ•µã‚’è¿½å°¾ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Parabola Shot ƒNƒ‰ƒXi•ú•¨ü’ej
=======
// Parabola Shot ã‚¯ãƒ©ã‚¹ï¼ˆè¿½å°¾ãƒ»æ”¾ç‰©ç·šå¼¾ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Parabola_Shot : public Shot {

	// æ”¾ç‰©ç·šã«é–¢ã™ã‚‹å¤‰æ•°
	float a;
	float b;
	float c;

public:

	Parabola_Shot();
<<<<<<< HEAD
	void SET_position(int, int); // À•W‚ğİ’è
=======
	void SET_position(int, int); // åˆæœŸä½ç½®ãƒ»åº§æ¨™ã‚’æ±‚ã‚ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy1 ƒNƒ‰ƒXi’Êíj
=======
// Enemy1 ã‚¯ãƒ©ã‚¹ï¼ˆé€šå¸¸ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy1 : public Thing {

protected:

<<<<<<< HEAD
	int count; // ”š”j‚µ‚Äíœ‚·‚é‚Ü‚Å‚Ì”’l‚É
	int up_down; // ã‰º•ûŒü
	bool count_flag; // ”š”jƒtƒ‰ƒO
=======
	int count; // çˆ†ç ´ã—ã¦å‰Šé™¤ã™ã‚‹ã¾ã§ã€€æ•°å€¤ã‚’å…¥ã‚Œã‚‹
	int up_down; // ä¸Šä¸‹æ–¹å‘
	bool count_flag; // çˆ†ç ´ãƒ•ãƒ©ã‚°
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

public:

	Enemy1();
<<<<<<< HEAD
	ThingType GET_TYPE(); // ©•ª‚ğ ENEMY1 ƒ^ƒCƒv‚Å•Ô‚·
	ThingType HIT_TYPE(); // “–‚½‚é“G‚ğ PLAYER ƒ^ƒCƒv‚Å•Ô‚·
=======
	ThingType GET_TYPE(); // è‡ªåˆ†ã‚’ ENEMY1 ã‚¿ã‚¤ãƒ—ã¨è¿”ã™
	ThingType HIT_TYPE(); // å½“ãŸã‚‹æ•µã‚’ PLAYER ã‚¿ã‚¤ãƒ—ã¨è¿”ã™
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy); // ENEMY1ï½6ã¾ã§å…±é€šè¨­å®š
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy2 ƒNƒ‰ƒXiƒ^ƒtj
=======
// Enemy2 ã‚¯ãƒ©ã‚¹ï¼ˆã‚¿ãƒ•ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy2 : public Enemy1 {

public:

	Enemy2();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy3 ƒNƒ‰ƒXiƒxƒNƒgƒ‹j
=======
// Enemy3 ã‚¯ãƒ©ã‚¹ï¼ˆãƒ™ã‚¯ãƒˆãƒ«ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy3 : public Enemy1 {

public:

	Enemy3();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy4 ƒNƒ‰ƒXi‚‘¬j
=======
// Enemy4 ã‚¯ãƒ©ã‚¹ï¼ˆé«˜é€Ÿï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy4 : public Enemy1 {

public:

	Enemy4();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy5 ƒNƒ‰ƒXi’ÊíUŒ‚j
=======
// Enemy5 ã‚¯ãƒ©ã‚¹ï¼ˆé€šå¸¸æ”»æ’ƒï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy5 : public Enemy1 {

public:

	Enemy5();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy6 ƒNƒ‰ƒXiƒxƒNƒgƒ‹UŒ‚j
=======
// Enemy6 ã‚¯ãƒ©ã‚¹ï¼ˆãƒ™ã‚¯ãƒˆãƒ«æ”»æ’ƒï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy6 : public Enemy1 {

public:

	Enemy6();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Boss1 ƒNƒ‰ƒXiSTAGE‚P`‚X‚Ü‚Å‹¤’Êj
=======
// Enemy Boss1 ã‚¯ãƒ©ã‚¹ï¼ˆSTAGEï¼‘ï½ï¼™ã¾ã§å…±é€šï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy_Boss1 : public Enemy1 {

protected:

	int add_speed; // é€Ÿåº¦ã‚’ä¸Šã’ã‚‹
	int Warn_p; // WARNING!!

public:

	Enemy_Boss1();
	void move();
<<<<<<< HEAD
	void life_draw(); // ‘Ì—Í‚ğ•`‰æ
=======
	void life_draw(); // ä½“åŠ›ã‚’æç”»ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Boss2 ƒNƒ‰ƒXiSTAGE‚P‚Oj
=======
// Enemy Boss2 ã‚¯ãƒ©ã‚¹ï¼ˆSTAGEï¼‘ï¼ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy_Boss2 : public Enemy_Boss1 {

public:

	Enemy_Boss2();
	void move();
	void life_draw();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Shot1 ƒNƒ‰ƒXiƒ{ƒX—pj
=======
// Enemy Shot1 ã‚¯ãƒ©ã‚¹ï¼ˆãƒœã‚¹ç”¨ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy_Shot1 : public Thing {

public:

	Enemy_Shot1();
<<<<<<< HEAD
	ThingType GET_TYPE(); // ©•ª‚ğ ENEMY_SHOT1 ƒ^ƒCƒv‚Å•Ô‚·
	ThingType HIT_TYPE(); // “–‚½‚é“G‚ğ PLAYER ƒ^ƒCƒv‚Å•Ô‚·
=======
	ThingType GET_TYPE(); // è‡ªåˆ†ã‚’ ENEMY_SHOT1 ã‚¿ã‚¤ãƒ—ã¨è¿”ã™
	ThingType HIT_TYPE(); // å½“ãŸã‚‹æ•µã‚’ PLAYER ã‚¿ã‚¤ãƒ—ã¨è¿”ã™
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Shot2 ƒNƒ‰ƒXiENEMY5E6—pj
=======
// Enemy Shot2 ã‚¯ãƒ©ã‚¹ï¼ˆENEMY5ãƒ»6ç”¨ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy_Shot2 : public Enemy_Shot1 {

public:

	Enemy_Shot2();
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Heal1 ƒNƒ‰ƒXi‘Ì—Í‰ñ•œj
=======
// Heal1 ã‚¯ãƒ©ã‚¹ï¼ˆä½“åŠ›å›å¾©ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Heal1 : public Thing {

public:

	Heal1();
<<<<<<< HEAD
	ThingType GET_TYPE(); // ©•ª‚ğ HEAL1 ƒ^ƒCƒv‚Å•Ô‚·
	ThingType HIT_TYPE(); // “–‚½‚é‚à‚Ì‚ğ PLAYER ƒ^ƒCƒv‚Å•Ô‚·
=======
	ThingType GET_TYPE(); // è‡ªåˆ†ã‚’ HEAL1 ã‚¿ã‚¤ãƒ—ã¨è¿”ã™
	ThingType HIT_TYPE(); // å½“ãŸã‚‹ã‚‚ã®ã‚’ PLAYER ã‚¿ã‚¤ãƒ—ã¨è¿”ã™
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Heal2 ƒNƒ‰ƒXi“Áê—Ê‰ñ•œj
=======
// Heal2 ã‚¯ãƒ©ã‚¹ï¼ˆç‰¹æ®Šé‡å›å¾©ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Heal2 : public Heal1 {

public:

	Heal2();
	void draw();
	void move();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Game ƒNƒ‰ƒX
class Game {

	std::list <ThingPointa> thing_list; // Thing ƒNƒ‰ƒX@ƒXƒ}[ƒgƒ|ƒCƒ“ƒ^‚ğƒŠƒXƒgilistjŒ^ƒf[ƒ^\‘¢ithing_listj‚É
=======
// Game ã‚¯ãƒ©ã‚¹
class Game {

	std::list <ThingPointa> thing_list; // Thing ã‚¯ãƒ©ã‚¹ã®ã‚¹ãƒãƒ¼ãƒˆãƒã‚¤ãƒ³ã‚¿ã‚’ list å‹ãƒ‡ãƒ¼ã‚¿æ§‹é€ ï¼ˆthing_listï¼‰ã«å…¥ã‚Œã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

private:

	// ãƒãƒƒã‚¯ç”¨å¤‰æ•°
	int p_x; // x åº§æ¨™ï¼ˆãƒ«ãƒ¼ãƒ—ä»•æ§˜ï¼‰
	int p_w; // æ¨ªå¹…
	int add_s; // é€Ÿåº¦

<<<<<<< HEAD
	// ‰æ‘œ“Ç—p•Ï”
	int Game_p; // ƒoƒbƒN
=======
	// ç”»åƒèª­è¾¼ç”¨å¤‰æ•°
	int Game_p; // ãƒãƒƒã‚¯ã®ç”»åƒ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	int Title_p; // SHOOTING GAME
	int Select_p; // STAGE SELECT
	int Number_p; // 1 2 3 4 5 6 7 8 9 10
	int Push_p; // PUSH SPACE
	int Over_p; // GAME OVER
	int Clear_p; // GAME CLEAR
	int Pause_p; // PAUSE
	int Esc_p; // ESC : TITLEESPACE : REPLAY

<<<<<<< HEAD
	// ƒtƒ‰ƒO•Ï”
	bool push_flag; // PUSH_spaceŠÖ”EPUSH_backŠÖ”—p
	bool play_flag; // ƒvƒŒƒC—pEtrue ‚ÅƒXƒ^[ƒg
	bool boss_flag; // ƒ{ƒX—p
	bool space_flag; // ƒXƒy[ƒX—p

	// ƒXƒRƒAEŠÔ‚ÉŠÖ‚·‚é•Ï”
	int high_score; // ƒnƒCƒXƒRƒAihigh_score < now_score ‚Ìê‡j
	int now_score; // ƒXƒRƒA
	int now_time; // c‚èŠÔ
	int start_time; // ‚Ps ’PˆÊ‚ÅŒv‘ª‚·‚é
	int stop_time; // ƒ|[ƒY‚·‚éê‡@Œ»İŠÔ‚ğ“¾‚é
	int pause_time; // ƒ|[ƒY‰æ–Ê‚ÌŒo‰ßŠÔ
	int limit_time; // §ŒÀŠÔ
=======
	// ãƒ•ãƒ©ã‚°ç”¨å¤‰æ•°
	bool push_flag; // SPACE or BACK SPACE ç”¨ãƒ•ãƒ©ã‚°
	bool game_flag; // true ã§ã‚¹ã‚¿ãƒ¼ãƒˆã™ã‚‹
	bool boss_flag; // Boss ãƒ•ãƒ©ã‚°
	bool space_flag; // PUSH SPACE ãƒ•ãƒ©ã‚°

	// ã‚¹ã‚³ã‚¢è¨˜éŒ²ç”¨å¤‰æ•°
	int high_score; // ãƒã‚¤ã‚¹ã‚³ã‚¢ï¼ˆhigh_score < now_score ã®å ´åˆï¼‰
	int now_score; // ã‚¹ã‚³ã‚¢ã«ç½®æ›
	int timer; // ã‚¿ã‚¤ãƒãƒ¼
	int now_time; // æ®‹ã‚Šæ™‚é–“ã‚’è¨˜éŒ²ã™ã‚‹
	int start_time; // ï¼‘s å˜ä½ã§è¨ˆæ¸¬ã™ã‚‹
	int limit_time; // åˆ¶é™æ™‚é–“
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

public:

	// ç”»é¢ç”¨å¤‰æ•°
	static const int WIDTH = 1200; // æ¨ªå¹…
	static const int HEIGHT = 600; // ç¸¦å¹…

<<<<<<< HEAD
	void ADD_list(ThingPointa&); // Thing ƒNƒ‰ƒX@ƒXƒ}[ƒgƒ|ƒCƒ“ƒ^‚ÉƒŠƒXƒgilistj‚ğ’Ç‰Á
	void ADD_score(int sc); // ƒXƒRƒA‚ğ’Ç‰Á
	bool PUSH_space(); // SPACE ‘€ì
	bool PUSH_back(); // BACK SPACE ‘€ì

	// ƒXƒRƒA‚Ì‹L˜^‚ğÀ‘•‚·‚éŠÖ”
	void LOAD_highscore(); // “Ç
	void SAVE_highscore(); // •Û‘¶

	void GAME_SET(); // İ’è
	void GAME_ALL(); // •ªŠò
	void GAME_TITLE(); // ƒ^ƒCƒgƒ‹‰æ–Ê
	void GAME_SELECT(); // ‘I‘ğ‰æ–Ê
	void GAME_PLAY(); // ƒvƒŒƒC‰æ–Ê
	void GAME_OVER(); // ƒI[ƒo[‰æ–Ê
	void GAME_CLEAR(); // ƒNƒŠƒA‰æ–Ê
	void GAME_END(); // I—¹
};

//-------------------------------------------------------------------------------------

Game* game; // Game ƒNƒ‰ƒX‚Ìƒƒ‚ƒŠ‚ğŠm•Û@À‘ÌiƒCƒ“ƒXƒ^ƒ“ƒXj‰»

//-------------------------------------------------------------------------------------
=======
	void ADD_list(ThingPointa&); // Thing ã‚¯ãƒ©ã‚¹ã€€ã‚¹ãƒãƒ¼ãƒˆãƒã‚¤ãƒ³ã‚¿ã«ãƒªã‚¹ãƒˆï¼ˆlistï¼‰ã‚’è¿½åŠ ã™ã‚‹
	void ADD_score(int sc); // ã‚¹ã‚³ã‚¢ã‚’è¿½åŠ ã™ã‚‹
	bool PUSH_space(); // SPACE æ“ä½œ
	bool PUSH_back(); // BACK SPACE æ“ä½œ

	// ã‚¹ã‚³ã‚¢ã®è¨˜éŒ²ã‚’å®Ÿè£…ã™ã‚‹é–¢æ•°
	void LOAD_highscore(); // ã‚¹ã‚³ã‚¢èª­è¾¼
	void SAVE_highscore(); // ã‚¹ã‚³ã‚¢ä¿å­˜

	void GAME_SET(); // åˆæœŸè¨­å®š
	void GAME_ALL(); // åˆ†å²

	void GAME_TITLE(); // ã‚¿ã‚¤ãƒˆãƒ«ç”»é¢
	void GAME_SELECT(); // æ“ä½œèª¬æ˜
	void GAME_PLAY(); // ãƒ—ãƒ¬ã‚¤ç”»é¢
	void GAME_OVER(); // ã‚ªãƒ¼ãƒãƒ¼ç”»é¢
	void GAME_CLEAR(); // ã‚¯ãƒªã‚¢ç”»é¢

	void GAME_END(); // çµ‚äº†
};

Game* game; // Game ã‚¯ãƒ©ã‚¹ã®ãƒ¡ãƒ¢ãƒªã‚’ç¢ºä¿ã—ã¦å®Ÿä½“ï¼ˆã‚¤ãƒ³ã‚¹ã‚¿ãƒ³ã‚¹ï¼‰åŒ–ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

// Thing ã‚¯ãƒ©ã‚¹ã®å®Ÿè£…
void Thing::remove() {

<<<<<<< HEAD
	remove_flag = true; // íœƒtƒ‰ƒO‚ğ true ‚É
=======
	remove_flag = true; // å‰Šé™¤ãƒ•ãƒ©ã‚°ã‚’ true ã«ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

Thing::Thing() {

<<<<<<< HEAD
	remove_flag = false; // íœƒtƒ‰ƒO‚ğ false ‚É
	pause_flag = false; // ƒ|[ƒYi‹x~jƒtƒ‰ƒO‚ğ false ‚É
=======
	remove_flag = false; // å‰Šé™¤ãƒ•ãƒ©ã‚°ã‚’ false ã«ã™ã‚‹
	pause_flag = false; // ãƒãƒ¼ã‚ºï¼ˆä¼‘æ­¢ï¼‰ãƒ•ãƒ©ã‚°ã‚’ false ã«ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Thing::SET_picture(const char* file_name, ThingType thing) {

<<<<<<< HEAD
	// loaded_picture ‚Í‚O‚Ìê‡@LoadGraph ‚ğÀ‘•
=======
	// loaded_picture ã¯ï¼ã®å ´åˆã€€LoadGraph ã‚’å®Ÿè£…ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (loaded_picture[thing] == 0) {

		loaded_picture[thing] = LoadGraph(file_name);
	}

<<<<<<< HEAD
	hit_w = m_w; // ‰¡•‚ğ hit_w ‚É
	hit_h = m_h; // c•‚ğ hit_ h ‚É
	hit_x = hit_y = 0; // ¶ãÀ•W‚ğ‚O‚É
=======
	hit_w = m_w; // æ¨ªå¹…ã€€å½“ãŸã‚Šåˆ¤å®šã«ç½®ã
	hit_h = m_h; // ç¸¦å¹…ã€€å½“ãŸã‚Šåˆ¤å®šã«ç½®ã
	hit_x = hit_y = 0; // å½“ãŸã‚Šåˆ¤å®šã€€å·¦ä¸Šåº§æ¨™ã‚’ï¼ã«ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Thing::SET_sound(const char* file_name, Sound sound) {

<<<<<<< HEAD
	// loaded_sound ‚Í‚O‚Ìê‡@LoadSoundMem ‚ğÀ‘•
=======
	// loaded_sound ã¯ï¼ã®å ´åˆã€€LoadSoundMem ã‚’å®Ÿè£…ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (loaded_sound[sound] == 0) {

		loaded_sound[sound] = LoadSoundMem(file_name);
	}
}

void Thing::SET_position(int position_x, int position_y) {

<<<<<<< HEAD
	m_x = position_x; // İ’è’l‚ğ m_xix À•Wj ‚É
	m_y = position_y; // İ’è’l‚ğ m_yiy À•Wj‚É
=======
	m_x = position_x; // è¨­å®šå€¤ã‚’ m_xï¼ˆx åº§æ¨™ï¼‰ ã«å…¥ã‚Œã‚‹
	m_y = position_y; // è¨­å®šå€¤ã‚’ m_yï¼ˆy åº§æ¨™ï¼‰ã«å…¥ã‚Œã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Thing::SET_hitarea(int h_x, int h_y, int h_w, int h_h) {

<<<<<<< HEAD
	hit_x = h_x; // ‘Š‘Î“I x À•W‚ğİ’è
	hit_y = h_y; // ‘Š‘Î“I y À•W‚ğİ’è
	hit_w = h_w; // ‰¡•‚ğİ’è
	hit_h = h_h; // c•‚ğİ’è
=======
	hit_x = h_x; // ç›¸å¯¾çš„ x åº§æ¨™ã‚’è¨­å®šã™ã‚‹
	hit_y = h_y; // ç›¸å¯¾çš„ y åº§æ¨™ã‚’è¨­å®šã™ã‚‹
	hit_w = h_w; // æ¨ªå¹…ã‚’è¨­å®šã™ã‚‹
	hit_h = h_h; // ç¸¦å¹…ã‚’è¨­å®šã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

bool Thing::GET_remove() {

	return remove_flag;
}

ThingType Thing::HIT_TYPE() {

	return TYPE_NONE;
}

void Thing::draw() {

<<<<<<< HEAD
	// ¶ã(m_x, m_y)					‰Eã(m_x + m_w, m_y)
	// ¶‰º(m_x, m_y + m_h)		‰E‰º(m_x + m_w, m_y + m_h)
	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[GET_TYPE()], TRUE); // TRUE ‚Í‰æ‘œ‚Ì–³F‚ğƒNƒŠƒA‚É
=======
	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[GET_TYPE()], TRUE); // åº§æ¨™ä½ç½®ã«æç”»ã™ã‚‹ã€€TRUE ã¯ç”»åƒãƒãƒƒã‚¯ã‚’ã‚¯ãƒªã‚¢ã«ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Thing::life_draw() {

	if (0 < life_now) {

		DrawExtendGraph(m_x, m_y - 15, m_x + 65, m_y - 10, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(m_x, m_y - 15, m_x + (65 * life_now) / life_max, m_y - 10, loaded_picture[TYPE_LIFE], TRUE); // ä½“åŠ›ã®å€¤ã§å·¦ã¸ãšã‚Œã‚‹
	}
}

int Thing::GET_damage() {

	return damage;
}

int Thing::GET_energy() {

	return energy;
}

bool Thing::HIT_test(ThingPointa& other) {

<<<<<<< HEAD
	// ‰æ‘œ“¯m‚Ì“–‚½‚è”»’èÀ•W
	int x_1 = m_x + hit_x; // x À•W
	int y_1 = m_y + hit_y; // y À•W
	int w_1 = hit_w; // ‰¡•
	int h_1 = hit_h; // c•

	// ‘Î‰‚·‚é“–‚½‚è”»’èÀ•W
	int x_2 = other->m_x + other->hit_x; // x À•W
	int y_2 = other->m_y + other->hit_y; // y À•W
	int w_2 = other->hit_w; // ‰¡•
	int h_2 = other->hit_h; // c•

	// “–‚½‚è”»’è
=======
	// ç”»åƒåŒå£«ã®å½“ãŸã‚Šåˆ¤å®š
	int x_1 = m_x + hit_x; // å½“ãŸã‚Šåˆ¤å®šï¼ˆx åº§æ¨™ï¼‰
	int y_1 = m_y + hit_y; // å½“ãŸã‚Šåˆ¤å®šï¼ˆy åº§æ¨™ï¼‰
	int w_1 = hit_w; // å½“ãŸã‚Šåˆ¤å®šï¼ˆæ¨ªå¹…ï¼‰
	int h_1 = hit_h; // å½“ãŸã‚Šåˆ¤å®šï¼ˆç¸¦å¹…ï¼‰

	int x_2 = other->m_x + other->hit_x; // å¯¾å¿œã™ã‚‹å½“ãŸã‚Šåˆ¤å®šï¼ˆx åº§æ¨™ï¼‰
	int y_2 = other->m_y + other->hit_y; // å¯¾å¿œã™ã‚‹å½“ãŸã‚Šåˆ¤å®šï¼ˆy åº§æ¨™ï¼‰
	int w_2 = other->hit_w; // å¯¾å¿œã™ã‚‹å½“ãŸã‚Šåˆ¤å®šï¼ˆæ¨ªå¹…ï¼‰
	int h_2 = other->hit_h; // å¯¾å¿œã™ã‚‹å½“ãŸã‚Šåˆ¤å®šï¼ˆç¸¦å¹…ï¼‰

	// å½“ãŸã‚Šåˆ¤å®šã®è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (x_2 < x_1 + w_1 &&
		x_1 < x_2 + w_2 &&
		y_2 < y_1 + h_1 &&
		y_1 < y_2 + h_2) return true;

	return false; // ä¸Šè¨˜ä»¥å¤–ã¯ false ã«
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Player ƒNƒ‰ƒX‚ÌÀ‘•
=======
// Player ã‚¯ãƒ©ã‚¹ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Player::Player() {

	m_w = 80; // æ¨ªå¹…
	m_h = 50; // ç¸¦å¹…
	m_s = 8; // é€Ÿåº¦

<<<<<<< HEAD
	// ‰æ‘œ‚ğİ’è
=======
	// ç”»åƒã‚’è¨­å®šã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	SET_picture("PLAYER.png", TYPE_PLAYER);
	SET_picture("HEART.png", TYPE_HEART);
	SET_picture("ENERGY.png", TYPE_ENERGY);

<<<<<<< HEAD
	SET_position(150, 300); // xEy À•W‚ğİ’è
	SET_hitarea(10, 10, 70, 40); // “–‚½‚è”»’è‚ğİ’è
	life_max = 5; // ƒ‰ƒCƒt‚ğİ’è
	life_now = life_max; // ƒ‰ƒCƒt‚Ì’l‚ğİ’èƒ‰ƒCƒt‚É
	energy_max = 1; // “Áê—Í‚ğİ’è
	energy_now = energy_max; // “Áê—Í‚Ì’l‚ğİ’è“Áê—Í‚É
	damage = 0; // ‘¹ŠQ—Ê
	energy = 0; // “Áê—Ê
	shot_flag = false; // shot ƒtƒ‰ƒO‚ğ false ‚É
	beam_flag = false; // beam ƒtƒ‰ƒO‚ğ false ‚É
	dead_time = 0; // deat_time ‚ğ‚O‚É
	SET_sound("SHOT1.mp3", SOUND_SHOT1); // Shot ‰¹
	SET_sound("E ATTACK.mp3", SOUND_E_ATTACK); // ‘¹ŠQ‰¹
=======
	SET_position(150, 300); // xãƒ»y åº§æ¨™ã‚’è¨­å®šã™ã‚‹
	SET_hitarea(10, 10, 70, 40); // å½“ãŸã‚Šåˆ¤å®šã‚’è¨­å®šã™ã‚‹
	life_max = 5; // åˆæœŸãƒ©ã‚¤ãƒ•ã‚’è¨­å®šã™ã‚‹
	life_now = life_max; // ä»Šã®ãƒ©ã‚¤ãƒ•ã«åˆæœŸãƒ©ã‚¤ãƒ•ã‚’ç½®ã
	energy_max = 1; // åˆæœŸç‰¹æ®ŠåŠ›ã‚’è¨­å®šã™ã‚‹
	energy_now = energy_max; // ä»Šã®ç‰¹æ®ŠåŠ›ã«åˆæœŸç‰¹æ®ŠåŠ›ã‚’ç½®ã
	damage = 0; // æå®³é‡
	energy = 0; // ç‰¹æ®Šé‡
	shot_flag = false; // shot ãƒ•ãƒ©ã‚°ã‚’ false ã«ã™ã‚‹
	beam_flag = false; // beam ãƒ•ãƒ©ã‚°ã‚’ false ã«ã™ã‚‹
	dead_time = 0; // deat_time ã‚’ï¼ã«è¨­å®šï¼ˆç‚¹æ»…ç”¨ï¼‰
	SET_sound("SHOT1.mp3", SOUND_SHOT1); // Shot éŸ³
	SET_sound("E ATTACK.mp3", SOUND_E_ATTACK); // æå®³éŸ³
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

ThingType Player::HIT_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Player::GET_TYPE() {

	return TYPE_PLAYER;
}

void Player::move() {

	// ç‚¹æ»…ã‚¨ãƒ•ã‚§ã‚¯ãƒˆã€€ãƒã‚¤ãƒŠã‚¹ã™ã‚‹
	if (0 < dead_time) dead_time--;

	// ãƒãƒ¼ã‚ºï¼ˆä¼‘æ­¢ï¼‰ãƒ•ãƒ©ã‚° false ã®å ´åˆ
	if (!pause_flag) {

		// chage_time = 0 ãã—ã¦ beam ãƒ•ãƒ©ã‚° false ã®å ´åˆ
		if (charge_time == 0 && !beam_flag) {

			// å¤‰ä½è¨­å®š
			if (CheckHitKey(KEY_INPUT_LEFT)) m_x -= m_s; // â†å·¦
			if (CheckHitKey(KEY_INPUT_RIGHT)) m_x += m_s; // â†’å³
			if (CheckHitKey(KEY_INPUT_UP)) m_y -= m_s; // â†‘ä¸Š
			if (CheckHitKey(KEY_INPUT_DOWN)) m_y += m_s; // â†“ä¸‹

			// ç”»é¢ã®å½“ãŸã‚Šåˆ¤å®š
			if (m_x < 0) m_x = 0; // ç”»é¢å·¦
			if (Game::WIDTH < m_x + m_w) m_x = Game::WIDTH - m_w; // ç”»é¢å³
			if (m_y < 0) m_y = 0; // ç”»é¢ä¸Š
			if (Game::HEIGHT < m_y + m_h) m_y = Game::HEIGHT - m_h; // ç”»é¢ä¸‹
		}

		// é€šå¸¸å¼¾ï¼ˆï¼¢ï¼‰
		if (CheckHitKey(KEY_INPUT_B) && shot_count % 8 == 0) {

			if (!shot_flag) { // shot ãƒ•ãƒ©ã‚° false ã®å ´åˆ

<<<<<<< HEAD
				ThingPointa shot(new Shot); // Shot ƒNƒ‰ƒXì¬@‚»‚ÌƒAƒhƒŒƒX‚ğ Thing ƒNƒ‰ƒX‚ÌƒXƒ}[ƒgƒ|ƒCƒ“ƒ^‚É“n‚·
				shot->SET_position(m_x + m_w - 10, m_y + 25); // Shot ‚ÌÀ•W‚ğİ’è
				game->ADD_list(shot); // Thing ƒŠƒXƒg‚É Shot ƒAƒhƒŒƒX‚ğ’Ç‰Á
				PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK); // Shot ‰¹
=======
				ThingPointa shot(new Shot); // Shot ã‚¯ãƒ©ã‚¹ä½œæˆã€€ãã®ã‚¢ãƒ‰ãƒ¬ã‚¹ã‚’ Thing ã‚¯ãƒ©ã‚¹ã®ã‚¹ãƒãƒ¼ãƒˆãƒã‚¤ãƒ³ã‚¿ã«æ¸¡ã™
				shot->SET_position(m_x + m_w - 10, m_y + 25); // Shot ã®åˆæœŸä½ç½®ã‚’è¨­å®šã™ã‚‹
				game->ADD_list(shot); // Thing ãƒªã‚¹ãƒˆã« Shot ã‚¢ãƒ‰ãƒ¬ã‚¹ã‚’è¿½åŠ ã™ã‚‹
				PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK); // Shot éŸ³
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			}
		}

		// è²«é€šå¼¾ï¼ˆï¼´ï¼‰
		else if (CheckHitKey(KEY_INPUT_T) && shot_count % 10 == 0) {

			// ç‰¹æ®Šé‡ï¼”ä»¥ä¸Šã®å ´åˆã€€ç™ºå°„å¯
			if (4 <= energy_now) {

				if (!shot_flag) {

					ThingPointa through_shot(new Through_Shot);
					through_shot->SET_position(m_x + m_w - 30, m_y + 25);
					game->ADD_list(through_shot);
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);
				}
			}
		}

		// å…‰ç·šï¼ˆï¼£ï¼‰
		else if (CheckHitKey(KEY_INPUT_C)) {

			// ç‰¹æ®Šé‡ï¼•ä»¥ä¸Šã®å ´åˆã€€ç™ºå°„å¯
			if (5 <= energy_now) {

				if (!beam_flag) { // beam ãƒ•ãƒ©ã‚° false ã®å ´åˆ

					ThingPointa beam(new Beam);
					beam->SET_position(m_x + m_w + 15, m_y - 10);
					game->ADD_list(beam);
					beam_flag = true; // é€£æ‰“ä»•æ§˜
					PlaySoundMem(loaded_sound[SOUND_BEAM], DX_PLAYTYPE_BACK);
				}
			}
		}

		// æ¸¦å¼¾ï¼ˆï¼¶ï¼‰
		else if (CheckHitKey(KEY_INPUT_V) && shot_count % 6 == 0) {

			// ç‰¹æ®Šé‡ï¼“ä»¥ä¸Šã®å ´åˆã€€ç™ºå°„å¯
			if (3 <= energy_now) {

				if (!shot_flag) {

					ThingPointa vortex_shot(new Vortex_Shot);
					vortex_shot->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(vortex_shot);
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);
				}
			}
		}

		// æ•£å¸ƒå¼¾ï¼ˆï¼³ï¼‰
		else if (CheckHitKey(KEY_INPUT_S) && shot_count % 10 == 0) {

			// ç‰¹æ®Šé‡ï¼™ä»¥ä¸Šã®å ´åˆã€€ç™ºå°„å¯
			if (9 <= energy_now) {

				if (!shot_flag) {

<<<<<<< HEAD
					for (int i = 0; i < 7; i++) { // ‚V”­

						ThingPointa spray_shot1(new Spray_Shot);
						spray_shot1->SET_position(m_x + m_w - 10, m_y + 25);
						spray_shot1->SET_angle(3.14 * (3 - i) / 18); // U•z‚·‚éŠp“xi‚R‚O‹E‚Q‚O‹E‚P‚O‹E‚O‹j‚ğã‰º‚Éİ’è
=======
					for (int i = 0; i < 7; i++) { // ï¼—å€‹ç™ºå°„ã™ã‚‹

						ThingPointa spray_shot1(new Spray_Shot);
						spray_shot1->SET_position(m_x + m_w - 10, m_y + 25);
						spray_shot1->SET_angle(3.14 * (3 - i) / 18); // æ•£å¸ƒã™ã‚‹è§’åº¦ï¼ˆï¼“ï¼Â°ãƒ»ï¼’ï¼Â°ãƒ»ï¼‘ï¼Â°ãƒ»ï¼Â°ï¼‰ã‚’ä¸Šä¸‹ã«è¨­å®šã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
						game->ADD_list(spray_shot1);
					}

					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK); // Shot éŸ³
				}
			}
		}

		// èºæ—‹å¼¾ï¼ˆï¼²ï¼‰
		else if (CheckHitKey(KEY_INPUT_R) && shot_count % 4 == 0) {

			// ç‰¹æ®Šé‡ï¼‘ï¼ã®å ´åˆã€€ç™ºå°„å¯
			if (10 <= energy_now) {

				if (!shot_flag) {

					// ä¸Š
					ThingPointa rasen_Shot_1(new Rasen_Shot);
					rasen_Shot_1->SET_position(m_x + m_w - 10, m_y + 25);
					rasen_Shot_1->SET_sign(1); // ƒvƒ‰ƒX‚É
					game->ADD_list(rasen_Shot_1);

					// ä¸‹
					ThingPointa rasen_Shot_2(new Rasen_Shot);
					rasen_Shot_2->SET_position(m_x + m_w - 10, m_y + 25);
					rasen_Shot_2->SET_sign(-1); // ƒ}ƒCƒiƒX‚É
					game->ADD_list(rasen_Shot_2);
					PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
				}
			}
		}

		// æ‹¡å¤§å¼¾ï¼ˆï¼¯ï¼‰
		else if (CheckHitKey(KEY_INPUT_O)) {

			// ç‰¹æ®Šé‡ï¼’ä»¥ä¸Šã®å ´åˆã€€ç™ºå°„å¯
			if (2 <= energy_now) {

				// ç™ºå°„æº–å‚™æ™‚é–“
				if (charge_time <= 5) charge_time++;

				if (charge_time == 5) {

					ThingPointa charge_shot(new Charge_Shot);
					charge_shot->SET_position(m_x + m_w + 15, m_y + 35);
					game->ADD_list(charge_shot);
					PlaySoundMem(loaded_sound[SOUND_CHARGE], DX_PLAYTYPE_BACK);
				}
			}
		}

		// æ™‚é™å¼¾ï¼ˆï¼ºï¼‰
		else if (CheckHitKey(KEY_INPUT_Z)) {

			// ç‰¹æ®Šé‡ï¼˜ä»¥ä¸Šã®å ´åˆã€€ç™ºå°„å¯
			if (8 <= energy_now) {

				if (!shot_flag) {

					ThingPointa period_shot1(new Period_Shot1);
					period_shot1->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(period_shot1);
					shot_flag = true; // é€£æ‰“ä»•æ§˜
					PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
				}
			}
		}

		// è¿½å°¾å¼¾ï¼ˆï¼¨ï¼‰
		else if (CheckHitKey(KEY_INPUT_H) && shot_count % 28 == 0) {

			// ç‰¹æ®Šé‡ï¼—ä»¥ä¸Šã®å ´åˆã€€ç™ºå°„å¯
			if (7 <= energy_now) {

				// æ®‹ã‚‹æ•µâ—¯ã®å ´åˆ
				if (0 < enemy_num) {

					if (!shot_flag) {

						ThingPointa homing_shot(new Homing_Shot);
						homing_shot->SET_position(m_x + m_w - 10, m_y + 25);
						game->ADD_list(homing_shot);
						PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
					}
				}
			}
		}

<<<<<<< HEAD
		// •ú•¨ü’ei‚oj
=======
		// è¿½å°¾ãƒ»æ”¾ç‰©ç·šå¼¾ï¼ˆï¼°ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		else if (CheckHitKey(KEY_INPUT_P) && shot_count % 28 == 0) {

			// ç‰¹æ®Šé‡ï¼–ä»¥ä¸Šã®å ´åˆã€€ç™ºå°„å¯
			if (6 <= energy_now) {

				// æ®‹ã‚‹æ•µâ—¯ã®å ´åˆ
				if (0 < enemy_num) {

					if (!shot_flag) {

						ThingPointa parabola_shot(new Parabola_Shot);
						parabola_shot->SET_position(m_x + m_w - 10, m_y + 25);
						game->ADD_list(parabola_shot);
						PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
					}
				}
			}
		}

<<<<<<< HEAD
		// ‘S‚Ä‚Ì’e‚ğg—p‰Â‚É
=======
		// å…¨ã¦ã®å¼¾ã‚’ä½¿ç”¨å¯ã«ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		else if (CheckHitKey(KEY_INPUT_Q)) energy_now = 10;

		else {

			shot_flag = false; // shot ãƒ•ãƒ©ã‚°ã‚’ falseã«
			beam_flag = false; // beam ãƒ•ãƒ©ã‚° ã‚’ false ã«
			charge_time = 0; // charge_time ã‚’ï¼ã«
		}
	}

<<<<<<< HEAD
	// ƒ‰ƒCƒt‚O‚Ìê‡
	if (life_now <= 0) {

		scene = 3; // ƒI[ƒo[‰æ–Ê‚Ö
		StopSoundMem(Play_m); // ƒvƒŒƒC‰æ–Ê‚Ì‰¹‚ğ’â~
		StopSoundMem(Boss_m); // ƒ{ƒX‰æ–Ê‚Ì‰¹‚ğ’â~
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // ƒI[ƒo[‰æ–Ê‚Ì‰¹‚ğÄ¶
=======
	// ãƒ©ã‚¤ãƒ•ï¼ã«ãªã£ãŸå ´åˆ
	if (life_now <= 0) {

		scene = 3; // ã‚ªãƒ¼ãƒãƒ¼ç”»é¢ã¸
		StopSoundMem(Play_m); // ãƒ—ãƒ¬ã‚¤ä¸­ã®éŸ³ã‚’åœæ­¢ã™ã‚‹
		StopSoundMem(Boss_m); // ãƒœã‚¹ä¸­ã®éŸ³ã‚’åœæ­¢ã™ã‚‹
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // ã‚ªãƒ¼ãƒãƒ¼ä¸­ã®éŸ³ã‚’å†ç”Ÿã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	}

	// ãƒ©ã‚¤ãƒ•ã®ä¸Šé™è¨­å®š
	if (10 <= life_now) life_now = 10;

	// ç‰¹æ®Šé‡ã®ä¸Šé™è¨­å®š
	if (10 <= energy_now) energy_now = 10;
}

void Player::heart_draw() {

	if (0 < life_now) {

<<<<<<< HEAD
		// ‘Ì—Í‚Ì’l‚Åƒn[ƒg‚Ì”‚ğ’²®
=======
		// ä»Šã®ä½“åŠ›ã«ã‚ˆã‚Šãƒãƒ¼ãƒˆã®æ•°ã‚’èª¿æ•´ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		for (int i = 0; i < life_now; i++) {

			DrawExtendGraph(5 + i * 45, 5, 55 + i * 45, 45, loaded_picture[TYPE_HEART], TRUE);
		}
	}
}

void Player::energy_draw() {

	if (0 < energy_now) {

<<<<<<< HEAD
		// “Áê—Ê‚Ì’l‚Åƒn[ƒg‚Ì”‚ğ’²®
=======
		// ä»Šã®ç‰¹æ®Šé‡ã«ã‚ˆã‚Šãƒãƒ¼ãƒˆã®æ•°ã‚’èª¿æ•´ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		for (int i = 0; i < energy_now; i++) {

			DrawExtendGraph(460 + i * 45, 5, 510 + i * 45, 45, loaded_picture[TYPE_ENERGY], TRUE);
		}
	}

<<<<<<< HEAD
	// “Áê—Ê‚Ì’l‚Åiƒn[ƒg‚Ìã‚Éj•¶š‚ğ•`‰æ
	int color = GetColor(255, 255, 255); // F‚ğİ’è

	DrawFormatString(480, 15, color, "B");
	// “Áê—Ê‚Q`‚P‚OˆÈã‚Ìê‡
	if (2   <= energy_now) DrawFormatString(525, 15, color, "O");
	if (3   <= energy_now) DrawFormatString(570, 15, color, "V");
	if (4   <= energy_now) DrawFormatString(615, 15, color, "T");
	if (5   <= energy_now) DrawFormatString(660, 15, color, "C");
	if (6   <= energy_now) DrawFormatString(705, 15, color, "P");
	if (7   <= energy_now) DrawFormatString(750, 15, color, "H");
	if (8   <= energy_now) DrawFormatString(795, 15, color, "Z");
	if (9   <= energy_now) DrawFormatString(840, 15, color, "S");
	if (10 <= energy_now) DrawFormatString(885, 15, color, "R");
=======
	// ä»Šã®ç‰¹æ®Šé‡ã«ã‚ˆã‚Šï¼ˆãƒãƒ¼ãƒˆã®ä¸Šã«ï¼‰æ–‡å­—ã‚’æç”»ã™ã‚‹
	int color = GetColor(255, 255, 255); // è‰²
	DrawFormatString(480, 15, color, "B");

	// ç‰¹æ®Šé‡ï¼’ï½ï¼‘ï¼ä»¥ä¸Šã®å ´åˆ
	if (2 <= energy_now) {
		DrawFormatString(525, 15, color, "O");
	}

	if (3 <= energy_now) {
		DrawFormatString(570, 15, color, "V");
	}

	if (4 <= energy_now) {
		DrawFormatString(615, 15, color, "M");
	}

	if (5 <= energy_now) {
		DrawFormatString(660, 15, color, "C");
	}

	if (6 <= energy_now) {
		DrawFormatString(705, 15, color, "P");
	}

	if (7 <= energy_now) {
		DrawFormatString(750, 15, color, "H");
	}

	if (8 <= energy_now) {
		DrawFormatString(795, 15, color, "Z");
	}

	if (9 <= energy_now) {
		DrawFormatString(840, 15, color, "S");
	}

	if (10 <= energy_now) {
		DrawFormatString(885, 15, color, "R");
	}
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Player::draw() {

<<<<<<< HEAD
	heart_draw(); // ‘Ì—Í‚ğ•`‰æ
	energy_draw(); // “Áê—Ê‚ğ•`‰æ

	if (dead_time % 5 == 0) Thing::draw(); // ‚T‚ÅŠ„‚èØ‚ê‚éê‡@“_–Å‚Å•`‰æ
=======
	heart_draw(); // ä½“åŠ›ã‚’æç”»ã™ã‚‹
	energy_draw(); // ç‰¹æ®Šé‡ã‚’æç”»ã™ã‚‹

	if (dead_time % 5 == 0) Thing::draw(); // ï¼•ã§å‰²ã‚Šåˆ‡ã‚Œã‚‹å ´åˆã€€ç‚¹æ»…ã—ã¦æç”»ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Player::hit(int damage, int energy) {

	// æ•µã®å ´åˆ
	if (dead_time <= 0 && 0 < damage) {

<<<<<<< HEAD
		dead_time = 50; // dead_time ‚ğ‚T‚O‚É
		life_now -= damage; // ‘Ì—Í‚ğƒ}ƒCƒiƒX‚·‚é
		PlaySoundMem(loaded_sound[SOUND_E_ATTACK], DX_PLAYTYPE_BACK); // ‘¹ŠQ‰¹
	}

	// HEAL1 ‚Ìê‡
	if (damage < 0) life_now -= damage; // ‘Ì—Í‚Ì’Ç‰Á

	// HEAL2 ‚Ìê‡
	if (energy < 0) energy_now -= energy; // “Áê—Ê‚Ì’Ç‰Á
}

//-------------------------------------------------------------------------------------

// Shot ƒNƒ‰ƒXi’Êí’ej‚ÌÀ‘•
Shot::Shot() {

	m_w = 12; // ‰¡•
	m_h = 12; // c•
	m_s = 10; // ‘¬“x
	damage = 5; // ‘¹ŠQ—Ê
	SET_picture("SHOT1.png", TYPE_SHOT1); // ‰æ‘œ
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK); // ‰¹
=======
		dead_time = 50; // ç‚¹æ»…ã‚«ã‚¦ãƒ³ãƒˆã‚’ï¼•ï¼ã«
		life_now -= damage; // ä½“åŠ›ã‚’ãƒã‚¤ãƒŠã‚¹ã™ã‚‹
		PlaySoundMem(loaded_sound[SOUND_E_ATTACK], DX_PLAYTYPE_BACK); // æå®³éŸ³
	}

	// HEAL1 ã®å ´åˆ
	if (damage < 0) life_now -= damage; // ä½“åŠ›ã®å¢—åŠ 

	// HEAL2 ã®å ´åˆ
	if (energy < 0) energy_now -= energy; // ç‰¹æ®Šé‡ã®å¢—åŠ 
}

// Shot ã‚¯ãƒ©ã‚¹ï¼ˆé€šå¸¸å¼¾ï¼‰ã®å®Ÿè£…
Shot::Shot() {

	m_w = 12; // æ¨ªå¹…
	m_h = 12; // ç¸¦å¹…
	m_s = 10; // é€Ÿåº¦
	damage = 5; // æå®³é‡
	SET_picture("SHOT1.png", TYPE_SHOT1); // ç”»åƒ
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK); // åŠ¹æœéŸ³
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

ThingType Shot::GET_TYPE() {

	return TYPE_SHOT1;
}

ThingType Shot::HIT_TYPE() {

	return TYPE_ENEMY1;
}

void Shot::move() {

<<<<<<< HEAD
	if (!pause_flag) m_x += m_s; // ‘¬“x‚ğ‚P‚O‚É

	if (Game::WIDTH < m_x) remove(); // ‰æ–Ê¶‚Åíœ
=======
	if (!pause_flag) m_x += m_s; // é€Ÿåº¦ã‚’ï¼‘ï¼ã«ã™ã‚‹

	if (Game::WIDTH < m_x) remove(); // ç”»é¢å·¦ã§å‰Šé™¤ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT1], TRUE);
}

void Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Through Shot ƒNƒ‰ƒXiŠÑ’Ê’ej‚ÌÀ‘•
=======
// Through Shot ã‚¯ãƒ©ã‚¹ï¼ˆè²«é€šå¼¾ï¼‰ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Through_Shot::Through_Shot() {

	m_w = 34;
	m_h = 15;
	m_s = 20;
	damage = 1;
	SET_picture("SHOT2.png", TYPE_SHOT2);
	SET_sound("SHOT2.mp3", SOUND_SHOT2);
}

void Through_Shot::move() {

<<<<<<< HEAD
	if (!pause_flag) m_x += m_s; // ‘¬“x‚ğ‚Q‚O‚É
=======
	if (!pause_flag) m_x += m_s; // é€Ÿåº¦ã‚’ï¼’ï¼ã«ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	if (Game::WIDTH < m_x + m_w) remove();
}

void Through_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Through_Shot::hit(int damage, int energy) {

<<<<<<< HEAD
	// ŠÑ’Ê‚·‚éˆ× remove ŠÖ”‚ÍÀ‘•~
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Beam ƒNƒ‰ƒXiŒõüj‚ÌÀ‘•
Beam::Beam() {

	m_w = 0; // L’·‚·‚éˆ×‚O‚É
=======
	// è²«é€šã™ã‚‹ç‚º remove()é–¢æ•°ã¯å®Ÿè£…ã—ãªã„
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// Beam ã‚¯ãƒ©ã‚¹ï¼ˆå…‰ç·šï¼‰ã®å®Ÿè£…
Beam::Beam() {

	m_w = 0; // åˆæœŸã¯ï¼ã«
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	m_h = 80;
	m_s = 15;
	damage = 1;
	SET_picture("BEAM.png", TYPE_BEAM);
	SET_sound("BEAM.mp3", SOUND_BEAM);
}

void Beam::move() {

	if (!pause_flag) {

		m_w += m_s;
<<<<<<< HEAD
		hit_w = m_w; // ‰¡•‚ğ“–‚½‚è”»’è‚É
=======
		hit_w = m_w; // å½“ãŸã‚Šåˆ¤å®šã«ç½®æ›ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	}

	if (Game::WIDTH + 100 < m_x + m_w) remove();
}

void Beam::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_BEAM], TRUE);
}

void Beam::hit(int damage, int energy) {

	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Vortex Shot ƒNƒ‰ƒXi‰Q’ej‚ÌÀ‘•
=======
// Vortex Shot ã‚¯ãƒ©ã‚¹ï¼ˆæ¸¦å¼¾ï¼‰ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Vortex_Shot::Vortex_Shot() {

	m_w = 34;
	m_h = 15;
	damage = 10;
	angle = 0; // è§’åº¦ã‚’ï¼ã«
	rad = 0; // åŠå¾„ã‚’ï¼ã«
}

void Vortex_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;
}

void Vortex_Shot::move() {

	if (!pause_flag) {

		rad += 0.8; // å††ã®åŠå¾„ã«ãƒ—ãƒ©ã‚¹ã™ã‚‹
		angle += 8 / rad; // è§’åº¦ã‚’ãƒ—ãƒ©ã‚¹ã™ã‚‹ï¼ˆè§’é€Ÿåº¦ã‚’èª¿æ•´ï¼‰

		// å›ã‚‹è¨ˆç®—
		m_x = center_x + (float)rad * cos(angle);
		m_y = center_y + (float)rad * sin(angle);
	}

	if (Game::WIDTH < m_x) remove();
}

void Vortex_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Vortex_Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Spray Shot ƒNƒ‰ƒXiU•z’ej‚ÌÀ‘•
=======
// Spray Shot ã‚¯ãƒ©ã‚¹ï¼ˆæ•£å¸ƒå¼¾ï¼‰ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Spray_Shot::Spray_Shot() {

	m_w = 34;
	m_h = 15;
	m_s = 10;
	damage = 5;
	angle = 0;
}

void Spray_Shot::SET_angle(float a) {

<<<<<<< HEAD
	angle = a; // ˆø”‚ğŠp“x‚É
=======
	angle = a; // è§’åº¦ã«ç½®ã
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Spray_Shot::move() {

	if (!pause_flag) {

		m_x += m_s * cos(angle);
		m_y += m_s * sin(angle);
	}
	if (Game::WIDTH < m_x) remove();
}

void Spray_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Spray_Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Rasen Shot1E2 ƒNƒ‰ƒXi—†ù’ej‚ÌÀ‘•
=======
// Rasen Shot1ãƒ»2 ã‚¯ãƒ©ã‚¹ï¼ˆèºæ—‹å¼¾ï¼‰ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Rasen_Shot::Rasen_Shot() {

	m_w = 12;
	m_h = 12;
	m_s = 8;
	damage = 1;
	angle = 0; // è§’åº¦ã‚’ï¼ã«
	sign = 0;
}

void Rasen_Shot::SET_position(int position_x, int position_y) {

	m_x = position_x;
	center_y = position_y;
}

void Rasen_Shot::SET_sign(int s) {

<<<<<<< HEAD
	sign = s; // ˆø”‚ğ•„†‚É
=======
	sign = s; // ç¬¦å·ã«ç½®ã
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Rasen_Shot::move() {

	if (!pause_flag) {

		angle += 0.2;
		m_x += m_s;
		m_y = center_y - sign * 60 * sin(angle); // ã‚µã‚¤ãƒ³ã‚«ãƒ¼ãƒ–ã®å¿œç”¨
	}

	if (Game::WIDTH < m_x) remove();
}

void Rasen_Shot::draw() {

<<<<<<< HEAD
	// —§‘Ì“I‚É•`‰æ
=======
	// å¤§ãã•ã‚’éšæ™‚å¤‰æ›´ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	DrawExtendGraph(m_x, m_y, m_x + m_w * (1.2 - sign * cos(angle)) / 2, m_y + m_h * (1.2 - sign * cos(angle)) / 2, loaded_picture[TYPE_SHOT1], TRUE);
}

void Rasen_Shot::hit(int damage, int energy) {

	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Charge Shot ƒNƒ‰ƒXiŠg‘å’ej‚ÌÀ‘•
=======
// Charge Shot ã‚¯ãƒ©ã‚¹ï¼ˆæ‹¡å¤§å¼¾ï¼‰ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Charge_Shot::Charge_Shot() {

	m_w = 0;
	m_h = 0;
	m_s = 15;
	damage = 0;
	SET_picture("CHARGE SHOT.png", TYPE_CHARGE_SHOT);
	SET_sound("CHARGE.mp3", SOUND_CHARGE); // CHARGE ä¸­ã®éŸ³
	SET_sound("CHARGE SHOT.mp3", SOUND_CHARGE_SHOT); // ç™ºå°„éŸ³
	charge_flag = false; // charge ãƒ•ãƒ©ã‚°ã‚’ false ã«
}

void Charge_Shot::move() {

	if (!charge_flag) {

		// u‚nv‚ğ‰Ÿ‚·ê‡
		if (CheckHitKey(KEY_INPUT_O)) {

<<<<<<< HEAD
			// ˆĞ—Í§ŒÀ‚ğ‚T‚O‚Éi‘¹ŠQ—Ê‚Í‚O‚É‚µ‚Ä‚¢‚éˆ×j
=======
			// ã‚¢ã‚¿ãƒƒã‚¯MAXã‚’ï¼•ï¼ã«ã™ã‚‹ï¼ˆåˆæœŸæå®³é‡ã¯ï¼ã«ã—ã¦ã„ã‚‹ãŸã‚ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			if (damage < 50) {

				damage++;

				m_x += 1;
				m_y -= 2;
<<<<<<< HEAD
				m_w = 2 * damage; // ‘¹ŠQ—Ê‚É”º‚¢Šg‘å
				m_h = 4 * damage;

				// “–‚½‚è”»’è‚ÌŒë·’ù³
=======
				m_w = 2 * damage; // æå®³é‡ã«ä¼´ã„å¤§ãããªã‚‹
				m_h = 4 * damage;

				// å½“ãŸã‚Šåˆ¤å®šã®èª¤å·®è¨‚æ­£ã‚’ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				hit_w = m_w + 20;
				hit_h = m_h;
			}

			// æå®³é‡ï¼•ï¼æœªæº€ã®å ´åˆ
			else {

				charge_flag = true;
				StopSoundMem(loaded_sound[SOUND_CHARGE]);
				PlaySoundMem(loaded_sound[SOUND_CHARGE_SHOT], DX_PLAYTYPE_BACK);
			}
		}

<<<<<<< HEAD
=======
		// ã€Œï¼¯ã€ã‚’æŠ¼ã—ã¦ã„ãªã„å ´åˆ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		else {

			charge_flag = true;
			StopSoundMem(loaded_sound[SOUND_CHARGE]);
			PlaySoundMem(loaded_sound[SOUND_CHARGE_SHOT], DX_PLAYTYPE_BACK);
		}
	}

<<<<<<< HEAD
	else if (!pause_flag) m_x += m_s; // ‘¬“x‚ğ‚P‚T‚É
=======
	else if (!pause_flag) m_x += m_s; // é€Ÿåº¦ã‚’ï¼‘ï¼•ã«ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	if (Game::WIDTH < m_x) remove();
}

void Charge_Shot::draw() {

<<<<<<< HEAD
	// angle ‚Ì’l‚ğ‚Q‚ÅŠ„‚èØ‚ê‚éê‡@•`‰æ
=======
	// angle ã®å€¤ã‚’ï¼’ã§å‰²ã‚Š ä½™ã‚Šï¼å ´åˆã€€æç”»ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if ((int)angle % 2 == 0) {

		DrawRotaGraph((2 * m_x + m_w) / 2, (2 * m_y + m_h) / 2, (double)m_w / 50, angle, loaded_picture[TYPE_CHARGE_SHOT], TRUE);
	}

<<<<<<< HEAD
	if (!pause_flag) angle += 30; // angle ‚Ì’l‚É‚R‚Tƒvƒ‰ƒX‚·‚é
=======
	if (!pause_flag) angle += 30; // angle ã®å€¤ã«ï¼“ï¼•è¶³ã—ç¶šã‘ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Charge_Shot::hit(int damage, int energy) {

	remove();
	StopSoundMem(loaded_sound[SOUND_CHARGE]);
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot1 ƒNƒ‰ƒXiŒÀ’ej‚ÌÀ‘•
=======
// Period Shot1 ã‚¯ãƒ©ã‚¹ï¼ˆæ™‚é™å¼¾ï¼‰ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Period_Shot1::Period_Shot1() {

	m_w = 15;
	m_h = 15;
	m_s = 12;
	damage = 0;
<<<<<<< HEAD
	shot_time = 30; // ”­Ë‚Ü‚Å‚ÌŠÔ‚ğ‚R‚O‚É
	shot_count = 1; // ‚T‰ñ”­Ë‚·‚éˆ×‚P‚É
=======
	shot_time = 30; // ç™ºå°„ã™ã‚‹ã¾ã§ã®æ™‚é–“ã‚’ï¼“ï¼ã«
	shot_count = 1; // ï¼•å›ç™ºå°„ã™ã‚‹ãŸã‚ã« åˆæœŸã¯ï¼‘ã«
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	SET_picture("SHOT3.png", TYPE_SHOT3);
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK);
}

ThingType Period_Shot1::GET_TYPE() {

	return TYPE_SHOT3;
}

ThingType Period_Shot1::HIT_TYPE() {

<<<<<<< HEAD
	return TYPE_NONE; // –{‘Ì‚É“–‚½‚è”»’è~
=======
	return TYPE_NONE; // æœ¬ä½“ã«ã¯å½“ãŸã‚Šåˆ¤å®šÃ—
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Period_Shot1::move() {

	if (!pause_flag) {

<<<<<<< HEAD
		if (0 <= shot_time) m_x += m_s; // ”­Ë‚Ü‚Å‰E•ûŒü‚Ö
=======
		if (0 <= shot_time) m_x += m_s; // ç™ºå°„ã™ã‚‹ã¾ã§å³æ–¹å‘ã¸
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

		if (shot_time < 0) {

			// ï¼•å›ç™ºå°„
			if (shot_time % 10 == 0 && shot_count <= 5) {

<<<<<<< HEAD
				// “–‚½‚è”»’èü’e‚ğ”­Ë
				// ‰º•ûŒü
=======
				// å½“ãŸã‚Šåˆ¤å®šâ—¯ã€€å¼¾ã‚’ç™ºå°„ã™ã‚‹
				// ä¸‹æ–¹å‘
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				ThingPointa period_shot2(new Period_Shot2());
				game->ADD_list(period_shot2);
				period_shot2->SET_sign(1);
				period_shot2->SET_position(m_x + 1, m_y - 10);

				// å³æ–¹å‘
				ThingPointa period_shot3(new Period_Shot3());
				game->ADD_list(period_shot3);
				period_shot3->SET_sign(1);
				period_shot3->SET_position(m_x - 5, m_y + 2);

				// ä¸Šæ–¹å‘
				ThingPointa period_shot4(new Period_Shot2());
				game->ADD_list(period_shot4);
				period_shot4->SET_sign(-1);
				period_shot4->SET_position(m_x + 1, m_y - 10);

				// å·¦æ–¹å‘
				ThingPointa period_shot5(new Period_Shot3());
				game->ADD_list(period_shot5);
				period_shot5->SET_position(m_x - 12, m_y + 2);
				period_shot5->SET_sign(-1);
				PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);

				shot_count++;
			}

<<<<<<< HEAD
			if (5 < shot_count) remove(); // ‚T”­‚Åíœ
=======
			if (5 < shot_count) remove(); // ï¼•å›ç›®ã§å‰Šé™¤ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		}

		shot_time--;
	}
}

void Period_Shot1::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT3], TRUE);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------
=======
void Period_Shot1::hit(int damage, int energy) {} // å½“ãŸã‚Šåˆ¤å®šÃ—
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

// Period Shot2ï¼ˆä¸Šä¸‹ï¼‰ã‚¯ãƒ©ã‚¹ã®å®Ÿè£…
Period_Shot2::Period_Shot2() {

	m_w = 15;
	m_h = 34;
	m_s = 20;
	damage = 5;
	sign = 0;
	SET_picture("SHOT4.png", TYPE_SHOT4);
}

void Period_Shot2::SET_sign(int s) {

	sign = s;
}

void Period_Shot2::move() {

	if (!pause_flag) m_y += sign * m_s;

	if (m_y + m_h < 0 || Game::HEIGHT < m_y) remove();
}

void Period_Shot2::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT4], TRUE);
}

void Period_Shot2::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot3i¶‰EjƒNƒ‰ƒX‚ÌÀ‘•
=======
// Period Shot3ï¼ˆå·¦å³ï¼‰ã‚¯ãƒ©ã‚¹ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Period_Shot3::Period_Shot3() {

	m_w = 34;
	m_h = 15;
	m_s = 20;
	damage = 5;
	sign = 0;
}

void Period_Shot3::SET_sign(int s) {

	sign = s;
}

void Period_Shot3::move() {

	if (!pause_flag) m_x += sign * m_s;

	if (Game::WIDTH < m_x || m_x + m_w < 0) remove();
}

void Period_Shot3::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Period_Shot3::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Homing Shot ƒNƒ‰ƒXi’Ç”ö’ej‚ÌÀ‘•
=======
// Homing Shot ã‚¯ãƒ©ã‚¹ï¼ˆè¿½å°¾å¼¾ï¼‰ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Homing_Shot::Homing_Shot() {

	m_w = 12;
	m_h = 12;
	m_s = 10;
	damage = 20;
<<<<<<< HEAD
	shot_s = 10; // shot_s ‚ğ‚P‚O‚É
=======
	shot_s = 10; // shot_s ã‚’10ã«ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Homing_Shot::move() {

	if (!pause_flag) {

<<<<<<< HEAD
		// c‚é“Gü‚Ìê‡
		if (0 < enemy_num) {

			// ’Ç”ö‚ÌŒvZ
			// sqrt() ‚Íâ‘Î’l
			// pow() ‚Í‚×‚«æ
			// ˆê’è‚Ì‘¬“x‚Å’Ç”ö
=======
		// æ®‹ã‚‹æ•µâ—¯
		if (0 < enemy_num) {

			// è¿½å°¾ã™ã‚‹è¨ˆç®—
			// sqrt() ã¯çµ¶å¯¾å€¤ã®è¨ˆç®—
			// pow() ã¯ã¹ãä¹—ã®è¨ˆç®—
			// ä¸€å®šã®é€Ÿåº¦ã§è¿½å°¾ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			m_x += ((enemy_x - m_x) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
			m_y += ((enemy_y - m_y) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
		}

<<<<<<< HEAD
		else m_x += m_s; // c‚é“G~‚Ìê‡@‰E•ûŒü‚Ö
=======
		else m_x += m_s; // æ®‹ã‚‹æ•µÃ— å³æ–¹å‘ã¸
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	}

	if (Game::WIDTH < m_x) remove();
}

void Homing_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT1], TRUE);
}

void Homing_Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Parabola Shot ƒNƒ‰ƒXi•ú•¨ü’ej‚ÌÀ‘•
=======
// Parabola Shot ã‚¯ãƒ©ã‚¹ï¼ˆè¿½å°¾ãƒ»æ”¾ç‰©ç·šå¼¾ï¼‰ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Parabola_Shot::Parabola_Shot() {

	m_w = 12;
	m_h = 12;
	damage = 50;
<<<<<<< HEAD
	m_s = 0; // shot_s ‚ğ‚O‚É
=======
	m_s = 0; // shot_s ã‚’ 0ã«
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Parabola_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;

<<<<<<< HEAD
	// s—ñŒvZ‚ÅO“_‚ÌÀ•W‚ğŒvZ
=======
	// è¡Œåˆ—è¨ˆç®—ã§ä¸‰ç‚¹ã®åº§æ¨™ã‚’æ±‚ã‚ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	float frame = (enemy_x - center_x) / (8 + enemy_s);

	// å¼¾ãƒ»æ•µã‚’å…¥ã‚Œã‚‹ï¼“ç‚¹ã®åº§æ¨™
	float x_1 = center_x;
	float x_2 = enemy_x - enemy_s * frame;
	float x_3 = center_x + 1;

	float y_1 = center_y;
	float y_2 = enemy_y;
<<<<<<< HEAD
	float y_3 = center_y - tan(3.14 / 3); // Šp“x‚U‚O‹‚É
=======
	float y_3 = center_y - tan(3.14 / 3); // è§’åº¦ï¼–ï¼Â°ã§ä¸Šæ˜‡ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	float det_A = -(x_1 - x_2) * (x_2 - x_3) * (x_3 - x_1);
	float det_a = y_1 * x_2 + y_2 * x_3 + y_3 * x_1 - x_2 * y_3 - x_3 * y_1 - x_1 * y_2;
	float det_b = pow(x_1, 2) * y_2 + pow(x_2, 2) * y_3 + pow(x_3, 2) * y_1 - y_1 * pow(x_2, 2) - y_2 * pow(x_3, 2) - y_3 * pow(x_1, 2);
	float det_c = pow(x_1, 2) * x_2 * y_3 + pow(x_2, 2) * x_3 * y_1 + pow(x_3, 2) * x_1 * y_2 - y_1 * x_2 * pow(x_3, 2) - y_2 * x_3 * pow(x_1, 2) - y_3 * x_1 * pow(x_2, 2);

	// ã‚¯ãƒ©ãƒ¡ãƒ«ã«ã‚ˆã‚‹è¨ˆç®—
	a = det_a / det_A;
	b = det_b / det_A;
	c = det_c / det_A;
}

void Parabola_Shot::move() {

	if (!pause_flag) {

		m_s += 8;
		m_x = center_x + m_s;
<<<<<<< HEAD
		m_y = a * pow(m_x, 2) + b * m_x + c; // •ú•¨ü‚Å•`‰æ
=======
		m_y = a * pow(m_x, 2) + b * m_x + c; // æ”¾ç‰©ç·šã«æç”»ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	}
}

void Parabola_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT1], TRUE);
}

void Parabola_Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// ENEMY1`6ƒNƒ‰ƒX‚ÌÀ‘•
=======
// ENEMY1ï½6ã‚¯ãƒ©ã‚¹ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Enemy1::Enemy1() {

	m_w = 80;
	m_h = 50;

<<<<<<< HEAD
	// STAGE ‚Ì’l‚Å‘¬“x‚ğİ’è
	if (stage <= 6) m_s = 8;
	if (7 <= stage) m_s = 10;

	life_max = 10; // ‘Ì—Í‚P‚O‚É
	life_now = life_max; // ‘Ì—Í‚Ì’l‚ğİ’è‘Ì—Í‚É
	damage = 1; // ‘¹ŠQ—Ê‚P‚É
	energy = 0; // “Áê—Ê‚O‚É
	count = 0; // ‘Ì—Í != 0 ‚Å count ‚ğ‚O‚É
	count_flag = false; // ‘Ì—Í != 0 ‚Å count ƒtƒ‰ƒO‚Í false ‚É
	SET_picture("ENEMY1.png", TYPE_ENEMY1);
	SET_picture("BURN.png", TYPE_BURN);
	SET_sound("BREAK.mp3", SOUND_BREAK);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h)); // À•W
=======
	// STAGEã«ã‚ˆã‚Šé€Ÿåº¦ã‚’è¨­å®š
	if (stage <= 6) m_s = 8;
	if (7 <= stage) m_s = 10;

	life_max = 10; // ä½“åŠ›ï¼‘ï¼
	life_now = life_max; // è¨­å®šä½“åŠ›ã‚’ç¾åœ¨ã®ä½“åŠ›ã«å…¥ã‚Œã‚‹
	damage = 1; // æå®³é‡ï¼‘
	energy = 0; // ç‰¹æ®Šé‡ï¼
	count = 0; // ä½“åŠ› != 0 ã§ count ã‚’ï¼ã«
	count_flag = false; // ä½“åŠ› != 0 ã§ count ãƒ•ãƒ©ã‚°ã¯ false ã«
	SET_picture("ENEMY1.png", TYPE_ENEMY1);
	SET_picture("BURN.png", TYPE_BURN);
	SET_sound("BREAK.mp3", SOUND_BREAK);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h)); // åˆæœŸä½ç½®
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

ThingType Enemy1::GET_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Enemy1::HIT_TYPE() {

	return TYPE_PLAYER;
}

void Enemy1::move() {

	if (!pause_flag) m_x -= m_s; // é€Ÿåº¦ï¼˜ or ï¼‘ï¼

	// çˆ†ç ´å¾Œ count ã¯ï¼‘ï¼“ã®å€¤ã‚’å¾—ã‚‹
	if (0 < count) {

		count--;
		count_flag = true;
	}

	// ç”»é¢å·¦ã«å…¥ã‚‹å ´åˆ
	if (m_x + m_w < 0) {

		remove(); // å‰Šé™¤ã™ã‚‹

		if (score < 20000 && 0 < score) game->ADD_score(-100); // ã‚¹ã‚³ã‚¢ã‚’ãƒã‚¤ãƒŠã‚¹ã™ã‚‹

		if (0 < enemy_num) enemy_num -= 1; // enemy_num ã‚’ãƒã‚¤ãƒŠã‚¹ã™ã‚‹
	}

<<<<<<< HEAD
	// HomingEParabola ShotƒNƒ‰ƒXi’Ç”ö’eE•ú•¨ü’ej‚ğÀ‘•‚·‚éˆ×@’l‚ğƒOƒ[ƒoƒ‹•Ï”‚É
=======
	// Homingãƒ»Parabola Shotã‚¯ãƒ©ã‚¹ï¼ˆè¿½å°¾å¼¾ï¼‰ã‚’å®Ÿè£…ã™ã‚‹ç‚ºã€€ã‚°ãƒ­ãƒ¼ãƒãƒ«å¤‰æ•°ã«å€¤ã‚’å…¥ã‚Œã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy1::draw() {

<<<<<<< HEAD
	life_draw(); // ‘Ì—Í‚ğ•`‰æ
=======
	life_draw(); // ä½“åŠ›ã‚’æç”»ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY1], TRUE);
	}

	// çˆ†ç ´å¾Œ count ã«ã¯ï¼‘ï¼“ãƒ»count_flag ã¯ move() ã§ true ã«
	if (count_flag && 0 <= count) {

<<<<<<< HEAD
		// ”š”jƒGƒtƒFƒNƒg‚ğ•`‰æ
		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		// count <= 0 ‚Ìê‡@íœ
		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200); // ƒXƒRƒA‚ğ’Ç‰Á
=======
		// çˆ†ç ´ã‚¨ãƒ•ã‚§ã‚¯ãƒˆã‚’æç”»ã™ã‚‹
		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		// count <= 0 ã®å ´åˆã€€å‰Šé™¤ã™ã‚‹
		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200); // ã‚¹ã‚³ã‚¢ã«å¾—ç‚¹ã‚’è¿½åŠ ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

			if (0 < enemy_num) enemy_num -= 1; // enemy_num ã‚’ãƒã‚¤ãƒŠã‚¹ã™ã‚‹
		}
	}
}

void Enemy1::hit(int damage, int energy) {

	life_now -= damage; // ä½“åŠ›ã‚’ãƒã‚¤ãƒŠã‚¹ã™ã‚‹

<<<<<<< HEAD
	// ‘Ì—Í‚O‚Ìê‡@”š”jƒGƒtƒFƒNƒg‚ğÀ‘•
	if (life_now <= 0 && count == 0) {

		count = 13; // count ‚ğ‚P‚R‚É
=======
	// ä½“åŠ›ï¼ã®å ´åˆã€€çˆ†ç ´ã‚¨ãƒ•ã‚§ã‚¯ãƒˆã‚’å®Ÿè£…ã™ã‚‹
	if (life_now <= 0 && count == 0) {

		count = 13; // count ã«ï¼‘ï¼“ã®å€¤ã‚’å…¥ã‚Œã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		PlaySoundMem(loaded_sound[SOUND_BREAK], DX_PLAYTYPE_BACK);
	}
}

//-------------------------------------------------------------------------------------

Enemy2::Enemy2() {

	m_w = 80;
	m_h = 50;

	if (stage <= 3) m_s = 3;
	if (4 <= stage && stage <= 9) m_s = 4;
	if (stage == 10) m_s = 5;

	life_max = 20;
	life_now = life_max;
	damage = 1;
	energy = 0;
	count = 0;
	count_flag = false;
	SET_picture("ENEMY2.png", TYPE_ENEMY2);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy2::move() {

	if (!pause_flag) m_x -= m_s;

	if (0 < count) {

		count--;
		count_flag = true;
	}

	if (m_x + m_w < 0) {

		remove();

		if (score < 20000 && 0 < score) game->ADD_score(-100);

		if (0 < enemy_num) enemy_num -= 1;
	}

	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy2::draw() {

	life_draw();

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY2], TRUE);
	}

	if (count_flag && 0 <= count) {

		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200);

			if (0 < enemy_num) enemy_num -= 1;
		}
	}
}

//-------------------------------------------------------------------------------------

Enemy3::Enemy3() {

	m_w = 80;
	m_h = 50;

	if (stage <= 6) m_s = 5;
	if (7 <= stage) m_s = 7;

	life_max = 10;
	life_now = life_max;
	damage = 1;
	energy = 0;
	up_down = 6; // ä¸Šä¸‹æ–¹å‘ã®é€Ÿåº¦ã‚’ï¼–ã«
	count = 0;
	count_flag = false;
	SET_picture("ENEMY3.png", TYPE_ENEMY3);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy3::move() {

	if (!pause_flag) {

		m_x -= m_s;
		m_y += up_down; // ä¸Šä¸‹æ–¹å‘ã®é€Ÿåº¦
	}

	// ç”»é¢ã®å½“ãŸã‚Šåˆ¤å®š
	if (m_y < 0) up_down = -up_down; // ä¸Š
	if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // ä¸‹

	if (0 < count) {

		count--;
		count_flag = true;
	}

	if (m_x + m_w < 0) {

		remove();

		if (score < 20000 && 0 < score) game->ADD_score(-100);

		if (0 < enemy_num) enemy_num -= 1;
	}

	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy3::draw() {

	life_draw();

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY3], TRUE);
	}

	if (count_flag && 0 <= count) {

		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200);

			if (0 < enemy_num) enemy_num -= 1;
		}
	}
}

//-------------------------------------------------------------------------------------

Enemy4::Enemy4() {

	m_w = 60;
	m_h = 35;
	m_s = 12;
	life_max = 5;
	life_now = life_max;
	damage = 1;
	energy = 0;
	count = 0;
	count_flag = false;
	SET_picture("ENEMY4.png", TYPE_ENEMY4);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy4::move() {

	if (!pause_flag) m_x -= m_s;

	if (0 < count) {

		count--;
		count_flag = true;
	}

	if (m_x + m_w < 0) {

		remove();

		if (score < 20000 && 0 < score) game->ADD_score(-100);

		if (0 < enemy_num) enemy_num -= 1;
	}

	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy4::draw() {

	life_draw();

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY4], TRUE);
	}

	if (count_flag && 0 <= count) {

		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200);

			if (0 < enemy_num) enemy_num -= 1;
		}
	}
}

//-------------------------------------------------------------------------------------

Enemy5::Enemy5() {

	m_w = 80;
	m_h = 50;

	if (stage <= 6) m_s = 4;
	if (7 <= stage) m_s = 5;

	life_max = 20;
	life_now = life_max;
	damage = 1;
	energy = 0;
	up_down = 6; // ä¸Šä¸‹æ–¹å‘ã®é€Ÿåº¦ã‚’ï¼–ã«
	count = 0;
	count_flag = false;
	SET_picture("ENEMY5.png", TYPE_ENEMY5);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy5::move() {

	if (!pause_flag) {

		// ä¸€å®šã®åº§æ¨™ã¾ã§å·¦å‘ãã¸
		if (1000 < m_x) m_x -= m_s;

		// ä¸€å®šã®åº§æ¨™ã§ä¸Šä¸‹å‘ãã¸
		if (m_x <= 1000) {

			m_y -= up_down;

			// ç”»é¢ã®å½“ãŸã‚Šåˆ¤å®š
			if (m_y < 0) up_down = -up_down; // ä¸Š
			if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // ä¸‹

			if (GetRand(60) == 0) {

<<<<<<< HEAD
				ThingPointa enemy_shot2(new Enemy_Shot2); // Enemy Shot2 ƒNƒ‰ƒXì¬@‚»‚ÌƒAƒhƒŒƒX‚ğ Thing ƒNƒ‰ƒX‚ÌƒXƒ}[ƒgƒ|ƒCƒ“ƒ^‚É“n‚·
				enemy_shot2->SET_position(m_x - 10, m_y + 25); // À•W
				game->ADD_list(enemy_shot2); // Thing ƒŠƒXƒg‚É Enemy Shot2 ƒAƒhƒŒƒX‚ğ’Ç‰Á
=======
				ThingPointa enemy_shot2(new Enemy_Shot2); // Enemy Shot2 ã‚¯ãƒ©ã‚¹ä½œæˆã€€ãã®ã‚¢ãƒ‰ãƒ¬ã‚¹ã‚’ Thing ã‚¯ãƒ©ã‚¹ã®ã‚¹ãƒãƒ¼ãƒˆãƒã‚¤ãƒ³ã‚¿ã«æ¸¡ã™
				enemy_shot2->SET_position(m_x - 10, m_y + 25); // åˆæœŸä½ç½®
				game->ADD_list(enemy_shot2); // Thing ãƒªã‚¹ãƒˆã« Enemy Shot2 ã‚¢ãƒ‰ãƒ¬ã‚¹ã‚’è¿½åŠ ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				PlaySoundMem(loaded_sound[SOUND_ENEMY_SHOT], DX_PLAYTYPE_BACK);
			}
		}
	}

	if (0 < count) {

		count--;
		count_flag = true;
	}

	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy5::draw() {

	life_draw();

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY5], TRUE);
	}

	if (count_flag && 0 <= count) {

		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200);

			if (0 < enemy_num) enemy_num -= 1;
		}
	}
}

//-------------------------------------------------------------------------------------

Enemy6::Enemy6() {

	m_w = 80;
	m_h = 50;

	if (stage <= 6) m_s = 5;
	if (7 <= stage) m_s = 7;

	life_max = 20;
	life_now = life_max;
	damage = 1;
	energy = 0;
	up_down = 6;
	count = 0;
	count_flag = false;
	SET_picture("ENEMY6.png", TYPE_ENEMY6);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy6::move() {

	if (!pause_flag) {

		m_x -= m_s;
		m_y -= up_down;

<<<<<<< HEAD
		// ‰æ–Ê‚Ì“–‚½‚è”»’è
		if (m_y < 0) up_down = -up_down; // ã
		if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // ‰º
		if (m_x < 0) m_s = -2; // ¶
		if (Game::WIDTH + 200 < m_x + m_w) remove(); // ‰æ–Ê‰E‚Åíœ
=======
		// ç”»é¢ã®å½“ãŸã‚Šåˆ¤å®š
		if (m_y < 0) up_down = -up_down; // ä¸Š
		if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // ä¸‹
		if (m_x < 0) m_s = -2; // å·¦
		if (Game::WIDTH + 200 < m_x + m_w) remove(); // ç”»é¢å³ã§å‰Šé™¤ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

		if (GetRand(60) == 0) {

			ThingPointa enemy_shot2(new Enemy_Shot2);
			enemy_shot2->SET_position(m_x - 10, m_y + 25);
			game->ADD_list(enemy_shot2);
			PlaySoundMem(loaded_sound[SOUND_ENEMY_SHOT], DX_PLAYTYPE_BACK);
		}
	}

	if (0 < count) {

		count--;
		count_flag = true;
	}

	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy6::draw() {

	life_draw();

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY6], TRUE);
	}

	if (count_flag && 0 <= count) {

		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200);

			if (0 < enemy_num) enemy_num -= 1;
		}
	}
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// ENEMY BOSS1E2ƒNƒ‰ƒX‚ÌÀ‘•
=======
// ENEMY BOSS1ãƒ»2ã‚¯ãƒ©ã‚¹ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Enemy_Boss1::Enemy_Boss1() {

	// Enemy Boss1 ãƒ©ã‚¤ãƒ•è¨­å®š
	if (stage == 1 || stage == 4 || stage == 7) life_max = 3000; // STAGEï¼‘ãƒ»ï¼”ãƒ»ï¼—
	if (stage == 2 || stage == 5 || stage == 8) life_max = 3500; // STAGEï¼’ãƒ»ï¼•ãƒ»ï¼˜
	if (stage == 3 || stage == 6 || stage == 9) life_max = 4000; // STAGEï¼“ãƒ»ï¼–ãƒ»ï¼™

	m_w = 350;
	m_h = 390;
	life_now = life_max;
	damage = 1;
	energy = 0;
<<<<<<< HEAD
	up_down = 3; // ã‰ºŒü‚«‘¬“x‚ğ‚R‚É
	add_speed = 0; // ‘Ì—Í”¼•ª‚É‚È‚é‚Ü‚Å‰Á‘¬‚Í‚O‚É
	count = 0;
	count_flag = false;

	// STAGE‚Ì’l‚Å‰æ‘œ‚ğİ’è
=======
	up_down = 3; // ä¸Šä¸‹å‘ãé€Ÿåº¦
	add_speed = 0; // ä½“åŠ›ãŒåŠåˆ†ã«ãªã‚‹ã¾ã§åŠ é€Ÿã¯ï¼ã«
	count = 0;
	count_flag = false;

	// STAGEã«ã‚ˆã‚Šæç”»ã™ã‚‹ç”»åƒã‚’è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (stage <= 3) SET_picture("ENEMY BOSS1.png", TYPE_ENEMY_BOSS1);
	if (4 <= stage && stage <= 6) SET_picture("ENEMY BOSS2.png", TYPE_ENEMY_BOSS2);
	if (7 <= stage && stage <= 9) SET_picture("ENEMY BOSS3.png", TYPE_ENEMY_BOSS3);

	SET_hitarea(150, 50, 340, 340); // å½“ãŸã‚Šåˆ¤å®šã®è¨­å®š
	Warn_p = LoadGraph("WARNING.png"); // WARNING!!
	SET_position(Game::WIDTH, 140);
}

void Enemy_Boss1::move() {

<<<<<<< HEAD
	// ‘Ì—Í”¼•ªˆÈ‰º‚Ìê‡@‘¬“x‚ğã¸
=======
	// ä½“åŠ›ãŒåŠåˆ†ä»¥ä¸‹ã®å ´åˆã€€é€Ÿåº¦ã‚’ä¸Šã’ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (life_now < life_max / 2) add_speed = 3;

	if (!pause_flag) {

<<<<<<< HEAD
		// ˆê’è‚ÌÀ•W‚Ü‚Å¶•ûŒü
=======
		// ä¸€å®šã®åº§æ¨™ã¾ã§å·¦å‘ã
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		if (790 < m_x) {

			m_x -= 2;

			if ((int)m_x % 10 == 0) {

				DrawExtendGraph(70, 260, Game::WIDTH - 70, Game::HEIGHT - 260, Warn_p, TRUE); // WARNING!!
			}
		}
	}

	if (0 < count) {

		count--;
		count_flag = true;
	}

	if (!pause_flag) {

<<<<<<< HEAD
		// ˆê’è‚ÌÀ•W‚Ìê‡@ã‰º•ûŒü
=======
		// ä¸€å®šã®åº§æ¨™ã®å ´åˆã€€ä¸Šä¸‹å‘ã
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		if (m_x <= 790) {

			m_y += up_down;

			// ç”»é¢ã®å½“ãŸã‚Šåˆ¤å®š
			if (m_y + hit_y + 100 < 0) up_down = 4 + add_speed;
			if (Game::HEIGHT + 100 < m_y + hit_h) up_down = -(4 + add_speed);

			if (GetRand(30) == 0) {

				// ^‚ñ’†
				ThingPointa enemy_shot1_1(new Enemy_Shot1);
				enemy_shot1_1->SET_position(m_x + m_w - 250, m_y + 190);
				game->ADD_list(enemy_shot1_1);

				// ‰º
				ThingPointa enemy_shot1_2(new Enemy_Shot1);
				enemy_shot1_2->SET_position(m_x + m_w - 210, m_y + 220);
				game->ADD_list(enemy_shot1_2);

				// ã
				ThingPointa enemy_shot1_3(new Enemy_Shot1);
				enemy_shot1_3->SET_position(m_x + m_w - 210, m_y + 160);
				game->ADD_list(enemy_shot1_3);
				PlaySoundMem(loaded_sound[SOUND_ENEMY_SHOT], DX_PLAYTYPE_BACK);
			}
		}
	}
}

void Enemy_Boss1::life_draw() {

	int life_x = Game::WIDTH - 245; // åº§æ¨™ã®èª¿æ•´

	if (0 < life_now) {

		DrawExtendGraph(life_x, 5, life_x + 245, 30, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(life_x, 5, life_x + (245 * life_now) / life_max, 30, loaded_picture[TYPE_LIFE], TRUE);
	}
}

void Enemy_Boss1::draw() {

	life_draw(); // ä½“åŠ›ã®æç”»

	if (0 < life_now) {

		SetFontSize(20); // æ–‡å­—ã‚µã‚¤ã‚ºã®è¨­å®š
		DrawFormatString(Game::WIDTH - 250, 5, GetColor(255, 255, 255), "%d", life_now); // ä½“åŠ›æ•°å€¤ã®æç”»
	}

	if (!count_flag) {

<<<<<<< HEAD
		// STAGE‚Ì’l‚Å‰æ‘œ‚ğİ’è
=======
		// STAGEã«ã‚ˆã‚Šç”»åƒã‚’è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		if (stage <= 3) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS1], TRUE);
		if (4 <= stage && stage <= 6) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS2], TRUE);
		if (7 <= stage && stage <= 9) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS3], TRUE);
	}

	if (count_flag && 0 <= count) {

		DrawExtendGraph(m_x - 6 * count, m_y - 6 * count, m_x + m_w + 6 * count, m_y + m_h + 6 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		if (count <= 0 && !count_flag) {

			remove();
			scene = 4; // ã‚¯ãƒªã‚¢ç”»é¢ã¸
			StopSoundMem(Boss_m);
			PlaySoundMem(Clear_m, DX_PLAYTYPE_LOOP);
		}
	}
}

void Enemy_Boss1::hit(int damage, int energy) {

	life_now -= damage;

	if (life_now <= 0 && count == 0) {

		count = 13;
		PlaySoundMem(loaded_sound[SOUND_BREAK], DX_PLAYTYPE_BACK);
	}
}

//-------------------------------------------------------------------------------------

Enemy_Boss2::Enemy_Boss2() {

	m_w = 370;
	m_h = 350;
	life_max = 5000; // Enemy Boss2 ãƒ©ã‚¤ãƒ•è¨­å®š
	life_now = life_max;
	damage = 1;
	energy = 0;
	up_down = 4;
	add_speed = 0;
	count = 0;
	count_flag = false;
	SET_picture("ENEMY BOSS4.png", TYPE_ENEMY_BOSS4);
	SET_hitarea(150, 50, 350, 300);
	Warn_p = LoadGraph("WARNING.png");
	SET_position(Game::WIDTH, 140);
}

void Enemy_Boss2::move() {

	if (life_now < life_max / 2) add_speed = 3;

	if (!pause_flag) {

		if (780 < m_x) {

			m_x -= 3;

			if ((int)m_x % 10 == 0) {

				DrawExtendGraph(70, 260, Game::WIDTH - 70, Game::HEIGHT - 260, Warn_p, TRUE); // WARNING!!
			}
		}
	}

	if (0 < count) {

		count--;
		count_flag = true;
	}

	if (!pause_flag) {

		if (m_x <= 780) {

			m_y += up_down;

			if (m_y + hit_y + 100 < 0) up_down = 4 + add_speed;
			if (Game::HEIGHT + 100 < m_y + hit_h) up_down = -(4 + add_speed);

			if (GetRand(30) == 0) {

				// å·¦
				ThingPointa enemy_shot1_1(new Enemy_Shot1);
				enemy_shot1_1->SET_position(m_x + m_w - 250, m_y + 190);
				game->ADD_list(enemy_shot1_1);

				// çœŸã‚“ä¸­ä¸‹
				ThingPointa enemy_shot1_2(new Enemy_Shot1);
				enemy_shot1_2->SET_position(m_x + m_w - 210, m_y + 220);
				game->ADD_list(enemy_shot1_2);

				// çœŸã‚“ä¸­ä¸Š
				ThingPointa enemy_shot1_3(new Enemy_Shot1);
				enemy_shot1_3->SET_position(m_x + m_w - 210, m_y + 160);
				game->ADD_list(enemy_shot1_3);

				// å³ä¸‹
				ThingPointa enemy_shot1_4(new Enemy_Shot1);
				enemy_shot1_4->SET_position(m_x + m_w - 170, m_y + 250);
				game->ADD_list(enemy_shot1_4);

				// å³ä¸Š
				ThingPointa enemy_shot1_5(new Enemy_Shot1);
				enemy_shot1_5->SET_position(m_x + m_w - 170, m_y + 130);
				game->ADD_list(enemy_shot1_5);
				PlaySoundMem(loaded_sound[SOUND_ENEMY_SHOT], DX_PLAYTYPE_BACK);
			}
		}
	}
}

void Enemy_Boss2::life_draw() {

	int life_x = Game::WIDTH - 245;

	if (0 < life_now) {

		DrawExtendGraph(life_x, 5, life_x + 245, 30, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(life_x, 5, life_x + (245 * life_now) / life_max, 30, loaded_picture[TYPE_LIFE], TRUE);
	}
}

void Enemy_Boss2::draw() {

	life_draw();

	if (0 < life_now) {

		SetFontSize(20);
		DrawFormatString(Game::WIDTH - 250, 5, GetColor(255, 255, 255), "%d", life_now);
	}

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS4], TRUE);
	}

	if (count_flag && 0 <= count) {

		DrawExtendGraph(m_x - 6 * count, m_y - 6 * count, m_x + m_w + 6 * count, m_y + m_h + 6 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		if (count <= 0 && !count_flag) {

			remove();
			scene = 4;
			StopSoundMem(Boss_m);
			PlaySoundMem(Clear_m, DX_PLAYTYPE_LOOP);
		}
	}
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Shot1 ƒNƒ‰ƒXiƒ{ƒXj‚ÌÀ‘•
=======
// Enemy Shot1 ã‚¯ãƒ©ã‚¹ï¼ˆãƒœã‚¹ï¼‰ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Enemy_Shot1::Enemy_Shot1() {

	m_w = 25;
	m_h = 25;

	if (stage <= 3) m_s = 16;
	if (4 <= stage && stage <= 6) m_s = 18;
	if (7 <= stage && stage <= 9) m_s = 20;
	if (stage == 10) m_s = 22;

	damage = 2;
	energy = 0;
	SET_picture("ENEMY SHOT.png", TYPE_ENEMY_SHOT);
	SET_sound("ENEMY SHOT.mp3", SOUND_ENEMY_SHOT);
}

ThingType Enemy_Shot1::GET_TYPE() {

	return TYPE_ENEMY_SHOT;
}

ThingType Enemy_Shot1::HIT_TYPE() {

	return TYPE_PLAYER;
}

void Enemy_Shot1::move() {

	if (!pause_flag) m_x -= m_s;

	if (m_x + m_w < 0) remove();
}

void Enemy_Shot1::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_SHOT], TRUE);
}

void Enemy_Shot1::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_ENEMY_SHOT], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Shot2 ƒNƒ‰ƒXiENEMY5E6j‚ÌÀ‘•
=======
// Enemy Shot2 ã‚¯ãƒ©ã‚¹ï¼ˆENEMY5ãƒ»6ï¼‰ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Enemy_Shot2::Enemy_Shot2() {

	m_w = 12;
	m_h = 12;
	m_s = 10;
	damage = 1;
	energy = 0;
	SET_picture("SHOT1.png", TYPE_ENEMY_SHOT);
}

void Enemy_Shot2::move() {

	if (!pause_flag) m_x -= m_s;

	if (m_x + m_w < 0) remove();
}

void Enemy_Shot2::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_SHOT], TRUE);
}

void Enemy_Shot2::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_ENEMY_SHOT], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// HEAL1i‘Ì—Í‰ñ•œjƒNƒ‰ƒX‚ÌÀ‘•
=======
// HEAL1ï¼ˆä½“åŠ›å›å¾©ï¼‰ã‚¯ãƒ©ã‚¹ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Heal1::Heal1() {

	m_w = 25;
	m_h = 21;
	m_s = 6;
<<<<<<< HEAD
	damage = -1; // ’l‚Íƒ}ƒCƒiƒX‚É‚µ‚Ä‰ñ•œ‚É
=======
	damage = -1; // å€¤ã¯ãƒã‚¤ãƒŠã‚¹ã«ã—ã¦å›å¾©ã«ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	energy = 0;
	SET_picture("HEART.png", TYPE_HEAL1);
	SET_sound("HEAL.mp3", SOUND_HEAL);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

ThingType Heal1::GET_TYPE() {

	return TYPE_HEAL1;
}

ThingType Heal1::HIT_TYPE() {

	return TYPE_PLAYER;
}

void Heal1::move() {

	if (!pause_flag) m_x -= m_s;

	if (m_x + m_w < 0) remove();
}

void Heal1::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_HEAL1], TRUE);
}

void Heal1::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_HEAL], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// HEAL2i“Áê—Ê‰ñ•œjƒNƒ‰ƒX‚ÌÀ‘•
=======
// HEAL2ï¼ˆç‰¹æ®Šé‡å›å¾©ï¼‰ã‚¯ãƒ©ã‚¹ã®å®Ÿè£…
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Heal2::Heal2() {

	m_w = 25;
	m_h = 21;
	m_s = 10;
	damage = 0;
<<<<<<< HEAD
	energy = -1; // ’l‚ğƒ}ƒCƒiƒX‚É‚µ‚Ä“Áê—Ê‰ñ•œ‚É
=======
	energy = -1; // å€¤ã‚’ãƒã‚¤ãƒŠã‚¹ã«ã—ã¦ç‰¹æ®Šé‡å›å¾©ã«ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	SET_picture("ENERGY.png", TYPE_HEAL2);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Heal2::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_HEAL2], TRUE);
}

void Heal2::move() {

	if (!pause_flag) m_x -= m_s;

	if (m_x + m_w < 0) remove();
}

void Heal2::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_HEAL], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Game ƒNƒ‰ƒX‚ÌÀ‘•
void Game::ADD_list(ThingPointa & add) {

	thing_list.push_back(add); // Thing ƒŠƒXƒg‚Ì back ‚É Thing ƒNƒ‰ƒX‚Ì add ‚ğ’Ç‰Á
=======
// Game ã‚¯ãƒ©ã‚¹ã®å®Ÿè£…
void Game::ADD_list(ThingPointa & add) {

	thing_list.push_back(add); // Thing ãƒªã‚¹ãƒˆã®ä¸‹ã« Thing ã‚¯ãƒ©ã‚¹ã® add ã‚’è¿½åŠ ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Game::ADD_score(int sc) {

	score += sc; // ã‚¹ã‚³ã‚¢ã‚’è¿½åŠ 
}

bool Game::PUSH_space() {

	if (CheckHitKey(KEY_INPUT_SPACE)) {

		// push_flagã€€false ã®å ´åˆ
		if (!push_flag) {

			push_flag = true;
			return true;
		}
	}

	// ä¸Šè¨˜ä»¥å¤– false ã«
	else push_flag = false;

	return false; // false ã§è¿”ã™
}

bool Game::PUSH_back() {

	if (CheckHitKey(KEY_INPUT_BACK)) {

		if (!push_flag) {

			push_flag = true;
			return true;
		}
	}

	else push_flag = false;

	return false;
}

void Game::LOAD_highscore() {

	// text ã®å€¤ã‚’èª­è¾¼ã™ã‚‹ï¼ˆãƒã‚¤ã‚¹ã‚³ã‚¢ï¼‰
	FILE* file;
	fopen_s(&file, "HIGH SCORE.txt", "r");
	fscanf_s(file, "%d", &high_score);
	fclose(file);
}

void Game::SAVE_highscore() {

	// text ã®å€¤ã‚’è¨˜éŒ²ã™ã‚‹ï¼ˆã‚¹ã‚³ã‚¢ï¼‰
	FILE* file;
	fopen_s(&file, "HIGH SCORE.txt", "w");
	fprintf(file, "%d", now_score);
	fclose(file);
}

//-------------------------------------------------------------------------------------

void Game::GAME_SET() {

<<<<<<< HEAD
	game = this; // ©ƒCƒ“ƒXƒ^ƒ“ƒX‚ÌƒAƒhƒŒƒX‚ğ•ÛiÃ“Ij
	scene = 0; // ƒ^ƒCƒgƒ‹‰æ–Ê‚Ö
	stage = 0; // STAGE‚ğ‚O‚É
	score = 0; // ƒXƒRƒA‚ğ‚O‚É
	p_x = 0; // ƒoƒbƒN‚Ì x À•W‚ğ¶ã‚Éİ’è
	p_w = WIDTH; // ƒoƒbƒN‚Ì‰¡•‚ğ WIDTH ‚É
	limit_time = 600; // §ŒÀŠÔ‚ğ‚U‚O‚O‚É

	LOAD_highscore(); // ƒXƒRƒA‚Ì“Ç

	ChangeWindowMode(TRUE); // ƒEƒBƒ“ƒhƒE‚ğŠJ‚­
	SetGraphMode(WIDTH, HEIGHT, 32); // ƒEƒBƒ“ƒhƒE‚Ì‰¡•Ec•EƒJƒ‰[İ’è
	DxLib_Init(); // DXƒ‰ƒCƒuƒ‰ƒŠ‚ğ‰Šú‰»
	SetDrawScreen(DX_SCREEN_BACK); // ƒEƒ‰‚É‰æ‘œ‚ğ•`‰æ
=======
	game = this; // è‡ªã‚¤ãƒ³ã‚¹ã‚¿ãƒ³ã‚¹ã®ã‚¢ãƒ‰ãƒ¬ã‚¹ã‚’ä¿æŒã™ã‚‹ï¼ˆé™çš„ï¼‰
	scene = 0; // ã‚¿ã‚¤ãƒˆãƒ«ç”»é¢ã¸
	stage = 0; // STAGEã‚’ï¼ã«ã™ã‚‹
	score = 0; // ã‚¹ã‚³ã‚¢ã‚’ï¼ã«
	p_x = 0; // ãƒãƒƒã‚¯ã® x åº§æ¨™ã‚’å·¦ä¸Šã«è¨­å®š
	p_w = WIDTH; // ãƒãƒƒã‚¯ã®æ¨ªå¹…ã‚’ WIDTH ã«ç½®æ›
	limit_time = 600; // åˆ¶é™æ™‚é–“ã‚’ï¼–ï¼ï¼ã«

	LOAD_highscore(); // ã‚¹ã‚³ã‚¢ã®èª­è¾¼
	start_time = GetNowCount(); // ï¼‘s å˜ä½ã«ã™ã‚‹

	ChangeWindowMode(TRUE); // ã‚¦ã‚£ãƒ³ãƒ‰ã‚¦ã‚’é–‹ã
	SetGraphMode(WIDTH, HEIGHT, 32); // ã‚¦ã‚£ãƒ³ãƒ‰ã‚¦ã®æ¨ªå¹…ãƒ»ç¸¦å¹…ãƒ»ã‚«ãƒ©ãƒ¼ã®è¨­å®š
	DxLib_Init(); // DXãƒ©ã‚¤ãƒ–ãƒ©ãƒªã‚’åˆæœŸåŒ–ã™ã‚‹
	SetDrawScreen(DX_SCREEN_BACK); // ã‚¦ãƒ©ã«ç”»åƒã‚’æç”»
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	// ç”»åƒã®èª­è¾¼
	loaded_picture[TYPE_EMPTY] = LoadGraph("EMPTY.png");
	loaded_picture[TYPE_LIFE] = LoadGraph("LIFE.png");
	Title_p = LoadGraph("TITLE.png");
	Select_p = LoadGraph("STAGE SELECT.png");
	Number_p = LoadGraph("NUMBER.png");
	Over_p = LoadGraph("GAME OVER.png");
	Clear_p = LoadGraph("GAME CLEAR.png");
	Push_p = LoadGraph("PUSH SPACE.png");
	Pause_p = LoadGraph("PAUSE.png");
	Esc_p = LoadGraph("ESC.png");
	Game_p = LoadGraph("BACK.jpg");

	// éŸ³æ¥½ãƒ•ã‚¡ã‚¤ãƒ«ã®èª­è¾¼
	Title_m = LoadSoundMem("TITLE.mp3");
	Play_m = LoadSoundMem("GAME PLAY.mp3");
	Over_m = LoadSoundMem("GAME OVER.mp3");
	Clear_m = LoadSoundMem("GAME CLEAR.mp3");
	Pause_m = LoadSoundMem("PAUSE.mp3");
	Boss_m = LoadSoundMem("BOSS GAME.mp3");

<<<<<<< HEAD
	PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // ƒ^ƒCƒgƒ‹‰æ–Ê‚Ì‰¹‚ğÄ¶
=======
	PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // ã‚¿ã‚¤ãƒˆãƒ«éŸ³å†ç”Ÿ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

//-------------------------------------------------------------------------------------

void Game::GAME_ALL() {

<<<<<<< HEAD
	// ƒCƒxƒ“ƒgˆ—‚ÌÀ‘•ŠÖ”
=======
	// ã‚¤ãƒ™ãƒ³ãƒˆå‡¦ç†ã‚’å®Ÿè£…ã™ã‚‹é–¢æ•°
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	while (!ProcessMessage()) {

		ClearDrawScreen(); // ç”»åƒã‚’å‰Šé™¤ï¼ˆã‚¦ãƒ©ã®åˆæœŸåŒ–ï¼‰

		if (scene == 0) GAME_TITLE();

		if (scene == 1) GAME_SELECT();

		if (scene == 2) GAME_PLAY();

		if (scene == 3) GAME_OVER();

		if (scene == 4) GAME_CLEAR();

		ScreenFlip(); // ç”»åƒã‚’ã‚ªãƒ¢ãƒ†ã«å‡ºã™
	}
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 0 ‚Ìê‡@ƒ^ƒCƒgƒ‹‰æ–Ê
void Game::GAME_TITLE() {

	SetBackgroundColor(0, 0, 0); // ƒoƒbƒN‚ÌF‚ğ•F‚Éİ’è
	DrawExtendGraph(10, 200, WIDTH - 10, HEIGHT - 200, Title_p, TRUE); // ƒ^ƒCƒgƒ‹
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE
=======
// scene == 0 ã®æ™‚ã€€ã‚¿ã‚¤ãƒˆãƒ«ç”»é¢ã«ã™ã‚‹
void Game::GAME_TITLE() {

	SetBackgroundColor(0, 0, 0); // ãƒãƒƒã‚¯ã®è‰²ã‚’é»’è‰²ã«è¨­å®š
	DrawExtendGraph(10, 200, WIDTH - 10, HEIGHT - 200, Title_p, TRUE); // ã‚¿ã‚¤ãƒˆãƒ«ã®æç”»
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE ã®æç”»
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	// æ–‡å­—ã®æç”»
	SetFontSize(20); // ã‚µã‚¤ã‚ºã®è¨­å®š
	DrawFormatString(10, 10, GetColor(255, 255, 255), "B E S T  S C O R E : %d", high_score);

<<<<<<< HEAD
	thing_list.clear(); // Thing ƒŠƒXƒg‚ğ‰Šú‰»
	score = 0; // ƒXƒRƒA‚ğ‚O‚É
	add_s = 0; // ƒoƒbƒN‚ğ‚‘¬‚Å‰ñ‚·
	limit_time = 600; // §ŒÀŠÔ‚ğ‚U‚O‚O‚É

	// SPACE ‚ğ‰Ÿ‚·ê‡@‘I‘ğ‰æ–Ê‚Ö
	if (PUSH_space()) scene = 1;

	play_flag = false; // ƒvƒŒƒCƒtƒ‰ƒO‚ğ false ‚É
	boss_flag = false; // ƒ{ƒXƒtƒ‰ƒO‚ğ false ‚É
	space_flag = false; // ƒXƒy[ƒXƒtƒ‰ƒO‚ğ false ‚É
}

//-------------------------------------------------------------------------------------

// scene == 1 ‚Ìê‡@‘I‘ğ‰æ–Ê
=======
	thing_list.clear(); // Thing ãƒªã‚¹ãƒˆã‚’åˆæœŸåŒ–ã™ã‚‹
	score = 0; // ã‚¹ã‚³ã‚¢ã‚’ï¼ã«
	add_s = 0; // ãƒãƒƒã‚¯ã‚’é«˜é€Ÿã§å›ã™

	// SPACE KEY ã‚’æŠ¼ã—ãŸå ´åˆã€€SELECTç”»é¢ã¸
	if (PUSH_space()) scene = 1;

	game_flag = false; // game_flag ã‚’ false ã«
	boss_flag = false; // ãƒœã‚¹ãƒ•ãƒ©ã‚°ã‚’ false ã«
	space_flag = false; // PUSH SPACE ãƒ•ãƒ©ã‚°ã‚’ false ã«
}

// scene == 1 ã®æ™‚ã€€é¸æŠç”»é¢
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
void Game::GAME_SELECT() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(70, 200, WIDTH - 70, HEIGHT - 200, Select_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Number_p, TRUE); // PUSH SPACE ã®æç”»

	// ä»¥ä¸‹â†“ STAGEï¼‘ï½ï¼‘ï¼ã®åˆ†å²
	// stage == 1 ã«è¨­å®š
	if (CheckHitKey(KEY_INPUT_1)) {

		scene = 2; // ãƒ—ãƒ¬ã‚¤ç”»é¢
		stage = 1; // STAGEï¼‘

		// PLAYER ç”Ÿæˆ
		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 2 ‚Éİ’è
=======
	// stage == 2 ã«è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_2)) {

		scene = 2;
		stage = 2; // STAGEï¼’

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 3 ‚Éİ’è
=======
	// stage == 3 ã«è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_3)) {

		scene = 2;
		stage = 3; // STAGEï¼“

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 4 ‚Éİ’è
=======
	// stage == 4 ã«è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_4)) {

		scene = 2;
		stage = 4; // STAGEï¼”

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 5 ‚Éİ’è
=======
	// stage == 5 ã«è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_5)) {

		scene = 2;
		stage = 5; // STAGEï¼•

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 6 ‚Éİ’è
=======
	// stage == 6 ã«è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_6)) {

		scene = 2;
		stage = 6; // STAGEï¼–

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 7 ‚Éİ’è
=======
	// stage == 7 ã«è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_7)) {

		scene = 2;
		stage = 7; // STAGEï¼—

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 8 ‚Éİ’è
=======
	// stage == 8 ã«è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_8)) {

		scene = 2;
		stage = 8; // STAGEï¼˜

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 9 ‚Éİ’è
=======
	// stage == 9 ã«è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_9)) {

		scene = 2;
		stage = 9; // STAGEï¼™

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 10 ‚Éİ’è
=======
	// stage == 10 ã«è¨­å®š
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_0)) {

		scene = 2;
		stage = 10; // STAGEï¼‘ï¼

		ThingPointa player(new Player);
		ADD_list(player);
	}
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 2 ‚Ìê‡@ƒvƒŒƒC‰æ–Ê
=======
// scene == 2 ã®æ™‚ã€€ãƒ—ãƒ¬ã‚¤ç”»é¢
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
void Game::GAME_PLAY() {

	// ãƒãƒƒã‚¯ã®æç”»
	DrawExtendGraph(p_x, 0, p_w, HEIGHT, Game_p, TRUE);
	DrawExtendGraph(p_x + WIDTH, 0, p_w + WIDTH, HEIGHT, Game_p, TRUE); // ï¼’æšç›®ã®ãƒ«ãƒ¼ãƒ—

	//-------------------------------------------------------------------------------------

	if (!pause_flag) {

		// STAGEï¼‘ï½ï¼“ã®å ´åˆ
		if (stage <= 3) {

			// ã‚¨ãƒ•ã‚§ã‚¯ãƒˆã®å®Ÿè£…ï¼ˆãƒãƒƒã‚¯ã‚’å·¦ã¸å›ã™ï¼‰
			p_x -= 2 + add_s;
			p_w -= 2 + add_s;
		}

		// STAGEï¼”ï½ï¼™ã®å ´åˆ
		if (4 <= stage && stage <= 9) {

			p_x -= 3 + add_s;
			p_w -= 3 + add_s;
		}

		// STAGEï¼‘ï¼ã®å ´åˆ
		if (stage == 10) {

			p_x -= 4 + add_s;
			p_w -= 4 + add_s;
		}
	}

	// ãƒœã‚¹ã®å ´åˆã€€ãƒãƒƒã‚¯ã‚’é«˜é€Ÿã§å›ã™
	if (add_s < 40 && boss_flag) add_s += 1;

	// ãƒãƒƒã‚¯ã®ãƒ«ãƒ¼ãƒ—
	if (p_x <= -1200) {

		p_x = 0;
		p_w = WIDTH;
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// for_each‚ÍƒRƒ“ƒeƒiilist etc.j‚Ì first-last ‚É‘Î‚µ‚ÄŠÖ”‚Ì“K—p‚ğÀ‘•
	// \•¶‚Í [CAPTURE] (‰¼ˆø”ƒŠƒXƒg) {ŠÖ”‚Ì–{‘Ì}
	// Thing ƒŠƒXƒg‚É“ü‚é‘S‚Ä‚ÌƒNƒ‰ƒX‚Ì moveŠÖ”‚ğg—p
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->move(); });

	// Thing ƒŠƒXƒg‚É“ü‚é‘S‚Ä‚ÌƒNƒ‰ƒX‚Ì drawŠÖ”‚ğ‚ğg—p‚·‚é
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->draw(); });

	// “–‚½‚è”»’è‚ÌÀ‘•
	// ”ÍˆÍ‘S‚Ä‚ÌƒNƒ‰ƒX‚ÉŠÖ”‚ğu•iQÆjv‚É@ŠÖ”“à‚Å mob ‚ğg—po—ˆ‚é
	// ‚QŒÂ‚ÌƒNƒ‰ƒX‚ğg—p‚µ‚Ä‚¢‚éˆ×@‚±‚Ì•”•ª‚¾‚¯‚±‚ÌŒ`
	// “–‚½‚éê‡@—¼•û‚Ì hitŠÖ”‚ğ“K—p
	for_each(thing_list.begin(), thing_list.end(), [&](ThingPointa & main) {

		if (main->HIT_TYPE() == TYPE_NONE) return; // TYPE_NONE ‚Ìê‡@–³‹
=======
	// for_eachã¯ã‚³ãƒ³ãƒ†ãƒŠï¼ˆlist etc.ï¼‰ã® first-last ã«å¯¾ã—ã¦é–¢æ•°ã®é©ç”¨ã‚’å®Ÿè£…ã™ã‚‹
	// æ§‹æ–‡ã¯ [CAPTURE] (ä»®å¼•æ•°ãƒªã‚¹ãƒˆ) {é–¢æ•°ã®æœ¬ä½“}
	// Thing ãƒªã‚¹ãƒˆã«å…¥ã‚‹å…¨ã¦ã®ã‚¯ãƒ©ã‚¹ã® move()é–¢æ•°ã‚’ã‚’ä½¿ç”¨ã™ã‚‹
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->move(); });

	// Thing ãƒªã‚¹ãƒˆã«å…¥ã‚‹å…¨ã¦ã®ã‚¯ãƒ©ã‚¹ã® draw()é–¢æ•°ã‚’ã‚’ä½¿ç”¨ã™ã‚‹
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->draw(); });

	// å½“ãŸã‚Šåˆ¤å®šã®å®Ÿè£…ã‚’ã™ã‚‹
	// ç¯„å›²å…¨ã¦ã®ã‚¯ãƒ©ã‚¹ã«é–¢æ•°ã‚’ã€Œï¼†ï¼ˆå‚ç…§ï¼‰ã€ã«ã™ã‚‹ã“ã¨ã§ é–¢æ•°å†…ã§ mob ã‚’ä½¿ç”¨å‡ºæ¥ã‚‹
	// ï¼’å€‹ã®ã‚¯ãƒ©ã‚¹ã‚’ä½¿ç”¨ã—ã¦ã„ã‚‹ãŸã‚ ã“ã®éƒ¨åˆ†ã ã‘ã“ã®å½¢
	// å½“ãŸã‚‹å ´åˆ ä¸¡æ–¹ã® hit()é–¢æ•°ã‚’é©ç”¨ã™ã‚‹
	for_each(thing_list.begin(), thing_list.end(), [&](ThingPointa & main) {

		if (main->HIT_TYPE() == TYPE_NONE) return; // TYPE_NONEã®å ´åˆã€€ç„¡è¦–ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

		for_each(thing_list.begin(), thing_list.end(), [&](ThingPointa & mob) {

			// ä¸¡æ–¹ã® HIT ã‚¿ã‚¤ãƒ—ãƒ»GET ã‚¿ã‚¤ãƒ—ã‚’åˆ¤åˆ¥ã—ã¦ è¿”ã™ã‚¿ã‚¤ãƒ—ã®ç­‰ã—ã„å ´åˆ
			if (main->HIT_TYPE() == mob->GET_TYPE()) {

				// å½“ãŸã‚‹å ´åˆ
				if (main->HIT_test(mob)) {

<<<<<<< HEAD
					// hitŠÖ”‚ğ“K—p
					// ‘¹ŠQ—ÊE“Áê—Ê‚ÌŒvZ‚É GET_damageŠÖ”EGET_energyŠÖ”‚ğg—p
=======
					// hit()é–¢æ•°ã‚’é©ç”¨ã™ã‚‹
					// æå®³é‡ãƒ»ç‰¹æ®Šé‡ã®è¨ˆç®—ã« GET_damage()é–¢æ•°ãƒ»GET_energy()é–¢æ•°ã‚’ä½¿ç”¨ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
					main->hit(mob->GET_damage(), mob->GET_energy());
					mob->hit(main->GET_damage(), main->GET_energy());
				}
			}
		});
	});

	// shot_count ã‚’ãƒ—ãƒ©ã‚¹ã™ã‚‹
	shot_count++;

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------
=======
	// game_flag true ã®å ´åˆ
	if (game_flag) {

		// åˆ¶é™æ™‚é–“ã®è¨ˆç®—
		timer = (GetNowCount() - start_time) / 1000 - limit_time;
		now_time = -timer;
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	// ƒvƒŒƒC’†‚Ìê‡
	if (play_flag) {
		
		SetFontSize(20);
<<<<<<< HEAD
		DrawFormatString(WIDTH - 200, HEIGHT - 35, GetColor(255, 255, 255), "T I M E : %d", now_time); // §ŒÀŠÔ‚Ì•`‰æ
	
		// ƒ|[ƒYi‹x~jƒtƒ‰ƒO false ‚Ìê‡@“GE‰ñ•œ‚ğ¶¬
		if (!pause_flag) {

			// §ŒÀŠÔ‚ÌŒvZ
			now_time = (start_time - GetNowCount()) / 1000 + limit_time;

			// ƒXƒRƒA‚Q‚O‚O‚O‚O–¢–‚Ìê‡
			if (score < 20000) {

				//-------------------------------------------------------------------------------------
				// “G‚ÌoŒ»iSTAGE‚P`‚Xj

				// ENEMY1i•’Êj
				if (stage == 1 || stage == 2 || stage == 3 || stage == 5 || stage == 6 || stage == 7) { // oŒ» STAGE İ’è

					if (GetRand(40) == 0) {

						ThingPointa enemy1(new Enemy1); // “G¶¬
						ADD_list(enemy1); // Thing ƒŠƒXƒg‚É ENEMY1 ƒAƒhƒŒƒX‚ğ’Ç‰Á
						if (0 <= enemy_num) enemy_num += 1; // enemy_num ‚É+‚P
					}
				}

				//-------------------------------------------------------------------------------------
				// ENEMY2iƒ^ƒtj
=======
		DrawFormatString(WIDTH - 200, HEIGHT - 35, GetColor(255, 255, 255), "T I M E : %d", now_time); // åˆ¶é™æ™‚é–“ã®æç”»

		// ãƒãƒ¼ã‚ºï¼ˆä¼‘æ­¢ï¼‰ãƒ•ãƒ©ã‚° falseã§ã‚ã‚‹å ´åˆã€€æ•µãƒ»å›å¾©ã‚’ç”Ÿæˆ
		if (!pause_flag) {

			// ã‚¹ã‚³ã‚¢ï¼’ï¼ï¼ï¼ï¼æœªæº€ã®å ´åˆ
			if (score < 20000) {

				// æ•µã®å‡ºç¾ï¼ˆSTAGEï¼‘ï½ï¼™ï¼‰
				// ENEMY1ï¼ˆæ™®é€šï¼‰
				if (stage == 1 || stage == 2 || stage == 3 || stage == 5 || stage == 6 || stage == 7) { // å‡ºç¾ã™ã‚‹ STAGE è¨­å®š

					if (GetRand(40) == 0) {

						ThingPointa enemy1(new Enemy1); // æ•µç”Ÿæˆ
						ADD_list(enemy1); // Thing ãƒªã‚¹ãƒˆã« ENEMY1 ã‚¢ãƒ‰ãƒ¬ã‚¹ã‚’è¿½åŠ 

						if (0 <= enemy_num) enemy_num += 1; // enemy_num ã«+ï¼‘ã™ã‚‹
					}
				}

				// ENEMY2ï¼ˆã‚¿ãƒ•ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				if (stage == 1 || stage == 2 || stage == 3 || stage == 4 || stage == 5 || stage == 6 || stage == 8) {

					if (GetRand(80) == 0) {

						ThingPointa enemy2(new Enemy2);
						ADD_list(enemy2);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

<<<<<<< HEAD
				//-------------------------------------------------------------------------------------
				// ENEMY3iƒxƒNƒgƒ‹j
=======
				// ENEMY3ï¼ˆãƒ™ã‚¯ãƒˆãƒ«ï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				if (stage == 2 || stage == 4 || stage == 7 || stage == 8) {

					if (GetRand(100) == 0) {

						ThingPointa enemy3(new Enemy3);
						ADD_list(enemy3);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

<<<<<<< HEAD
				//-------------------------------------------------------------------------------------
				// ENEMY4i‚‘¬j
=======
				// ENEMY4ï¼ˆé«˜é€Ÿï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				if (stage == 3 || stage == 4 || stage == 7 || stage == 9) {

					if (GetRand(40) == 0) {

						ThingPointa enemy4(new Enemy4);
						ADD_list(enemy4);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

<<<<<<< HEAD
				//-------------------------------------------------------------------------------------
				// ENEMY5i’ÊíUŒ‚j
=======
				// ENEMY5ï¼ˆé€šå¸¸æ”»æ’ƒï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				if (stage == 5 || stage == 7 || stage == 9) {

					if (GetRand(120) == 0) {

						ThingPointa enemy5(new Enemy5);
						ADD_list(enemy5);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

<<<<<<< HEAD
				//-------------------------------------------------------------------------------------
				// ENEMY6iƒxƒNƒgƒ‹UŒ‚j
=======
				// ENEMY6ï¼ˆãƒ™ã‚¯ãƒˆãƒ«æ”»æ’ƒï¼‰
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				if (stage == 6 || stage == 8 || stage == 9) {

					if (GetRand(120) == 0) {

						ThingPointa enemy6(new Enemy6);
						ADD_list(enemy6);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}
			}

<<<<<<< HEAD
			//-------------------------------------------------------------------------------------
			// STAGE‚P‚O

=======
			// STAGEï¼‘ï¼
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			if (stage == 10) {

				if (0 <= score && score < 20000) {

					if (GetRand(50) == 0) {

						ThingPointa enemy1(new Enemy1);
						ADD_list(enemy1);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				if (0 <= score && score < 4000) {

					if (GetRand(20) == 0) {

						ThingPointa enemy2(new Enemy2);
						ADD_list(enemy2);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				if (4000 <= score && score < 8000) {

					if (GetRand(20) == 0) {

						ThingPointa enemy3(new Enemy3);
						ADD_list(enemy3);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				if (8000 <= score && score < 12000) {

					if (GetRand(10) == 0) {

						ThingPointa enemy4(new Enemy4);
						ADD_list(enemy4);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				if (12000 <= score && score < 16000) {

					if (GetRand(30) == 0) {

						ThingPointa enemy5(new Enemy5);
						ADD_list(enemy5);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				if (16000 <= score && score < 20000) {

					if (GetRand(40) == 0) {

						ThingPointa enemy6(new Enemy6);
						ADD_list(enemy6);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}
			}

<<<<<<< HEAD
			//-------------------------------------------------------------------------------------
			// ƒXƒRƒA ‚Q‚O‚O‚O‚OˆÈã ‚»‚µ‚Ä ƒ{ƒXƒtƒ‰ƒO false ‚Ìê‡@ƒ{ƒX‚ğ¶¬
=======
			// ã‚¹ã‚³ã‚¢ ï¼’ï¼ï¼ï¼ï¼ä»¥ä¸Š ãã—ã¦ ãƒœã‚¹ãƒ•ãƒ©ã‚° false ã®å ´åˆã€€ãƒœã‚¹ã‚’ç”Ÿæˆã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			if (20000 <= score && !boss_flag) {

				boss_flag = true; // ãƒœã‚¹ãƒ•ãƒ©ã‚°ã‚’ true ã«

				if (boss_flag) {

<<<<<<< HEAD
					StopSoundMem(Play_m); // ƒvƒŒƒC‰æ–Ê‚Ì‰¹‚ğ’â~
					PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP); // ƒ{ƒX‰æ–Ê‚Ì‰¹‚ğÄ¶
=======
					StopSoundMem(Play_m); // ãƒ—ãƒ¬ã‚¤ä¸­ã®éŸ³ã‚’åœæ­¢ã™ã‚‹
					PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP); // ãƒœã‚¹ä¸­ã®éŸ³ã‚’å†ç”Ÿã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

					// STAGEï¼‘ï½ï¼™ã®å ´åˆ
					if (stage <= 9) {

						ThingPointa enemy_boss1(new Enemy_Boss1);
						ADD_list(enemy_boss1);
					}

					// STAGEï¼‘ï¼ã®å ´åˆ
					if (stage == 10) {

						ThingPointa enemy_boss2(new Enemy_Boss2);
						ADD_list(enemy_boss2);
					}
				}
			}

<<<<<<< HEAD
			//-------------------------------------------------------------------------------------
			// í‚É¶¬@ ‰ñ•œ¶¬
=======
			// å¸¸ã«ç”Ÿæˆã™ã‚‹
			// å›å¾©ç”Ÿæˆ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			if (GetRand(350) == 0) {

				ThingPointa heal(new Heal1);
				ADD_list(heal);
			}

			if (GetRand(600) == 0) {

				ThingPointa heal2(new Heal2);
				ADD_list(heal2);
			}
		}

<<<<<<< HEAD
		//-------------------------------------------------------------------------------------
		// ƒ|[ƒYi‹x~j‰æ–Ê‚Ö
		if (PUSH_back()) {

			if (!pause_flag) {

				stop_time = GetNowCount(); // Œ»İŠÔ‚ğ“¾‚é
				PlaySoundMem(Pause_m, DX_PLAYTYPE_BACK); // ƒ|[ƒY‰æ–Ê‚Ì‰¹‚ğÄ¶
			}

			pause_flag = true;
			StopSoundMem(Play_m); // ƒvƒŒƒC‰æ–Ê‚Ì‰¹‚ğ’â~
			StopSoundMem(Boss_m); // ƒ{ƒX‰æ–Ê‚Ì‰¹‚ğ’â~
		}

		// ƒ|[ƒYi‹x~j‰æ–Ê
=======
		// ãƒãƒ¼ã‚ºï¼ˆä¼‘æ­¢ï¼‰ç”»é¢ã¸
		if (PUSH_back()) {

			if (!pause_flag) PlaySoundMem(Pause_m, DX_PLAYTYPE_BACK); // ãƒãƒ¼ã‚ºéŸ³ã®å†ç”Ÿã™ã‚‹

			pause_flag = true;
			StopSoundMem(Play_m); // ãƒ—ãƒ¬ã‚¤ä¸­ã®éŸ³ã‚’åœæ­¢ã™ã‚‹
			StopSoundMem(Boss_m); // ãƒœã‚¹ä¸­ã®éŸ³ã‚’åœæ­¢ã™ã‚‹
		}

		// ãƒãƒ¼ã‚ºï¼ˆä¼‘æ­¢ï¼‰ç”»é¢ã‚’æç”»ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		if (pause_flag) {

			DrawBox(150, 150, WIDTH - 150, HEIGHT - 150, GetColor(255, 255, 255), TRUE);
			DrawExtendGraph(170, 170, WIDTH - 170, 240, Pause_p, TRUE);
			DrawExtendGraph(160, 330, WIDTH - 160, 420, Esc_p, TRUE);

<<<<<<< HEAD
			pause_time = (GetNowCount() - stop_time) / 1000; // ƒ|[ƒYŠÔ‚ğŒvZ
			
			//-------------------------------------------------------------------------------------
			// ƒ|[ƒY‚ÌI—¹EÄŠJ
=======
			// ãƒãƒ¼ã‚ºã®çµ‚äº†ãƒ»å†é–‹ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			if (PUSH_space()) {

				pause_flag = false;
				limit_time = pause_time + limit_time; // ƒ|[ƒYŠÔ•ªƒvƒ‰ƒX‚·‚é
				pause_time = 0; // ‚O‚É

<<<<<<< HEAD
				// ƒ{ƒX–¢“oê‚Ìê‡@ƒvƒŒƒC’†‚Ì‰¹‚ğÄ¶
				if (!boss_flag) PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP);

				// ƒ{ƒX“oê’†‚Ìê‡@ƒ{ƒX’†‚Ì‰¹‚ğÄ¶
=======
				// ãƒœã‚¹æœªç™»å ´ã®å ´åˆã€€ãƒ—ãƒ¬ã‚¤ä¸­ã®éŸ³ã‚’å†ç”Ÿã™ã‚‹
				if (!boss_flag) PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP);

				// ãƒœã‚¹ã®å ´åˆã€€ãƒœã‚¹ä¸­ã®éŸ³ã‚’å†ç”Ÿã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				if (boss_flag) PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP);
			}
		}

<<<<<<< HEAD
		//-------------------------------------------------------------------------------------
		// ƒvƒŒƒC‚µ‚Ä‚¢‚éŠÔ@‰æ–Ê¶’[‚É•¶š‚ğ•`‰æ
		else DrawFormatString(50, HEIGHT - 35, GetColor(255, 255, 255), "B A C K  S P A C E : P A U S E");
	}

	//-------------------------------------------------------------------------------------
	// ƒvƒŒƒC‘O@•¶š‚ğ•`‰æ
	else {

		// B ‚ğ‰Ÿ‚·ê‡@PUSH SPACE ‚ğ•`‰æ
		if (CheckHitKey(KEY_INPUT_B)) space_flag = true; // ƒXƒy[ƒXƒtƒ‰ƒO‚ğ true ‚É
		if (space_flag) DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

		// ‘€ìŠm”F@•¶š‚ğ•`‰æ
		DrawFormatString(600, 140, GetColor(255, 255, 255), "¡ O P E R A T I N G  M E T H O D ¡");
=======
		// ãƒ—ãƒ¬ã‚¤ã—ã¦ã„ã‚‹é–“ã€€ç”»é¢å·¦ç«¯ã«æ–‡å­—ã‚’æç”»ã™ã‚‹
		else DrawFormatString(50, HEIGHT - 35, GetColor(255, 255, 255), "B A C K  S P A C E : P A U S E");
	}

	// game_flagã€€false ã®å ´åˆã€€æ–‡å­—ã‚’æç”»ã™ã‚‹
	else {

		// B ã‚’æŠ¼ã—ãŸå ´åˆã€€PUSH SPACE ã‚’æç”»ã™ã‚‹
		if (CheckHitKey(KEY_INPUT_B)) space_flag = true;
		if (space_flag) DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

		// æ“ä½œã€€æ–‡å­—ã‚’æç”»ã™ã‚‹
		DrawFormatString(600, 140, GetColor(255, 255, 255), "â–  O P E R A T I N G  M E T H O D â– ");
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		DrawFormatString(600, 170, GetColor(0, 255, 255), "B : S H O T");
		DrawFormatString(600, 200, GetColor(255, 255, 255), "E L S E : S P E C I A L  S H O T");
		DrawFormatString(600, 230, GetColor(0, 255, 255), "S C O R E : 2 0 0 0 0");

		DrawFormatString(600, 320, GetColor(255, 255, 255), "â–  H I N T â– ");
		DrawFormatString(600, 350, GetColor(0, 255, 255), "I F  Y O U  G E T  T H E  B L U E  H E A R T");
		DrawFormatString(600, 380, GetColor(0, 255, 255), "Y O U  C A N  U S E  S P E C I A L  S H O T ...");

<<<<<<< HEAD
		//-------------------------------------------------------------------------------------
		// SPACE ‚ğ‰Ÿ‚·ê‡@ƒvƒŒƒCƒXƒ^[ƒg
		if (PUSH_space()) {

			StopSoundMem(Title_m); // ƒ^ƒCƒgƒ‹‰æ–Ê‚Ì‰¹‚ğ’â~
			PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP); // ƒvƒŒƒC‰æ–Ê‚Ì‰¹‚ğÄ¶
			play_flag = true; // ƒvƒŒƒCƒtƒ‰ƒO‚ğ true ‚É
			start_time = GetNowCount(); // §ŒÀŠÔ‚ğƒXƒ^[ƒg
		}
	}

	//-------------------------------------------------------------------------------------
	// ƒ{ƒX–¢“oê‚Ìê‡@ƒXƒRƒA‚ğ¦‚·
=======
		// SPACE KEY ã‚’æŠ¼ã—ãŸå ´åˆã€€ãƒ—ãƒ¬ã‚¤ã‚¹ã‚¿ãƒ¼ãƒˆã™ã‚‹
		if (PUSH_space()) {

			StopSoundMem(Title_m); // ã‚¿ã‚¤ãƒˆãƒ«ä¸­ã®éŸ³ã‚’åœæ­¢ã™ã‚‹
			PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP); // ãƒ—ãƒ¬ã‚¤ä¸­ã®éŸ³ã‚’å†ç”Ÿã™ã‚‹
			game_flag = true; // game_flag ã‚’ trueã«ã™ã‚‹
			start_time = GetNowCount(); // æ™‚é–“çµŒéã‚’ã‚¹ã‚¿ãƒ¼ãƒˆã™ã‚‹
		}
	}

	// ãƒœã‚¹æœªç™»å ´ã®å ´åˆã€€ã‚¹ã‚³ã‚¢ã‚’ç¤ºã™
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (!boss_flag) {

		SetFontSize(20);
		DrawFormatString(WIDTH - 220, 15, GetColor(255, 255, 255), "S C O R E : %d", score);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------
	// ESC ‚ğ‰Ÿ‚·ê‡@ƒ^ƒCƒgƒ‹‰æ–Ê‚Ö
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {

		scene = 0; // ƒ^ƒCƒgƒ‹‰æ–Ê‚Ö
		StopSoundMem(Title_m); // ƒ^ƒCƒgƒ‹‰æ–Ê‚Ì‰¹‚ğ’â~
		StopSoundMem(Play_m); // ƒvƒŒƒC‰æ–Ê‚Ì‰¹‚ğ’â~
		StopSoundMem(Boss_m); // ƒ{ƒX‰æ–Ê‚Ì‰¹‚ğ’â~
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // ƒ^ƒCƒgƒ‹‰æ–Ê‚Ì‰¹‚ğÄ¶
	}

	//-------------------------------------------------------------------------------------
	// ƒXƒRƒA‚ÌãŒÀi‚Q‚O‚O‚O‚O‚Éİ’èj
	if (20000 <= score) score = 20000;

	//-------------------------------------------------------------------------------------
	// §ŒÀŠÔ‚O‚Ìê‡
	if (now_time < 0) {

		scene = 3; // ƒI[ƒo[‰æ–Ê‚Ö
		StopSoundMem(Play_m); // ƒvƒŒƒC‰æ–Ê‚Ì‰¹‚ğ’â~
		StopSoundMem(Boss_m); // ƒ{ƒX‰æ–Ê‚Ì‰¹‚ğ’â~
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // ƒI[ƒo[‰æ–Ê‚Ì‰¹‚ğÄ¶
	}

	//-------------------------------------------------------------------------------------
	// Thing ƒŠƒXƒg“à‚ÅğŒFuíœƒtƒ‰ƒO true v‚ÌƒNƒ‰ƒX‚ğœ‚¯‚éiremove_if ŠÖ”j
	// íœƒtƒ‰ƒO true ‚ÌƒNƒ‰ƒX‚ğ‘O‚É
	// ‚»‚µ‚Ä ‚»‚ÌƒNƒ‰ƒX‚ğ list.erase ‚Å Thing ƒŠƒXƒg‚ÅíœEƒŠƒXƒg“à‚ğŠñ‚¹‚é
=======
	// ESC ã‚’æŠ¼ã—ãŸå ´åˆã€€ã‚¿ã‚¤ãƒˆãƒ«ç”»é¢ã¸æˆ»ã‚‹
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {

		scene = 0;
		StopSoundMem(Title_m); // ã‚¿ã‚¤ãƒˆãƒ«ä¸­ã®éŸ³ã‚’åœæ­¢ã™ã‚‹
		StopSoundMem(Play_m); // ãƒ—ãƒ¬ã‚¤ä¸­ã®éŸ³ã‚’åœæ­¢ã™ã‚‹
		StopSoundMem(Boss_m); // ãƒœã‚¹ä¸­ã®éŸ³ã‚’åœæ­¢ã™ã‚‹
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // ã‚¿ã‚¤ãƒˆãƒ«ä¸­ã®éŸ³ã‚’å†ç”Ÿã™ã‚‹
	}

	// ã‚¹ã‚³ã‚¢ã®ä¸Šé™ï¼ˆï¼’ï¼ï¼ï¼ï¼ã«è¨­å®šï¼‰
	if (20000 <= score) score = 20000;

	// åˆ¶é™æ™‚é–“ï¼ã«ãªã£ãŸå ´åˆ
	if (now_time < 0) {

		scene = 3; // ã‚ªãƒ¼ãƒãƒ¼ç”»é¢ã¸
		StopSoundMem(Play_m); // ãƒ—ãƒ¬ã‚¤ä¸­ã®éŸ³ã‚’åœæ­¢ã™ã‚‹
		StopSoundMem(Boss_m); // ãƒœã‚¹ä¸­ã®éŸ³ã‚’åœæ­¢ã™ã‚‹
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // ã‚ªãƒ¼ãƒãƒ¼ä¸­ã®éŸ³ã‚’å†ç”Ÿã™ã‚‹
	}

	// Thing ãƒªã‚¹ãƒˆå†…ã§æ¡ä»¶ï¼šå‰Šé™¤ãƒ•ãƒ©ã‚° true ã®ã‚¯ãƒ©ã‚¹ã‚’é™¤ã‘ã‚‹ï¼ˆremove_if é–¢æ•°ï¼‰
	// å‰Šé™¤ãƒ•ãƒ©ã‚° true ã®ã‚¯ãƒ©ã‚¹ã‚’å‰ã«ã™ã‚‹
	// ãã—ã¦ ãã®ã‚¯ãƒ©ã‚¹ã‚’ list.erase ã«ã‚ˆã‚Š Thing ãƒªã‚¹ãƒˆã§å‰Šé™¤ãƒ»ãƒªã‚¹ãƒˆå†…ã‚’è©°ã‚ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	auto end = remove_if(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {return Thing->GET_remove(); });
	thing_list.erase(end, thing_list.end());
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 3 ‚Ìê‡@ƒI[ƒo[‰æ–Ê
=======
// scene == 3 ã®æ™‚ã€€ã‚ªãƒ¼ãƒãƒ¼ç”»é¢
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
void Game::GAME_OVER() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Over_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

<<<<<<< HEAD
	now_score = score; // ƒXƒRƒA‚É
=======
	now_score = score; // ã‚¹ã‚³ã‚¢ã«ç½®æ›ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Y O U R  S C O R E : %d", now_score);

<<<<<<< HEAD
	// ƒnƒCƒXƒRƒAƒƒXƒRƒA‚Ìê‡
	if (high_score < now_score) {

		// ’l‚ğã‘‚«E‹L˜^
=======
	// ãƒã‚¤ã‚¹ã‚³ã‚¢ã‚ˆã‚Šã‚¹ã‚³ã‚¢ãŒå¤§ãã„å ´åˆ
	if (high_score < now_score) {

		// å€¤ã‚’ä¸Šæ›¸ããƒ»è¨˜éŒ²ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		high_score = now_score;
		SAVE_highscore();
	}

<<<<<<< HEAD
	// SPACE ‚ğ‰Ÿ‚·ê‡@ƒ^ƒCƒgƒ‹‰æ–Ê‚Ö
=======
	// SPACE KEY ã‚’æŠ¼ã—ãŸå ´åˆã€€ã‚¿ã‚¤ãƒˆãƒ«ç”»é¢ã¸æˆ»ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Over_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 4 ‚Ìê‡@ƒNƒŠƒA‰æ–Ê
=======
// scene == 4 ã®æ™‚ã€€ã‚¯ãƒªã‚¢ç”»é¢
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
void Game::GAME_CLEAR() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Clear_p, TRUE);
<<<<<<< HEAD
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE

	// ƒXƒRƒA‚É
	// ƒXƒRƒA@@ŠÔƒXƒRƒA@{@ƒXƒRƒAiMAX‚Q‚O‚O‚O‚Oj@{@STAGE ~ 10000
=======
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE ã®æç”»

	// ã‚¹ã‚³ã‚¢ã«ç½®æ›ã™ã‚‹
	// ã‚¹ã‚³ã‚¢ã€€ï¼ã€€æ™‚é–“ã‚¹ã‚³ã‚¢ã€€ï¼‹ã€€ã‚¹ã‚³ã‚¢ï¼ˆMAXï¼’ï¼ï¼ï¼ï¼ï¼‰ã€€ï¼‹ã€€STAGE Ã— 10000
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	now_score = now_time * 100 + score + stage * 10000;

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Y O U R  S C O R E : %d", now_score);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "T I M E  P O I N T : %d + S C O R E : %d + S T A G E  P O I N T : %d", now_time * 100, score, stage * 10000);

<<<<<<< HEAD
	// ƒnƒCƒXƒRƒAƒƒXƒRƒA‚Ìê‡
	if (high_score < now_score) {

		// ’l‚ğã‘‚«E‹L˜^
=======
	// ãƒã‚¤ã‚¹ã‚³ã‚¢ã‚ˆã‚Šã‚¹ã‚³ã‚¢ãŒå¤§ãã„å ´åˆ
	if (high_score < now_score) {

		// å€¤ã‚’ä¸Šæ›¸ããƒ»è¨˜éŒ²ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		high_score = now_score;
		SAVE_highscore();
	}

<<<<<<< HEAD
	// SPACE ‚ğ‰Ÿ‚·ê‡ ƒ^ƒCƒgƒ‹‰æ–Ê‚Ö
=======
	// SPACE KEY ã‚’æŠ¼ã—ãŸå ´åˆ ã‚¿ã‚¤ãƒˆãƒ«ç”»é¢ã¸
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Clear_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

void Game::GAME_END() {

	DxLib_End(); // DXãƒ©ã‚¤ãƒ–ãƒ©ãƒªã®çµ‚äº†
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// WinMain ŠÖ”
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game; // Game ƒNƒ‰ƒX‚ğ game ‚É
=======
// WinMain é–¢æ•°
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game; // GAME ã‚¯ãƒ©ã‚¹ã‚’ game ã«ç½®æ›ã™ã‚‹
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	game.GAME_SET();
	game.GAME_ALL();
	game.GAME_END();
	return 0;
}
