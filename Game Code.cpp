#include <iostream> // namespace を使用する
#include <memory> // スマートポインタ（自動デストラクタ付）を使用
#include <list> // コンテナ（list）を使用する
#include <algorithm> // for_eachを使用する
# include <cmath> // pow()（べき乗の計算）を使用する
#include "DxLib.h" // DXライブラリを使用する

using namespace std;

// 列挙型 関数のスイッチとして使用
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

// 音楽
enum Sound {

	SOUND_SHOT1, // SHOT音
	SOUND_SHOT2, // SHOT音2
	SOUND_CHARGE, // CHARGE中の音
	SOUND_CHARGE_SHOT, // CHARGE SHOTを放射する音
	SOUND_ENEMY_SHOT, // ENEMY SHOTの音
	SOUND_BEAM, // BEAM音
	SOUND_E_ATTACK, // ENEMYのアタック音
	SOUND_P_ATTACK, // PLAYERのアタック音
	SOUND_HEAL, // 回復音
	SOUND_BREAK, // 破壊音
	SOUND_NUM, // 列挙対の数
};

class Thing; // スマートポインタ（自動デストラクタ付）の Thing クラスを作るために宣言する

// Thing クラスのスマートポインタ（shared_ptr で Thing 型）ThingPointa を定義する
// GAME クラスで コンテナ（list）の型に使用する
// スマートポインタは new で確保したメモリを自動的に delete する
// typedef は元々あるデータ型に異なる名前を付ける
typedef std::shared_ptr <Thing> ThingPointa;

// グローバル変数（全体に関わる変数）
int scene; // 画面
int stage; // STAGE
int score; // スコア
int shot_count = 0; // 弾の発射間隔の調整 0に設定する
int enemy_x; // 敵の x座標に置換する
int enemy_y; // 敵の y座標に置換する
int enemy_num = 0; // 画面上の敵の数 0に設定する
int enemy_s; // 敵の速度
int pause_flag; // ポーズ（休止）フラグ

int loaded_picture[TYPE_NUM]; // 画像配列
int loaded_sound[SOUND_NUM]; // 音配列

int Title_m; // タイトル中の音
int Play_m; // プレイ中の音
int Over_m; // オーバー中の音
int Clear_m; // クリア中の音
int Pause_m; // ポーズ（休止）画面の効果音
int Boss_m; // ボス中の音

// Thing クラス（継承クラス）
class Thing {

protected: // 子クラスに継承する

	float m_x; // x 座標
	float m_y; // y 座標
	int m_w; // 横幅
	int m_h; // 縦幅
	int m_s; // 速度

	float hit_x; // 当たり判定の x 座標
	float hit_y; // 当たり判定の y 座標
	float hit_w; // 当たり判定の横幅
	float hit_h; // 当たり判定の縦幅

	int life_max; // 設定体力
	int life_now; // 今の体力
	int energy_max; // 設定特殊量
	int energy_now; // 特殊量の数
	int damage; // 損害量
	int energy; // 特殊量
	bool remove_flag; // 削除フラグ
	void remove(); // 削除フラグを true にする

public:

	Thing(); // コンストラクタ（削除フラグを false に）
	void SET_picture(const char* file_name, ThingType thing); // const char* にする　クラスに画像を設置する
	virtual void SET_sound(const char* file_name, Sound sound); // const char* にする　クラスに音を設置する
	virtual void SET_position(int, int); // 初期座標を設定
	void SET_hitarea(int, int, int, int); // 当たり判定を設定
	bool GET_remove(); // 削除フラグを得る
	bool HIT_test(ThingPointa&); // 当たり判定の関数

	virtual ThingType GET_TYPE() = 0; // タイプを得る（純粋仮想）
	virtual ThingType HIT_TYPE(); // 当たる タイプを NONE にする（仮想）

	int GET_damage(); // 損害量 の処理
	int GET_energy(); // 特殊量 の処理

	virtual void move() = 0; // 行動範囲（純粋仮想）
	virtual void draw(); // 画像の描画
	void life_draw(); // 体力の描画
	virtual void hit(int damage, int energy) = 0; // 当たり判定 true の時の処理（純粋仮想）
};

// PLAYER クラス
class Player : public Thing {

private:

	int charge_time; // charge カウント
	int dead_time; // dead カウント（点滅）
	bool beam_flag; // beam フラグ
	bool shot_flag; // shot フラグ

public:

	Player(); // コンストラクタ（初期設定）
	ThingType GET_TYPE(); // 自分を PLAYER タイプと返す
	ThingType HIT_TYPE(); // 当たる Thing タイプを ENEMY1 タイプと返す
	void move(); // 行動範囲・攻撃・壁の当たり判定
	void heart_draw(); // 体力の描画
	void energy_draw(); // 特殊量の描画
	void draw(); // 損害量に対して点滅
	void hit(int damage, int energy); // カウントを50にする
};

// SHOT クラス（通常弾）
class Shot : public Thing {

protected:

	float angle; // 円上の角度
	float center_x; // 中心 x 座標の設定
	float center_y; // 中心 y 座標の設定
	float shot_s; // 弾の速度

public:

	Shot(); // コンストラクタ（初期設定）
	ThingType GET_TYPE(); // 自分を SHOT1 タイプと返す
	ThingType HIT_TYPE(); // 当たる敵を ENEMY1 タイプと返す
	void move(); // 右方向へ　画面の端で削除する
	void draw(); // 描画
	void hit(int damage, int energy); // 処理・削除
};

// THROUGH SHOT クラス（貫通弾）
class Through_Shot : public Shot {

public:

	Through_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// BEAM クラス（光線）
class Beam : public Shot {

public:

	Beam();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// RASEN SHOT クラス（スパイラル弾）
class Rasen_Shot : public Through_Shot {

private:

	float rad; // 半径

public:

	void SET_position(int, int); // 初期位置を設定する
	Rasen_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT1 クラス（散布弾）
class Spray_Shot1 : public Through_Shot {

public:

	Spray_Shot1();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT2 クラス（下1）
class Spray_Shot2 : public Spray_Shot1 {

public:

	Spray_Shot2();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT3 クラス（上1）
class Spray_Shot3 : public Spray_Shot1 {

public:

	Spray_Shot3();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT4 クラス（下3）
class Spray_Shot4 : public Spray_Shot1 {

public:

	Spray_Shot4();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT5 クラス（上3）
class Spray_Shot5 : public Spray_Shot1 {

public:

	Spray_Shot5();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT6 クラス（下2）
class Spray_Shot6 : public Spray_Shot1 {

public:

	Spray_Shot6();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT7 クラス（上2）
class Spray_Shot7 : public Spray_Shot1 {

public:

	Spray_Shot7();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// VORTEX SHOT1 クラス（渦弾）
class Vortex_Shot1 : public Shot {

public:

	Vortex_Shot1();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// VORTEX SHOT2 クラス
class Vortex_Shot2 : public Vortex_Shot1 {

public:

	Vortex_Shot2();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// CHARGE SHOT クラス
class Charge_Shot : public Shot {

private:

	bool charge_flag; // charge フラグ

public:

	Charge_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// PERIOD SHOT1 クラス（時限弾）
class Period_Shot1 : public Thing {

private:

	int shot_time; // 発射するまでの時間
	int shot_count; // 発射する数を設定

public:

	Period_Shot1();
	// 当たり判定は無い タイプを NONE で返す
	ThingType GET_TYPE();
	ThingType HIT_TYPE();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// PERIOD SHOT2 クラス（上）
class Period_Shot2 : public Through_Shot {

public:

	Period_Shot2();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// PERIOD SHOT3 クラス（右）
class Period_Shot3 : public Period_Shot2 {

public:

	Period_Shot3();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// PERIOD SHOT4 クラス（下）
class Period_Shot4 : public Period_Shot2 {

public:

	Period_Shot4();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// PERIOD SHOT5 クラス（左）
class Period_Shot5 : public Period_Shot2 {

public:

