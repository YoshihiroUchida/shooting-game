<<<<<<< HEAD
#include <iostream> // namespace ���g�p
#include <memory> // �X�}�[�g�|�C���^�i�����f�X�g���N�^�t�j���g�p
#include <list> // �R���e�i�ilist�j���g�p
#include <algorithm> // for_each ���g�p
#include <cmath> // pow()�i�ׂ���̌v�Z�j���g�p
#include "DxLib.h" // DX���C�u�������g�p

using namespace std; // std::�`�̍\���𗪂�

//-------------------------------------------------------------------------------------

// �񋓌^�@�֐��̃X�C�b�`�Ƃ��Ďg�p
// �摜
=======
// Visual Studio C++
#include <iostream> // namespace を使用する
#include <memory> // スマートポインタ（自動デストラクタ付）を使用する
#include <list> // コンテナ（list）を使用する
#include <algorithm> // for_each を使用する
#include <cmath> // pow()（べき乗の計算）を使用する
#include "DxLib.h" // DXライブラリを使用する

using namespace std; // std::～の構文を略す

// 列挙型　関数のスイッチとして使用する
// 画像
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
	TYPE_NUM, // 列挙対の数
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// ���y
=======
// 音楽
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

class Thing; // �X�}�[�g�|�C���^�i�����f�X�g���N�^�t�j�� Thing �N���X�����ׂɐ錾

// Thing �N���X�@�X�}�[�g�|�C���^�ishared_ptr �� Thing �^�jThingPointa
// Game �N���X�ŃR���e�i�ilist�j�̌^���g�p
// new �Ŋm�ۂ����������������I�� delete ����
// typedef �̓f�[�^�^�֕ʖ���t����
typedef shared_ptr <Thing> ThingPointa;

//-------------------------------------------------------------------------------------

// �O���[�o���ϐ��i�R�[�h�S�̂Ɋ֘A����ϐ��j
int scene; // ���
int stage; // STAGE
int score; // �X�R�A
int shot_count = 0; // �e�̊Ԋu�����@������
int enemy_x; // �G�� x ���W��
int enemy_y; // �G�� y ���W��
int enemy_num = 0; // ��ʏ�̓G�@������
int enemy_s; // �G�̑��x
bool pause_flag; // �|�[�Y�i�x�~�j�t���O

int loaded_picture[TYPE_NUM]; // �摜�z��
int loaded_sound[SOUND_NUM]; // ���z��

// ���t�@�C���i�[�p�ϐ��iGame �N���X�j
int Title_m; // �^�C�g�����
int Play_m; // �v���C���
int Over_m; // �I�[�o�[���
int Clear_m; // �N���A���
int Pause_m; // �|�[�Y�i�x�~�j���
int Boss_m; // �{�X���

//-------------------------------------------------------------------------------------

// Thing �N���X�i�p���N���X�j
class Thing {

protected: // �q�N���X�Ɍp��

	float m_x; // x ���W
	float m_y; // y ���W
	int m_w; // ����
	int m_h; // �c��
	int m_s; // ���x

	// �����蔻��p�ϐ�
	float hit_x; // x ���W
	float hit_y; // y ���W
	float hit_w; // ����
	float hit_h; // �c��

	int life_max; // �ݒ�̗�
	int life_now; // ���̗̑�
	int energy_max; // �ݒ�����
	int energy_now; // ���̓����
	int damage; // ���Q��
	int energy; // �����
	bool remove_flag; // �폜�t���O
	void remove(); // �폜�t���O�� true ��

public:

	Thing(); // �R���X�g���N�^�i�폜�t���O�� false �Ɂj
	void SET_picture(const char* file_name, ThingType thing); // const char* �Ɂ@�N���X�p�@�摜
	virtual void SET_sound(const char* file_name, Sound sound); // const char* �Ɂ@�N���X�p�@��
	virtual void SET_position(int, int); // ���W��ݒ�
	virtual void SET_hitarea(int, int, int, int); // �����蔻���ݒ�
	bool GET_remove(); // �폜�t���O�𓾂�
	bool HIT_test(ThingPointa&); // �����蔻��

	virtual ThingType GET_TYPE() = 0; // �����̃^�C�v�𓾂�i�������z�j
	virtual ThingType HIT_TYPE(); // ������^�C�v�� NONE �Ɂi���z�j

	int GET_damage(); // ���Q�ʂ̏���
	int GET_energy(); // ����ʂ̏���

	virtual void SET_angle(float a) {}; // �p�x��ݒ�
	virtual void SET_sign(int s) {}; // ������ݒ�
	virtual void move() = 0; // ����i�������z�j
	virtual void draw(); // �摜��`��
	virtual void life_draw(); // �̗͂�`��
	virtual void hit(int damage, int energy) = 0; // �����蔻�� true �̏ꍇ�@�����i�������z�j
};

//-------------------------------------------------------------------------------------

// Player �N���X
=======
class Thing; // スマートポインタ（自動デストラクタ付）の Thing クラスを作る為に宣言する

// Thing クラスのスマートポインタ（shared_ptr で Thing 型）ThingPointa を定義する
// Game クラスでコンテナ（list）の型に使用する
// スマートポインタは new で確保したメモリを自動的に delete する
// typedef は元々のデータ型へ別名を付ける
typedef shared_ptr <Thing> ThingPointa;

// グローバル変数（全体に関連する変数）
int scene; // 画面
int stage; // STAGE
int score; // スコア
int shot_count = 0; // 弾の間隔調整　０に設定する
int enemy_x; // 敵の x 座標に置く
int enemy_y; // 敵の y 座標に置く
int enemy_num = 0; // 画面上の敵　０に設定する
int enemy_s; // 敵の速度
bool pause_flag; // ポーズ（休止）フラグ

int loaded_picture[TYPE_NUM]; // 画像配列
int loaded_sound[SOUND_NUM]; // 音配列

// 音楽ファイル格納用変数（Game クラスにて設定する）
int Title_m; // タイトル中
int Play_m; // プレイ中
int Over_m; // オーバー中
int Clear_m; // クリア中
int Pause_m; // ポーズ（休止）画面
int Boss_m; // ボス中

// Thing クラス（継承クラス）
class Thing {

protected: // 子クラスに継承する

	float m_x; // x 座標
	float m_y; // y 座標
	int m_w; // 横幅
	int m_h; // 縦幅
	int m_s; // 速度

	// 当たり判定変数
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
	void remove(); // 削除フラグを true にする

public:

	Thing(); // コンストラクタ（削除フラグを false に）
	void SET_picture(const char* file_name, ThingType thing); // const char* にする　クラスに画像を置く
	virtual void SET_sound(const char* file_name, Sound sound); // const char* にする　クラスに音を置く
	virtual void SET_position(int, int); // 初期座標を設定する
	virtual void SET_hitarea(int, int, int, int); // 当たり判定を設定する
	bool GET_remove(); // 削除フラグを得る
	bool HIT_test(ThingPointa&); // 当たり判定の関数

	virtual ThingType GET_TYPE() = 0; // 自分のタイプを得る（純粋仮想）
	virtual ThingType HIT_TYPE(); // 当たるタイプを NONE にする（仮想）

	int GET_damage(); // 損害量の処理をする
	int GET_energy(); // 特殊量の処理をする

	virtual void SET_angle(float a) {}; // 角度設定する
	virtual void SET_sign(int s) {}; // 符号設定する
	virtual void move() = 0; // 行動範囲（純粋仮想）
	virtual void draw(); // 画像描画をする
	virtual void life_draw(); // 体力描画をする
	virtual void hit(int damage, int energy) = 0; // 当たり判定 true の時　処理をする（純粋仮想）
};

// Player クラス
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Player : public Thing {

private:

<<<<<<< HEAD
	int charge_time; // charge �v���i�g��e�p�j
	int dead_time; // dead �v���i�_�ŗp�j
	bool beam_flag; // beam �t���O
	bool shot_flag; // shot �t���O

public:

	Player(); // �R���X�g���N�^�i�ݒ�j
	ThingType GET_TYPE(); // ������ PLAYER �^�C�v�ŕԂ�
	ThingType HIT_TYPE(); // ������^�C�v�� ENEMY1 �^�C�v�ŕԂ�
	void move(); // ���@�̓���@�e����@��ʂ̓����蔻��
	void heart_draw(); // �̗͂̕`��
	void energy_draw(); // ����ʂ̕`��
	void draw(); // dead_time �̒l�œ_��
	void hit(int damage, int energy); // dead_time ���T�O��
};

//-------------------------------------------------------------------------------------

// Shot �N���X�i�ʏ�e�j
=======
	int charge_time; // charge カウント
	int dead_time; // dead カウント（点滅）
	bool beam_flag; // beam フラグ
	bool shot_flag; // shot フラグ

public:

	Player(); // コンストラクタ（初期設定）
	ThingType GET_TYPE(); // 自分を PLAYER タイプで返す
	ThingType HIT_TYPE(); // 当たるタイプを ENEMY1 タイプで返す
	void move(); // 行動範囲・アタック・画面の当たり判定
	void heart_draw(); // 体力の描画をする
	void energy_draw(); // 特殊量の描画をする
	void draw(); // 損害量に対して点滅する
	void hit(int damage, int energy); // 点滅を５０にする
};

