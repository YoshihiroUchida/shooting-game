#define _USE_MATH_DEFINES
#include <math.h>
#include <memory> // for smart pointer
#include <list> // for list
#include <algorithm> // for for_each
#include "sqlite3.h" // for DB
#include "DxLib.h" // for DxLib

//=====================================================================================
// 画像ファイル用
enum class Object_Type {
	NONE,
	PLAYER,
	SHOT, THROUGH_SHOT, TIMED_SHOT, CHARGE_SHOT, BEAM,
	ENEMY, ENEMY2, ENEMY3, ENEMY4, ENEMY5, ENEMY6,
	ENEMY_BOSS1, ENEMY_BOSS2, ENEMY_BOSS3, ENEMY_BOSS4,
	HEAL1, HEAL2,
	BURN,

	// Game
	TITLE,
	STAGE_SELECT,
	LEFT, RIGHT,
	CLOCK,
	GAME_OVER, GAME_CLEAR,
	PUSH_SPACE,
	SCORE,
	PAUSE,
	PAUSE_MENU,
	BACK_SPACE,
	ESC,
	RESTART,
	WARNING,
	HP, SP,
	PLEASE_ENTER,
	RANKING, RANKING_LIST,

	// 弾道名称の表示用
	SHOT_FONT,
	NORMAL_FONT,
	CHARGE_FONT,
	SWIRL_FONT,
	THROUGH_FONT,
	BEAM_FONT,
	PARABOLA_FONT,
	HOMING_FONT,
	TIMED_FONT,
	N_WAY_FONT,
	SWIRL_3D_FONT,

	// 値表示用
	_0_, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_,
	NUM,
};

//-------------------------------------------------------------------------------------
// 音ファイル用
enum class Sound_Type {
	SHOT1, THROUGH_SHOT,
	CHARGE, CHARGE_SHOT,
	ENEMY_SHOT,
	BEAM,
	E_ATTACK, P_ATTACK,
	SWITCH, COMMAND, HEAL, BREAK, ALERT,
	TITLE, GAME_PLAY, GAME_OVER, GAME_CLEAR, PAUSE, BOSS,
	NUM,
};

//-------------------------------------------------------------------------------------
enum Stage_Type {
	TITLE,
	ACCOUNT,
	RANKING,
	SELECT,
	PLAY,
	GAME_OVER,
	GAME_CLEAR,
	ER,
};

enum Enemey_shot_Type {
	N_WAY_1,
	NORMAL,
	MULTI_DIRECT_SWIRL,
	TYPE_NUM,
};

//-------------------------------------------------------------------------------------
int en_x; // 敵のx座標
int en_y; // 敵のy座標
int enemy_num = 0; // 敵数
int enemy_s; // 敵の速度
int effect_vol = 180; // 効果音の音量
int bgm_vol = 190; // BGMの音量
int picture_array[static_cast<int>(Object_Type::NUM)]; // 画像ファイル用
int sound_array[static_cast<int>(Sound_Type::NUM)]; // 音ファイル用

//-------------------------------------------------------------------------------------
// 画像ファイルの読込み
void Set_picture(const char* file_name, const Object_Type ot) {
	char path[100];
	sprintf_s(path, "Picture_file/%s", file_name);

	if (picture_array[static_cast<int>(ot)] == 0) {
		picture_array[static_cast<int>(ot)] = LoadGraph(path);
	}
}

//-------------------------------------------------------------------------------------
// 音楽ファイルの読込み
void Set_sound(const char* file_name, const Sound_Type st) {
	char path[100];
	sprintf_s(path, "Sound_file/%s", file_name);

	if (sound_array[static_cast<int>(st)] == 0) {
		sound_array[static_cast<int>(st)] = LoadSoundMem(path);
	}
}

//-------------------------------------------------------------------------------------
// 簡易DXライブラリ関数
void My_DrawExtendGraph(int x1, int y1, int x2, int y2, const Object_Type ot) {
	DrawExtendGraph(x1, y1, x2, y2, picture_array[static_cast<int>(ot)], TRUE);
}

//-------------------------------------------------------------------------------------
// 度 → ラジアン変換
double Deg_to_rad(const double degree) {
	return degree * M_PI / 180.0;
}

//=====================================================================================
// スマートポインタ
class Object;
typedef std::shared_ptr <Object> Object_Pointer;

// 継承クラス
class Object {
protected:
	double m_x; // x座標
	double m_y; // y座標
	int m_w; // 横幅
	int m_h; // 縦幅
	int m_s; // 速度

	// 当たり判定用変数
	double hit_x; // x座標
	double hit_y; // y座標
	int hit_w; // 横幅
	int hit_h; // 縦幅

	int hp_max; // 最大HP
	int hp_now;	// 現在HP
	int sp_max;	// 最大SP
	int sp_now;	// 現在SP
	int damage;	// ダメージ量
	int energy;	// SP量
	int shot_count;
	bool remove_flag; // 削除フラグ
	void Remove();

public:
	Object();
	virtual Object_Type Get_type() = 0; // 自タイプを取得（純粋仮想）
	virtual Object_Type Hit_type() { return Object_Type::NONE; };

	virtual void Set_position(const int position_x, const int position_y); // 座標の設定
	virtual void Set_hit_area(const int x, const int y, const int w, const int h); // 当たり判定対象の設定

	bool Get_remove() { return remove_flag; }; // 削除フラグの取得
	bool Hit_test(Object_Pointer& op); // 当たり判定処理の設定

	int Get_damage() { return damage; };
	int Get_energy() { return energy; };

	virtual void Set_degree(const double degree) {}; // 角度の設定
	virtual void Set_sign(const int s) {}; // 符号 (+ ／ -) の設定
	void Set_range();
	virtual void Move() = 0; // 動作 (純粋仮想関数)
	virtual void Draw() = 0; // 画像を描画
	virtual void Hit(int damage, int energy) {}; // 当たり判定時の設定
	virtual void Hit() {};
};

//-------------------------------------------------------------------------------------
class Player : public Object {
private:
	double deg;
	int sign;
	int shot_num;
	int charge_time; // 拡大弾用
	int dead_time; // 点滅用
	bool beam_flag;
	bool shot_flag;

public:
	Player();
	void Move();
	void Draw_hp();
	void Draw_sp();
	void Draw_font();
	void Draw();
	void Hit(int damage, int energy);
	Object_Type Get_type() { return Object_Type::PLAYER; };
	Object_Type Hit_type() { return Object_Type::ENEMY; };
};

//-------------------------------------------------------------------------------------
// 通常弾
class Shot : public Object {
protected:
	double center_x; // 中心x座標
	double center_y; // 中心y座標
	double radian; // ラジアン

public:
	Shot();
	void Move();
	void Draw();
	void Hit();
	Object_Type Get_type() { return Object_Type::SHOT; };
	Object_Type Hit_type() { return Object_Type::ENEMY; };
};

//-------------------------------------------------------------------------------------
// 貫通弾
class Through_Shot : public Shot {
public:
	Through_Shot();
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// 光線
class Beam : public Shot {
public:
	Beam();
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// 渦巻弾
class Swirl_Shot : public Through_Shot {
private:
	double r; // 半径
	double tmp; // 計算調整用変数

public:
	Swirl_Shot();
	void Set_position(const int position_x, const int position_y);
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// N-way弾
class N_way_Shot : public Through_Shot {
public:
	N_way_Shot();
	void Set_degree(const double degree); // 角度を設定
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// 3D渦巻弾
class Swirl_3D_Shot : public Shot {
private:
	double r;
	int sign;

public:
	Swirl_3D_Shot();
	void Set_position(const int, const int);
	void Set_sign(int s);
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// チャージ弾
class Charge_Shot : public Shot {
private:
	int deg;
	bool charge_flag;

public:
	Charge_Shot();
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// 時限式弾
class Timed_Shot : public Object {
private:
	int time; // 発射までの時間
	int shot_count; // 発射する数

public:
	Timed_Shot();
	void Move();
	void Draw();
	Object_Type Get_type() { return Object_Type::TIMED_SHOT; };
	Object_Type Hit_type() { return Object_Type::NONE; };
};

//-------------------------------------------------------------------------------------
// 上・下
class Timed_Shot_Sub1 : public Through_Shot {
protected:
	int sign;

public:
	Timed_Shot_Sub1();
	void Set_sign(int s);
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// 左・右
class Timed_Shot_Sub2 : public Timed_Shot_Sub1 {
public:
	Timed_Shot_Sub2();
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// 追尾弾
class Homing_Shot : public Shot {
public:
	Homing_Shot();
	double Unit_vec(const double vec, const double vec_x, const double vec_y); // 単位ベクトルの取得
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// 放物線弾
class Parabola_Shot : public Shot {
private:
	double a = 0.0;
	double b = 0.0;
	double c = 0.0;

public:
	Parabola_Shot();
	void Det(const double(*mat)[3], double* det); // 行列式の計算
	void Set_position(const int, const int);
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// 加速弾
class Speed_Up_Shot : public Shot {
private:
	int acc = 0;

public:
	Speed_Up_Shot();
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// 多方向渦巻弾
class Multi_Direct_Swirl_Shot : public Shot {
public:
	Multi_Direct_Swirl_Shot();
	void Set_degree(const double degree);
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// 敵
class Enemy1 : public Object {
protected:
	int up_down; // 上下方向

public:
	Enemy1();
	void Effect(bool boss_flag);
	void Remove_func();	// 削除関連の実装
	void Move();
	void Draw();
	void Hit(int damage, int energy);
	Object_Type Get_type() { return Object_Type::ENEMY; };
	Object_Type Hit_type() { return Object_Type::PLAYER; };
};

//-------------------------------------------------------------------------------------
// タフ
class Enemy2 : public Enemy1 {
public:
	Enemy2();
	void Move();
	void Draw();
};

//-------------------------------------------------------------------------------------
// ベクトル
class Enemy3 : public Enemy1 {
public:
	Enemy3();
	void Move();
	void Draw();
};

//-------------------------------------------------------------------------------------
// スピード
class Enemy4 : public Enemy1 {
public:
	Enemy4();
	void Move();
	void Draw();
};

//-------------------------------------------------------------------------------------
// 通常攻撃
class Enemy5 : public Enemy1 {
public:
	Enemy5();
	void Move();
	void Draw();
};

//-------------------------------------------------------------------------------------
// ベクトル攻撃
class Enemy6 : public Enemy1 {
public:
	Enemy6();
	void Move();
	void Draw();
};

//-------------------------------------------------------------------------------------
class Enemy_Boss1 : public Enemy1 {
protected:
	int shot_count;
	int time;
	int add_speed; // 速度を上げる
	int tmp;
	int sign;
	double deg;
	bool time_flag;
	bool sound_flag;

public:
	Enemy_Boss1();
	void Set_shot_type(const int num);
	void Move();
	void Draw_hp();
	void Draw();
	void Hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------
class Enemy_Boss2 : public Enemy_Boss1 {
public:
	Enemy_Boss2();
	void Move();
	void Draw();
};

//-------------------------------------------------------------------------------------
class Enemy_Shot : public Object {
private:
	int type_num;
	int sign;
	double radian;
	double rad;
	double center_x;
	double center_y;

public:
	Enemy_Shot(const int size, const int num);
	void Set_position2(const int position_x, const int position_y);
	void Set_degree(const double degree);
	void Move();
	void Draw();
	void Hit();
	Object_Type Get_type() { return Object_Type::SHOT; };
	Object_Type Hit_type() { return Object_Type::PLAYER; };
};

//-------------------------------------------------------------------------------------
class Explosion : public Object {
private:
	int size;
	bool flag;

public:
	Explosion(const double x, const double y, const int w, const int h, const int c, bool boss_flag);
	void Move();
	void Draw();
	void Hit() {}; // 当たり判定×
	Object_Type Get_type() { return Object_Type::NONE; };
};

//-------------------------------------------------------------------------------------
// HP回復
class Heal1 : public Object {
public:
	Heal1();
	void Move();
	void Draw();
	void Hit();
	Object_Type Get_type() { return Object_Type::HEAL1; };
	Object_Type Hit_type() { return Object_Type::PLAYER; };
};

//-------------------------------------------------------------------------------------
// SP(Shot Points)回復
class Heal2 : public Heal1 {
public:
	Heal2();
	void Draw();
	void Move();
	void Hit();
};

//-------------------------------------------------------------------------------------
class Mob : public Object {
private:
	void Reset_position(bool); // 邪魔物の初期設定を再度・完全化不完全化
	int tmp = 0;

public:
	Mob();
	void Move();
	void Draw();
	Object_Type Get_type() { return Object_Type::NONE; };
};

//-------------------------------------------------------------------------------------
class Game {
private:
	// Object型のリスト
	std::list <Object_Pointer> objects_list;

