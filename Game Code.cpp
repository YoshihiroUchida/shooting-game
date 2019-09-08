<<<<<<< HEAD
#include <iostream> // namespace を使用
#include <memory> // スマートポインタ（自動デストラクタ付）を使用
#include <list> // コンテナ（list）を使用
#include <algorithm> // for_each を使用
#include <cmath> // pow()（べき乗の計算）を使用
#include "DxLib.h" // DXライブラリを使用

using namespace std; // std::〜の構文を略す

//-------------------------------------------------------------------------------------

// 列挙型　関数のスイッチとして使用
// 画像
=======
// Visual Studio C++
#include <iostream> // namespace 繧剃ｽｿ逕ｨ縺吶ｋ
#include <memory> // 繧ｹ繝槭�ｼ繝医�昴う繝ｳ繧ｿ�ｼ郁�ｪ蜍輔ョ繧ｹ繝医Λ繧ｯ繧ｿ莉假ｼ峨ｒ菴ｿ逕ｨ縺吶ｋ
#include <list> // 繧ｳ繝ｳ繝�繝奇ｼ�list�ｼ峨ｒ菴ｿ逕ｨ縺吶ｋ
#include <algorithm> // for_each 繧剃ｽｿ逕ｨ縺吶ｋ
#include <cmath> // pow()�ｼ医∋縺堺ｹ励�ｮ險育ｮ暦ｼ峨ｒ菴ｿ逕ｨ縺吶ｋ
#include "DxLib.h" // DX繝ｩ繧､繝悶Λ繝ｪ繧剃ｽｿ逕ｨ縺吶ｋ

using namespace std; // std::�ｽ槭�ｮ讒区枚繧堤払縺�

// 蛻玲嫌蝙九��髢｢謨ｰ縺ｮ繧ｹ繧､繝�繝√→縺励※菴ｿ逕ｨ縺吶ｋ
// 逕ｻ蜒�
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
	TYPE_NUM, // 蛻玲嫌蟇ｾ縺ｮ謨ｰ
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// 音楽
=======
// 髻ｳ讌ｽ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
enum Sound {

	SOUND_SHOT1, // SHOT1 髻ｳ
	SOUND_SHOT2, // SHOT2 髻ｳ
	SOUND_CHARGE, // CHARGE 荳ｭ縺ｮ髻ｳ
	SOUND_CHARGE_SHOT, // CHARGE SHOT縺ｮ髻ｳ
	SOUND_ENEMY_SHOT, // ENEMY SHOT縺ｮ髻ｳ
	SOUND_BEAM, // BEAM 髻ｳ
	SOUND_E_ATTACK, // ENEMY 縺ｮ繧｢繧ｿ繝�繧ｯ髻ｳ
	SOUND_P_ATTACK, // PLAYER 縺ｮ繧｢繧ｿ繝�繧ｯ髻ｳ
	SOUND_HEAL, // 蝗槫ｾｩ髻ｳ
	SOUND_BREAK, // 遐ｴ螢企浹
	SOUND_NUM, // 蛻玲嫌蟇ｾ縺ｮ謨ｰ
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

class Thing; // スマートポインタ（自動デストラクタ付）の Thing クラスを作る為に宣言

// Thing クラス　スマートポインタ（shared_ptr で Thing 型）ThingPointa
// Game クラスでコンテナ（list）の型を使用
// new で確保したメモリを自動的に delete する
// typedef はデータ型へ別名を付ける
typedef shared_ptr <Thing> ThingPointa;

//-------------------------------------------------------------------------------------

// グローバル変数（コード全体に関連する変数）
int scene; // 画面
int stage; // STAGE
int score; // スコア
int shot_count = 0; // 弾の間隔調整　初期化
int enemy_x; // 敵の x 座標に
int enemy_y; // 敵の y 座標に
int enemy_num = 0; // 画面上の敵　初期化
int enemy_s; // 敵の速度
bool pause_flag; // ポーズ（休止）フラグ

int loaded_picture[TYPE_NUM]; // 画像配列
int loaded_sound[SOUND_NUM]; // 音配列

// 音ファイル格納用変数（Game クラス）
int Title_m; // タイトル画面
int Play_m; // プレイ画面
int Over_m; // オーバー画面
int Clear_m; // クリア画面
int Pause_m; // ポーズ（休止）画面
int Boss_m; // ボス画面

//-------------------------------------------------------------------------------------

// Thing クラス（継承クラス）
class Thing {

protected: // 子クラスに継承

	float m_x; // x 座標
	float m_y; // y 座標
	int m_w; // 横幅
	int m_h; // 縦幅
	int m_s; // 速度

	// 当たり判定用変数
	float hit_x; // x 座標
	float hit_y; // y 座標
	float hit_w; // 横幅
	float hit_h; // 縦幅

	int life_max; // 設定体力
	int life_now; // 今の体力
	int energy_max; // 設定特殊量
	int energy_now; // 今の特殊量
	int damage; // 損害量
	int energy; // 特殊量
	bool remove_flag; // 削除フラグ
	void remove(); // 削除フラグを true に

public:

	Thing(); // コンストラクタ（削除フラグを false に）
	void SET_picture(const char* file_name, ThingType thing); // const char* に　クラス用　画像
	virtual void SET_sound(const char* file_name, Sound sound); // const char* に　クラス用　音
	virtual void SET_position(int, int); // 座標を設定
	virtual void SET_hitarea(int, int, int, int); // 当たり判定を設定
	bool GET_remove(); // 削除フラグを得る
	bool HIT_test(ThingPointa&); // 当たり判定

	virtual ThingType GET_TYPE() = 0; // 自分のタイプを得る（純粋仮想）
	virtual ThingType HIT_TYPE(); // 当たるタイプを NONE に（仮想）

	int GET_damage(); // 損害量の処理
	int GET_energy(); // 特殊量の処理

	virtual void SET_angle(float a) {}; // 角度を設定
	virtual void SET_sign(int s) {}; // 符号を設定
	virtual void move() = 0; // 動作（純粋仮想）
	virtual void draw(); // 画像を描画
	virtual void life_draw(); // 体力を描画
	virtual void hit(int damage, int energy) = 0; // 当たり判定 true の場合　処理（純粋仮想）
};

//-------------------------------------------------------------------------------------

// Player クラス
=======
class Thing; // 繧ｹ繝槭�ｼ繝医�昴う繝ｳ繧ｿ�ｼ郁�ｪ蜍輔ョ繧ｹ繝医Λ繧ｯ繧ｿ莉假ｼ峨�ｮ Thing 繧ｯ繝ｩ繧ｹ繧剃ｽ懊ｋ轤ｺ縺ｫ螳｣險�縺吶ｋ

// Thing 繧ｯ繝ｩ繧ｹ縺ｮ繧ｹ繝槭�ｼ繝医�昴う繝ｳ繧ｿ�ｼ�shared_ptr 縺ｧ Thing 蝙具ｼ欝hingPointa 繧貞ｮ夂ｾｩ縺吶ｋ
// Game 繧ｯ繝ｩ繧ｹ縺ｧ繧ｳ繝ｳ繝�繝奇ｼ�list�ｼ峨�ｮ蝙九↓菴ｿ逕ｨ縺吶ｋ
// 繧ｹ繝槭�ｼ繝医�昴う繝ｳ繧ｿ縺ｯ new 縺ｧ遒ｺ菫昴＠縺溘Γ繝｢繝ｪ繧定�ｪ蜍慕噪縺ｫ delete 縺吶ｋ
// typedef 縺ｯ蜈�縲�縺ｮ繝�繝ｼ繧ｿ蝙九∈蛻･蜷阪ｒ莉倥¢繧�
typedef shared_ptr <Thing> ThingPointa;

// 繧ｰ繝ｭ繝ｼ繝舌Ν螟画焚�ｼ亥�ｨ菴薙↓髢｢騾｣縺吶ｋ螟画焚�ｼ�
int scene; // 逕ｻ髱｢
int stage; // STAGE
int score; // 繧ｹ繧ｳ繧｢
int shot_count = 0; // 蠑ｾ縺ｮ髢馴囈隱ｿ謨ｴ縲��ｼ舌↓險ｭ螳壹☆繧�
int enemy_x; // 謨ｵ縺ｮ x 蠎ｧ讓吶↓鄂ｮ縺�
int enemy_y; // 謨ｵ縺ｮ y 蠎ｧ讓吶↓鄂ｮ縺�
int enemy_num = 0; // 逕ｻ髱｢荳翫�ｮ謨ｵ縲��ｼ舌↓險ｭ螳壹☆繧�
int enemy_s; // 謨ｵ縺ｮ騾溷ｺｦ
bool pause_flag; // 繝昴�ｼ繧ｺ�ｼ井ｼ第ｭ｢�ｼ峨ヵ繝ｩ繧ｰ

int loaded_picture[TYPE_NUM]; // 逕ｻ蜒城�榊��
int loaded_sound[SOUND_NUM]; // 髻ｳ驟榊��

// 髻ｳ讌ｽ繝輔ぃ繧､繝ｫ譬ｼ邏咲畑螟画焚�ｼ�Game 繧ｯ繝ｩ繧ｹ縺ｫ縺ｦ險ｭ螳壹☆繧具ｼ�
int Title_m; // 繧ｿ繧､繝医Ν荳ｭ
int Play_m; // 繝励Ξ繧､荳ｭ
int Over_m; // 繧ｪ繝ｼ繝舌�ｼ荳ｭ
int Clear_m; // 繧ｯ繝ｪ繧｢荳ｭ
int Pause_m; // 繝昴�ｼ繧ｺ�ｼ井ｼ第ｭ｢�ｼ臥判髱｢
int Boss_m; // 繝懊せ荳ｭ

// Thing 繧ｯ繝ｩ繧ｹ�ｼ育ｶ呎価繧ｯ繝ｩ繧ｹ�ｼ�
class Thing {

protected: // 蟄舌け繝ｩ繧ｹ縺ｫ邯呎価縺吶ｋ

	float m_x; // x 蠎ｧ讓�
	float m_y; // y 蠎ｧ讓�
	int m_w; // 讓ｪ蟷�
	int m_h; // 邵ｦ蟷�
	int m_s; // 騾溷ｺｦ

	// 蠖薙◆繧雁愛螳壼､画焚
	float hit_x; // x 蠎ｧ讓�
	float hit_y; // y 蠎ｧ讓�
	float hit_w; // 讓ｪ蟷�
	float hit_h; // 邵ｦ蟷�

	int life_max; // 險ｭ螳壻ｽ灘鴨
	int life_now; // 莉翫�ｮ菴灘鴨
	int energy_max; // 險ｭ螳夂音谿企��
	int energy_now; // 莉翫�ｮ迚ｹ谿企��
	int damage; // 謳榊ｮｳ驥�
	int energy; // 迚ｹ谿企��
	bool remove_flag; // 蜑企勁繝輔Λ繧ｰ
	void remove(); // 蜑企勁繝輔Λ繧ｰ繧� true 縺ｫ縺吶ｋ

public:

	Thing(); // 繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ�ｼ亥炎髯､繝輔Λ繧ｰ繧� false 縺ｫ�ｼ�
	void SET_picture(const char* file_name, ThingType thing); // const char* 縺ｫ縺吶ｋ縲�繧ｯ繝ｩ繧ｹ縺ｫ逕ｻ蜒上ｒ鄂ｮ縺�
	virtual void SET_sound(const char* file_name, Sound sound); // const char* 縺ｫ縺吶ｋ縲�繧ｯ繝ｩ繧ｹ縺ｫ髻ｳ繧堤ｽｮ縺�
	virtual void SET_position(int, int); // 蛻晄悄蠎ｧ讓吶ｒ險ｭ螳壹☆繧�
	virtual void SET_hitarea(int, int, int, int); // 蠖薙◆繧雁愛螳壹ｒ險ｭ螳壹☆繧�
	bool GET_remove(); // 蜑企勁繝輔Λ繧ｰ繧貞ｾ励ｋ
	bool HIT_test(ThingPointa&); // 蠖薙◆繧雁愛螳壹�ｮ髢｢謨ｰ

	virtual ThingType GET_TYPE() = 0; // 閾ｪ蛻�縺ｮ繧ｿ繧､繝励ｒ蠕励ｋ�ｼ育ｴ皮ｲ倶ｻｮ諠ｳ�ｼ�
	virtual ThingType HIT_TYPE(); // 蠖薙◆繧九ち繧､繝励ｒ NONE 縺ｫ縺吶ｋ�ｼ井ｻｮ諠ｳ�ｼ�

	int GET_damage(); // 謳榊ｮｳ驥上�ｮ蜃ｦ逅�繧偵☆繧�
	int GET_energy(); // 迚ｹ谿企�上�ｮ蜃ｦ逅�繧偵☆繧�

	virtual void SET_angle(float a) {}; // 隗貞ｺｦ險ｭ螳壹☆繧�
	virtual void SET_sign(int s) {}; // 隨ｦ蜿ｷ險ｭ螳壹☆繧�
	virtual void move() = 0; // 陦悟虚遽�蝗ｲ�ｼ育ｴ皮ｲ倶ｻｮ諠ｳ�ｼ�
	virtual void draw(); // 逕ｻ蜒乗緒逕ｻ繧偵☆繧�
	virtual void life_draw(); // 菴灘鴨謠冗判繧偵☆繧�
	virtual void hit(int damage, int energy) = 0; // 蠖薙◆繧雁愛螳� true 縺ｮ譎ゅ��蜃ｦ逅�繧偵☆繧具ｼ育ｴ皮ｲ倶ｻｮ諠ｳ�ｼ�
};

// Player 繧ｯ繝ｩ繧ｹ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Player : public Thing {

private:

<<<<<<< HEAD
	int charge_time; // charge 計測（拡大弾用）
	int dead_time; // dead 計測（点滅用）
	bool beam_flag; // beam フラグ
	bool shot_flag; // shot フラグ

public:

	Player(); // コンストラクタ（設定）
	ThingType GET_TYPE(); // 自分を PLAYER タイプで返す
	ThingType HIT_TYPE(); // 当たるタイプを ENEMY1 タイプで返す
	void move(); // 自機の動作　弾操作　画面の当たり判定
	void heart_draw(); // 体力の描画
	void energy_draw(); // 特殊量の描画
	void draw(); // dead_time の値で点滅
	void hit(int damage, int energy); // dead_time を５０に
};

//-------------------------------------------------------------------------------------

// Shot クラス（通常弾）
=======
	int charge_time; // charge 繧ｫ繧ｦ繝ｳ繝�
	int dead_time; // dead 繧ｫ繧ｦ繝ｳ繝茨ｼ育せ貊��ｼ�
	bool beam_flag; // beam 繝輔Λ繧ｰ
	bool shot_flag; // shot 繝輔Λ繧ｰ

public:

	Player(); // 繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ�ｼ亥�晄悄險ｭ螳夲ｼ�
	ThingType GET_TYPE(); // 閾ｪ蛻�繧� PLAYER 繧ｿ繧､繝励〒霑斐☆
	ThingType HIT_TYPE(); // 蠖薙◆繧九ち繧､繝励ｒ ENEMY1 繧ｿ繧､繝励〒霑斐☆
	void move(); // 陦悟虚遽�蝗ｲ繝ｻ繧｢繧ｿ繝�繧ｯ繝ｻ逕ｻ髱｢縺ｮ蠖薙◆繧雁愛螳�
	void heart_draw(); // 菴灘鴨縺ｮ謠冗判繧偵☆繧�
	void energy_draw(); // 迚ｹ谿企�上�ｮ謠冗判繧偵☆繧�
	void draw(); // 謳榊ｮｳ驥上↓蟇ｾ縺励※轤ｹ貊�縺吶ｋ
	void hit(int damage, int energy); // 轤ｹ貊�繧抵ｼ包ｼ舌↓縺吶ｋ
};

// Shot 繧ｯ繝ｩ繧ｹ�ｼ磯�壼ｸｸ蠑ｾ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Shot : public Thing {

protected:

	float angle; // 蜀�縺ｮ隗貞ｺｦ
	float center_x; // 荳ｭ蠢� x 蠎ｧ讓�
	float center_y; // 荳ｭ蠢� y 蠎ｧ讓�
	float shot_s; // 蠑ｾ縺ｮ騾溷ｺｦ