	Period_Shot5();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// HOMING SHOT クラス（追撃弾）
class Homing_Shot : public Shot {

public:

	Homing_Shot();
	void move(); // 敵を追いかける
	void draw();
	void hit(int damage, int energy);
};

// PARABOLA SHOT クラス（追撃・放物線弾）
class Parabola_Shot : public Shot {

	// 放物線に関する変数
	float a;
	float b;
	float c;

public:

	void SET_position(int, int); // 初期位置・座標を求める
	Parabola_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// ENEMY1 クラス（通常）
class Enemy1 : public Thing {

protected:

	int count; // 爆破して 削除するまでの数値を入れる
	int up_down; // 上下方向
	bool count_flag; // 爆破フラグ

public:

	Enemy1();
	ThingType GET_TYPE(); // 自分を ENEMY1 タイプと返す
	ThingType HIT_TYPE(); // 当たる敵を PLAYER タイプと返す
	void move();
	void draw();
	void hit(int damage, int energy); // ENEMY1~6まで共通設定
};

// ENEMY2 クラス（タフ）
class Enemy2 : public Enemy1 {

public:

	Enemy2();
	void move();
	void draw();
};

// ENEMY3 クラス（ベクトル）
class Enemy3 : public Enemy1 {

public:

	Enemy3();
	void move();
	void draw();
};

// ENEMY4 クラス（高速）
class Enemy4 : public Enemy1 {

public:

	Enemy4();
	void move();
	void draw();
};

// ENEMY5 クラス（通常攻撃）
class Enemy5 : public Enemy1 {

public:

	Enemy5();
	void move();
	void draw();
};

// ENEMY6 クラス（ベクトル攻撃）
class Enemy6 : public Enemy1 {

public:

	Enemy6();
	void move();
	void draw();
};

// ENEMY BOSS1 クラス（STAGE1~9まで共通）
class Enemy_Boss1 : public Enemy1 {

protected:

	int add_speed; // 速度を上げる
	int Warn_p; // WARNING!!

public:

	Enemy_Boss1();
	void move();
	void life_draw(); // 体力の描画
	void draw();
	void hit(int damage, int energy);
};

// ENEMY BOSS2 クラス（STAGE10）
class Enemy_Boss2 : public Enemy_Boss1 {

public:

	Enemy_Boss2();
	void move();
	void life_draw();
	void draw();
};

// ENEMY SHOT1 クラス（ボス）
class Enemy_Shot1 : public Thing {

public:

	Enemy_Shot1();
	ThingType GET_TYPE(); // 自分を ENEMY_SHOT1 タイプと返す
	ThingType HIT_TYPE(); // 当たる敵を PLAYER タイプと返す
	void move();
	void draw();
	void hit(int damage, int energy);
};

// ENEMY SHOT2 クラス（ENEMY5・6）
class Enemy_Shot2 : public Enemy_Shot1 {

public:

	Enemy_Shot2();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// HEAL1 クラス（体力回復）
class Heal1 : public Thing {

public:

	Heal1();
	ThingType GET_TYPE(); // 自分を HEAL1 タイプと返す
	ThingType HIT_TYPE(); // 当たるものを PLAYER タイプと返す
	void move();
	void draw();
	void hit(int damage, int energy);
};

// HEAL2 クラス（特殊量回復）
class Heal2 : public Heal1 {

public:

	Heal2();
	void draw();
	void move();
	void hit(int damage, int energy);
};

// GAME クラス
class Game {

	std::list <ThingPointa> thing_list; // Thing クラスのスマートポインタを list 型データ構造（thing_list）に入れる

private:

	int p_x; // バックの x 座標（ループ仕様）
	int p_w; // バックの横幅
	int add_s; // バックを高速で回す

	// 画像読込用変数
	int Game_p; // バックの画像
	int Title_p; // SHOOTING GAME
	int Select_p; // STAGE SELECT
	int Number_p; // 1 2 3 4 5 6 7 8 9 10
	int Push_p; // PUSH SPACE
	int Over_p; // GAME OVER
	int Clear_p; // GAME CLEAR
	int Pause_p; // PAUSE
	int Esc_p; // ESC:TITLE SPACE:REPLAY

	// フラグ用変数
	bool push_flag; // SPACE or BACK SPACE KEY用フラグ
	bool game_flag; // true でスタートする
	bool boss_flag; // BOSS フラグ
	bool space_flag; // PUSH SPACE フラグ

	// スコア記録用変数
	int high_score; // ハイスコア（high_score < now_score の場合）
	int now_score; // スコアに置換
	int timer; // 経過時間を0にする
	int now_time; // 残り時間を記録する
	int start_time; // 1s 単位で計測する
	int limit_time; // 制限時間

public:

	static const int WIDTH = 1200; // 画面の横幅
	static const int HEIGHT = 600; // 画面の縦幅
	void ADD_list(ThingPointa&); // Thing クラスのスマートポインタにリストを追加する
	void ADD_score(int sc); // スコアの追加
	bool PUSH_space(); // SPACE KEY の操作
	bool PUSH_back(); // BACK SPACE の操作

	// スコアの記録を実装する関数
	void LOAD_highscore(); // スコア読込
	void SAVE_highscore(); // スコア保存

