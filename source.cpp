#define _USE_MATH_DEFINES
#include <math.h>
#include <memory> // for smart pointer
#include <list> // for list
#include <algorithm> // for for_each
#include "sqlite3.h" // for DB
#include "DxLib.h" // for DxLib

//=====================================================================================
// �摜�t�@�C���p
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

	// �e�����̂̕\���p
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

	// �l�\���p
	_0_, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_,
	NUM,
};

//-------------------------------------------------------------------------------------
// ���t�@�C���p
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
int en_x; // �G��x���W
int en_y; // �G��y���W
int enemy_num = 0; // �G��
int enemy_s; // �G�̑��x
int effect_vol = 180; // ���ʉ��̉���
int bgm_vol = 190; // BGM�̉���
int picture_array[static_cast<int>(Object_Type::NUM)]; // �摜�t�@�C���p
int sound_array[static_cast<int>(Sound_Type::NUM)]; // ���t�@�C���p

//-------------------------------------------------------------------------------------
// �摜�t�@�C���̓Ǎ���
void Set_picture(const char* file_name, const Object_Type ot) {
	char path[100];
	sprintf_s(path, "Picture_file/%s", file_name);

	if (picture_array[static_cast<int>(ot)] == 0) {
		picture_array[static_cast<int>(ot)] = LoadGraph(path);
	}
}

//-------------------------------------------------------------------------------------
// ���y�t�@�C���̓Ǎ���
void Set_sound(const char* file_name, const Sound_Type st) {
	char path[100];
	sprintf_s(path, "Sound_file/%s", file_name);

	if (sound_array[static_cast<int>(st)] == 0) {
		sound_array[static_cast<int>(st)] = LoadSoundMem(path);
	}
}

//-------------------------------------------------------------------------------------
// �Ȉ�DX���C�u�����֐�
void My_DrawExtendGraph(int x1, int y1, int x2, int y2, const Object_Type ot) {
	DrawExtendGraph(x1, y1, x2, y2, picture_array[static_cast<int>(ot)], TRUE);
}

//-------------------------------------------------------------------------------------
// �x �� ���W�A���ϊ�
double Deg_to_rad(const double degree) {
	return degree * M_PI / 180.0;
}

//=====================================================================================
// �X�}�[�g�|�C���^
class Object;
typedef std::shared_ptr <Object> Object_Pointer;

// �p���N���X
class Object {
protected:
	double m_x; // x���W
	double m_y; // y���W
	int m_w; // ����
	int m_h; // �c��
	int m_s; // ���x

	// �����蔻��p�ϐ�
	double hit_x; // x���W
	double hit_y; // y���W
	int hit_w; // ����
	int hit_h; // �c��

	int hp_max; // �ő�HP
	int hp_now;	// ����HP
	int sp_max;	// �ő�SP
	int sp_now;	// ����SP
	int damage;	// �_���[�W��
	int energy;	// SP��
	int shot_count;
	bool remove_flag; // �폜�t���O
	void Remove();

public:
	Object();
	virtual Object_Type Get_type() = 0; // ���^�C�v���擾�i�������z�j
	virtual Object_Type Hit_type() { return Object_Type::NONE; };

	virtual void Set_position(const int position_x, const int position_y); // ���W�̐ݒ�
	virtual void Set_hit_area(const int x, const int y, const int w, const int h); // �����蔻��Ώۂ̐ݒ�

	bool Get_remove() { return remove_flag; }; // �폜�t���O�̎擾
	bool Hit_test(Object_Pointer& op); // �����蔻�菈���̐ݒ�

	int Get_damage() { return damage; };
	int Get_energy() { return energy; };

	virtual void Set_degree(const double degree) {}; // �p�x�̐ݒ�
	virtual void Set_sign(const int s) {}; // ���� (+ �^ -) �̐ݒ�
	void Set_range();
	virtual void Move() = 0; // ���� (�������z�֐�)
	virtual void Draw() = 0; // �摜��`��
	virtual void Hit(int damage, int energy) {}; // �����蔻�莞�̐ݒ�
	virtual void Hit() {};
};

//-------------------------------------------------------------------------------------
class Player : public Object {
private:
	double deg;
	int sign;
	int shot_num;
	int charge_time; // �g��e�p
	int dead_time; // �_�ŗp
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
// �ʏ�e
class Shot : public Object {
protected:
	double center_x; // ���Sx���W
	double center_y; // ���Sy���W
	double radian; // ���W�A��

public:
	Shot();
	void Move();
	void Draw();
	void Hit();
	Object_Type Get_type() { return Object_Type::SHOT; };
	Object_Type Hit_type() { return Object_Type::ENEMY; };
};

//-------------------------------------------------------------------------------------
// �ђʒe
class Through_Shot : public Shot {
public:
	Through_Shot();
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// ����
class Beam : public Shot {
public:
	Beam();
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// �Q���e
class Swirl_Shot : public Through_Shot {
private:
	double r; // ���a
	double tmp; // �v�Z�����p�ϐ�

public:
	Swirl_Shot();
	void Set_position(const int position_x, const int position_y);
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// N-way�e
class N_way_Shot : public Through_Shot {
public:
	N_way_Shot();
	void Set_degree(const double degree); // �p�x��ݒ�
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// 3D�Q���e
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
// �`���[�W�e
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
// �������e
class Timed_Shot : public Object {
private:
	int time; // ���˂܂ł̎���
	int shot_count; // ���˂��鐔

public:
	Timed_Shot();
	void Move();
	void Draw();
	Object_Type Get_type() { return Object_Type::TIMED_SHOT; };
	Object_Type Hit_type() { return Object_Type::NONE; };
};

//-------------------------------------------------------------------------------------
// ��E��
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
// ���E�E
class Timed_Shot_Sub2 : public Timed_Shot_Sub1 {
public:
	Timed_Shot_Sub2();
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// �ǔ��e
class Homing_Shot : public Shot {
public:
	Homing_Shot();
	double Unit_vec(const double vec, const double vec_x, const double vec_y); // �P�ʃx�N�g���̎擾
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// �������e
class Parabola_Shot : public Shot {
private:
	double a = 0.0;
	double b = 0.0;
	double c = 0.0;

public:
	Parabola_Shot();
	void Det(const double(*mat)[3], double* det); // �s�񎮂̌v�Z
	void Set_position(const int, const int);
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// �����e
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
// �������Q���e
class Multi_Direct_Swirl_Shot : public Shot {
public:
	Multi_Direct_Swirl_Shot();
	void Set_degree(const double degree);
	void Move();
	void Draw();
	void Hit();
};

//-------------------------------------------------------------------------------------
// �G
class Enemy1 : public Object {
protected:
	int up_down; // �㉺����

public:
	Enemy1();
	void Effect(bool boss_flag);
	void Remove_func();	// �폜�֘A�̎���
	void Move();
	void Draw();
	void Hit(int damage, int energy);
	Object_Type Get_type() { return Object_Type::ENEMY; };
	Object_Type Hit_type() { return Object_Type::PLAYER; };
};

//-------------------------------------------------------------------------------------
// �^�t
class Enemy2 : public Enemy1 {
public:
	Enemy2();
	void Move();
	void Draw();
};

//-------------------------------------------------------------------------------------
// �x�N�g��
class Enemy3 : public Enemy1 {
public:
	Enemy3();
	void Move();
	void Draw();
};

//-------------------------------------------------------------------------------------
// �X�s�[�h
class Enemy4 : public Enemy1 {
public:
	Enemy4();
	void Move();
	void Draw();
};

//-------------------------------------------------------------------------------------
// �ʏ�U��
class Enemy5 : public Enemy1 {
public:
	Enemy5();
	void Move();
	void Draw();
};

//-------------------------------------------------------------------------------------
// �x�N�g���U��
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
	int add_speed; // ���x���グ��
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
	void Hit() {}; // �����蔻��~
	Object_Type Get_type() { return Object_Type::NONE; };
};

//-------------------------------------------------------------------------------------
// HP��
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
// SP(Shot Points)��
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
	void Reset_position(bool); // �ז����̏����ݒ���ēx�E���S���s���S��
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
	// Object�^�̃��X�g
	std::list <Object_Pointer> objects_list;