// Shot クラス（通常弾）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Shot : public Thing {

protected:

	float angle; // 円の角度
	float center_x; // 中心 x 座標
	float center_y; // 中心 y 座標
	float shot_s; // 弾の速度

public:

<<<<<<< HEAD
	Shot(); // �R���X�g���N�^�i�ݒ�j
	ThingType GET_TYPE(); // ������ SHOT1 �^�C�v�ŕԂ�
	ThingType HIT_TYPE(); // ������G�� ENEMY1 �^�C�v�ŕԂ�
	void move(); // �E�����ց@��ʒ[�ō폜
	void draw(); // �`��
	void hit(int damage, int energy); // �����@�폜
};

//-------------------------------------------------------------------------------------

// Through Shot �N���X�i�ђʒe�j
=======
	Shot(); // コンストラクタ（初期設定）
	ThingType GET_TYPE(); // 自分を SHOT1 タイプで返す
	ThingType HIT_TYPE(); // 当たる敵を ENEMY1 タイプで返す
	void move(); // 右方向へ　画面の端で削除する
	void draw(); // 描画する
	void hit(int damage, int energy); // 処理・削除する
};

// Through Shot クラス（貫通弾）
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

// Beam �N���X�i�����j
=======
// Beam クラス（光線）
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

// Vortex Shot �N���X�i�Q�e�j
=======
// Vortex Shot クラス（渦弾）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Vortex_Shot : public Through_Shot {

private:

	float rad; // 半径

public:

	Vortex_Shot();
<<<<<<< HEAD
	void SET_position(int, int); // ���W��ݒ�
=======
	void SET_position(int, int); // 初期位置を設定する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Spray Shot �N���X�i�U�z�e�j
=======
// Spray Shot クラス（散布弾）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Spray_Shot : public Through_Shot {

public:

	Spray_Shot();
	void SET_angle(float a); // �p�x��ݒ�
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Rasen Shot �N���X�i�����e�j
=======
// Rasen Shot クラス（螺旋弾）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Rasen_Shot : public Shot {

private:

	int sign; // 1 or -1（符号格納）

public:

	Rasen_Shot();
	void SET_position(int, int);
	void SET_sign(int s); // ������ݒ�
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Charge Shot �N���X�i�g��e�j
=======
// Charge Shot クラス（拡大弾）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Charge_Shot : public Shot {

private:

	bool charge_flag; // charge フラグ

public:

	Charge_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot1 �N���X�i�����e�j
=======
// Period Shot1 クラス（時限弾）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot2 �N���X�i��E���j
=======
// Period Shot2 クラス（上・下）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Period_Shot2 : public Through_Shot {

protected:

	int sign; // ����

public:

	Period_Shot2();
	void SET_sign(int s);
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot3 �N���X�i���E�E�j
=======
// Period Shot3 クラス（左・右）
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

// Homing Shot �N���X�i�ǔ��e�j
=======
// Homing Shot クラス（追尾弾）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Homing_Shot : public Shot {

public:

	Homing_Shot();
<<<<<<< HEAD
	void move(); // �G��ǔ�
=======
	void move(); // 敵を追尾する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Parabola Shot �N���X�i�������e�j
=======
// Parabola Shot クラス（追尾・放物線弾）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Parabola_Shot : public Shot {

	// 放物線に関する変数
	float a;
	float b;
	float c;

public:

	Parabola_Shot();
<<<<<<< HEAD
	void SET_position(int, int); // ���W��ݒ�
=======
	void SET_position(int, int); // 初期位置・座標を求める
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy1 �N���X�i�ʏ�j
=======
// Enemy1 クラス（通常）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy1 : public Thing {

protected:

<<<<<<< HEAD
	int count; // ���j���č폜����܂ł̐��l��
	int up_down; // �㉺����
	bool count_flag; // ���j�t���O
=======
	int count; // 爆破して削除するまで　数値を入れる
	int up_down; // 上下方向
	bool count_flag; // 爆破フラグ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

public:

	Enemy1();
<<<<<<< HEAD
	ThingType GET_TYPE(); // ������ ENEMY1 �^�C�v�ŕԂ�
	ThingType HIT_TYPE(); // ������G�� PLAYER �^�C�v�ŕԂ�
=======
	ThingType GET_TYPE(); // 自分を ENEMY1 タイプと返す
	ThingType HIT_TYPE(); // 当たる敵を PLAYER タイプと返す
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy); // ENEMY1～6まで共通設定
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy2 �N���X�i�^�t�j
=======
// Enemy2 クラス（タフ）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy2 : public Enemy1 {

public:

	Enemy2();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy3 �N���X�i�x�N�g���j
=======
// Enemy3 クラス（ベクトル）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy3 : public Enemy1 {

public:

	Enemy3();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy4 �N���X�i�����j
=======
// Enemy4 クラス（高速）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy4 : public Enemy1 {

public:

	Enemy4();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy5 �N���X�i�ʏ�U���j
=======
// Enemy5 クラス（通常攻撃）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy5 : public Enemy1 {

public:

	Enemy5();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy6 �N���X�i�x�N�g���U���j
=======
// Enemy6 クラス（ベクトル攻撃）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy6 : public Enemy1 {

public:

	Enemy6();
	void move();
	void draw();
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Boss1 �N���X�iSTAGE�P�`�X�܂ŋ��ʁj
=======
// Enemy Boss1 クラス（STAGE１～９まで共通）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy_Boss1 : public Enemy1 {

protected:

	int add_speed; // 速度を上げる
	int Warn_p; // WARNING!!

public:

	Enemy_Boss1();
	void move();
<<<<<<< HEAD
	void life_draw(); // �̗͂�`��
=======
	void life_draw(); // 体力を描画する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Boss2 �N���X�iSTAGE�P�O�j
=======
// Enemy Boss2 クラス（STAGE１０）
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

// Enemy Shot1 �N���X�i�{�X�p�j
=======
// Enemy Shot1 クラス（ボス用）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Enemy_Shot1 : public Thing {

public:

	Enemy_Shot1();
<<<<<<< HEAD
	ThingType GET_TYPE(); // ������ ENEMY_SHOT1 �^�C�v�ŕԂ�
	ThingType HIT_TYPE(); // ������G�� PLAYER �^�C�v�ŕԂ�
=======
	ThingType GET_TYPE(); // 自分を ENEMY_SHOT1 タイプと返す
	ThingType HIT_TYPE(); // 当たる敵を PLAYER タイプと返す
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Shot2 �N���X�iENEMY5�E6�p�j
=======
// Enemy Shot2 クラス（ENEMY5・6用）
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

// Heal1 �N���X�i�̗͉񕜁j
=======
// Heal1 クラス（体力回復）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
class Heal1 : public Thing {

public:

	Heal1();
<<<<<<< HEAD
	ThingType GET_TYPE(); // ������ HEAL1 �^�C�v�ŕԂ�
	ThingType HIT_TYPE(); // ��������̂� PLAYER �^�C�v�ŕԂ�
=======
	ThingType GET_TYPE(); // 自分を HEAL1 タイプと返す
	ThingType HIT_TYPE(); // 当たるものを PLAYER タイプと返す
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	void move();
	void draw();
	void hit(int damage, int energy);
};

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Heal2 �N���X�i����ʉ񕜁j
=======
// Heal2 クラス（特殊量回復）
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

// Game �N���X
class Game {

	std::list <ThingPointa> thing_list; // Thing �N���X�@�X�}�[�g�|�C���^�����X�g�ilist�j�^�f�[�^�\���ithing_list�j��
=======
// Game クラス
class Game {

	std::list <ThingPointa> thing_list; // Thing クラスのスマートポインタを list 型データ構造（thing_list）に入れる
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

private:

	// バック用変数
	int p_x; // x 座標（ループ仕様）
	int p_w; // 横幅
	int add_s; // 速度

<<<<<<< HEAD
	// �摜�Ǎ��p�ϐ�
	int Game_p; // �o�b�N
=======
	// 画像読込用変数
	int Game_p; // バックの画像
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	int Title_p; // SHOOTING GAME
	int Select_p; // STAGE SELECT
	int Number_p; // 1 2 3 4 5 6 7 8 9 10
	int Push_p; // PUSH SPACE
	int Over_p; // GAME OVER
	int Clear_p; // GAME CLEAR
	int Pause_p; // PAUSE
	int Esc_p; // ESC : TITLE�ESPACE : REPLAY

<<<<<<< HEAD
	// �t���O�ϐ�
	bool push_flag; // PUSH_space�֐��EPUSH_back�֐��p
	bool play_flag; // �v���C�p�Etrue �ŃX�^�[�g
	bool boss_flag; // �{�X�p
	bool space_flag; // �X�y�[�X�p

