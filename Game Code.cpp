#include <iostream> // namespace ���g�p����
#include <memory> // �X�}�[�g�|�C���^�i�����f�X�g���N�^�t�j���g�p
#include <list> // �R���e�i�ilist�j���g�p����
#include <algorithm> // for_each���g�p����
# include <cmath> // pow()�i�ׂ���̌v�Z�j���g�p����
#include "DxLib.h" // DX���C�u�������g�p����

using namespace std;

// �񋓌^ �֐��̃X�C�b�`�Ƃ��Ďg�p
// �摜
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
	TYPE_NUM, // �񋓑΂̐�
};

// ���y
enum Sound {

	SOUND_SHOT1, // SHOT��
	SOUND_SHOT2, // SHOT��2
	SOUND_CHARGE, // CHARGE���̉�
	SOUND_CHARGE_SHOT, // CHARGE SHOT����˂��鉹
	SOUND_ENEMY_SHOT, // ENEMY SHOT�̉�
	SOUND_BEAM, // BEAM��
	SOUND_E_ATTACK, // ENEMY�̃A�^�b�N��
	SOUND_P_ATTACK, // PLAYER�̃A�^�b�N��
	SOUND_HEAL, // �񕜉�
	SOUND_BREAK, // �j��
	SOUND_NUM, // �񋓑΂̐�
};

class Thing; // �X�}�[�g�|�C���^�i�����f�X�g���N�^�t�j�� Thing �N���X����邽�߂ɐ錾����

// Thing �N���X�̃X�}�[�g�|�C���^�ishared_ptr �� Thing �^�jThingPointa ���`����
// GAME �N���X�� �R���e�i�ilist�j�̌^�Ɏg�p����
// �X�}�[�g�|�C���^�� new �Ŋm�ۂ����������������I�� delete ����
// typedef �͌��X����f�[�^�^�ɈقȂ閼�O��t����
typedef std::shared_ptr <Thing> ThingPointa;

// �O���[�o���ϐ��i�S�̂Ɋւ��ϐ��j
int scene; // ���
int stage; // STAGE
int score; // �X�R�A
int shot_count = 0; // �e�̔��ˊԊu�̒��� 0�ɐݒ肷��
int enemy_x; // �G�� x���W�ɒu������
int enemy_y; // �G�� y���W�ɒu������
int enemy_num = 0; // ��ʏ�̓G�̐� 0�ɐݒ肷��
int enemy_s; // �G�̑��x
int pause_flag; // �|�[�Y�i�x�~�j�t���O

int loaded_picture[TYPE_NUM]; // �摜�z��
int loaded_sound[SOUND_NUM]; // ���z��

int Title_m; // �^�C�g�����̉�
int Play_m; // �v���C���̉�
int Over_m; // �I�[�o�[���̉�
int Clear_m; // �N���A���̉�
int Pause_m; // �|�[�Y�i�x�~�j��ʂ̌��ʉ�
int Boss_m; // �{�X���̉�

// Thing �N���X�i�p���N���X�j
class Thing {

protected: // �q�N���X�Ɍp������

	float m_x; // x ���W
	float m_y; // y ���W
	int m_w; // ����
	int m_h; // �c��
	int m_s; // ���x

	float hit_x; // �����蔻��� x ���W
	float hit_y; // �����蔻��� y ���W
	float hit_w; // �����蔻��̉���
	float hit_h; // �����蔻��̏c��

	int life_max; // �ݒ�̗�
	int life_now; // ���̗̑�
	int energy_max; // �ݒ�����
	int energy_now; // ����ʂ̐�
	int damage; // ���Q��
	int energy; // �����
	bool remove_flag; // �폜�t���O
	void remove(); // �폜�t���O�� true �ɂ���

public:

	Thing(); // �R���X�g���N�^�i�폜�t���O�� false �Ɂj
	void SET_picture(const char* file_name, ThingType thing); // const char* �ɂ���@�N���X�ɉ摜��ݒu����
	virtual void SET_sound(const char* file_name, Sound sound); // const char* �ɂ���@�N���X�ɉ���ݒu����
	virtual void SET_position(int, int); // �������W��ݒ�
	void SET_hitarea(int, int, int, int); // �����蔻���ݒ�
	bool GET_remove(); // �폜�t���O�𓾂�
	bool HIT_test(ThingPointa&); // �����蔻��̊֐�

	virtual ThingType GET_TYPE() = 0; // �^�C�v�𓾂�i�������z�j
	virtual ThingType HIT_TYPE(); // ������ �^�C�v�� NONE �ɂ���i���z�j

	int GET_damage(); // ���Q�� �̏���
	int GET_energy(); // ����� �̏���

	virtual void move() = 0; // �s���͈́i�������z�j
	virtual void draw(); // �摜�̕`��
	void life_draw(); // �̗͂̕`��
	virtual void hit(int damage, int energy) = 0; // �����蔻�� true �̎��̏����i�������z�j
};

// PLAYER �N���X
class Player : public Thing {

private:

	int charge_time; // charge �J�E���g
	int dead_time; // dead �J�E���g�i�_�Łj
	bool beam_flag; // beam �t���O
	bool shot_flag; // shot �t���O

public:

	Player(); // �R���X�g���N�^�i�����ݒ�j
	ThingType GET_TYPE(); // ������ PLAYER �^�C�v�ƕԂ�
	ThingType HIT_TYPE(); // ������ Thing �^�C�v�� ENEMY1 �^�C�v�ƕԂ�
	void move(); // �s���͈́E�U���E�ǂ̓����蔻��
	void heart_draw(); // �̗͂̕`��
	void energy_draw(); // ����ʂ̕`��
	void draw(); // ���Q�ʂɑ΂��ē_��
	void hit(int damage, int energy); // �J�E���g��50�ɂ���
};

// SHOT �N���X�i�ʏ�e�j
class Shot : public Thing {

protected:

	float angle; // �~��̊p�x
	float center_x; // ���S x ���W�̐ݒ�
	float center_y; // ���S y ���W�̐ݒ�
	float shot_s; // �e�̑��x

public:

	Shot(); // �R���X�g���N�^�i�����ݒ�j
	ThingType GET_TYPE(); // ������ SHOT1 �^�C�v�ƕԂ�
	ThingType HIT_TYPE(); // ������G�� ENEMY1 �^�C�v�ƕԂ�
	void move(); // �E�����ց@��ʂ̒[�ō폜����
	void draw(); // �`��
	void hit(int damage, int energy); // �����E�폜
};

// THROUGH SHOT �N���X�i�ђʒe�j
class Through_Shot : public Shot {

public:

	Through_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// BEAM �N���X�i�����j
class Beam : public Shot {

public:

	Beam();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// RASEN SHOT �N���X�i�X�p�C�����e�j
class Rasen_Shot : public Through_Shot {

private:

	float rad; // ���a

public:

	void SET_position(int, int); // �����ʒu��ݒ肷��
	Rasen_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT1 �N���X�i�U�z�e�j
class Spray_Shot1 : public Through_Shot {

public:

	Spray_Shot1();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT2 �N���X�i��1�j
class Spray_Shot2 : public Spray_Shot1 {

public:

	Spray_Shot2();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT3 �N���X�i��1�j
class Spray_Shot3 : public Spray_Shot1 {

public:

	Spray_Shot3();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT4 �N���X�i��3�j
class Spray_Shot4 : public Spray_Shot1 {

public:

	Spray_Shot4();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT5 �N���X�i��3�j
class Spray_Shot5 : public Spray_Shot1 {

public:

	Spray_Shot5();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT6 �N���X�i��2�j
class Spray_Shot6 : public Spray_Shot1 {

public:

	Spray_Shot6();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// SPRAY SHOT7 �N���X�i��2�j
class Spray_Shot7 : public Spray_Shot1 {

public:

	Spray_Shot7();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// VORTEX SHOT1 �N���X�i�Q�e�j
class Vortex_Shot1 : public Shot {

public:

	Vortex_Shot1();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// VORTEX SHOT2 �N���X
class Vortex_Shot2 : public Vortex_Shot1 {

public:

	Vortex_Shot2();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// CHARGE SHOT �N���X
class Charge_Shot : public Shot {

private:

	bool charge_flag; // charge �t���O

public:

	Charge_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// PERIOD SHOT1 �N���X�i�����e�j
class Period_Shot1 : public Thing {

private:

	int shot_time; // ���˂���܂ł̎���
	int shot_count; // ���˂��鐔��ݒ�

public:

	Period_Shot1();
	// �����蔻��͖��� �^�C�v�� NONE �ŕԂ�
	ThingType GET_TYPE();
	ThingType HIT_TYPE();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// PERIOD SHOT2 �N���X�i��j
class Period_Shot2 : public Through_Shot {

public:

	Period_Shot2();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// PERIOD SHOT3 �N���X�i�E�j
class Period_Shot3 : public Period_Shot2 {

public:

	Period_Shot3();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// PERIOD SHOT4 �N���X�i���j
class Period_Shot4 : public Period_Shot2 {

public:

	Period_Shot4();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// PERIOD SHOT5 �N���X�i���j
class Period_Shot5 : public Period_Shot2 {

public:

	Period_Shot5();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// HOMING SHOT �N���X�i�ǌ��e�j
class Homing_Shot : public Shot {

public:

	Homing_Shot();
	void move(); // �G��ǂ�������
	void draw();
	void hit(int damage, int energy);
};

// PARABOLA SHOT �N���X�i�ǌ��E�������e�j
class Parabola_Shot : public Shot {

	// �������Ɋւ���ϐ�
	float a;
	float b;
	float c;

public:

	void SET_position(int, int); // �����ʒu�E���W�����߂�
	Parabola_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// ENEMY1 �N���X�i�ʏ�j
class Enemy1 : public Thing {

protected:

	int count; // ���j���� �폜����܂ł̐��l������
	int up_down; // �㉺����
	bool count_flag; // ���j�t���O

public:

	Enemy1();
	ThingType GET_TYPE(); // ������ ENEMY1 �^�C�v�ƕԂ�
	ThingType HIT_TYPE(); // ������G�� PLAYER �^�C�v�ƕԂ�
	void move();
	void draw();
	void hit(int damage, int energy); // ENEMY1~6�܂ŋ��ʐݒ�
};

// ENEMY2 �N���X�i�^�t�j
class Enemy2 : public Enemy1 {

public:

	Enemy2();
	void move();
	void draw();
};

// ENEMY3 �N���X�i�x�N�g���j
class Enemy3 : public Enemy1 {

public:

	Enemy3();
	void move();
	void draw();
};

// ENEMY4 �N���X�i�����j
class Enemy4 : public Enemy1 {

public:

	Enemy4();
	void move();
	void draw();
};

// ENEMY5 �N���X�i�ʏ�U���j
class Enemy5 : public Enemy1 {

public:

	Enemy5();
	void move();
	void draw();
};

// ENEMY6 �N���X�i�x�N�g���U���j
class Enemy6 : public Enemy1 {

public:

	Enemy6();
	void move();
	void draw();
};

// ENEMY BOSS1 �N���X�iSTAGE1~9�܂ŋ��ʁj
class Enemy_Boss1 : public Enemy1 {

protected:

	int add_speed; // ���x���グ��
	int Warn_p; // WARNING!!

public:

	Enemy_Boss1();
	void move();
	void life_draw(); // �̗͂̕`��
	void draw();
	void hit(int damage, int energy);
};

// ENEMY BOSS2 �N���X�iSTAGE10�j
class Enemy_Boss2 : public Enemy_Boss1 {

public:

	Enemy_Boss2();
	void move();
	void life_draw();
	void draw();
};

// ENEMY SHOT1 �N���X�i�{�X�j
class Enemy_Shot1 : public Thing {

public:

	Enemy_Shot1();
	ThingType GET_TYPE(); // ������ ENEMY_SHOT1 �^�C�v�ƕԂ�
	ThingType HIT_TYPE(); // ������G�� PLAYER �^�C�v�ƕԂ�
	void move();
	void draw();
	void hit(int damage, int energy);
};

// ENEMY SHOT2 �N���X�iENEMY5�E6�j
class Enemy_Shot2 : public Enemy_Shot1 {

public:

	Enemy_Shot2();
	void move();
	void draw();
	void hit(int damage, int energy);
};

// HEAL1 �N���X�i�̗͉񕜁j
class Heal1 : public Thing {

public:

	Heal1();
	ThingType GET_TYPE(); // ������ HEAL1 �^�C�v�ƕԂ�
	ThingType HIT_TYPE(); // ��������̂� PLAYER �^�C�v�ƕԂ�
	void move();
	void draw();
	void hit(int damage, int energy);
};

// HEAL2 �N���X�i����ʉ񕜁j
class Heal2 : public Heal1 {

public:

	Heal2();
	void draw();
	void move();
	void hit(int damage, int energy);
};

// GAME �N���X
class Game {

	std::list <ThingPointa> thing_list; // Thing �N���X�̃X�}�[�g�|�C���^�� list �^�f�[�^�\���ithing_list�j�ɓ����

private:

	int p_x; // �o�b�N�� x ���W�i���[�v�d�l�j
	int p_w; // �o�b�N�̉���
	int add_s; // �o�b�N�������ŉ�

	// �摜�Ǎ��p�ϐ�
	int Game_p; // �o�b�N�̉摜
	int Title_p; // SHOOTING GAME
	int Select_p; // STAGE SELECT
	int Number_p; // 1 2 3 4 5 6 7 8 9 10
	int Push_p; // PUSH SPACE
	int Over_p; // GAME OVER
	int Clear_p; // GAME CLEAR
	int Pause_p; // PAUSE
	int Esc_p; // ESC:TITLE SPACE:REPLAY

	// �t���O�p�ϐ�
	bool push_flag; // SPACE or BACK SPACE KEY�p�t���O
	bool game_flag; // true �ŃX�^�[�g����
	bool boss_flag; // BOSS �t���O
	bool space_flag; // PUSH SPACE �t���O

	// �X�R�A�L�^�p�ϐ�
	int high_score; // �n�C�X�R�A�ihigh_score < now_score �̏ꍇ�j
	int now_score; // �X�R�A�ɒu��
	int timer; // �o�ߎ��Ԃ�0�ɂ���
	int now_time; // �c�莞�Ԃ��L�^����
	int start_time; // 1s �P�ʂŌv������
	int limit_time; // ��������

public:

	static const int WIDTH = 1200; // ��ʂ̉���
	static const int HEIGHT = 600; // ��ʂ̏c��
	void ADD_list(ThingPointa&); // Thing �N���X�̃X�}�[�g�|�C���^�Ƀ��X�g��ǉ�����
	void ADD_score(int sc); // �X�R�A�̒ǉ�
	bool PUSH_space(); // SPACE KEY �̑���
	bool PUSH_back(); // BACK SPACE �̑���

	// �X�R�A�̋L�^����������֐�
	void LOAD_highscore(); // �X�R�A�Ǎ�
	void SAVE_highscore(); // �X�R�A�ۑ�

	void GAME_SET(); // �����ݒ�
	void GAME_ALL(); // ����
	void GAME_TITLE(); // �^�C�g�����
	void GAME_SELECT(); // �������
	void GAME_PLAY(); // �v���C���
	void GAME_OVER(); // �I�[�o�[���
	void GAME_CLEAR(); // �N���A���
	void GAME_END(); // �I��
};

Game* game; // GAME �N���X�̃��������m�ۂ��Ď��́i�C���X�^���X�j������

// Thing �N���X�̎���
void Thing::remove() {

	remove_flag = true; // �폜�t���O�� true�ɂ���
}

Thing::Thing() {

	remove_flag = false; // �폜�t���O�� false �ɂ���
	pause_flag = false; // �|�[�Y�i�x�~�j�t���O�� false �ɂ���
}

void Thing::SET_picture(const char* file_name, ThingType thing) {

	// loaded_picture ��0�̏ꍇ�@LoadGraph ������
	if (loaded_picture[thing] == 0) {

		loaded_picture[thing] = LoadGraph(file_name);
	}

	hit_w = m_w; // �����𓖂��蔻��ɒu��
	hit_h = m_h; // �����𓖂��蔻��ɒu��
	hit_x = hit_y = 0; // �摜�ɑ΂��鍶����W�� 0�ɂ���
}

void Thing::SET_sound(const char* file_name, Sound sound) {

	// loaded_sound ��0�̏ꍇ�@LoadSoundMem ������
	if (loaded_sound[sound] == 0) {

		loaded_sound[sound] = LoadSoundMem(file_name);
	}
}

void Thing::SET_position(int position_x, int position_y) {

	m_x = position_x; // �u���������l�� m_x�ix ���W�j �ɓ����
	m_y = position_y; // �u���������l�� m_y�iy ���W�j�ɓ����
}

void Thing::SET_hitarea(int h_x, int h_y, int h_w, int h_h) {

	hit_x = h_x; // ���ΓI x ���W��ݒ�
	hit_y = h_y; // ���ΓI y ���W��ݒ�
	hit_w = h_w; // ������ݒ�
	hit_h = h_h; // �c����ݒ�
}

bool Thing::GET_remove() {

	return remove_flag; // �폜�t���O��Ԃ�
}

ThingType Thing::HIT_TYPE() {

	return TYPE_NONE;
}

void Thing::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[GET_TYPE()], TRUE); // ���W�ʒu�ɕ`��ETRUE�͍��i�����ݒ�j�𓧖��F��
}

void Thing::life_draw() {

	if (0 < life_now) {

		DrawExtendGraph(m_x, m_y - 15, m_x + 65, m_y - 10, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(m_x, m_y - 15, m_x + (65 * life_now) / life_max, m_y - 10, loaded_picture[TYPE_LIFE], TRUE); // �̗͂ɔ������ւ����
	}
}

int Thing::GET_damage() {

	return damage;
}

int Thing::GET_energy() {

	return energy;
}

bool Thing::HIT_test(ThingPointa& other) {

	// �摜���m�̓����蔻��
	int x_1 = m_x + hit_x; // �����蔻��ix ���W�j
	int y_1 = m_y + hit_y; // �����蔻��iy ���W�j
	int w_1 = hit_w; // �����蔻��i�����j
	int h_1 = hit_h; // �����蔻��i�c���j
	int x_2 = other->m_x + other->hit_x; // �Ή����铖���蔻��ix ���W�j
	int y_2 = other->m_y + other->hit_y; // �Ή����铖���蔻��iy ���W�j
	int w_2 = other->hit_w; // �Ή����铖���蔻��i�����j
	int h_2 = other->hit_h; // �Ή����铖���蔻��i�c���j

	// �����蔻��̐ݒ�
	if (x_2 < x_1 + w_1 &&
		x_1 < x_2 + w_2 &&
		y_2 < y_1 + h_1 &&
		y_1 < y_2 + h_2) return true;

	return false; // ��L�ȊO�� false ��
}

// �ȉ��� PLAYER �N���X�̎���
Player::Player() {

	m_w = 80; // ����
	m_h = 50; // �c��
	m_s = 8; // ���x
	SET_picture("PLAYER.png", TYPE_PLAYER); // �摜
	SET_picture("HEART.png", TYPE_HEART);
	SET_picture("ENERGY.png", TYPE_ENERGY);
	SET_position(150, 300); // x�Ey ���W�̏����ʒu
	SET_hitarea(10, 10, 70, 40); // �����蔻��ݒ�
	life_max = 5; // �������C�t�ݒ�
	life_now = life_max; // ���݃��C�t�ɐݒ肵���l��u��
	energy_max = 1; // ��������͐ݒ�
	energy_now = energy_max; // ���ݓ���͂ɐݒ肵���l��u��
	damage = 0; // ���Q��
	energy = 0; // �����
	shot_flag = false; // shot �t���O�� false ��
	beam_flag = false; // beam �t���O�� false ��
	dead_time = 0; // deat_time ��0�ɐݒ�i�_�ŗp�j
	SET_sound("SHOT1.mp3", SOUND_SHOT1); // SHOT ��
	SET_sound("E ATTACK.mp3", SOUND_E_ATTACK); // ���Q��
}

ThingType Player::HIT_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Player::GET_TYPE() {

	return TYPE_PLAYER;
}

void Player::move() {

	// �_�ŃJ�E���g�� - 1����
	if (0 < dead_time) dead_time--;

	// �|�[�Y�i�x�~�j�t���O false �̏ꍇ
	if (!pause_flag) {

		// chage_time = 0 ������ beam �t���O false �̏ꍇ
		if (charge_time == 0 && !beam_flag) {

			// �ψʐݒ�
			if (CheckHitKey(KEY_INPUT_LEFT)) m_x -= m_s; // ����
			if (CheckHitKey(KEY_INPUT_RIGHT)) m_x += m_s; // ���E
			if (CheckHitKey(KEY_INPUT_UP)) m_y -= m_s; // ����
			if (CheckHitKey(KEY_INPUT_DOWN)) m_y += m_s; // ����

			// �ǂɑ΂��铖���蔻��ݒ�
			if (m_x < 0) m_x = 0; // ��ʍ�
			if (Game::WIDTH < m_x + m_w) m_x = Game::WIDTH - m_w; // ��ʉE
			if (m_y < 0) m_y = 0; // ��ʏ�
			if (Game::HEIGHT < m_y + m_h) m_y = Game::HEIGHT - m_h; // ��ʉ�
		}

		// �ʏ�e�i�a�j
		if (CheckHitKey(KEY_INPUT_B) && shot_count % 8 == 0) {

			if (!shot_flag) { // shot �t���O false �̏ꍇ

				ThingPointa shot(new Shot); // SHOT �N���X�쐬�@���̃A�h���X�� Thing �N���X�̃X�}�[�g�|�C���^�ɓn��
				shot->SET_position(m_x + m_w - 10, m_y + 25); // SHOT �̏����ʒu�ݒ�
				game->ADD_list(shot); // Thing ���X�g�� SHOT �A�h���X�ǉ�
				PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK); // SHOT��
			}
		}

		// �ђʒe�i�l�j
		else if (CheckHitKey(KEY_INPUT_M) && shot_count % 10 == 0) {

			// ����� 4�ȏ�̏ꍇ ���ˉ�
			if (4 <= energy_now) {

				if (!shot_flag) {

					ThingPointa through_shot(new Through_Shot);
					through_shot->SET_position(m_x + m_w - 30, m_y + 25);
					game->ADD_list(through_shot);
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);
				}
			}
		}

		// �����i�b�j
		else if (CheckHitKey(KEY_INPUT_C)) {

			// ����� 5�ȏ�̏ꍇ ���ˉ�
			if (5 <= energy_now) {

				if (!beam_flag) { // beam �t���O false �̏ꍇ

					ThingPointa beam(new Beam);
					beam->SET_position(m_x + m_w + 15, m_y - 10);
					game->ADD_list(beam);
					beam_flag = true; // �A�Ŏd�l
					PlaySoundMem(loaded_sound[SOUND_BEAM], DX_PLAYTYPE_BACK);
				}
			}
		}

		// �X�p�C�����e�i�q�j
		else if (CheckHitKey(KEY_INPUT_R) && shot_count % 6 == 0) {

			// ����� 3�ȏ�̏ꍇ ���ˉ�
			if (3 <= energy_now) {

				if (!shot_flag) {

					ThingPointa rasen_shot(new Rasen_Shot);
					rasen_shot->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(rasen_shot);
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);
				}
			}
		}

		// �U�z�e�i�r�j
		else if (CheckHitKey(KEY_INPUT_S) && shot_count % 10 == 0) {

			// ����� 9�ȏ�̏ꍇ ���ˉ�
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
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK); // SHOT��
				}
			}
		}