public:

<<<<<<< HEAD
	Shot(); // コンストラクタ（設定）
	ThingType GET_TYPE(); // 自分を SHOT1 タイプで返す
	ThingType HIT_TYPE(); // 当たる敵を ENEMY1 タイプで返す
	void move(); // 右方向へ　画面端で削除
	void draw(); // 描画
	void hit(int damage, int energy); // 処理　削除
};

//-------------------------------------------------------------------------------------

// Through Shot クラス（貫通弾）
=======
	Shot(); // 繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ�ｼ亥�晄悄險ｭ螳夲ｼ�
	ThingType GET_TYPE(); // 閾ｪ蛻�繧� SHOT1 繧ｿ繧､繝励〒霑斐☆
	ThingType HIT_TYPE(); // 蠖薙◆繧区雰繧� ENEMY1 繧ｿ繧､繝励〒霑斐☆
	void move(); // 蜿ｳ譁ｹ蜷代∈縲�逕ｻ髱｢縺ｮ遶ｯ縺ｧ蜑企勁縺吶ｋ
	void draw(); // 謠冗判縺吶ｋ
	void hit(int damage, int energy); // 蜃ｦ逅�繝ｻ蜑企勁縺吶ｋ
};

// Through Shot 繧ｯ繝ｩ繧ｹ�ｼ郁ｲｫ騾壼ｼｾ�ｼ�
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

// Beam クラス（光線）
=======
// Beam 繧ｯ繝ｩ繧ｹ�ｼ亥�臥ｷ夲ｼ�
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

// Vortex Shot クラス（渦弾）
=======
// Vortex Shot 繧ｯ繝ｩ繧ｹ�ｼ域ｸｦ蠑ｾ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Vortex_Shot : public Through_Shot {

private:

	float rad; // 蜊雁ｾ�

public:

	Vortex_Shot();
<<<<<<< HEAD
	void SET_position(int, int); // 座標を設定
=======
	void SET_position(int, int); // 蛻晄悄菴咲ｽｮ繧定ｨｭ螳壹☆繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Spray Shot クラス（散布弾）
=======
// Spray Shot 繧ｯ繝ｩ繧ｹ�ｼ域淵蟶�蠑ｾ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Spray_Shot : public Through_Shot {

public:

	Spray_Shot();
	void SET_angle(float a); // 角度を設定
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Rasen Shot クラス（螺旋弾）
=======
// Rasen Shot 繧ｯ繝ｩ繧ｹ�ｼ郁楴譌句ｼｾ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Rasen_Shot : public Shot {

private:

	int sign; // 1 or -1�ｼ育ｬｦ蜿ｷ譬ｼ邏搾ｼ�

public:

	Rasen_Shot();
	void SET_position(int, int);
	void SET_sign(int s); // 符号を設定
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Charge Shot クラス（拡大弾）
=======
// Charge Shot 繧ｯ繝ｩ繧ｹ�ｼ域僑螟ｧ蠑ｾ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Charge_Shot : public Shot {

private:

	bool charge_flag; // charge 繝輔Λ繧ｰ

public:

	Charge_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot1 クラス（時限弾）
=======
// Period Shot1 繧ｯ繝ｩ繧ｹ�ｼ域凾髯仙ｼｾ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Period_Shot1 : public Thing {

private:

	int shot_time; // 逋ｺ蟆�縺ｾ縺ｧ縺ｮ譎る俣
	int shot_count; // 逋ｺ蟆�縺吶ｋ謨ｰ

public:

	Period_Shot1();
	// 蠖薙◆繧雁愛螳堙励��繧ｿ繧､繝励ｒ NONE 縺ｧ霑斐☆
	ThingType GET_TYPE();
	ThingType HIT_TYPE();
	void move();
	void draw();
	void hit(int damage, int energy) {};
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot2 クラス（上・下）
=======
// Period Shot2 繧ｯ繝ｩ繧ｹ�ｼ井ｸ翫�ｻ荳具ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Period_Shot2 : public Through_Shot {

protected:

	int sign; // 符号

public:

	Period_Shot2();
	void SET_sign(int s);
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot3 クラス（左・右）
=======
// Period Shot3 繧ｯ繝ｩ繧ｹ�ｼ亥ｷｦ繝ｻ蜿ｳ�ｼ�
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

// Homing Shot クラス（追尾弾）
=======
// Homing Shot 繧ｯ繝ｩ繧ｹ�ｼ郁ｿｽ蟆ｾ蠑ｾ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Homing_Shot : public Shot {

public:

	Homing_Shot();
<<<<<<< HEAD
	void move(); // 敵を追尾
=======
	void move(); // 謨ｵ繧定ｿｽ蟆ｾ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Parabola Shot クラス（放物線弾）
=======
// Parabola Shot 繧ｯ繝ｩ繧ｹ�ｼ郁ｿｽ蟆ｾ繝ｻ謾ｾ迚ｩ邱壼ｼｾ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Parabola_Shot : public Shot {

	// 謾ｾ迚ｩ邱壹↓髢｢縺吶ｋ螟画焚
	float a;
	float b;
	float c;

public:

	Parabola_Shot();
<<<<<<< HEAD
	void SET_position(int, int); // 座標を設定
=======
	void SET_position(int, int); // 蛻晄悄菴咲ｽｮ繝ｻ蠎ｧ讓吶ｒ豎ゅａ繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy1 クラス（通常）
=======
// Enemy1 繧ｯ繝ｩ繧ｹ�ｼ磯�壼ｸｸ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy1 : public Thing {

protected:

<<<<<<< HEAD
	int count; // 爆破して削除するまでの数値に
	int up_down; // 上下方向
	bool count_flag; // 爆破フラグ
=======
	int count; // 辷�遐ｴ縺励※蜑企勁縺吶ｋ縺ｾ縺ｧ縲�謨ｰ蛟､繧貞�･繧後ｋ
	int up_down; // 荳贋ｸ区婿蜷�
	bool count_flag; // 辷�遐ｴ繝輔Λ繧ｰ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

public:

	Enemy1();
<<<<<<< HEAD
	ThingType GET_TYPE(); // 自分を ENEMY1 タイプで返す
	ThingType HIT_TYPE(); // 当たる敵を PLAYER タイプで返す
=======
	ThingType GET_TYPE(); // 閾ｪ蛻�繧� ENEMY1 繧ｿ繧､繝励→霑斐☆
	ThingType HIT_TYPE(); // 蠖薙◆繧区雰繧� PLAYER 繧ｿ繧､繝励→霑斐☆
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy); // ENEMY1�ｽ�6縺ｾ縺ｧ蜈ｱ騾夊ｨｭ螳�
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy2 クラス（タフ）
=======
// Enemy2 繧ｯ繝ｩ繧ｹ�ｼ医ち繝包ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy2 : public Enemy1 {

public:

	Enemy2();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy3 クラス（ベクトル）
=======
// Enemy3 繧ｯ繝ｩ繧ｹ�ｼ医�吶け繝医Ν�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy3 : public Enemy1 {

public:

	Enemy3();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy4 クラス（高速）
=======
// Enemy4 繧ｯ繝ｩ繧ｹ�ｼ磯ｫ倬�滂ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy4 : public Enemy1 {

public:

	Enemy4();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy5 クラス（通常攻撃）
=======
// Enemy5 繧ｯ繝ｩ繧ｹ�ｼ磯�壼ｸｸ謾ｻ謦��ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy5 : public Enemy1 {

public:

	Enemy5();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy6 クラス（ベクトル攻撃）
=======
// Enemy6 繧ｯ繝ｩ繧ｹ�ｼ医�吶け繝医Ν謾ｻ謦��ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy6 : public Enemy1 {

public:

	Enemy6();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Boss1 クラス（STAGE１〜９まで共通）
=======
// Enemy Boss1 繧ｯ繝ｩ繧ｹ�ｼ�STAGE�ｼ托ｽ橸ｼ吶∪縺ｧ蜈ｱ騾夲ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy_Boss1 : public Enemy1 {

protected:

	int add_speed; // 騾溷ｺｦ繧剃ｸ翫£繧�
	int Warn_p; // WARNING!!

public:

	Enemy_Boss1();
	void move();
<<<<<<< HEAD
	void life_draw(); // 体力を描画
=======
	void life_draw(); // 菴灘鴨繧呈緒逕ｻ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Boss2 クラス（STAGE１０）
=======
// Enemy Boss2 繧ｯ繝ｩ繧ｹ�ｼ�STAGE�ｼ托ｼ撰ｼ�
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

// Enemy Shot1 クラス（ボス用）
=======
// Enemy Shot1 繧ｯ繝ｩ繧ｹ�ｼ医�懊せ逕ｨ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy_Shot1 : public Thing {

public:

	Enemy_Shot1();
<<<<<<< HEAD
	ThingType GET_TYPE(); // 自分を ENEMY_SHOT1 タイプで返す
	ThingType HIT_TYPE(); // 当たる敵を PLAYER タイプで返す
=======
	ThingType GET_TYPE(); // 閾ｪ蛻�繧� ENEMY_SHOT1 繧ｿ繧､繝励→霑斐☆
	ThingType HIT_TYPE(); // 蠖薙◆繧区雰繧� PLAYER 繧ｿ繧､繝励→霑斐☆
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Shot2 クラス（ENEMY5・6用）
=======
// Enemy Shot2 繧ｯ繝ｩ繧ｹ�ｼ�ENEMY5繝ｻ6逕ｨ�ｼ�
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

// Heal1 クラス（体力回復）
=======
// Heal1 繧ｯ繝ｩ繧ｹ�ｼ井ｽ灘鴨蝗槫ｾｩ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Heal1 : public Thing {

public:

	Heal1();
<<<<<<< HEAD
	ThingType GET_TYPE(); // 自分を HEAL1 タイプで返す
	ThingType HIT_TYPE(); // 当たるものを PLAYER タイプで返す
=======
	ThingType GET_TYPE(); // 閾ｪ蛻�繧� HEAL1 繧ｿ繧､繝励→霑斐☆
	ThingType HIT_TYPE(); // 蠖薙◆繧九ｂ縺ｮ繧� PLAYER 繧ｿ繧､繝励→霑斐☆
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Heal2 クラス（特殊量回復）
=======
// Heal2 繧ｯ繝ｩ繧ｹ�ｼ育音谿企�丞屓蠕ｩ�ｼ�
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

// Game クラス
class Game {

	std::list <ThingPointa> thing_list; // Thing クラス　スマートポインタをリスト（list）型データ構造（thing_list）に
=======
// Game 繧ｯ繝ｩ繧ｹ
class Game {

	std::list <ThingPointa> thing_list; // Thing 繧ｯ繝ｩ繧ｹ縺ｮ繧ｹ繝槭�ｼ繝医�昴う繝ｳ繧ｿ繧� list 蝙九ョ繝ｼ繧ｿ讒矩���ｼ�thing_list�ｼ峨↓蜈･繧後ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

private:

	// 繝舌ャ繧ｯ逕ｨ螟画焚
	int p_x; // x 蠎ｧ讓呻ｼ医Ν繝ｼ繝嶺ｻ墓ｧ假ｼ�
	int p_w; // 讓ｪ蟷�
	int add_s; // 騾溷ｺｦ

<<<<<<< HEAD
	// 画像読込用変数
	int Game_p; // バック
=======
	// 逕ｻ蜒剰ｪｭ霎ｼ逕ｨ螟画焚
	int Game_p; // 繝舌ャ繧ｯ縺ｮ逕ｻ蜒�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	int Title_p; // SHOOTING GAME
	int Select_p; // STAGE SELECT
	int Number_p; // 1 2 3 4 5 6 7 8 9 10
	int Push_p; // PUSH SPACE
	int Over_p; // GAME OVER
	int Clear_p; // GAME CLEAR
	int Pause_p; // PAUSE
	int Esc_p; // ESC : TITLE・SPACE : REPLAY

<<<<<<< HEAD
	// フラグ変数
	bool push_flag; // PUSH_space関数・PUSH_back関数用
	bool play_flag; // プレイ用・true でスタート
	bool boss_flag; // ボス用
	bool space_flag; // スペース用

	// スコア・時間に関する変数
	int high_score; // ハイスコア（high_score < now_score の場合）
	int now_score; // スコア
	int now_time; // 残り時間
	int start_time; // １s 単位で計測する
	int stop_time; // ポーズする場合　現在時間を得る
	int pause_time; // ポーズ画面の経過時間
	int limit_time; // 制限時間
=======
	// 繝輔Λ繧ｰ逕ｨ螟画焚
	bool push_flag; // SPACE or BACK SPACE 逕ｨ繝輔Λ繧ｰ
	bool game_flag; // true 縺ｧ繧ｹ繧ｿ繝ｼ繝医☆繧�
	bool boss_flag; // Boss 繝輔Λ繧ｰ
	bool space_flag; // PUSH SPACE 繝輔Λ繧ｰ

	// 繧ｹ繧ｳ繧｢險倬鹸逕ｨ螟画焚
	int high_score; // 繝上う繧ｹ繧ｳ繧｢�ｼ�high_score < now_score 縺ｮ蝣ｴ蜷茨ｼ�
	int now_score; // 繧ｹ繧ｳ繧｢縺ｫ鄂ｮ謠�
	int timer; // 繧ｿ繧､繝槭�ｼ
	int now_time; // 谿九ｊ譎る俣繧定ｨ倬鹸縺吶ｋ
	int start_time; // �ｼ壮 蜊倅ｽ阪〒險域ｸｬ縺吶ｋ
	int limit_time; // 蛻ｶ髯先凾髢�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

public:

	// 逕ｻ髱｢逕ｨ螟画焚
	static const int WIDTH = 1200; // 讓ｪ蟷�
	static const int HEIGHT = 600; // 邵ｦ蟷�

<<<<<<< HEAD
	void ADD_list(ThingPointa&); // Thing クラス　スマートポインタにリスト（list）を追加
	void ADD_score(int sc); // スコアを追加
	bool PUSH_space(); // SPACE 操作
	bool PUSH_back(); // BACK SPACE 操作

	// スコアの記録を実装する関数
	void LOAD_highscore(); // 読込
	void SAVE_highscore(); // 保存

	void GAME_SET(); // 設定
	void GAME_ALL(); // 分岐
	void GAME_TITLE(); // タイトル画面
	void GAME_SELECT(); // 選択画面
	void GAME_PLAY(); // プレイ画面
	void GAME_OVER(); // オーバー画面
	void GAME_CLEAR(); // クリア画面
	void GAME_END(); // 終了
};

//-------------------------------------------------------------------------------------

Game* game; // Game クラスのメモリを確保　実体（インスタンス）化

//-------------------------------------------------------------------------------------
=======
	void ADD_list(ThingPointa&); // Thing 繧ｯ繝ｩ繧ｹ縲�繧ｹ繝槭�ｼ繝医�昴う繝ｳ繧ｿ縺ｫ繝ｪ繧ｹ繝茨ｼ�list�ｼ峨ｒ霑ｽ蜉�縺吶ｋ
	void ADD_score(int sc); // 繧ｹ繧ｳ繧｢繧定ｿｽ蜉�縺吶ｋ
	bool PUSH_space(); // SPACE 謫堺ｽ�
	bool PUSH_back(); // BACK SPACE 謫堺ｽ�

	// 繧ｹ繧ｳ繧｢縺ｮ險倬鹸繧貞ｮ溯｣�縺吶ｋ髢｢謨ｰ
	void LOAD_highscore(); // 繧ｹ繧ｳ繧｢隱ｭ霎ｼ
	void SAVE_highscore(); // 繧ｹ繧ｳ繧｢菫晏ｭ�

	void GAME_SET(); // 蛻晄悄險ｭ螳�
	void GAME_ALL(); // 蛻�蟯�

	void GAME_TITLE(); // 繧ｿ繧､繝医Ν逕ｻ髱｢
	void GAME_SELECT(); // 謫堺ｽ懆ｪｬ譏�
	void GAME_PLAY(); // 繝励Ξ繧､逕ｻ髱｢
	void GAME_OVER(); // 繧ｪ繝ｼ繝舌�ｼ逕ｻ髱｢
	void GAME_CLEAR(); // 繧ｯ繝ｪ繧｢逕ｻ髱｢