	// �t���O�ϐ�
	bool push_flag;	// PUSH_space�֐��EPUSH_back�֐��p
	bool play_flag;	// �v���C�p�Etrue �ŃX�^�[�g
	bool space_flag; // �X�y�[�X�p
	bool num_flag;
	bool name_flag;
	bool pause_flag;

	// �X�R�A�E���ԂɊւ���ϐ�
	int high_score;	// �ō����_
	int now_score; // �X�R�A
	int now_time; // �c�莞��
	int start_time;	// 1s �P�ʂŌv������
	int stop_time; // �|�[�Y����ꍇ�@���ݎ��Ԃ𓾂�
	int pause_time;	// �|�[�Y��ʂ̌o�ߎ���
	int limit_time;	// ��������
	int warning_time;

	static const int name_size = 20; // ������
	char name_data[name_size + 1] = "";
	const char* file_name = "database.db"; // �f�[�^�x�[�X�̃t�@�C����

public:
	bool boss_flag; // �{�X�t���O
	bool debug_flag; // �f�o�b�O�p
	int score; // �X�R�A
	int scene; // ���
	int stage; // �X�e�[�W

	Game();
	static const int Display_w = 1200; // �f�B�X�v���C�̃^�e��
	static const int Display_h = 600; // �f�B�X�v���C�̃��R��
	static const int Top = 40; // Play ��� ����W
	static const int Height = Display_h - 40; // Play ��� �����W

	void Add_list(Object_Pointer& tp); // ���X�g�̒ǉ�
	void Add_score(const int s); // �X�R�A�̒ǉ�
	bool Push_space(); // �X�y�[�X����
	bool Push_back(); // �o�b�N�X�y�[�X����

	// �f�[�^�x�[�X�֘A
	void Check_database();
	void Add_name_to_database();
	void Add_score_to_database(const int s);
	void Show_ranking_from_database();
	int Get_score(); // ���[�U�̃X�R�A�l�̎擾

	void Enemy_Form(const int x); // �G�̐���
	void Draw_numbers(const int num, const int x, const int y, const int w, const int h);
	void Switch_stage();

	// ���y�t�@�C���֘A
	void Sound_play(const Sound_Type st, const int volume); // ���ʉ��̍Đ�
	void Sound_loop_play(const Sound_Type st, const int volume); // ���[�vBGM�̍Đ�
	void Sound_stop(const Sound_Type st); // ���̒�~

	void Game_set(); // �ݒ�
	void Game_all(); // ����
	void Game_title(); // �^�C�g��
	void Game_Account(); // ���O�C��
	void Game_select(); // �X�e�[�W�I��
	void Game_ranking(); // �����L���O�\��
	void Game_play(); // �v���C
	void Game_over(); // Game Over
	void Game_clear(); // Game Clear
	void Error_screen(); // �G���[�΍�
	void Game_end(); // DX���C�u�����̏I��
};

//------------------------------------------------------------------------------------
Game* game; // �C���X�^���X��

// ��������
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
// �����蔻��͈͂̐ݒ�
void Object::Set_hit_area(const int x, const int y, const int w, const int h) {
	hit_x = x;
	hit_y = y;
	hit_w = w;
	hit_h = h;
}

//------------------------------------------------------------------------------------
// �����͈͂̐ݒ�
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
	const int x1 = (int)m_x + (int)hit_x; // x���W
	const int y1 = (int)m_y + (int)hit_y; // y���W
	const int w1 = hit_w; // ����
	const int h1 = hit_h; // �c��

	// �Ή����铖���蔻����W
	const int x2 = (int)op->m_x + (int)op->hit_x; // x���W
	const int y2 = (int)op->m_y + (int)op->hit_y; // y���W
	const int w2 = op->hit_w; // ����
	const int h2 = op->hit_h; // �c��

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
	hp_max = 10; // �ő�HP
	hp_now = 5;	// ����HP
	sp_max = 10; // �ő�SP
	sp_now = 1;	// ����SP
	damage = 0;
	energy = 0;
	shot_num = 1;
	shot_count = 0;	// �e�̊Ԋu����
	dead_time = 0;
	shot_flag = false;
	beam_flag = false;

	Set_position(150, 300);	// x�Ey ���W��ݒ�
	Set_hit_area(0, 10, m_w - 10, m_h - 10); // �����蔻���ݒ�

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