		// �Q�e�i�u�j
		else if (CheckHitKey(KEY_INPUT_V) && shot_count % 4 == 0) {

			// ����� 10�̏ꍇ ���ˉ�
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

		// CHAGE �e�i�n�j
		else if (CheckHitKey(KEY_INPUT_O)) {

			// ����� 2�ȏ�̏ꍇ ���ˉ�
			if (2 <= energy_now) {

				// ���ˏ�������
				if (charge_time <= 5) charge_time++;

				if (charge_time == 5) {

					ThingPointa charge_shot(new Charge_Shot);
					charge_shot->SET_position(m_x + m_w + 15, m_y + 35);
					game->ADD_list(charge_shot);
					PlaySoundMem(loaded_sound[SOUND_CHARGE], DX_PLAYTYPE_BACK);
				}
			}
		}

		// �����e�i�y�j
		else if (CheckHitKey(KEY_INPUT_Z)) {

			// ����� 8�ȏ�̏ꍇ ���ˉ�
			if (8 <= energy_now) {

				if (!shot_flag) {

					ThingPointa period_shot1(new Period_Shot1);
					period_shot1->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(period_shot1);
					shot_flag = true; // �A�ł���
					PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
				}
			}
		}

		// �ǌ��i�����j�e�i�g�j
		else if (CheckHitKey(KEY_INPUT_H) && shot_count % 28 == 0) {

			// ����� 7�ȏ�̏ꍇ ���ˉ�
			if (7 <= energy_now) {

				// �c������G������ꍇ
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

		// �ǌ��E�������e�i�o�j
		else if (CheckHitKey(KEY_INPUT_P) && shot_count % 28 == 0) {

			// ����� 6�ȏ�̏ꍇ ���ˉ�
			if (6 <= energy_now) {

				// �c������G������ꍇ
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

		// �������Ȃ��ꍇ
		else {

			shot_flag = false; // shot �t���O�� false��
			beam_flag = false; // beam �t���O �� false ��
			charge_time = 0; // charge_time �� 0 ��
		}
	}

	// ���C�t 0�ɂȂ����ꍇ
	if (life_now <= 0) {

		scene = 3; // �I�[�o�[��ʂ�
		StopSoundMem(Play_m); // �v���C���̉����~
		StopSoundMem(Boss_m); // �{�X���̉����~
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // �I�[�o�[��
	}

	// ���C�t�̏���ݒ�
	if (10 <= life_now) life_now = 10;

	// ����ʂ̏���ݒ�
	if (10 <= energy_now) energy_now = 10;
}

void Player::heart_draw() {

	if (0 < life_now) {

		// ���݂̗̑͂ɂ��n�[�g�̐��𒲐�����
		for (int i = 0; i < life_now; i++) {

			DrawExtendGraph(5 + i * 45, 5, 55 + i * 45, 45, loaded_picture[TYPE_HEART], TRUE);
		}
	}
}

void Player::energy_draw() {

	if (0 < energy_now) {

		// ���݂̓���ʂɂ��n�[�g�̐��𒲐�����
		for (int i = 0; i < energy_now; i++) {

			DrawExtendGraph(460 + i * 45, 5, 510 + i * 45, 45, loaded_picture[TYPE_ENERGY], TRUE);
		}
	}

	// ���݂̓���ʂɂ��i�n�[�g�̏�Ɂj������`��
	DrawFormatString(480, 15, GetColor(255, 255, 255), "B");

	// �����2~10�ȏ�̏ꍇ
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

	heart_draw(); // �̗�
	energy_draw(); // �����

	if (dead_time % 5 == 0) Thing::draw(); // 5�Ŋ���؂��ꍇ �_�ł��ĕ`�悷��
}

void Player::hit(int damage, int energy) {

	// �G�̏ꍇ
	if (dead_time <= 0 && 0 < damage) {

		dead_time = 50; // �_�ŃJ�E���g�� 50��
		life_now -= damage; // ���݂̗̑͂�� ���Q�ʂ��}�C�i�X����
		PlaySoundMem(loaded_sound[SOUND_E_ATTACK], DX_PLAYTYPE_BACK); // ���Q��
	}

	// HEAL1 �̏ꍇ
	if (damage < 0) life_now -= damage; // �̗͂̑���

	// HEAL2 �̏ꍇ
	if (energy < 0) energy_now -= energy; // ����ʂ̑���
}

// SHOT �N���X�i�ʏ�e�j�̎���
Shot::Shot() {

	m_w = 12; // ����
	m_h = 12; // �c��
	m_s = 10; // ���x
	damage = 5; // ���Q��
	SET_picture("SHOT1.png", TYPE_SHOT1); // �摜
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK); // ���ʉ�
}

ThingType Shot::GET_TYPE() {

	return TYPE_SHOT1;
}

ThingType Shot::HIT_TYPE() {

	return TYPE_ENEMY1;
}

void Shot::move() {

	if (!pause_flag) m_x += m_s; // ���x��10�ɂ���

	if (Game::WIDTH < m_x) remove(); // ��ʍ��ō폜����
}

void Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT1], TRUE);
}

void Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// THROUGH SHOT �N���X�i�ђʒe�j�̎���
Through_Shot::Through_Shot() {

	m_w = 34;
	m_h = 15;
	m_s = 20;
	damage = 1;
	SET_picture("SHOT2.png", TYPE_SHOT2);
	SET_sound("SHOT2.mp3", SOUND_SHOT2);
}

void Through_Shot::move() {

	if (!pause_flag) m_x += m_s; // ���x��20�ɂ���

	if (Game::WIDTH < m_x + m_w) remove();
}

void Through_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Through_Shot::hit(int damage, int energy) {

	// �ђʂ��邽�� remove()�@�͎������Ȃ�
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// BEAM �N���X�i�����j�̎���
Beam::Beam() {

	m_w = 0; // �������邽�� ������0��
	m_h = 80;
	m_s = 15;
	damage = 1;
	SET_picture("BEAM.png", TYPE_BEAM);
	SET_sound("BEAM.mp3", SOUND_BEAM);
}

void Beam::move() {

	if (!pause_flag) {

		m_w += m_s;
		hit_w = m_w; // �����蔻��ɒu������
	}

	if (Game::WIDTH + 100 < m_x + m_w) remove();
}

void Beam::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_BEAM], TRUE);
}

void Beam::hit(int damage, int energy) {

	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// RASEN SHOT �N���X�i�X�p�C�����e�j�̎���
Rasen_Shot::Rasen_Shot() {

	m_w = 34;
	m_h = 15;
	damage = 10;
	angle = 0; // �p�x��0��
	rad = 0; // ���a��0��
}

void Rasen_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;
}

void Rasen_Shot::move() {

	if (!pause_flag) {

		rad += 0.8; // �~�̔��a�ɉ���������
		angle += 8 / rad; // �p�x������������i�p���x�𒲐��j

		// �X�p�C��������v�Z
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

// SPRAY SHOT1~7 �N���X�i�U�z�e�j�̎���
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

		// �p�x30�x�̎O�p�`
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

		// �p�x30�x�̎O�p�`
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

		// �p�x10�x�̎O�p
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

		// �p�x10�x�̎O�p�`
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

		// �p�x20�x�̎O�p�`
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

		// �p�x20�x�̎O�p�`
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

// VORTEX SHOT1�E2 �N���X�i�Q�e�j�̎���
Vortex_Shot1::Vortex_Shot1() {

	m_w = 13;
	m_h = 13;
	m_s = 8;
	damage = 1;
	angle = 0; // �p�x��0��
}

void Vortex_Shot1::move() {

	if (!pause_flag) {

		angle += 0.01;
		m_x += m_s;
		m_y = m_y + 10 * cos(angle * 16); // �R�T�C���J�[�u�̉��p
	}

	if (Game::WIDTH < m_x) remove();
}

void Vortex_Shot1::draw() {

	// �Q��Ɍ����邽�߂ɑ傫���𐏎��ς���
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

// CHARGE SHOT �N���X�i�g��e�j�̎���
Charge_Shot::Charge_Shot() {

	m_w = 0;
	m_h = 0;
	m_s = 15;
	damage = 0;
	SET_picture("CHARGE SHOT.png", TYPE_CHARGE_SHOT);
	SET_sound("CHARGE.mp3", SOUND_CHARGE); // CHARGE���̉�
	SET_sound("CHARGE SHOT.mp3", SOUND_CHARGE_SHOT); // ���ˉ�
	charge_flag = false; // charge �t���O�� false ��
}

void Charge_Shot::move() {

	if (!charge_flag) {

		if (CheckHitKey(KEY_INPUT_O)) {

			// �U����MAX��50�Ƃ���i�������Q�ʂ�0�ɂ��Ă��邽�߁j
			if (damage < 50) {

				damage++;

				m_x += 1;
				m_y -= 2;
				m_w = 2 * damage; // ���Q�ʂ̑����ɔ��� �傫���Ȃ�
				m_h = 4 * damage;

				// �����蔻��̌덷����
				hit_w = m_w + 20;
				hit_h = m_h;
			}

			// ���Q�� 50�����̏ꍇ
			else {

				charge_flag = true;
				StopSoundMem(loaded_sound[SOUND_CHARGE]);
				PlaySoundMem(loaded_sound[SOUND_CHARGE_SHOT], DX_PLAYTYPE_BACK);
			}
		}

		// �n�������Ă��Ȃ��ꍇ
		else {

			charge_flag = true;
			StopSoundMem(loaded_sound[SOUND_CHARGE]);
			PlaySoundMem(loaded_sound[SOUND_CHARGE_SHOT], DX_PLAYTYPE_BACK);
		}
	}

	else if (!pause_flag) m_x += m_s; // ���x��15�ɂ���

	if (Game::WIDTH < m_x) remove();
}

void Charge_Shot::draw() {

	// angle �̒l��2�Ŋ��� �]��0�ꍇ �`�悷��
	if ((int)angle % 2 == 0) {

		DrawRotaGraph((2 * m_x + m_w) / 2, (2 * m_y + m_h) / 2, (double)m_w / 50, angle, loaded_picture[TYPE_CHARGE_SHOT], TRUE);
	}

	if (!pause_flag) angle += 30; // angle �̒l��35����������
}

void Charge_Shot::hit(int damage, int energy) {

	remove();
	StopSoundMem(loaded_sound[SOUND_CHARGE]);
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// PERIOD SHOT1 �N���X�i�����e�j�̎���
Period_Shot1::Period_Shot1() {

	m_w = 15;
	m_h = 15;
	m_s = 12;
	damage = 0;
	shot_time = 30; // ���˂���܂ł̎��Ԃ�30��
	shot_count = 1; // 5�񔭎˂��邽�߂� ������1��
	SET_picture("SHOT3.png", TYPE_SHOT3);
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK); 
}

ThingType Period_Shot1::GET_TYPE() {

	return TYPE_SHOT3;
}

ThingType Period_Shot1::HIT_TYPE() {

	return TYPE_NONE; // �{�̂ɂ͓����蔻��͖���
}

void Period_Shot1::move() {

	if (!pause_flag) {

		if (0 <= shot_time) m_x += m_s; // ���˂���܂ŉE������

		if (shot_time < 0) {

			// 5�񔭎�
			if (shot_time % 10 == 0 && shot_count <= 5) {

				// �����蔻��L��̒e�𔭎˂���
				// �����
				ThingPointa period_shot2(new Period_Shot2());
				game->ADD_list(period_shot2); //
				period_shot2->SET_position(m_x + 1, m_y - 10);

				// �E����
				ThingPointa period_shot3(new Period_Shot3());
				game->ADD_list(period_shot3);
				period_shot3->SET_position(m_x - 5, m_y + 2);

				// ������
				ThingPointa period_shot4(new Period_Shot4());
				game->ADD_list(period_shot4);
				period_shot4->SET_position(m_x + 1, m_y - 2);

				// ������
				ThingPointa period_shot5(new Period_Shot5());
				game->ADD_list(period_shot5); //
				period_shot5->SET_position(m_x - 10, m_y + 2);

				PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);

				shot_count++;
			}

			if (5 < shot_count) remove(); // 5�񔭎˂ō폜����
		}

		shot_time--;
	}
}

void Period_Shot1::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT3], TRUE);
}

void Period_Shot1::hit(int damage, int energy) {}

// PERIOD SHOT2�i��j�N���X�̎���
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

// PERIOD SHOT3�i�E�j�N���X�̎���
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

// PERIOD SHOT4�i���j�N���X�̎���
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

// PERIOD SHOT5�i���j�N���X�̎���
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

// HORMING SHOT �N���X�i�ǌ��e�j�̎���
Homing_Shot::Homing_Shot() {

	m_w = 12;
	m_h = 12;
	m_s = 10;
	damage = 20;
	shot_s = 10; // shot_s ��8�ɂ���
}

void Homing_Shot::move() {

	if (!pause_flag) {

		//�c������G������ꍇ
		if (0 < enemy_num) {

			// �ǔ�����v�Z
			// sqrt() �͐�Βl�̌v�Z
			// pow() �ׂ͂���̌v�Z
			m_x += ((enemy_x - m_x) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
			m_y += ((enemy_y - m_y) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
		}

		else m_x += m_s; // �c������G�����Ȃ��ꍇ �E������
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

// PARABOLA SHOT �N���X�i�ǌ��E�������e�j�̎���
void Parabola_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;

	// �s��v�Z�ɂ��O�_�̍��W�����߂�
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
	shot_s = 0; // shot_s ��0��
}

void Parabola_Shot::move() {

	if (!pause_flag) {

		shot_s += 8;
		m_x = center_x + shot_s;
		m_y = a * pow(m_x, 2) + b * m_x + c; // �������ɕ`��
	}
}

void Parabola_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT1], TRUE);
}

void Parabola_Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

// ENEMY1~6�N���X�̎���
Enemy1::Enemy1() {

	m_w = 80;
	m_h = 50;

	// STAGE�ɂ�葬�x��ݒ�
	if (stage <= 6) m_s = 8;
	if (7 <= stage) m_s = 10;

	life_max = 10; // �̗�10
	life_now = life_max; // �ݒ�̗͂����݂̗̑͂ɒu��
	damage = 1; // ���Q��1
	energy = 0; // �����0
	count = 0; // �̗� != 0 �� count ��0��
	count_flag = false; // �̗� != 0 �� count �t���O�� false ��
	SET_picture("ENEMY1.png", TYPE_ENEMY1);
	SET_picture("BURN.png", TYPE_BURN);
	SET_sound("BREAK.mp3", SOUND_BREAK);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h)); // �����ʒu
}

ThingType Enemy1::GET_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Enemy1::HIT_TYPE() {

	return TYPE_PLAYER;
}

void Enemy1::move() {

	if (!pause_flag) m_x -= m_s; // ���x8 or 10

	// ���j�� count ��13�̒l�𓾂�
	if (0 < count) {

		count--;
		count_flag = true;
	}

	// ��ʍ��ɓ���ꍇ
	if (m_x + m_w < 0) {

		remove(); // �폜����

		if (score < 20000 && 0 < score) game->ADD_score(-100); // �X�R�A���}�C�i�X����

		if (0 < enemy_num) enemy_num -= 1; // enemy_num ���}�C�i�X����
	}

	// HOMING�EPARABOLA SHOT�N���X�i�ǔ��e�j����������� �O���[�o���ϐ��ɒl��u������
	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy1::draw() {

	life_draw(); // �̗͂̕`��

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY1], TRUE);
	}