	// フラグ変数
	bool push_flag;	// PUSH_space関数・PUSH_back関数用
	bool play_flag;	// プレイ用・true でスタート
	bool space_flag; // スペース用
	bool num_flag;
	bool name_flag;
	bool pause_flag;

	// スコア・時間に関する変数
	int high_score;	// 最高得点
	int now_score; // スコア
	int now_time; // 残り時間
	int start_time;	// 1s 単位で計測する
	int stop_time; // ポーズする場合　現在時間を得る
	int pause_time;	// ポーズ画面の経過時間
	int limit_time;	// 制限時間
	int warning_time;

	static const int name_size = 20; // 文字数
	char name_data[name_size + 1] = "";
	const char* file_name = "database.db"; // データベースのファイル名

public:
	bool boss_flag; // ボスフラグ
	bool debug_flag; // デバッグ用
	int score; // スコア
	int scene; // 画面
	int stage; // ステージ

	Game();
	static const int Display_w = 1200; // ディスプレイのタテ幅
	static const int Display_h = 600; // ディスプレイのヨコ幅
	static const int Top = 40; // Play 画面 上座標
	static const int Height = Display_h - 40; // Play 画面 下座標

	void Add_list(Object_Pointer& tp); // リストの追加
	void Add_score(const int s); // スコアの追加
	bool Push_space(); // スペース操作
	bool Push_back(); // バックスペース操作

	// データベース関連
	void Check_database();
	void Add_name_to_database();
	void Add_score_to_database(const int s);
	void Show_ranking_from_database();
	int Get_score(); // ユーザのスコア値の取得

	void Enemy_Form(const int x); // 敵の生成
	void Draw_numbers(const int num, const int x, const int y, const int w, const int h);
	void Switch_stage();

	// 音楽ファイル関連
	void Sound_play(const Sound_Type st, const int volume); // 効果音の再生
	void Sound_loop_play(const Sound_Type st, const int volume); // ループBGMの再生
	void Sound_stop(const Sound_Type st); // 音の停止

	void Game_set(); // 設定
	void Game_all(); // 分岐
	void Game_title(); // タイトル
	void Game_Account(); // ログイン
	void Game_select(); // ステージ選択
	void Game_ranking(); // ランキング表示
	void Game_play(); // プレイ
	void Game_over(); // Game Over
	void Game_clear(); // Game Clear
	void Error_screen(); // エラー対策
	void Game_end(); // DXライブラリの終了
};

//------------------------------------------------------------------------------------
Game* game; // インスタンス化

// 実装部分
//====================================================================================
void Object::Remove() {
	remove_flag = true;
}

//------------------------------------------------------------------------------------
Object::Object() {
	m_x = 0;
	m_y = 0;
	m_w = 0;
	m_h = 0;
	m_y = 0;
	m_s = 0;
	damage = 0;
	energy = 0;
	hit_x = 0;
	hit_y = 0;
	hit_w = 0;
	hit_h = 0;
	hp_max = 0;
	hp_now = 0;
	sp_max = 0;
	sp_now = 0;
	shot_count = 0;
	remove_flag = false;
}

//------------------------------------------------------------------------------------
void Object::Set_position(const int position_x, const int position_y) {
	m_x = position_x;
	m_y = position_y;
}

//------------------------------------------------------------------------------------
// 当たり判定範囲の設定
void Object::Set_hit_area(const int x, const int y, const int w, const int h) {
	hit_x = x;
	hit_y = y;
	hit_w = w;
	hit_h = h;
}

//------------------------------------------------------------------------------------
// 生成範囲の設定
void Object::Set_range() {
	const int y = GetRand(Game::Height);

	if (y < Game::Top) {
		Set_position(Game::Display_w, Game::Top);
	}

	else if (Game::Height - m_h < y) {
		Set_position(Game::Display_w, Game::Height - m_h);
	}

	else {
		Set_position(Game::Display_w, y);
	}
}

//------------------------------------------------------------------------------------
bool Object::Hit_test(Object_Pointer& op) {
	const int x1 = (int)m_x + (int)hit_x; // x座標
	const int y1 = (int)m_y + (int)hit_y; // y座標
	const int w1 = hit_w; // 横幅
	const int h1 = hit_h; // 縦幅

	// 対応する当たり判定座標
	const int x2 = (int)op->m_x + (int)op->hit_x; // x座標
	const int y2 = (int)op->m_y + (int)op->hit_y; // y座標
	const int w2 = op->hit_w; // 横幅
	const int h2 = op->hit_h; // 縦幅

	if (x2 < x1 + w1 && x1 < x2 + w2 && y2 < y1 + h1 && y1 < y2 + h2) {
		return true;
	}
	return false;
}

//====================================================================================
Player::Player() {
	m_w = 70;
	m_h = 35;
	m_s = 8;
	deg = 0.0;
	sign = 1;
	charge_time = 0;
	hp_max = 10; // 最大HP
	hp_now = 5;	// 初期HP
	sp_max = 10; // 最大SP
	sp_now = 1;	// 初期SP
	damage = 0;
	energy = 0;
	shot_num = 1;
	shot_count = 0;	// 弾の間隔調整
	dead_time = 0;
	shot_flag = false;
	beam_flag = false;

	Set_position(150, 300);	// x・y 座標を設定
	Set_hit_area(0, 10, m_w - 10, m_h - 10); // 当たり判定を設定

	Set_picture("Player.png", Object_Type::PLAYER);
	Set_picture("Fonts/HP.png", Object_Type::HP);
	Set_picture("Fonts/SP.png", Object_Type::SP);
	Set_picture("Fonts/Shot_font.png", Object_Type::SHOT_FONT);
	Set_picture("Shots/Normal.png", Object_Type::NORMAL_FONT);
	Set_picture("Shots/Charge.png", Object_Type::CHARGE_FONT);
	Set_picture("Shots/Swirl.png", Object_Type::SWIRL_FONT);
	Set_picture("Shots/Through.png", Object_Type::THROUGH_FONT);
	Set_picture("Shots/Beam.png", Object_Type::BEAM_FONT);
	Set_picture("Shots/Parabola.png", Object_Type::PARABOLA_FONT);
	Set_picture("Shots/Homing.png", Object_Type::HOMING_FONT);
	Set_picture("Shots/Timed.png", Object_Type::TIMED_FONT);
	Set_picture("Shots/N_way.png", Object_Type::N_WAY_FONT);
	Set_picture("Shots/3D_Swirl.png", Object_Type::SWIRL_3D_FONT);

	// 音ファイル設定
	Set_sound("SHOT2.mp3", Sound_Type::THROUGH_SHOT);
	Set_sound("E ATTACK.mp3", Sound_Type::E_ATTACK);
}

//------------------------------------------------------------------------------------
void Player::Move() {
	if (0 < dead_time) {
		dead_time--; // 点滅用
	}

	if (charge_time == 0 && !beam_flag) {
		// 移動制御(左利き・右利き対応)
		// 左方向
		if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A)) {
			m_x -= m_s;
		}
		// 右方向
		if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) {
			m_x += m_s;
		}
		// 上方向
		if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W)) {
			m_y -= m_s;
		}
		// 下方向
		if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S)) {
			m_y += m_s;
		}

		//　画面の当たり判定
		// 左部分
		if (m_x < 0) {
			m_x = 0;
		}
		// 右部分（画面の半分を超えない設計）
		if (Game::Display_w / 2 < m_x + m_w) {
			m_x = static_cast<double>(Game::Display_w) / 2.0 - static_cast<double>(m_w);
		}
		// 上部分
		if (m_y < Game::Top) {
			m_y = Game::Top;
		}
		// 下部分
		if (Game::Height < m_y + m_h) {
			m_y = double((Game::Height)) - double(m_h);
		}
		//-----------------------------------------------------------------
	}

	//　弾道の切り替え
	if (CheckHitKey(KEY_INPUT_V)) {
		if (!shot_flag) {
			shot_num -= 1;
			shot_flag = true;
			game->Sound_play(Sound_Type::SWITCH, effect_vol);

			if (shot_num < 1) {
				shot_num = sp_now;
			}
		}
	}

	else if (CheckHitKey(KEY_INPUT_N)) {
		if (!shot_flag) {
			shot_num += 1;
			shot_flag = true;
			game->Sound_play(Sound_Type::SWITCH, effect_vol);

			if (sp_now < shot_num) {
				shot_num = 1;
			}
		}
	}

	// 隠しコマンド
	else if (CheckHitKey(KEY_INPUT_Z)) {
		// 多方向渦巻弾
		if (shot_count % 4 == 0) {
			if (!shot_flag) {
				for (int i = 0; i < 4; i++) {
					Object_Pointer shot(new Multi_Direct_Swirl_Shot);
					shot->Set_degree(deg + i * 90.0);
					shot->Set_position(m_x + m_w - 10, m_y + 25);
					game->Add_list(shot);
				}
				game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
			}
		}
	}

	else if (CheckHitKey(KEY_INPUT_X)) {
		//	加速弾
		if (shot_count % 6 == 0) {
			if (!shot_flag) {
				Object_Pointer shot(new Speed_Up_Shot);
				shot->Set_position(m_x + m_w - 10, m_y + 25);
				game->Add_list(shot);
				game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
			}
		}
	}

	//-------------------------------------------------------------------------------
	else if (CheckHitKey(KEY_INPUT_B)) {
		switch (shot_num) {
		case 1:
			// 通常弾
			if (1 <= sp_now) {
				if (!shot_flag) {
					if (shot_count % 8 == 0) {
						Object_Pointer shot(new Shot); // インスタンス生成
						shot->Set_position(m_x + m_w - 10, m_y + 25); // 座標の設定
						game->Add_list(shot); // リスト追加
						game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol); // 効果音
					}
				}
			}
			break;

		case 2:
			// 集中弾
			if (2 <= sp_now) {
				// 発射準備時間(インターバル)
				if (charge_time <= 5) {
					charge_time++;
				}

				if (charge_time == 5) {
					Object_Pointer charge_shot(new Charge_Shot);
					charge_shot->Set_position(m_x + m_w + 15, m_y + 35);
					game->Add_list(charge_shot);
					game->Sound_play(Sound_Type::CHARGE, 200);
				}
			}
			break;

		case 3:
			// 渦巻弾
			if (3 <= sp_now) {
				if (!shot_flag) {
					if (shot_count % 7 == 0) {
						Object_Pointer swirl_shot(new Swirl_Shot);
						swirl_shot->Set_position(m_x + m_w - 10, m_y + 25);
						game->Add_list(swirl_shot);
						game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
					}
				}
			}
			break;

		case 4:
			// 貫通弾
			if (4 <= sp_now) {
				if (!shot_flag) {
					if (shot_count % 10 == 0) {
						Object_Pointer through_shot(new Through_Shot);
						through_shot->Set_position(m_x + m_w - 30, m_y + 25);
						game->Add_list(through_shot);
						game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
					}
				}
			}
			break;

		case 5:
			// 光線
			if (5 <= sp_now) {
				if (!beam_flag) {
					Object_Pointer beam(new Beam);
					beam->Set_position(m_x + m_w + 15, m_y - 10);
					game->Add_list(beam);
					game->Sound_play(Sound_Type::BEAM, effect_vol);
					beam_flag = true; // 連打仕様
				}
			}
			break;

		case 6:
			// 放物線弾
			if (6 <= sp_now) {
				if (!shot_flag) {
					if (shot_count % 28 == 0) {
						if (0 < enemy_num) {
							Object_Pointer parabola_shot(new Parabola_Shot);
							parabola_shot->Set_position(m_x + m_w - 10, m_y + 25);
							game->Add_list(parabola_shot);
							game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
						}
					}
				}
			}
			break;

		case 7:
			// 追尾弾
			if (7 <= sp_now) {
				if (shot_count % 28 == 0) {
					if (!shot_flag) {
						if (0 < enemy_num) {
							Object_Pointer homing_shot(new Homing_Shot);
							homing_shot->Set_position(m_x + m_w - 10, m_y + 25);
							game->Add_list(homing_shot);
							game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
						}
					}
				}
			}
			break;

		case 8:
			// 時限式弾
			if (8 <= sp_now) {
				if (!shot_flag) {
					Object_Pointer timed_shot(new Timed_Shot);
					timed_shot->Set_position(m_x + m_w - 10, m_y + 25);
					game->Add_list(timed_shot);
					shot_flag = true; // 連打仕様
					game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
				}
			}
			break;

		case 9:
			// N-way弾
			if (9 <= sp_now) {
				if (shot_count % 10 == 0) {
					if (!shot_flag) {
						for (int i = 0; i < 7; i++) { // 7発
							Object_Pointer n_way_shot(new N_way_Shot);
							n_way_shot->Set_position(m_x + m_w - 10, m_y + 25);
							n_way_shot->Set_degree((3.0 - i) * 10.0); // 30°・20°・10°・0°を上下に設定
							game->Add_list(n_way_shot);
						}
						game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
					}
				}
			}
			break;

		case 10:
			// 立体型渦巻弾
			if (10 <= sp_now) {
				if (shot_count % 4 == 0) {
					if (!shot_flag) {
						for (int i = 1; -1 <= i; i -= 2) {
							Object_Pointer swirl_3d_shot(new Swirl_3D_Shot);
							swirl_3d_shot->Set_position(m_x + m_w - 10, m_y + 25);
							swirl_3d_shot->Set_sign(i);
							game->Add_list(swirl_3d_shot);
						}
					}
				}

				if (shot_count % 6 == 0) {
					game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
				}
			}
			break;
		}
	}