	// ���t�@�C���ݒ�
	Set_sound("SHOT2.mp3", Sound_Type::THROUGH_SHOT);
	Set_sound("E ATTACK.mp3", Sound_Type::E_ATTACK);
}

//------------------------------------------------------------------------------------
void Player::Move() {
	if (0 < dead_time) {
		dead_time--; // �_�ŗp
	}

	if (charge_time == 0 && !beam_flag) {
		// �ړ�����(�������E�E�����Ή�)
		// ������
		if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A)) {
			m_x -= m_s;
		}
		// �E����
		if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) {
			m_x += m_s;
		}
		// �����
		if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W)) {
			m_y -= m_s;
		}
		// ������
		if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S)) {
			m_y += m_s;
		}

		//�@��ʂ̓����蔻��
		// ������
		if (m_x < 0) {
			m_x = 0;
		}
		// �E�����i��ʂ̔����𒴂��Ȃ��݌v�j
		if (Game::Display_w / 2 < m_x + m_w) {
			m_x = static_cast<double>(Game::Display_w) / 2.0 - static_cast<double>(m_w);
		}
		// �㕔��
		if (m_y < Game::Top) {
			m_y = Game::Top;
		}
		// ������
		if (Game::Height < m_y + m_h) {
			m_y = double((Game::Height)) - double(m_h);
		}
		//-----------------------------------------------------------------
	}

	//�@�e���̐؂�ւ�
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

	// �B���R�}���h
	else if (CheckHitKey(KEY_INPUT_Z)) {
		// �������Q���e
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
		//	�����e
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
			// �ʏ�e
			if (1 <= sp_now) {
				if (!shot_flag) {
					if (shot_count % 8 == 0) {
						Object_Pointer shot(new Shot); // �C���X�^���X����
						shot->Set_position(m_x + m_w - 10, m_y + 25); // ���W�̐ݒ�
						game->Add_list(shot); // ���X�g�ǉ�
						game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol); // ���ʉ�
					}
				}
			}
			break;

		case 2:
			// �W���e
			if (2 <= sp_now) {
				// ���ˏ�������(�C���^�[�o��)
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
			// �Q���e
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
			// �ђʒe
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
			// ����
			if (5 <= sp_now) {
				if (!beam_flag) {
					Object_Pointer beam(new Beam);
					beam->Set_position(m_x + m_w + 15, m_y - 10);
					game->Add_list(beam);
					game->Sound_play(Sound_Type::BEAM, effect_vol);
					beam_flag = true; // �A�Ŏd�l
				}
			}
			break;

		case 6:
			// �������e
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
			// �ǔ��e
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
			// �������e
			if (8 <= sp_now) {
				if (!shot_flag) {
					Object_Pointer timed_shot(new Timed_Shot);
					timed_shot->Set_position(m_x + m_w - 10, m_y + 25);
					game->Add_list(timed_shot);
					shot_flag = true; // �A�Ŏd�l
					game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
				}
			}
			break;

		case 9:
			// N-way�e
			if (9 <= sp_now) {
				if (shot_count % 10 == 0) {
					if (!shot_flag) {
						for (int i = 0; i < 7; i++) { // 7��
							Object_Pointer n_way_shot(new N_way_Shot);
							n_way_shot->Set_position(m_x + m_w - 10, m_y + 25);
							n_way_shot->Set_degree((3.0 - i) * 10.0); // 30���E20���E10���E0�����㉺�ɐݒ�
							game->Add_list(n_way_shot);
						}
						game->Sound_play(Sound_Type::THROUGH_SHOT, effect_vol);
					}
				}
			}
			break;

		case 10:
			// ���̌^�Q���e
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

	// �S�e�����g�p�� (�f�o�b�O�p)
	else if (CheckHitKey(KEY_INPUT_0)) {
		sp_now = 10;
	}

	// �{�^���������Ă��Ȃ��Ƃ�
	else {
		shot_flag = false;
		beam_flag = false;
		charge_time = 0;
	}

	if (hp_now <= 0) {
		game->scene = GAME_OVER;
		game->Sound_stop(Sound_Type::GAME_PLAY); // �v���C��ʂ̉����~
		game->Sound_stop(Sound_Type::BOSS); // �{�X��ʂ̉����~
		game->Sound_loop_play(Sound_Type::GAME_OVER, bgm_vol); // �I�[�o�[��ʂ̉����Đ�
	}

	// ����ݒ�
	if (10 <= hp_now) {
		hp_now = 10;
	}
	if (10 <= sp_now) {
		sp_now = 10;
	}

	// 360�x�ȏ�̂Ƃ�
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
// ���C�t�\��
void Player::Draw_hp() {
	const int x1 = 10; // ����W
	const int w1 = 30; // �摜�̉���

	My_DrawExtendGraph(x1, 10, x1 + w1, Game::Top - 10, Object_Type::HP);

	const int x2 = x1 + w1 + 5; // ����W
	const int w2 = 15; // ���̉���
	const int space = 5; // �����m�̊Ԋu

	for (int i = 0; i < hp_max; i++) {
		DrawBox(x2 + i * (w2 + space), 5, (x2 + w2) + i * (w2 + space), Game::Top - 5, GetColor(130, 0, 130), TRUE);
	}
	for (int i = 0; i < hp_now; i++) {
		DrawBox(x2 + i * (w2 + space), 5, (x2 + w2) + i * (w2 + space), Game::Top - 5, GetColor(0, 255, 255), TRUE);
	}
}

//------------------------------------------------------------------------------------
void Player::Draw_sp() {
	const int x1 = 270; // ����W
	const int w1 = 30; // �摜�̉���

	My_DrawExtendGraph(x1, 10, x1 + w1, Game::Top - 10, Object_Type::SP);

	const int x2 = x1 + w1 + 5;	// ����W
	const int w2 = 15; // ���̉���
	const int space = 5; // �����m�̊Ԋu

	for (int i = 0; i < sp_max; i++) {
		DrawBox(x2 + i * (w2 + space), 5, (x2 + w2) + i * (w2 + space), Game::Top - 5, GetColor(130, 0, 130), TRUE);
	}
	for (int i = 0; i < sp_now; i++) {
		DrawBox(x2 + i * (w2 + space), 5, (x2 + w2) + i * (w2 + space), Game::Top - 5, GetColor(0, 255, 0), TRUE);
	}
}

//------------------------------------------------------------------------------------
void Player::Draw_font() {
	Object_Type ot;	// �摜���ʗp

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
		// �G���[����
		ot = Object_Type::NONE;
		break;
	}

	const int x1 = Game::Display_w / 2 + 20; // ����W
	const int w1 = 150; // �摜�̉���
	const int space = 10; // �Ԋu

	DrawBox(x1 - space, 5, x1 + w1 + space, Game::Top - 5, GetColor(50, 50, 50), TRUE);
	My_DrawExtendGraph(x1, 10, x1 + w1, Game::Top - 10, ot);

	const int x2 = (x1 + w1 + space) + space; // ����W
	const int w2 = 90; // �摜�̉���

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
	// �G
	if (dead_time <= 0 && 0 < damage) {
		dead_time = 50;
		hp_now -= damage; // HP�����炷
		game->Sound_play(Sound_Type::E_ATTACK, effect_vol); // �_���[�W��
	}

	// �񕜓���
	if (damage < 0 && hp_now < 10) {
		hp_now -= damage; // HP��
	}
	if (energy < 0 && sp_now < 10) {
		sp_now -= energy; // SP��
	}
}