	// �X�R�A�E���ԂɊւ���ϐ�
	int high_score; // �n�C�X�R�A�ihigh_score < now_score �̏ꍇ�j
	int now_score; // �X�R�A
	int now_time; // �c�莞��
	int start_time; // �Ps �P�ʂŌv������
	int stop_time; // �|�[�Y����ꍇ�@���ݎ��Ԃ𓾂�
	int pause_time; // �|�[�Y��ʂ̌o�ߎ���
	int limit_time; // ��������
=======
	// フラグ用変数
	bool push_flag; // SPACE or BACK SPACE 用フラグ
	bool game_flag; // true でスタートする
	bool boss_flag; // Boss フラグ
	bool space_flag; // PUSH SPACE フラグ

	// スコア記録用変数
	int high_score; // ハイスコア（high_score < now_score の場合）
	int now_score; // スコアに置換
	int timer; // タイマー
	int now_time; // 残り時間を記録する
	int start_time; // １s 単位で計測する
	int limit_time; // 制限時間
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

public:

	// 画面用変数
	static const int WIDTH = 1200; // 横幅
	static const int HEIGHT = 600; // 縦幅

<<<<<<< HEAD
	void ADD_list(ThingPointa&); // Thing �N���X�@�X�}�[�g�|�C���^�Ƀ��X�g�ilist�j��ǉ�
	void ADD_score(int sc); // �X�R�A��ǉ�
	bool PUSH_space(); // SPACE ����
	bool PUSH_back(); // BACK SPACE ����

	// �X�R�A�̋L�^����������֐�
	void LOAD_highscore(); // �Ǎ�
	void SAVE_highscore(); // �ۑ�

	void GAME_SET(); // �ݒ�
	void GAME_ALL(); // ����
	void GAME_TITLE(); // �^�C�g�����
	void GAME_SELECT(); // �I�����
	void GAME_PLAY(); // �v���C���
	void GAME_OVER(); // �I�[�o�[���
	void GAME_CLEAR(); // �N���A���
	void GAME_END(); // �I��
};

//-------------------------------------------------------------------------------------

Game* game; // Game �N���X�̃��������m�ہ@���́i�C���X�^���X�j��

//-------------------------------------------------------------------------------------
=======
	void ADD_list(ThingPointa&); // Thing クラス　スマートポインタにリスト（list）を追加する
	void ADD_score(int sc); // スコアを追加する
	bool PUSH_space(); // SPACE 操作
	bool PUSH_back(); // BACK SPACE 操作

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

Game* game; // Game クラスのメモリを確保して実体（インスタンス）化する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

// Thing クラスの実装
void Thing::remove() {

<<<<<<< HEAD
	remove_flag = true; // �폜�t���O�� true ��
=======
	remove_flag = true; // 削除フラグを true にする
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

Thing::Thing() {

<<<<<<< HEAD
	remove_flag = false; // �폜�t���O�� false ��
	pause_flag = false; // �|�[�Y�i�x�~�j�t���O�� false ��
=======
	remove_flag = false; // 削除フラグを false にする
	pause_flag = false; // ポーズ（休止）フラグを false にする
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Thing::SET_picture(const char* file_name, ThingType thing) {

<<<<<<< HEAD
	// loaded_picture �͂O�̏ꍇ�@LoadGraph ������
=======
	// loaded_picture は０の場合　LoadGraph を実装する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (loaded_picture[thing] == 0) {

		loaded_picture[thing] = LoadGraph(file_name);
	}

<<<<<<< HEAD
	hit_w = m_w; // ������ hit_w ��
	hit_h = m_h; // �c���� hit_ h ��
	hit_x = hit_y = 0; // ������W���O��
=======
	hit_w = m_w; // 横幅　当たり判定に置く
	hit_h = m_h; // 縦幅　当たり判定に置く
	hit_x = hit_y = 0; // 当たり判定　左上座標を０にする
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Thing::SET_sound(const char* file_name, Sound sound) {

<<<<<<< HEAD
	// loaded_sound �͂O�̏ꍇ�@LoadSoundMem ������
=======
	// loaded_sound は０の場合　LoadSoundMem を実装する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (loaded_sound[sound] == 0) {

		loaded_sound[sound] = LoadSoundMem(file_name);
	}
}

void Thing::SET_position(int position_x, int position_y) {

<<<<<<< HEAD
	m_x = position_x; // �ݒ�l�� m_x�ix ���W�j ��
	m_y = position_y; // �ݒ�l�� m_y�iy ���W�j��
=======
	m_x = position_x; // 設定値を m_x（x 座標） に入れる
	m_y = position_y; // 設定値を m_y（y 座標）に入れる
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Thing::SET_hitarea(int h_x, int h_y, int h_w, int h_h) {

<<<<<<< HEAD
	hit_x = h_x; // ���ΓI x ���W��ݒ�
	hit_y = h_y; // ���ΓI y ���W��ݒ�
	hit_w = h_w; // ������ݒ�
	hit_h = h_h; // �c����ݒ�
=======
	hit_x = h_x; // 相対的 x 座標を設定する
	hit_y = h_y; // 相対的 y 座標を設定する
	hit_w = h_w; // 横幅を設定する
	hit_h = h_h; // 縦幅を設定する
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
	// ����(m_x, m_y)					�E��(m_x + m_w, m_y)
	// ����(m_x, m_y + m_h)		�E��(m_x + m_w, m_y + m_h)
	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[GET_TYPE()], TRUE); // TRUE �͉摜�̖��F���N���A��
=======
	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[GET_TYPE()], TRUE); // 座標位置に描画する　TRUE は画像バックをクリアにする
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
	// �摜���m�̓����蔻����W
	int x_1 = m_x + hit_x; // x ���W
	int y_1 = m_y + hit_y; // y ���W
	int w_1 = hit_w; // ����
	int h_1 = hit_h; // �c��

	// �Ή����铖���蔻����W
	int x_2 = other->m_x + other->hit_x; // x ���W
	int y_2 = other->m_y + other->hit_y; // y ���W
	int w_2 = other->hit_w; // ����
	int h_2 = other->hit_h; // �c��

	// �����蔻��
=======
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
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (x_2 < x_1 + w_1 &&
		x_1 < x_2 + w_2 &&
		y_2 < y_1 + h_1 &&
		y_1 < y_2 + h_2) return true;

	return false; // 上記以外は false に
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Player �N���X�̎���
=======
// Player クラスの実装
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Player::Player() {

	m_w = 80; // 横幅
	m_h = 50; // 縦幅
	m_s = 8; // 速度

<<<<<<< HEAD
	// �摜��ݒ�
=======
	// 画像を設定する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	SET_picture("PLAYER.png", TYPE_PLAYER);
	SET_picture("HEART.png", TYPE_HEART);
	SET_picture("ENERGY.png", TYPE_ENERGY);

<<<<<<< HEAD
	SET_position(150, 300); // x�Ey ���W��ݒ�
	SET_hitarea(10, 10, 70, 40); // �����蔻���ݒ�
	life_max = 5; // ���C�t��ݒ�
	life_now = life_max; // ���C�t�̒l��ݒ胉�C�t��
	energy_max = 1; // ����͂�ݒ�
	energy_now = energy_max; // ����͂̒l��ݒ����͂�
	damage = 0; // ���Q��
	energy = 0; // �����
	shot_flag = false; // shot �t���O�� false ��
	beam_flag = false; // beam �t���O�� false ��
	dead_time = 0; // deat_time ���O��
	SET_sound("SHOT1.mp3", SOUND_SHOT1); // Shot ��
	SET_sound("E ATTACK.mp3", SOUND_E_ATTACK); // ���Q��
=======
	SET_position(150, 300); // x・y 座標を設定する
	SET_hitarea(10, 10, 70, 40); // 当たり判定を設定する
	life_max = 5; // 初期ライフを設定する
	life_now = life_max; // 今のライフに初期ライフを置く
	energy_max = 1; // 初期特殊力を設定する
	energy_now = energy_max; // 今の特殊力に初期特殊力を置く
	damage = 0; // 損害量
	energy = 0; // 特殊量
	shot_flag = false; // shot フラグを false にする
	beam_flag = false; // beam フラグを false にする
	dead_time = 0; // deat_time を０に設定（点滅用）
	SET_sound("SHOT1.mp3", SOUND_SHOT1); // Shot 音
	SET_sound("E ATTACK.mp3", SOUND_E_ATTACK); // 損害音
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
				ThingPointa shot(new Shot); // Shot �N���X�쐬�@���̃A�h���X�� Thing �N���X�̃X�}�[�g�|�C���^�ɓn��
				shot->SET_position(m_x + m_w - 10, m_y + 25); // Shot �̍��W��ݒ�
				game->ADD_list(shot); // Thing ���X�g�� Shot �A�h���X��ǉ�
				PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK); // Shot ��
=======
				ThingPointa shot(new Shot); // Shot クラス作成　そのアドレスを Thing クラスのスマートポインタに渡す
				shot->SET_position(m_x + m_w - 10, m_y + 25); // Shot の初期位置を設定する
				game->ADD_list(shot); // Thing リストに Shot アドレスを追加する
				PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK); // Shot 音
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
					for (int i = 0; i < 7; i++) { // �V��

						ThingPointa spray_shot1(new Spray_Shot);
						spray_shot1->SET_position(m_x + m_w - 10, m_y + 25);
						spray_shot1->SET_angle(3.14 * (3 - i) / 18); // �U�z����p�x�i�R�O���E�Q�O���E�P�O���E�O���j���㉺�ɐݒ�
=======
					for (int i = 0; i < 7; i++) { // ７個発射する

						ThingPointa spray_shot1(new Spray_Shot);
						spray_shot1->SET_position(m_x + m_w - 10, m_y + 25);
						spray_shot1->SET_angle(3.14 * (3 - i) / 18); // 散布する角度（３０°・２０°・１０°・０°）を上下に設定する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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
					rasen_Shot_1->SET_sign(1); // �v���X��
					game->ADD_list(rasen_Shot_1);

					// 下
					ThingPointa rasen_Shot_2(new Rasen_Shot);
					rasen_Shot_2->SET_position(m_x + m_w - 10, m_y + 25);
					rasen_Shot_2->SET_sign(-1); // �}�C�i�X��
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

<<<<<<< HEAD
		// �������e�i�o�j
=======
		// 追尾・放物線弾（Ｐ）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
		// �S�Ă̒e���g�p��
=======
		// 全ての弾を使用可にする
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		else if (CheckHitKey(KEY_INPUT_Q)) energy_now = 10;

		else {

			shot_flag = false; // shot フラグを falseに
			beam_flag = false; // beam フラグ を false に
			charge_time = 0; // charge_time を０に
		}
	}

<<<<<<< HEAD
	// ���C�t�O�̏ꍇ
	if (life_now <= 0) {

		scene = 3; // �I�[�o�[��ʂ�
		StopSoundMem(Play_m); // �v���C��ʂ̉����~
		StopSoundMem(Boss_m); // �{�X��ʂ̉����~
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // �I�[�o�[��ʂ̉����Đ�
=======
	// ライフ０になった場合
	if (life_now <= 0) {

		scene = 3; // オーバー画面へ
		StopSoundMem(Play_m); // プレイ中の音を停止する
		StopSoundMem(Boss_m); // ボス中の音を停止する
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // オーバー中の音を再生する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	}

	// ライフの上限設定
	if (10 <= life_now) life_now = 10;

	// 特殊量の上限設定
	if (10 <= energy_now) energy_now = 10;
}

void Player::heart_draw() {

	if (0 < life_now) {

<<<<<<< HEAD
		// �̗͂̒l�Ńn�[�g�̐��𒲐�
=======
		// 今の体力によりハートの数を調整する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		for (int i = 0; i < life_now; i++) {

			DrawExtendGraph(5 + i * 45, 5, 55 + i * 45, 45, loaded_picture[TYPE_HEART], TRUE);
		}
	}
}

void Player::energy_draw() {

	if (0 < energy_now) {

<<<<<<< HEAD
		// ����ʂ̒l�Ńn�[�g�̐��𒲐�
=======
		// 今の特殊量によりハートの数を調整する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		for (int i = 0; i < energy_now; i++) {

			DrawExtendGraph(460 + i * 45, 5, 510 + i * 45, 45, loaded_picture[TYPE_ENERGY], TRUE);
		}
	}

<<<<<<< HEAD
	// ����ʂ̒l�Łi�n�[�g�̏�Ɂj������`��
	int color = GetColor(255, 255, 255); // �F��ݒ�

	DrawFormatString(480, 15, color, "B");
	// ����ʂQ�`�P�O�ȏ�̏ꍇ
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
	// 今の特殊量により（ハートの上に）文字を描画する
	int color = GetColor(255, 255, 255); // 色
	DrawFormatString(480, 15, color, "B");

	// 特殊量２～１０以上の場合
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
	heart_draw(); // �̗͂�`��
	energy_draw(); // ����ʂ�`��

	if (dead_time % 5 == 0) Thing::draw(); // �T�Ŋ���؂��ꍇ�@�_�łŕ`��
=======
	heart_draw(); // 体力を描画する
	energy_draw(); // 特殊量を描画する

	if (dead_time % 5 == 0) Thing::draw(); // ５で割り切れる場合　点滅して描画する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Player::hit(int damage, int energy) {

	// 敵の場合
	if (dead_time <= 0 && 0 < damage) {

<<<<<<< HEAD
		dead_time = 50; // dead_time ���T�O��
		life_now -= damage; // �̗͂��}�C�i�X����
		PlaySoundMem(loaded_sound[SOUND_E_ATTACK], DX_PLAYTYPE_BACK); // ���Q��
	}

	// HEAL1 �̏ꍇ
	if (damage < 0) life_now -= damage; // �̗͂̒ǉ�

	// HEAL2 �̏ꍇ
	if (energy < 0) energy_now -= energy; // ����ʂ̒ǉ�
}

//-------------------------------------------------------------------------------------

// Shot �N���X�i�ʏ�e�j�̎���
Shot::Shot() {

	m_w = 12; // ����
	m_h = 12; // �c��
	m_s = 10; // ���x
	damage = 5; // ���Q��
	SET_picture("SHOT1.png", TYPE_SHOT1); // �摜
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK); // ��
=======
		dead_time = 50; // 点滅カウントを５０に
		life_now -= damage; // 体力をマイナスする
		PlaySoundMem(loaded_sound[SOUND_E_ATTACK], DX_PLAYTYPE_BACK); // 損害音
	}

	// HEAL1 の場合
	if (damage < 0) life_now -= damage; // 体力の増加

	// HEAL2 の場合
	if (energy < 0) energy_now -= energy; // 特殊量の増加
}