	void GAME_END(); // 邨ゆｺ�
};

Game* game; // Game 繧ｯ繝ｩ繧ｹ縺ｮ繝｡繝｢繝ｪ繧堤｢ｺ菫昴＠縺ｦ螳滉ｽ難ｼ医う繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ�ｼ牙喧縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

// Thing 繧ｯ繝ｩ繧ｹ縺ｮ螳溯｣�
void Thing::remove() {

<<<<<<< HEAD
	remove_flag = true; // 削除フラグを true に
=======
	remove_flag = true; // 蜑企勁繝輔Λ繧ｰ繧� true 縺ｫ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

Thing::Thing() {

<<<<<<< HEAD
	remove_flag = false; // 削除フラグを false に
	pause_flag = false; // ポーズ（休止）フラグを false に
=======
	remove_flag = false; // 蜑企勁繝輔Λ繧ｰ繧� false 縺ｫ縺吶ｋ
	pause_flag = false; // 繝昴�ｼ繧ｺ�ｼ井ｼ第ｭ｢�ｼ峨ヵ繝ｩ繧ｰ繧� false 縺ｫ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Thing::SET_picture(const char* file_name, ThingType thing) {

<<<<<<< HEAD
	// loaded_picture は０の場合　LoadGraph を実装
=======
	// loaded_picture 縺ｯ�ｼ舌�ｮ蝣ｴ蜷医��LoadGraph 繧貞ｮ溯｣�縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (loaded_picture[thing] == 0) {

		loaded_picture[thing] = LoadGraph(file_name);
	}

<<<<<<< HEAD
	hit_w = m_w; // 横幅を hit_w に
	hit_h = m_h; // 縦幅を hit_ h に
	hit_x = hit_y = 0; // 左上座標を０に
=======
	hit_w = m_w; // 讓ｪ蟷�縲�蠖薙◆繧雁愛螳壹↓鄂ｮ縺�
	hit_h = m_h; // 邵ｦ蟷�縲�蠖薙◆繧雁愛螳壹↓鄂ｮ縺�
	hit_x = hit_y = 0; // 蠖薙◆繧雁愛螳壹��蟾ｦ荳雁ｺｧ讓吶ｒ�ｼ舌↓縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Thing::SET_sound(const char* file_name, Sound sound) {

<<<<<<< HEAD
	// loaded_sound は０の場合　LoadSoundMem を実装
=======
	// loaded_sound 縺ｯ�ｼ舌�ｮ蝣ｴ蜷医��LoadSoundMem 繧貞ｮ溯｣�縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (loaded_sound[sound] == 0) {

		loaded_sound[sound] = LoadSoundMem(file_name);
	}
}

void Thing::SET_position(int position_x, int position_y) {

<<<<<<< HEAD
	m_x = position_x; // 設定値を m_x（x 座標） に
	m_y = position_y; // 設定値を m_y（y 座標）に
=======
	m_x = position_x; // 險ｭ螳壼�､繧� m_x�ｼ�x 蠎ｧ讓呻ｼ� 縺ｫ蜈･繧後ｋ
	m_y = position_y; // 險ｭ螳壼�､繧� m_y�ｼ�y 蠎ｧ讓呻ｼ峨↓蜈･繧後ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Thing::SET_hitarea(int h_x, int h_y, int h_w, int h_h) {

<<<<<<< HEAD
	hit_x = h_x; // 相対的 x 座標を設定
	hit_y = h_y; // 相対的 y 座標を設定
	hit_w = h_w; // 横幅を設定
	hit_h = h_h; // 縦幅を設定
=======
	hit_x = h_x; // 逶ｸ蟇ｾ逧� x 蠎ｧ讓吶ｒ險ｭ螳壹☆繧�
	hit_y = h_y; // 逶ｸ蟇ｾ逧� y 蠎ｧ讓吶ｒ險ｭ螳壹☆繧�
	hit_w = h_w; // 讓ｪ蟷�繧定ｨｭ螳壹☆繧�
	hit_h = h_h; // 邵ｦ蟷�繧定ｨｭ螳壹☆繧�
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
	// 左上(m_x, m_y)					右上(m_x + m_w, m_y)
	// 左下(m_x, m_y + m_h)		右下(m_x + m_w, m_y + m_h)
	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[GET_TYPE()], TRUE); // TRUE は画像の無色をクリアに