//====================================================================================
// �ʏ�e�̎���
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
// �ђʒe
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
// ����
Beam::Beam() {
	m_w = 0; // �L�����邽��
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
	hit_w = m_w; // �����𓖂��蔻��ɒǉ�

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
// �Q���e
Swirl_Shot::Swirl_Shot() {
	m_w = 12;
	m_h = 12;
	damage = 10;
	radian = 0.0;
	r = 5.0; // ���a
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
	r += 2 - tmp; // ���a���̒���
	radian += 8 / r; // �p���x�̒���

	// �O�p�֐��̉��p
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
// N-way�e
N_way_Shot::N_way_Shot() {
	m_w = 12;
	m_h = 12;
	m_s = 8;
	damage = 5;
	radian = 0;
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
// �p�x�̎擾
void N_way_Shot::Set_degree(const double d) {
	radian = Deg_to_rad(d);
}

//-------------------------------------------------------------------------------------
void N_way_Shot::Move() {
	// �O�p�֐��̉��p
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
// 3D�Q���e
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
// ���W�̎擾
void Swirl_3D_Shot::Set_position(const int position_x, const int position_y) {
	m_x = position_x;
	center_y = position_y;
}

//-------------------------------------------------------------------------------------
// �����̎擾
void Swirl_3D_Shot::Set_sign(const int s) {
	sign = s;
}

//-------------------------------------------------------------------------------------
void Swirl_3D_Shot::Move() {
	radian += Deg_to_rad(10) / (r / 60.0);
	m_x += m_s / (1 + r / 100.0);
	m_y = center_y - sign * r * sin(radian); // �T�C���J�[�u�̉��p

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
// �`���[�W�e
Charge_Shot::Charge_Shot() {
	m_w = 0;
	m_h = 0;
	m_s = 15;
	damage = 0;
	deg = 0;
	charge_flag = false;

	Set_hit_area(0, 0, m_w, m_h);
	Set_picture("Charge_shot.png", Object_Type::CHARGE_SHOT);
	Set_sound("CHARGE.mp3", Sound_Type::CHARGE); // CHARGE ���̉�
	Set_sound("CHARGE SHOT.mp3", Sound_Type::CHARGE_SHOT); // ���ˉ�
}

//-------------------------------------------------------------------------------------
void Charge_Shot::Move() {
	if (!charge_flag) {
		if (CheckHitKey(KEY_INPUT_B)) {
			if (damage < 50) {
				damage++;
				m_y -= 2;
				m_w = 4 * damage; // ���Q�ʂɔ����g��
				m_h = 4 * damage;

				// �����蔻��̌덷����
				hit_w = m_w;
				hit_h = m_h;

				// ��ʓ��Ɏ��܂�݌v
				if (m_y < Game::Top || Game::Height < m_y + m_h) {
					charge_flag = true;
					game->Sound_stop(Sound_Type::CHARGE);
					game->Sound_play(Sound_Type::CHARGE_SHOT, effect_vol);
				}
			}

			// 50�ɂȂ�
			else {
				charge_flag = true;
				game->Sound_stop(Sound_Type::CHARGE);
				game->Sound_play(Sound_Type::CHARGE_SHOT, effect_vol);
			}
		}

		// ����
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
// �������e
Timed_Shot::Timed_Shot() {
	m_w = 15;
	m_h = 15;
	m_s = 12;
	damage = 0;
	time = 30; // ���˂܂ł̎���
	shot_count = 1; // �e���J�E���g�p
	Set_hit_area(0, 0, m_w, m_h);
	Set_picture("Timed_shot.png", Object_Type::TIMED_SHOT);
	Set_sound("P ATTACK.mp3", Sound_Type::P_ATTACK);
}

//-------------------------------------------------------------------------------------
void Timed_Shot::Move() {
	const int max = 5; // �e��

	if (0 <= time) {
		m_x += m_s; // ���˂܂ŉE������
	}

	else {
		if (time % 10 == 0 && shot_count <= max) {

			for (int i = -1; i <= 1; i += 2) {
				// �㉺����
				Object_Pointer sub1(new Timed_Shot_Sub1());
				game->Add_list(sub1);
				sub1->Set_sign(i);
				sub1->Set_position(m_x + 1, m_y - 10 * i);

				// ���E����
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
// �㉺
Timed_Shot_Sub1::Timed_Shot_Sub1() {
	m_w = 12;
	m_h = 12;
	m_s = 15;
	damage = 5;
	sign = 0;
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
// �����̎擾
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
// ���E
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
// �ǔ��e
Homing_Shot::Homing_Shot() {
	m_w = 12;
	m_h = 12;
	m_s = 10;
	damage = 20;
	Set_hit_area(0, 0, m_w, m_h);
}

//-------------------------------------------------------------------------------------
// �P�ʃx�N�g���v�Z
double Homing_Shot::Unit_vec(const double vec, const double vec_x, const double vec_y) {
	return vec / sqrt(vec_x * vec_x + vec_y * vec_y);
}

//-------------------------------------------------------------------------------------
// ��葬�x
void Homing_Shot::Move() {
	if (0 < enemy_num) {
		m_x += Unit_vec(en_x - m_x, en_x - m_x, en_y - m_y) * m_s;
		m_y += Unit_vec(en_y - m_y, en_x - m_x, en_y - m_y) * m_s;
	}
	else {
		m_x += m_s; // �G�����Ȃ��ꍇ�͉E������
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
// �������e
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
// �s�񎮂̌v�Z
void Parabola_Shot::Det(const double(*mat)[3], double* det) {
	*det += mat[0][0] * mat[1][1] * mat[2][2];
	*det += mat[0][1] * mat[1][2] * mat[2][0];
	*det += mat[0][2] * mat[1][0] * mat[2][1];

	*det -= mat[0][0] * mat[1][2] * mat[2][1];
	*det -= mat[0][1] * mat[1][0] * mat[2][2];
	*det -= mat[0][2] * mat[1][1] * mat[2][0];
}

//-------------------------------------------------------------------------------------
// ���W�̎擾
void Parabola_Shot::Set_position(const int position_x, const int position_y) {
	center_x = position_x;
	center_y = position_y;

	double frame = (en_x - center_x) / (8 + enemy_s);

	double x1 = center_x;							// ���ˍ��W
	double x2 = en_x - enemy_s * frame;				// �G�̍��W
	double x3 = static_cast<double>(center_x) + 1;	// �C�ӂ�	���W

	double y1 = center_y;
	double y2 = en_y;
	double y3 = center_y - tan(Deg_to_rad(60)); // 45�x

	// �s��
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

	// �N�������̍s��
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
// �����e
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
	acc++; // �����x

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
// �������Q���e
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
// ���j�G�t�F�N�g�̎���
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
		Remove(); // �폜

		// �ʏ�̓G
		if (!flag) {
			game->Add_score(200); // �X�R�A�{
		}

		// �{�X
		else {
			game->scene = GAME_CLEAR; // �N���A��ʂ�
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

	// ���x�ݒ�
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

	// ��ʍ��ɓ���ꍇ
	if (m_x + m_w < 0) {
		Remove_func();
	}

	// �e�������p
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
// ��ʊO�̍폜����
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
		Effect(false); // ���j�G�t�F�N�g�̎��s
		Remove();

		if (0 < enemy_num) {
			enemy_num -= 1; // �G��-1
		}
	}
}

//====================================================================================
Enemy2::Enemy2() {
	m_w = 70;
	m_h = 35;

	// ���x����
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
// �ǔ���
Enemy3::Enemy3() {
	m_w = 70;
	m_h = 35;

	// ���x�ݒ�
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
	up_down = 6; // �c�����̑��x

	Set_picture("Enemy3.png", Object_Type::ENEMY3);
	Set_hit_area(0, 0, m_w, m_h);
	Set_range();
}

//-------------------------------------------------------------------------------------
void Enemy3::Move() {
	m_x -= m_s;
	m_y += up_down; // �㉺�����̑��x

	// �㉺�̓����蔻��
	// ��ˉ� or ���ˏ�
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
// ����
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
	// ���̍��W�܂ō��ړ�
	if (1000 < m_x) {
		m_x -= m_s;
	}

	// ���̍��W�ŏ㉺�ړ�
	else {
		m_y -= up_down;

		// �����蔻��
		if (m_y < Game::Top || Game::Height < m_y + m_h) {
			up_down = -up_down;
		}

		if (GetRand(60) == 0) {
			Object_Pointer enemy_shot(new Enemy_Shot(12, 1));
			enemy_shot->Set_position(m_x - 10, m_y + 25); // ���W
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

	// ��ʂ̓����蔻��
	if (m_y < Game::Top || Game::Height < m_y + m_h) {
		up_down = -up_down;
	}

	if (m_x < 0) {
		m_s = -2; // ��
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
	// �̗͐ݒ�
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
	up_down = 1;	// �㉺�������x
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
	Set_hit_area(50, 20, m_w, m_h - 20); // �����蔻��̐ݒ�
	Set_position(Game::Display_w, 150);
}

//-------------------------------------------------------------------------------------
void Enemy_Boss1::Set_shot_type(const int num) {
	int size = 20; // �e�̃T�C�Y

	switch (num) {
	case N_WAY_1:
		// N-way�e
		for (int i = 1; i <= 7; i++) {
			Object_Pointer enemy_shot(new Enemy_Shot(18, num));
			enemy_shot->Set_position(m_x - 10, m_y + m_h / 2.0 - 15);
			enemy_shot->Set_degree((3.0 - i) * 10.0);
			game->Add_list(enemy_shot);
		}
		break;

	case NORMAL:
		// �ʏ�e
		for (int i = 1; i <= 2; i++) {
			Object_Pointer enemy_shot(new Enemy_Shot(size + 10, num));
			enemy_shot->Set_position(m_x + 40, m_y + m_h / 2.0 - 240 + i * 150);
			game->Add_list(enemy_shot);
		}
		break;

	case MULTI_DIRECT_SWIRL:
		// �������Q���e
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
	// �̗͔����ȉ��̏ꍇ�@���x���㏸
	if (hp_now < hp_max / 2) {
		if (up_down < 0) {
			up_down = -3;
		}
		else {
			up_down = 3;
		}
	}

	// ���̍��W�܂ō�����
	if (920 < m_x) {
		m_x -= 1;
	}
	// �㉺����
	else {
		if (!sound_flag) {
			sound_flag = true;
			game->Sound_loop_play(Sound_Type::BOSS, bgm_vol); // �{�X�o�g���p�̉��y�̍Đ�
		}

		if (!time_flag) {
			time = GetNowCount(); // 10�b�v���p
			tmp = GetRand(TYPE_NUM - 1);
			time_flag = true;
		}
		// 10�b�o�߂Œe���ύX
		if (5 < (GetNowCount() - time) / 1000) {
			time_flag = false;
		}

		if (tmp != MULTI_DIRECT_SWIRL) {
			m_y += up_down;
		}

		// ��ʂ̓����蔻��
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
	unsigned int color = GetColor(50, 205, 50);	// RGB�l

	if (hp_now < hp_max / 2) {
		color = GetColor(220, 200, 0);
	}
	if (hp_now < hp_max / 4) {
		color = GetColor(255, 0, 0);
	}

	const int x1 = Game::Display_w - 300; // ��̍��W
	const int w1 = 240; // ����
	const int space = 3; // �Ԋu

	// ���C�t�̕`��
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
	// �̗͔����ȉ��̏ꍇ�@���x���㏸
	if (hp_now < hp_max / 2) {
		if (up_down < 0) {
			up_down = -5;
		}
		else {
			up_down = 5;
		}
	}

	// ���̍��W�܂ō�����
	if (920 < m_x) {
		m_x -= 1;
	}
	// �㉺����
	else {
		if (!sound_flag) {
			sound_flag = true;
			game->Sound_loop_play(Sound_Type::BOSS, bgm_vol); // �{�X�o�g���p�̉��y�̍Đ�
		}

		if (!time_flag) {
			time = GetNowCount(); // 10�b�v���p
			tmp = GetRand(TYPE_NUM - 1);
			time_flag = true;
		}
		// 10�b�o�߂Œe���ύX
		if (5 < (GetNowCount() - time) / 1000) {
			time_flag = false;
		}

		if (tmp != MULTI_DIRECT_SWIRL) {
			m_y += up_down;
		}

		// ��ʂ̓����蔻��
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

	// ���x�ݒ�
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
// �p�x�̎擾
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
		color = GetColor(255, 0, 0); // ��
	}
	else if (7 <= game->stage && game->stage <= 9) {
		color = GetColor(0, 255, 0); // ��
	}
	else if (game->stage == 10) {
		color = GetColor(200, 200, 200); // �D
	}

	DrawCircle(m_x + m_w / 2.0, m_y + m_h / 2.0, m_w / 2.0, color, TRUE);
}

//-------------------------------------------------------------------------------------
void Enemy_Shot::Hit() {
	Remove();
	game->Sound_play(Sound_Type::ENEMY_SHOT, effect_vol);
}

//====================================================================================
// �̗͉�
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
// ����ʉ�
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
	int cx = GetRand(Game::Display_w); // ���E�͂ݏo�����Ƃ���
	tmp = GetRand(Game::Height);

	// ���S�o���o���z�u
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

	// �G�Ɠ����d�g��
	else {
		Set_range();
	}

	// ���x�ݒ�
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
		Reset_position(false); // �폜�ł͂Ȃ��J��Ԃ��z�u
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
// ���ʉ��o��
void Game::Sound_play(const Sound_Type st, const int volume) {
	ChangeVolumeSoundMem(volume, sound_array[static_cast<int>(st)]); // ���ʒ���
	PlaySoundMem(sound_array[static_cast<int>(st)], DX_PLAYTYPE_BACK);
}

//------------------------------------------------------------------------------------
// ���[�vBGM�o��
void Game::Sound_loop_play(const Sound_Type s, const int volume) {
	ChangeVolumeSoundMem(volume, sound_array[static_cast<int>(s)]); // ���ʒ���
	PlaySoundMem(sound_array[static_cast<int>(s)], DX_PLAYTYPE_LOOP);
}

//------------------------------------------------------------------------------------
// �Đ���~
void Game::Sound_stop(const Sound_Type st) {
	StopSoundMem(sound_array[static_cast<int>(st)]);
}

//------------------------------------------------------------------------------------
// ���X�g�֒ǉ�
void Game::Add_list(Object_Pointer& op) {
	objects_list.push_back(op);
}

//------------------------------------------------------------------------------------
// �X�R�A�̒ǉ�
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

	// DB�t�@�C���̊J��
	int con = sqlite3_open(file_name, &db);

	// �G���[����
	if (con != SQLITE_OK) {
		scene = ER;
	}

	// �e�[�u���쐬(���݂��Ȃ��ꍇ�̂�)
	con = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Users(name text primary key, score integer)", NULL, NULL, NULL);
	sqlite3_close(db);
}

//------------------------------------------------------------------------------------
// �f�[�^�x�[�X�֖��O��ۑ�
void Game::Add_name_to_database() {
	char SQL1[100];
	char SQL2[100];
	sqlite3* db = NULL;
	sqlite3_stmt* res = NULL;

	// DB�t�@�C���̊J��
	int con = sqlite3_open(file_name, &db);

	// �G���[����
	if (con != SQLITE_OK) {
		scene = ER;
	}

	// ���[�U�̌���
	sprintf_s(SQL1, "SELECT COUNT(*) FROM Users WHERE name = \'%s\'", name_data);
	con = sqlite3_prepare_v2(db, SQL1, -1, &res, NULL); // ���ߎ��s
	con = sqlite3_step(res);

	// �V�K�̖��O�̏ꍇ
	if (sqlite3_column_int(res, 0) == 0) {
		sprintf_s(SQL2, "INSERT INTO Users(name) values(\'%s\')", name_data);	// ������̐���
		con = sqlite3_exec(db, SQL2, NULL, NULL, NULL);							// ���ߎ��s
	}
	sqlite3_finalize(res);
	sqlite3_close_v2(db);
}

//------------------------------------------------------------------------------------
// �f�[�^�x�[�X�փX�R�A�ۑ�
void Game::Add_score_to_database(const int s) {
	char SQL[100];
	sqlite3* db = NULL;

	// DB�t�@�C���̊J��
	int con = sqlite3_open(file_name, &db);

	// �G���[���
	if (con != SQLITE_OK) {
		scene = ER;
	}

	// �X�R�A�̏㏑��
	sprintf_s(SQL, "UPDATE Users SET score = %d WHERE name = \'%s\'", s, name_data);
	con = sqlite3_exec(db, SQL, NULL, NULL, NULL);

	// �G���[���
	if (con != SQLITE_OK) {
		scene = ER;
	}
	// �t�@�C�������
	sqlite3_close(db);
}

//------------------------------------------------------------------------------------
// ���ʕ\��
void Game::Show_ranking_from_database() {
	sqlite3* db = NULL;
	sqlite3_stmt* res = NULL;

	// DB�t�@�C���̊J��
	int con = sqlite3_open(file_name, &db);

	// �f�[�^�̒��o (�~��)
	con = sqlite3_prepare_v2(db, "SELECT * FROM Users ORDER BY score DESC", -1, &res, NULL);

	// �����T�C�Y
	SetFontSize(25);

	for (int i = 0; SQLITE_ROW == (con = sqlite3_step(res)) && i < 10; i++) {
		const int x = 350; // �x���W
		const int y = 200 + i * 30; // �y���W
		unsigned int color = GetColor(255, 255, 255); // RGB�l
		char buf[50]; // ������i�[�p

		if (i + 1 < 10) {
			sprintf_s(buf, " %d %s", i + 1, sqlite3_column_text(res, 0));
		}
		else {
			sprintf_s(buf, "%d %s", i + 1, sqlite3_column_text(res, 0));
		}

		// ����+���O�\��
		DrawString(x, y, buf, color);

		// �X�R�A�擾
		const int ones_score = sqlite3_column_int(res, 1);

		// �����킹
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
		DrawString(x + 400, y, buf, color); // �X�R�A�\��
	}

	// �t�@�C�������
	sqlite3_finalize(res);
	sqlite3_close_v2(db);
}

//------------------------------------------------------------------------------------
// ���[�U�̃X�R�A�擾
int Game::Get_score() {
	int result = 0;
	char SQL[100];
	sqlite3* db = NULL;
	sqlite3_stmt* res = NULL;

	// DB�t�@�C���̊J��
	int con = sqlite3_open(file_name, &db);

	sprintf_s(SQL, "SELECT * FROM Users WHERE name = \'%s\'", name_data);

	con = sqlite3_prepare_v2(db, SQL, -1, &res, NULL);
	// �G���[����
	if (con != SQLITE_OK) {
		scene = ER;
	}

	con = sqlite3_step(res);
	result = sqlite3_column_int(res, 1); // �X�R�A�擾

	// �t�@�C�������
	sqlite3_finalize(res);
	sqlite3_close_v2(db);
	return result;
}

//------------------------------------------------------------------------------------
// �G�̐���
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
		// �G���[����
		enemy.reset(new Enemy1);
		break;
	}

	Add_list(enemy);

	if (0 <= enemy_num) {
		enemy_num += 1; // �G��+1
	}
}

//------------------------------------------------------------------------------------
void Game::Draw_numbers(const int num, const int x, const int y, const int w, const int h) {
	const int interval = 3; // �������m�̊Ԋu

	if (0 < num) {
		const int digits_num = (int)log10(num); // ����

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
	game = this;		// ���C���X�^���X�̃A�h���X��ێ��i�ÓI�j
	scene = TITLE;		// �^�C�g����

	ChangeWindowMode(TRUE); // �E�B���h�E���J��
	SetGraphMode(Display_w, Display_h, 32); // �E�B���h�E�̉���, �c��, �J���[�ݒ�
	DxLib_Init(); // DX���C�u�����̏�����
	SetDrawScreen(DX_SCREEN_BACK); // �E���ɉ摜��`��
	Check_database(); // �f�[�^�x�[�X�̊m�F

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

	// ���y�t�@�C���̃��[�h
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
// �C�x���g�����̎���
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
			// �G���[���
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
	limit_time = 600; // ��������
	play_flag = false;
	boss_flag = false;
	space_flag = false;
	num_flag = false;
	pause_flag = false;
	debug_flag = false;	// �f�o�b�O���邩�ۂ�

	if (Push_space()) {
		if (!name_flag) {
			scene = ACCOUNT;
		}
		else {
			scene = SELECT;
		}

		Sound_play(Sound_Type::COMMAND, 230);
	}

	// ���ʕ\��
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
// ���[�U�o�^
void Game::Game_Account() {
	const int x = 270;
	const int y = 300;

	My_DrawExtendGraph(50, 150, Display_w - 50, 150 + 50, Object_Type::PLEASE_ENTER);
	DrawBox(x, y, Display_w - x, y + 75, GetColor(255, 255, 255), FALSE);

	// ���O�̓���
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
// ���ʕ\��
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

		// �f�o�b�O��
		if (debug_flag == true) {
			Sound_stop(Sound_Type::TITLE);	// BGM������
		}
	}
}

//-------------------------------------------------------------------------------------
void Game::Game_play() {
	// UI�p
	DrawBox(0, 0, Display_w, Top, GetColor(75, 75, 75), TRUE); // �㕔��
	DrawBox(0, Height, Display_w, Display_h, GetColor(75, 75, 75), TRUE); // ������

	// ���X�g�ɓ���S�ẴC���X�^���X�ɓK�p
	if (!pause_flag) {
		for_each(objects_list.begin(), objects_list.end(), [](Object_Pointer& object) {object->Move(); });
		for_each(objects_list.begin(), objects_list.end(), [&](Object_Pointer& oneself) {

			if (oneself->Hit_type() == Object_Type::NONE) return;

			for_each(objects_list.begin(), objects_list.end(), [&](Object_Pointer& opponent) {
				// �^�C�v����v����ꍇ
				if (oneself->Hit_type() == opponent->Get_type()) {
					// ������ꍇ
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

	// �v���C�O
	if (!play_flag) {
		if (CheckHitKey(KEY_INPUT_B)) {
			space_flag = true;
		}

		if (space_flag && ! debug_flag) {
			My_DrawExtendGraph(300, Display_h - 80, Display_w - 300, Display_h - 30, Object_Type::PUSH_SPACE);
		}

		// �X�^�[�g
		if (Push_space()) {
			if (!debug_flag) {
				Sound_stop(Sound_Type::TITLE); // �^�C�g����ʂ̉����~
				Sound_loop_play(Sound_Type::GAME_PLAY, bgm_vol); // �v���C��ʂ̉����Đ�
			}
			start_time = GetNowCount(); // �������Ԃ̌v��
			play_flag = true;
		}
	}

	// �v���C���̏ꍇ
	else {
		int x = Display_w - 180;

		// �������Ԃ̕\��
		DrawBox(x + 10, Height + 5, (x + 10) + 105, Display_h - 5, GetColor(50, 50, 50), TRUE);
		Draw_numbers(now_time, x + 45, Height + 10, 18, 20);

		// ���v�摜
		My_DrawExtendGraph(x, Height + 5, x + 30, Display_h - 5, Object_Type::CLOCK);

		if (!pause_flag) {
			// �������Ԃ̌v�Z
			now_time = (start_time - GetNowCount()) / 1000 + limit_time;

			if (score < 20000) { // �G�̐���(�e�X�e�[�W�ݒ�)
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
			// �{�X����
			if (20000 <= score && !boss_flag) {
				boss_flag = true;

				Sound_stop(Sound_Type::GAME_PLAY); // �ʏ�o�g�����y�̒�~
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
			// �{�X�o�g��
			if (boss_flag) {
				if ((GetNowCount() - warning_time) / 1000 < 5) {
					if (((GetNowCount() - warning_time) / 1000) % 2 == 0) {
						My_DrawExtendGraph(70, Display_h / 2 - 40, Display_w - 70, Display_h / 2 + 40, Object_Type::WARNING);
					}
				}
			}

			// �񕜂̐���
			if (GetRand(350) == 0) {
				Object_Pointer heal(new Heal1);
				Add_list(heal);
			}

			if (GetRand(600) == 0) {
				Object_Pointer heal(new Heal2);
				Add_list(heal);
			}
		}

		// �|�[�Y��ʂ�
		if (Push_back()) {
			if (!pause_flag) {
				stop_time = GetNowCount(); // ���ݎ��Ԃ̎擾
				Sound_play(Sound_Type::PAUSE, effect_vol);
			}
			pause_flag = true;
			Sound_stop(Sound_Type::GAME_PLAY); // �ʏ�o�g�����̒�~
			Sound_stop(Sound_Type::BOSS);
		}

		//---------------------------------------------------------------
		// �|�[�Y���
		if (pause_flag) {
			pause_time = (GetNowCount() - stop_time) / 1000; // �|�[�Y���Ԃ��v�Z

			DrawBox(150, 150, Display_w - 150, Display_h - 150, GetColor(240, 240, 240), TRUE);
			My_DrawExtendGraph(160, 170, Display_w - 160, 170 + 70, Object_Type::PAUSE_MENU);
			My_DrawExtendGraph(160, 330, Display_w - 160, 330 + 40, Object_Type::ESC);
			My_DrawExtendGraph(270, 380, Display_w - 270, 380 + 40, Object_Type::RESTART);

			// �ĊJ
			if (Push_space()) {
				pause_flag = false;
				limit_time = pause_time + limit_time; // �|�[�Y���ԕ��v���X
				pause_time = 0;

				if (!boss_flag) {
					Sound_loop_play(Sound_Type::GAME_PLAY, bgm_vol); // �ʏ�o�g��BGM�̍Đ�
				}
				else {
					Sound_loop_play(Sound_Type::BOSS, bgm_vol); // �{�X�o�g��BGM�̍Đ�
				}
			}
		}
		//---------------------------------------------------------------
		// �v���C���@��ʍ��[�ɕ����̕\��
		else {
			My_DrawExtendGraph(10, Height + 10, 250, Display_h - 10, Object_Type::BACK_SPACE);
			My_DrawExtendGraph(265, Height + 10, 300 + 80, Display_h - 10, Object_Type::PAUSE);
		}
	}

	// �{�X���o��̏ꍇ�@�X�R�A�\��
	if (!boss_flag) {
		My_DrawExtendGraph(Display_w - 300, 10, Display_w - 300 + 110, Top - 10, Object_Type::SCORE);
		DrawBox((Display_w - 300 + 110) + 10, 5, (Display_w - 300 + 110) + 10 + 125, Top - 5, GetColor(50, 50, 50), TRUE);
		Draw_numbers(score, (Display_w - 300 + 110) + 20, 10, 18, 20);
	}

	// �^�C�g����ʂ֖߂�
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		scene = TITLE;
		Sound_stop(Sound_Type::TITLE); // �^�C�g����ʂ̉����~
		Sound_stop(Sound_Type::GAME_PLAY); // �v���C��ʂ̉����~
		Sound_stop(Sound_Type::BOSS); // �{�X��ʂ̉����~
		Sound_loop_play(Sound_Type::TITLE, bgm_vol); // �^�C�g����ʂ̉����Đ�
	}

	// ����ݒ�
	if (20000 <= score) {
		score = 20000;
	}

	/*
	// �{�X�f�o�b�O�p
	if (CheckHitKey(KEY_INPUT_1)) {
		score = 20000;
	}*/

	// �������� 0 �ɂȂ����ꍇ GAME OVER
	if (now_time < 0) {
		scene = GAME_OVER;
		Sound_stop(Sound_Type::GAME_PLAY);
		Sound_stop(Sound_Type::BOSS);
		Sound_loop_play(Sound_Type::GAME_OVER, bgm_vol);
	}

	// ���X�g���ŏ���: remove_flag == true �̃N���X��������iremove_if �֐��j
	// �폜�t���O true �̃N���X��O��
	// ���̃N���X�� list.erase �ō폜�E���X�g�����񂹂�
	auto end = remove_if(objects_list.begin(), objects_list.end(), [](Object_Pointer& Object) {return Object->Get_remove(); });
	objects_list.erase(end, objects_list.end());
}

//-------------------------------------------------------------------------------------
void Game::Game_over() {
	My_DrawExtendGraph(100, 250, Display_w - 100, Display_h - 250, Object_Type::GAME_OVER);
	My_DrawExtendGraph(300, Display_h - 80, Display_w - 300, Display_h - 30, Object_Type::PUSH_SPACE);

	now_score = score;
	Draw_numbers(now_score, 10, 10, 20, 20); // �X�R�A�\��

	// �l���㏑���E�L�^
	if (Get_score() < now_score) {
		Add_score_to_database(now_score);
	}

	// �^�C�g����ʂ�
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

	// �X�R�A�\��
	Draw_numbers(now_time * 100, 10, 10, 20, 20);
	Draw_numbers(score, 10, 40, 20, 20);
	Draw_numbers(stage * 10000, 10, 70, 20, 20);
	Draw_numbers(now_score, 10, 100, 20, 20);

	// �l���㏑���E�L�^
	if (Get_score() < now_score) {
		Add_score_to_database(now_score);
	}

	// �^�C�g����ʂ�
	if (Push_space()) {
		scene = TITLE;
		Sound_stop(Sound_Type::GAME_CLEAR);
		Sound_play(Sound_Type::COMMAND, 230);
		Sound_loop_play(Sound_Type::TITLE, bgm_vol);
	}
}

//------------------------------------------------------------------------------------
// �G���[�����p
void Game::Error_screen() {
	DrawString(50, 50, "ERROR!", GetColor(255, 0, 0));

	if (Push_space()) {
		Game_end();
	}
}

//------------------------------------------------------------------------------------
// DX���C�u���������
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