// Shot クラス（通常弾）の実装
Shot::Shot() {

	m_w = 12; // 横幅
	m_h = 12; // 縦幅
	m_s = 10; // 速度
	damage = 5; // 損害量
	SET_picture("SHOT1.png", TYPE_SHOT1); // 画像
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK); // 効果音
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
	if (!pause_flag) m_x += m_s; // ���x���P�O��

	if (Game::WIDTH < m_x) remove(); // ��ʍ��ō폜
=======
	if (!pause_flag) m_x += m_s; // 速度を１０にする

	if (Game::WIDTH < m_x) remove(); // 画面左で削除する
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

// Through Shot �N���X�i�ђʒe�j�̎���
=======
// Through Shot クラス（貫通弾）の実装
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
	if (!pause_flag) m_x += m_s; // ���x���Q�O��
=======
	if (!pause_flag) m_x += m_s; // 速度を２０にする
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	if (Game::WIDTH < m_x + m_w) remove();
}

void Through_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Through_Shot::hit(int damage, int energy) {

<<<<<<< HEAD
	// �ђʂ���� remove �֐��͎����~
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Beam �N���X�i�����j�̎���
Beam::Beam() {

	m_w = 0; // �L������ׂO��
=======
	// 貫通する為 remove()関数は実装しない
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// Beam クラス（光線）の実装
Beam::Beam() {

	m_w = 0; // 初期は０に
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
		hit_w = m_w; // �����𓖂��蔻���
=======
		hit_w = m_w; // 当たり判定に置換する
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

// Vortex Shot �N���X�i�Q�e�j�̎���
=======
// Vortex Shot クラス（渦弾）の実装
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Spray Shot �N���X�i�U�z�e�j�̎���
=======
// Spray Shot クラス（散布弾）の実装
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
	angle = a; // �������p�x��
=======
	angle = a; // 角度に置く
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

// Rasen Shot1�E2 �N���X�i�����e�j�̎���
=======
// Rasen Shot1・2 クラス（螺旋弾）の実装
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
	sign = s; // �����𕄍���
=======
	sign = s; // 符号に置く
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
	// ���̓I�ɕ`��
=======
	// 大きさを随時変更する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	DrawExtendGraph(m_x, m_y, m_x + m_w * (1.2 - sign * cos(angle)) / 2, m_y + m_h * (1.2 - sign * cos(angle)) / 2, loaded_picture[TYPE_SHOT1], TRUE);
}

void Rasen_Shot::hit(int damage, int energy) {

	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Charge Shot �N���X�i�g��e�j�̎���
=======
// Charge Shot クラス（拡大弾）の実装
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

		// �u�n�v�������ꍇ
		if (CheckHitKey(KEY_INPUT_O)) {

<<<<<<< HEAD
			// �З͐������T�O�Ɂi���Q�ʂ͂O�ɂ��Ă���ׁj
=======
			// アタックMAXを５０にする（初期損害量は０にしているため）
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			if (damage < 50) {

				damage++;

				m_x += 1;
				m_y -= 2;
<<<<<<< HEAD
				m_w = 2 * damage; // ���Q�ʂɔ����g��
				m_h = 4 * damage;

				// �����蔻��̌덷����
=======
				m_w = 2 * damage; // 損害量に伴い大きくなる
				m_h = 4 * damage;

				// 当たり判定の誤差訂正をする
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
=======
		// 「Ｏ」を押していない場合
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		else {

			charge_flag = true;
			StopSoundMem(loaded_sound[SOUND_CHARGE]);
			PlaySoundMem(loaded_sound[SOUND_CHARGE_SHOT], DX_PLAYTYPE_BACK);
		}
	}

<<<<<<< HEAD
	else if (!pause_flag) m_x += m_s; // ���x���P�T��
=======
	else if (!pause_flag) m_x += m_s; // 速度を１５にする
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	if (Game::WIDTH < m_x) remove();
}

void Charge_Shot::draw() {

<<<<<<< HEAD
	// angle �̒l���Q�Ŋ���؂��ꍇ�@�`��
=======
	// angle の値を２で割り 余り０場合　描画する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if ((int)angle % 2 == 0) {

		DrawRotaGraph((2 * m_x + m_w) / 2, (2 * m_y + m_h) / 2, (double)m_w / 50, angle, loaded_picture[TYPE_CHARGE_SHOT], TRUE);
	}

<<<<<<< HEAD
	if (!pause_flag) angle += 30; // angle �̒l�ɂR�T�v���X����
=======
	if (!pause_flag) angle += 30; // angle の値に３５足し続ける
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Charge_Shot::hit(int damage, int energy) {

	remove();
	StopSoundMem(loaded_sound[SOUND_CHARGE]);
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot1 �N���X�i�����e�j�̎���
=======
// Period Shot1 クラス（時限弾）の実装
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Period_Shot1::Period_Shot1() {

	m_w = 15;
	m_h = 15;
	m_s = 12;
	damage = 0;
<<<<<<< HEAD
	shot_time = 30; // ���˂܂ł̎��Ԃ��R�O��
	shot_count = 1; // �T�񔭎˂���ׂP��
=======
	shot_time = 30; // 発射するまでの時間を３０に
	shot_count = 1; // ５回発射するために 初期は１に
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	SET_picture("SHOT3.png", TYPE_SHOT3);
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK);
}

ThingType Period_Shot1::GET_TYPE() {

	return TYPE_SHOT3;
}

ThingType Period_Shot1::HIT_TYPE() {

<<<<<<< HEAD
	return TYPE_NONE; // �{�̂ɓ����蔻��~
=======
	return TYPE_NONE; // 本体には当たり判定×
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Period_Shot1::move() {

	if (!pause_flag) {

<<<<<<< HEAD
		if (0 <= shot_time) m_x += m_s; // ���˂܂ŉE������
=======
		if (0 <= shot_time) m_x += m_s; // 発射するまで右方向へ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

		if (shot_time < 0) {

			// ５回発射
			if (shot_time % 10 == 0 && shot_count <= 5) {

<<<<<<< HEAD
				// �����蔻����e�𔭎�
				// ������
=======
				// 当たり判定◯　弾を発射する
				// 下方向
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
			if (5 < shot_count) remove(); // �T���ō폜
=======
			if (5 < shot_count) remove(); // ５回目で削除する
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
void Period_Shot1::hit(int damage, int energy) {} // 当たり判定×
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

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

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Period Shot3�i���E�j�N���X�̎���
=======
// Period Shot3（左右）クラスの実装
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

// Homing Shot �N���X�i�ǔ��e�j�̎���
=======
// Homing Shot クラス（追尾弾）の実装
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Homing_Shot::Homing_Shot() {

	m_w = 12;
	m_h = 12;
	m_s = 10;
	damage = 20;
<<<<<<< HEAD
	shot_s = 10; // shot_s ���P�O��
=======
	shot_s = 10; // shot_s を10にする
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Homing_Shot::move() {

	if (!pause_flag) {

<<<<<<< HEAD
		// �c��G���̏ꍇ
		if (0 < enemy_num) {

			// �ǔ��̌v�Z
			// sqrt() �͐�Βl
			// pow() �ׂ͂���
			// ���̑��x�Œǔ�
=======
		// 残る敵◯
		if (0 < enemy_num) {

			// 追尾する計算
			// sqrt() は絶対値の計算
			// pow() はべき乗の計算
			// 一定の速度で追尾する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			m_x += ((enemy_x - m_x) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
			m_y += ((enemy_y - m_y) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
		}

<<<<<<< HEAD
		else m_x += m_s; // �c��G�~�̏ꍇ�@�E������
=======
		else m_x += m_s; // 残る敵× 右方向へ
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

// Parabola Shot �N���X�i�������e�j�̎���
=======
// Parabola Shot クラス（追尾・放物線弾）の実装
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Parabola_Shot::Parabola_Shot() {

	m_w = 12;
	m_h = 12;
	damage = 50;
<<<<<<< HEAD
	m_s = 0; // shot_s ���O��
=======
	m_s = 0; // shot_s を 0に
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

void Parabola_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;

<<<<<<< HEAD
	// �s��v�Z�ŎO�_�̍��W���v�Z
=======
	// 行列計算で三点の座標を求める
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	float frame = (enemy_x - center_x) / (8 + enemy_s);

	// 弾・敵を入れる３点の座標
	float x_1 = center_x;
	float x_2 = enemy_x - enemy_s * frame;
	float x_3 = center_x + 1;

	float y_1 = center_y;
	float y_2 = enemy_y;
<<<<<<< HEAD
	float y_3 = center_y - tan(3.14 / 3); // �p�x�U�O����
=======
	float y_3 = center_y - tan(3.14 / 3); // 角度６０°で上昇する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

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
<<<<<<< HEAD
		m_y = a * pow(m_x, 2) + b * m_x + c; // �������ŕ`��
=======
		m_y = a * pow(m_x, 2) + b * m_x + c; // 放物線に描画する
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

// ENEMY1�`6�N���X�̎���
=======
// ENEMY1～6クラスの実装
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Enemy1::Enemy1() {

	m_w = 80;
	m_h = 50;

<<<<<<< HEAD
	// STAGE �̒l�ő��x��ݒ�
	if (stage <= 6) m_s = 8;
	if (7 <= stage) m_s = 10;

	life_max = 10; // �̗͂P�O��
	life_now = life_max; // �̗͂̒l��ݒ�̗͂�
	damage = 1; // ���Q�ʂP��
	energy = 0; // ����ʂO��
	count = 0; // �̗� != 0 �� count ���O��
	count_flag = false; // �̗� != 0 �� count �t���O�� false ��
	SET_picture("ENEMY1.png", TYPE_ENEMY1);
	SET_picture("BURN.png", TYPE_BURN);
	SET_sound("BREAK.mp3", SOUND_BREAK);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h)); // ���W
=======
	// STAGEにより速度を設定
	if (stage <= 6) m_s = 8;
	if (7 <= stage) m_s = 10;

	life_max = 10; // 体力１０
	life_now = life_max; // 設定体力を現在の体力に入れる
	damage = 1; // 損害量１
	energy = 0; // 特殊量０
	count = 0; // 体力 != 0 で count を０に
	count_flag = false; // 体力 != 0 で count フラグは false に
	SET_picture("ENEMY1.png", TYPE_ENEMY1);
	SET_picture("BURN.png", TYPE_BURN);
	SET_sound("BREAK.mp3", SOUND_BREAK);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h)); // 初期位置
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
	// Homing�EParabola Shot�N���X�i�ǔ��e�E�������e�j����������ׁ@�l���O���[�o���ϐ���
=======
	// Homing・Parabola Shotクラス（追尾弾）を実装する為　グローバル変数に値を入れる
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy1::draw() {

<<<<<<< HEAD
	life_draw(); // �̗͂�`��
=======
	life_draw(); // 体力を描画する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY1], TRUE);
	}

	// 爆破後 count には１３・count_flag は move() で true に
	if (count_flag && 0 <= count) {

<<<<<<< HEAD
		// ���j�G�t�F�N�g��`��
		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		// count <= 0 �̏ꍇ�@�폜
		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200); // �X�R�A��ǉ�
=======
		// 爆破エフェクトを描画する
		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		// count <= 0 の場合　削除する
		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200); // スコアに得点を追加する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

			if (0 < enemy_num) enemy_num -= 1; // enemy_num をマイナスする
		}
	}
}

void Enemy1::hit(int damage, int energy) {

	life_now -= damage; // 体力をマイナスする

<<<<<<< HEAD
	// �̗͂O�̏ꍇ�@���j�G�t�F�N�g������
	if (life_now <= 0 && count == 0) {

		count = 13; // count ���P�R��
=======
	// 体力０の場合　爆破エフェクトを実装する
	if (life_now <= 0 && count == 0) {

		count = 13; // count に１３の値を入れる
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

<<<<<<< HEAD
				ThingPointa enemy_shot2(new Enemy_Shot2); // Enemy Shot2 �N���X�쐬�@���̃A�h���X�� Thing �N���X�̃X�}�[�g�|�C���^�ɓn��
				enemy_shot2->SET_position(m_x - 10, m_y + 25); // ���W
				game->ADD_list(enemy_shot2); // Thing ���X�g�� Enemy Shot2 �A�h���X��ǉ�
=======
				ThingPointa enemy_shot2(new Enemy_Shot2); // Enemy Shot2 クラス作成　そのアドレスを Thing クラスのスマートポインタに渡す
				enemy_shot2->SET_position(m_x - 10, m_y + 25); // 初期位置
				game->ADD_list(enemy_shot2); // Thing リストに Enemy Shot2 アドレスを追加する
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
		// ��ʂ̓����蔻��
		if (m_y < 0) up_down = -up_down; // ��
		if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // ��
		if (m_x < 0) m_s = -2; // ��
		if (Game::WIDTH + 200 < m_x + m_w) remove(); // ��ʉE�ō폜
=======
		// 画面の当たり判定
		if (m_y < 0) up_down = -up_down; // 上
		if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // 下
		if (m_x < 0) m_s = -2; // 左
		if (Game::WIDTH + 200 < m_x + m_w) remove(); // 画面右で削除する
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

// ENEMY BOSS1�E2�N���X�̎���
=======
// ENEMY BOSS1・2クラスの実装
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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
<<<<<<< HEAD
	up_down = 3; // �㉺�������x���R��
	add_speed = 0; // �̗͔����ɂȂ�܂ŉ����͂O��
	count = 0;
	count_flag = false;

	// STAGE�̒l�ŉ摜��ݒ�
=======
	up_down = 3; // 上下向き速度
	add_speed = 0; // 体力が半分になるまで加速は０に
	count = 0;
	count_flag = false;

	// STAGEにより描画する画像を設定
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (stage <= 3) SET_picture("ENEMY BOSS1.png", TYPE_ENEMY_BOSS1);
	if (4 <= stage && stage <= 6) SET_picture("ENEMY BOSS2.png", TYPE_ENEMY_BOSS2);
	if (7 <= stage && stage <= 9) SET_picture("ENEMY BOSS3.png", TYPE_ENEMY_BOSS3);

	SET_hitarea(150, 50, 340, 340); // 当たり判定の設定
	Warn_p = LoadGraph("WARNING.png"); // WARNING!!
	SET_position(Game::WIDTH, 140);
}

void Enemy_Boss1::move() {

<<<<<<< HEAD
	// �̗͔����ȉ��̏ꍇ�@���x���㏸
=======
	// 体力が半分以下の場合　速度を上げる
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (life_now < life_max / 2) add_speed = 3;

	if (!pause_flag) {

<<<<<<< HEAD
		// ���̍��W�܂ō�����
=======
		// 一定の座標まで左向き
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
		// ���̍��W�̏ꍇ�@�㉺����
=======
		// 一定の座標の場合　上下向き
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		if (m_x <= 790) {

			m_y += up_down;

			// 画面の当たり判定
			if (m_y + hit_y + 100 < 0) up_down = 4 + add_speed;
			if (Game::HEIGHT + 100 < m_y + hit_h) up_down = -(4 + add_speed);

			if (GetRand(30) == 0) {

				// �^��
				ThingPointa enemy_shot1_1(new Enemy_Shot1);
				enemy_shot1_1->SET_position(m_x + m_w - 250, m_y + 190);
				game->ADD_list(enemy_shot1_1);

				// ��
				ThingPointa enemy_shot1_2(new Enemy_Shot1);
				enemy_shot1_2->SET_position(m_x + m_w - 210, m_y + 220);
				game->ADD_list(enemy_shot1_2);

				// ��
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

<<<<<<< HEAD
		// STAGE�̒l�ŉ摜��ݒ�
=======
		// STAGEにより画像を設定
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

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// Enemy Shot1 �N���X�i�{�X�j�̎���
=======
// Enemy Shot1 クラス（ボス）の実装
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

// Enemy Shot2 �N���X�iENEMY5�E6�j�̎���
=======
// Enemy Shot2 クラス（ENEMY5・6）の実装
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

// HEAL1�i�̗͉񕜁j�N���X�̎���
=======
// HEAL1（体力回復）クラスの実装
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Heal1::Heal1() {

	m_w = 25;
	m_h = 21;
	m_s = 6;
<<<<<<< HEAD
	damage = -1; // �l�̓}�C�i�X�ɂ��ĉ񕜂�
=======
	damage = -1; // 値はマイナスにして回復にする
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

// HEAL2�i����ʉ񕜁j�N���X�̎���
=======
// HEAL2（特殊量回復）クラスの実装
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
Heal2::Heal2() {

	m_w = 25;
	m_h = 21;
	m_s = 10;
	damage = 0;
<<<<<<< HEAD
	energy = -1; // �l���}�C�i�X�ɂ��ē���ʉ񕜂�
=======
	energy = -1; // 値をマイナスにして特殊量回復にする
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

// Game �N���X�̎���
void Game::ADD_list(ThingPointa & add) {

	thing_list.push_back(add); // Thing ���X�g�� back �� Thing �N���X�� add ��ǉ�
=======
// Game クラスの実装
void Game::ADD_list(ThingPointa & add) {

	thing_list.push_back(add); // Thing リストの下に Thing クラスの add を追加する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
	game = this; // ���C���X�^���X�̃A�h���X��ێ��i�ÓI�j
	scene = 0; // �^�C�g����ʂ�
	stage = 0; // STAGE���O��
	score = 0; // �X�R�A���O��
	p_x = 0; // �o�b�N�� x ���W������ɐݒ�
	p_w = WIDTH; // �o�b�N�̉����� WIDTH ��
	limit_time = 600; // �������Ԃ��U�O�O��

	LOAD_highscore(); // �X�R�A�̓Ǎ�

	ChangeWindowMode(TRUE); // �E�B���h�E���J��
	SetGraphMode(WIDTH, HEIGHT, 32); // �E�B���h�E�̉����E�c���E�J���[�ݒ�
	DxLib_Init(); // DX���C�u������������
	SetDrawScreen(DX_SCREEN_BACK); // �E���ɉ摜��`��
=======
	game = this; // 自インスタンスのアドレスを保持する（静的）
	scene = 0; // タイトル画面へ
	stage = 0; // STAGEを０にする
	score = 0; // スコアを０に
	p_x = 0; // バックの x 座標を左上に設定
	p_w = WIDTH; // バックの横幅を WIDTH に置換
	limit_time = 600; // 制限時間を６００に

	LOAD_highscore(); // スコアの読込
	start_time = GetNowCount(); // １s 単位にする

	ChangeWindowMode(TRUE); // ウィンドウを開く
	SetGraphMode(WIDTH, HEIGHT, 32); // ウィンドウの横幅・縦幅・カラーの設定
	DxLib_Init(); // DXライブラリを初期化する
	SetDrawScreen(DX_SCREEN_BACK); // ウラに画像を描画
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

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

<<<<<<< HEAD
	PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // �^�C�g����ʂ̉����Đ�
=======
	PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // タイトル音再生
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
}

//-------------------------------------------------------------------------------------

void Game::GAME_ALL() {

<<<<<<< HEAD
	// �C�x���g�����̎����֐�
=======
	// イベント処理を実装する関数
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 0 �̏ꍇ�@�^�C�g�����
void Game::GAME_TITLE() {

	SetBackgroundColor(0, 0, 0); // �o�b�N�̐F�����F�ɐݒ�
	DrawExtendGraph(10, 200, WIDTH - 10, HEIGHT - 200, Title_p, TRUE); // �^�C�g��
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE
=======
// scene == 0 の時　タイトル画面にする
void Game::GAME_TITLE() {

	SetBackgroundColor(0, 0, 0); // バックの色を黒色に設定
	DrawExtendGraph(10, 200, WIDTH - 10, HEIGHT - 200, Title_p, TRUE); // タイトルの描画
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE の描画
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	// 文字の描画
	SetFontSize(20); // サイズの設定
	DrawFormatString(10, 10, GetColor(255, 255, 255), "B E S T  S C O R E : %d", high_score);

<<<<<<< HEAD
	thing_list.clear(); // Thing ���X�g��������
	score = 0; // �X�R�A���O��
	add_s = 0; // �o�b�N�������ŉ�
	limit_time = 600; // �������Ԃ��U�O�O��

	// SPACE �������ꍇ�@�I����ʂ�
	if (PUSH_space()) scene = 1;

	play_flag = false; // �v���C�t���O�� false ��
	boss_flag = false; // �{�X�t���O�� false ��
	space_flag = false; // �X�y�[�X�t���O�� false ��
}

//-------------------------------------------------------------------------------------

// scene == 1 �̏ꍇ�@�I�����
=======
	thing_list.clear(); // Thing リストを初期化する
	score = 0; // スコアを０に
	add_s = 0; // バックを高速で回す

	// SPACE KEY を押した場合　SELECT画面へ
	if (PUSH_space()) scene = 1;

	game_flag = false; // game_flag を false に
	boss_flag = false; // ボスフラグを false に
	space_flag = false; // PUSH SPACE フラグを false に
}

// scene == 1 の時　選択画面
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 2 �ɐݒ�
=======
	// stage == 2 に設定
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_2)) {

		scene = 2;
		stage = 2; // STAGE２

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 3 �ɐݒ�
=======
	// stage == 3 に設定
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_3)) {

		scene = 2;
		stage = 3; // STAGE３

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 4 �ɐݒ�
=======
	// stage == 4 に設定
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_4)) {

		scene = 2;
		stage = 4; // STAGE４

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 5 �ɐݒ�
=======
	// stage == 5 に設定
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_5)) {

		scene = 2;
		stage = 5; // STAGE５

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 6 �ɐݒ�
=======
	// stage == 6 に設定
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_6)) {

		scene = 2;
		stage = 6; // STAGE６

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 7 �ɐݒ�
=======
	// stage == 7 に設定
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_7)) {

		scene = 2;
		stage = 7; // STAGE７

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 8 �ɐݒ�
=======
	// stage == 8 に設定
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_8)) {

		scene = 2;
		stage = 8; // STAGE８

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 9 �ɐݒ�
=======
	// stage == 9 に設定
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_9)) {

		scene = 2;
		stage = 9; // STAGE９

		ThingPointa player(new Player);
		ADD_list(player);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// stage == 10 �ɐݒ�
=======
	// stage == 10 に設定
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (CheckHitKey(KEY_INPUT_0)) {

		scene = 2;
		stage = 10; // STAGE１０

		ThingPointa player(new Player);
		ADD_list(player);
	}
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 2 �̏ꍇ�@�v���C���
=======
// scene == 2 の時　プレイ画面
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
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

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------

	// for_each�̓R���e�i�ilist etc.�j�� first-last �ɑ΂��Ċ֐��̓K�p������
	// �\���� [CAPTURE] (���������X�g) {�֐��̖{��}
	// Thing ���X�g�ɓ���S�ẴN���X�� move�֐����g�p
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->move(); });

	// Thing ���X�g�ɓ���S�ẴN���X�� draw�֐������g�p����
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->draw(); });

	// �����蔻��̎���
	// �͈͑S�ẴN���X�Ɋ֐����u���i�Q�Ɓj�v�Ɂ@�֐����� mob ���g�p�o����
	// �Q�̃N���X���g�p���Ă���ׁ@���̕����������̌`
	// ������ꍇ�@������ hit�֐���K�p
	for_each(thing_list.begin(), thing_list.end(), [&](ThingPointa & main) {

		if (main->HIT_TYPE() == TYPE_NONE) return; // TYPE_NONE �̏ꍇ�@����
=======
	// for_eachはコンテナ（list etc.）の first-last に対して関数の適用を実装する
	// 構文は [CAPTURE] (仮引数リスト) {関数の本体}
	// Thing リストに入る全てのクラスの move()関数をを使用する
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->move(); });

	// Thing リストに入る全てのクラスの draw()関数をを使用する
	for_each(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {Thing->draw(); });

	// 当たり判定の実装をする
	// 範囲全てのクラスに関数を「＆（参照）」にすることで 関数内で mob を使用出来る
	// ２個のクラスを使用しているため この部分だけこの形
	// 当たる場合 両方の hit()関数を適用する
	for_each(thing_list.begin(), thing_list.end(), [&](ThingPointa & main) {

		if (main->HIT_TYPE() == TYPE_NONE) return; // TYPE_NONEの場合　無視する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

		for_each(thing_list.begin(), thing_list.end(), [&](ThingPointa & mob) {

			// 両方の HIT タイプ・GET タイプを判別して 返すタイプの等しい場合
			if (main->HIT_TYPE() == mob->GET_TYPE()) {

				// 当たる場合
				if (main->HIT_test(mob)) {

<<<<<<< HEAD
					// hit�֐���K�p
					// ���Q�ʁE����ʂ̌v�Z�� GET_damage�֐��EGET_energy�֐����g�p
=======
					// hit()関数を適用する
					// 損害量・特殊量の計算に GET_damage()関数・GET_energy()関数を使用する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
					main->hit(mob->GET_damage(), mob->GET_energy());
					mob->hit(main->GET_damage(), main->GET_energy());
				}
			}
		});
	});

	// shot_count をプラスする
	shot_count++;

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------
=======
	// game_flag true の場合
	if (game_flag) {

		// 制限時間の計算
		timer = (GetNowCount() - start_time) / 1000 - limit_time;
		now_time = -timer;
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	// �v���C���̏ꍇ
	if (play_flag) {
		
		SetFontSize(20);
<<<<<<< HEAD
		DrawFormatString(WIDTH - 200, HEIGHT - 35, GetColor(255, 255, 255), "T I M E : %d", now_time); // �������Ԃ̕`��
	
		// �|�[�Y�i�x�~�j�t���O false �̏ꍇ�@�G�E�񕜂𐶐�
		if (!pause_flag) {

			// �������Ԃ̌v�Z
			now_time = (start_time - GetNowCount()) / 1000 + limit_time;

			// �X�R�A�Q�O�O�O�O�����̏ꍇ
			if (score < 20000) {

				//-------------------------------------------------------------------------------------
				// �G�̏o���iSTAGE�P�`�X�j

				// ENEMY1�i���ʁj
				if (stage == 1 || stage == 2 || stage == 3 || stage == 5 || stage == 6 || stage == 7) { // �o�� STAGE �ݒ�

					if (GetRand(40) == 0) {

						ThingPointa enemy1(new Enemy1); // �G����
						ADD_list(enemy1); // Thing ���X�g�� ENEMY1 �A�h���X��ǉ�
						if (0 <= enemy_num) enemy_num += 1; // enemy_num ��+�P
					}
				}

				//-------------------------------------------------------------------------------------
				// ENEMY2�i�^�t�j
=======
		DrawFormatString(WIDTH - 200, HEIGHT - 35, GetColor(255, 255, 255), "T I M E : %d", now_time); // 制限時間の描画

		// ポーズ（休止）フラグ falseである場合　敵・回復を生成
		if (!pause_flag) {

			// スコア２００００未満の場合
			if (score < 20000) {

				// 敵の出現（STAGE１～９）
				// ENEMY1（普通）
				if (stage == 1 || stage == 2 || stage == 3 || stage == 5 || stage == 6 || stage == 7) { // 出現する STAGE 設定

					if (GetRand(40) == 0) {

						ThingPointa enemy1(new Enemy1); // 敵生成
						ADD_list(enemy1); // Thing リストに ENEMY1 アドレスを追加

						if (0 <= enemy_num) enemy_num += 1; // enemy_num に+１する
					}
				}

				// ENEMY2（タフ）
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
				// ENEMY3�i�x�N�g���j
=======
				// ENEMY3（ベクトル）
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
				// ENEMY4�i�����j
=======
				// ENEMY4（高速）
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
				// ENEMY5�i�ʏ�U���j
=======
				// ENEMY5（通常攻撃）
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
				// ENEMY6�i�x�N�g���U���j
=======
				// ENEMY6（ベクトル攻撃）
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
			// STAGE�P�O

=======
			// STAGE１０
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
			// �X�R�A �Q�O�O�O�O�ȏ� ������ �{�X�t���O false �̏ꍇ�@�{�X�𐶐�
=======
			// スコア ２００００以上 そして ボスフラグ false の場合　ボスを生成する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			if (20000 <= score && !boss_flag) {

				boss_flag = true; // ボスフラグを true に

				if (boss_flag) {

<<<<<<< HEAD
					StopSoundMem(Play_m); // �v���C��ʂ̉����~
					PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP); // �{�X��ʂ̉����Đ�
=======
					StopSoundMem(Play_m); // プレイ中の音を停止する
					PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP); // ボス中の音を再生する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

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

<<<<<<< HEAD
			//-------------------------------------------------------------------------------------
			// ��ɐ����@ �񕜐���
=======
			// 常に生成する
			// 回復生成
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
		// �|�[�Y�i�x�~�j��ʂ�
		if (PUSH_back()) {

			if (!pause_flag) {

				stop_time = GetNowCount(); // ���ݎ��Ԃ𓾂�
				PlaySoundMem(Pause_m, DX_PLAYTYPE_BACK); // �|�[�Y��ʂ̉����Đ�
			}

			pause_flag = true;
			StopSoundMem(Play_m); // �v���C��ʂ̉����~
			StopSoundMem(Boss_m); // �{�X��ʂ̉����~
		}

		// �|�[�Y�i�x�~�j���
=======
		// ポーズ（休止）画面へ
		if (PUSH_back()) {

			if (!pause_flag) PlaySoundMem(Pause_m, DX_PLAYTYPE_BACK); // ポーズ音の再生する

			pause_flag = true;
			StopSoundMem(Play_m); // プレイ中の音を停止する
			StopSoundMem(Boss_m); // ボス中の音を停止する
		}

		// ポーズ（休止）画面を描画する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		if (pause_flag) {

			DrawBox(150, 150, WIDTH - 150, HEIGHT - 150, GetColor(255, 255, 255), TRUE);
			DrawExtendGraph(170, 170, WIDTH - 170, 240, Pause_p, TRUE);
			DrawExtendGraph(160, 330, WIDTH - 160, 420, Esc_p, TRUE);

<<<<<<< HEAD
			pause_time = (GetNowCount() - stop_time) / 1000; // �|�[�Y���Ԃ��v�Z
			
			//-------------------------------------------------------------------------------------
			// �|�[�Y�̏I���E�ĊJ
=======
			// ポーズの終了・再開する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
			if (PUSH_space()) {

				pause_flag = false;
				limit_time = pause_time + limit_time; // �|�[�Y���ԕ��v���X����
				pause_time = 0; // �O��

<<<<<<< HEAD
				// �{�X���o��̏ꍇ�@�v���C���̉����Đ�
				if (!boss_flag) PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP);

				// �{�X�o�ꒆ�̏ꍇ�@�{�X���̉����Đ�
=======
				// ボス未登場の場合　プレイ中の音を再生する
				if (!boss_flag) PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP);

				// ボスの場合　ボス中の音を再生する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
				if (boss_flag) PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP);
			}
		}

<<<<<<< HEAD
		//-------------------------------------------------------------------------------------
		// �v���C���Ă���ԁ@��ʍ��[�ɕ�����`��
		else DrawFormatString(50, HEIGHT - 35, GetColor(255, 255, 255), "B A C K  S P A C E : P A U S E");
	}

	//-------------------------------------------------------------------------------------
	// �v���C�O�@������`��
	else {

		// B �������ꍇ�@PUSH SPACE ��`��
		if (CheckHitKey(KEY_INPUT_B)) space_flag = true; // �X�y�[�X�t���O�� true ��
		if (space_flag) DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

		// ����m�F�@������`��
		DrawFormatString(600, 140, GetColor(255, 255, 255), "�� O P E R A T I N G  M E T H O D ��");
=======
		// プレイしている間　画面左端に文字を描画する
		else DrawFormatString(50, HEIGHT - 35, GetColor(255, 255, 255), "B A C K  S P A C E : P A U S E");
	}

	// game_flag　false の場合　文字を描画する
	else {

		// B を押した場合　PUSH SPACE を描画する
		if (CheckHitKey(KEY_INPUT_B)) space_flag = true;
		if (space_flag) DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

		// 操作　文字を描画する
		DrawFormatString(600, 140, GetColor(255, 255, 255), "■ O P E R A T I N G  M E T H O D ■");
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		DrawFormatString(600, 170, GetColor(0, 255, 255), "B : S H O T");
		DrawFormatString(600, 200, GetColor(255, 255, 255), "E L S E : S P E C I A L  S H O T");
		DrawFormatString(600, 230, GetColor(0, 255, 255), "S C O R E : 2 0 0 0 0");

		DrawFormatString(600, 320, GetColor(255, 255, 255), "■ H I N T ■");
		DrawFormatString(600, 350, GetColor(0, 255, 255), "I F  Y O U  G E T  T H E  B L U E  H E A R T");
		DrawFormatString(600, 380, GetColor(0, 255, 255), "Y O U  C A N  U S E  S P E C I A L  S H O T ...");

<<<<<<< HEAD
		//-------------------------------------------------------------------------------------
		// SPACE �������ꍇ�@�v���C�X�^�[�g
		if (PUSH_space()) {

			StopSoundMem(Title_m); // �^�C�g����ʂ̉����~
			PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP); // �v���C��ʂ̉����Đ�
			play_flag = true; // �v���C�t���O�� true ��
			start_time = GetNowCount(); // �������Ԃ��X�^�[�g
		}
	}

	//-------------------------------------------------------------------------------------
	// �{�X���o��̏ꍇ�@�X�R�A������
=======
		// SPACE KEY を押した場合　プレイスタートする
		if (PUSH_space()) {

			StopSoundMem(Title_m); // タイトル中の音を停止する
			PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP); // プレイ中の音を再生する
			game_flag = true; // game_flag を trueにする
			start_time = GetNowCount(); // 時間経過をスタートする
		}
	}

	// ボス未登場の場合　スコアを示す
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (!boss_flag) {

		SetFontSize(20);
		DrawFormatString(WIDTH - 220, 15, GetColor(255, 255, 255), "S C O R E : %d", score);
	}

<<<<<<< HEAD
	//-------------------------------------------------------------------------------------
	// ESC �������ꍇ�@�^�C�g����ʂ�
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {

		scene = 0; // �^�C�g����ʂ�
		StopSoundMem(Title_m); // �^�C�g����ʂ̉����~
		StopSoundMem(Play_m); // �v���C��ʂ̉����~
		StopSoundMem(Boss_m); // �{�X��ʂ̉����~
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // �^�C�g����ʂ̉����Đ�
	}

	//-------------------------------------------------------------------------------------
	// �X�R�A�̏���i�Q�O�O�O�O�ɐݒ�j
	if (20000 <= score) score = 20000;

	//-------------------------------------------------------------------------------------
	// �������ԂO�̏ꍇ
	if (now_time < 0) {

		scene = 3; // �I�[�o�[��ʂ�
		StopSoundMem(Play_m); // �v���C��ʂ̉����~
		StopSoundMem(Boss_m); // �{�X��ʂ̉����~
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // �I�[�o�[��ʂ̉����Đ�
	}

	//-------------------------------------------------------------------------------------
	// Thing ���X�g���ŏ����F�u�폜�t���O true �v�̃N���X��������iremove_if �֐��j
	// �폜�t���O true �̃N���X��O��
	// ������ ���̃N���X�� list.erase �� Thing ���X�g�ō폜�E���X�g�����񂹂�
=======
	// ESC を押した場合　タイトル画面へ戻る
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {

		scene = 0;
		StopSoundMem(Title_m); // タイトル中の音を停止する
		StopSoundMem(Play_m); // プレイ中の音を停止する
		StopSoundMem(Boss_m); // ボス中の音を停止する
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // タイトル中の音を再生する
	}

	// スコアの上限（２００００に設定）
	if (20000 <= score) score = 20000;

	// 制限時間０になった場合
	if (now_time < 0) {

		scene = 3; // オーバー画面へ
		StopSoundMem(Play_m); // プレイ中の音を停止する
		StopSoundMem(Boss_m); // ボス中の音を停止する
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // オーバー中の音を再生する
	}

	// Thing リスト内で条件：削除フラグ true のクラスを除ける（remove_if 関数）
	// 削除フラグ true のクラスを前にする
	// そして そのクラスを list.erase により Thing リストで削除・リスト内を詰める
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	auto end = remove_if(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {return Thing->GET_remove(); });
	thing_list.erase(end, thing_list.end());
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 3 �̏ꍇ�@�I�[�o�[���
=======
// scene == 3 の時　オーバー画面
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
void Game::GAME_OVER() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Over_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

<<<<<<< HEAD
	now_score = score; // �X�R�A��
=======
	now_score = score; // スコアに置換する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Y O U R  S C O R E : %d", now_score);

<<<<<<< HEAD
	// �n�C�X�R�A���X�R�A�̏ꍇ
	if (high_score < now_score) {

		// �l���㏑���E�L�^
=======
	// ハイスコアよりスコアが大きい場合
	if (high_score < now_score) {

		// 値を上書き・記録する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		high_score = now_score;
		SAVE_highscore();
	}

<<<<<<< HEAD
	// SPACE �������ꍇ�@�^�C�g����ʂ�
=======
	// SPACE KEY を押した場合　タイトル画面へ戻る
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Over_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// scene == 4 �̏ꍇ�@�N���A���
=======
// scene == 4 の時　クリア画面
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
void Game::GAME_CLEAR() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Clear_p, TRUE);
<<<<<<< HEAD
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE

	// �X�R�A��
	// �X�R�A�@���@���ԃX�R�A�@�{�@�X�R�A�iMAX�Q�O�O�O�O�j�@�{�@STAGE �~ 10000
=======
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE の描画

	// スコアに置換する
	// スコア　＝　時間スコア　＋　スコア（MAX２００００）　＋　STAGE × 10000
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	now_score = now_time * 100 + score + stage * 10000;

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Y O U R  S C O R E : %d", now_score);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "T I M E  P O I N T : %d + S C O R E : %d + S T A G E  P O I N T : %d", now_time * 100, score, stage * 10000);

<<<<<<< HEAD
	// �n�C�X�R�A���X�R�A�̏ꍇ
	if (high_score < now_score) {

		// �l���㏑���E�L�^
=======
	// ハイスコアよりスコアが大きい場合
	if (high_score < now_score) {

		// 値を上書き・記録する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
		high_score = now_score;
		SAVE_highscore();
	}

<<<<<<< HEAD
	// SPACE �������ꍇ �^�C�g����ʂ�
=======
	// SPACE KEY を押した場合 タイトル画面へ
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Clear_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

void Game::GAME_END() {

	DxLib_End(); // DXライブラリの終了
}

<<<<<<< HEAD
//-------------------------------------------------------------------------------------

// WinMain �֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game; // Game �N���X�� game ��
=======
// WinMain 関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game; // GAME クラスを game に置換する
>>>>>>> 5060ce1f13446755c2d57fc4693205081dc6c8aa
	game.GAME_SET();
	game.GAME_ALL();
	game.GAME_END();
	return 0;
}