=======
	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[GET_TYPE()], TRUE); // 蠎ｧ讓吩ｽ咲ｽｮ縺ｫ謠冗判縺吶ｋ縲�TRUE 縺ｯ逕ｻ蜒上ヰ繝�繧ｯ繧偵け繝ｪ繧｢縺ｫ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Thing::life_draw() {

	if (0 < life_now) {

		DrawExtendGraph(m_x, m_y - 15, m_x + 65, m_y - 10, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(m_x, m_y - 15, m_x + (65 * life_now) / life_max, m_y - 10, loaded_picture[TYPE_LIFE], TRUE); // 菴灘鴨縺ｮ蛟､縺ｧ蟾ｦ縺ｸ縺壹ｌ繧�
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
	// 画像同士の当たり判定座標
	int x_1 = m_x + hit_x; // x 座標
	int y_1 = m_y + hit_y; // y 座標
	int w_1 = hit_w; // 横幅
	int h_1 = hit_h; // 縦幅

	// 対応する当たり判定座標
	int x_2 = other->m_x + other->hit_x; // x 座標
	int y_2 = other->m_y + other->hit_y; // y 座標
	int w_2 = other->hit_w; // 横幅
	int h_2 = other->hit_h; // 縦幅

	// 当たり判定
=======
	// 逕ｻ蜒丞酔螢ｫ縺ｮ蠖薙◆繧雁愛螳�
	int x_1 = m_x + hit_x; // 蠖薙◆繧雁愛螳夲ｼ�x 蠎ｧ讓呻ｼ�
	int y_1 = m_y + hit_y; // 蠖薙◆繧雁愛螳夲ｼ�y 蠎ｧ讓呻ｼ�
	int w_1 = hit_w; // 蠖薙◆繧雁愛螳夲ｼ域ｨｪ蟷��ｼ�
	int h_1 = hit_h; // 蠖薙◆繧雁愛螳夲ｼ育ｸｦ蟷��ｼ�

	int x_2 = other->m_x + other->hit_x; // 蟇ｾ蠢懊☆繧句ｽ薙◆繧雁愛螳夲ｼ�x 蠎ｧ讓呻ｼ�
	int y_2 = other->m_y + other->hit_y; // 蟇ｾ蠢懊☆繧句ｽ薙◆繧雁愛螳夲ｼ�y 蠎ｧ讓呻ｼ�
	int w_2 = other->hit_w; // 蟇ｾ蠢懊☆繧句ｽ薙◆繧雁愛螳夲ｼ域ｨｪ蟷��ｼ�
	int h_2 = other->hit_h; // 蟇ｾ蠢懊☆繧句ｽ薙◆繧雁愛螳夲ｼ育ｸｦ蟷��ｼ�

	// 蠖薙◆繧雁愛螳壹�ｮ險ｭ螳�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (x_2 < x_1 + w_1 &&
		x_1 < x_2 + w_2 &&
		y_2 < y_1 + h_1 &&
		y_1 < y_2 + h_2) return true;

	return false; // 荳願ｨ倅ｻ･螟悶�ｯ false 縺ｫ
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Player クラスの実装
=======
// Player 繧ｯ繝ｩ繧ｹ縺ｮ螳溯｣�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Player::Player() {

	m_w = 80; // 讓ｪ蟷�
	m_h = 50; // 邵ｦ蟷�
	m_s = 8; // 騾溷ｺｦ

<<<<<<< HEAD
	// 画像を設定
=======
	// 逕ｻ蜒上ｒ險ｭ螳壹☆繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	SET_picture("PLAYER.png", TYPE_PLAYER);
	SET_picture("HEART.png", TYPE_HEART);
	SET_picture("ENERGY.png", TYPE_ENERGY);

<<<<<<< HEAD
	SET_position(150, 300); // x・y 座標を設定
	SET_hitarea(10, 10, 70, 40); // 当たり判定を設定
	life_max = 5; // ライフを設定
	life_now = life_max; // ライフの値を設定ライフに
	energy_max = 1; // 特殊力を設定
	energy_now = energy_max; // 特殊力の値を設定特殊力に
	damage = 0; // 損害量
	energy = 0; // 特殊量
	shot_flag = false; // shot フラグを false に
	beam_flag = false; // beam フラグを false に
	dead_time = 0; // deat_time を０に
	SET_sound("SHOT1.mp3", SOUND_SHOT1); // Shot 音
	SET_sound("E ATTACK.mp3", SOUND_E_ATTACK); // 損害音
=======
	SET_position(150, 300); // x繝ｻy 蠎ｧ讓吶ｒ險ｭ螳壹☆繧�
	SET_hitarea(10, 10, 70, 40); // 蠖薙◆繧雁愛螳壹ｒ險ｭ螳壹☆繧�
	life_max = 5; // 蛻晄悄繝ｩ繧､繝輔ｒ險ｭ螳壹☆繧�
	life_now = life_max; // 莉翫�ｮ繝ｩ繧､繝輔↓蛻晄悄繝ｩ繧､繝輔ｒ鄂ｮ縺�
	energy_max = 1; // 蛻晄悄迚ｹ谿雁鴨繧定ｨｭ螳壹☆繧�
	energy_now = energy_max; // 莉翫�ｮ迚ｹ谿雁鴨縺ｫ蛻晄悄迚ｹ谿雁鴨繧堤ｽｮ縺�
	damage = 0; // 謳榊ｮｳ驥�
	energy = 0; // 迚ｹ谿企��
	shot_flag = false; // shot 繝輔Λ繧ｰ繧� false 縺ｫ縺吶ｋ
	beam_flag = false; // beam 繝輔Λ繧ｰ繧� false 縺ｫ縺吶ｋ
	dead_time = 0; // deat_time 繧抵ｼ舌↓險ｭ螳夲ｼ育せ貊�逕ｨ�ｼ�
	SET_sound("SHOT1.mp3", SOUND_SHOT1); // Shot 髻ｳ
	SET_sound("E ATTACK.mp3", SOUND_E_ATTACK); // 謳榊ｮｳ髻ｳ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

ThingType Player::HIT_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Player::GET_TYPE() {

	return TYPE_PLAYER;
}

void Player::move() {

	// 轤ｹ貊�繧ｨ繝輔ぉ繧ｯ繝医��繝槭う繝翫せ縺吶ｋ
	if (0 < dead_time) dead_time--;

	// 繝昴�ｼ繧ｺ�ｼ井ｼ第ｭ｢�ｼ峨ヵ繝ｩ繧ｰ false 縺ｮ蝣ｴ蜷�
	if (!pause_flag) {

		// chage_time = 0 縺昴＠縺ｦ beam 繝輔Λ繧ｰ false 縺ｮ蝣ｴ蜷�
		if (charge_time == 0 && !beam_flag) {

			// 螟我ｽ崎ｨｭ螳�
			if (CheckHitKey(KEY_INPUT_LEFT)) m_x -= m_s; // 竊仙ｷｦ
			if (CheckHitKey(KEY_INPUT_RIGHT)) m_x += m_s; // 竊貞承
			if (CheckHitKey(KEY_INPUT_UP)) m_y -= m_s; // 竊台ｸ�
			if (CheckHitKey(KEY_INPUT_DOWN)) m_y += m_s; // 竊謎ｸ�

			// 逕ｻ髱｢縺ｮ蠖薙◆繧雁愛螳�
			if (m_x < 0) m_x = 0; // 逕ｻ髱｢蟾ｦ
			if (Game::WIDTH < m_x + m_w) m_x = Game::WIDTH - m_w; // 逕ｻ髱｢蜿ｳ
			if (m_y < 0) m_y = 0; // 逕ｻ髱｢荳�
			if (Game::HEIGHT < m_y + m_h) m_y = Game::HEIGHT - m_h; // 逕ｻ髱｢荳�
		}

		// 騾壼ｸｸ蠑ｾ�ｼ茨ｼ｢�ｼ�
		if (CheckHitKey(KEY_INPUT_B) && shot_count % 8 == 0) {

			if (!shot_flag) { // shot 繝輔Λ繧ｰ false 縺ｮ蝣ｴ蜷�

<<<<<<< HEAD
				ThingPointa shot(new Shot); // Shot クラス作成　そのアドレスを Thing クラスのスマートポインタに渡す
				shot->SET_position(m_x + m_w - 10, m_y + 25); // Shot の座標を設定
				game->ADD_list(shot); // Thing リストに Shot アドレスを追加
				PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK); // Shot 音
=======
				ThingPointa shot(new Shot); // Shot 繧ｯ繝ｩ繧ｹ菴懈�舌��縺昴�ｮ繧｢繝峨Ξ繧ｹ繧� Thing 繧ｯ繝ｩ繧ｹ縺ｮ繧ｹ繝槭�ｼ繝医�昴う繝ｳ繧ｿ縺ｫ貂｡縺�
				shot->SET_position(m_x + m_w - 10, m_y + 25); // Shot 縺ｮ蛻晄悄菴咲ｽｮ繧定ｨｭ螳壹☆繧�
				game->ADD_list(shot); // Thing 繝ｪ繧ｹ繝医↓ Shot 繧｢繝峨Ξ繧ｹ繧定ｿｽ蜉�縺吶ｋ
				PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK); // Shot 髻ｳ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			}
		}

		// 雋ｫ騾壼ｼｾ�ｼ茨ｼｴ�ｼ�
		else if (CheckHitKey(KEY_INPUT_T) && shot_count % 10 == 0) {

			// 迚ｹ谿企�擾ｼ比ｻ･荳翫�ｮ蝣ｴ蜷医��逋ｺ蟆�蜿ｯ
			if (4 <= energy_now) {

				if (!shot_flag) {

					ThingPointa through_shot(new Through_Shot);
					through_shot->SET_position(m_x + m_w - 30, m_y + 25);
					game->ADD_list(through_shot);
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 蜈臥ｷ夲ｼ茨ｼ｣�ｼ�
		else if (CheckHitKey(KEY_INPUT_C)) {

			// 迚ｹ谿企�擾ｼ穂ｻ･荳翫�ｮ蝣ｴ蜷医��逋ｺ蟆�蜿ｯ
			if (5 <= energy_now) {

				if (!beam_flag) { // beam 繝輔Λ繧ｰ false 縺ｮ蝣ｴ蜷�

					ThingPointa beam(new Beam);
					beam->SET_position(m_x + m_w + 15, m_y - 10);
					game->ADD_list(beam);
					beam_flag = true; // 騾｣謇謎ｻ墓ｧ�
					PlaySoundMem(loaded_sound[SOUND_BEAM], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 貂ｦ蠑ｾ�ｼ茨ｼｶ�ｼ�
		else if (CheckHitKey(KEY_INPUT_V) && shot_count % 6 == 0) {

			// 迚ｹ谿企�擾ｼ謎ｻ･荳翫�ｮ蝣ｴ蜷医��逋ｺ蟆�蜿ｯ
			if (3 <= energy_now) {

				if (!shot_flag) {

					ThingPointa vortex_shot(new Vortex_Shot);
					vortex_shot->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(vortex_shot);
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 謨｣蟶�蠑ｾ�ｼ茨ｼｳ�ｼ�
		else if (CheckHitKey(KEY_INPUT_S) && shot_count % 10 == 0) {

			// 迚ｹ谿企�擾ｼ吩ｻ･荳翫�ｮ蝣ｴ蜷医��逋ｺ蟆�蜿ｯ
			if (9 <= energy_now) {

				if (!shot_flag) {

<<<<<<< HEAD
					for (int i = 0; i < 7; i++) { // ７発

						ThingPointa spray_shot1(new Spray_Shot);
						spray_shot1->SET_position(m_x + m_w - 10, m_y + 25);
						spray_shot1->SET_angle(3.14 * (3 - i) / 18); // 散布する角度（３０°・２０°・１０°・０°）を上下に設定
=======
					for (int i = 0; i < 7; i++) { // �ｼ怜�狗匱蟆�縺吶ｋ

						ThingPointa spray_shot1(new Spray_Shot);
						spray_shot1->SET_position(m_x + m_w - 10, m_y + 25);
						spray_shot1->SET_angle(3.14 * (3 - i) / 18); // 謨｣蟶�縺吶ｋ隗貞ｺｦ�ｼ茨ｼ難ｼ青ｰ繝ｻ�ｼ抵ｼ青ｰ繝ｻ�ｼ托ｼ青ｰ繝ｻ�ｼ青ｰ�ｼ峨ｒ荳贋ｸ九↓險ｭ螳壹☆繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
						game->ADD_list(spray_shot1);
					}

					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK); // Shot 髻ｳ
				}
			}
		}

		// 陞ｺ譌句ｼｾ�ｼ茨ｼｲ�ｼ�
		else if (CheckHitKey(KEY_INPUT_R) && shot_count % 4 == 0) {

			// 迚ｹ谿企�擾ｼ托ｼ舌�ｮ蝣ｴ蜷医��逋ｺ蟆�蜿ｯ
			if (10 <= energy_now) {

				if (!shot_flag) {

					// 荳�
					ThingPointa rasen_Shot_1(new Rasen_Shot);
					rasen_Shot_1->SET_position(m_x + m_w - 10, m_y + 25);
					rasen_Shot_1->SET_sign(1); // プラスに
					game->ADD_list(rasen_Shot_1);

					// 荳�
					ThingPointa rasen_Shot_2(new Rasen_Shot);
					rasen_Shot_2->SET_position(m_x + m_w - 10, m_y + 25);
					rasen_Shot_2->SET_sign(-1); // マイナスに
					game->ADD_list(rasen_Shot_2);
					PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 諡｡螟ｧ蠑ｾ�ｼ茨ｼｯ�ｼ�
		else if (CheckHitKey(KEY_INPUT_O)) {

			// 迚ｹ谿企�擾ｼ剃ｻ･荳翫�ｮ蝣ｴ蜷医��逋ｺ蟆�蜿ｯ
			if (2 <= energy_now) {

				// 逋ｺ蟆�貅門ｙ譎る俣
				if (charge_time <= 5) charge_time++;

				if (charge_time == 5) {

					ThingPointa charge_shot(new Charge_Shot);
					charge_shot->SET_position(m_x + m_w + 15, m_y + 35);
					game->ADD_list(charge_shot);
					PlaySoundMem(loaded_sound[SOUND_CHARGE], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 譎る剞蠑ｾ�ｼ茨ｼｺ�ｼ�
		else if (CheckHitKey(KEY_INPUT_Z)) {

			// 迚ｹ谿企�擾ｼ倅ｻ･荳翫�ｮ蝣ｴ蜷医��逋ｺ蟆�蜿ｯ
			if (8 <= energy_now) {

				if (!shot_flag) {

					ThingPointa period_shot1(new Period_Shot1);
					period_shot1->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(period_shot1);
					shot_flag = true; // 騾｣謇謎ｻ墓ｧ�
					PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 霑ｽ蟆ｾ蠑ｾ�ｼ茨ｼｨ�ｼ�
		else if (CheckHitKey(KEY_INPUT_H) && shot_count % 28 == 0) {

			// 迚ｹ谿企�擾ｼ嶺ｻ･荳翫�ｮ蝣ｴ蜷医��逋ｺ蟆�蜿ｯ
			if (7 <= energy_now) {

				// 谿九ｋ謨ｵ笳ｯ縺ｮ蝣ｴ蜷�
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
		// 放物線弾（Ｐ）
=======
		// 霑ｽ蟆ｾ繝ｻ謾ｾ迚ｩ邱壼ｼｾ�ｼ茨ｼｰ�ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		else if (CheckHitKey(KEY_INPUT_P) && shot_count % 28 == 0) {

			// 迚ｹ谿企�擾ｼ紋ｻ･荳翫�ｮ蝣ｴ蜷医��逋ｺ蟆�蜿ｯ
			if (6 <= energy_now) {

				// 谿九ｋ謨ｵ笳ｯ縺ｮ蝣ｴ蜷�
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
		// 全ての弾を使用可に
=======
		// 蜈ｨ縺ｦ縺ｮ蠑ｾ繧剃ｽｿ逕ｨ蜿ｯ縺ｫ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		else if (CheckHitKey(KEY_INPUT_Q)) energy_now = 10;

		else {

			shot_flag = false; // shot 繝輔Λ繧ｰ繧� false縺ｫ
			beam_flag = false; // beam 繝輔Λ繧ｰ 繧� false 縺ｫ
			charge_time = 0; // charge_time 繧抵ｼ舌↓
		}
	}

<<<<<<< HEAD
	// ライフ０の場合
	if (life_now <= 0) {

		scene = 3; // オーバー画面へ
		StopSoundMem(Play_m); // プレイ画面の音を停止
		StopSoundMem(Boss_m); // ボス画面の音を停止
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // オーバー画面の音を再生
=======
	// 繝ｩ繧､繝包ｼ舌↓縺ｪ縺｣縺溷�ｴ蜷�
	if (life_now <= 0) {

		scene = 3; // 繧ｪ繝ｼ繝舌�ｼ逕ｻ髱｢縺ｸ
		StopSoundMem(Play_m); // 繝励Ξ繧､荳ｭ縺ｮ髻ｳ繧貞●豁｢縺吶ｋ
		StopSoundMem(Boss_m); // 繝懊せ荳ｭ縺ｮ髻ｳ繧貞●豁｢縺吶ｋ
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // 繧ｪ繝ｼ繝舌�ｼ荳ｭ縺ｮ髻ｳ繧貞�咲函縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	}

	// 繝ｩ繧､繝輔�ｮ荳企剞險ｭ螳�
	if (10 <= life_now) life_now = 10;

	// 迚ｹ谿企�上�ｮ荳企剞險ｭ螳�
	if (10 <= energy_now) energy_now = 10;
}

void Player::heart_draw() {

	if (0 < life_now) {

<<<<<<< HEAD
		// 体力の値でハートの数を調整
=======
		// 莉翫�ｮ菴灘鴨縺ｫ繧医ｊ繝上�ｼ繝医�ｮ謨ｰ繧定ｪｿ謨ｴ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		for (int i = 0; i < life_now; i++) {

			DrawExtendGraph(5 + i * 45, 5, 55 + i * 45, 45, loaded_picture[TYPE_HEART], TRUE);
		}
	}
}

void Player::energy_draw() {

	if (0 < energy_now) {

<<<<<<< HEAD
		// 特殊量の値でハートの数を調整
=======
		// 莉翫�ｮ迚ｹ谿企�上↓繧医ｊ繝上�ｼ繝医�ｮ謨ｰ繧定ｪｿ謨ｴ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		for (int i = 0; i < energy_now; i++) {

			DrawExtendGraph(460 + i * 45, 5, 510 + i * 45, 45, loaded_picture[TYPE_ENERGY], TRUE);
		}
	}

<<<<<<< HEAD
	// 特殊量の値で（ハートの上に）文字を描画
	int color = GetColor(255, 255, 255); // 色を設定

	DrawFormatString(480, 15, color, "B");
	// 特殊量２〜１０以上の場合
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
	// 莉翫�ｮ迚ｹ谿企�上↓繧医ｊ�ｼ医ワ繝ｼ繝医�ｮ荳翫↓�ｼ画枚蟄励ｒ謠冗判縺吶ｋ
	int color = GetColor(255, 255, 255); // 濶ｲ
	DrawFormatString(480, 15, color, "B");

	// 迚ｹ谿企�擾ｼ抵ｽ橸ｼ托ｼ蝉ｻ･荳翫�ｮ蝣ｴ蜷�
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
	heart_draw(); // 体力を描画
	energy_draw(); // 特殊量を描画

	if (dead_time % 5 == 0) Thing::draw(); // ５で割り切れる場合　点滅で描画
=======
	heart_draw(); // 菴灘鴨繧呈緒逕ｻ縺吶ｋ
	energy_draw(); // 迚ｹ谿企�上ｒ謠冗判縺吶ｋ

	if (dead_time % 5 == 0) Thing::draw(); // �ｼ輔〒蜑ｲ繧雁��繧後ｋ蝣ｴ蜷医��轤ｹ貊�縺励※謠冗判縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Player::hit(int damage, int energy) {

	// 謨ｵ縺ｮ蝣ｴ蜷�
	if (dead_time <= 0 && 0 < damage) {

<<<<<<< HEAD
		dead_time = 50; // dead_time を５０に
		life_now -= damage; // 体力をマイナスする
		PlaySoundMem(loaded_sound[SOUND_E_ATTACK], DX_PLAYTYPE_BACK); // 損害音
	}

	// HEAL1 の場合
	if (damage < 0) life_now -= damage; // 体力の追加

	// HEAL2 の場合
	if (energy < 0) energy_now -= energy; // 特殊量の追加
}

//-------------------------------------------------------------------------------------

// Shot クラス（通常弾）の実装
Shot::Shot() {

	m_w = 12; // 横幅
	m_h = 12; // 縦幅
	m_s = 10; // 速度
	damage = 5; // 損害量
	SET_picture("SHOT1.png", TYPE_SHOT1); // 画像
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK); // 音
=======
		dead_time = 50; // 轤ｹ貊�繧ｫ繧ｦ繝ｳ繝医ｒ�ｼ包ｼ舌↓
		life_now -= damage; // 菴灘鴨繧偵�槭う繝翫せ縺吶ｋ
		PlaySoundMem(loaded_sound[SOUND_E_ATTACK], DX_PLAYTYPE_BACK); // 謳榊ｮｳ髻ｳ
	}

	// HEAL1 縺ｮ蝣ｴ蜷�
	if (damage < 0) life_now -= damage; // 菴灘鴨縺ｮ蠅怜刈

	// HEAL2 縺ｮ蝣ｴ蜷�
	if (energy < 0) energy_now -= energy; // 迚ｹ谿企�上�ｮ蠅怜刈
}

// Shot 繧ｯ繝ｩ繧ｹ�ｼ磯�壼ｸｸ蠑ｾ�ｼ峨�ｮ螳溯｣�
Shot::Shot() {

	m_w = 12; // 讓ｪ蟷�
	m_h = 12; // 邵ｦ蟷�
	m_s = 10; // 騾溷ｺｦ
	damage = 5; // 謳榊ｮｳ驥�
	SET_picture("SHOT1.png", TYPE_SHOT1); // 逕ｻ蜒�
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK); // 蜉ｹ譫憺浹
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
	if (!pause_flag) m_x += m_s; // 速度を１０に

	if (Game::WIDTH < m_x) remove(); // 画面左で削除
=======
	if (!pause_flag) m_x += m_s; // 騾溷ｺｦ繧抵ｼ托ｼ舌↓縺吶ｋ

	if (Game::WIDTH < m_x) remove(); // 逕ｻ髱｢蟾ｦ縺ｧ蜑企勁縺吶ｋ
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

// Through Shot クラス（貫通弾）の実装
=======
// Through Shot 繧ｯ繝ｩ繧ｹ�ｼ郁ｲｫ騾壼ｼｾ�ｼ峨�ｮ螳溯｣�
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
	if (!pause_flag) m_x += m_s; // 速度を２０に
=======
	if (!pause_flag) m_x += m_s; // 騾溷ｺｦ繧抵ｼ抵ｼ舌↓縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	if (Game::WIDTH < m_x + m_w) remove();
}

void Through_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Through_Shot::hit(int damage, int energy) {

<<<<<<< HEAD
	// 貫通する為 remove 関数は実装×
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Beam クラス（光線）の実装
Beam::Beam() {

	m_w = 0; // 伸長する為０に
=======
	// 雋ｫ騾壹☆繧狗ぜ remove()髢｢謨ｰ縺ｯ螳溯｣�縺励↑縺�
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// Beam 繧ｯ繝ｩ繧ｹ�ｼ亥�臥ｷ夲ｼ峨�ｮ螳溯｣�
Beam::Beam() {

	m_w = 0; // 蛻晄悄縺ｯ�ｼ舌↓
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
		hit_w = m_w; // 横幅を当たり判定に
=======
		hit_w = m_w; // 蠖薙◆繧雁愛螳壹↓鄂ｮ謠帙☆繧�
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

// Vortex Shot クラス（渦弾）の実装
=======
// Vortex Shot 繧ｯ繝ｩ繧ｹ�ｼ域ｸｦ蠑ｾ�ｼ峨�ｮ螳溯｣�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Vortex_Shot::Vortex_Shot() {

	m_w = 34;
	m_h = 15;
	damage = 10;
	angle = 0; // 隗貞ｺｦ繧抵ｼ舌↓
	rad = 0; // 蜊雁ｾ�繧抵ｼ舌↓
}

void Vortex_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;
}

void Vortex_Shot::move() {

	if (!pause_flag) {

		rad += 0.8; // 蜀�縺ｮ蜊雁ｾ�縺ｫ繝励Λ繧ｹ縺吶ｋ
		angle += 8 / rad; // 隗貞ｺｦ繧偵�励Λ繧ｹ縺吶ｋ�ｼ郁ｧ帝�溷ｺｦ繧定ｪｿ謨ｴ�ｼ�

		// 蝗槭ｋ險育ｮ�
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

// Spray Shot クラス（散布弾）の実装
=======
// Spray Shot 繧ｯ繝ｩ繧ｹ�ｼ域淵蟶�蠑ｾ�ｼ峨�ｮ螳溯｣�
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
	angle = a; // 引数を角度に
=======
	angle = a; // 隗貞ｺｦ縺ｫ鄂ｮ縺�
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

// Rasen Shot1・2 クラス（螺旋弾）の実装
=======
// Rasen Shot1繝ｻ2 繧ｯ繝ｩ繧ｹ�ｼ郁楴譌句ｼｾ�ｼ峨�ｮ螳溯｣�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Rasen_Shot::Rasen_Shot() {

	m_w = 12;
	m_h = 12;
	m_s = 8;
	damage = 1;
	angle = 0; // 隗貞ｺｦ繧抵ｼ舌↓
	sign = 0;
}

void Rasen_Shot::SET_position(int position_x, int position_y) {

	m_x = position_x;
	center_y = position_y;
}

void Rasen_Shot::SET_sign(int s) {

<<<<<<< HEAD
	sign = s; // 引数を符号に
=======
	sign = s; // 隨ｦ蜿ｷ縺ｫ鄂ｮ縺�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Rasen_Shot::move() {

	if (!pause_flag) {

		angle += 0.2;
		m_x += m_s;
		m_y = center_y - sign * 60 * sin(angle); // 繧ｵ繧､繝ｳ繧ｫ繝ｼ繝悶�ｮ蠢懃畑
	}

	if (Game::WIDTH < m_x) remove();
}

void Rasen_Shot::draw() {

<<<<<<< HEAD
	// 立体的に描画
=======
	// 螟ｧ縺阪＆繧帝囂譎ょ､画峩縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	DrawExtendGraph(m_x, m_y, m_x + m_w * (1.2 - sign * cos(angle)) / 2, m_y + m_h * (1.2 - sign * cos(angle)) / 2, loaded_picture[TYPE_SHOT1], TRUE);
}

void Rasen_Shot::hit(int damage, int energy) {

	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Charge Shot クラス（拡大弾）の実装
=======
// Charge Shot 繧ｯ繝ｩ繧ｹ�ｼ域僑螟ｧ蠑ｾ�ｼ峨�ｮ螳溯｣�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Charge_Shot::Charge_Shot() {

	m_w = 0;
	m_h = 0;
	m_s = 15;
	damage = 0;
	SET_picture("CHARGE SHOT.png", TYPE_CHARGE_SHOT);
	SET_sound("CHARGE.mp3", SOUND_CHARGE); // CHARGE 荳ｭ縺ｮ髻ｳ
	SET_sound("CHARGE SHOT.mp3", SOUND_CHARGE_SHOT); // 逋ｺ蟆�髻ｳ
	charge_flag = false; // charge 繝輔Λ繧ｰ繧� false 縺ｫ
}

void Charge_Shot::move() {

	if (!charge_flag) {

		// 「Ｏ」を押す場合
		if (CheckHitKey(KEY_INPUT_O)) {

<<<<<<< HEAD
			// 威力制限を５０に（損害量は０にしている為）
=======
			// 繧｢繧ｿ繝�繧ｯMAX繧抵ｼ包ｼ舌↓縺吶ｋ�ｼ亥�晄悄謳榊ｮｳ驥上�ｯ�ｼ舌↓縺励※縺�繧九◆繧��ｼ�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			if (damage < 50) {

				damage++;

				m_x += 1;
				m_y -= 2;
<<<<<<< HEAD
				m_w = 2 * damage; // 損害量に伴い拡大
				m_h = 4 * damage;

				// 当たり判定の誤差訂正
=======
				m_w = 2 * damage; // 謳榊ｮｳ驥上↓莨ｴ縺�螟ｧ縺阪￥縺ｪ繧�
				m_h = 4 * damage;

				// 蠖薙◆繧雁愛螳壹�ｮ隱､蟾ｮ險よｭ｣繧偵☆繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				hit_w = m_w + 20;
				hit_h = m_h;
			}

			// 謳榊ｮｳ驥擾ｼ包ｼ先悴貅�縺ｮ蝣ｴ蜷�
			else {

				charge_flag = true;
				StopSoundMem(loaded_sound[SOUND_CHARGE]);
				PlaySoundMem(loaded_sound[SOUND_CHARGE_SHOT], DX_PLAYTYPE_BACK);
			}
		}

<<<<<<< HEAD
=======
		// 縲鯉ｼｯ縲阪ｒ謚ｼ縺励※縺�縺ｪ縺�蝣ｴ蜷�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		else {

			charge_flag = true;
			StopSoundMem(loaded_sound[SOUND_CHARGE]);
			PlaySoundMem(loaded_sound[SOUND_CHARGE_SHOT], DX_PLAYTYPE_BACK);
		}
	}

<<<<<<< HEAD
	else if (!pause_flag) m_x += m_s; // 速度を１５に
=======
	else if (!pause_flag) m_x += m_s; // 騾溷ｺｦ繧抵ｼ托ｼ輔↓縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	if (Game::WIDTH < m_x) remove();
}

void Charge_Shot::draw() {

<<<<<<< HEAD
	// angle の値を２で割り切れる場合　描画
=======
	// angle 縺ｮ蛟､繧抵ｼ偵〒蜑ｲ繧� 菴吶ｊ�ｼ仙�ｴ蜷医��謠冗判縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if ((int)angle % 2 == 0) {

		DrawRotaGraph((2 * m_x + m_w) / 2, (2 * m_y + m_h) / 2, (double)m_w / 50, angle, loaded_picture[TYPE_CHARGE_SHOT], TRUE);
	}

<<<<<<< HEAD
	if (!pause_flag) angle += 30; // angle の値に３５プラスする
=======
	if (!pause_flag) angle += 30; // angle 縺ｮ蛟､縺ｫ�ｼ難ｼ戊ｶｳ縺礼ｶ壹¢繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Charge_Shot::hit(int damage, int energy) {

	remove();
	StopSoundMem(loaded_sound[SOUND_CHARGE]);
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot1 クラス（時限弾）の実装
=======
// Period Shot1 繧ｯ繝ｩ繧ｹ�ｼ域凾髯仙ｼｾ�ｼ峨�ｮ螳溯｣�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Period_Shot1::Period_Shot1() {

	m_w = 15;
	m_h = 15;
	m_s = 12;
	damage = 0;
<<<<<<< HEAD
	shot_time = 30; // 発射までの時間を３０に
	shot_count = 1; // ５回発射する為１に
=======
	shot_time = 30; // 逋ｺ蟆�縺吶ｋ縺ｾ縺ｧ縺ｮ譎る俣繧抵ｼ難ｼ舌↓
	shot_count = 1; // �ｼ募屓逋ｺ蟆�縺吶ｋ縺溘ａ縺ｫ 蛻晄悄縺ｯ�ｼ代↓
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	SET_picture("SHOT3.png", TYPE_SHOT3);
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK);
}

ThingType Period_Shot1::GET_TYPE() {

	return TYPE_SHOT3;
}

ThingType Period_Shot1::HIT_TYPE() {

<<<<<<< HEAD
	return TYPE_NONE; // 本体に当たり判定×
=======
	return TYPE_NONE; // 譛ｬ菴薙↓縺ｯ蠖薙◆繧雁愛螳堙�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Period_Shot1::move() {

	if (!pause_flag) {

<<<<<<< HEAD
		if (0 <= shot_time) m_x += m_s; // 発射まで右方向へ
=======
		if (0 <= shot_time) m_x += m_s; // 逋ｺ蟆�縺吶ｋ縺ｾ縺ｧ蜿ｳ譁ｹ蜷代∈
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

		if (shot_time < 0) {

			// �ｼ募屓逋ｺ蟆�
			if (shot_time % 10 == 0 && shot_count <= 5) {

<<<<<<< HEAD
				// 当たり判定◯弾を発射
				// 下方向
=======
				// 蠖薙◆繧雁愛螳壺留縲�蠑ｾ繧堤匱蟆�縺吶ｋ
				// 荳区婿蜷�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				ThingPointa period_shot2(new Period_Shot2());
				game->ADD_list(period_shot2);
				period_shot2->SET_sign(1);
				period_shot2->SET_position(m_x + 1, m_y - 10);

				// 蜿ｳ譁ｹ蜷�
				ThingPointa period_shot3(new Period_Shot3());
				game->ADD_list(period_shot3);
				period_shot3->SET_sign(1);
				period_shot3->SET_position(m_x - 5, m_y + 2);

				// 荳頑婿蜷�
				ThingPointa period_shot4(new Period_Shot2());
				game->ADD_list(period_shot4);
				period_shot4->SET_sign(-1);
				period_shot4->SET_position(m_x + 1, m_y - 10);

				// 蟾ｦ譁ｹ蜷�
				ThingPointa period_shot5(new Period_Shot3());
				game->ADD_list(period_shot5);
				period_shot5->SET_position(m_x - 12, m_y + 2);
				period_shot5->SET_sign(-1);
				PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);

				shot_count++;
			}

<<<<<<< HEAD
			if (5 < shot_count) remove(); // ５発で削除
=======
			if (5 < shot_count) remove(); // �ｼ募屓逶ｮ縺ｧ蜑企勁縺吶ｋ
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
void Period_Shot1::hit(int damage, int energy) {} // 蠖薙◆繧雁愛螳堙�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

// Period Shot2�ｼ井ｸ贋ｸ具ｼ峨け繝ｩ繧ｹ縺ｮ螳溯｣�
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

// Period Shot3（左右）クラスの実装
=======
// Period Shot3�ｼ亥ｷｦ蜿ｳ�ｼ峨け繝ｩ繧ｹ縺ｮ螳溯｣�
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

// Homing Shot クラス（追尾弾）の実装
=======
// Homing Shot 繧ｯ繝ｩ繧ｹ�ｼ郁ｿｽ蟆ｾ蠑ｾ�ｼ峨�ｮ螳溯｣�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Homing_Shot::Homing_Shot() {

	m_w = 12;
	m_h = 12;
	m_s = 10;
	damage = 20;
<<<<<<< HEAD
	shot_s = 10; // shot_s を１０に
=======
	shot_s = 10; // shot_s 繧�10縺ｫ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Homing_Shot::move() {

	if (!pause_flag) {

<<<<<<< HEAD
		// 残る敵◯の場合
		if (0 < enemy_num) {

			// 追尾の計算
			// sqrt() は絶対値
			// pow() はべき乗
			// 一定の速度で追尾
=======
		// 谿九ｋ謨ｵ笳ｯ
		if (0 < enemy_num) {

			// 霑ｽ蟆ｾ縺吶ｋ險育ｮ�
			// sqrt() 縺ｯ邨ｶ蟇ｾ蛟､縺ｮ險育ｮ�
			// pow() 縺ｯ縺ｹ縺堺ｹ励�ｮ險育ｮ�
			// 荳�螳壹�ｮ騾溷ｺｦ縺ｧ霑ｽ蟆ｾ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			m_x += ((enemy_x - m_x) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
			m_y += ((enemy_y - m_y) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
		}

<<<<<<< HEAD
		else m_x += m_s; // 残る敵×の場合　右方向へ
=======
		else m_x += m_s; // 谿九ｋ謨ｵﾃ� 蜿ｳ譁ｹ蜷代∈
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

// Parabola Shot クラス（放物線弾）の実装
=======
// Parabola Shot 繧ｯ繝ｩ繧ｹ�ｼ郁ｿｽ蟆ｾ繝ｻ謾ｾ迚ｩ邱壼ｼｾ�ｼ峨�ｮ螳溯｣�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Parabola_Shot::Parabola_Shot() {

	m_w = 12;
	m_h = 12;
	damage = 50;
<<<<<<< HEAD
	m_s = 0; // shot_s を０に
=======
	m_s = 0; // shot_s 繧� 0縺ｫ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Parabola_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;

<<<<<<< HEAD
	// 行列計算で三点の座標を計算
=======
	// 陦悟�苓ｨ育ｮ励〒荳臥せ縺ｮ蠎ｧ讓吶ｒ豎ゅａ繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	float frame = (enemy_x - center_x) / (8 + enemy_s);

	// 蠑ｾ繝ｻ謨ｵ繧貞�･繧後ｋ�ｼ鍋せ縺ｮ蠎ｧ讓�
	float x_1 = center_x;
	float x_2 = enemy_x - enemy_s * frame;
	float x_3 = center_x + 1;

	float y_1 = center_y;
	float y_2 = enemy_y;
<<<<<<< HEAD
	float y_3 = center_y - tan(3.14 / 3); // 角度６０°に
=======
	float y_3 = center_y - tan(3.14 / 3); // 隗貞ｺｦ�ｼ厄ｼ青ｰ縺ｧ荳頑��縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	float det_A = -(x_1 - x_2) * (x_2 - x_3) * (x_3 - x_1);
	float det_a = y_1 * x_2 + y_2 * x_3 + y_3 * x_1 - x_2 * y_3 - x_3 * y_1 - x_1 * y_2;
	float det_b = pow(x_1, 2) * y_2 + pow(x_2, 2) * y_3 + pow(x_3, 2) * y_1 - y_1 * pow(x_2, 2) - y_2 * pow(x_3, 2) - y_3 * pow(x_1, 2);
	float det_c = pow(x_1, 2) * x_2 * y_3 + pow(x_2, 2) * x_3 * y_1 + pow(x_3, 2) * x_1 * y_2 - y_1 * x_2 * pow(x_3, 2) - y_2 * x_3 * pow(x_1, 2) - y_3 * x_1 * pow(x_2, 2);

	// 繧ｯ繝ｩ繝｡繝ｫ縺ｫ繧医ｋ險育ｮ�
	a = det_a / det_A;
	b = det_b / det_A;
	c = det_c / det_A;
}

void Parabola_Shot::move() {

	if (!pause_flag) {

		m_s += 8;
		m_x = center_x + m_s;
<<<<<<< HEAD
		m_y = a * pow(m_x, 2) + b * m_x + c; // 放物線で描画
=======
		m_y = a * pow(m_x, 2) + b * m_x + c; // 謾ｾ迚ｩ邱壹↓謠冗判縺吶ｋ
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

// ENEMY1〜6クラスの実装
=======
// ENEMY1�ｽ�6繧ｯ繝ｩ繧ｹ縺ｮ螳溯｣�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Enemy1::Enemy1() {

	m_w = 80;
	m_h = 50;

<<<<<<< HEAD
	// STAGE の値で速度を設定
	if (stage <= 6) m_s = 8;
	if (7 <= stage) m_s = 10;

	life_max = 10; // 体力１０に
	life_now = life_max; // 体力の値を設定体力に
	damage = 1; // 損害量１に
	energy = 0; // 特殊量０に
	count = 0; // 体力 != 0 で count を０に
	count_flag = false; // 体力 != 0 で count フラグは false に
	SET_picture("ENEMY1.png", TYPE_ENEMY1);
	SET_picture("BURN.png", TYPE_BURN);
	SET_sound("BREAK.mp3", SOUND_BREAK);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h)); // 座標
=======
	// STAGE縺ｫ繧医ｊ騾溷ｺｦ繧定ｨｭ螳�
	if (stage <= 6) m_s = 8;
	if (7 <= stage) m_s = 10;

	life_max = 10; // 菴灘鴨�ｼ托ｼ�
	life_now = life_max; // 險ｭ螳壻ｽ灘鴨繧堤樟蝨ｨ縺ｮ菴灘鴨縺ｫ蜈･繧後ｋ
	damage = 1; // 謳榊ｮｳ驥擾ｼ�
	energy = 0; // 迚ｹ谿企�擾ｼ�
	count = 0; // 菴灘鴨 != 0 縺ｧ count 繧抵ｼ舌↓
	count_flag = false; // 菴灘鴨 != 0 縺ｧ count 繝輔Λ繧ｰ縺ｯ false 縺ｫ
	SET_picture("ENEMY1.png", TYPE_ENEMY1);
	SET_picture("BURN.png", TYPE_BURN);
	SET_sound("BREAK.mp3", SOUND_BREAK);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h)); // 蛻晄悄菴咲ｽｮ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

ThingType Enemy1::GET_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Enemy1::HIT_TYPE() {

	return TYPE_PLAYER;
}

void Enemy1::move() {

	if (!pause_flag) m_x -= m_s; // 騾溷ｺｦ�ｼ� or �ｼ托ｼ�

	// 辷�遐ｴ蠕� count 縺ｯ�ｼ托ｼ薙�ｮ蛟､繧貞ｾ励ｋ
	if (0 < count) {

		count--;
		count_flag = true;
	}

	// 逕ｻ髱｢蟾ｦ縺ｫ蜈･繧句�ｴ蜷�
	if (m_x + m_w < 0) {

		remove(); // 蜑企勁縺吶ｋ

		if (score < 20000 && 0 < score) game->ADD_score(-100); // 繧ｹ繧ｳ繧｢繧偵�槭う繝翫せ縺吶ｋ

		if (0 < enemy_num) enemy_num -= 1; // enemy_num 繧偵�槭う繝翫せ縺吶ｋ
	}

<<<<<<< HEAD
	// Homing・Parabola Shotクラス（追尾弾・放物線弾）を実装する為　値をグローバル変数に
=======
	// Homing繝ｻParabola Shot繧ｯ繝ｩ繧ｹ�ｼ郁ｿｽ蟆ｾ蠑ｾ�ｼ峨ｒ螳溯｣�縺吶ｋ轤ｺ縲�繧ｰ繝ｭ繝ｼ繝舌Ν螟画焚縺ｫ蛟､繧貞�･繧後ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy1::draw() {

<<<<<<< HEAD
	life_draw(); // 体力を描画
=======
	life_draw(); // 菴灘鴨繧呈緒逕ｻ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY1], TRUE);
	}

	// 辷�遐ｴ蠕� count 縺ｫ縺ｯ�ｼ托ｼ薙�ｻcount_flag 縺ｯ move() 縺ｧ true 縺ｫ
	if (count_flag && 0 <= count) {

<<<<<<< HEAD
		// 爆破エフェクトを描画
		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		// count <= 0 の場合　削除
		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200); // スコアを追加
=======
		// 辷�遐ｴ繧ｨ繝輔ぉ繧ｯ繝医ｒ謠冗判縺吶ｋ
		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		// count <= 0 縺ｮ蝣ｴ蜷医��蜑企勁縺吶ｋ
		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200); // 繧ｹ繧ｳ繧｢縺ｫ蠕礼せ繧定ｿｽ蜉�縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

			if (0 < enemy_num) enemy_num -= 1; // enemy_num 繧偵�槭う繝翫せ縺吶ｋ
		}
	}
}

void Enemy1::hit(int damage, int energy) {

	life_now -= damage; // 菴灘鴨繧偵�槭う繝翫せ縺吶ｋ

<<<<<<< HEAD
	// 体力０の場合　爆破エフェクトを実装
	if (life_now <= 0 && count == 0) {

		count = 13; // count を１３に
=======
	// 菴灘鴨�ｼ舌�ｮ蝣ｴ蜷医��辷�遐ｴ繧ｨ繝輔ぉ繧ｯ繝医ｒ螳溯｣�縺吶ｋ
	if (life_now <= 0 && count == 0) {

		count = 13; // count 縺ｫ�ｼ托ｼ薙�ｮ蛟､繧貞�･繧後ｋ
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
	up_down = 6; // 荳贋ｸ区婿蜷代�ｮ騾溷ｺｦ繧抵ｼ悶↓
	count = 0;
	count_flag = false;
	SET_picture("ENEMY3.png", TYPE_ENEMY3);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy3::move() {

	if (!pause_flag) {

		m_x -= m_s;
		m_y += up_down; // 荳贋ｸ区婿蜷代�ｮ騾溷ｺｦ
	}

	// 逕ｻ髱｢縺ｮ蠖薙◆繧雁愛螳�
	if (m_y < 0) up_down = -up_down; // 荳�
	if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // 荳�

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
	up_down = 6; // 荳贋ｸ区婿蜷代�ｮ騾溷ｺｦ繧抵ｼ悶↓
	count = 0;
	count_flag = false;
	SET_picture("ENEMY5.png", TYPE_ENEMY5);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy5::move() {

	if (!pause_flag) {

		// 荳�螳壹�ｮ蠎ｧ讓吶∪縺ｧ蟾ｦ蜷代″縺ｸ
		if (1000 < m_x) m_x -= m_s;

		// 荳�螳壹�ｮ蠎ｧ讓吶〒荳贋ｸ句髄縺阪∈
		if (m_x <= 1000) {

			m_y -= up_down;

			// 逕ｻ髱｢縺ｮ蠖薙◆繧雁愛螳�
			if (m_y < 0) up_down = -up_down; // 荳�
			if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // 荳�

			if (GetRand(60) == 0) {

<<<<<<< HEAD
				ThingPointa enemy_shot2(new Enemy_Shot2); // Enemy Shot2 クラス作成　そのアドレスを Thing クラスのスマートポインタに渡す
				enemy_shot2->SET_position(m_x - 10, m_y + 25); // 座標
				game->ADD_list(enemy_shot2); // Thing リストに Enemy Shot2 アドレスを追加
=======
				ThingPointa enemy_shot2(new Enemy_Shot2); // Enemy Shot2 繧ｯ繝ｩ繧ｹ菴懈�舌��縺昴�ｮ繧｢繝峨Ξ繧ｹ繧� Thing 繧ｯ繝ｩ繧ｹ縺ｮ繧ｹ繝槭�ｼ繝医�昴う繝ｳ繧ｿ縺ｫ貂｡縺�
				enemy_shot2->SET_position(m_x - 10, m_y + 25); // 蛻晄悄菴咲ｽｮ
				game->ADD_list(enemy_shot2); // Thing 繝ｪ繧ｹ繝医↓ Enemy Shot2 繧｢繝峨Ξ繧ｹ繧定ｿｽ蜉�縺吶ｋ
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
		// 画面の当たり判定
		if (m_y < 0) up_down = -up_down; // 上
		if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // 下
		if (m_x < 0) m_s = -2; // 左
		if (Game::WIDTH + 200 < m_x + m_w) remove(); // 画面右で削除
=======
		// 逕ｻ髱｢縺ｮ蠖薙◆繧雁愛螳�
		if (m_y < 0) up_down = -up_down; // 荳�
		if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // 荳�
		if (m_x < 0) m_s = -2; // 蟾ｦ
		if (Game::WIDTH + 200 < m_x + m_w) remove(); // 逕ｻ髱｢蜿ｳ縺ｧ蜑企勁縺吶ｋ
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

// ENEMY BOSS1・2クラスの実装
=======
// ENEMY BOSS1繝ｻ2繧ｯ繝ｩ繧ｹ縺ｮ螳溯｣�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Enemy_Boss1::Enemy_Boss1() {

	// Enemy Boss1 繝ｩ繧､繝戊ｨｭ螳�
	if (stage == 1 || stage == 4 || stage == 7) life_max = 3000; // STAGE�ｼ代�ｻ�ｼ斐�ｻ�ｼ�
	if (stage == 2 || stage == 5 || stage == 8) life_max = 3500; // STAGE�ｼ偵�ｻ�ｼ輔�ｻ�ｼ�
	if (stage == 3 || stage == 6 || stage == 9) life_max = 4000; // STAGE�ｼ薙�ｻ�ｼ悶�ｻ�ｼ�

	m_w = 350;
	m_h = 390;
	life_now = life_max;
	damage = 1;
	energy = 0;
<<<<<<< HEAD
	up_down = 3; // 上下向き速度を３に
	add_speed = 0; // 体力半分になるまで加速は０に
	count = 0;
	count_flag = false;

	// STAGEの値で画像を設定
=======
	up_down = 3; // 荳贋ｸ句髄縺埼�溷ｺｦ
	add_speed = 0; // 菴灘鴨縺悟濠蛻�縺ｫ縺ｪ繧九∪縺ｧ蜉�騾溘�ｯ�ｼ舌↓
	count = 0;
	count_flag = false;

	// STAGE縺ｫ繧医ｊ謠冗判縺吶ｋ逕ｻ蜒上ｒ險ｭ螳�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (stage <= 3) SET_picture("ENEMY BOSS1.png", TYPE_ENEMY_BOSS1);
	if (4 <= stage && stage <= 6) SET_picture("ENEMY BOSS2.png", TYPE_ENEMY_BOSS2);
	if (7 <= stage && stage <= 9) SET_picture("ENEMY BOSS3.png", TYPE_ENEMY_BOSS3);

	SET_hitarea(150, 50, 340, 340); // 蠖薙◆繧雁愛螳壹�ｮ險ｭ螳�
	Warn_p = LoadGraph("WARNING.png"); // WARNING!!
	SET_position(Game::WIDTH, 140);
}

void Enemy_Boss1::move() {

<<<<<<< HEAD
	// 体力半分以下の場合　速度を上昇
=======
	// 菴灘鴨縺悟濠蛻�莉･荳九�ｮ蝣ｴ蜷医��騾溷ｺｦ繧剃ｸ翫£繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (life_now < life_max / 2) add_speed = 3;

	if (!pause_flag) {

<<<<<<< HEAD
		// 一定の座標まで左方向
=======
		// 荳�螳壹�ｮ蠎ｧ讓吶∪縺ｧ蟾ｦ蜷代″
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
		// 一定の座標の場合　上下方向
=======
		// 荳�螳壹�ｮ蠎ｧ讓吶�ｮ蝣ｴ蜷医��荳贋ｸ句髄縺�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		if (m_x <= 790) {

			m_y += up_down;

			// 逕ｻ髱｢縺ｮ蠖薙◆繧雁愛螳�
			if (m_y + hit_y + 100 < 0) up_down = 4 + add_speed;
			if (Game::HEIGHT + 100 < m_y + hit_h) up_down = -(4 + add_speed);

			if (GetRand(30) == 0) {

				// 真ん中
				ThingPointa enemy_shot1_1(new Enemy_Shot1);
				enemy_shot1_1->SET_position(m_x + m_w - 250, m_y + 190);
				game->ADD_list(enemy_shot1_1);

				// 下
				ThingPointa enemy_shot1_2(new Enemy_Shot1);
				enemy_shot1_2->SET_position(m_x + m_w - 210, m_y + 220);
				game->ADD_list(enemy_shot1_2);

				// 上
				ThingPointa enemy_shot1_3(new Enemy_Shot1);
				enemy_shot1_3->SET_position(m_x + m_w - 210, m_y + 160);
				game->ADD_list(enemy_shot1_3);
				PlaySoundMem(loaded_sound[SOUND_ENEMY_SHOT], DX_PLAYTYPE_BACK);
			}
		}
	}
}

void Enemy_Boss1::life_draw() {

	int life_x = Game::WIDTH - 245; // 蠎ｧ讓吶�ｮ隱ｿ謨ｴ

	if (0 < life_now) {

		DrawExtendGraph(life_x, 5, life_x + 245, 30, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(life_x, 5, life_x + (245 * life_now) / life_max, 30, loaded_picture[TYPE_LIFE], TRUE);
	}
}

void Enemy_Boss1::draw() {

	life_draw(); // 菴灘鴨縺ｮ謠冗判

	if (0 < life_now) {

		SetFontSize(20); // 譁�蟄励し繧､繧ｺ縺ｮ險ｭ螳�
		DrawFormatString(Game::WIDTH - 250, 5, GetColor(255, 255, 255), "%d", life_now); // 菴灘鴨謨ｰ蛟､縺ｮ謠冗判
	}

	if (!count_flag) {

<<<<<<< HEAD
		// STAGEの値で画像を設定
=======
		// STAGE縺ｫ繧医ｊ逕ｻ蜒上ｒ險ｭ螳�
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
			scene = 4; // 繧ｯ繝ｪ繧｢逕ｻ髱｢縺ｸ
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
	life_max = 5000; // Enemy Boss2 繝ｩ繧､繝戊ｨｭ螳�
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

				// 蟾ｦ
				ThingPointa enemy_shot1_1(new Enemy_Shot1);
				enemy_shot1_1->SET_position(m_x + m_w - 250, m_y + 190);
				game->ADD_list(enemy_shot1_1);

				// 逵溘ｓ荳ｭ荳�
				ThingPointa enemy_shot1_2(new Enemy_Shot1);
				enemy_shot1_2->SET_position(m_x + m_w - 210, m_y + 220);
				game->ADD_list(enemy_shot1_2);

				// 逵溘ｓ荳ｭ荳�
				ThingPointa enemy_shot1_3(new Enemy_Shot1);
				enemy_shot1_3->SET_position(m_x + m_w - 210, m_y + 160);
				game->ADD_list(enemy_shot1_3);

				// 蜿ｳ荳�
				ThingPointa enemy_shot1_4(new Enemy_Shot1);
				enemy_shot1_4->SET_position(m_x + m_w - 170, m_y + 250);
				game->ADD_list(enemy_shot1_4);

				// 蜿ｳ荳�
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

// Enemy Shot1 クラス（ボス）の実装
=======
// Enemy Shot1 繧ｯ繝ｩ繧ｹ�ｼ医�懊せ�ｼ峨�ｮ螳溯｣�
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

// Enemy Shot2 クラス（ENEMY5・6）の実装
=======
// Enemy Shot2 繧ｯ繝ｩ繧ｹ�ｼ�ENEMY5繝ｻ6�ｼ峨�ｮ螳溯｣�
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

// HEAL1（体力回復）クラスの実装
=======
// HEAL1�ｼ井ｽ灘鴨蝗槫ｾｩ�ｼ峨け繝ｩ繧ｹ縺ｮ螳溯｣�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Heal1::Heal1() {

	m_w = 25;
	m_h = 21;
	m_s = 6;
<<<<<<< HEAD
	damage = -1; // 値はマイナスにして回復に
=======
	damage = -1; // 蛟､縺ｯ繝槭う繝翫せ縺ｫ縺励※蝗槫ｾｩ縺ｫ縺吶ｋ
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

// HEAL2（特殊量回復）クラスの実装
=======
// HEAL2�ｼ育音谿企�丞屓蠕ｩ�ｼ峨け繝ｩ繧ｹ縺ｮ螳溯｣�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Heal2::Heal2() {

	m_w = 25;
	m_h = 21;
	m_s = 10;
	damage = 0;
<<<<<<< HEAD
	energy = -1; // 値をマイナスにして特殊量回復に
=======
	energy = -1; // 蛟､繧偵�槭う繝翫せ縺ｫ縺励※迚ｹ谿企�丞屓蠕ｩ縺ｫ縺吶ｋ
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

// Game クラスの実装
void Game::ADD_list(ThingPointa & add) {

	thing_list.push_back(add); // Thing リストの back に Thing クラスの add を追加
=======
// Game 繧ｯ繝ｩ繧ｹ縺ｮ螳溯｣�
void Game::ADD_list(ThingPointa & add) {

	thing_list.push_back(add); // Thing 繝ｪ繧ｹ繝医�ｮ荳九↓ Thing 繧ｯ繝ｩ繧ｹ縺ｮ add 繧定ｿｽ蜉�縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Game::ADD_score(int sc) {

	score += sc; // 繧ｹ繧ｳ繧｢繧定ｿｽ蜉�
}

bool Game::PUSH_space() {

	if (CheckHitKey(KEY_INPUT_SPACE)) {

		// push_flag縲�false 縺ｮ蝣ｴ蜷�
		if (!push_flag) {

			push_flag = true;
			return true;
		}
	}

	// 荳願ｨ倅ｻ･螟� false 縺ｫ
	else push_flag = false;

	return false; // false 縺ｧ霑斐☆
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

	// text 縺ｮ蛟､繧定ｪｭ霎ｼ縺吶ｋ�ｼ医ワ繧､繧ｹ繧ｳ繧｢�ｼ�
	FILE* file;
	fopen_s(&file, "HIGH SCORE.txt", "r");
	fscanf_s(file, "%d", &high_score);
	fclose(file);
}

void Game::SAVE_highscore() {

	// text 縺ｮ蛟､繧定ｨ倬鹸縺吶ｋ�ｼ医せ繧ｳ繧｢�ｼ�
	FILE* file;
	fopen_s(&file, "HIGH SCORE.txt", "w");
	fprintf(file, "%d", now_score);
	fclose(file);
}

//-------------------------------------------------------------------------------------

void Game::GAME_SET() {

<<<<<<< HEAD
	game = this; // 自インスタンスのアドレスを保持（静的）
	scene = 0; // タイトル画面へ
	stage = 0; // STAGEを０に
	score = 0; // スコアを０に
	p_x = 0; // バックの x 座標を左上に設定
	p_w = WIDTH; // バックの横幅を WIDTH に
	limit_time = 600; // 制限時間を６００に

	LOAD_highscore(); // スコアの読込

	ChangeWindowMode(TRUE); // ウィンドウを開く
	SetGraphMode(WIDTH, HEIGHT, 32); // ウィンドウの横幅・縦幅・カラー設定
	DxLib_Init(); // DXライブラリを初期化
	SetDrawScreen(DX_SCREEN_BACK); // ウラに画像を描画
=======
	game = this; // 閾ｪ繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ縺ｮ繧｢繝峨Ξ繧ｹ繧剃ｿ晄戟縺吶ｋ�ｼ磯撕逧��ｼ�
	scene = 0; // 繧ｿ繧､繝医Ν逕ｻ髱｢縺ｸ
	stage = 0; // STAGE繧抵ｼ舌↓縺吶ｋ
	score = 0; // 繧ｹ繧ｳ繧｢繧抵ｼ舌↓
	p_x = 0; // 繝舌ャ繧ｯ縺ｮ x 蠎ｧ讓吶ｒ蟾ｦ荳翫↓險ｭ螳�
	p_w = WIDTH; // 繝舌ャ繧ｯ縺ｮ讓ｪ蟷�繧� WIDTH 縺ｫ鄂ｮ謠�
	limit_time = 600; // 蛻ｶ髯先凾髢薙ｒ�ｼ厄ｼ撰ｼ舌↓

	LOAD_highscore(); // 繧ｹ繧ｳ繧｢縺ｮ隱ｭ霎ｼ
	start_time = GetNowCount(); // �ｼ壮 蜊倅ｽ阪↓縺吶ｋ

	ChangeWindowMode(TRUE); // 繧ｦ繧｣繝ｳ繝峨え繧帝幕縺�
	SetGraphMode(WIDTH, HEIGHT, 32); // 繧ｦ繧｣繝ｳ繝峨え縺ｮ讓ｪ蟷�繝ｻ邵ｦ蟷�繝ｻ繧ｫ繝ｩ繝ｼ縺ｮ險ｭ螳�
	DxLib_Init(); // DX繝ｩ繧､繝悶Λ繝ｪ繧貞�晄悄蛹悶☆繧�
	SetDrawScreen(DX_SCREEN_BACK); // 繧ｦ繝ｩ縺ｫ逕ｻ蜒上ｒ謠冗判
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	// 逕ｻ蜒上�ｮ隱ｭ霎ｼ
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

	// 髻ｳ讌ｽ繝輔ぃ繧､繝ｫ縺ｮ隱ｭ霎ｼ
	Title_m = LoadSoundMem("TITLE.mp3");
	Play_m = LoadSoundMem("GAME PLAY.mp3");
	Over_m = LoadSoundMem("GAME OVER.mp3");
	Clear_m = LoadSoundMem("GAME CLEAR.mp3");
	Pause_m = LoadSoundMem("PAUSE.mp3");
	Boss_m = LoadSoundMem("BOSS GAME.mp3");

<<<<<<< HEAD
	PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // タイトル画面の音を再生
=======
	PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // 繧ｿ繧､繝医Ν髻ｳ蜀咲函
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

//-------------------------------------------------------------------------------------

void Game::GAME_ALL() {

<<<<<<< HEAD
	// イベント処理の実装関数
=======
	// 繧､繝吶Φ繝亥�ｦ逅�繧貞ｮ溯｣�縺吶ｋ髢｢謨ｰ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	while (!ProcessMessage()) {

		ClearDrawScreen(); // 逕ｻ蜒上ｒ蜑企勁�ｼ医え繝ｩ縺ｮ蛻晄悄蛹厄ｼ�

		if (scene == 0) GAME_TITLE();

		if (scene == 1) GAME_SELECT();

		if (scene == 2) GAME_PLAY();

		if (scene == 3) GAME_OVER();

		if (scene == 4) GAME_CLEAR();

		ScreenFlip(); // 逕ｻ蜒上ｒ繧ｪ繝｢繝�縺ｫ蜃ｺ縺�
	}
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 0 の場合　タイトル画面
void Game::GAME_TITLE() {

	SetBackgroundColor(0, 0, 0); // バックの色を黒色に設定
	DrawExtendGraph(10, 200, WIDTH - 10, HEIGHT - 200, Title_p, TRUE); // タイトル
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE
=======
// scene == 0 縺ｮ譎ゅ��繧ｿ繧､繝医Ν逕ｻ髱｢縺ｫ縺吶ｋ
void Game::GAME_TITLE() {

	SetBackgroundColor(0, 0, 0); // 繝舌ャ繧ｯ縺ｮ濶ｲ繧帝ｻ定牡縺ｫ險ｭ螳�
	DrawExtendGraph(10, 200, WIDTH - 10, HEIGHT - 200, Title_p, TRUE); // 繧ｿ繧､繝医Ν縺ｮ謠冗判
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE 縺ｮ謠冗判
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	// 譁�蟄励�ｮ謠冗判
	SetFontSize(20); // 繧ｵ繧､繧ｺ縺ｮ險ｭ螳�
	DrawFormatString(10, 10, GetColor(255, 255, 255), "B E S T  S C O R E : %d", high_score);

<<<<<<< HEAD
	thing_list.clear(); // Thing リストを初期化
	score = 0; // スコアを０に
	add_s = 0; // バックを高速で回す
	limit_time = 600; // 制限時間を６００に

	// SPACE を押す場合　選択画面へ
	if (PUSH_space()) scene = 1;

	play_flag = false; // プレイフラグを false に
	boss_flag = false; // ボスフラグを false に
	space_flag = false; // スペースフラグを false に
}

//-------------------------------------------------------------------------------------

// scene == 1 の場合　選択画面
=======
	thing_list.clear(); // Thing 繝ｪ繧ｹ繝医ｒ蛻晄悄蛹悶☆繧�
	score = 0; // 繧ｹ繧ｳ繧｢繧抵ｼ舌↓
	add_s = 0; // 繝舌ャ繧ｯ繧帝ｫ倬�溘〒蝗槭☆

	// SPACE KEY 繧呈款縺励◆蝣ｴ蜷医��SELECT逕ｻ髱｢縺ｸ
	if (PUSH_space()) scene = 1;

	game_flag = false; // game_flag 繧� false 縺ｫ
	boss_flag = false; // 繝懊せ繝輔Λ繧ｰ繧� false 縺ｫ
	space_flag = false; // PUSH SPACE 繝輔Λ繧ｰ繧� false 縺ｫ
}

// scene == 1 縺ｮ譎ゅ��驕ｸ謚樒判髱｢
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
void Game::GAME_SELECT() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(70, 200, WIDTH - 70, HEIGHT - 200, Select_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Number_p, TRUE); // PUSH SPACE 縺ｮ謠冗判

	// 莉･荳銀�� STAGE�ｼ托ｽ橸ｼ托ｼ舌�ｮ蛻�蟯�
	// stage == 1 縺ｫ險ｭ螳�
	if (CheckHitKey(KEY_INPUT_1)) {

		scene = 2; // 繝励Ξ繧､逕ｻ髱｢
		stage = 1; // STAGE�ｼ�

		// PLAYER 逕滓��
		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 2 に設定
=======
	// stage == 2 縺ｫ險ｭ螳�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_2)) {

		scene = 2;
		stage = 2; // STAGE�ｼ�

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 3 に設定
=======
	// stage == 3 縺ｫ險ｭ螳�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_3)) {

		scene = 2;
		stage = 3; // STAGE�ｼ�

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 4 に設定
=======
	// stage == 4 縺ｫ險ｭ螳�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_4)) {

		scene = 2;
		stage = 4; // STAGE�ｼ�

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 5 に設定
=======
	// stage == 5 縺ｫ險ｭ螳�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_5)) {

		scene = 2;
		stage = 5; // STAGE�ｼ�

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 6 に設定
=======
	// stage == 6 縺ｫ險ｭ螳�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_6)) {

		scene = 2;
		stage = 6; // STAGE�ｼ�

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 7 に設定
=======
	// stage == 7 縺ｫ險ｭ螳�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_7)) {

		scene = 2;
		stage = 7; // STAGE�ｼ�

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 8 に設定
=======
	// stage == 8 縺ｫ險ｭ螳�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_8)) {

		scene = 2;
		stage = 8; // STAGE�ｼ�

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 9 に設定
=======
	// stage == 9 縺ｫ險ｭ螳�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_9)) {

		scene = 2;
		stage = 9; // STAGE�ｼ�

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 10 に設定
=======
	// stage == 10 縺ｫ險ｭ螳�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_0)) {

		scene = 2;
		stage = 10; // STAGE�ｼ托ｼ�

		ThingPointa player(new Player);
		ADD_list(player);
	}
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 2 の場合　プレイ画面
=======
// scene == 2 縺ｮ譎ゅ��繝励Ξ繧､逕ｻ髱｢
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
void Game::GAME_PLAY() {

	// 繝舌ャ繧ｯ縺ｮ謠冗判
	DrawExtendGraph(p_x, 0, p_w, HEIGHT, Game_p, TRUE);
	DrawExtendGraph(p_x + WIDTH, 0, p_w + WIDTH, HEIGHT, Game_p, TRUE); // �ｼ呈椢逶ｮ縺ｮ繝ｫ繝ｼ繝�

	//-------------------------------------------------------------------------------------

	if (!pause_flag) {

		// STAGE�ｼ托ｽ橸ｼ薙�ｮ蝣ｴ蜷�
		if (stage <= 3) {

			// 繧ｨ繝輔ぉ繧ｯ繝医�ｮ螳溯｣��ｼ医ヰ繝�繧ｯ繧貞ｷｦ縺ｸ蝗槭☆�ｼ�
			p_x -= 2 + add_s;
			p_w -= 2 + add_s;
		}

		// STAGE�ｼ費ｽ橸ｼ吶�ｮ蝣ｴ蜷�
		if (4 <= stage && stage <= 9) {

			p_x -= 3 + add_s;
			p_w -= 3 + add_s;
		}

		// STAGE�ｼ托ｼ舌�ｮ蝣ｴ蜷�
		if (stage == 10) {

			p_x -= 4 + add_s;
			p_w -= 4 + add_s;
		}
	}

	// 繝懊せ縺ｮ蝣ｴ蜷医��繝舌ャ繧ｯ繧帝ｫ倬�溘〒蝗槭☆
	if (add_s < 40 && boss_flag) add_s += 1;

	// 繝舌ャ繧ｯ縺ｮ繝ｫ繝ｼ繝�
	if (p_x <= -1200) {

		p_x = 0;
		p_w = WIDTH;
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// for_eachはコンテナ（list etc.）の first-last に対して関数の適用を実装
	// 構文は [CAPTURE] (仮引数リスト) {関数の本体}
	// Thing リストに入る全てのクラスの move関数を使用
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->move(); });

	// Thing リストに入る全てのクラスの draw関数をを使用する
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->draw(); });

	// 当たり判定の実装
	// 範囲全てのクラスに関数を「＆（参照）」に　関数内で mob を使用出来る
	// ２個のクラスを使用している為　この部分だけこの形
	// 当たる場合　両方の hit関数を適用
	for_each(thing_list.begin(), thing_list.end(), [&](ThingPointa & main) {

		if (main->HIT_TYPE() == TYPE_NONE) return; // TYPE_NONE の場合　無視
=======
	// for_each縺ｯ繧ｳ繝ｳ繝�繝奇ｼ�list etc.�ｼ峨�ｮ first-last 縺ｫ蟇ｾ縺励※髢｢謨ｰ縺ｮ驕ｩ逕ｨ繧貞ｮ溯｣�縺吶ｋ
	// 讒区枚縺ｯ [CAPTURE] (莉ｮ蠑墓焚繝ｪ繧ｹ繝�) {髢｢謨ｰ縺ｮ譛ｬ菴党
	// Thing 繝ｪ繧ｹ繝医↓蜈･繧句�ｨ縺ｦ縺ｮ繧ｯ繝ｩ繧ｹ縺ｮ move()髢｢謨ｰ繧偵ｒ菴ｿ逕ｨ縺吶ｋ
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->move(); });

	// Thing 繝ｪ繧ｹ繝医↓蜈･繧句�ｨ縺ｦ縺ｮ繧ｯ繝ｩ繧ｹ縺ｮ draw()髢｢謨ｰ繧偵ｒ菴ｿ逕ｨ縺吶ｋ
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->draw(); });

	// 蠖薙◆繧雁愛螳壹�ｮ螳溯｣�繧偵☆繧�
	// 遽�蝗ｲ蜈ｨ縺ｦ縺ｮ繧ｯ繝ｩ繧ｹ縺ｫ髢｢謨ｰ繧偵�鯉ｼ��ｼ亥盾辣ｧ�ｼ峨�阪↓縺吶ｋ縺薙→縺ｧ 髢｢謨ｰ蜀�縺ｧ mob 繧剃ｽｿ逕ｨ蜃ｺ譚･繧�
	// �ｼ貞�九�ｮ繧ｯ繝ｩ繧ｹ繧剃ｽｿ逕ｨ縺励※縺�繧九◆繧� 縺薙�ｮ驛ｨ蛻�縺�縺代％縺ｮ蠖｢
	// 蠖薙◆繧句�ｴ蜷� 荳｡譁ｹ縺ｮ hit()髢｢謨ｰ繧帝←逕ｨ縺吶ｋ
	for_each(thing_list.begin(), thing_list.end(), [&](ThingPointa & main) {

		if (main->HIT_TYPE() == TYPE_NONE) return; // TYPE_NONE縺ｮ蝣ｴ蜷医��辟｡隕悶☆繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

		for_each(thing_list.begin(), thing_list.end(), [&](ThingPointa & mob) {

			// 荳｡譁ｹ縺ｮ HIT 繧ｿ繧､繝励�ｻGET 繧ｿ繧､繝励ｒ蛻､蛻･縺励※ 霑斐☆繧ｿ繧､繝励�ｮ遲峨＠縺�蝣ｴ蜷�
			if (main->HIT_TYPE() == mob->GET_TYPE()) {

				// 蠖薙◆繧句�ｴ蜷�
				if (main->HIT_test(mob)) {

<<<<<<< HEAD
					// hit関数を適用
					// 損害量・特殊量の計算に GET_damage関数・GET_energy関数を使用
=======
					// hit()髢｢謨ｰ繧帝←逕ｨ縺吶ｋ
					// 謳榊ｮｳ驥上�ｻ迚ｹ谿企�上�ｮ險育ｮ励↓ GET_damage()髢｢謨ｰ繝ｻGET_energy()髢｢謨ｰ繧剃ｽｿ逕ｨ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
					main->hit(mob->GET_damage(), mob->GET_energy());
					mob->hit(main->GET_damage(), main->GET_energy());
				}
			}
		});
	});

	// shot_count 繧偵�励Λ繧ｹ縺吶ｋ
	shot_count++;

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------
=======
	// game_flag true 縺ｮ蝣ｴ蜷�
	if (game_flag) {

		// 蛻ｶ髯先凾髢薙�ｮ險育ｮ�
		timer = (GetNowCount() - start_time) / 1000 - limit_time;
		now_time = -timer;
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	// プレイ中の場合
	if (play_flag) {
		
		SetFontSize(20);
<<<<<<< HEAD
		DrawFormatString(WIDTH - 200, HEIGHT - 35, GetColor(255, 255, 255), "T I M E : %d", now_time); // 制限時間の描画
	
		// ポーズ（休止）フラグ false の場合　敵・回復を生成
		if (!pause_flag) {

			// 制限時間の計算
			now_time = (start_time - GetNowCount()) / 1000 + limit_time;

			// スコア２００００未満の場合
			if (score < 20000) {

				//-------------------------------------------------------------------------------------
				// 敵の出現（STAGE１〜９）

				// ENEMY1（普通）
				if (stage == 1 || stage == 2 || stage == 3 || stage == 5 || stage == 6 || stage == 7) { // 出現 STAGE 設定

					if (GetRand(40) == 0) {

						ThingPointa enemy1(new Enemy1); // 敵生成
						ADD_list(enemy1); // Thing リストに ENEMY1 アドレスを追加
						if (0 <= enemy_num) enemy_num += 1; // enemy_num に+１
					}
				}

				//-------------------------------------------------------------------------------------
				// ENEMY2（タフ）
=======
		DrawFormatString(WIDTH - 200, HEIGHT - 35, GetColor(255, 255, 255), "T I M E : %d", now_time); // 蛻ｶ髯先凾髢薙�ｮ謠冗判

		// 繝昴�ｼ繧ｺ�ｼ井ｼ第ｭ｢�ｼ峨ヵ繝ｩ繧ｰ false縺ｧ縺ゅｋ蝣ｴ蜷医��謨ｵ繝ｻ蝗槫ｾｩ繧堤函謌�
		if (!pause_flag) {

			// 繧ｹ繧ｳ繧｢�ｼ抵ｼ撰ｼ撰ｼ撰ｼ先悴貅�縺ｮ蝣ｴ蜷�
			if (score < 20000) {

				// 謨ｵ縺ｮ蜃ｺ迴ｾ�ｼ�STAGE�ｼ托ｽ橸ｼ呻ｼ�
				// ENEMY1�ｼ域勸騾夲ｼ�
				if (stage == 1 || stage == 2 || stage == 3 || stage == 5 || stage == 6 || stage == 7) { // 蜃ｺ迴ｾ縺吶ｋ STAGE 險ｭ螳�

					if (GetRand(40) == 0) {

						ThingPointa enemy1(new Enemy1); // 謨ｵ逕滓��
						ADD_list(enemy1); // Thing 繝ｪ繧ｹ繝医↓ ENEMY1 繧｢繝峨Ξ繧ｹ繧定ｿｽ蜉�

						if (0 <= enemy_num) enemy_num += 1; // enemy_num 縺ｫ+�ｼ代☆繧�
					}
				}

				// ENEMY2�ｼ医ち繝包ｼ�
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
				// ENEMY3（ベクトル）
=======
				// ENEMY3�ｼ医�吶け繝医Ν�ｼ�
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
				// ENEMY4（高速）
=======
				// ENEMY4�ｼ磯ｫ倬�滂ｼ�
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
				// ENEMY5（通常攻撃）
=======
				// ENEMY5�ｼ磯�壼ｸｸ謾ｻ謦��ｼ�
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
				// ENEMY6（ベクトル攻撃）
=======
				// ENEMY6�ｼ医�吶け繝医Ν謾ｻ謦��ｼ�
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
			// STAGE１０

=======
			// STAGE�ｼ托ｼ�
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
			// スコア ２００００以上 そして ボスフラグ false の場合　ボスを生成
=======
			// 繧ｹ繧ｳ繧｢ �ｼ抵ｼ撰ｼ撰ｼ撰ｼ蝉ｻ･荳� 縺昴＠縺ｦ 繝懊せ繝輔Λ繧ｰ false 縺ｮ蝣ｴ蜷医��繝懊せ繧堤函謌舌☆繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			if (20000 <= score && !boss_flag) {

				boss_flag = true; // 繝懊せ繝輔Λ繧ｰ繧� true 縺ｫ

				if (boss_flag) {

<<<<<<< HEAD
					StopSoundMem(Play_m); // プレイ画面の音を停止
					PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP); // ボス画面の音を再生
=======
					StopSoundMem(Play_m); // 繝励Ξ繧､荳ｭ縺ｮ髻ｳ繧貞●豁｢縺吶ｋ
					PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP); // 繝懊せ荳ｭ縺ｮ髻ｳ繧貞�咲函縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

					// STAGE�ｼ托ｽ橸ｼ吶�ｮ蝣ｴ蜷�
					if (stage <= 9) {

						ThingPointa enemy_boss1(new Enemy_Boss1);
						ADD_list(enemy_boss1);
					}

					// STAGE�ｼ托ｼ舌�ｮ蝣ｴ蜷�
					if (stage == 10) {

						ThingPointa enemy_boss2(new Enemy_Boss2);
						ADD_list(enemy_boss2);
					}
				}
			}

<<<<<<< HEAD
			//-------------------------------------------------------------------------------------
			// 常に生成　 回復生成
=======
			// 蟶ｸ縺ｫ逕滓�舌☆繧�
			// 蝗槫ｾｩ逕滓��
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
		// ポーズ（休止）画面へ
		if (PUSH_back()) {

			if (!pause_flag) {

				stop_time = GetNowCount(); // 現在時間を得る
				PlaySoundMem(Pause_m, DX_PLAYTYPE_BACK); // ポーズ画面の音を再生
			}

			pause_flag = true;
			StopSoundMem(Play_m); // プレイ画面の音を停止
			StopSoundMem(Boss_m); // ボス画面の音を停止
		}

		// ポーズ（休止）画面
=======
		// 繝昴�ｼ繧ｺ�ｼ井ｼ第ｭ｢�ｼ臥判髱｢縺ｸ
		if (PUSH_back()) {

			if (!pause_flag) PlaySoundMem(Pause_m, DX_PLAYTYPE_BACK); // 繝昴�ｼ繧ｺ髻ｳ縺ｮ蜀咲函縺吶ｋ

			pause_flag = true;
			StopSoundMem(Play_m); // 繝励Ξ繧､荳ｭ縺ｮ髻ｳ繧貞●豁｢縺吶ｋ
			StopSoundMem(Boss_m); // 繝懊せ荳ｭ縺ｮ髻ｳ繧貞●豁｢縺吶ｋ
		}

		// 繝昴�ｼ繧ｺ�ｼ井ｼ第ｭ｢�ｼ臥判髱｢繧呈緒逕ｻ縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		if (pause_flag) {

			DrawBox(150, 150, WIDTH - 150, HEIGHT - 150, GetColor(255, 255, 255), TRUE);
			DrawExtendGraph(170, 170, WIDTH - 170, 240, Pause_p, TRUE);
			DrawExtendGraph(160, 330, WIDTH - 160, 420, Esc_p, TRUE);

<<<<<<< HEAD
			pause_time = (GetNowCount() - stop_time) / 1000; // ポーズ時間を計算
			
			//-------------------------------------------------------------------------------------
			// ポーズの終了・再開
=======
			// 繝昴�ｼ繧ｺ縺ｮ邨ゆｺ�繝ｻ蜀埼幕縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			if (PUSH_space()) {

				pause_flag = false;
				limit_time = pause_time + limit_time; // ポーズ時間分プラスする
				pause_time = 0; // ０に

<<<<<<< HEAD
				// ボス未登場の場合　プレイ中の音を再生
				if (!boss_flag) PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP);

				// ボス登場中の場合　ボス中の音を再生
=======
				// 繝懊せ譛ｪ逋ｻ蝣ｴ縺ｮ蝣ｴ蜷医��繝励Ξ繧､荳ｭ縺ｮ髻ｳ繧貞�咲函縺吶ｋ
				if (!boss_flag) PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP);

				// 繝懊せ縺ｮ蝣ｴ蜷医��繝懊せ荳ｭ縺ｮ髻ｳ繧貞�咲函縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				if (boss_flag) PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP);
			}
		}

<<<<<<< HEAD
		//-------------------------------------------------------------------------------------
		// プレイしている間　画面左端に文字を描画
		else DrawFormatString(50, HEIGHT - 35, GetColor(255, 255, 255), "B A C K  S P A C E : P A U S E");
	}

	//-------------------------------------------------------------------------------------
	// プレイ前　文字を描画
	else {

		// B を押す場合　PUSH SPACE を描画
		if (CheckHitKey(KEY_INPUT_B)) space_flag = true; // スペースフラグを true に
		if (space_flag) DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

		// 操作確認　文字を描画
		DrawFormatString(600, 140, GetColor(255, 255, 255), "■ O P E R A T I N G  M E T H O D ■");
=======
		// 繝励Ξ繧､縺励※縺�繧矩俣縲�逕ｻ髱｢蟾ｦ遶ｯ縺ｫ譁�蟄励ｒ謠冗判縺吶ｋ
		else DrawFormatString(50, HEIGHT - 35, GetColor(255, 255, 255), "B A C K  S P A C E : P A U S E");
	}

	// game_flag縲�false 縺ｮ蝣ｴ蜷医��譁�蟄励ｒ謠冗判縺吶ｋ
	else {

		// B 繧呈款縺励◆蝣ｴ蜷医��PUSH SPACE 繧呈緒逕ｻ縺吶ｋ
		if (CheckHitKey(KEY_INPUT_B)) space_flag = true;
		if (space_flag) DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

		// 謫堺ｽ懊��譁�蟄励ｒ謠冗判縺吶ｋ
		DrawFormatString(600, 140, GetColor(255, 255, 255), "笆� O P E R A T I N G  M E T H O D 笆�");
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		DrawFormatString(600, 170, GetColor(0, 255, 255), "B : S H O T");
		DrawFormatString(600, 200, GetColor(255, 255, 255), "E L S E : S P E C I A L  S H O T");
		DrawFormatString(600, 230, GetColor(0, 255, 255), "S C O R E : 2 0 0 0 0");

		DrawFormatString(600, 320, GetColor(255, 255, 255), "笆� H I N T 笆�");
		DrawFormatString(600, 350, GetColor(0, 255, 255), "I F  Y O U  G E T  T H E  B L U E  H E A R T");
		DrawFormatString(600, 380, GetColor(0, 255, 255), "Y O U  C A N  U S E  S P E C I A L  S H O T ...");

<<<<<<< HEAD
		//-------------------------------------------------------------------------------------
		// SPACE を押す場合　プレイスタート
		if (PUSH_space()) {

			StopSoundMem(Title_m); // タイトル画面の音を停止
			PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP); // プレイ画面の音を再生
			play_flag = true; // プレイフラグを true に
			start_time = GetNowCount(); // 制限時間をスタート
		}
	}

	//-------------------------------------------------------------------------------------
	// ボス未登場の場合　スコアを示す
=======
		// SPACE KEY 繧呈款縺励◆蝣ｴ蜷医��繝励Ξ繧､繧ｹ繧ｿ繝ｼ繝医☆繧�
		if (PUSH_space()) {

			StopSoundMem(Title_m); // 繧ｿ繧､繝医Ν荳ｭ縺ｮ髻ｳ繧貞●豁｢縺吶ｋ
			PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP); // 繝励Ξ繧､荳ｭ縺ｮ髻ｳ繧貞�咲函縺吶ｋ
			game_flag = true; // game_flag 繧� true縺ｫ縺吶ｋ
			start_time = GetNowCount(); // 譎る俣邨碁℃繧偵せ繧ｿ繝ｼ繝医☆繧�
		}
	}

	// 繝懊せ譛ｪ逋ｻ蝣ｴ縺ｮ蝣ｴ蜷医��繧ｹ繧ｳ繧｢繧堤､ｺ縺�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (!boss_flag) {

		SetFontSize(20);
		DrawFormatString(WIDTH - 220, 15, GetColor(255, 255, 255), "S C O R E : %d", score);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------
	// ESC を押す場合　タイトル画面へ
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {

		scene = 0; // タイトル画面へ
		StopSoundMem(Title_m); // タイトル画面の音を停止
		StopSoundMem(Play_m); // プレイ画面の音を停止
		StopSoundMem(Boss_m); // ボス画面の音を停止
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // タイトル画面の音を再生
	}

	//-------------------------------------------------------------------------------------
	// スコアの上限（２００００に設定）
	if (20000 <= score) score = 20000;

	//-------------------------------------------------------------------------------------
	// 制限時間０の場合
	if (now_time < 0) {

		scene = 3; // オーバー画面へ
		StopSoundMem(Play_m); // プレイ画面の音を停止
		StopSoundMem(Boss_m); // ボス画面の音を停止
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // オーバー画面の音を再生
	}

	//-------------------------------------------------------------------------------------
	// Thing リスト内で条件：「削除フラグ true 」のクラスを除ける（remove_if 関数）
	// 削除フラグ true のクラスを前に
	// そして そのクラスを list.erase で Thing リストで削除・リスト内を寄せる
=======
	// ESC 繧呈款縺励◆蝣ｴ蜷医��繧ｿ繧､繝医Ν逕ｻ髱｢縺ｸ謌ｻ繧�
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {

		scene = 0;
		StopSoundMem(Title_m); // 繧ｿ繧､繝医Ν荳ｭ縺ｮ髻ｳ繧貞●豁｢縺吶ｋ
		StopSoundMem(Play_m); // 繝励Ξ繧､荳ｭ縺ｮ髻ｳ繧貞●豁｢縺吶ｋ
		StopSoundMem(Boss_m); // 繝懊せ荳ｭ縺ｮ髻ｳ繧貞●豁｢縺吶ｋ
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // 繧ｿ繧､繝医Ν荳ｭ縺ｮ髻ｳ繧貞�咲函縺吶ｋ
	}

	// 繧ｹ繧ｳ繧｢縺ｮ荳企剞�ｼ茨ｼ抵ｼ撰ｼ撰ｼ撰ｼ舌↓險ｭ螳夲ｼ�
	if (20000 <= score) score = 20000;

	// 蛻ｶ髯先凾髢難ｼ舌↓縺ｪ縺｣縺溷�ｴ蜷�
	if (now_time < 0) {

		scene = 3; // 繧ｪ繝ｼ繝舌�ｼ逕ｻ髱｢縺ｸ
		StopSoundMem(Play_m); // 繝励Ξ繧､荳ｭ縺ｮ髻ｳ繧貞●豁｢縺吶ｋ
		StopSoundMem(Boss_m); // 繝懊せ荳ｭ縺ｮ髻ｳ繧貞●豁｢縺吶ｋ
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // 繧ｪ繝ｼ繝舌�ｼ荳ｭ縺ｮ髻ｳ繧貞�咲函縺吶ｋ
	}

	// Thing 繝ｪ繧ｹ繝亥��縺ｧ譚｡莉ｶ�ｼ壼炎髯､繝輔Λ繧ｰ true 縺ｮ繧ｯ繝ｩ繧ｹ繧帝勁縺代ｋ�ｼ�remove_if 髢｢謨ｰ�ｼ�
	// 蜑企勁繝輔Λ繧ｰ true 縺ｮ繧ｯ繝ｩ繧ｹ繧貞燕縺ｫ縺吶ｋ
	// 縺昴＠縺ｦ 縺昴�ｮ繧ｯ繝ｩ繧ｹ繧� list.erase 縺ｫ繧医ｊ Thing 繝ｪ繧ｹ繝医〒蜑企勁繝ｻ繝ｪ繧ｹ繝亥��繧定ｩｰ繧√ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	auto end = remove_if(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {return Thing->GET_remove(); });
	thing_list.erase(end, thing_list.end());
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 3 の場合　オーバー画面
=======
// scene == 3 縺ｮ譎ゅ��繧ｪ繝ｼ繝舌�ｼ逕ｻ髱｢
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
void Game::GAME_OVER() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Over_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

<<<<<<< HEAD
	now_score = score; // スコアに
=======
	now_score = score; // 繧ｹ繧ｳ繧｢縺ｫ鄂ｮ謠帙☆繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Y O U R  S C O R E : %d", now_score);

<<<<<<< HEAD
	// ハイスコア＜スコアの場合
	if (high_score < now_score) {

		// 値を上書き・記録
=======
	// 繝上う繧ｹ繧ｳ繧｢繧医ｊ繧ｹ繧ｳ繧｢縺悟､ｧ縺阪＞蝣ｴ蜷�
	if (high_score < now_score) {

		// 蛟､繧剃ｸ頑嶌縺阪�ｻ險倬鹸縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		high_score = now_score;
		SAVE_highscore();
	}

<<<<<<< HEAD
	// SPACE を押す場合　タイトル画面へ
=======
	// SPACE KEY 繧呈款縺励◆蝣ｴ蜷医��繧ｿ繧､繝医Ν逕ｻ髱｢縺ｸ謌ｻ繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Over_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 4 の場合　クリア画面
=======
// scene == 4 縺ｮ譎ゅ��繧ｯ繝ｪ繧｢逕ｻ髱｢
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
void Game::GAME_CLEAR() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Clear_p, TRUE);
<<<<<<< HEAD
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE

	// スコアに
	// スコア　＝　時間スコア　＋　スコア（MAX２００００）　＋　STAGE × 10000
=======
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE 縺ｮ謠冗判

	// 繧ｹ繧ｳ繧｢縺ｫ鄂ｮ謠帙☆繧�
	// 繧ｹ繧ｳ繧｢縲��ｼ昴��譎る俣繧ｹ繧ｳ繧｢縲��ｼ九��繧ｹ繧ｳ繧｢�ｼ�MAX�ｼ抵ｼ撰ｼ撰ｼ撰ｼ撰ｼ峨���ｼ九��STAGE ﾃ� 10000
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	now_score = now_time * 100 + score + stage * 10000;

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Y O U R  S C O R E : %d", now_score);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "T I M E  P O I N T : %d + S C O R E : %d + S T A G E  P O I N T : %d", now_time * 100, score, stage * 10000);

<<<<<<< HEAD
	// ハイスコア＜スコアの場合
	if (high_score < now_score) {

		// 値を上書き・記録
=======
	// 繝上う繧ｹ繧ｳ繧｢繧医ｊ繧ｹ繧ｳ繧｢縺悟､ｧ縺阪＞蝣ｴ蜷�
	if (high_score < now_score) {

		// 蛟､繧剃ｸ頑嶌縺阪�ｻ險倬鹸縺吶ｋ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		high_score = now_score;
		SAVE_highscore();
	}

<<<<<<< HEAD
	// SPACE を押す場合 タイトル画面へ
=======
	// SPACE KEY 繧呈款縺励◆蝣ｴ蜷� 繧ｿ繧､繝医Ν逕ｻ髱｢縺ｸ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Clear_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

void Game::GAME_END() {

	DxLib_End(); // DX繝ｩ繧､繝悶Λ繝ｪ縺ｮ邨ゆｺ�
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// WinMain 関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game; // Game クラスを game に
=======
// WinMain 髢｢謨ｰ
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game; // GAME 繧ｯ繝ｩ繧ｹ繧� game 縺ｫ鄂ｮ謠帙☆繧�
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	game.GAME_SET();
	game.GAME_ALL();
	game.GAME_END();
	return 0;
}