	void GAME_SET(); // 初期設定
	void GAME_ALL(); // 分岐
	void GAME_TITLE(); // タイトル画面
	void GAME_SELECT(); // 操作説明
	void GAME_PLAY(); // プレイ画面
	void GAME_OVER(); // オーバー画面
	void GAME_CLEAR(); // クリア画面
	void GAME_END(); // 終了
};

Game* game; // GAME クラスのメモリを確保して実体（インスタンス）化する

// Thing クラスの実装
void Thing::remove() {

	remove_flag = true; // 削除フラグを trueにする
}

Thing::Thing() {

	remove_flag = false; // 削除フラグを false にする
	pause_flag = false; // ポーズ（休止）フラグを false にする
}

void Thing::SET_picture(const char* file_name, ThingType thing) {

	// loaded_picture は0の場合　LoadGraph を実装
	if (loaded_picture[thing] == 0) {

		loaded_picture[thing] = LoadGraph(file_name);
	}

	hit_w = m_w; // 横幅を当たり判定に置換
	hit_h = m_h; // 横幅を当たり判定に置換
	hit_x = hit_y = 0; // 画像に対する左上座標を 0にする
}

void Thing::SET_sound(const char* file_name, Sound sound) {

	// loaded_sound は0の場合　LoadSoundMem を実装
	if (loaded_sound[sound] == 0) {

		loaded_sound[sound] = LoadSoundMem(file_name);
	}
}

void Thing::SET_position(int position_x, int position_y) {

	m_x = position_x; // 置き換えた値を m_x（x 座標） に入れる
	m_y = position_y; // 置き換えた値を m_y（y 座標）に入れる
}

void Thing::SET_hitarea(int h_x, int h_y, int h_w, int h_h) {

	hit_x = h_x; // 相対的 x 座標を設定
	hit_y = h_y; // 相対的 y 座標を設定
	hit_w = h_w; // 横幅を設定
	hit_h = h_h; // 縦幅を設定
}

bool Thing::GET_remove() {

	return remove_flag; // 削除フラグを返す
}

ThingType Thing::HIT_TYPE() {

	return TYPE_NONE;
}

void Thing::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[GET_TYPE()], TRUE); // 座標位置に描画・TRUEは黒（初期設定）を透明色に
}

void Thing::life_draw() {

	if (0 < life_now) {

		DrawExtendGraph(m_x, m_y - 15, m_x + 65, m_y - 10, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(m_x, m_y - 15, m_x + (65 * life_now) / life_max, m_y - 10, loaded_picture[TYPE_LIFE], TRUE); // 体力に伴い左へずれる
	}
}

int Thing::GET_damage() {

	return damage;
}

int Thing::GET_energy() {

	return energy;
}

bool Thing::HIT_test(ThingPointa& other) {

	// 画像同士の当たり判定
	int x_1 = m_x + hit_x; // 当たり判定（x 座標）
	int y_1 = m_y + hit_y; // 当たり判定（y 座標）
	int w_1 = hit_w; // 当たり判定（横幅）
	int h_1 = hit_h; // 当たり判定（縦幅）
	int x_2 = other->m_x + other->hit_x; // 対応する当たり判定（x 座標）
	int y_2 = other->m_y + other->hit_y; // 対応する当たり判定（y 座標）
	int w_2 = other->hit_w; // 対応する当たり判定（横幅）
	int h_2 = other->hit_h; // 対応する当たり判定（縦幅）

	// 当たり判定の設定
	if (x_2 < x_1 + w_1 &&
		x_1 < x_2 + w_2 &&
		y_2 < y_1 + h_1 &&
		y_1 < y_2 + h_2) return true;

	return false; // 上記以外は false に
}

// 以下↓ PLAYER クラスの実装
Player::Player() {

	m_w = 80; // 横幅
	m_h = 50; // 縦幅
	m_s = 8; // 速度
	SET_picture("PLAYER.png", TYPE_PLAYER); // 画像
	SET_picture("HEART.png", TYPE_HEART);
	SET_picture("ENERGY.png", TYPE_ENERGY);
	SET_position(150, 300); // x・y 座標の初期位置
	SET_hitarea(10, 10, 70, 40); // 当たり判定設定
	life_max = 5; // 初期ライフ設定
	life_now = life_max; // 現在ライフに設定した値を置換
	energy_max = 1; // 初期特殊力設定
	energy_now = energy_max; // 現在特殊力に設定した値を置換
	damage = 0; // 損害量
	energy = 0; // 特殊量
	shot_flag = false; // shot フラグを false に
	beam_flag = false; // beam フラグを false に
	dead_time = 0; // deat_time を0に設定（点滅用）
	SET_sound("SHOT1.mp3", SOUND_SHOT1); // SHOT 音
	SET_sound("E ATTACK.mp3", SOUND_E_ATTACK); // 損害音
}

ThingType Player::HIT_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Player::GET_TYPE() {

	return TYPE_PLAYER;
}

void Player::move() {

	// 点滅カウントを - 1する
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

			// 壁に対する当たり判定設定
			if (m_x < 0) m_x = 0; // 画面左
			if (Game::WIDTH < m_x + m_w) m_x = Game::WIDTH - m_w; // 画面右
			if (m_y < 0) m_y = 0; // 画面上
			if (Game::HEIGHT < m_y + m_h) m_y = Game::HEIGHT - m_h; // 画面下
		}

		// 通常弾（Ｂ）
		if (CheckHitKey(KEY_INPUT_B) && shot_count % 8 == 0) {

			if (!shot_flag) { // shot フラグ false の場合

				ThingPointa shot(new Shot); // SHOT クラス作成　そのアドレスを Thing クラスのスマートポインタに渡す
				shot->SET_position(m_x + m_w - 10, m_y + 25); // SHOT の初期位置設定
				game->ADD_list(shot); // Thing リストに SHOT アドレス追加
				PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK); // SHOT音
			}
		}