	// 全弾道を使用可 (デバッグ用)
	else if (CheckHitKey(KEY_INPUT_0)) {
		sp_now = 10;
	}

	// ボタンを押していないとき
	else {
		shot_flag = false;
		beam_flag = false;
		charge_time = 0;
	}

	if (hp_now <= 0) {
		game->scene = GAME_OVER;
		game->Sound_stop(Sound_Type::GAME_PLAY); // プレイ画面の音を停止
		game->Sound_stop(Sound_Type::BOSS); // ボス画面の音を停止
		game->Sound_loop_play(Sound_Type::GAME_OVER, bgm_vol); // オーバー画面の音を再生
	}

	// 上限設定
	if (10 <= hp_now) {
		hp_now = 10;
	}
	if (10 <= sp_now) {
		sp_now = 10;
	}

	// 360度以上のとき
	if (360 < deg) {
		deg = 0;
	}
	deg += 3 * sign;

	if (1000 < shot_count) {
		shot_count = 0;
	}
	shot_count++;
}

//------------------------------------------------------------------------------------
// ライフ表示
void Player::Draw_hp() {
	const int x1 = 10; // 基準座標
	const int w1 = 30; // 画像の横幅

	My_DrawExtendGraph(x1, 10, x1 + w1, Game::Top - 10, Object_Type::HP);

	const int x2 = x1 + w1 + 5; // 基準座標
	const int w2 = 15; // □の横幅
	const int space = 5; // □同士の間隔

	for (int i = 0; i < hp_max; i++) {
		DrawBox(x2 + i * (w2 + space), 5, (x2 + w2) + i * (w2 + space), Game::Top - 5, GetColor(130, 0, 130), TRUE);
	}
	for (int i = 0; i < hp_now; i++) {
		DrawBox(x2 + i * (w2 + space), 5, (x2 + w2) + i * (w2 + space), Game::Top - 5, GetColor(0, 255, 255), TRUE);
	}
}

//------------------------------------------------------------------------------------
void Player::Draw_sp() {
	const int x1 = 270; // 基準座標
	const int w1 = 30; // 画像の横幅

	My_DrawExtendGraph(x1, 10, x1 + w1, Game::Top - 10, Object_Type::SP);

	const int x2 = x1 + w1 + 5;	// 基準座標
	const int w2 = 15; // □の横幅
	const int space = 5; // □同士の間隔

	for (int i = 0; i < sp_max; i++) {
		DrawBox(x2 + i * (w2 + space), 5, (x2 + w2) + i * (w2 + space), Game::Top - 5, GetColor(130, 0, 130), TRUE);
	}
	for (int i = 0; i < sp_now; i++) {
		DrawBox(x2 + i * (w2 + space), 5, (x2 + w2) + i * (w2 + space), Game::Top - 5, GetColor(0, 255, 0), TRUE);
	}
}

//------------------------------------------------------------------------------------
void Player::Draw_font() {
	Object_Type ot;	// 画像判別用

	switch (shot_num) {
	case 1:
		ot = Object_Type::NORMAL_FONT;
		break;
	case 2:
		ot = Object_Type::CHARGE_FONT;
		break;
	case 3:
		ot = Object_Type::SWIRL_FONT;
		break;
	case 4:
		ot = Object_Type::THROUGH_FONT;
		break;
	case 5:
		ot = Object_Type::BEAM_FONT;
		break;
	case 6:
		ot = Object_Type::PARABOLA_FONT;
		break;
	case 7:
		ot = Object_Type::HOMING_FONT;
		break;
	case 8:
		ot = Object_Type::TIMED_FONT;
		break;
	case 9:
		ot = Object_Type::N_WAY_FONT;
		break;
	case 10:
		ot = Object_Type::SWIRL_3D_FONT;
		break;
	default:
		// エラー処理
		ot = Object_Type::NONE;
		break;
	}

	const int x1 = Game::Display_w / 2 + 20; // 基準座標
	const int w1 = 150; // 画像の横幅
	const int space = 10; // 間隔

	DrawBox(x1 - space, 5, x1 + w1 + space, Game::Top - 5, GetColor(50, 50, 50), TRUE);
	My_DrawExtendGraph(x1, 10, x1 + w1, Game::Top - 10, ot);

	const int x2 = (x1 + w1 + space) + space; // 基準座標
	const int w2 = 90; // 画像の横幅

	if (shot_num != 5) {
		My_DrawExtendGraph(x2, 10, x2 + w2, Game::Top - 10, Object_Type::SHOT_FONT);
	}
}

//------------------------------------------------------------------------------------
void Player::Draw() {
	Draw_hp();
	Draw_sp();
	Draw_font();

	if (dead_time % 5 == 0) {
		My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::PLAYER);
	}
}

//------------------------------------------------------------------------------------
void Player::Hit(int damage, int energy) {
	// 敵
	if (dead_time <= 0 && 0 < damage) {
		dead_time = 50;
		hp_now -= damage; // HPを減らす
		game->Sound_play(Sound_Type::E_ATTACK, effect_vol); // ダメージ音
	}

	// 回復道具
	if (damage < 0 && hp_now < 10) {
		hp_now -= damage; // HP回復
	}
	if (energy < 0 && sp_now < 10) {
		sp_now -= energy; // SP回復
	}
}

//====================================================================================
// 通常弾の実装
Shot::Shot() {
	center_x = 0.0;
	center_y = 0.0;
	radian = 0.0;
	m_w = 12;
	m_h = 12;
	m_s = 10;
	damage = 5;
	Set_hit_area(10, 0, m_w, m_h);
	Set_sound("P ATTACK.mp3", Sound_Type::P_ATTACK);
}

//------------------------------------------------------------------------------------
void Shot::Move() {
	m_x += m_s;

	if (Game::Display_w < m_x) {
		Remove();
	}
}

//------------------------------------------------------------------------------------
void Shot::Draw() {
	DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 2.0, GetColor(0, 255, 255), TRUE);
}

//------------------------------------------------------------------------------------
void Shot::Hit() {
	Remove();
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// 貫通弾
Through_Shot::Through_Shot() {
	m_w = 25;
	m_h = 10;
	m_s = 20;
	damage = 1;
	Set_hit_area(0, 0, m_w, m_h);
	Set_picture("Through_shot.png", Object_Type::THROUGH_SHOT);
	Set_sound("SHOT2.mp3", Sound_Type::THROUGH_SHOT);
}

//-------------------------------------------------------------------------------------
void Through_Shot::Move() {
	m_x += m_s;

	if (Game::Display_w < m_x + m_w) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void Through_Shot::Draw() {
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::THROUGH_SHOT);
}

//-------------------------------------------------------------------------------------
void Through_Shot::Hit() {
	// Remove();
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// 光線
Beam::Beam() {
	m_w = 0; // 伸長するため
	m_h = 80;
	m_s = 15;
	damage = 1;
	Set_hit_area(0, 0, m_w, m_h);
	Set_picture("Beam.png", Object_Type::BEAM);
	Set_sound("BEAM.mp3", Sound_Type::BEAM);
}

//-------------------------------------------------------------------------------------
void Beam::Move() {
	m_w += m_s;
	hit_w = m_w; // 横幅を当たり判定に追加

	if (Game::Display_w + 100 < (int)m_x + m_w) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void Beam::Draw() {
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::BEAM);
}

//-------------------------------------------------------------------------------------
void Beam::Hit() {
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// 渦巻弾
Swirl_Shot::Swirl_Shot() {
	m_w = 12;
	m_h = 12;
	damage = 10;
	radian = 0.0;
	r = 5.0; // 半径
	tmp = 0.0;
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
void Swirl_Shot::Set_position(const int position_x, const int position_y) {
	center_x = position_x;
	center_y = position_y;
}

//-------------------------------------------------------------------------------------
void Swirl_Shot::Move() {
	r += 2 - tmp; // 半径長の調整
	radian += 8 / r; // 角速度の調整

	// 三角関数の応用
	m_x = center_x - r * cos(radian);
	m_y = center_y - r * sin(radian);

	if (tmp < 1.5) {
		tmp += 0.05;
	}

	if (Game::Display_w < m_x) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void Swirl_Shot::Draw() {
	if (Game::Top < m_y && m_y + m_h < Game::Height) {
		DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 2.0, GetColor(0, 255, 0), TRUE);
	}
}

//-------------------------------------------------------------------------------------
void Swirl_Shot::Hit() {
	Remove();
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// N-way弾
N_way_Shot::N_way_Shot() {
	m_w = 12;
	m_h = 12;
	m_s = 8;
	damage = 5;
	radian = 0;
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
// 角度の取得
void N_way_Shot::Set_degree(const double d) {
	radian = Deg_to_rad(d);
}

//-------------------------------------------------------------------------------------
void N_way_Shot::Move() {
	// 三角関数の応用
	m_x += m_s * cos(radian);
	m_y += m_s * sin(radian);

	if (Game::Display_w <= m_x || m_y <= Game::Top || Game::Height <= m_y + m_h) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void N_way_Shot::Draw() {
	DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 2.0, GetColor(255, 0, 255), TRUE);
}

//-------------------------------------------------------------------------------------
void N_way_Shot::Hit() {
	Remove();
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// 3D渦巻弾
Swirl_3D_Shot::Swirl_3D_Shot() {
	m_w = 12;
	m_h = 12;
	m_s = 8;
	damage = 1;
	radian = 0;
	sign = 0;
	r = 50.0;
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
// 座標の取得
void Swirl_3D_Shot::Set_position(const int position_x, const int position_y) {
	m_x = position_x;
	center_y = position_y;
}

//-------------------------------------------------------------------------------------
// 符号の取得
void Swirl_3D_Shot::Set_sign(const int s) {
	sign = s;
}

//-------------------------------------------------------------------------------------
void Swirl_3D_Shot::Move() {
	radian += Deg_to_rad(10) / (r / 60.0);
	m_x += m_s / (1 + r / 100.0);
	m_y = center_y - sign * r * sin(radian); // サインカーブの応用

	if (Game::Display_w < (int)m_x) {
		Remove();
	}

	if ((int)r % 17 == 0) {
		m_w++;
		m_h++;
	}
	r += 0.5;
}

//-------------------------------------------------------------------------------------
void Swirl_3D_Shot::Draw() {
	double size = (1.5 - sign * cos(radian)) / 2.0;

	if (m_y + m_h < Game::Height && Game::Top < m_y) {
		DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w * size / 2.0, GetColor(240, 0, 240), TRUE);
	}
}

//-------------------------------------------------------------------------------------
void Swirl_3D_Shot::Hit() {
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// チャージ弾
Charge_Shot::Charge_Shot() {
	m_w = 0;
	m_h = 0;
	m_s = 15;
	damage = 0;
	deg = 0;
	charge_flag = false;

	Set_hit_area(0, 0, m_w, m_h);
	Set_picture("Charge_shot.png", Object_Type::CHARGE_SHOT);
	Set_sound("CHARGE.mp3", Sound_Type::CHARGE); // CHARGE 中の音
	Set_sound("CHARGE SHOT.mp3", Sound_Type::CHARGE_SHOT); // 発射音
}

//-------------------------------------------------------------------------------------
void Charge_Shot::Move() {
	if (!charge_flag) {
		if (CheckHitKey(KEY_INPUT_B)) {
			if (damage < 50) {
				damage++;
				m_y -= 2;
				m_w = 4 * damage; // 損害量に伴い拡大
				m_h = 4 * damage;

				// 当たり判定の誤差訂正
				hit_w = m_w;
				hit_h = m_h;

				// 画面内に収まる設計
				if (m_y < Game::Top || Game::Height < m_y + m_h) {
					charge_flag = true;
					game->Sound_stop(Sound_Type::CHARGE);
					game->Sound_play(Sound_Type::CHARGE_SHOT, effect_vol);
				}
			}

			// 50になる
			else {
				charge_flag = true;
				game->Sound_stop(Sound_Type::CHARGE);
				game->Sound_play(Sound_Type::CHARGE_SHOT, effect_vol);
			}
		}

		// 離す
		else {
			charge_flag = true;
			game->Sound_stop(Sound_Type::CHARGE);
			game->Sound_play(Sound_Type::CHARGE_SHOT, effect_vol);
		}
	}

	else {
		m_x += m_s;
	}

	if (Game::Display_w < m_x) {
		Remove();
	}
	deg += 20;
}

//-------------------------------------------------------------------------------------
void Charge_Shot::Draw() {
	int GrHandle = picture_array[static_cast<int>(Object_Type::CHARGE_SHOT)];
	DrawRotaGraph(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 360.0, deg * M_PI / 180, GrHandle, TRUE, FALSE);
}

//-------------------------------------------------------------------------------------
void Charge_Shot::Hit() {
	game->Sound_stop(Sound_Type::CHARGE);
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// 時限式弾
Timed_Shot::Timed_Shot() {
	m_w = 15;
	m_h = 15;
	m_s = 12;
	damage = 0;
	time = 30; // 発射までの時間
	shot_count = 1; // 弾数カウント用
	Set_hit_area(0, 0, m_w, m_h);
	Set_picture("Timed_shot.png", Object_Type::TIMED_SHOT);
	Set_sound("P ATTACK.mp3", Sound_Type::P_ATTACK);
}

//-------------------------------------------------------------------------------------
void Timed_Shot::Move() {
	const int max = 5; // 弾数

	if (0 <= time) {
		m_x += m_s; // 発射まで右方向へ
	}

	else {
		if (time % 10 == 0 && shot_count <= max) {

			for (int i = -1; i <= 1; i += 2) {
				// 上下方向
				Object_Pointer sub1(new Timed_Shot_Sub1());
				game->Add_list(sub1);
				sub1->Set_sign(i);
				sub1->Set_position(m_x + 1, m_y - 10 * i);

				// 左右方向
				Object_Pointer sub2(new Timed_Shot_Sub2());
				game->Add_list(sub2);
				sub2->Set_sign(i);
				sub2->Set_position(m_x - 9 - (5 * i), m_y + 2);
			}

			game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
			shot_count++;
		}

		if (max < shot_count) {
			Remove();
		}
	}
	time--;
}

//-------------------------------------------------------------------------------------
void Timed_Shot::Draw() {
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::TIMED_SHOT);
}

////====================================================================================
// 上下
Timed_Shot_Sub1::Timed_Shot_Sub1() {
	m_w = 12;
	m_h = 12;
	m_s = 15;
	damage = 5;
	sign = 0;
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
// 符号の取得
void Timed_Shot_Sub1::Set_sign(const int s) {
	sign = s;
}

//-------------------------------------------------------------------------------------
void Timed_Shot_Sub1::Move() {
	m_y += (double)sign * (double)m_s;

	if (m_y < 0 || Game::Display_h < m_y + m_h) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void Timed_Shot_Sub1::Draw() {
	if (Game::Top < m_y && m_y + m_h < Game::Height) {
		DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 2.0, GetColor(255, 150, 0), TRUE);
	}
}

//-------------------------------------------------------------------------------------
void Timed_Shot_Sub1::Hit() {
	Remove();
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// 左右
Timed_Shot_Sub2::Timed_Shot_Sub2() {
	m_w = 12;
	m_h = 12;
	m_s = 15;
	damage = 5;
	sign = 0;
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
void Timed_Shot_Sub2::Move() {
	m_x += (double)sign * (double)m_s;

	if (Game::Display_w < m_x || m_x + m_w < 0) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void Timed_Shot_Sub2::Draw() {
	DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 2.0, GetColor(255, 150, 0), TRUE);
}

//-------------------------------------------------------------------------------------
void Timed_Shot_Sub2::Hit() {
	Remove();
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// 追尾弾
Homing_Shot::Homing_Shot() {
	m_w = 12;
	m_h = 12;
	m_s = 10;
	damage = 20;
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
// 単位ベクトル計算
double Homing_Shot::Unit_vec(const double vec, const double vec_x, const double vec_y) {
	return vec / sqrt(vec_x * vec_x + vec_y * vec_y);
}

//-------------------------------------------------------------------------------------
// 一定速度
void Homing_Shot::Move() {
	if (0 < enemy_num) {
		m_x += Unit_vec(en_x - m_x, en_x - m_x, en_y - m_y) * m_s;
		m_y += Unit_vec(en_y - m_y, en_x - m_x, en_y - m_y) * m_s;
	}
	else {
		m_x += m_s; // 敵がいない場合は右方向へ
	}

	if (Game::Display_w < m_x) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void Homing_Shot::Draw() {
	DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 2.0, GetColor(0, 255, 0), TRUE);
}

//-------------------------------------------------------------------------------------
void Homing_Shot::Hit() {
	Remove();
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// 放物線弾
Parabola_Shot::Parabola_Shot() {
	m_w = 12;
	m_h = 12;
	damage = 50;
	m_s = 0;

	a = 0;
	b = 0;
	c = 0;

	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
// 行列式の計算
void Parabola_Shot::Det(const double(*mat)[3], double* det) {
	*det += mat[0][0] * mat[1][1] * mat[2][2];
	*det += mat[0][1] * mat[1][2] * mat[2][0];
	*det += mat[0][2] * mat[1][0] * mat[2][1];

	*det -= mat[0][0] * mat[1][2] * mat[2][1];
	*det -= mat[0][1] * mat[1][0] * mat[2][2];
	*det -= mat[0][2] * mat[1][1] * mat[2][0];
}

//-------------------------------------------------------------------------------------
// 座標の取得
void Parabola_Shot::Set_position(const int position_x, const int position_y) {
	center_x = position_x;
	center_y = position_y;

	double frame = (en_x - center_x) / (8 + enemy_s);

	double x1 = center_x;							// 発射座標
	double x2 = en_x - enemy_s * frame;				// 敵の座標
	double x3 = static_cast<double>(center_x) + 1;	// 任意の	座標

	double y1 = center_y;
	double y2 = en_y;
	double y3 = center_y - tan(Deg_to_rad(60)); // 45度

	// 行列
	double mat_A[3][3] = {
		{x1 * x1, x1, 1},
		{x2 * x2, x2, 1},
		{x3 * x3, x3, 1},
	};

	double mat_a[3][3] = {
		{y1, x1, 1},
		{y2, x2, 1},
		{y3, x3, 1},
	};

	double mat_b[3][3] = {
		{x1 * x1, y1, 1},
		{x2 * x2, y2, 1},
		{x3 * x3, y3, 1},
	};

	double mat_c[3][3] = {
		{x1 * x1, x1, y1},
		{x2 * x2, x2, y2},
		{x3 * x3, x3, y3},
	};

	double det_A = 0.0;
	double det_a = 0.0;
	double det_b = 0.0;
	double det_c = 0.0;

	Det(mat_A, &det_A);
	Det(mat_a, &det_a);
	Det(mat_b, &det_b);
	Det(mat_c, &det_c);

	// クラメルの行列式
	a = det_a / det_A;
	b = det_b / det_A;
	c = det_c / det_A;
}

//-------------------------------------------------------------------------------------
void Parabola_Shot::Move() {
	m_s += 8;
	m_x = center_x + m_s;
	m_y = a * (m_x * m_x) + b * m_x + c;
}

//-------------------------------------------------------------------------------------
void Parabola_Shot::Draw() {
	if (Game::Top < m_y && m_y + m_h < Game::Height) {
		DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 2.0, GetColor(255, 0, 0), TRUE);
	}
}

//-------------------------------------------------------------------------------------
void Parabola_Shot::Hit() {
	Remove();
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// 加速弾
Speed_Up_Shot::Speed_Up_Shot() {
	m_w = 12;
	m_h = 12;
	m_s = 1;
	damage = 5;
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
void Speed_Up_Shot::Move() {
	m_x += m_s * (acc / 2.0);
	acc++; // 加速度

	if (Game::Display_w < (int)m_x) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void Speed_Up_Shot::Draw() {
	DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 2.0, GetColor(0, 255, 0), TRUE);
}

//-------------------------------------------------------------------------------------
void Speed_Up_Shot::Hit() {
	Remove();
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// 多方向渦巻弾
Multi_Direct_Swirl_Shot::Multi_Direct_Swirl_Shot() {
	m_w = 12;
	m_h = 12;
	m_s = 3;
	damage = 3;
	radian = 0;
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
void Multi_Direct_Swirl_Shot::Set_degree(const double degree) {
	radian = Deg_to_rad(degree);
}

//-------------------------------------------------------------------------------------
void Multi_Direct_Swirl_Shot::Move() {
	m_x += m_s * cos(radian);
	m_y += m_s * sin(radian);

	if (Game::Display_w < m_x || m_x < 0 || m_y < Game::Top || Game::Height < m_y + m_h) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void Multi_Direct_Swirl_Shot::Draw() {
	DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 2.0, GetColor(0, 255, 0), TRUE);
}

//-------------------------------------------------------------------------------------
void Multi_Direct_Swirl_Shot::Hit() {
	Remove();
	game->Sound_play(Sound_Type::P_ATTACK, effect_vol);
}

//====================================================================================
// 爆破エフェクトの実装
Explosion::Explosion(const double x, const double y, const int w, const int h, const int s, bool boss_flag) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	size = s;
	damage = 0;
	flag = boss_flag;
	Set_picture("Explosion.png", Object_Type::BURN);
}

//-------------------------------------------------------------------------------------
void Explosion::Draw() {
	int x = m_x - 5 * size;
	int y = m_y - 5 * size;
	int w = m_x + (m_w - 30) + 5 * size;
	int h = m_y + m_h + 5 * size;

	My_DrawExtendGraph(x, y, w, h, Object_Type::BURN);

	if (size <= 0) {
		Remove(); // 削除

		// 通常の敵
		if (!flag) {
			game->Add_score(200); // スコア＋
		}

		// ボス
		else {
			game->scene = GAME_CLEAR; // クリア画面へ
			game->Sound_stop(Sound_Type::BOSS);
			game->Sound_loop_play(Sound_Type::GAME_CLEAR, bgm_vol);
		}
	}
}

//-------------------------------------------------------------------------------------
void Explosion::Move() {
	size--;
}

//====================================================================================
Enemy1::Enemy1() {
	m_w = 70;
	m_h = 35;

	// 速度設定
	if (game->stage <= 6) {
		m_s = 8;
	}
	else {
		m_s = 10;
	}

	hp_max = 10;
	hp_now = hp_max;
	damage = 1;
	energy = 0;
	up_down = 0;

	Set_hit_area(0, 0, m_w, m_h);
	Set_picture("Enemy1.png", Object_Type::ENEMY);
	Set_sound("BREAK.mp3", Sound_Type::BREAK);
	Set_range();
}

//-------------------------------------------------------------------------------------
void Enemy1::Move() {
	m_x -= m_s;

	// 画面左に入る場合
	if (m_x + m_w < 0) {
		Remove_func();
	}

	// 弾道実装用
	en_x = m_x;
	en_y = m_y;
	enemy_s = m_s;
}

//-------------------------------------------------------------------------------------
void Enemy1::Effect(bool boss_flag) {
	Object_Pointer explosion(new Explosion(m_x, m_y, m_w, m_h, 13, boss_flag));
	game->Add_list(explosion);
	game->Sound_play(Sound_Type::BREAK, effect_vol);
}

//-------------------------------------------------------------------------------------
// 画面外の削除処理
void Enemy1::Remove_func() {
	Remove();

	if (game->score < 20000 && 0 < game->score) {
		game->Add_score(-100);
	}

	if (0 < enemy_num) {
		enemy_num -= 1;
	}
}

//-------------------------------------------------------------------------------------
void Enemy1::Draw() {
	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, picture_array[static_cast<int>(Object_Type::ENEMY)], TRUE);
}

//-------------------------------------------------------------------------------------
void Enemy1::Hit(int damage, int energy) {
	hp_now -= damage;

	if (hp_now <= 0) {
		Effect(false); // 爆破エフェクトの実行
		Remove();

		if (0 < enemy_num) {
			enemy_num -= 1; // 敵数-1
		}
	}
}

//====================================================================================
Enemy2::Enemy2() {
	m_w = 70;
	m_h = 35;

	// 速度調整
	if (game->stage <= 3) {
		m_s = 3;
	}
	else if (4 <= game->stage && game->stage <= 9) {
		m_s = 4;
	}
	else if (game->stage == 10) {
		m_s = 5;
	}

	hp_max = 20;
	hp_now = hp_max;
	damage = 1;
	energy = 0;
	Set_hit_area(0, 0, m_w, m_h);

	Set_picture("Enemy2.png", Object_Type::ENEMY2);
	Set_range();
}

//-------------------------------------------------------------------------------------
void Enemy2::Move() {
	m_x -= m_s;
	en_x = m_x;
	en_y = m_y;
	enemy_s = m_s;

	if (m_x + m_w < 0) {
		Remove_func();
	}
}

//-------------------------------------------------------------------------------------
void Enemy2::Draw() {
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::ENEMY2);
}

//====================================================================================
// 壁反射
Enemy3::Enemy3() {
	m_w = 70;
	m_h = 35;

	// 速度設定
	if (game->stage <= 6) {
		m_s = 5;
	}
	else {
		m_s = 7;
	}

	hp_max = 10;
	hp_now = hp_max;
	damage = 1;
	energy = 0;
	up_down = 6; // 縦方向の速度

	Set_picture("Enemy3.png", Object_Type::ENEMY3);
	Set_hit_area(0, 0, m_w, m_h);
	Set_range();
}

//-------------------------------------------------------------------------------------
void Enemy3::Move() {
	m_x -= m_s;
	m_y += up_down; // 上下方向の速度

	// 上下の当たり判定
	// 上⇒下 or 下⇒上
	if (m_y < Game::Top || Game::Height < m_y + m_h) {
		up_down = -up_down;
	}

	if (m_x + m_w < 0) {
		Remove_func();
	}

	en_x = m_x;
	en_y = m_y;
	enemy_s = m_s;
}

//-------------------------------------------------------------------------------------
void Enemy3::Draw() {
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::ENEMY3);
}

//====================================================================================
// 高速
Enemy4::Enemy4() {
	m_w = 60;
	m_h = 35;
	m_s = 12;
	hp_max = 5;
	hp_now = hp_max;
	damage = 1;
	energy = 0;
	Set_picture("Enemy4.png", Object_Type::ENEMY4);
	Set_hit_area(0, 0, m_w, m_h);
	Set_range();
}

//-------------------------------------------------------------------------------------
void Enemy4::Move() {
	m_x -= m_s;
	en_x = m_x;
	en_y = m_y;
	enemy_s = m_s;

	if (m_x + m_w < 0) {
		Remove_func();
	}
}

//-------------------------------------------------------------------------------------
void Enemy4::Draw() {
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::ENEMY4);
}

//====================================================================================
Enemy5::Enemy5() {
	m_w = 70;
	m_h = 35;

	if (game->stage <= 6) {
		m_s = 4;
	}
	else {
		m_s = 5;
	}

	hp_max = 20;
	hp_now = hp_max;
	damage = 1;
	energy = 0;
	up_down = 6;

	Set_picture("Enemy5.png", Object_Type::ENEMY5);
	Set_hit_area(0, 0, m_w, m_h);
	Set_range();
}

//-------------------------------------------------------------------------------------
void Enemy5::Move() {
	// 一定の座標まで左移動
	if (1000 < m_x) {
		m_x -= m_s;
	}

	// 一定の座標で上下移動
	else {
		m_y -= up_down;

		// 当たり判定
		if (m_y < Game::Top || Game::Height < m_y + m_h) {
			up_down = -up_down;
		}

		if (GetRand(60) == 0) {
			Object_Pointer enemy_shot(new Enemy_Shot(12, 1));
			enemy_shot->Set_position(m_x - 10, m_y + 25); // 座標
			game->Add_list(enemy_shot);
			game->Sound_play(Sound_Type::ENEMY_SHOT, effect_vol);
		}
	}

	en_x = m_x;
	en_y = m_y;
	enemy_s = m_s;
}

//-------------------------------------------------------------------------------------
void Enemy5::Draw() {
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::ENEMY5);
}

//====================================================================================
Enemy6::Enemy6() {
	m_w = 70;
	m_h = 35;

	if (game->stage <= 6) {
		m_s = 5;
	}
	else {
		m_s = 7;
	}

	hp_max = 20;
	hp_now = hp_max;
	damage = 1;
	energy = 0;
	up_down = 6;

	Set_picture("Enemy6.png", Object_Type::ENEMY6);
	Set_hit_area(0, 0, m_w, m_h);
	Set_range();
}

//-------------------------------------------------------------------------------------
void Enemy6::Move() {
	m_x -= m_s;
	m_y -= up_down;

	// 画面の当たり判定
	if (m_y < Game::Top || Game::Height < m_y + m_h) {
		up_down = -up_down;
	}

	if (m_x < 0) {
		m_s = -2; // 左
	}

	if (Game::Display_w + 200 < m_x + m_w) {
		Remove_func();
	}

	if (GetRand(60) == 0) {
		Object_Pointer enemy_shot(new Enemy_Shot(12, 1));
		enemy_shot->Set_position(m_x - 10, m_y + 25);
		game->Add_list(enemy_shot);
		game->Sound_play(Sound_Type::ENEMY_SHOT, effect_vol);
	}

	en_x = m_x;
	en_y = m_y;
	enemy_s = m_s;
}

//-------------------------------------------------------------------------------------
void Enemy6::Draw() {
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::ENEMY6);
}

//====================================================================================
Enemy_Boss1::Enemy_Boss1() {
	// 体力設定
	switch (game->stage) {
	case 1:
		hp_max = 5000;
		break;
	case 2:
		hp_max = 5500;
		break;
	case 3:
		hp_max = 6000;
		break;
	case 4:
		hp_max = 6500;
		break;
	case 5:
		hp_max = 7000;
		break;
	case 6:
		hp_max = 7500;
		break;
	case 7:
		hp_max = 8000;
		break;
	case 8:
		hp_max = 8500;
		break;
	case 9:
		hp_max = 9000;
		break;
	}

	m_w = 210;
	m_h = 250;
	hp_now = hp_max;
	damage = 1;
	energy = 0;
	up_down = 1;	// 上下向き速度
	add_speed = 2;
	shot_count = 0;
	time = 0;
	tmp = 0;
	deg = 0;
	sign = 1;
	time_flag = false;
	sound_flag = false;

	Set_picture("Enemy_boss1.png", Object_Type::ENEMY_BOSS1);
	Set_picture("Enemy_boss2.png", Object_Type::ENEMY_BOSS2);
	Set_picture("Enemy_boss3.png", Object_Type::ENEMY_BOSS3);
	Set_hit_area(50, 20, m_w, m_h - 20); // 当たり判定の設定
	Set_position(Game::Display_w, 150);
}

//-------------------------------------------------------------------------------------
void Enemy_Boss1::Set_shot_type(const int num) {
	int size = 20; // 弾のサイズ

	switch (num) {
	case N_WAY_1:
		// N-way弾
		for (int i = 1; i <= 7; i++) {
			Object_Pointer enemy_shot(new Enemy_Shot(18, num));
			enemy_shot->Set_position(m_x - 10, m_y + m_h / 2.0 - 15);
			enemy_shot->Set_degree((3.0 - i) * 10.0);
			game->Add_list(enemy_shot);
		}
		break;

	case NORMAL:
		// 通常弾
		for (int i = 1; i <= 2; i++) {
			Object_Pointer enemy_shot(new Enemy_Shot(size + 10, num));
			enemy_shot->Set_position(m_x + 40, m_y + m_h / 2.0 - 240 + i * 150);
			game->Add_list(enemy_shot);
		}
		break;

	case MULTI_DIRECT_SWIRL:
		// 多方向渦巻弾
		for (int i = 0; i < 6; i++) {
			Object_Pointer shot(new Enemy_Shot(size, num));
			shot->Set_degree(deg + i * (360.0 / 6.0));
			shot->Set_position(m_x - 10, m_y + m_h / 2.0 - 15);
			game->Add_list(shot);
		}
		break;
	}

	deg += sign * 11;

	if (360 < deg || deg < 0) {
		sign = -sign;
	}
}

//-------------------------------------------------------------------------------------
void Enemy_Boss1::Move() {
	// 体力半分以下の場合　速度を上昇
	if (hp_now < hp_max / 2) {
		if (up_down < 0) {
			up_down = -3;
		}
		else {
			up_down = 3;
		}
	}

	// 一定の座標まで左方向
	if (920 < m_x) {
		m_x -= 1;
	}
	// 上下方向
	else {
		if (!sound_flag) {
			sound_flag = true;
			game->Sound_loop_play(Sound_Type::BOSS, bgm_vol); // ボスバトル用の音楽の再生
		}

		if (!time_flag) {
			time = GetNowCount(); // 10秒計測用
			tmp = GetRand(TYPE_NUM - 1);
			time_flag = true;
		}
		// 10秒経過で弾道変更
		if (5 < (GetNowCount() - time) / 1000) {
			time_flag = false;
		}

		if (tmp != MULTI_DIRECT_SWIRL) {
			m_y += up_down;
		}

		// 画面の当たり判定
		if ((int)m_y < Game::Top || Game::Height < (int)m_y + m_h) {
			up_down = -up_down;
		}

		if (shot_count % 6 == 0) {
			Set_shot_type(tmp);
			game->Sound_play(Sound_Type::ENEMY_SHOT, effect_vol);
		}
	}

	if (360 < shot_count) {
		shot_count = 0;
	}
	shot_count++;
}

//-------------------------------------------------------------------------------------
void Enemy_Boss1::Draw_hp() {
	unsigned int color = GetColor(50, 205, 50);	// RGB値

	if (hp_now < hp_max / 2) {
		color = GetColor(220, 200, 0);
	}
	if (hp_now < hp_max / 4) {
		color = GetColor(255, 0, 0);
	}

	const int x1 = Game::Display_w - 300; // 基準の座標
	const int w1 = 240; // 横幅
	const int space = 3; // 間隔

	// ライフの描画
	DrawBox(x1, 5, x1 + w1, Game::Top - 5, GetColor(200, 200, 200), TRUE);

	const int x2 = x1 + space;

	DrawBox(x2, 8, x1 + w1 - space, Game::Top - 8, GetColor(50, 50, 50), TRUE);
	DrawBoxAA(x2, 8, x2 + (w1 - 2 * space) * (hp_now / (float)hp_max), Game::Top - 8, color, TRUE);
}

//-------------------------------------------------------------------------------------
void Enemy_Boss1::Draw() {
	Object_Type ot = Object_Type::NONE;

	if (game->stage <= 3) {
		ot = Object_Type::ENEMY_BOSS1;
	}
	else if (4 <= game->stage && game->stage <= 6) {
		ot = Object_Type::ENEMY_BOSS2;
	}
	else {
		ot = Object_Type::ENEMY_BOSS3;
	}

	Draw_hp();
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, ot);
}

//-------------------------------------------------------------------------------------
void Enemy_Boss1::Hit(int damage, int energy) {
	hp_now -= damage;

	if (hp_now <= 0) {
		Effect(true);
		game->Sound_play(Sound_Type::BREAK, effect_vol);
		Remove();
	}
}

//====================================================================================
Enemy_Boss2::Enemy_Boss2() {
	m_w = 370;
	m_h = 350;
	hp_max = 10000;
	hp_now = hp_max;
	damage = 1;
	energy = 0;
	up_down = 1;
	add_speed = 0;
	shot_count = 0;
	time = 0;
	tmp = 0;
	deg = 0;
	time_flag = false;
	Set_picture("Enemy_boss4.png", Object_Type::ENEMY_BOSS4);
	Set_hit_area(150, 50, 350, 300);
	Set_position(Game::Display_w, 140);
}

//-------------------------------------------------------------------------------------
void Enemy_Boss2::Move() {
	// 体力半分以下の場合　速度を上昇
	if (hp_now < hp_max / 2) {
		if (up_down < 0) {
			up_down = -5;
		}
		else {
			up_down = 5;
		}
	}

	// 一定の座標まで左方向
	if (920 < m_x) {
		m_x -= 1;
	}
	// 上下方向
	else {
		if (!sound_flag) {
			sound_flag = true;
			game->Sound_loop_play(Sound_Type::BOSS, bgm_vol); // ボスバトル用の音楽の再生
		}

		if (!time_flag) {
			time = GetNowCount(); // 10秒計測用
			tmp = GetRand(TYPE_NUM - 1);
			time_flag = true;
		}
		// 10秒経過で弾道変更
		if (5 < (GetNowCount() - time) / 1000) {
			time_flag = false;
		}

		if (tmp != MULTI_DIRECT_SWIRL) {
			m_y += up_down;
		}

		// 画面の当たり判定
		if ((int)m_y < Game::Top || Game::Height < (int)m_y + m_h) {
			up_down = -up_down;
		}

		if (shot_count % 6 == 0) {
			Set_shot_type(tmp);
			game->Sound_play(Sound_Type::ENEMY_SHOT, effect_vol);
		}
	}

	if (360 < shot_count) {
		shot_count = 0;
	}
	shot_count++;
}

//-------------------------------------------------------------------------------------
void Enemy_Boss2::Draw() {
	Draw_hp();
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::ENEMY_BOSS4);
}

//====================================================================================
Enemy_Shot::Enemy_Shot(const int size, const int num) {
	m_w = m_h = size;
	type_num = num;
	radian = 0.0;
	rad = 0.0;
	center_x = 0.0;
	center_y = 0.0;
	sign = 1;

	// 速度設定
	if (game->stage <= 3) {
		m_s = 8;
	}
	else if (4 <= game->stage && game->stage <= 6) {
		m_s = 10;
	}
	else if (7 <= game->stage && game->stage <= 9) {
		m_s = 12;
	}
	else {
		m_s = 14;
	}

	damage = 1;
	energy = 0;

	Set_sound("ENEMY SHOT.mp3", Sound_Type::ENEMY_SHOT);
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
// 角度の取得
void Enemy_Shot::Set_degree(const double degree) {
	radian = Deg_to_rad(degree);;
}

//-------------------------------------------------------------------------------------
void Enemy_Shot::Set_position2(const int position_x, const int position_y) {
	center_x = position_x;
	center_y = position_y;
}

//-------------------------------------------------------------------------------------
void Enemy_Shot::Move() {
	switch (type_num) {
	case N_WAY_1:
		m_x -= m_s * cos(radian);
		m_y -= m_s * sin(radian);
		break;

	case NORMAL:
		m_x -= m_s;
		break;

	case MULTI_DIRECT_SWIRL:
		m_x -= m_s * cos(radian);
		m_y -= m_s * sin(radian);
		break;
	}

	if (m_x + m_w < 0 || m_y <= Game::Top || Game::Height <= m_y + m_h) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void Enemy_Shot::Draw() {
	unsigned int color = GetColor(0, 180, 255);

	if (4 <= game->stage && game->stage <= 6) {
		color = GetColor(255, 0, 0); // 赤
	}
	else if (7 <= game->stage && game->stage <= 9) {
		color = GetColor(0, 255, 0); // 緑
	}
	else if (game->stage == 10) {
		color = GetColor(200, 200, 200); // 灰
	}

	DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 2.0, color, TRUE);
}

//-------------------------------------------------------------------------------------
void Enemy_Shot::Hit() {
	Remove();
	game->Sound_play(Sound_Type::ENEMY_SHOT, effect_vol);
}

//====================================================================================
// 体力回復
Heal1::Heal1() {
	m_w = 20;
	m_h = 25;
	m_s = 6;
	damage = -1;
	energy = 0;
	Set_picture("Heal1.png", Object_Type::HEAL1);
	Set_sound("HEAL.mp3", Sound_Type::HEAL);
	Set_hit_area(0, 0, m_w, m_h);
	Set_range();
}

//-------------------------------------------------------------------------------------
void Heal1::Move() {
	m_x -= m_s;

	if (m_x + m_w < 0) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void Heal1::Draw() {
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::HEAL1);
}

//-------------------------------------------------------------------------------------
void Heal1::Hit() {
	Remove();
	game->Sound_play(Sound_Type::HEAL, effect_vol);
}

//====================================================================================
// 特殊量回復
Heal2::Heal2() {
	m_w = 20;
	m_h = 25;
	m_s = 10;
	damage = 0;
	energy = -1;
	Set_picture("Heal2.png", Object_Type::HEAL2);
	Set_hit_area(0, 0, m_w, m_h);
	Set_range();
}

//-------------------------------------------------------------------------------------
void Heal2::Draw() {
	My_DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, Object_Type::HEAL2);
}

//-------------------------------------------------------------------------------------
void Heal2::Move() {
	m_x -= m_s;

	if (m_x + m_w < 0) {
		Remove();
	}
}

//-------------------------------------------------------------------------------------
void Heal2::Hit() {
	Remove();
	game->Sound_play(Sound_Type::HEAL, effect_vol);
}

//====================================================================================
Mob::Mob() {
	m_w = 3;
	m_h = 3;
	Reset_position(true);
}

//-------------------------------------------------------------------------------------
void Mob::Reset_position(const bool i) {
	int cx = GetRand(Game::Display_w); // 左右はみ出しを可とする
	tmp = GetRand(Game::Height);

	// 完全バラバラ配置
	if (i) {
		if (tmp < Game::Top) {
			Set_position(cx, Game::Top);
		}
		else if (Game::Height - m_h < tmp) {
			Set_position(cx, Game::Height - m_h);
		}
		else {
			Set_position(cx, tmp);
		}
	}

	// 敵と同じ仕組み
	else {
		Set_range();
	}

	// 速度設定
	m_s = GetRand(4) + 1;
}

//-------------------------------------------------------------------------------------
void Mob::Move() {
	if (game->boss_flag) {
		m_x -= ((double)m_s + 15.0);
	}
	else {
		m_x -= m_s;
	}

	if (m_x < m_w) {
		Reset_position(false); // 削除ではなく繰り返し配置
	}
}

void Mob::Draw() {
	DrawBox(m_x, m_y, m_x + m_w, m_y + m_h, GetColor(255, 255, 255), TRUE);
}

//====================================================================================
Game::Game() {
	high_score = 0;
	now_score = 0;
	limit_time = 0;
	now_time = 0;
	start_time = 0;
	pause_time = 0;
	stop_time = 0;
	scene = TITLE;
	stage = 1;
	push_flag = false;
	boss_flag = false;
	play_flag = false;
	space_flag = false;
	num_flag = false;
	name_flag = false;
	pause_flag = false;
}

//------------------------------------------------------------------------------------
// 効果音出力
void Game::Sound_play(const Sound_Type st, const int volume) {
	ChangeVolumeSoundMem(volume, sound_array[static_cast<int>(st)]); // 音量調整
	PlaySoundMem(sound_array[static_cast<int>(st)], DX_PLAYTYPE_BACK);
}

//------------------------------------------------------------------------------------
// ループBGM出力
void Game::Sound_loop_play(const Sound_Type s, const int volume) {
	ChangeVolumeSoundMem(volume, sound_array[static_cast<int>(s)]); // 音量調整
	PlaySoundMem(sound_array[static_cast<int>(s)], DX_PLAYTYPE_LOOP);
}

//------------------------------------------------------------------------------------
// 再生停止
void Game::Sound_stop(const Sound_Type st) {
	StopSoundMem(sound_array[static_cast<int>(st)]);
}

//------------------------------------------------------------------------------------
// リストへ追加
void Game::Add_list(Object_Pointer& op) {
	objects_list.push_back(op);
}

//------------------------------------------------------------------------------------
// スコアの追加
void Game::Add_score(const int s) {
	score += s;
}

//------------------------------------------------------------------------------------
bool Game::Push_space() {
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (!push_flag) {
			push_flag = true;
			return true;
		}
	}
	else {
		push_flag = false;
	}
	return false;
}

//------------------------------------------------------------------------------------
bool Game::Push_back() {
	if (CheckHitKey(KEY_INPUT_BACK)) {
		if (!push_flag) {
			push_flag = true;
			return true;
		}
	}
	else {
		push_flag = false;
	}
	return false;
}

//------------------------------------------------------------------------------------
void Game::Check_database() {
	sqlite3* db = NULL;

	// DBファイルの開閉
	int con = sqlite3_open(file_name, &db);

	// エラー処理
	if (con != SQLITE_OK) {
		scene = ER;
	}

	// テーブル作成(存在しない場合のみ)
	con = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Users(name text primary key, score integer)", NULL, NULL, NULL);
	sqlite3_close(db);
}

//------------------------------------------------------------------------------------
// データベースへ名前を保存
void Game::Add_name_to_database() {
	char SQL1[100];
	char SQL2[100];
	sqlite3* db = NULL;
	sqlite3_stmt* res = NULL;

	// DBファイルの開閉
	int con = sqlite3_open(file_name, &db);

	// エラー処理
	if (con != SQLITE_OK) {
		scene = ER;
	}

	// ユーザの検索
	sprintf_s(SQL1, "SELECT COUNT(*) FROM Users WHERE name = \'%s\'", name_data);
	con = sqlite3_prepare_v2(db, SQL1, -1, &res, NULL); // 命令実行
	con = sqlite3_step(res);

	// 新規の名前の場合
	if (sqlite3_column_int(res, 0) == 0) {
		sprintf_s(SQL2, "INSERT INTO Users(name) values(\'%s\')", name_data);	// 文字列の生成
		con = sqlite3_exec(db, SQL2, NULL, NULL, NULL);							// 命令実行
	}
	sqlite3_finalize(res);
	sqlite3_close_v2(db);
}

//------------------------------------------------------------------------------------
// データベースへスコア保存
void Game::Add_score_to_database(const int s) {
	char SQL[100];
	sqlite3* db = NULL;

	// DBファイルの開閉
	int con = sqlite3_open(file_name, &db);

	// エラー回避
	if (con != SQLITE_OK) {
		scene = ER;
	}

	// スコアの上書き
	sprintf_s(SQL, "UPDATE Users SET score = %d WHERE name = \'%s\'", s, name_data);
	con = sqlite3_exec(db, SQL, NULL, NULL, NULL);

	// エラー回避
	if (con != SQLITE_OK) {
		scene = ER;
	}
	// ファイルを閉じる
	sqlite3_close(db);
}

//------------------------------------------------------------------------------------
// 順位表示
void Game::Show_ranking_from_database() {
	sqlite3* db = NULL;
	sqlite3_stmt* res = NULL;

	// DBファイルの開閉
	int con = sqlite3_open(file_name, &db);

	// データの抽出 (降順)
	con = sqlite3_prepare_v2(db, "SELECT * FROM Users ORDER BY score DESC", -1, &res, NULL);

	// 文字サイズ
	SetFontSize(25);

	for (int i = 0; SQLITE_ROW == (con = sqlite3_step(res)) && i < 10; i++) {
		const int x = 350; // 基準x座標
		const int y = 200 + i * 30; // 基準y座標
		unsigned int color = GetColor(255, 255, 255); // RGB値
		char buf[50]; // 文字列格納用

		if (i + 1 < 10) {
			sprintf_s(buf, " %d %s", i + 1, sqlite3_column_text(res, 0));
		}
		else {
			sprintf_s(buf, "%d %s", i + 1, sqlite3_column_text(res, 0));
		}

		// 順位+名前表示
		DrawString(x, y, buf, color);

		// スコア取得
		const int ones_score = sqlite3_column_int(res, 1);

		// 桁合わせ
		if (ones_score < 1000) {
			sprintf_s(buf, "   %d", ones_score);
		}
		else if (ones_score < 10000) {
			sprintf_s(buf, "  %d", ones_score);
		}
		else if (ones_score < 100000) {
			sprintf_s(buf, " %d", ones_score);
		}
		else {
			sprintf_s(buf, "%d", ones_score);
		}
		DrawString(x + 400, y, buf, color); // スコア表示
	}

	// ファイルを閉じる
	sqlite3_finalize(res);
	sqlite3_close_v2(db);
}

//------------------------------------------------------------------------------------
// ユーザのスコア取得
int Game::Get_score() {
	int result = 0;
	char SQL[100];
	sqlite3* db = NULL;
	sqlite3_stmt* res = NULL;

	// DBファイルの開閉
	int con = sqlite3_open(file_name, &db);

	sprintf_s(SQL, "SELECT * FROM Users WHERE name = \'%s\'", name_data);

	con = sqlite3_prepare_v2(db, SQL, -1, &res, NULL);
	// エラー処理
	if (con != SQLITE_OK) {
		scene = ER;
	}

	con = sqlite3_step(res);
	result = sqlite3_column_int(res, 1); // スコア取得

	// ファイルを閉じる
	sqlite3_finalize(res);
	sqlite3_close_v2(db);
	return result;
}

//------------------------------------------------------------------------------------
// 敵の生成
void Game::Enemy_Form(const int x) {
	Object_Pointer enemy;

	switch (x) {
	case 1:
		enemy.reset(new Enemy1);
		break;
	case 2:
		enemy.reset(new Enemy2);
		break;
	case 3:
		enemy.reset(new Enemy3);
		break;
	case 4:
		enemy.reset(new Enemy4);
		break;
	case 5:
		enemy.reset(new Enemy5);
		break;
	case 6:
		enemy.reset(new Enemy6);
		break;
	default:
		// エラー処理
		enemy.reset(new Enemy1);
		break;
	}

	Add_list(enemy);

	if (0 <= enemy_num) {
		enemy_num += 1; // 敵数+1
	}
}

//------------------------------------------------------------------------------------
void Game::Draw_numbers(const int num, const int x, const int y, const int w, const int h) {
	const int interval = 3; // 文字同士の間隔

	if (0 < num) {
		const int digits_num = (int)log10(num); // 桁数

		for (int i = (int)pow(10, digits_num), j = 0; 0 < i; i /= 10, j += (w + interval)) {
			Object_Type ot;
			switch ((num / i) % 10) {
			case 0:
				ot = Object_Type::_0_;
				break;
			case 1:
				ot = Object_Type::_1_;
				break;
			case 2:
				ot = Object_Type::_2_;
				break;
			case 3:
				ot = Object_Type::_3_;
				break;
			case 4:
				ot = Object_Type::_4_;
				break;
			case 5:
				ot = Object_Type::_5_;
				break;
			case 6:
				ot = Object_Type::_6_;
				break;
			case 7:
				ot = Object_Type::_7_;
				break;
			case 8:
				ot = Object_Type::_8_;
				break;
			case 9:
				ot = Object_Type::_9_;
				break;
			default:
				ot = Object_Type::_0_;
				break;
			}
			My_DrawExtendGraph(x + j, y, x + w + j, y + h, ot);
		}
	}
	else {
		My_DrawExtendGraph(x, y, x + w, y + h, Object_Type::_0_);
	}
}

//------------------------------------------------------------------------------------
void Game::Game_set() {
	game = this;		// 自インスタンスのアドレスを保持（静的）
	scene = TITLE;		// タイトルへ

	ChangeWindowMode(TRUE); // ウィンドウを開く
	SetGraphMode(Display_w, Display_h, 32); // ウィンドウの横幅, 縦幅, カラー設定
	DxLib_Init(); // DXライブラリの初期化
	SetDrawScreen(DX_SCREEN_BACK); // ウラに画像を描画
	Check_database(); // データベースの確認

	Set_picture("Clock.png", Object_Type::CLOCK);
	Set_picture("Left.png", Object_Type::LEFT);
	Set_picture("Right.png", Object_Type::RIGHT);
	Set_picture("Fonts/Title.png", Object_Type::TITLE);
	Set_picture("Fonts/Stage_select.png", Object_Type::STAGE_SELECT);
	Set_picture("Fonts/Game_over.png", Object_Type::GAME_OVER);
	Set_picture("Fonts/Game_clear.png", Object_Type::GAME_CLEAR);
	Set_picture("Fonts/Push_space.png", Object_Type::PUSH_SPACE);
	Set_picture("Fonts/Pause.png", Object_Type::PAUSE);
	Set_picture("Fonts/Pause_menu.png", Object_Type::PAUSE_MENU);
	Set_picture("Fonts/Esc.png", Object_Type::ESC);
	Set_picture("Fonts/Restart.png", Object_Type::RESTART);
	Set_picture("Fonts/Warning.png", Object_Type::WARNING);
	Set_picture("Fonts/Score.png", Object_Type::SCORE);
	Set_picture("Fonts/Back_space.png", Object_Type::BACK_SPACE);
	Set_picture("Fonts/Please_enter.png", Object_Type::PLEASE_ENTER);
	Set_picture("Fonts/Ranking.png", Object_Type::RANKING);
	Set_picture("Fonts/Score_ranking.png", Object_Type::RANKING_LIST);

	Set_picture("Numbers/0.png", Object_Type::_0_);
	Set_picture("Numbers/1.png", Object_Type::_1_);
	Set_picture("Numbers/2.png", Object_Type::_2_);
	Set_picture("Numbers/3.png", Object_Type::_3_);
	Set_picture("Numbers/4.png", Object_Type::_4_);
	Set_picture("Numbers/5.png", Object_Type::_5_);
	Set_picture("Numbers/6.png", Object_Type::_6_);
	Set_picture("Numbers/7.png", Object_Type::_7_);
	Set_picture("Numbers/8.png", Object_Type::_8_);
	Set_picture("Numbers/9.png", Object_Type::_9_);

	// 音楽ファイルのロード
	Set_sound("TITLE.mp3", Sound_Type::TITLE);
	Set_sound("GAME PLAY.mp3", Sound_Type::GAME_PLAY);
	Set_sound("GAME OVER.mp3", Sound_Type::GAME_OVER);
	Set_sound("GAME CLEAR.mp3", Sound_Type::GAME_CLEAR);
	Set_sound("PAUSE.mp3", Sound_Type::PAUSE);
	Set_sound("BOSS GAME.mp3", Sound_Type::BOSS);
	Set_sound("change.mp3", Sound_Type::SWITCH);
	Set_sound("Command.wav", Sound_Type::COMMAND);
	Set_sound("Alert.wav", Sound_Type::ALERT);

	Sound_loop_play(Sound_Type::TITLE, bgm_vol);
}

//------------------------------------------------------------------------------------
// イベント処理の実装
void Game::Game_all() {
	while (!ProcessMessage()) {
		ClearDrawScreen();
		switch (scene) {
		case TITLE:
			Game_title();
			break;
		case ACCOUNT:
			Game_Account();
			break;
		case RANKING:
			Game_ranking();
			break;
		case SELECT:
			Game_select();
			break;
		case PLAY:
			Game_play();
			break;
		case GAME_OVER:
			Game_over();
			break;
		case GAME_CLEAR:
			Game_clear();
			break;
		case ER:
			// エラー画面
			Error_screen();
			break;
		}
		ScreenFlip();
	}
}

//------------------------------------------------------------------------------------
void Game::Game_title() {
	objects_list.clear();
	score = 0;
	stage = 1;
	enemy_num = 0;
	limit_time = 600; // 制限時間
	play_flag = false;
	boss_flag = false;
	space_flag = false;
	num_flag = false;
	pause_flag = false;
	debug_flag = false;	// デバッグするか否か

	if (Push_space()) {
		if (!name_flag) {
			scene = ACCOUNT;
		}
		else {
			scene = SELECT;
		}

		Sound_play(Sound_Type::COMMAND, 230);
	}

	// 順位表へ
	else if (CheckHitKey(KEY_INPUT_BACK)) {
		scene = RANKING;
		Sound_play(Sound_Type::COMMAND, 230);
	}

	My_DrawExtendGraph(10, 250, Display_w - 10, Display_h - 250, Object_Type::TITLE);
	My_DrawExtendGraph(300, Display_h - 80, Display_w - 300, Display_h - 30, Object_Type::PUSH_SPACE);
	My_DrawExtendGraph(Display_w - (Display_w / 4) + 15, 15, Display_w - 15, 15 + 25, Object_Type::BACK_SPACE);
	My_DrawExtendGraph(Display_w - (Display_w / 4) + 15, 50, Display_w - 15, 50 + 40, Object_Type::RANKING);
}

//------------------------------------------------------------------------------------
// ユーザ登録
void Game::Game_Account() {
	const int x = 270;
	const int y = 300;

	My_DrawExtendGraph(50, 150, Display_w - 50, 150 + 50, Object_Type::PLEASE_ENTER);
	DrawBox(x, y, Display_w - x, y + 75, GetColor(255, 255, 255), FALSE);

	// 名前の入力
	SetFontSize(60);
	KeyInputSingleCharString(x + 10, y + 10, name_size, name_data, FALSE);

	// Enter
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		scene = SELECT;
		Sound_play(Sound_Type::COMMAND, 230);
		name_flag = true;
		Add_name_to_database();
	}
}

//------------------------------------------------------------------------------------
// 順位表示
void Game::Game_ranking() {
	My_DrawExtendGraph(100, 70, Display_w - 100, 70 + 80, Object_Type::RANKING_LIST);
	My_DrawExtendGraph(300, Display_h - 80, Display_w - 300, Display_h - 30, Object_Type::PUSH_SPACE);
	Show_ranking_from_database();

	if (Push_space()) {
		scene = TITLE;
		Sound_play(Sound_Type::COMMAND, 230);
	}
}

//------------------------------------------------------------------------------------
void Game::Switch_stage() {
	if (CheckHitKey(KEY_INPUT_N)) {
		if (!num_flag) {
			num_flag = true;
			Sound_play(Sound_Type::SWITCH, effect_vol);
			if (stage != 10) {
				stage++;
			}
		}
	}
	else if (CheckHitKey(KEY_INPUT_V)) {
		if (!num_flag) {
			num_flag = true;
			Sound_play(Sound_Type::SWITCH, effect_vol);
			if (stage != 1) {
				stage--;
			}
		}
	}
	else {
		num_flag = false;
	}
}

//-------------------------------------------------------------------------------------
void Game::Game_select() {
	const int y = Display_h - 250;
	int size = 40;

	My_DrawExtendGraph(50, 150, Display_w - 50, 150 + 80, Object_Type::STAGE_SELECT);
	My_DrawExtendGraph(300, Display_h - 80, Display_w - 300, Display_h - 30, Object_Type::PUSH_SPACE);
	Draw_numbers(Get_score(), 10, 10, 20, 20);
	Switch_stage();
	Draw_numbers(stage, (Display_w / 2) - (size / 2), y, size, size);

	if (stage != 1) {
		My_DrawExtendGraph(400, y, 550, y + size, Object_Type::LEFT);
	}

	if (stage != 10) {
		My_DrawExtendGraph(650, y, 800, y + size, Object_Type::RIGHT);
	}

	if (Push_space()) {
		scene = PLAY;
		Sound_play(Sound_Type::COMMAND, 230);

		for (int i = 0; i < 50; i++) {
			Object_Pointer cloud(new Mob);
			Add_list(cloud);
		}

		Object_Pointer player(new Player);
		Add_list(player);

		// デバッグ時
		if (debug_flag == true) {
			Sound_stop(Sound_Type::TITLE);	// BGMを消す
		}
	}
}

//-------------------------------------------------------------------------------------
void Game::Game_play() {
	// UI用
	DrawBox(0, 0, Display_w, Top, GetColor(75, 75, 75), TRUE); // 上部分
	DrawBox(0, Height, Display_w, Display_h, GetColor(75, 75, 75), TRUE); // 下部分

	// リストに入る全てのインスタンスに適用
	if (!pause_flag) {
		for_each(objects_list.begin(), objects_list.end(), [](Object_Pointer& object) {object->Move(); });
		for_each(objects_list.begin(), objects_list.end(), [&](Object_Pointer& oneself) {

			if (oneself->Hit_type() == Object_Type::NONE) return;

			for_each(objects_list.begin(), objects_list.end(), [&](Object_Pointer& opponent) {
				// タイプが一致する場合
				if (oneself->Hit_type() == opponent->Get_type()) {
					// 当たる場合
					if (oneself->Hit_test(opponent)) {
						oneself->Hit(opponent->Get_damage(), opponent->Get_energy());
						oneself->Hit();
						opponent->Hit(oneself->Get_damage(), oneself->Get_energy());
					}
				}
				});
			});
	}

	for_each(objects_list.begin(), objects_list.end(), [](Object_Pointer& object) {object->Draw(); });

	// プレイ前
	if (!play_flag) {
		if (CheckHitKey(KEY_INPUT_B)) {
			space_flag = true;
		}

		if (space_flag && ! debug_flag) {
			My_DrawExtendGraph(300, Display_h - 80, Display_w - 300, Display_h - 30, Object_Type::PUSH_SPACE);
		}

		// スタート
		if (Push_space()) {
			if (!debug_flag) {
				Sound_stop(Sound_Type::TITLE); // タイトル画面の音を停止
				Sound_loop_play(Sound_Type::GAME_PLAY, bgm_vol); // プレイ画面の音を再生
			}
			start_time = GetNowCount(); // 制限時間の計測
			play_flag = true;
		}
	}

	// プレイ中の場合
	else {
		int x = Display_w - 180;

		// 制限時間の表示
		DrawBox(x + 10, Height + 5, (x + 10) + 105, Display_h - 5, GetColor(50, 50, 50), TRUE);
		Draw_numbers(now_time, x + 45, Height + 10, 18, 20);

		// 時計画像
		My_DrawExtendGraph(x, Height + 5, x + 30, Display_h - 5, Object_Type::CLOCK);

		if (!pause_flag) {
			// 制限時間の計算
			now_time = (start_time - GetNowCount()) / 1000 + limit_time;

			if (score < 20000) { // 敵の生成(各ステージ設定)
				switch (stage) {
				case 1:
					if (GetRand(40) == 0) Enemy_Form(1);
					if (GetRand(80) == 0) Enemy_Form(2);
					break;
				case 2:
					if (GetRand(40) == 0) Enemy_Form(1);
					if (GetRand(80) == 0) Enemy_Form(2);
					if (GetRand(100) == 0) Enemy_Form(3);
					break;
				case 3:
					if (GetRand(40) == 0) Enemy_Form(1);
					if (GetRand(80) == 0) Enemy_Form(2);
					if (GetRand(40) == 0) Enemy_Form(4);
					break;
				case 4:
					if (GetRand(80) == 0) Enemy_Form(2);
					if (GetRand(100) == 0) Enemy_Form(3);
					if (GetRand(40) == 0) Enemy_Form(4);
					break;
				case 5:
					if (GetRand(40) == 0) Enemy_Form(1);
					if (GetRand(80) == 0) Enemy_Form(2);
					if (GetRand(120) == 0) Enemy_Form(5);
					break;
				case 6:
					if (GetRand(40) == 0) Enemy_Form(1);
					if (GetRand(80) == 0) Enemy_Form(2);
					if (GetRand(120) == 0) Enemy_Form(6);
					break;
				case 7:
					if (GetRand(40) == 0) Enemy_Form(1);
					if (GetRand(100) == 0) Enemy_Form(3);
					if (GetRand(40) == 0) Enemy_Form(4);
					if (GetRand(120) == 0) Enemy_Form(5);
					break;
				case 8:
					if (GetRand(80) == 0) Enemy_Form(2);
					if (GetRand(100) == 0) Enemy_Form(3);
					if (GetRand(120) == 0) Enemy_Form(6);
					break;
				case 9:
					if (GetRand(40) == 0) Enemy_Form(4);
					if (GetRand(120) == 0) Enemy_Form(5);
					if (GetRand(120) == 0) Enemy_Form(6);
					break;
				case 10:
					if (0 <= score && score < 20000) {
						if (GetRand(50) == 0) Enemy_Form(1);
					}

					if (0 <= score && score < 4000) {
						if (GetRand(20) == 0) Enemy_Form(2);
					}

					if (4000 <= score && score < 8000) {
						if (GetRand(20) == 0) Enemy_Form(3);
					}

					if (8000 <= score && score < 12000) {
						if (GetRand(10) == 0) Enemy_Form(4);
					}

					if (12000 <= score && score < 16000) {
						if (GetRand(30) == 0) Enemy_Form(5);
					}

					if (16000 <= score && score < 20000) {
						if (GetRand(40) == 0) Enemy_Form(6);
					}
					break;
				}
			}

			//-------------------------------------------------------------------------------------
			// ボス生成
			if (20000 <= score && !boss_flag) {
				boss_flag = true;

				Sound_stop(Sound_Type::GAME_PLAY); // 通常バトル音楽の停止
				Sound_play(Sound_Type::ALERT, bgm_vol);
				warning_time = GetNowCount();

				Object_Pointer enemy_boss;

				if (stage <= 9) {
					enemy_boss.reset(new Enemy_Boss1);
				}
				else {
					enemy_boss.reset(new Enemy_Boss2);
				}

				Add_list(enemy_boss);
			}

			//-------------------------------------------------------------------------------------
			// ボスバトル
			if (boss_flag) {
				if ((GetNowCount() - warning_time) / 1000 < 5) {
					if (((GetNowCount() - warning_time) / 1000) % 2 == 0) {
						My_DrawExtendGraph(70, Display_h / 2 - 40, Display_w - 70, Display_h / 2 + 40, Object_Type::WARNING);
					}
				}
			}

			// 回復の生成
			if (GetRand(350) == 0) {
				Object_Pointer heal(new Heal1);
				Add_list(heal);
			}

			if (GetRand(600) == 0) {
				Object_Pointer heal(new Heal2);
				Add_list(heal);
			}
		}

		// ポーズ画面へ
		if (Push_back()) {
			if (!pause_flag) {
				stop_time = GetNowCount(); // 現在時間の取得
				Sound_play(Sound_Type::PAUSE, effect_vol);
			}
			pause_flag = true;
			Sound_stop(Sound_Type::GAME_PLAY); // 通常バトル音の停止
			Sound_stop(Sound_Type::BOSS);
		}

		//---------------------------------------------------------------
		// ポーズ画面
		if (pause_flag) {
			pause_time = (GetNowCount() - stop_time) / 1000; // ポーズ時間を計算

			DrawBox(150, 150, Display_w - 150, Display_h - 150, GetColor(240, 240, 240), TRUE);
			My_DrawExtendGraph(160, 170, Display_w - 160, 170 + 70, Object_Type::PAUSE_MENU);
			My_DrawExtendGraph(160, 330, Display_w - 160, 330 + 40, Object_Type::ESC);
			My_DrawExtendGraph(270, 380, Display_w - 270, 380 + 40, Object_Type::RESTART);

			// 再開
			if (Push_space()) {
				pause_flag = false;
				limit_time = pause_time + limit_time; // ポーズ時間分プラス
				pause_time = 0;

				if (!boss_flag) {
					Sound_loop_play(Sound_Type::GAME_PLAY, bgm_vol); // 通常バトルBGMの再生
				}
				else {
					Sound_loop_play(Sound_Type::BOSS, bgm_vol); // ボスバトルBGMの再生
				}
			}
		}
		//---------------------------------------------------------------
		// プレイ中　画面左端に文字の表示
		else {
			My_DrawExtendGraph(10, Height + 10, 250, Display_h - 10, Object_Type::BACK_SPACE);
			My_DrawExtendGraph(265, Height + 10, 300 + 80, Display_h - 10, Object_Type::PAUSE);
		}
	}

	// ボス未登場の場合　スコア表示
	if (!boss_flag) {
		My_DrawExtendGraph(Display_w - 300, 10, Display_w - 300 + 110, Top - 10, Object_Type::SCORE);
		DrawBox((Display_w - 300 + 110) + 10, 5, (Display_w - 300 + 110) + 10 + 125, Top - 5, GetColor(50, 50, 50), TRUE);
		Draw_numbers(score, (Display_w - 300 + 110) + 20, 10, 18, 20);
	}

	// タイトル画面へ戻る
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		scene = TITLE;
		Sound_stop(Sound_Type::TITLE); // タイトル画面の音を停止
		Sound_stop(Sound_Type::GAME_PLAY); // プレイ画面の音を停止
		Sound_stop(Sound_Type::BOSS); // ボス画面の音を停止
		Sound_loop_play(Sound_Type::TITLE, bgm_vol); // タイトル画面の音を再生
	}

	// 上限設定
	if (20000 <= score) {
		score = 20000;
	}

	/*
	// ボスデバッグ用
	if (CheckHitKey(KEY_INPUT_1)) {
		score = 20000;
	}*/

	// 制限時間 0 になった場合 GAME OVER
	if (now_time < 0) {
		scene = GAME_OVER;
		Sound_stop(Sound_Type::GAME_PLAY);
		Sound_stop(Sound_Type::BOSS);
		Sound_loop_play(Sound_Type::GAME_OVER, bgm_vol);
	}

	// リスト内で条件: remove_flag == true のクラスを除ける（remove_if 関数）
	// 削除フラグ true のクラスを前に
	// そのクラスを list.erase で削除・リスト内を寄せる
	auto end = remove_if(objects_list.begin(), objects_list.end(), [](Object_Pointer& Object) {return Object->Get_remove(); });
	objects_list.erase(end, objects_list.end());
}

//-------------------------------------------------------------------------------------
void Game::Game_over() {
	My_DrawExtendGraph(100, 250, Display_w - 100, Display_h - 250, Object_Type::GAME_OVER);
	My_DrawExtendGraph(300, Display_h - 80, Display_w - 300, Display_h - 30, Object_Type::PUSH_SPACE);

	now_score = score;
	Draw_numbers(now_score, 10, 10, 20, 20); // スコア表示

	// 値を上書き・記録
	if (Get_score() < now_score) {
		Add_score_to_database(now_score);
	}

	// タイトル画面へ
	if (Push_space()) {
		scene = TITLE;
		Sound_play(Sound_Type::COMMAND, 230);
		Sound_stop(Sound_Type::GAME_OVER);
		Sound_loop_play(Sound_Type::TITLE, bgm_vol);
	}
}

//-------------------------------------------------------------------------------------
void Game::Game_clear() {
	My_DrawExtendGraph(90, 250, Display_w - 90, Display_h - 250, Object_Type::GAME_CLEAR);
	My_DrawExtendGraph(300, Display_h - 80, Display_w - 300, Display_h - 30, Object_Type::PUSH_SPACE);

	now_score = now_time * 100 + score + stage * 10000;

	// スコア表示
	Draw_numbers(now_time * 100, 10, 10, 20, 20);
	Draw_numbers(score, 10, 40, 20, 20);
	Draw_numbers(stage * 10000, 10, 70, 20, 20);
	Draw_numbers(now_score, 10, 100, 20, 20);

	// 値を上書き・記録
	if (Get_score() < now_score) {
		Add_score_to_database(now_score);
	}

	// タイトル画面へ
	if (Push_space()) {
		scene = TITLE;
		Sound_stop(Sound_Type::GAME_CLEAR);
		Sound_play(Sound_Type::COMMAND, 230);
		Sound_loop_play(Sound_Type::TITLE, bgm_vol);
	}
}

//------------------------------------------------------------------------------------
// エラー処理用
void Game::Error_screen() {
	DrawString(50, 50, "ERROR!", GetColor(255, 0, 0));

	if (Push_space()) {
		Game_end();
	}
}

//------------------------------------------------------------------------------------
// DXライブラリを閉じる
void Game::Game_end() {
	DxLib_End();
}

//====================================================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	Game software;
	software.Game_set();
	software.Game_all();
	software.Game_end();
	return 0;
}