#include <iostream> // namespace を使用
#include <memory> // スマートポインタ（自動デストラクタ付）を使用
#include <list> // コンテナ（list）を使用
#include <algorithm> // for_each を使用
#include <cmath> // pow()（べき乗の計算）を使用
#include "DxLib.h" // DXライブラリを使用

using namespace std; // std::～の構文を略す

//-------------------------------------------------------------------------------------

// 列挙型　関数のスイッチとして使用
// 画像
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
	TYPE_NUM, // 列挙対の数
};

//-------------------------------------------------------------------------------------

// 音楽
enum Sound {

	SOUND_SHOT1, // SHOT1 音
	SOUND_SHOT2, // SHOT2 音
	SOUND_CHARGE, // CHARGE 中の音
	SOUND_CHARGE_SHOT, // CHARGE SHOTの音
	SOUND_ENEMY_SHOT, // ENEMY SHOTの音
	SOUND_BEAM, // BEAM 音
	SOUND_E_ATTACK, // ENEMY のアタック音
	SOUND_P_ATTACK, // PLAYER のアタック音
	SOUND_HEAL, // 回復音
	SOUND_BREAK, // 破壊音
	SOUND_NUM, // 列挙対の数
};

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
class Player : public Thing {

private:

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
class Shot : public Thing {

protected:

	float angle; // 円の角度
	float center_x; // 中心 x 座標
	float center_y; // 中心 y 座標
	float shot_s; // 弾の速度

public:

	Shot(); // コンストラクタ（設定）
	ThingType GET_TYPE(); // 自分を SHOT1 タイプで返す
	ThingType HIT_TYPE(); // 当たる敵を ENEMY1 タイプで返す
	void move(); // 右方向へ　画面端で削除
	void draw(); // 描画
	void hit(int damage, int energy); // 処理　削除
};

//-------------------------------------------------------------------------------------

// Through Shot クラス（貫通弾）
class Through_Shot : public Shot {

public:

	Through_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Beam クラス（光線）
class Beam : public Shot {

public:

	Beam();
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Vortex Shot クラス（渦弾）
class Vortex_Shot : public Through_Shot {

private:

	float rad; // 半径

public:

	Vortex_Shot();
	void SET_position(int, int); // 座標を設定
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Spray Shot クラス（散布弾）
class Spray_Shot : public Through_Shot {

public:

	Spray_Shot();
	void SET_angle(float a); // 角度を設定
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Rasen Shot クラス（螺旋弾）
class Rasen_Shot : public Shot {

private:

	int sign; // 1 or -1（符号格納）

public:

	Rasen_Shot();
	void SET_position(int, int);
	void SET_sign(int s); // 符号を設定
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Charge Shot クラス（拡大弾）
class Charge_Shot : public Shot {

private:

	bool charge_flag; // charge フラグ

public:

	Charge_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Period Shot1 クラス（時限弾）
class Period_Shot1 : public Thing {

private:

	int shot_time; // 発射までの時間
	int shot_count; // 発射する数

public:

	Period_Shot1();
	// 当たり判定×　タイプを NONE で返す
	ThingType GET_TYPE();
	ThingType HIT_TYPE();
	void move();
	void draw();
	void hit(int damage, int energy) {};
};

//-------------------------------------------------------------------------------------

// Period Shot2 クラス（上・下）
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

//-------------------------------------------------------------------------------------

// Period Shot3 クラス（左・右）
class Period_Shot3 : public Period_Shot2 {

public:

	Period_Shot3();
	void SET_sign(int s);
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Homing Shot クラス（追尾弾）
class Homing_Shot : public Shot {

public:

	Homing_Shot();
	void move(); // 敵を追尾
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Parabola Shot クラス（放物線弾）
class Parabola_Shot : public Shot {

	// 放物線に関する変数
	float a;
	float b;
	float c;

public:

	Parabola_Shot();
	void SET_position(int, int); // 座標を設定
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Enemy1 クラス（通常）
class Enemy1 : public Thing {

protected:

	int count; // 爆破して削除するまでの数値に
	int up_down; // 上下方向
	bool count_flag; // 爆破フラグ

public:

	Enemy1();
	ThingType GET_TYPE(); // 自分を ENEMY1 タイプで返す
	ThingType HIT_TYPE(); // 当たる敵を PLAYER タイプで返す
	void move();
	void draw();
	void hit(int damage, int energy); // ENEMY1～6まで共通設定
};

//-------------------------------------------------------------------------------------

// Enemy2 クラス（タフ）
class Enemy2 : public Enemy1 {

public:

	Enemy2();
	void move();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy3 クラス（ベクトル）
class Enemy3 : public Enemy1 {

public:

	Enemy3();
	void move();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy4 クラス（高速）
class Enemy4 : public Enemy1 {

public:

	Enemy4();
	void move();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy5 クラス（通常攻撃）
class Enemy5 : public Enemy1 {

public:

	Enemy5();
	void move();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy6 クラス（ベクトル攻撃）
class Enemy6 : public Enemy1 {

public:

	Enemy6();
	void move();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy Boss1 クラス（STAGE１～９まで共通）
class Enemy_Boss1 : public Enemy1 {

protected:

	int add_speed; // 速度を上げる
	int Warn_p; // WARNING!!

public:

	Enemy_Boss1();
	void move();
	void life_draw(); // 体力を描画
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Enemy Boss2 クラス（STAGE１０）
class Enemy_Boss2 : public Enemy_Boss1 {

public:

	Enemy_Boss2();
	void move();
	void life_draw();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy Shot1 クラス（ボス用）
class Enemy_Shot1 : public Thing {

public:

	Enemy_Shot1();
	ThingType GET_TYPE(); // 自分を ENEMY_SHOT1 タイプで返す
	ThingType HIT_TYPE(); // 当たる敵を PLAYER タイプで返す
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Enemy Shot2 クラス（ENEMY5・6用）
class Enemy_Shot2 : public Enemy_Shot1 {

public:

	Enemy_Shot2();
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Heal1 クラス（体力回復）
class Heal1 : public Thing {

public:

	Heal1();
	ThingType GET_TYPE(); // 自分を HEAL1 タイプで返す
	ThingType HIT_TYPE(); // 当たるものを PLAYER タイプで返す
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Heal2 クラス（特殊量回復）
class Heal2 : public Heal1 {

public:

	Heal2();
	void draw();
	void move();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Game クラス
class Game {

	std::list <ThingPointa> thing_list; // Thing クラス　スマートポインタをリスト（list）型データ構造（thing_list）に

private:

	// バック用変数
	int p_x; // x 座標（ループ仕様）
	int p_w; // 横幅
	int add_s; // 速度

	// 画像読込用変数
	int Game_p; // バック
	int Title_p; // SHOOTING GAME
	int Select_p; // STAGE SELECT
	int Number_p; // 1 2 3 4 5 6 7 8 9 10
	int Push_p; // PUSH SPACE
	int Over_p; // GAME OVER
	int Clear_p; // GAME CLEAR
	int Pause_p; // PAUSE
	int Esc_p; // ESC : TITLE・SPACE : REPLAY

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

public:

	// 画面用変数
	static const int WIDTH = 1200; // 横幅
	static const int HEIGHT = 600; // 縦幅

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

// Thing クラスの実装
void Thing::remove() {

	remove_flag = true; // 削除フラグを true に
}

Thing::Thing() {

	remove_flag = false; // 削除フラグを false に
	pause_flag = false; // ポーズ（休止）フラグを false に
}

void Thing::SET_picture(const char* file_name, ThingType thing) {

	// loaded_picture は０の場合　LoadGraph を実装
	if (loaded_picture[thing] == 0) {

		loaded_picture[thing] = LoadGraph(file_name);
	}

	hit_w = m_w; // 横幅を hit_w に
	hit_h = m_h; // 縦幅を hit_ h に
	hit_x = hit_y = 0; // 左上座標を０に
}

void Thing::SET_sound(const char* file_name, Sound sound) {

	// loaded_sound は０の場合　LoadSoundMem を実装
	if (loaded_sound[sound] == 0) {

		loaded_sound[sound] = LoadSoundMem(file_name);
	}
}

void Thing::SET_position(int position_x, int position_y) {

	m_x = position_x; // 設定値を m_x（x 座標） に
	m_y = position_y; // 設定値を m_y（y 座標）に
}

void Thing::SET_hitarea(int h_x, int h_y, int h_w, int h_h) {

	hit_x = h_x; // 相対的 x 座標を設定
	hit_y = h_y; // 相対的 y 座標を設定
	hit_w = h_w; // 横幅を設定
	hit_h = h_h; // 縦幅を設定
}

bool Thing::GET_remove() {

	return remove_flag;
}

ThingType Thing::HIT_TYPE() {

	return TYPE_NONE;
}

void Thing::draw() {

	// 左上(m_x, m_y)					右上(m_x + m_w, m_y)
	// 左下(m_x, m_y + m_h)		右下(m_x + m_w, m_y + m_h)
	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[GET_TYPE()], TRUE); // TRUE は画像の無色をクリアに
}

void Thing::life_draw() {

	if (0 < life_now) {

		DrawExtendGraph(m_x, m_y - 15, m_x + 65, m_y - 10, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(m_x, m_y - 15, m_x + (65 * life_now) / life_max, m_y - 10, loaded_picture[TYPE_LIFE], TRUE); // 体力の値で左へずれる
	}
}

int Thing::GET_damage() {

	return damage;
}

int Thing::GET_energy() {

	return energy;
}

bool Thing::HIT_test(ThingPointa& other) {

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
	if (x_2 < x_1 + w_1 &&
		x_1 < x_2 + w_2 &&
		y_2 < y_1 + h_1 &&
		y_1 < y_2 + h_2) return true;

	return false; // 上記以外は false に
}

//-------------------------------------------------------------------------------------

// Player クラスの実装
Player::Player() {

	m_w = 80; // 横幅
	m_h = 50; // 縦幅
	m_s = 8; // 速度

	// 画像を設定
	SET_picture("PLAYER.png", TYPE_PLAYER);
	SET_picture("HEART.png", TYPE_HEART);
	SET_picture("ENERGY.png", TYPE_ENERGY);

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
}

ThingType Player::HIT_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Player::GET_TYPE() {

	return TYPE_PLAYER;
}

void Player::move() {

	// 点滅エフェクト　マイナスする
	if (0 < dead_time) dead_time--;

	// ポーズ（休止）フラグ false の場合
	if (!pause_flag) {

		// chage_time = 0 そして beam フラグ false の場合
		if (charge_time == 0 && !beam_flag) {

			// 変位設定
			if (CheckHitKey(KEY_INPUT_LEFT)) m_x -= m_s; // ←左
			if (CheckHitKey(KEY_INPUT_RIGHT)) m_x += m_s; // →右
			if (CheckHitKey(KEY_INPUT_UP)) m_y -= m_s; // ↑上
			if (CheckHitKey(KEY_INPUT_DOWN)) m_y += m_s; // ↓下

			// 画面の当たり判定
			if (m_x < 0) m_x = 0; // 画面左
			if (Game::WIDTH < m_x + m_w) m_x = Game::WIDTH - m_w; // 画面右
			if (m_y < 0) m_y = 0; // 画面上
			if (Game::HEIGHT < m_y + m_h) m_y = Game::HEIGHT - m_h; // 画面下
		}

		// 通常弾（Ｂ）
		if (CheckHitKey(KEY_INPUT_B) && shot_count % 8 == 0) {

			if (!shot_flag) { // shot フラグ false の場合

				ThingPointa shot(new Shot); // Shot クラス作成　そのアドレスを Thing クラスのスマートポインタに渡す
				shot->SET_position(m_x + m_w - 10, m_y + 25); // Shot の座標を設定
				game->ADD_list(shot); // Thing リストに Shot アドレスを追加
				PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK); // Shot 音
			}
		}

		// 貫通弾（Ｔ）
		else if (CheckHitKey(KEY_INPUT_T) && shot_count % 10 == 0) {

			// 特殊量４以上の場合　発射可
			if (4 <= energy_now) {

				if (!shot_flag) {

					ThingPointa through_shot(new Through_Shot);
					through_shot->SET_position(m_x + m_w - 30, m_y + 25);
					game->ADD_list(through_shot);
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 光線（Ｃ）
		else if (CheckHitKey(KEY_INPUT_C)) {

			// 特殊量５以上の場合　発射可
			if (5 <= energy_now) {

				if (!beam_flag) { // beam フラグ false の場合

					ThingPointa beam(new Beam);
					beam->SET_position(m_x + m_w + 15, m_y - 10);
					game->ADD_list(beam);
					beam_flag = true; // 連打仕様
					PlaySoundMem(loaded_sound[SOUND_BEAM], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 渦弾（Ｖ）
		else if (CheckHitKey(KEY_INPUT_V) && shot_count % 6 == 0) {

			// 特殊量３以上の場合　発射可
			if (3 <= energy_now) {

				if (!shot_flag) {

					ThingPointa vortex_shot(new Vortex_Shot);
					vortex_shot->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(vortex_shot);
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 散布弾（Ｓ）
		else if (CheckHitKey(KEY_INPUT_S) && shot_count % 10 == 0) {

			// 特殊量９以上の場合　発射可
			if (9 <= energy_now) {

				if (!shot_flag) {

					for (int i = 0; i < 7; i++) { // ７発

						ThingPointa spray_shot1(new Spray_Shot);
						spray_shot1->SET_position(m_x + m_w - 10, m_y + 25);
						spray_shot1->SET_angle(3.14 * (3 - i) / 18); // 散布する角度（３０°・２０°・１０°・０°）を上下に設定
						game->ADD_list(spray_shot1);
					}

					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK); // Shot 音
				}
			}
		}

		// 螺旋弾（Ｒ）
		else if (CheckHitKey(KEY_INPUT_R) && shot_count % 4 == 0) {

			// 特殊量１０の場合　発射可
			if (10 <= energy_now) {

				if (!shot_flag) {

					// 上
					ThingPointa rasen_Shot_1(new Rasen_Shot);
					rasen_Shot_1->SET_position(m_x + m_w - 10, m_y + 25);
					rasen_Shot_1->SET_sign(1); // プラスに
					game->ADD_list(rasen_Shot_1);

					// 下
					ThingPointa rasen_Shot_2(new Rasen_Shot);
					rasen_Shot_2->SET_position(m_x + m_w - 10, m_y + 25);
					rasen_Shot_2->SET_sign(-1); // マイナスに
					game->ADD_list(rasen_Shot_2);
					PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 拡大弾（Ｏ）
		else if (CheckHitKey(KEY_INPUT_O)) {

			// 特殊量２以上の場合　発射可
			if (2 <= energy_now) {

				// 発射準備時間
				if (charge_time <= 5) charge_time++;

				if (charge_time == 5) {

					ThingPointa charge_shot(new Charge_Shot);
					charge_shot->SET_position(m_x + m_w + 15, m_y + 35);
					game->ADD_list(charge_shot);
					PlaySoundMem(loaded_sound[SOUND_CHARGE], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 時限弾（Ｚ）
		else if (CheckHitKey(KEY_INPUT_Z)) {

			// 特殊量８以上の場合　発射可
			if (8 <= energy_now) {

				if (!shot_flag) {

					ThingPointa period_shot1(new Period_Shot1);
					period_shot1->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(period_shot1);
					shot_flag = true; // 連打仕様
					PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 追尾弾（Ｈ）
		else if (CheckHitKey(KEY_INPUT_H) && shot_count % 28 == 0) {

			// 特殊量７以上の場合　発射可
			if (7 <= energy_now) {

				// 残る敵◯の場合
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

		// 放物線弾（Ｐ）
		else if (CheckHitKey(KEY_INPUT_P) && shot_count % 28 == 0) {

			// 特殊量６以上の場合　発射可
			if (6 <= energy_now) {

				// 残る敵◯の場合
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

		// 全ての弾を使用可に
		else if (CheckHitKey(KEY_INPUT_Q)) energy_now = 10;

		else {

			shot_flag = false; // shot フラグを falseに
			beam_flag = false; // beam フラグ を false に
			charge_time = 0; // charge_time を０に
		}
	}

	// ライフ０の場合
	if (life_now <= 0) {

		scene = 3; // オーバー画面へ
		StopSoundMem(Play_m); // プレイ画面の音を停止
		StopSoundMem(Boss_m); // ボス画面の音を停止
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // オーバー画面の音を再生
	}

	// ライフの上限設定
	if (10 <= life_now) life_now = 10;

	// 特殊量の上限設定
	if (10 <= energy_now) energy_now = 10;
}

void Player::heart_draw() {

	if (0 < life_now) {

		// 体力の値でハートの数を調整
		for (int i = 0; i < life_now; i++) {

			DrawExtendGraph(5 + i * 45, 5, 55 + i * 45, 45, loaded_picture[TYPE_HEART], TRUE);
		}
	}
}

void Player::energy_draw() {

	if (0 < energy_now) {

		// 特殊量の値でハートの数を調整
		for (int i = 0; i < energy_now; i++) {

			DrawExtendGraph(460 + i * 45, 5, 510 + i * 45, 45, loaded_picture[TYPE_ENERGY], TRUE);
		}
	}

	// 特殊量の値で（ハートの上に）文字を描画
	int color = GetColor(255, 255, 255); // 色を設定

	DrawFormatString(480, 15, color, "B");
	// 特殊量２～１０以上の場合
	if (2   <= energy_now) DrawFormatString(525, 15, color, "O");
	if (3   <= energy_now) DrawFormatString(570, 15, color, "V");
	if (4   <= energy_now) DrawFormatString(615, 15, color, "T");
	if (5   <= energy_now) DrawFormatString(660, 15, color, "C");
	if (6   <= energy_now) DrawFormatString(705, 15, color, "P");
	if (7   <= energy_now) DrawFormatString(750, 15, color, "H");
	if (8   <= energy_now) DrawFormatString(795, 15, color, "Z");
	if (9   <= energy_now) DrawFormatString(840, 15, color, "S");
	if (10 <= energy_now) DrawFormatString(885, 15, color, "R");
}

void Player::draw() {

	heart_draw(); // 体力を描画
	energy_draw(); // 特殊量を描画

	if (dead_time % 5 == 0) Thing::draw(); // ５で割り切れる場合　点滅で描画
}

void Player::hit(int damage, int energy) {

	// 敵の場合
	if (dead_time <= 0 && 0 < damage) {

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
}

ThingType Shot::GET_TYPE() {

	return TYPE_SHOT1;
}

ThingType Shot::HIT_TYPE() {

	return TYPE_ENEMY1;
}

void Shot::move() {

	if (!pause_flag) m_x += m_s; // 速度を１０に

	if (Game::WIDTH < m_x) remove(); // 画面左で削除
}

void Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT1], TRUE);
}

void Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Through Shot クラス（貫通弾）の実装
Through_Shot::Through_Shot() {

	m_w = 34;
	m_h = 15;
	m_s = 20;
	damage = 1;
	SET_picture("SHOT2.png", TYPE_SHOT2);
	SET_sound("SHOT2.mp3", SOUND_SHOT2);
}

void Through_Shot::move() {

	if (!pause_flag) m_x += m_s; // 速度を２０に

	if (Game::WIDTH < m_x + m_w) remove();
}

void Through_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Through_Shot::hit(int damage, int energy) {

	// 貫通する為 remove 関数は実装×
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Beam クラス（光線）の実装
Beam::Beam() {

	m_w = 0; // 伸長する為０に
	m_h = 80;
	m_s = 15;
	damage = 1;
	SET_picture("BEAM.png", TYPE_BEAM);
	SET_sound("BEAM.mp3", SOUND_BEAM);
}

void Beam::move() {

	if (!pause_flag) {

		m_w += m_s;
		hit_w = m_w; // 横幅を当たり判定に
	}

	if (Game::WIDTH + 100 < m_x + m_w) remove();
}

void Beam::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_BEAM], TRUE);
}

void Beam::hit(int damage, int energy) {

	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Vortex Shot クラス（渦弾）の実装
Vortex_Shot::Vortex_Shot() {

	m_w = 34;
	m_h = 15;
	damage = 10;
	angle = 0; // 角度を０に
	rad = 0; // 半径を０に
}

void Vortex_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;
}

void Vortex_Shot::move() {

	if (!pause_flag) {

		rad += 0.8; // 円の半径にプラスする
		angle += 8 / rad; // 角度をプラスする（角速度を調整）

		// 回る計算
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

//-------------------------------------------------------------------------------------

// Spray Shot クラス（散布弾）の実装
Spray_Shot::Spray_Shot() {

	m_w = 34;
	m_h = 15;
	m_s = 10;
	damage = 5;
	angle = 0;
}

void Spray_Shot::SET_angle(float a) {

	angle = a; // 引数を角度に
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

//-------------------------------------------------------------------------------------

// Rasen Shot1・2 クラス（螺旋弾）の実装
Rasen_Shot::Rasen_Shot() {

	m_w = 12;
	m_h = 12;
	m_s = 8;
	damage = 1;
	angle = 0; // 角度を０に
	sign = 0;
}

void Rasen_Shot::SET_position(int position_x, int position_y) {

	m_x = position_x;
	center_y = position_y;
}

void Rasen_Shot::SET_sign(int s) {

	sign = s; // 引数を符号に
}

void Rasen_Shot::move() {

	if (!pause_flag) {

		angle += 0.2;
		m_x += m_s;
		m_y = center_y - sign * 60 * sin(angle); // サインカーブの応用
	}

	if (Game::WIDTH < m_x) remove();
}

void Rasen_Shot::draw() {

	// 立体的に描画
	DrawExtendGraph(m_x, m_y, m_x + m_w * (1.2 - sign * cos(angle)) / 2, m_y + m_h * (1.2 - sign * cos(angle)) / 2, loaded_picture[TYPE_SHOT1], TRUE);
}

void Rasen_Shot::hit(int damage, int energy) {

	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Charge Shot クラス（拡大弾）の実装
Charge_Shot::Charge_Shot() {

	m_w = 0;
	m_h = 0;
	m_s = 15;
	damage = 0;
	SET_picture("CHARGE SHOT.png", TYPE_CHARGE_SHOT);
	SET_sound("CHARGE.mp3", SOUND_CHARGE); // CHARGE 中の音
	SET_sound("CHARGE SHOT.mp3", SOUND_CHARGE_SHOT); // 発射音
	charge_flag = false; // charge フラグを false に
}

void Charge_Shot::move() {

	if (!charge_flag) {

		// 「Ｏ」を押す場合
		if (CheckHitKey(KEY_INPUT_O)) {

			// 威力制限を５０に（損害量は０にしている為）
			if (damage < 50) {

				damage++;

				m_x += 1;
				m_y -= 2;
				m_w = 2 * damage; // 損害量に伴い拡大
				m_h = 4 * damage;

				// 当たり判定の誤差訂正
				hit_w = m_w + 20;
				hit_h = m_h;
			}

			// 損害量５０未満の場合
			else {

				charge_flag = true;
				StopSoundMem(loaded_sound[SOUND_CHARGE]);
				PlaySoundMem(loaded_sound[SOUND_CHARGE_SHOT], DX_PLAYTYPE_BACK);
			}
		}

		else {

			charge_flag = true;
			StopSoundMem(loaded_sound[SOUND_CHARGE]);
			PlaySoundMem(loaded_sound[SOUND_CHARGE_SHOT], DX_PLAYTYPE_BACK);
		}
	}

	else if (!pause_flag) m_x += m_s; // 速度を１５に

	if (Game::WIDTH < m_x) remove();
}

void Charge_Shot::draw() {

	// angle の値を２で割り切れる場合　描画
	if ((int)angle % 2 == 0) {

		DrawRotaGraph((2 * m_x + m_w) / 2, (2 * m_y + m_h) / 2, (double)m_w / 50, angle, loaded_picture[TYPE_CHARGE_SHOT], TRUE);
	}

	if (!pause_flag) angle += 30; // angle の値に３５プラスする
}

void Charge_Shot::hit(int damage, int energy) {

	remove();
	StopSoundMem(loaded_sound[SOUND_CHARGE]);
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Period Shot1 クラス（時限弾）の実装
Period_Shot1::Period_Shot1() {

	m_w = 15;
	m_h = 15;
	m_s = 12;
	damage = 0;
	shot_time = 30; // 発射までの時間を３０に
	shot_count = 1; // ５回発射する為１に
	SET_picture("SHOT3.png", TYPE_SHOT3);
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK);
}

ThingType Period_Shot1::GET_TYPE() {

	return TYPE_SHOT3;
}

ThingType Period_Shot1::HIT_TYPE() {

	return TYPE_NONE; // 本体に当たり判定×
}

void Period_Shot1::move() {

	if (!pause_flag) {

		if (0 <= shot_time) m_x += m_s; // 発射まで右方向へ

		if (shot_time < 0) {

			// ５回発射
			if (shot_time % 10 == 0 && shot_count <= 5) {

				// 当たり判定◯弾を発射
				// 下方向
				ThingPointa period_shot2(new Period_Shot2());
				game->ADD_list(period_shot2);
				period_shot2->SET_sign(1);
				period_shot2->SET_position(m_x + 1, m_y - 10);

				// 右方向
				ThingPointa period_shot3(new Period_Shot3());
				game->ADD_list(period_shot3);
				period_shot3->SET_sign(1);
				period_shot3->SET_position(m_x - 5, m_y + 2);

				// 上方向
				ThingPointa period_shot4(new Period_Shot2());
				game->ADD_list(period_shot4);
				period_shot4->SET_sign(-1);
				period_shot4->SET_position(m_x + 1, m_y - 10);

				// 左方向
				ThingPointa period_shot5(new Period_Shot3());
				game->ADD_list(period_shot5);
				period_shot5->SET_position(m_x - 12, m_y + 2);
				period_shot5->SET_sign(-1);
				PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);

				shot_count++;
			}

			if (5 < shot_count) remove(); // ５発で削除
		}

		shot_time--;
	}
}

void Period_Shot1::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT3], TRUE);
}

//-------------------------------------------------------------------------------------

// Period Shot2（上下）クラスの実装
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

//-------------------------------------------------------------------------------------

// Period Shot3（左右）クラスの実装
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

//-------------------------------------------------------------------------------------

// Homing Shot クラス（追尾弾）の実装
Homing_Shot::Homing_Shot() {

	m_w = 12;
	m_h = 12;
	m_s = 10;
	damage = 20;
	shot_s = 10; // shot_s を１０に
}

void Homing_Shot::move() {

	if (!pause_flag) {

		// 残る敵◯の場合
		if (0 < enemy_num) {

			// 追尾の計算
			// sqrt() は絶対値
			// pow() はべき乗
			// 一定の速度で追尾
			m_x += ((enemy_x - m_x) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
			m_y += ((enemy_y - m_y) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
		}

		else m_x += m_s; // 残る敵×の場合　右方向へ
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

//-------------------------------------------------------------------------------------

// Parabola Shot クラス（放物線弾）の実装
Parabola_Shot::Parabola_Shot() {

	m_w = 12;
	m_h = 12;
	damage = 50;
	m_s = 0; // shot_s を０に
}

void Parabola_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;

	// 行列計算で三点の座標を計算
	float frame = (enemy_x - center_x) / (8 + enemy_s);

	// 弾・敵を入れる３点の座標
	float x_1 = center_x;
	float x_2 = enemy_x - enemy_s * frame;
	float x_3 = center_x + 1;

	float y_1 = center_y;
	float y_2 = enemy_y;
	float y_3 = center_y - tan(3.14 / 3); // 角度６０°に

	float det_A = -(x_1 - x_2) * (x_2 - x_3) * (x_3 - x_1);
	float det_a = y_1 * x_2 + y_2 * x_3 + y_3 * x_1 - x_2 * y_3 - x_3 * y_1 - x_1 * y_2;
	float det_b = pow(x_1, 2) * y_2 + pow(x_2, 2) * y_3 + pow(x_3, 2) * y_1 - y_1 * pow(x_2, 2) - y_2 * pow(x_3, 2) - y_3 * pow(x_1, 2);
	float det_c = pow(x_1, 2) * x_2 * y_3 + pow(x_2, 2) * x_3 * y_1 + pow(x_3, 2) * x_1 * y_2 - y_1 * x_2 * pow(x_3, 2) - y_2 * x_3 * pow(x_1, 2) - y_3 * x_1 * pow(x_2, 2);

	// クラメルによる計算
	a = det_a / det_A;
	b = det_b / det_A;
	c = det_c / det_A;
}

void Parabola_Shot::move() {

	if (!pause_flag) {

		m_s += 8;
		m_x = center_x + m_s;
		m_y = a * pow(m_x, 2) + b * m_x + c; // 放物線で描画
	}
}

void Parabola_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT1], TRUE);
}

void Parabola_Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// ENEMY1～6クラスの実装
Enemy1::Enemy1() {

	m_w = 80;
	m_h = 50;

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
}

ThingType Enemy1::GET_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Enemy1::HIT_TYPE() {

	return TYPE_PLAYER;
}

void Enemy1::move() {

	if (!pause_flag) m_x -= m_s; // 速度８ or １０

	// 爆破後 count は１３の値を得る
	if (0 < count) {

		count--;
		count_flag = true;
	}

	// 画面左に入る場合
	if (m_x + m_w < 0) {

		remove(); // 削除する

		if (score < 20000 && 0 < score) game->ADD_score(-100); // スコアをマイナスする

		if (0 < enemy_num) enemy_num -= 1; // enemy_num をマイナスする
	}

	// Homing・Parabola Shotクラス（追尾弾・放物線弾）を実装する為　値をグローバル変数に
	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy1::draw() {

	life_draw(); // 体力を描画

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY1], TRUE);
	}

	// 爆破後 count には１３・count_flag は move() で true に
	if (count_flag && 0 <= count) {

		// 爆破エフェクトを描画
		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		// count <= 0 の場合　削除
		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200); // スコアを追加

			if (0 < enemy_num) enemy_num -= 1; // enemy_num をマイナスする
		}
	}
}

void Enemy1::hit(int damage, int energy) {

	life_now -= damage; // 体力をマイナスする

	// 体力０の場合　爆破エフェクトを実装
	if (life_now <= 0 && count == 0) {

		count = 13; // count を１３に
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
	up_down = 6; // 上下方向の速度を６に
	count = 0;
	count_flag = false;
	SET_picture("ENEMY3.png", TYPE_ENEMY3);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy3::move() {

	if (!pause_flag) {

		m_x -= m_s;
		m_y += up_down; // 上下方向の速度
	}

	// 画面の当たり判定
	if (m_y < 0) up_down = -up_down; // 上
	if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // 下

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
	up_down = 6; // 上下方向の速度を６に
	count = 0;
	count_flag = false;
	SET_picture("ENEMY5.png", TYPE_ENEMY5);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy5::move() {

	if (!pause_flag) {

		// 一定の座標まで左向きへ
		if (1000 < m_x) m_x -= m_s;

		// 一定の座標で上下向きへ
		if (m_x <= 1000) {

			m_y -= up_down;

			// 画面の当たり判定
			if (m_y < 0) up_down = -up_down; // 上
			if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // 下

			if (GetRand(60) == 0) {

				ThingPointa enemy_shot2(new Enemy_Shot2); // Enemy Shot2 クラス作成　そのアドレスを Thing クラスのスマートポインタに渡す
				enemy_shot2->SET_position(m_x - 10, m_y + 25); // 座標
				game->ADD_list(enemy_shot2); // Thing リストに Enemy Shot2 アドレスを追加
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

		// 画面の当たり判定
		if (m_y < 0) up_down = -up_down; // 上
		if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // 下
		if (m_x < 0) m_s = -2; // 左
		if (Game::WIDTH + 200 < m_x + m_w) remove(); // 画面右で削除

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

//-------------------------------------------------------------------------------------

// ENEMY BOSS1・2クラスの実装
Enemy_Boss1::Enemy_Boss1() {

	// Enemy Boss1 ライフ設定
	if (stage == 1 || stage == 4 || stage == 7) life_max = 3000; // STAGE１・４・７
	if (stage == 2 || stage == 5 || stage == 8) life_max = 3500; // STAGE２・５・８
	if (stage == 3 || stage == 6 || stage == 9) life_max = 4000; // STAGE３・６・９

	m_w = 350;
	m_h = 390;
	life_now = life_max;
	damage = 1;
	energy = 0;
	up_down = 3; // 上下向き速度を３に
	add_speed = 0; // 体力半分になるまで加速は０に
	count = 0;
	count_flag = false;

	// STAGEの値で画像を設定
	if (stage <= 3) SET_picture("ENEMY BOSS1.png", TYPE_ENEMY_BOSS1);
	if (4 <= stage && stage <= 6) SET_picture("ENEMY BOSS2.png", TYPE_ENEMY_BOSS2);
	if (7 <= stage && stage <= 9) SET_picture("ENEMY BOSS3.png", TYPE_ENEMY_BOSS3);

	SET_hitarea(150, 50, 340, 340); // 当たり判定の設定
	Warn_p = LoadGraph("WARNING.png"); // WARNING!!
	SET_position(Game::WIDTH, 140);
}

void Enemy_Boss1::move() {

	// 体力半分以下の場合　速度を上昇
	if (life_now < life_max / 2) add_speed = 3;

	if (!pause_flag) {

		// 一定の座標まで左方向
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

		// 一定の座標の場合　上下方向
		if (m_x <= 790) {

			m_y += up_down;

			// 画面の当たり判定
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

	int life_x = Game::WIDTH - 245; // 座標の調整

	if (0 < life_now) {

		DrawExtendGraph(life_x, 5, life_x + 245, 30, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(life_x, 5, life_x + (245 * life_now) / life_max, 30, loaded_picture[TYPE_LIFE], TRUE);
	}
}

void Enemy_Boss1::draw() {

	life_draw(); // 体力の描画

	if (0 < life_now) {

		SetFontSize(20); // 文字サイズの設定
		DrawFormatString(Game::WIDTH - 250, 5, GetColor(255, 255, 255), "%d", life_now); // 体力数値の描画
	}

	if (!count_flag) {

		// STAGEの値で画像を設定
		if (stage <= 3) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS1], TRUE);
		if (4 <= stage && stage <= 6) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS2], TRUE);
		if (7 <= stage && stage <= 9) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS3], TRUE);
	}

	if (count_flag && 0 <= count) {

		DrawExtendGraph(m_x - 6 * count, m_y - 6 * count, m_x + m_w + 6 * count, m_y + m_h + 6 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		if (count <= 0 && !count_flag) {

			remove();
			scene = 4; // クリア画面へ
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
	life_max = 5000; // Enemy Boss2 ライフ設定
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

				// 左
				ThingPointa enemy_shot1_1(new Enemy_Shot1);
				enemy_shot1_1->SET_position(m_x + m_w - 250, m_y + 190);
				game->ADD_list(enemy_shot1_1);

				// 真ん中下
				ThingPointa enemy_shot1_2(new Enemy_Shot1);
				enemy_shot1_2->SET_position(m_x + m_w - 210, m_y + 220);
				game->ADD_list(enemy_shot1_2);

				// 真ん中上
				ThingPointa enemy_shot1_3(new Enemy_Shot1);
				enemy_shot1_3->SET_position(m_x + m_w - 210, m_y + 160);
				game->ADD_list(enemy_shot1_3);

				// 右下
				ThingPointa enemy_shot1_4(new Enemy_Shot1);
				enemy_shot1_4->SET_position(m_x + m_w - 170, m_y + 250);
				game->ADD_list(enemy_shot1_4);

				// 右上
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

//-------------------------------------------------------------------------------------

// Enemy Shot1 クラス（ボス）の実装
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

//-------------------------------------------------------------------------------------

// Enemy Shot2 クラス（ENEMY5・6）の実装
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

//-------------------------------------------------------------------------------------

// HEAL1（体力回復）クラスの実装
Heal1::Heal1() {

	m_w = 25;
	m_h = 21;
	m_s = 6;
	damage = -1; // 値はマイナスにして回復に
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

//-------------------------------------------------------------------------------------

// HEAL2（特殊量回復）クラスの実装
Heal2::Heal2() {

	m_w = 25;
	m_h = 21;
	m_s = 10;
	damage = 0;
	energy = -1; // 値をマイナスにして特殊量回復に
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

//-------------------------------------------------------------------------------------

// Game クラスの実装
void Game::ADD_list(ThingPointa & add) {

	thing_list.push_back(add); // Thing リストの back に Thing クラスの add を追加
}

void Game::ADD_score(int sc) {

	score += sc; // スコアを追加
}

bool Game::PUSH_space() {

	if (CheckHitKey(KEY_INPUT_SPACE)) {

		// push_flag　false の場合
		if (!push_flag) {

			push_flag = true;
			return true;
		}
	}

	// 上記以外 false に
	else push_flag = false;

	return false; // false で返す
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

	// text の値を読込する（ハイスコア）
	FILE* file;
	fopen_s(&file, "HIGH SCORE.txt", "r");
	fscanf_s(file, "%d", &high_score);
	fclose(file);
}

void Game::SAVE_highscore() {

	// text の値を記録する（スコア）
	FILE* file;
	fopen_s(&file, "HIGH SCORE.txt", "w");
	fprintf(file, "%d", now_score);
	fclose(file);
}

//-------------------------------------------------------------------------------------

void Game::GAME_SET() {

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

	// 画像の読込
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

	// 音楽ファイルの読込
	Title_m = LoadSoundMem("TITLE.mp3");
	Play_m = LoadSoundMem("GAME PLAY.mp3");
	Over_m = LoadSoundMem("GAME OVER.mp3");
	Clear_m = LoadSoundMem("GAME CLEAR.mp3");
	Pause_m = LoadSoundMem("PAUSE.mp3");
	Boss_m = LoadSoundMem("BOSS GAME.mp3");

	PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // タイトル画面の音を再生
}

//-------------------------------------------------------------------------------------

void Game::GAME_ALL() {

	// イベント処理の実装関数
	while (!ProcessMessage()) {

		ClearDrawScreen(); // 画像を削除（ウラの初期化）

		if (scene == 0) GAME_TITLE();

		if (scene == 1) GAME_SELECT();

		if (scene == 2) GAME_PLAY();

		if (scene == 3) GAME_OVER();

		if (scene == 4) GAME_CLEAR();

		ScreenFlip(); // 画像をオモテに出す
	}
}

//-------------------------------------------------------------------------------------

// scene == 0 の場合　タイトル画面
void Game::GAME_TITLE() {

	SetBackgroundColor(0, 0, 0); // バックの色を黒色に設定
	DrawExtendGraph(10, 200, WIDTH - 10, HEIGHT - 200, Title_p, TRUE); // タイトル
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE

	// 文字の描画
	SetFontSize(20); // サイズの設定
	DrawFormatString(10, 10, GetColor(255, 255, 255), "B E S T  S C O R E : %d", high_score);

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
void Game::GAME_SELECT() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(70, 200, WIDTH - 70, HEIGHT - 200, Select_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Number_p, TRUE); // PUSH SPACE の描画

	// 以下↓ STAGE１～１０の分岐
	// stage == 1 に設定
	if (CheckHitKey(KEY_INPUT_1)) {

		scene = 2; // プレイ画面
		stage = 1; // STAGE１

		// PLAYER 生成
		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 2 に設定
	if (CheckHitKey(KEY_INPUT_2)) {

		scene = 2;
		stage = 2; // STAGE２

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 3 に設定
	if (CheckHitKey(KEY_INPUT_3)) {

		scene = 2;
		stage = 3; // STAGE３

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 4 に設定
	if (CheckHitKey(KEY_INPUT_4)) {

		scene = 2;
		stage = 4; // STAGE４

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 5 に設定
	if (CheckHitKey(KEY_INPUT_5)) {

		scene = 2;
		stage = 5; // STAGE５

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 6 に設定
	if (CheckHitKey(KEY_INPUT_6)) {

		scene = 2;
		stage = 6; // STAGE６

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 7 に設定
	if (CheckHitKey(KEY_INPUT_7)) {

		scene = 2;
		stage = 7; // STAGE７

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 8 に設定
	if (CheckHitKey(KEY_INPUT_8)) {

		scene = 2;
		stage = 8; // STAGE８

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 9 に設定
	if (CheckHitKey(KEY_INPUT_9)) {

		scene = 2;
		stage = 9; // STAGE９

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 10 に設定
	if (CheckHitKey(KEY_INPUT_0)) {

		scene = 2;
		stage = 10; // STAGE１０

		ThingPointa player(new Player);
		ADD_list(player);
	}
}

//-------------------------------------------------------------------------------------

// scene == 2 の場合　プレイ画面
void Game::GAME_PLAY() {

	// バックの描画
	DrawExtendGraph(p_x, 0, p_w, HEIGHT, Game_p, TRUE);
	DrawExtendGraph(p_x + WIDTH, 0, p_w + WIDTH, HEIGHT, Game_p, TRUE); // ２枚目のループ

	//-------------------------------------------------------------------------------------

	if (!pause_flag) {

		// STAGE１～３の場合
		if (stage <= 3) {

			// エフェクトの実装（バックを左へ回す）
			p_x -= 2 + add_s;
			p_w -= 2 + add_s;
		}

		// STAGE４～９の場合
		if (4 <= stage && stage <= 9) {

			p_x -= 3 + add_s;
			p_w -= 3 + add_s;
		}

		// STAGE１０の場合
		if (stage == 10) {

			p_x -= 4 + add_s;
			p_w -= 4 + add_s;
		}
	}

	// ボスの場合　バックを高速で回す
	if (add_s < 40 && boss_flag) add_s += 1;

	// バックのループ
	if (p_x <= -1200) {

		p_x = 0;
		p_w = WIDTH;
	}

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

		for_each(thing_list.begin(), thing_list.end(), [&](ThingPointa & mob) {

			// 両方の HIT タイプ・GET タイプを判別して 返すタイプの等しい場合
			if (main->HIT_TYPE() == mob->GET_TYPE()) {

				// 当たる場合
				if (main->HIT_test(mob)) {

					// hit関数を適用
					// 損害量・特殊量の計算に GET_damage関数・GET_energy関数を使用
					main->hit(mob->GET_damage(), mob->GET_energy());
					mob->hit(main->GET_damage(), main->GET_energy());
				}
			}
		});
	});

	// shot_count をプラスする
	shot_count++;

	//-------------------------------------------------------------------------------------

	// プレイ中の場合
	if (play_flag) {
		
		SetFontSize(20);
		DrawFormatString(WIDTH - 200, HEIGHT - 35, GetColor(255, 255, 255), "T I M E : %d", now_time); // 制限時間の描画
	
		// ポーズ（休止）フラグ false の場合　敵・回復を生成
		if (!pause_flag) {

			// 制限時間の計算
			now_time = (start_time - GetNowCount()) / 1000 + limit_time;

			// スコア２００００未満の場合
			if (score < 20000) {

				//-------------------------------------------------------------------------------------
				// 敵の出現（STAGE１～９）

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
				if (stage == 1 || stage == 2 || stage == 3 || stage == 4 || stage == 5 || stage == 6 || stage == 8) {

					if (GetRand(80) == 0) {

						ThingPointa enemy2(new Enemy2);
						ADD_list(enemy2);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				//-------------------------------------------------------------------------------------
				// ENEMY3（ベクトル）
				if (stage == 2 || stage == 4 || stage == 7 || stage == 8) {

					if (GetRand(100) == 0) {

						ThingPointa enemy3(new Enemy3);
						ADD_list(enemy3);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				//-------------------------------------------------------------------------------------
				// ENEMY4（高速）
				if (stage == 3 || stage == 4 || stage == 7 || stage == 9) {

					if (GetRand(40) == 0) {

						ThingPointa enemy4(new Enemy4);
						ADD_list(enemy4);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				//-------------------------------------------------------------------------------------
				// ENEMY5（通常攻撃）
				if (stage == 5 || stage == 7 || stage == 9) {

					if (GetRand(120) == 0) {

						ThingPointa enemy5(new Enemy5);
						ADD_list(enemy5);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				//-------------------------------------------------------------------------------------
				// ENEMY6（ベクトル攻撃）
				if (stage == 6 || stage == 8 || stage == 9) {

					if (GetRand(120) == 0) {

						ThingPointa enemy6(new Enemy6);
						ADD_list(enemy6);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}
			}

			//-------------------------------------------------------------------------------------
			// STAGE１０

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

			//-------------------------------------------------------------------------------------
			// スコア ２００００以上 そして ボスフラグ false の場合　ボスを生成
			if (20000 <= score && !boss_flag) {

				boss_flag = true; // ボスフラグを true に

				if (boss_flag) {

					StopSoundMem(Play_m); // プレイ画面の音を停止
					PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP); // ボス画面の音を再生

					// STAGE１～９の場合
					if (stage <= 9) {

						ThingPointa enemy_boss1(new Enemy_Boss1);
						ADD_list(enemy_boss1);
					}

					// STAGE１０の場合
					if (stage == 10) {

						ThingPointa enemy_boss2(new Enemy_Boss2);
						ADD_list(enemy_boss2);
					}
				}
			}

			//-------------------------------------------------------------------------------------
			// 常に生成　 回復生成
			if (GetRand(350) == 0) {

				ThingPointa heal(new Heal1);
				ADD_list(heal);
			}

			if (GetRand(600) == 0) {

				ThingPointa heal2(new Heal2);
				ADD_list(heal2);
			}
		}

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
		if (pause_flag) {

			DrawBox(150, 150, WIDTH - 150, HEIGHT - 150, GetColor(255, 255, 255), TRUE);
			DrawExtendGraph(170, 170, WIDTH - 170, 240, Pause_p, TRUE);
			DrawExtendGraph(160, 330, WIDTH - 160, 420, Esc_p, TRUE);

			pause_time = (GetNowCount() - stop_time) / 1000; // ポーズ時間を計算
			
			//-------------------------------------------------------------------------------------
			// ポーズの終了・再開
			if (PUSH_space()) {

				pause_flag = false;
				limit_time = pause_time + limit_time; // ポーズ時間分プラスする
				pause_time = 0; // ０に

				// ボス未登場の場合　プレイ中の音を再生
				if (!boss_flag) PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP);

				// ボス登場中の場合　ボス中の音を再生
				if (boss_flag) PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP);
			}
		}

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
		DrawFormatString(600, 170, GetColor(0, 255, 255), "B : S H O T");
		DrawFormatString(600, 200, GetColor(255, 255, 255), "E L S E : S P E C I A L  S H O T");
		DrawFormatString(600, 230, GetColor(0, 255, 255), "S C O R E : 2 0 0 0 0");

		DrawFormatString(600, 320, GetColor(255, 255, 255), "■ H I N T ■");
		DrawFormatString(600, 350, GetColor(0, 255, 255), "I F  Y O U  G E T  T H E  B L U E  H E A R T");
		DrawFormatString(600, 380, GetColor(0, 255, 255), "Y O U  C A N  U S E  S P E C I A L  S H O T ...");

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
	if (!boss_flag) {

		SetFontSize(20);
		DrawFormatString(WIDTH - 220, 15, GetColor(255, 255, 255), "S C O R E : %d", score);
	}

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
	auto end = remove_if(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {return Thing->GET_remove(); });
	thing_list.erase(end, thing_list.end());
}

//-------------------------------------------------------------------------------------

// scene == 3 の場合　オーバー画面
void Game::GAME_OVER() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Over_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

	now_score = score; // スコアに

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Y O U R  S C O R E : %d", now_score);

	// ハイスコア＜スコアの場合
	if (high_score < now_score) {

		// 値を上書き・記録
		high_score = now_score;
		SAVE_highscore();
	}

	// SPACE を押す場合　タイトル画面へ
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Over_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

//-------------------------------------------------------------------------------------

// scene == 4 の場合　クリア画面
void Game::GAME_CLEAR() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Clear_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE

	// スコアに
	// スコア　＝　時間スコア　＋　スコア（MAX２００００）　＋　STAGE × 10000
	now_score = now_time * 100 + score + stage * 10000;

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Y O U R  S C O R E : %d", now_score);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "T I M E  P O I N T : %d + S C O R E : %d + S T A G E  P O I N T : %d", now_time * 100, score, stage * 10000);

	// ハイスコア＜スコアの場合
	if (high_score < now_score) {

		// 値を上書き・記録
		high_score = now_score;
		SAVE_highscore();
	}

	// SPACE を押す場合 タイトル画面へ
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Clear_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

void Game::GAME_END() {

	DxLib_End(); // DXライブラリの終了
}

//-------------------------------------------------------------------------------------

// WinMain 関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game; // Game クラスを game に
	game.GAME_SET();
	game.GAME_ALL();
	game.GAME_END();
	return 0;
}