		// 貫通弾（Ｍ）
		else if (CheckHitKey(KEY_INPUT_M) && shot_count % 10 == 0) {

			// 特殊量 4以上の場合 発射可
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

			// 特殊量 5以上の場合 発射可
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

		// スパイラル弾（Ｒ）
		else if (CheckHitKey(KEY_INPUT_R) && shot_count % 6 == 0) {

			// 特殊量 3以上の場合 発射可
			if (3 <= energy_now) {

				if (!shot_flag) {

					ThingPointa rasen_shot(new Rasen_Shot);
					rasen_shot->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(rasen_shot);
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 散布弾（Ｓ）
		else if (CheckHitKey(KEY_INPUT_S) && shot_count % 10 == 0) {

			// 特殊量 9以上の場合 発射可
			if (9 <= energy_now) {

				if (!shot_flag) {

					ThingPointa spray_shot1(new Spray_Shot1);
					spray_shot1->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(spray_shot1);

					ThingPointa spray_shot2(new Spray_Shot2);
					spray_shot2->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(spray_shot2);

					ThingPointa spray_shot3(new Spray_Shot3);
					spray_shot3->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(spray_shot3);

					ThingPointa spray_shot4(new Spray_Shot4);
					spray_shot4->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(spray_shot4);

					ThingPointa spray_shot5(new Spray_Shot5);
					spray_shot5->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(spray_shot5);

					ThingPointa spray_shot6(new Spray_Shot6);
					spray_shot6->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(spray_shot6);

					ThingPointa spray_shot7(new Spray_Shot7);
					spray_shot7->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(spray_shot7);
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK); // SHOT音
				}
			}
		}

		// 渦弾（Ｖ）
		else if (CheckHitKey(KEY_INPUT_V) && shot_count % 4 == 0) {

			// 特殊量 10の場合 発射可
			if (10 <= energy_now) {

				if (!shot_flag) {

					ThingPointa vortex_Shot1(new Vortex_Shot1);
					vortex_Shot1->SET_position(m_x + m_w - 10, m_y + 35);
					game->ADD_list(vortex_Shot1);

					ThingPointa vortex_Shot2(new Vortex_Shot2);
					vortex_Shot2->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(vortex_Shot2);
					PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
				}
			}
		}

		// CHAGE 弾（Ｏ）
		else if (CheckHitKey(KEY_INPUT_O)) {

			// 特殊量 2以上の場合 発射可
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

			// 特殊量 8以上の場合 発射可
			if (8 <= energy_now) {

				if (!shot_flag) {

					ThingPointa period_shot1(new Period_Shot1);
					period_shot1->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(period_shot1);
					shot_flag = true; // 連打する
					PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
				}
			}
		}

		// 追撃（直線）弾（Ｈ）
		else if (CheckHitKey(KEY_INPUT_H) && shot_count % 28 == 0) {

			// 特殊量 7以上の場合 発射可
			if (7 <= energy_now) {

				// 残存する敵がいる場合
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

		// 追撃・放物線弾（Ｐ）
		else if (CheckHitKey(KEY_INPUT_P) && shot_count % 28 == 0) {

			// 特殊量 6以上の場合 発射可
			if (6 <= energy_now) {

				// 残存する敵がいる場合
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

		// 何もしない場合
		else {

			shot_flag = false; // shot フラグを falseに
			beam_flag = false; // beam フラグ を false に
			charge_time = 0; // charge_time を 0 に
		}
	}

	// ライフ 0になった場合
	if (life_now <= 0) {

		scene = 3; // オーバー画面へ
		StopSoundMem(Play_m); // プレイ中の音を停止
		StopSoundMem(Boss_m); // ボス中の音を停止
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // オーバー音
	}

	// ライフの上限設定
	if (10 <= life_now) life_now = 10;

	// 特殊量の上限設定
	if (10 <= energy_now) energy_now = 10;
}

void Player::heart_draw() {

	if (0 < life_now) {

		// 現在の体力によりハートの数を調整する
		for (int i = 0; i < life_now; i++) {

			DrawExtendGraph(5 + i * 45, 5, 55 + i * 45, 45, loaded_picture[TYPE_HEART], TRUE);
		}
	}
}

void Player::energy_draw() {

	if (0 < energy_now) {

		// 現在の特殊量によりハートの数を調整する
		for (int i = 0; i < energy_now; i++) {

			DrawExtendGraph(460 + i * 45, 5, 510 + i * 45, 45, loaded_picture[TYPE_ENERGY], TRUE);
		}
	}

	// 現在の特殊量により（ハートの上に）文字を描画
	DrawFormatString(480, 15, GetColor(255, 255, 255), "B");

	// 特殊量2~10以上の場合
	if (2 <= energy_now)		DrawFormatString(525, 15, GetColor(255, 255, 255), "O");

	if (3 <= energy_now)		DrawFormatString(570, 15, GetColor(255, 255, 255), "R");

	if (4 <= energy_now)		DrawFormatString(615, 15, GetColor(255, 255, 255), "M");
	
	if (5 <= energy_now)		DrawFormatString(660, 15, GetColor(255, 255, 255), "C");
	
	if (6 <= energy_now)		DrawFormatString(705, 15, GetColor(255, 255, 255), "P");
	
	if (7 <= energy_now)		DrawFormatString(750, 15, GetColor(255, 255, 255), "H");
	
	if (8 <= energy_now)		DrawFormatString(795, 15, GetColor(255, 255, 255), "Z");
	
	if (9 <= energy_now)		DrawFormatString(840, 15, GetColor(255, 255, 255), "S");
	
	if (10 == energy_now)	DrawFormatString(885, 15, GetColor(255, 255, 255), "V");
}

void Player::draw() {

	heart_draw(); // 体力
	energy_draw(); // 特殊量

	if (dead_time % 5 == 0) Thing::draw(); // 5で割り切れる場合 点滅して描画する
}

void Player::hit(int damage, int energy) {

	// 敵の場合
	if (dead_time <= 0 && 0 < damage) {

		dead_time = 50; // 点滅カウントを 50に
		life_now -= damage; // 現在の体力より 損害量をマイナスする
		PlaySoundMem(loaded_sound[SOUND_E_ATTACK], DX_PLAYTYPE_BACK); // 損害音
	}

	// HEAL1 の場合
	if (damage < 0) life_now -= damage; // 体力の増加

	// HEAL2 の場合
	if (energy < 0) energy_now -= energy; // 特殊量の増加
}

// SHOT クラス（通常弾）の実装
Shot::Shot() {

	m_w = 12; // 横幅
	m_h = 12; // 縦幅
	m_s = 10; // 速度
	damage = 5; // 損害量
	SET_picture("SHOT1.png", TYPE_SHOT1); // 画像
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK); // 効果音
}

ThingType Shot::GET_TYPE() {

	return TYPE_SHOT1;
}

ThingType Shot::HIT_TYPE() {

	return TYPE_ENEMY1;
}

void Shot::move() {

	if (!pause_flag) m_x += m_s; // 速度を10にする

	if (Game::WIDTH < m_x) remove(); // 画面左で削除する
}

void Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT1], TRUE);
}

void Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// THROUGH SHOT クラス（貫通弾）の実装
Through_Shot::Through_Shot() {

	m_w = 34;
	m_h = 15;
	m_s = 20;
	damage = 1;
	SET_picture("SHOT2.png", TYPE_SHOT2);
	SET_sound("SHOT2.mp3", SOUND_SHOT2);
}

void Through_Shot::move() {

	if (!pause_flag) m_x += m_s; // 速度を20にする

	if (Game::WIDTH < m_x + m_w) remove();
}

void Through_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Through_Shot::hit(int damage, int energy) {

	// 貫通するため remove()　は実装しない
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// BEAM クラス（光線）の実装
Beam::Beam() {

	m_w = 0; // 増加するため 初期は0に
	m_h = 80;
	m_s = 15;
	damage = 1;
	SET_picture("BEAM.png", TYPE_BEAM);
	SET_sound("BEAM.mp3", SOUND_BEAM);
}

void Beam::move() {

	if (!pause_flag) {

		m_w += m_s;
		hit_w = m_w; // 当たり判定に置換する
	}

	if (Game::WIDTH + 100 < m_x + m_w) remove();
}

void Beam::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_BEAM], TRUE);
}

void Beam::hit(int damage, int energy) {

	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// RASEN SHOT クラス（スパイラル弾）の実装
Rasen_Shot::Rasen_Shot() {

	m_w = 34;
	m_h = 15;
	damage = 10;
	angle = 0; // 角度を0に
	rad = 0; // 半径を0に
}

void Rasen_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;
}

void Rasen_Shot::move() {

	if (!pause_flag) {

		rad += 0.8; // 円の半径に加え続ける
		angle += 8 / rad; // 角度を加え続ける（角速度を調整）

		// スパイラルする計算
		m_x = center_x + (float)rad * cos(angle);
		m_y = center_y + (float)rad * sin(angle);
	}

	if (Game::WIDTH < m_x) remove();
}

void Rasen_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Rasen_Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// SPRAY SHOT1~7 クラス（散布弾）の実装
Spray_Shot1::Spray_Shot1() {

	m_w = 34;
	m_h = 15;
	m_s = 10;
	damage = 5;
}

void Spray_Shot1::move() {

	if (!pause_flag) m_x += m_s;

	if (Game::WIDTH < m_x) remove();
}

void Spray_Shot1::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Spray_Shot1::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

Spray_Shot2::Spray_Shot2() {

	m_w = 34;
	m_h = 15;
	m_s = 10;
	damage = 5;
}

void Spray_Shot2::move() {

	if (!pause_flag) {

		// 角度30度の三角形
		m_x += m_s * cos(3.14 / 6);
		m_y += m_s * sin(3.14 / 6);
	}

	if (Game::WIDTH < m_x) remove();
}

void Spray_Shot2::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Spray_Shot2::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

Spray_Shot3::Spray_Shot3() {

	m_w = 34;
	m_h = 15;
	m_s = 10;
	damage = 5;
}

void Spray_Shot3::move() {

	if (!pause_flag) {

		// 角度30度の三角形
		m_x += m_s * cos(3.14 / 6);
		m_y -= m_s * sin(3.14 / 6);
	}

	if (Game::WIDTH < m_x) remove();
}

void Spray_Shot3::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Spray_Shot3::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

Spray_Shot4::Spray_Shot4() {

	m_w = 34;
	m_h = 15;
	m_s = 10;
	damage = 5;
}

void Spray_Shot4::move() {

	if (!pause_flag) {

		// 角度10度の三角
		m_x += m_s * cos(3.14 / 18);
		m_y += m_s * sin(3.14 / 18);
	}

	if (Game::WIDTH < m_x) remove();
}

void Spray_Shot4::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Spray_Shot4::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

Spray_Shot5::Spray_Shot5() {

	m_w = 34;
	m_h = 15;
	m_s = 10;
	damage = 5;
}

void Spray_Shot5::move() {

	if (!pause_flag) {

		// 角度10度の三角形
		m_x += m_s * cos(3.14 / 18);
		m_y -= m_s * sin(3.14 / 18);
	}

	if (Game::WIDTH < m_x) remove();
}

void Spray_Shot5::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Spray_Shot5::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

Spray_Shot6::Spray_Shot6() {

	m_w = 34;
	m_h = 15;
	m_s = 10;
	damage = 5;
}

void Spray_Shot6::move() {

	if (!pause_flag) {

		// 角度20度の三角形
		m_x += m_s * cos(3.14 / 9);
		m_y += m_s * sin(3.14 / 9);
	}

	if (Game::WIDTH < m_x) remove();
}

void Spray_Shot6::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Spray_Shot6::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

Spray_Shot7::Spray_Shot7() {

	m_w = 34;
	m_h = 15;
	m_s = 10;
	damage = 5;
}

void Spray_Shot7::move() {

	if (!pause_flag) {

		// 角度20度の三角形
		m_x += m_s * cos(3.14 / 9);
		m_y -= m_s * sin(3.14 / 9);
	}

	if (Game::WIDTH < m_x) remove();
}

void Spray_Shot7::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Spray_Shot7::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// VORTEX SHOT1・2 クラス（渦弾）の実装
Vortex_Shot1::Vortex_Shot1() {

	m_w = 13;
	m_h = 13;
	m_s = 8;
	damage = 1;
	angle = 0; // 角度を0に
}

void Vortex_Shot1::move() {

	if (!pause_flag) {

		angle += 0.01;
		m_x += m_s;
		m_y = m_y + 10 * cos(angle * 16); // コサインカーブの応用
	}

	if (Game::WIDTH < m_x) remove();
}

void Vortex_Shot1::draw() {

	// 渦状に見せるために大きさを随時変える
	DrawExtendGraph(m_x, m_y, m_x + m_w * (1 + cos(angle * 16)) / 2, m_y + m_h * (1 + cos(angle * 16)) / 2, loaded_picture[TYPE_SHOT1], TRUE);
}

void Vortex_Shot1::hit(int damage, int energy) {

	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

Vortex_Shot2::Vortex_Shot2() {

	m_w = 13;
	m_h = 13;
	m_s = 8;
	damage = 1;
	angle = 0;
}

void Vortex_Shot2::move() {

	if (!pause_flag) {

		angle += 0.01;
		m_x += m_s;
		m_y = m_y - 10 * cos(angle * 16);
	}

	if (Game::WIDTH < m_x) remove();
}

void Vortex_Shot2::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w * (1 - cos(angle * 16)) / 2, m_y + m_h * (1 - cos(angle * 16)) / 2, loaded_picture[TYPE_SHOT1], TRUE);
}

void Vortex_Shot2::hit(int damage, int energy) {

	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// CHARGE SHOT クラス（拡大弾）の実装
Charge_Shot::Charge_Shot() {

	m_w = 0;
	m_h = 0;
	m_s = 15;
	damage = 0;
	SET_picture("CHARGE SHOT.png", TYPE_CHARGE_SHOT);
	SET_sound("CHARGE.mp3", SOUND_CHARGE); // CHARGE中の音
	SET_sound("CHARGE SHOT.mp3", SOUND_CHARGE_SHOT); // 発射音
	charge_flag = false; // charge フラグを false に
}

void Charge_Shot::move() {

	if (!charge_flag) {

		if (CheckHitKey(KEY_INPUT_O)) {

			// 攻撃力MAXを50とする（初期損害量は0にしているため）
			if (damage < 50) {

				damage++;

				m_x += 1;
				m_y -= 2;
				m_w = 2 * damage; // 損害量の増加に伴い 大きくなる
				m_h = 4 * damage;

				// 当たり判定の誤差訂正
				hit_w = m_w + 20;
				hit_h = m_h;
			}

			// 損害量 50未満の場合
			else {

				charge_flag = true;
				StopSoundMem(loaded_sound[SOUND_CHARGE]);
				PlaySoundMem(loaded_sound[SOUND_CHARGE_SHOT], DX_PLAYTYPE_BACK);
			}
		}

		// Ｏを押していない場合
		else {

			charge_flag = true;
			StopSoundMem(loaded_sound[SOUND_CHARGE]);
			PlaySoundMem(loaded_sound[SOUND_CHARGE_SHOT], DX_PLAYTYPE_BACK);
		}
	}

	else if (!pause_flag) m_x += m_s; // 速度を15にする

	if (Game::WIDTH < m_x) remove();
}

void Charge_Shot::draw() {

	// angle の値を2で割り 余り0場合 描画する
	if ((int)angle % 2 == 0) {

		DrawRotaGraph((2 * m_x + m_w) / 2, (2 * m_y + m_h) / 2, (double)m_w / 50, angle, loaded_picture[TYPE_CHARGE_SHOT], TRUE);
	}

	if (!pause_flag) angle += 30; // angle の値に35足し続ける
}

void Charge_Shot::hit(int damage, int energy) {

	remove();
	StopSoundMem(loaded_sound[SOUND_CHARGE]);
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// PERIOD SHOT1 クラス（時限弾）の実装
Period_Shot1::Period_Shot1() {

	m_w = 15;
	m_h = 15;
	m_s = 12;
	damage = 0;
	shot_time = 30; // 発射するまでの時間を30に
	shot_count = 1; // 5回発射するために 初期は1に
	SET_picture("SHOT3.png", TYPE_SHOT3);
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK); 
}

ThingType Period_Shot1::GET_TYPE() {

	return TYPE_SHOT3;
}

ThingType Period_Shot1::HIT_TYPE() {

	return TYPE_NONE; // 本体には当たり判定は無い
}

void Period_Shot1::move() {

	if (!pause_flag) {

		if (0 <= shot_time) m_x += m_s; // 発射するまで右方向へ

		if (shot_time < 0) {

			// 5回発射
			if (shot_time % 10 == 0 && shot_count <= 5) {

				// 当たり判定有りの弾を発射する
				// 上方向
				ThingPointa period_shot2(new Period_Shot2());
				game->ADD_list(period_shot2); //
				period_shot2->SET_position(m_x + 1, m_y - 10);

				// 右方向
				ThingPointa period_shot3(new Period_Shot3());
				game->ADD_list(period_shot3);
				period_shot3->SET_position(m_x - 5, m_y + 2);

				// 下方向
				ThingPointa period_shot4(new Period_Shot4());
				game->ADD_list(period_shot4);
				period_shot4->SET_position(m_x + 1, m_y - 2);

				// 左方向
				ThingPointa period_shot5(new Period_Shot5());
				game->ADD_list(period_shot5); //
				period_shot5->SET_position(m_x - 10, m_y + 2);

				PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);

				shot_count++;
			}

			if (5 < shot_count) remove(); // 5回発射で削除する
		}

		shot_time--;
	}
}

void Period_Shot1::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT3], TRUE);
}

void Period_Shot1::hit(int damage, int energy) {}

// PERIOD SHOT2（上）クラスの実装
Period_Shot2::Period_Shot2() {

	m_w = 15;
	m_h = 34;
	m_s = 20;
	damage = 5;
	SET_picture("SHOT4.png", TYPE_SHOT4);
}

void Period_Shot2::move() {

	if (!pause_flag) m_y -= m_s;

	if (m_y + m_h < 0) remove();
}

void Period_Shot2::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT4], TRUE);
}

void Period_Shot2::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// PERIOD SHOT3（右）クラスの実装
Period_Shot3::Period_Shot3() {

	m_w = 34;
	m_h = 15;
	m_s = 20;
	damage = 5;
}

void Period_Shot3::move() {

	if (!pause_flag) m_x += m_s;

	if (Game::WIDTH < m_x) remove();
}

void Period_Shot3::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Period_Shot3::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// PERIOD SHOT4（下）クラスの実装
Period_Shot4::Period_Shot4() {

	m_w = 15;
	m_h = 34;
	m_s = 20;
	damage = 5;
}

void Period_Shot4::move() {

	if (!pause_flag) m_y += m_s;

	if (Game::HEIGHT < m_y) remove();
}

void Period_Shot4::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT4], TRUE);
}

void Period_Shot4::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// PERIOD SHOT5（左）クラスの実装
Period_Shot5::Period_Shot5() {

	m_w = 34;
	m_h = 15;
	m_s = 20;
	damage = 5;
}

void Period_Shot5::move() {

	if (!pause_flag) m_x -= m_s;

	if (m_x + m_w < 0) remove();
}

void Period_Shot5::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Period_Shot5::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// HORMING SHOT クラス（追撃弾）の実装
Homing_Shot::Homing_Shot() {

	m_w = 12;
	m_h = 12;
	m_s = 10;
	damage = 20;
	shot_s = 10; // shot_s を8にする
}

void Homing_Shot::move() {

	if (!pause_flag) {

		//残存する敵がいる場合
		if (0 < enemy_num) {

			// 追尾する計算
			// sqrt() は絶対値の計算
			// pow() はべき乗の計算
			m_x += ((enemy_x - m_x) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
			m_y += ((enemy_y - m_y) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
		}

		else m_x += m_s; // 残存する敵がいない場合 右方向へ
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

// PARABOLA SHOT クラス（追撃・放物線弾）の実装
void Parabola_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;

	// 行列計算により三点の座標を求める
	float frame = (enemy_x - center_x) / (8 + enemy_s);

	float x_1 = center_x;
	float x_2 = enemy_x - enemy_s * frame;
	float x_3 = center_x + 1;

	float y_1 = center_y;
	float y_2 = enemy_y;
	float y_3 = center_y - tan(3.14 / 3);

	float det_A = -(x_1 - x_2) * (x_2 - x_3) * (x_3 - x_1);
	float det_a = y_1 * x_2 + y_2 * x_3 + y_3 * x_1 - x_2 * y_3 - x_3 * y_1 - x_1 * y_2;
	float det_b = pow(x_1, 2) * y_2 + pow(x_2, 2) * y_3 + pow(x_3, 2) * y_1 - y_1 * pow(x_2, 2) - y_2 * pow(x_3, 2) - y_3 * pow(x_1, 2);
	float det_c = pow(x_1, 2) * x_2 * y_3 + pow(x_2, 2) * x_3 * y_1 + pow(x_3, 2) * x_1 * y_2 - y_1 * x_2 * pow(x_3, 2) - y_2 * x_3 * pow(x_1, 2) - y_3 * x_1 * pow(x_2, 2);

	a = det_a / det_A;
	b = det_b / det_A;
	c = det_c / det_A;
}

Parabola_Shot::Parabola_Shot() {

	m_w = 12;
	m_h = 12;
	damage = 50;
	shot_s = 0; // shot_s を0に
}

void Parabola_Shot::move() {

	if (!pause_flag) {

		shot_s += 8;
		m_x = center_x + shot_s;
		m_y = a * pow(m_x, 2) + b * m_x + c; // 放物線に描画
	}
}

void Parabola_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT1], TRUE);
}

void Parabola_Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// ENEMY1~6クラスの実装
Enemy1::Enemy1() {

	m_w = 80;
	m_h = 50;

	// STAGEにより速度を設定
	if (stage <= 6) m_s = 8;
	if (7 <= stage) m_s = 10;

	life_max = 10; // 体力10
	life_now = life_max; // 設定体力を現在の体力に置換
	damage = 1; // 損害量1
	energy = 0; // 特殊量0
	count = 0; // 体力 != 0 で count を0に
	count_flag = false; // 体力 != 0 で count フラグは false に
	SET_picture("ENEMY1.png", TYPE_ENEMY1);
	SET_picture("BURN.png", TYPE_BURN);
	SET_sound("BREAK.mp3", SOUND_BREAK);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h)); // 初期位置
}

ThingType Enemy1::GET_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Enemy1::HIT_TYPE() {

	return TYPE_PLAYER;
}

void Enemy1::move() {

	if (!pause_flag) m_x -= m_s; // 速度8 or 10

	// 爆破後 count は13の値を得る
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

	// HOMING・PARABOLA SHOTクラス（追尾弾）を実装する為 グローバル変数に値を置換する
	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy1::draw() {

	life_draw(); // 体力の描画

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY1], TRUE);
	}