	// ���j�� count �ɂ�13�Ecount_flag �� move() �� true ��
	if (count_flag && 0 <= count) {

		// ���j�G�t�F�N�g��`��
		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		// count <= 0 �̏ꍇ �폜����
		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200); // �X�R�A�ɓ��_��ǉ�����

			if (0 < enemy_num) enemy_num -= 1; // enemy_num ���}�C�i�X����
		}
	}
}

void Enemy1::hit(int damage, int energy) {

	life_now -= damage; // �̗͂��}�C�i�X����

	// �̗�0�̏ꍇ ���j�G�t�F�N�g����������
	if (life_now <= 0 && count == 0) {

		count = 13; // count ��13�̒l������
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
	up_down = 6; // �㉺�����̑��x��6��
	count = 0;
	count_flag = false;
	SET_picture("ENEMY3.png", TYPE_ENEMY3);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy3::move() {

	if (!pause_flag) {

		m_x -= m_s;
		m_y += up_down; // �㉺�����̑��x
	}

	// �ǂ̓����蔻��
	if (m_y < 0) up_down = -up_down; // ��
	if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // ��

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
	up_down = 6; // �㉺�����̑��x��6��
	count = 0;
	count_flag = false;
	SET_picture("ENEMY5.png", TYPE_ENEMY5);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy5::move() {

	if (!pause_flag) {

		// ����̍��W�܂ō�������
		if (1000 < m_x) m_x -= m_s;

		// ����̍��W�ŏ㉺������
		if (m_x <= 1000) {

			m_y -= up_down;

			// �ǂ̓����蔻��
			if (m_y < 0) up_down = -up_down; // ��
			if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // ��

			if (GetRand(60) == 0) {

				ThingPointa enemy_shot2(new Enemy_Shot2); // ENEMY SHOT2 �N���X�쐬�@���̃A�h���X�� Thing �N���X�̃X�}�[�g�|�C���^�ɓn��
				enemy_shot2->SET_position(m_x - 10, m_y + 25); // �����z�u�̐ݒ�
				game->ADD_list(enemy_shot2); // Thing ���X�g�� ENEMY SHOT2 �A�h���X�ǉ�

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

		// �ǂ̓����蔻��
		if (m_y < 0) up_down = - up_down; // ��
		if (Game::HEIGHT < m_y + m_h) up_down = - up_down; // ��
		if (m_x < 0) m_s = - 2; // ��
		if (Game::WIDTH + 200 < m_x + m_w) remove(); // ��ʉE�ō폜����

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

// ENEMY BOSS1�E2�N���X�̎���
Enemy_Boss1::Enemy_Boss1() {

	// ENEMY_BOSS1 ���C�t�ݒ�
	if (stage == 1 || stage == 4 || stage == 7) life_max = 3000; // STAGE1�E4�E7
	if (stage == 2 || stage == 5 || stage == 8) life_max = 3500; // STAGE2�E5�E8
	if (stage == 3 || stage == 6 || stage == 9) life_max = 4000; // STAGE3�E6�E9

	m_w = 350;
	m_h = 390;
	life_now = life_max;
	damage = 1;
	energy = 0;
	up_down = 3; // �㉺�������x
	add_speed = 0; // �̗͂������ɂȂ�܂ŉ�����0��
	count = 0;
	count_flag = false;

	// STAGE�ɂ��`�悷��摜��ݒ�
	if (stage <= 3) SET_picture("ENEMY BOSS1.png", TYPE_ENEMY_BOSS1);
	if (4 <= stage && stage <= 6) SET_picture("ENEMY BOSS2.png", TYPE_ENEMY_BOSS2);
	if (7 <= stage && stage <= 9) SET_picture("ENEMY BOSS3.png", TYPE_ENEMY_BOSS3);

	SET_hitarea(150, 50, 340, 340); // �����蔻��̐ݒ�
	Warn_p = LoadGraph("WARNING.png"); // WARNING!!
	SET_position(Game::WIDTH, 140);
}

void Enemy_Boss1::move() {

	// �̗͂������ȉ��̏ꍇ �������グ��
	if (life_now < life_max / 2) add_speed = 3;

	if (!pause_flag) {

		// ����̍��W�܂ō�����
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

		// ����̍��W�̏ꍇ �㉺����
		if (m_x <= 790) {

			m_y += up_down;

			// �ǂ̓����蔻��
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

	int life_x = Game::WIDTH - 245; // ���W�̒���

	if (0 < life_now) {

		DrawExtendGraph(life_x, 5, life_x + 245, 30, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(life_x, 5, life_x + (245 * life_now) / life_max, 30, loaded_picture[TYPE_LIFE], TRUE);
	}
}

void Enemy_Boss1::draw() {

	life_draw(); // �̗�

	if (0 < life_now) {

		SetFontSize(20); // �����T�C�Y�̐ݒ�
		DrawFormatString(Game::WIDTH - 250, 5, GetColor(255, 255, 255), "%d", life_now); // �̗͐��l�̕`��
	}

	if (!count_flag) {

		// STAGE�ɂ��摜��ݒ�
		if (stage <= 3) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS1], TRUE);
		if (4 <= stage && stage <= 6) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS2], TRUE);
		if (7 <= stage && stage <= 9) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS3], TRUE);
	}

	if (count_flag && 0 <= count) {

		DrawExtendGraph(m_x - 6 * count, m_y - 6 * count, m_x + m_w + 6 * count, m_y + m_h + 6 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		if (count <= 0 && !count_flag) {

			remove();
			scene = 4; // �{�X�����j�� �N���A��ʂ�
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
	life_max = 5000; // ENEMY BOSS2 ���C�t�ݒ�
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

				// ��
				ThingPointa enemy_shot1_1(new Enemy_Shot1);
				enemy_shot1_1->SET_position(m_x + m_w - 250, m_y + 190);
				game->ADD_list(enemy_shot1_1);

				// �^�񒆉�
				ThingPointa enemy_shot1_2(new Enemy_Shot1);
				enemy_shot1_2->SET_position(m_x + m_w - 210, m_y + 220);
				game->ADD_list(enemy_shot1_2);

				// �^�񒆏�
				ThingPointa enemy_shot1_3(new Enemy_Shot1);
				enemy_shot1_3->SET_position(m_x + m_w - 210, m_y + 160);
				game->ADD_list(enemy_shot1_3);

				// �E��
				ThingPointa enemy_shot1_4(new Enemy_Shot1);
				enemy_shot1_4->SET_position(m_x + m_w - 170, m_y + 250);
				game->ADD_list(enemy_shot1_4);

				// �E��
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

// ENEMY SHOT1 �N���X�i�{�X�j�̎���
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

// ENEMY SHOT2 �N���X�iENEMY5�E6�j�̎���
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

// HEAL1�i�̗͉񕜁j�N���X�̎���
Heal1::Heal1() {

	m_w = 25;
	m_h = 21;
	m_s = 6;
	damage = -1; // �l�̓}�C�i�X�ɂ��ĉ񕜂ɂ���
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

// HEAL2�i����ʉ񕜁j�N���X�̎���
Heal2::Heal2() {

	m_w = 25;
	m_h = 21;
	m_s = 10;
	damage = 0;
	energy = -1; // �l���}�C�i�X�ɂ��ē���ʉ񕜂ɂ���
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

// GAME �N���X�̎���
void Game::ADD_list(ThingPointa & add) {

	thing_list.push_back(add); // Thing ���X�g�̉��� Thing �N���X�� add ��ǉ�����
}

void Game::ADD_score(int sc) {

	score += sc; // �X�R�A��ǉ�
}

bool Game::PUSH_space() {

	if (CheckHitKey(KEY_INPUT_SPACE)) {

		// push_flag false �̏ꍇ
		if (!push_flag) {

			push_flag = true;
			return true;
		}
	}

	// ��L�ȊO false ��
	else push_flag = false;

	return false; // false �ŕԂ�
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

	// text �̒l��Ǎ�����i�n�C�X�R�A�j
	FILE* file;
	fopen_s(&file, "HIGH SCORE.txt", "r");
	fscanf_s(file, "%d", &high_score);
	fclose(file);
}

void Game::SAVE_highscore() {

	// text �̒l���L�^����i�X�R�A�j
	FILE* file;
	fopen_s(&file, "HIGH SCORE.txt", "w");
	fprintf(file, "%d", now_score);
	fclose(file);
}

void Game::GAME_SET() {

	game = this; // ���C���X�^���X�̃A�h���X��ێ�����i�ÓI�j
	scene = 0; // �^�C�g����ʂ�
	stage = 0; // STAGE��0�ɂ���
	score = 0; // �X�R�A�� 0��
	p_x = 0; // �o�b�N�� x ���W������ɐݒ�
	p_w = WIDTH; // �o�b�N�̉����� WIDTH �ɒu��
	limit_time = 500; // �������Ԃ�500��

	LOAD_highscore(); // �X�R�A�̓Ǎ�
	start_time = GetNowCount(); // 1s �P�ʂɂ���

	ChangeWindowMode(TRUE); // �E�B���h�E���J��
	SetGraphMode(WIDTH, HEIGHT, 32); // �E�B���h�E�̉����E�c���E�J���[�̐ݒ�
	DxLib_Init(); // DX���C�u����������������
	SetDrawScreen(DX_SCREEN_BACK); // ���ʂɉ摜��`��

	// �摜�̓Ǎ�
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

	// ���y�t�@�C���̓Ǎ�
	Title_m = LoadSoundMem("TITLE.mp3");
	Play_m = LoadSoundMem("GAME PLAY.mp3");
	Over_m = LoadSoundMem("GAME OVER.mp3");
	Clear_m = LoadSoundMem("GAME CLEAR.mp3");
	Pause_m = LoadSoundMem("PAUSE.mp3");
	Boss_m = LoadSoundMem("BOSS GAME.mp3");

	PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // �^�C�g�����Đ�
}

void Game::GAME_ALL() {

	// �C�x���g��������������֐�
	while (!ProcessMessage()) {

		ClearDrawScreen(); // �摜���폜�i�E���̏������j

		if (scene == 0) GAME_TITLE();

		if (scene == 1) GAME_SELECT();

		if (scene == 2) GAME_PLAY();

		if (scene == 3) GAME_OVER();

		if (scene == 4) GAME_CLEAR();

		ScreenFlip(); // �摜���I���e�ɏo��
	}
}

// scene == 0 �̎��@�^�C�g����ʂɂ���
void Game::GAME_TITLE() {

	SetBackgroundColor(0, 0, 0); // �o�b�N�̐F�����F�ɐݒ�
	DrawExtendGraph(10, 200, WIDTH - 10, HEIGHT - 200, Title_p, TRUE); // �^�C�g���̕`��
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE �̕`��

	// �����̕`��
	SetFontSize(20); // �T�C�Y�̐ݒ�
	DrawFormatString(10, 10, GetColor(255, 255, 255), "BEST SCORE:%d", high_score);

	thing_list.clear(); // Thing ���X�g������������
	score = 0; // �X�R�A��0��
	add_s = 0; // STAGE10�̏ꍇ �o�b�N���������������ɒu������

	// SPACE KEY ���������ꍇ�@SELECT��ʂ�
	if (PUSH_space()) scene = 1;

	game_flag = false; // game_flag �� false ��
	boss_flag = false; // �{�X�t���O�� false ��
	space_flag = false; // PUSH SPACE �t���O�� false ��
}

// scene == 1 �̎��@�I�����
void Game::GAME_SELECT() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(50, 200, WIDTH - 50, HEIGHT - 200, Select_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Number_p, TRUE); // PUSH SPACE �̕`��

	// �ȉ��� STAGE1~10�̕���
	// stage == 1 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_1)) {

		scene = 2; // �v���C���
		stage = 1; // STAGE1

		// PLAYER ����
		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 2 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_2)) {

		scene = 2;
		stage = 2; // STAGE2

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 3 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_3)) {

		scene = 2;
		stage = 3; // STAGE3

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 4 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_4)) {

		scene = 2;
		stage = 4; // STAGE4

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 5 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_5)) {

		scene = 2;
		stage = 5; // STAGE5

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 6 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_6)) {

		scene = 2;
		stage = 6; // STAGE6

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 7 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_7)) {

		scene = 2;
		stage = 7; // STAGE7

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 8 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_8)) {

		scene = 2;
		stage = 8; // STAGE8

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 9 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_9)) {

		scene = 2;
		stage = 9; // STAGE9

		ThingPointa player(new Player);
		ADD_list(player);
	}

	// stage == 10 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_0)) {

		scene = 2;
		stage = 10; // STAGE10

		ThingPointa player(new Player);
		ADD_list(player);
	}
}

// scene == 2 �̎��@�v���C���
void Game::GAME_PLAY() {

	// �o�b�N�̕`��
	DrawExtendGraph(p_x, 0, p_w, HEIGHT, Game_p, TRUE);
	DrawExtendGraph(p_x + WIDTH, 0, p_w + WIDTH, HEIGHT, Game_p, TRUE); // �񖇖ڂ̃��[�v

	if (!pause_flag) {

		// STAGE1�`3�̏ꍇ
		if (stage <= 3) {

			// �G�t�F�N�g�̎����i�o�b�N�����֓������j
			p_x -= 2 + add_s;
			p_w -= 2 + add_s;
		}

		// STAGE4�`9�̏ꍇ
		if (4 <= stage && stage <= 9) {

			p_x -= 3 + add_s;
			p_w -= 3 + add_s;
		}

		// STAGE10�̏ꍇ
		if (stage == 10) {

			p_x -= 4 + add_s;
			p_w -= 4 + add_s;
		}
	}

	// STAGE10�@�{�X�̏ꍇ�̓o�b�N�������œ�����
	if (add_s < 40 && boss_flag) add_s += 1;

	// �o�b�N�̃��[�v
	if (p_x <= -1200) {

		p_x = 0;
		p_w = WIDTH;
	}

	// for_each�̓R���e�i�ilist etc.�j�� first-last �ɑ΂��Ċ֐��̓K�p����������
	// �\���� [CAPTURE] (���������X�g) {�֐��̖{��}
	// Thing ���X�g�ɓ���S�ẴN���X�� move()�֐������g�p����
	for_each(thing_list.begin(), thing_list.end(), [] (ThingPointa & Thing) {Thing->move();});

	// Thing ���X�g�ɓ���S�ẴN���X�� draw()�֐������g�p����
	for_each(thing_list.begin(), thing_list.end(), [] (ThingPointa & Thing) {Thing->draw();});

	// �����蔻��̎���
	// �͈͑S�ẴN���X�Ɋ֐����u���i�Q�Ɓj�v�ɂ��邱�Ƃ� �֐����� mob ���g�p�o����
	// ��̃N���X���g�p���Ă��邽�� ���̕����������̌`
	// ������ꍇ ������ hit()�֐���K�p����
	for_each(thing_list.begin(), thing_list.end(), [&] (ThingPointa & main) {

		if (main->HIT_TYPE() == TYPE_NONE) return; // TYPE_NONE�̏ꍇ�@��������

		for_each(thing_list.begin(), thing_list.end(), [&] (ThingPointa & mob) {

			// ������ HIT �^�C�v�EGET �^�C�v�𔻕ʂ��� �Ԃ��^�C�v�̓������ꍇ
			if (main->HIT_TYPE() == mob->GET_TYPE()) {

				// ������ꍇ
				if (main->HIT_test(mob)) {

					// hit()�֐���K�p����
					// ���Q�ʁE����ʂ̌v�Z�� GET_damage()�֐��EGET_energy()�֐����g�p����
					main->hit(mob->GET_damage(), mob->GET_energy());
					mob->hit(main->GET_damage(), main->GET_energy());
				}
			}
		});
	});

	// shot_count �𑫂�������
	shot_count++;

	// game_flag true �̏ꍇ
	if (game_flag) {

		// �������Ԃ̌v�Z
		timer = (GetNowCount() - start_time) / 1000 - limit_time;
		now_time = -timer;

		SetFontSize(20);
		DrawFormatString(WIDTH - 120, HEIGHT - 30, GetColor(255, 255, 255), "TIME:%d", now_time); // �������Ԃ̕`��

		// �|�[�Y�i�x�~�j�t���O false�ł���ꍇ�@�G�E�񕜂𐶐�
		if (!pause_flag) {

			// �X�R�A�@20000�����̏ꍇ
			if (score < 20000) {

				// �G�̏o���iSTAGE1~9�j
				// ENEMY1�i���ʁj
				if (stage == 1 || stage == 2 || stage == 3 || stage == 5 || stage == 6 || stage == 7) { // �o������ STAGE �ݒ�

					if (GetRand(40) == 0) {

						ThingPointa enemy1(new Enemy1); // �G����
						ADD_list(enemy1); // Thing ���X�g�� ENEMY1 �A�h���X��ǉ�

						if (0 <= enemy_num) enemy_num += 1; // enemy_num ��+�P����
					}
				}

				// ENEMY2�i�^�t�j
				if (stage == 1 || stage == 2 || stage == 3 || stage == 4 || stage == 5 || stage == 6 || stage == 8) {

					if (GetRand(80) == 0) {

						ThingPointa enemy2(new Enemy2);
						ADD_list(enemy2);

						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				// ENEMY3�i�x�N�g���j
				if (stage == 2 || stage == 4 || stage == 7 || stage == 8) {

					if (GetRand(100) == 0) {

						ThingPointa enemy3(new Enemy3);
						ADD_list(enemy3);

						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				// ENEMY4�i�����j
				if (stage == 3 || stage == 4 || stage == 7 || stage == 9) {

					if (GetRand(40) == 0) {

						ThingPointa enemy4(new Enemy4);
						ADD_list(enemy4);

						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				// ENEMY5�i�ʏ�U���j
				if (stage == 5 || stage == 7 || stage == 9) {

					if (GetRand(120) == 0) {

						ThingPointa enemy5(new Enemy5);
						ADD_list(enemy5);

						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				// ENEMY6�i�x�N�g���U���j
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

			// �X�R�A 10000�ȏ� ������ �{�X�t���O false �̏ꍇ�@�{�X����
			if (20000 <= score && !boss_flag) {

				boss_flag = true; // �{�X�t���O�� true ��

				if (boss_flag) {

					StopSoundMem(Play_m); // �v���C���̉����~
					PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP); // �{�X���̉����Đ�

					// STAGE1�`9 �̏ꍇ
					if (stage <= 9) {

						ThingPointa enemy_boss1(new Enemy_Boss1);
						ADD_list(enemy_boss1);
					}

					// STAGE10 �� �ꍇ
					if (stage == 10) {

						ThingPointa enemy_boss2(new Enemy_Boss2);
						ADD_list(enemy_boss2);
					}
				}
			}

			// ��ɐ�������
			// �񕜐���
			if (GetRand(350) == 0) {

				ThingPointa heal(new Heal1);
				ADD_list(heal);
			}

			if (GetRand(600) == 0) {

				ThingPointa heal2(new Heal2);
				ADD_list(heal2);
			}
		}

		// �|�[�Y�i�x�~�j��ʂ�
		if (PUSH_back()) {

			if (!pause_flag) PlaySoundMem(Pause_m, DX_PLAYTYPE_BACK); // �|�[�Y���̍Đ�

			pause_flag = true;
			StopSoundMem(Play_m); // �v���C���̉����~
			StopSoundMem(Boss_m); // �{�X���̉����~
		}

		// �|�[�Y�i�x�~�j��ʂ̕`��
		if (pause_flag) {

			DrawBox(150, 150, WIDTH - 150, HEIGHT - 150, GetColor(255, 255, 255), TRUE);
			DrawExtendGraph(170, 170, WIDTH - 170, 240, Pause_p, TRUE);
			DrawExtendGraph(160, 330, WIDTH - 160, 420, Esc_p, TRUE);

			// �|�[�Y�̏I���E�ĊJ
			if (PUSH_space()) {

				pause_flag = false;

				// �{�X���o��̏ꍇ �v���C���̉����Đ�
				if (!boss_flag) PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP);

				// �{�X�̏ꍇ �{�X���̉����Đ�
				if (boss_flag) PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP);
			}
		}

		// �v���C���Ă���ԁ@��ʍ��[�ɕ�����`��
		else DrawFormatString(20, HEIGHT - 30, GetColor(255, 255, 255), "BACK SPACE:PAUSE");
	}

	// game_flag false �̏ꍇ ������`��
	else {

		// B ���������ꍇ PUSH SPACE ��`��
		if (CheckHitKey(KEY_INPUT_B)) space_flag = true;
		if (space_flag) DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

		// ���� �����̕`��
		DrawFormatString(620, 180, GetColor(255, 255, 255), "�� OPERATING METHOD ��");
		DrawFormatString(620, 210, GetColor(0, 255, 255), "B:SHOT");
		DrawFormatString(620, 240, GetColor(255, 255, 255), "ELSE:SPECIAL SHOT");
		DrawFormatString(620, 270, GetColor(0, 255, 255), "SCORE:20000");

		DrawFormatString(620, 350, GetColor(255, 255, 255), "�� HINT ��");
		DrawFormatString(620, 380, GetColor(0, 255, 255), "IF YOU GET THE BLUE HEART");
		DrawFormatString(620, 410, GetColor(0, 255, 255), "YOU CAN USE SPECIAL SHOT...");

		// SPACE KEY ���������ꍇ �v���C����
		if (PUSH_space()) {

			StopSoundMem(Title_m); // �^�C�g�����̉����~
			PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP); // �v���C���̉����Đ�
			game_flag = true; // game_flag �� true��
			start_time = GetNowCount(); // ��������
		}
	}

	// �{�X���o��̏ꍇ�@�X�R�A������
	if (!boss_flag) {

		SetFontSize(20);
		DrawFormatString(WIDTH - 220, 10, GetColor(255, 255, 255), "SCORE:%d", score);
	}

	// ESC ���������ꍇ�@�^�C�g����ʂ֖߂�
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {

		scene = 0;
		StopSoundMem(Title_m); // �^�C�g�����̉����~
		StopSoundMem(Play_m); // �v���C���̉����~
		StopSoundMem(Boss_m); // �{�X���̉����~
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // �^�C�g�����̉����Đ�
	}

	// �X�R�A�̏���i20000�ɐݒ�j
	if (20000 <= score) score = 20000;

	// �������� 0�ɂȂ����ꍇ
	if (now_time < 0) {

		scene = 3; // �I�[�o�[��ʂ�
		StopSoundMem(Play_m); // �v���C���̉����~
		StopSoundMem(Boss_m); // �{�X���̉����~
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // �I�[�o�[��
	}

	// Thing ���X�g���ŏ����F�폜�t���O true �̃N���X��������iremove_if �֐��j
	// �폜�t���O true �̃N���X��O�ɂ���
	// ������ ���̃N���X�� list.erase �ɂ�� Thing ���X�g�ō폜�E���X�g�����l�߂�
	auto end = remove_if(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {return Thing->GET_remove();});
	thing_list.erase(end, thing_list.end());
}

// scene == 3 �̎��@�I�[�o�[���
void Game::GAME_OVER() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Over_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

	now_score = score; // �X�R�A�ɒu��

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "YOUR SCORE:%d", now_score);

	// �n�C�X�R�A���X�R�A���傫���ꍇ
	if (high_score < now_score) {

		// �l���㏑���E�L�^����
		high_score = now_score;
		SAVE_highscore();
	}

	// SPACE KEY ���������ꍇ �^�C�g����ʂ�
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Over_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

// scene == 4 �̎��@�N���A���
void Game::GAME_CLEAR() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Clear_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE �̕`��

	// �X�R�A�̌v�Z
	// �X�R�A�@���@���ԃX�R�A�@�{�@�X�R�A�iMax 20000�j�@�{�@STAGE �~ 10000
	now_score = now_time * 100 + score + stage * 10000;

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "YOUR SCORE:%d", now_score);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "TIME POINT:%d + SCORE:%d + STAGE POINT:%d", now_time * 100, score, stage * 10000);

	// �n�C�X�R�A���X�R�A���傫���ꍇ
	if (high_score < now_score) {

		// �l���㏑���E�L�^����
		high_score = now_score;
		SAVE_highscore();
	}

	// SPACE KEY ���������ꍇ �^�C�g����ʂ�
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Clear_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

void Game::GAME_END() {

	DxLib_End(); // DX���C�u�����̏I��
}

// WinMain �֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game; // GAME �N���X�� game �ɒu��
	game.GAME_SET();
	game.GAME_ALL();
	game.GAME_END();
	return 0;
}