	// 爆破後 count には13・count_flag は move() で true に
	if (count_flag && 0 <= count) {

		// 爆破エフェクトを描画
		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		// count <= 0 の場合 削除する
		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200); // スコアに得点を追加する

			if (0 < enemy_num) enemy_num -= 1; // enemy_num をマイナスする
		}
	}
}

void Enemy1::hit(int damage, int energy) {

	life_now -= damage; // 体力をマイナスする

	// 体力0の場合 爆破エフェクトを実装する
	if (life_now <= 0 && count == 0) {

		count = 13; // count に13の値を入れる
		PlaySoundMem(loaded_sound[SOUND_BREAK], DX_PLAYTYPE_BACK);
	}
}

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

Enemy3::Enemy3() {

	m_w = 80;
	m_h = 50;

	if (stage <= 6) m_s = 5;
	if (7 <= stage) m_s = 7;

	life_max = 10;
	life_now = life_max;
	damage = 1;
	energy = 0;
	up_down = 6; // 上下方向の速度を6に
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

	// 壁の当たり判定
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

Enemy5::Enemy5() {

	m_w = 80;
	m_h = 50;

	if (stage <= 6) m_s = 4;
	if (7 <= stage) m_s = 5;
	
	life_max = 20;
	life_now = life_max;
	damage = 1;
	energy = 0;
	up_down = 6; // 上下方向の速度を6に
	count = 0;
	count_flag = false;
	SET_picture("ENEMY5.png", TYPE_ENEMY5);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy5::move() {

	if (!pause_flag) {

		// 特定の座標まで左向きへ
		if (1000 < m_x) m_x -= m_s;

		// 特定の座標で上下向きへ
		if (m_x <= 1000) {

			m_y -= up_down;

			// 壁の当たり判定
			if (m_y < 0) up_down = -up_down; // 上
			if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // 下

			if (GetRand(60) == 0) {

				ThingPointa enemy_shot2(new Enemy_Shot2); // ENEMY SHOT2 クラス作成　そのアドレスを Thing クラスのスマートポインタに渡す
				enemy_shot2->SET_position(m_x - 10, m_y + 25); // 初期配置の設定
				game->ADD_list(enemy_shot2); // Thing リストに ENEMY SHOT2 アドレス追加

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

		// 壁の当たり判定
		if (m_y < 0) up_down = - up_down; // 上
		if (Game::HEIGHT < m_y + m_h) up_down = - up_down; // 下
		if (m_x < 0) m_s = - 2; // 左
		if (Game::WIDTH + 200 < m_x + m_w) remove(); // 画面右で削除する

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

// ENEMY BOSS1・2クラスの実装
Enemy_Boss1::Enemy_Boss1() {

	// ENEMY_BOSS1 ライフ設定
	if (stage == 1 || stage == 4 || stage == 7) life_max = 3000; // STAGE1・4・7
	if (stage == 2 || stage == 5 || stage == 8) life_max = 3500; // STAGE2・5・8
	if (stage == 3 || stage == 6 || stage == 9) life_max = 4000; // STAGE3・6・9

	m_w = 350;
	m_h = 390;
	life_now = life_max;
	damage = 1;
	energy = 0;
	up_down = 3; // 上下向き速度
	add_speed = 0; // 体力が半分になるまで加速は0に
	count = 0;
	count_flag = false;

	// STAGEにより描画する画像を設定
	if (stage <= 3) SET_picture("ENEMY BOSS1.png", TYPE_ENEMY_BOSS1);
	if (4 <= stage && stage <= 6) SET_picture("ENEMY BOSS2.png", TYPE_ENEMY_BOSS2);
	if (7 <= stage && stage <= 9) SET_picture("ENEMY BOSS3.png", TYPE_ENEMY_BOSS3);

	SET_hitarea(150, 50, 340, 340); // 当たり判定の設定
	Warn_p = LoadGraph("WARNING.png"); // WARNING!!
	SET_position(Game::WIDTH, 140);
}

void Enemy_Boss1::move() {

	// 体力が半分以下の場合 速さを上げる
	if (life_now < life_max / 2) add_speed = 3;

	if (!pause_flag) {

		// 特定の座標まで左向き
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

		// 特定の座標の場合 上下向き
		if (m_x <= 790) {

			m_y += up_down;

			// 壁の当たり判定
			if (m_y + hit_y + 100 < 0) up_down = 4 + add_speed;
			if (Game::HEIGHT + 100 < m_y + hit_h) up_down = -(4 + add_speed);

			if (GetRand(30) == 0) {

				ThingPointa enemy_shot1_1(new Enemy_Shot1);
				enemy_shot1_1->SET_position(m_x + m_w - 250, m_y + 190);
				game->ADD_list(enemy_shot1_1);

				ThingPointa enemy_shot1_2(new Enemy_Shot1);
				enemy_shot1_2->SET_position(m_x + m_w - 210, m_y + 220);
				game->ADD_list(enemy_shot1_2);

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

	life_draw(); // 体力

	if (0 < life_now) {

		SetFontSize(20); // 文字サイズの設定
		DrawFormatString(Game::WIDTH - 250, 5, GetColor(255, 255, 255), "%d", life_now); // 体力数値の描画
	}

	if (!count_flag) {

		// STAGEにより画像を設定
		if (stage <= 3) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS1], TRUE);
		if (4 <= stage && stage <= 6) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS2], TRUE);
		if (7 <= stage && stage <= 9) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS3], TRUE);
	}

	if (count_flag && 0 <= count) {

		DrawExtendGraph(m_x - 6 * count, m_y - 6 * count, m_x + m_w + 6 * count, m_y + m_h + 6 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		if (count <= 0 && !count_flag) {

			remove();
			scene = 4; // ボスを撃破後 クリア画面へ
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

Enemy_Boss2::Enemy_Boss2() {

	m_w = 370;
	m_h = 350;
	life_max = 5000; // ENEMY BOSS2 ライフ設定
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

// ENEMY SHOT1 クラス（ボス）の実装
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

// ENEMY SHOT2 クラス（ENEMY5・6）の実装
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

// HEAL1（体力回復）クラスの実装
Heal1::Heal1() {

	m_w = 25;
	m_h = 21;
	m_s = 6;
	damage = -1; // 値はマイナスにして回復にする
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

// HEAL2（特殊量回復）クラスの実装
Heal2::Heal2() {

	m_w = 25;
	m_h = 21;
	m_s = 10;
	damage = 0;
	energy = -1; // 値をマイナスにして特殊量回復にする
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

// GAME クラスの実装
void Game::ADD_list(ThingPointa & add) {

	thing_list.push_back(add); // Thing リストの下に Thing クラスの add を追加する
}

void Game::ADD_score(int sc) {

	score += sc; // スコアを追加
}

bool Game::PUSH_space() {

	if (CheckHitKey(KEY_INPUT_SPACE)) {

		// push_flag false の場合
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

void Game::GAME_SET() {

	game = this; // 自インスタンスのアドレスを保持する（静的）
	scene = 0; // タイトル画面へ
	stage = 0; // STAGEを0にする
	score = 0; // スコアを 0に
	p_x = 0; // バックの x 座標を左上に設定
	p_w = WIDTH; // バックの横幅を WIDTH に置換
	limit_time = 500; // 制限時間を500に

	LOAD_highscore(); // スコアの読込
	start_time = GetNowCount(); // 1s 単位にする

	ChangeWindowMode(TRUE); // ウィンドウを開く
	SetGraphMode(WIDTH, HEIGHT, 32); // ウィンドウの横幅・縦幅・カラーの設定
	DxLib_Init(); // DXライブラリを初期化する
	SetDrawScreen(DX_SCREEN_BACK); // 裏面に画像を描画

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

	PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // タイトル音再生
}

void Game::GAME_ALL() {

	// イベント処理を実装する関数
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

// scene == 0 の時　タイトル画面にする
void Game::GAME_TITLE() {

	SetBackgroundColor(0, 0, 0); // バックの色を黒色に設定
	DrawExtendGraph(10, 200, WIDTH - 10, HEIGHT - 200, Title_p, TRUE); // タイトルの描画
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE の描画

	// 文字の描画
	SetFontSize(20); // サイズの設定
	DrawFormatString(10, 10, GetColor(255, 255, 255), "BEST SCORE:%d", high_score);

	thing_list.clear(); // Thing リストを初期化する
	score = 0; // スコアを0に
	add_s = 0; // STAGE10の場合 バックを高速動かす時に置換する

	// SPACE KEY を押した場合　SELECT画面へ
	if (PUSH_space()) scene = 1;

	game_flag = false; // game_flag を false に
	boss_flag = false; // ボスフラグを false に
	space_flag = false; // PUSH SPACE フラグを false に
}

// scene == 1 の時　選択画面
void Game::GAME_SELECT() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(50, 200, WIDTH - 50, HEIGHT - 200, Select_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Number_p, TRUE); // PUSH SPACE の描画

	// 以下↓ STAGE1~10の分岐
	// stage == 1 に設定
	if (CheckHitKey(KEY_INPUT_1)) {

		scene = 2; // プレイ画面
		stage = 1; // STAGE1

		// PLAYER 生成
		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 2 に設定
	if (CheckHitKey(KEY_INPUT_2)) {

		scene = 2;
		stage = 2; // STAGE2

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 3 に設定
	if (CheckHitKey(KEY_INPUT_3)) {

		scene = 2;
		stage = 3; // STAGE3

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 4 に設定
	if (CheckHitKey(KEY_INPUT_4)) {

		scene = 2;
		stage = 4; // STAGE4

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 5 に設定
	if (CheckHitKey(KEY_INPUT_5)) {

		scene = 2;
		stage = 5; // STAGE5

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 6 に設定
	if (CheckHitKey(KEY_INPUT_6)) {

		scene = 2;
		stage = 6; // STAGE6

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 7 に設定
	if (CheckHitKey(KEY_INPUT_7)) {

		scene = 2;
		stage = 7; // STAGE7

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 8 に設定
	if (CheckHitKey(KEY_INPUT_8)) {

		scene = 2;
		stage = 8; // STAGE8

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 9 に設定
	if (CheckHitKey(KEY_INPUT_9)) {

		scene = 2;
		stage = 9; // STAGE9

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 10 に設定
	if (CheckHitKey(KEY_INPUT_0)) {

		scene = 2;
		stage = 10; // STAGE10

		ThingPointa player(new Player);
		ADD_list(player);
	}
}

// scene == 2 の時　プレイ画面
void Game::GAME_PLAY() {

	// バックの描画
	DrawExtendGraph(p_x, 0, p_w, HEIGHT, Game_p, TRUE);
	DrawExtendGraph(p_x + WIDTH, 0, p_w + WIDTH, HEIGHT, Game_p, TRUE); // 二枚目のループ

	if (!pause_flag) {

		// STAGE1～3の場合
		if (stage <= 3) {

			// エフェクトの実装（バックを左へ動かす）
			p_x -= 2 + add_s;
			p_w -= 2 + add_s;
		}

		// STAGE4～9の場合
		if (4 <= stage && stage <= 9) {

			p_x -= 3 + add_s;
			p_w -= 3 + add_s;
		}

		// STAGE10の場合
		if (stage == 10) {

			p_x -= 4 + add_s;
			p_w -= 4 + add_s;
		}
	}

	// STAGE10　ボスの場合はバックを高速で動かす
	if (add_s < 40 && boss_flag) add_s += 1;

	// バックのループ
	if (p_x <= -1200) {

		p_x = 0;
		p_w = WIDTH;
	}

	// for_eachはコンテナ（list etc.）の first-last に対して関数の適用を実装する
	// 構文は [CAPTURE] (仮引数リスト) {関数の本体}
	// Thing リストに入る全てのクラスの move()関数をを使用する
	for_each(thing_list.begin(), thing_list.end(), [] (ThingPointa & Thing) {Thing->move();});

	// Thing リストに入る全てのクラスの draw()関数をを使用する
	for_each(thing_list.begin(), thing_list.end(), [] (ThingPointa & Thing) {Thing->draw();});

	// 当たり判定の実装
	// 範囲全てのクラスに関数を「＆（参照）」にすることで 関数内で mob を使用出来る
	// 二個のクラスを使用しているため この部分だけこの形
	// 当たる場合 両方の hit()関数を適用する
	for_each(thing_list.begin(), thing_list.end(), [&] (ThingPointa & main) {

		if (main->HIT_TYPE() == TYPE_NONE) return; // TYPE_NONEの場合　無視する

		for_each(thing_list.begin(), thing_list.end(), [&] (ThingPointa & mob) {

			// 両方の HIT タイプ・GET タイプを判別して 返すタイプの等しい場合
			if (main->HIT_TYPE() == mob->GET_TYPE()) {

				// 当たる場合
				if (main->HIT_test(mob)) {

					// hit()関数を適用する
					// 損害量・特殊量の計算に GET_damage()関数・GET_energy()関数を使用する
					main->hit(mob->GET_damage(), mob->GET_energy());
					mob->hit(main->GET_damage(), main->GET_energy());
				}
			}
		});
	});

	// shot_count を足し続ける
	shot_count++;

	// game_flag true の場合
	if (game_flag) {

		// 制限時間の計算
		timer = (GetNowCount() - start_time) / 1000 - limit_time;
		now_time = -timer;

		SetFontSize(20);
		DrawFormatString(WIDTH - 120, HEIGHT - 30, GetColor(255, 255, 255), "TIME:%d", now_time); // 制限時間の描画

		// ポーズ（休止）フラグ falseである場合　敵・回復を生成
		if (!pause_flag) {

			// スコア　20000未満の場合
			if (score < 20000) {

				// 敵の出現（STAGE1~9）
				// ENEMY1（普通）
				if (stage == 1 || stage == 2 || stage == 3 || stage == 5 || stage == 6 || stage == 7) { // 出現する STAGE 設定

					if (GetRand(40) == 0) {

						ThingPointa enemy1(new Enemy1); // 敵生成
						ADD_list(enemy1); // Thing リストに ENEMY1 アドレスを追加

						if (0 <= enemy_num) enemy_num += 1; // enemy_num に+１する
					}
				}

				// ENEMY2（タフ）
				if (stage == 1 || stage == 2 || stage == 3 || stage == 4 || stage == 5 || stage == 6 || stage == 8) {

					if (GetRand(80) == 0) {

						ThingPointa enemy2(new Enemy2);
						ADD_list(enemy2);

						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				// ENEMY3（ベクトル）
				if (stage == 2 || stage == 4 || stage == 7 || stage == 8) {

					if (GetRand(100) == 0) {

						ThingPointa enemy3(new Enemy3);
						ADD_list(enemy3);

						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				// ENEMY4（高速）
				if (stage == 3 || stage == 4 || stage == 7 || stage == 9) {

					if (GetRand(40) == 0) {

						ThingPointa enemy4(new Enemy4);
						ADD_list(enemy4);

						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				// ENEMY5（通常攻撃）
				if (stage == 5 || stage == 7 || stage == 9) {

					if (GetRand(120) == 0) {

						ThingPointa enemy5(new Enemy5);
						ADD_list(enemy5);

						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				// ENEMY6（ベクトル攻撃）
				if (stage == 6 || stage == 8 || stage == 9) {

					if (GetRand(120) == 0) {

						ThingPointa enemy6(new Enemy6);
						ADD_list(enemy6);

						if (0 <= enemy_num) enemy_num += 1;
					}
				}
			}

			// STAGE10
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

			// スコア 10000以上 そして ボスフラグ false の場合　ボス生成
			if (20000 <= score && !boss_flag) {

				boss_flag = true; // ボスフラグを true に

				if (boss_flag) {

					StopSoundMem(Play_m); // プレイ中の音を停止
					PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP); // ボス中の音を再生

					// STAGE1～9 の場合
					if (stage <= 9) {

						ThingPointa enemy_boss1(new Enemy_Boss1);
						ADD_list(enemy_boss1);
					}

					// STAGE10 の 場合
					if (stage == 10) {

						ThingPointa enemy_boss2(new Enemy_Boss2);
						ADD_list(enemy_boss2);
					}
				}
			}

			// 常に生成する
			// 回復生成
			if (GetRand(350) == 0) {

				ThingPointa heal(new Heal1);
				ADD_list(heal);
			}

			if (GetRand(600) == 0) {

				ThingPointa heal2(new Heal2);
				ADD_list(heal2);
			}
		}

		// ポーズ（休止）画面へ
		if (PUSH_back()) {

			if (!pause_flag) PlaySoundMem(Pause_m, DX_PLAYTYPE_BACK); // ポーズ音の再生

			pause_flag = true;
			StopSoundMem(Play_m); // プレイ中の音を停止
			StopSoundMem(Boss_m); // ボス中の音を停止
		}

		// ポーズ（休止）画面の描画
		if (pause_flag) {

			DrawBox(150, 150, WIDTH - 150, HEIGHT - 150, GetColor(255, 255, 255), TRUE);
			DrawExtendGraph(170, 170, WIDTH - 170, 240, Pause_p, TRUE);
			DrawExtendGraph(160, 330, WIDTH - 160, 420, Esc_p, TRUE);

			// ポーズの終了・再開
			if (PUSH_space()) {

				pause_flag = false;

				// ボス未登場の場合 プレイ中の音を再生
				if (!boss_flag) PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP);

				// ボスの場合 ボス中の音を再生
				if (boss_flag) PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP);
			}
		}

		// プレイしている間　画面左端に文字を描画
		else DrawFormatString(20, HEIGHT - 30, GetColor(255, 255, 255), "BACK SPACE:PAUSE");
	}

	// game_flag false の場合 文字を描画
	else {

		// B を押した場合 PUSH SPACE を描画
		if (CheckHitKey(KEY_INPUT_B)) space_flag = true;
		if (space_flag) DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

		// 操作 文字の描画
		DrawFormatString(620, 180, GetColor(255, 255, 255), "■ OPERATING METHOD ■");
		DrawFormatString(620, 210, GetColor(0, 255, 255), "B:SHOT");
		DrawFormatString(620, 240, GetColor(255, 255, 255), "ELSE:SPECIAL SHOT");
		DrawFormatString(620, 270, GetColor(0, 255, 255), "SCORE:20000");

		DrawFormatString(620, 350, GetColor(255, 255, 255), "■ HINT ■");
		DrawFormatString(620, 380, GetColor(0, 255, 255), "IF YOU GET THE BLUE HEART");
		DrawFormatString(620, 410, GetColor(0, 255, 255), "YOU CAN USE SPECIAL SHOT...");

		// SPACE KEY を押した場合 プレイする
		if (PUSH_space()) {

			StopSoundMem(Title_m); // タイトル中の音を停止
			PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP); // プレイ中の音を再生
			game_flag = true; // game_flag を trueに
			start_time = GetNowCount(); // 制限時間
		}
	}

	// ボス未登場の場合　スコアを示す
	if (!boss_flag) {

		SetFontSize(20);
		DrawFormatString(WIDTH - 220, 10, GetColor(255, 255, 255), "SCORE:%d", score);
	}

	// ESC を押した場合　タイトル画面へ戻る
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {

		scene = 0;
		StopSoundMem(Title_m); // タイトル中の音を停止
		StopSoundMem(Play_m); // プレイ中の音を停止
		StopSoundMem(Boss_m); // ボス中の音を停止
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // タイトル中の音を再生
	}

	// スコアの上限（20000に設定）
	if (20000 <= score) score = 20000;

	// 制限時間 0になった場合
	if (now_time < 0) {

		scene = 3; // オーバー画面へ
		StopSoundMem(Play_m); // プレイ中の音を停止
		StopSoundMem(Boss_m); // ボス中の音を停止
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // オーバー音
	}

	// Thing リスト内で条件：削除フラグ true のクラスを除ける（remove_if 関数）
	// 削除フラグ true のクラスを前にする
	// そして そのクラスを list.erase により Thing リストで削除・リスト内を詰める
	auto end = remove_if(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {return Thing->GET_remove();});
	thing_list.erase(end, thing_list.end());
}

// scene == 3 の時　オーバー画面
void Game::GAME_OVER() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Over_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

	now_score = score; // スコアに置換

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "YOUR SCORE:%d", now_score);

	// ハイスコアよりスコアが大きい場合
	if (high_score < now_score) {

		// 値を上書き・記録する
		high_score = now_score;
		SAVE_highscore();
	}

	// SPACE KEY を押した場合 タイトル画面へ
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Over_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

// scene == 4 の時　クリア画面
void Game::GAME_CLEAR() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Clear_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE の描画

	// スコアの計算
	// スコア　＝　時間スコア　＋　スコア（Max 20000）　＋　STAGE × 10000
	now_score = now_time * 100 + score + stage * 10000;

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "YOUR SCORE:%d", now_score);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "TIME POINT:%d + SCORE:%d + STAGE POINT:%d", now_time * 100, score, stage * 10000);

	// ハイスコアよりスコアが大きい場合
	if (high_score < now_score) {

		// 値を上書き・記録する
		high_score = now_score;
		SAVE_highscore();
	}

	// SPACE KEY を押した場合 タイトル画面へ
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Clear_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

void Game::GAME_END() {

	DxLib_End(); // DXライブラリの終了
}

// WinMain 関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game; // GAME クラスを game に置換
	game.GAME_SET();
	game.GAME_ALL();
	game.GAME_END();
	return 0;
}