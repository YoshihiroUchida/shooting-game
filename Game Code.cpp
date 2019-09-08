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

//-------------------------------------------------------------------------------------

// ���y
enum Sound {

	SOUND_SHOT1, // SHOT1 ��
	SOUND_SHOT2, // SHOT2 ��
	SOUND_CHARGE, // CHARGE ���̉�
	SOUND_CHARGE_SHOT, // CHARGE SHOT�̉�
	SOUND_ENEMY_SHOT, // ENEMY SHOT�̉�
	SOUND_BEAM, // BEAM ��
	SOUND_E_ATTACK, // ENEMY �̃A�^�b�N��
	SOUND_P_ATTACK, // PLAYER �̃A�^�b�N��
	SOUND_HEAL, // �񕜉�
	SOUND_BREAK, // �j��
	SOUND_NUM, // �񋓑΂̐�
};

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
class Player : public Thing {

private:

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
class Shot : public Thing {

protected:

	float angle; // �~�̊p�x
	float center_x; // ���S x ���W
	float center_y; // ���S y ���W
	float shot_s; // �e�̑��x

public:

	Shot(); // �R���X�g���N�^�i�ݒ�j
	ThingType GET_TYPE(); // ������ SHOT1 �^�C�v�ŕԂ�
	ThingType HIT_TYPE(); // ������G�� ENEMY1 �^�C�v�ŕԂ�
	void move(); // �E�����ց@��ʒ[�ō폜
	void draw(); // �`��
	void hit(int damage, int energy); // �����@�폜
};

//-------------------------------------------------------------------------------------

// Through Shot �N���X�i�ђʒe�j
class Through_Shot : public Shot {

public:

	Through_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Beam �N���X�i�����j
class Beam : public Shot {

public:

	Beam();
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Vortex Shot �N���X�i�Q�e�j
class Vortex_Shot : public Through_Shot {

private:

	float rad; // ���a

public:

	Vortex_Shot();
	void SET_position(int, int); // ���W��ݒ�
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Spray Shot �N���X�i�U�z�e�j
class Spray_Shot : public Through_Shot {

public:

	Spray_Shot();
	void SET_angle(float a); // �p�x��ݒ�
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Rasen Shot �N���X�i�����e�j
class Rasen_Shot : public Shot {

private:

	int sign; // 1 or -1�i�����i�[�j

public:

	Rasen_Shot();
	void SET_position(int, int);
	void SET_sign(int s); // ������ݒ�
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Charge Shot �N���X�i�g��e�j
class Charge_Shot : public Shot {

private:

	bool charge_flag; // charge �t���O

public:

	Charge_Shot();
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Period Shot1 �N���X�i�����e�j
class Period_Shot1 : public Thing {

private:

	int shot_time; // ���˂܂ł̎���
	int shot_count; // ���˂��鐔

public:

	Period_Shot1();
	// �����蔻��~�@�^�C�v�� NONE �ŕԂ�
	ThingType GET_TYPE();
	ThingType HIT_TYPE();
	void move();
	void draw();
	void hit(int damage, int energy) {};
};

//-------------------------------------------------------------------------------------

// Period Shot2 �N���X�i��E���j
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

//-------------------------------------------------------------------------------------

// Period Shot3 �N���X�i���E�E�j
class Period_Shot3 : public Period_Shot2 {

public:

	Period_Shot3();
	void SET_sign(int s);
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Homing Shot �N���X�i�ǔ��e�j
class Homing_Shot : public Shot {

public:

	Homing_Shot();
	void move(); // �G��ǔ�
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Parabola Shot �N���X�i�������e�j
class Parabola_Shot : public Shot {

	// �������Ɋւ���ϐ�
	float a;
	float b;
	float c;

public:

	Parabola_Shot();
	void SET_position(int, int); // ���W��ݒ�
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Enemy1 �N���X�i�ʏ�j
class Enemy1 : public Thing {

protected:

	int count; // ���j���č폜����܂ł̐��l��
	int up_down; // �㉺����
	bool count_flag; // ���j�t���O

public:

	Enemy1();
	ThingType GET_TYPE(); // ������ ENEMY1 �^�C�v�ŕԂ�
	ThingType HIT_TYPE(); // ������G�� PLAYER �^�C�v�ŕԂ�
	void move();
	void draw();
	void hit(int damage, int energy); // ENEMY1�`6�܂ŋ��ʐݒ�
};

//-------------------------------------------------------------------------------------

// Enemy2 �N���X�i�^�t�j
class Enemy2 : public Enemy1 {

public:

	Enemy2();
	void move();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy3 �N���X�i�x�N�g���j
class Enemy3 : public Enemy1 {

public:

	Enemy3();
	void move();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy4 �N���X�i�����j
class Enemy4 : public Enemy1 {

public:

	Enemy4();
	void move();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy5 �N���X�i�ʏ�U���j
class Enemy5 : public Enemy1 {

public:

	Enemy5();
	void move();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy6 �N���X�i�x�N�g���U���j
class Enemy6 : public Enemy1 {

public:

	Enemy6();
	void move();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy Boss1 �N���X�iSTAGE�P�`�X�܂ŋ��ʁj
class Enemy_Boss1 : public Enemy1 {

protected:

	int add_speed; // ���x���グ��
	int Warn_p; // WARNING!!

public:

	Enemy_Boss1();
	void move();
	void life_draw(); // �̗͂�`��
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Enemy Boss2 �N���X�iSTAGE�P�O�j
class Enemy_Boss2 : public Enemy_Boss1 {

public:

	Enemy_Boss2();
	void move();
	void life_draw();
	void draw();
};

//-------------------------------------------------------------------------------------

// Enemy Shot1 �N���X�i�{�X�p�j
class Enemy_Shot1 : public Thing {

public:

	Enemy_Shot1();
	ThingType GET_TYPE(); // ������ ENEMY_SHOT1 �^�C�v�ŕԂ�
	ThingType HIT_TYPE(); // ������G�� PLAYER �^�C�v�ŕԂ�
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Enemy Shot2 �N���X�iENEMY5�E6�p�j
class Enemy_Shot2 : public Enemy_Shot1 {

public:

	Enemy_Shot2();
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Heal1 �N���X�i�̗͉񕜁j
class Heal1 : public Thing {

public:

	Heal1();
	ThingType GET_TYPE(); // ������ HEAL1 �^�C�v�ŕԂ�
	ThingType HIT_TYPE(); // ��������̂� PLAYER �^�C�v�ŕԂ�
	void move();
	void draw();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Heal2 �N���X�i����ʉ񕜁j
class Heal2 : public Heal1 {

public:

	Heal2();
	void draw();
	void move();
	void hit(int damage, int energy);
};

//-------------------------------------------------------------------------------------

// Game �N���X
class Game {

	std::list <ThingPointa> thing_list; // Thing �N���X�@�X�}�[�g�|�C���^�����X�g�ilist�j�^�f�[�^�\���ithing_list�j��

private:

	// �o�b�N�p�ϐ�
	int p_x; // x ���W�i���[�v�d�l�j
	int p_w; // ����
	int add_s; // ���x

	// �摜�Ǎ��p�ϐ�
	int Game_p; // �o�b�N
	int Title_p; // SHOOTING GAME
	int Select_p; // STAGE SELECT
	int Number_p; // 1 2 3 4 5 6 7 8 9 10
	int Push_p; // PUSH SPACE
	int Over_p; // GAME OVER
	int Clear_p; // GAME CLEAR
	int Pause_p; // PAUSE
	int Esc_p; // ESC : TITLE�ESPACE : REPLAY

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

public:

	// ��ʗp�ϐ�
	static const int WIDTH = 1200; // ����
	static const int HEIGHT = 600; // �c��

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

// Thing �N���X�̎���
void Thing::remove() {

	remove_flag = true; // �폜�t���O�� true ��
}

Thing::Thing() {

	remove_flag = false; // �폜�t���O�� false ��
	pause_flag = false; // �|�[�Y�i�x�~�j�t���O�� false ��
}

void Thing::SET_picture(const char* file_name, ThingType thing) {

	// loaded_picture �͂O�̏ꍇ�@LoadGraph ������
	if (loaded_picture[thing] == 0) {

		loaded_picture[thing] = LoadGraph(file_name);
	}

	hit_w = m_w; // ������ hit_w ��
	hit_h = m_h; // �c���� hit_ h ��
	hit_x = hit_y = 0; // ������W���O��
}

void Thing::SET_sound(const char* file_name, Sound sound) {

	// loaded_sound �͂O�̏ꍇ�@LoadSoundMem ������
	if (loaded_sound[sound] == 0) {

		loaded_sound[sound] = LoadSoundMem(file_name);
	}
}

void Thing::SET_position(int position_x, int position_y) {

	m_x = position_x; // �ݒ�l�� m_x�ix ���W�j ��
	m_y = position_y; // �ݒ�l�� m_y�iy ���W�j��
}

void Thing::SET_hitarea(int h_x, int h_y, int h_w, int h_h) {

	hit_x = h_x; // ���ΓI x ���W��ݒ�
	hit_y = h_y; // ���ΓI y ���W��ݒ�
	hit_w = h_w; // ������ݒ�
	hit_h = h_h; // �c����ݒ�
}

bool Thing::GET_remove() {

	return remove_flag;
}

ThingType Thing::HIT_TYPE() {

	return TYPE_NONE;
}

void Thing::draw() {

	// ����(m_x, m_y)					�E��(m_x + m_w, m_y)
	// ����(m_x, m_y + m_h)		�E��(m_x + m_w, m_y + m_h)
	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[GET_TYPE()], TRUE); // TRUE �͉摜�̖��F���N���A��
}

void Thing::life_draw() {

	if (0 < life_now) {

		DrawExtendGraph(m_x, m_y - 15, m_x + 65, m_y - 10, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(m_x, m_y - 15, m_x + (65 * life_now) / life_max, m_y - 10, loaded_picture[TYPE_LIFE], TRUE); // �̗͂̒l�ō��ւ����
	}
}

int Thing::GET_damage() {

	return damage;
}

int Thing::GET_energy() {

	return energy;
}

bool Thing::HIT_test(ThingPointa& other) {

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
	if (x_2 < x_1 + w_1 &&
		x_1 < x_2 + w_2 &&
		y_2 < y_1 + h_1 &&
		y_1 < y_2 + h_2) return true;

	return false; // ��L�ȊO�� false ��
}

//-------------------------------------------------------------------------------------

// Player �N���X�̎���
Player::Player() {

	m_w = 80; // ����
	m_h = 50; // �c��
	m_s = 8; // ���x

	// �摜��ݒ�
	SET_picture("PLAYER.png", TYPE_PLAYER);
	SET_picture("HEART.png", TYPE_HEART);
	SET_picture("ENERGY.png", TYPE_ENERGY);

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
}

ThingType Player::HIT_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Player::GET_TYPE() {

	return TYPE_PLAYER;
}

void Player::move() {

	// �_�ŃG�t�F�N�g�@�}�C�i�X����
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

			// ��ʂ̓����蔻��
			if (m_x < 0) m_x = 0; // ��ʍ�
			if (Game::WIDTH < m_x + m_w) m_x = Game::WIDTH - m_w; // ��ʉE
			if (m_y < 0) m_y = 0; // ��ʏ�
			if (Game::HEIGHT < m_y + m_h) m_y = Game::HEIGHT - m_h; // ��ʉ�
		}

		// �ʏ�e�i�a�j
		if (CheckHitKey(KEY_INPUT_B) && shot_count % 8 == 0) {

			if (!shot_flag) { // shot �t���O false �̏ꍇ

				ThingPointa shot(new Shot); // Shot �N���X�쐬�@���̃A�h���X�� Thing �N���X�̃X�}�[�g�|�C���^�ɓn��
				shot->SET_position(m_x + m_w - 10, m_y + 25); // Shot �̍��W��ݒ�
				game->ADD_list(shot); // Thing ���X�g�� Shot �A�h���X��ǉ�
				PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK); // Shot ��
			}
		}

		// �ђʒe�i�s�j
		else if (CheckHitKey(KEY_INPUT_T) && shot_count % 10 == 0) {

			// ����ʂS�ȏ�̏ꍇ�@���ˉ�
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

			// ����ʂT�ȏ�̏ꍇ�@���ˉ�
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

		// �Q�e�i�u�j
		else if (CheckHitKey(KEY_INPUT_V) && shot_count % 6 == 0) {

			// ����ʂR�ȏ�̏ꍇ�@���ˉ�
			if (3 <= energy_now) {

				if (!shot_flag) {

					ThingPointa vortex_shot(new Vortex_Shot);
					vortex_shot->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(vortex_shot);
					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);
				}
			}
		}

		// �U�z�e�i�r�j
		else if (CheckHitKey(KEY_INPUT_S) && shot_count % 10 == 0) {

			// ����ʂX�ȏ�̏ꍇ�@���ˉ�
			if (9 <= energy_now) {

				if (!shot_flag) {

					for (int i = 0; i < 7; i++) { // �V��

						ThingPointa spray_shot1(new Spray_Shot);
						spray_shot1->SET_position(m_x + m_w - 10, m_y + 25);
						spray_shot1->SET_angle(3.14 * (3 - i) / 18); // �U�z����p�x�i�R�O���E�Q�O���E�P�O���E�O���j���㉺�ɐݒ�
						game->ADD_list(spray_shot1);
					}

					PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK); // Shot ��
				}
			}
		}

		// �����e�i�q�j
		else if (CheckHitKey(KEY_INPUT_R) && shot_count % 4 == 0) {

			// ����ʂP�O�̏ꍇ�@���ˉ�
			if (10 <= energy_now) {

				if (!shot_flag) {

					// ��
					ThingPointa rasen_Shot_1(new Rasen_Shot);
					rasen_Shot_1->SET_position(m_x + m_w - 10, m_y + 25);
					rasen_Shot_1->SET_sign(1); // �v���X��
					game->ADD_list(rasen_Shot_1);

					// ��
					ThingPointa rasen_Shot_2(new Rasen_Shot);
					rasen_Shot_2->SET_position(m_x + m_w - 10, m_y + 25);
					rasen_Shot_2->SET_sign(-1); // �}�C�i�X��
					game->ADD_list(rasen_Shot_2);
					PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
				}
			}
		}

		// �g��e�i�n�j
		else if (CheckHitKey(KEY_INPUT_O)) {

			// ����ʂQ�ȏ�̏ꍇ�@���ˉ�
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

			// ����ʂW�ȏ�̏ꍇ�@���ˉ�
			if (8 <= energy_now) {

				if (!shot_flag) {

					ThingPointa period_shot1(new Period_Shot1);
					period_shot1->SET_position(m_x + m_w - 10, m_y + 25);
					game->ADD_list(period_shot1);
					shot_flag = true; // �A�Ŏd�l
					PlaySoundMem(loaded_sound[SOUND_SHOT1], DX_PLAYTYPE_BACK);
				}
			}
		}

		// �ǔ��e�i�g�j
		else if (CheckHitKey(KEY_INPUT_H) && shot_count % 28 == 0) {

			// ����ʂV�ȏ�̏ꍇ�@���ˉ�
			if (7 <= energy_now) {

				// �c��G���̏ꍇ
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

		// �������e�i�o�j
		else if (CheckHitKey(KEY_INPUT_P) && shot_count % 28 == 0) {

			// ����ʂU�ȏ�̏ꍇ�@���ˉ�
			if (6 <= energy_now) {

				// �c��G���̏ꍇ
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

		// �S�Ă̒e���g�p��
		else if (CheckHitKey(KEY_INPUT_Q)) energy_now = 10;

		else {

			shot_flag = false; // shot �t���O�� false��
			beam_flag = false; // beam �t���O �� false ��
			charge_time = 0; // charge_time ���O��
		}
	}

	// ���C�t�O�̏ꍇ
	if (life_now <= 0) {

		scene = 3; // �I�[�o�[��ʂ�
		StopSoundMem(Play_m); // �v���C��ʂ̉����~
		StopSoundMem(Boss_m); // �{�X��ʂ̉����~
		PlaySoundMem(Over_m, DX_PLAYTYPE_LOOP); // �I�[�o�[��ʂ̉����Đ�
	}

	// ���C�t�̏���ݒ�
	if (10 <= life_now) life_now = 10;

	// ����ʂ̏���ݒ�
	if (10 <= energy_now) energy_now = 10;
}

void Player::heart_draw() {

	if (0 < life_now) {

		// �̗͂̒l�Ńn�[�g�̐��𒲐�
		for (int i = 0; i < life_now; i++) {

			DrawExtendGraph(5 + i * 45, 5, 55 + i * 45, 45, loaded_picture[TYPE_HEART], TRUE);
		}
	}
}

void Player::energy_draw() {

	if (0 < energy_now) {

		// ����ʂ̒l�Ńn�[�g�̐��𒲐�
		for (int i = 0; i < energy_now; i++) {

			DrawExtendGraph(460 + i * 45, 5, 510 + i * 45, 45, loaded_picture[TYPE_ENERGY], TRUE);
		}
	}

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
}

void Player::draw() {

	heart_draw(); // �̗͂�`��
	energy_draw(); // ����ʂ�`��

	if (dead_time % 5 == 0) Thing::draw(); // �T�Ŋ���؂��ꍇ�@�_�łŕ`��
}

void Player::hit(int damage, int energy) {

	// �G�̏ꍇ
	if (dead_time <= 0 && 0 < damage) {

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
}

ThingType Shot::GET_TYPE() {

	return TYPE_SHOT1;
}

ThingType Shot::HIT_TYPE() {

	return TYPE_ENEMY1;
}

void Shot::move() {

	if (!pause_flag) m_x += m_s; // ���x���P�O��

	if (Game::WIDTH < m_x) remove(); // ��ʍ��ō폜
}

void Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT1], TRUE);
}

void Shot::hit(int damage, int energy) {

	remove();
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Through Shot �N���X�i�ђʒe�j�̎���
Through_Shot::Through_Shot() {

	m_w = 34;
	m_h = 15;
	m_s = 20;
	damage = 1;
	SET_picture("SHOT2.png", TYPE_SHOT2);
	SET_sound("SHOT2.mp3", SOUND_SHOT2);
}

void Through_Shot::move() {

	if (!pause_flag) m_x += m_s; // ���x���Q�O��

	if (Game::WIDTH < m_x + m_w) remove();
}

void Through_Shot::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT2], TRUE);
}

void Through_Shot::hit(int damage, int energy) {

	// �ђʂ���� remove �֐��͎����~
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Beam �N���X�i�����j�̎���
Beam::Beam() {

	m_w = 0; // �L������ׂO��
	m_h = 80;
	m_s = 15;
	damage = 1;
	SET_picture("BEAM.png", TYPE_BEAM);
	SET_sound("BEAM.mp3", SOUND_BEAM);
}

void Beam::move() {

	if (!pause_flag) {

		m_w += m_s;
		hit_w = m_w; // �����𓖂��蔻���
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

// Vortex Shot �N���X�i�Q�e�j�̎���
Vortex_Shot::Vortex_Shot() {

	m_w = 34;
	m_h = 15;
	damage = 10;
	angle = 0; // �p�x���O��
	rad = 0; // ���a���O��
}

void Vortex_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;
}

void Vortex_Shot::move() {

	if (!pause_flag) {

		rad += 0.8; // �~�̔��a�Ƀv���X����
		angle += 8 / rad; // �p�x���v���X����i�p���x�𒲐��j

		// ���v�Z
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

// Spray Shot �N���X�i�U�z�e�j�̎���
Spray_Shot::Spray_Shot() {

	m_w = 34;
	m_h = 15;
	m_s = 10;
	damage = 5;
	angle = 0;
}

void Spray_Shot::SET_angle(float a) {

	angle = a; // �������p�x��
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

// Rasen Shot1�E2 �N���X�i�����e�j�̎���
Rasen_Shot::Rasen_Shot() {

	m_w = 12;
	m_h = 12;
	m_s = 8;
	damage = 1;
	angle = 0; // �p�x���O��
	sign = 0;
}

void Rasen_Shot::SET_position(int position_x, int position_y) {

	m_x = position_x;
	center_y = position_y;
}

void Rasen_Shot::SET_sign(int s) {

	sign = s; // �����𕄍���
}

void Rasen_Shot::move() {

	if (!pause_flag) {

		angle += 0.2;
		m_x += m_s;
		m_y = center_y - sign * 60 * sin(angle); // �T�C���J�[�u�̉��p
	}

	if (Game::WIDTH < m_x) remove();
}

void Rasen_Shot::draw() {

	// ���̓I�ɕ`��
	DrawExtendGraph(m_x, m_y, m_x + m_w * (1.2 - sign * cos(angle)) / 2, m_y + m_h * (1.2 - sign * cos(angle)) / 2, loaded_picture[TYPE_SHOT1], TRUE);
}

void Rasen_Shot::hit(int damage, int energy) {

	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Charge Shot �N���X�i�g��e�j�̎���
Charge_Shot::Charge_Shot() {

	m_w = 0;
	m_h = 0;
	m_s = 15;
	damage = 0;
	SET_picture("CHARGE SHOT.png", TYPE_CHARGE_SHOT);
	SET_sound("CHARGE.mp3", SOUND_CHARGE); // CHARGE ���̉�
	SET_sound("CHARGE SHOT.mp3", SOUND_CHARGE_SHOT); // ���ˉ�
	charge_flag = false; // charge �t���O�� false ��
}

void Charge_Shot::move() {

	if (!charge_flag) {

		// �u�n�v�������ꍇ
		if (CheckHitKey(KEY_INPUT_O)) {

			// �З͐������T�O�Ɂi���Q�ʂ͂O�ɂ��Ă���ׁj
			if (damage < 50) {

				damage++;

				m_x += 1;
				m_y -= 2;
				m_w = 2 * damage; // ���Q�ʂɔ����g��
				m_h = 4 * damage;

				// �����蔻��̌덷����
				hit_w = m_w + 20;
				hit_h = m_h;
			}

			// ���Q�ʂT�O�����̏ꍇ
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

	else if (!pause_flag) m_x += m_s; // ���x���P�T��

	if (Game::WIDTH < m_x) remove();
}

void Charge_Shot::draw() {

	// angle �̒l���Q�Ŋ���؂��ꍇ�@�`��
	if ((int)angle % 2 == 0) {

		DrawRotaGraph((2 * m_x + m_w) / 2, (2 * m_y + m_h) / 2, (double)m_w / 50, angle, loaded_picture[TYPE_CHARGE_SHOT], TRUE);
	}

	if (!pause_flag) angle += 30; // angle �̒l�ɂR�T�v���X����
}

void Charge_Shot::hit(int damage, int energy) {

	remove();
	StopSoundMem(loaded_sound[SOUND_CHARGE]);
	PlaySoundMem(loaded_sound[SOUND_P_ATTACK], DX_PLAYTYPE_BACK);
}

//-------------------------------------------------------------------------------------

// Period Shot1 �N���X�i�����e�j�̎���
Period_Shot1::Period_Shot1() {

	m_w = 15;
	m_h = 15;
	m_s = 12;
	damage = 0;
	shot_time = 30; // ���˂܂ł̎��Ԃ��R�O��
	shot_count = 1; // �T�񔭎˂���ׂP��
	SET_picture("SHOT3.png", TYPE_SHOT3);
	SET_sound("P ATTACK.mp3", SOUND_P_ATTACK);
}

ThingType Period_Shot1::GET_TYPE() {

	return TYPE_SHOT3;
}

ThingType Period_Shot1::HIT_TYPE() {

	return TYPE_NONE; // �{�̂ɓ����蔻��~
}

void Period_Shot1::move() {

	if (!pause_flag) {

		if (0 <= shot_time) m_x += m_s; // ���˂܂ŉE������

		if (shot_time < 0) {

			// �T�񔭎�
			if (shot_time % 10 == 0 && shot_count <= 5) {

				// �����蔻����e�𔭎�
				// ������
				ThingPointa period_shot2(new Period_Shot2());
				game->ADD_list(period_shot2);
				period_shot2->SET_sign(1);
				period_shot2->SET_position(m_x + 1, m_y - 10);

				// �E����
				ThingPointa period_shot3(new Period_Shot3());
				game->ADD_list(period_shot3);
				period_shot3->SET_sign(1);
				period_shot3->SET_position(m_x - 5, m_y + 2);

				// �����
				ThingPointa period_shot4(new Period_Shot2());
				game->ADD_list(period_shot4);
				period_shot4->SET_sign(-1);
				period_shot4->SET_position(m_x + 1, m_y - 10);

				// ������
				ThingPointa period_shot5(new Period_Shot3());
				game->ADD_list(period_shot5);
				period_shot5->SET_position(m_x - 12, m_y + 2);
				period_shot5->SET_sign(-1);
				PlaySoundMem(loaded_sound[SOUND_SHOT2], DX_PLAYTYPE_BACK);

				shot_count++;
			}

			if (5 < shot_count) remove(); // �T���ō폜
		}

		shot_time--;
	}
}

void Period_Shot1::draw() {

	DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_SHOT3], TRUE);
}

//-------------------------------------------------------------------------------------

// Period Shot2�i�㉺�j�N���X�̎���
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

// Period Shot3�i���E�j�N���X�̎���
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

// Homing Shot �N���X�i�ǔ��e�j�̎���
Homing_Shot::Homing_Shot() {

	m_w = 12;
	m_h = 12;
	m_s = 10;
	damage = 20;
	shot_s = 10; // shot_s ���P�O��
}

void Homing_Shot::move() {

	if (!pause_flag) {

		// �c��G���̏ꍇ
		if (0 < enemy_num) {

			// �ǔ��̌v�Z
			// sqrt() �͐�Βl
			// pow() �ׂ͂���
			// ���̑��x�Œǔ�
			m_x += ((enemy_x - m_x) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
			m_y += ((enemy_y - m_y) / sqrt(pow(enemy_x - m_x, 2) + pow(enemy_y - m_y, 2))) * shot_s;
		}

		else m_x += m_s; // �c��G�~�̏ꍇ�@�E������
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

// Parabola Shot �N���X�i�������e�j�̎���
Parabola_Shot::Parabola_Shot() {

	m_w = 12;
	m_h = 12;
	damage = 50;
	m_s = 0; // shot_s ���O��
}

void Parabola_Shot::SET_position(int position_x, int position_y) {

	center_x = position_x;
	center_y = position_y;

	// �s��v�Z�ŎO�_�̍��W���v�Z
	float frame = (enemy_x - center_x) / (8 + enemy_s);

	// �e�E�G������R�_�̍��W
	float x_1 = center_x;
	float x_2 = enemy_x - enemy_s * frame;
	float x_3 = center_x + 1;

	float y_1 = center_y;
	float y_2 = enemy_y;
	float y_3 = center_y - tan(3.14 / 3); // �p�x�U�O����

	float det_A = -(x_1 - x_2) * (x_2 - x_3) * (x_3 - x_1);
	float det_a = y_1 * x_2 + y_2 * x_3 + y_3 * x_1 - x_2 * y_3 - x_3 * y_1 - x_1 * y_2;
	float det_b = pow(x_1, 2) * y_2 + pow(x_2, 2) * y_3 + pow(x_3, 2) * y_1 - y_1 * pow(x_2, 2) - y_2 * pow(x_3, 2) - y_3 * pow(x_1, 2);
	float det_c = pow(x_1, 2) * x_2 * y_3 + pow(x_2, 2) * x_3 * y_1 + pow(x_3, 2) * x_1 * y_2 - y_1 * x_2 * pow(x_3, 2) - y_2 * x_3 * pow(x_1, 2) - y_3 * x_1 * pow(x_2, 2);

	// �N�������ɂ��v�Z
	a = det_a / det_A;
	b = det_b / det_A;
	c = det_c / det_A;
}

void Parabola_Shot::move() {

	if (!pause_flag) {

		m_s += 8;
		m_x = center_x + m_s;
		m_y = a * pow(m_x, 2) + b * m_x + c; // �������ŕ`��
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

// ENEMY1�`6�N���X�̎���
Enemy1::Enemy1() {

	m_w = 80;
	m_h = 50;

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
}

ThingType Enemy1::GET_TYPE() {

	return TYPE_ENEMY1;
}

ThingType Enemy1::HIT_TYPE() {

	return TYPE_PLAYER;
}

void Enemy1::move() {

	if (!pause_flag) m_x -= m_s; // ���x�W or �P�O

	// ���j�� count �͂P�R�̒l�𓾂�
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

	// Homing�EParabola Shot�N���X�i�ǔ��e�E�������e�j����������ׁ@�l���O���[�o���ϐ���
	enemy_x = m_x;
	enemy_y = m_y;
	enemy_s = m_s;
}

void Enemy1::draw() {

	life_draw(); // �̗͂�`��

	if (!count_flag) {

		DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY1], TRUE);
	}

	// ���j�� count �ɂ͂P�R�Ecount_flag �� move() �� true ��
	if (count_flag && 0 <= count) {

		// ���j�G�t�F�N�g��`��
		DrawExtendGraph(m_x - 5 * count, m_y - 5 * count, m_x + (m_w - 30) + 5 * count, m_y + m_h + 5 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		// count <= 0 �̏ꍇ�@�폜
		if (count <= 0 && !count_flag) {

			remove();
			game->ADD_score(200); // �X�R�A��ǉ�

			if (0 < enemy_num) enemy_num -= 1; // enemy_num ���}�C�i�X����
		}
	}
}

void Enemy1::hit(int damage, int energy) {

	life_now -= damage; // �̗͂��}�C�i�X����

	// �̗͂O�̏ꍇ�@���j�G�t�F�N�g������
	if (life_now <= 0 && count == 0) {

		count = 13; // count ���P�R��
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
	up_down = 6; // �㉺�����̑��x���U��
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

	// ��ʂ̓����蔻��
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
	up_down = 6; // �㉺�����̑��x���U��
	count = 0;
	count_flag = false;
	SET_picture("ENEMY5.png", TYPE_ENEMY5);
	SET_position(Game::WIDTH, GetRand(Game::HEIGHT - m_h));
}

void Enemy5::move() {

	if (!pause_flag) {

		// ���̍��W�܂ō�������
		if (1000 < m_x) m_x -= m_s;

		// ���̍��W�ŏ㉺������
		if (m_x <= 1000) {

			m_y -= up_down;

			// ��ʂ̓����蔻��
			if (m_y < 0) up_down = -up_down; // ��
			if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // ��

			if (GetRand(60) == 0) {

				ThingPointa enemy_shot2(new Enemy_Shot2); // Enemy Shot2 �N���X�쐬�@���̃A�h���X�� Thing �N���X�̃X�}�[�g�|�C���^�ɓn��
				enemy_shot2->SET_position(m_x - 10, m_y + 25); // ���W
				game->ADD_list(enemy_shot2); // Thing ���X�g�� Enemy Shot2 �A�h���X��ǉ�
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

		// ��ʂ̓����蔻��
		if (m_y < 0) up_down = -up_down; // ��
		if (Game::HEIGHT < m_y + m_h) up_down = -up_down; // ��
		if (m_x < 0) m_s = -2; // ��
		if (Game::WIDTH + 200 < m_x + m_w) remove(); // ��ʉE�ō폜

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

// ENEMY BOSS1�E2�N���X�̎���
Enemy_Boss1::Enemy_Boss1() {

	// Enemy Boss1 ���C�t�ݒ�
	if (stage == 1 || stage == 4 || stage == 7) life_max = 3000; // STAGE�P�E�S�E�V
	if (stage == 2 || stage == 5 || stage == 8) life_max = 3500; // STAGE�Q�E�T�E�W
	if (stage == 3 || stage == 6 || stage == 9) life_max = 4000; // STAGE�R�E�U�E�X

	m_w = 350;
	m_h = 390;
	life_now = life_max;
	damage = 1;
	energy = 0;
	up_down = 3; // �㉺�������x���R��
	add_speed = 0; // �̗͔����ɂȂ�܂ŉ����͂O��
	count = 0;
	count_flag = false;

	// STAGE�̒l�ŉ摜��ݒ�
	if (stage <= 3) SET_picture("ENEMY BOSS1.png", TYPE_ENEMY_BOSS1);
	if (4 <= stage && stage <= 6) SET_picture("ENEMY BOSS2.png", TYPE_ENEMY_BOSS2);
	if (7 <= stage && stage <= 9) SET_picture("ENEMY BOSS3.png", TYPE_ENEMY_BOSS3);

	SET_hitarea(150, 50, 340, 340); // �����蔻��̐ݒ�
	Warn_p = LoadGraph("WARNING.png"); // WARNING!!
	SET_position(Game::WIDTH, 140);
}

void Enemy_Boss1::move() {

	// �̗͔����ȉ��̏ꍇ�@���x���㏸
	if (life_now < life_max / 2) add_speed = 3;

	if (!pause_flag) {

		// ���̍��W�܂ō�����
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

		// ���̍��W�̏ꍇ�@�㉺����
		if (m_x <= 790) {

			m_y += up_down;

			// ��ʂ̓����蔻��
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

	int life_x = Game::WIDTH - 245; // ���W�̒���

	if (0 < life_now) {

		DrawExtendGraph(life_x, 5, life_x + 245, 30, loaded_picture[TYPE_EMPTY], TRUE);
		DrawExtendGraph(life_x, 5, life_x + (245 * life_now) / life_max, 30, loaded_picture[TYPE_LIFE], TRUE);
	}
}

void Enemy_Boss1::draw() {

	life_draw(); // �̗͂̕`��

	if (0 < life_now) {

		SetFontSize(20); // �����T�C�Y�̐ݒ�
		DrawFormatString(Game::WIDTH - 250, 5, GetColor(255, 255, 255), "%d", life_now); // �̗͐��l�̕`��
	}

	if (!count_flag) {

		// STAGE�̒l�ŉ摜��ݒ�
		if (stage <= 3) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS1], TRUE);
		if (4 <= stage && stage <= 6) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS2], TRUE);
		if (7 <= stage && stage <= 9) DrawExtendGraph(m_x, m_y, m_x + m_w, m_y + m_h, loaded_picture[TYPE_ENEMY_BOSS3], TRUE);
	}

	if (count_flag && 0 <= count) {

		DrawExtendGraph(m_x - 6 * count, m_y - 6 * count, m_x + m_w + 6 * count, m_y + m_h + 6 * count, loaded_picture[TYPE_BURN], TRUE);
		count_flag = false;

		if (count <= 0 && !count_flag) {

			remove();
			scene = 4; // �N���A��ʂ�
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
	life_max = 5000; // Enemy Boss2 ���C�t�ݒ�
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

//-------------------------------------------------------------------------------------

// Enemy Shot1 �N���X�i�{�X�j�̎���
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

// Enemy Shot2 �N���X�iENEMY5�E6�j�̎���
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

// HEAL1�i�̗͉񕜁j�N���X�̎���
Heal1::Heal1() {

	m_w = 25;
	m_h = 21;
	m_s = 6;
	damage = -1; // �l�̓}�C�i�X�ɂ��ĉ񕜂�
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

// HEAL2�i����ʉ񕜁j�N���X�̎���
Heal2::Heal2() {

	m_w = 25;
	m_h = 21;
	m_s = 10;
	damage = 0;
	energy = -1; // �l���}�C�i�X�ɂ��ē���ʉ񕜂�
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

// Game �N���X�̎���
void Game::ADD_list(ThingPointa & add) {

	thing_list.push_back(add); // Thing ���X�g�� back �� Thing �N���X�� add ��ǉ�
}

void Game::ADD_score(int sc) {

	score += sc; // �X�R�A��ǉ�
}

bool Game::PUSH_space() {

	if (CheckHitKey(KEY_INPUT_SPACE)) {

		// push_flag�@false �̏ꍇ
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

//-------------------------------------------------------------------------------------

void Game::GAME_SET() {

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

	PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP); // �^�C�g����ʂ̉����Đ�
}

//-------------------------------------------------------------------------------------

void Game::GAME_ALL() {

	// �C�x���g�����̎����֐�
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

//-------------------------------------------------------------------------------------

// scene == 0 �̏ꍇ�@�^�C�g�����
void Game::GAME_TITLE() {

	SetBackgroundColor(0, 0, 0); // �o�b�N�̐F�����F�ɐݒ�
	DrawExtendGraph(10, 200, WIDTH - 10, HEIGHT - 200, Title_p, TRUE); // �^�C�g��
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE

	// �����̕`��
	SetFontSize(20); // �T�C�Y�̐ݒ�
	DrawFormatString(10, 10, GetColor(255, 255, 255), "B E S T  S C O R E : %d", high_score);

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
void Game::GAME_SELECT() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(70, 200, WIDTH - 70, HEIGHT - 200, Select_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Number_p, TRUE); // PUSH SPACE �̕`��

	// �ȉ��� STAGE�P�`�P�O�̕���
	// stage == 1 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_1)) {

		scene = 2; // �v���C���
		stage = 1; // STAGE�P

		// PLAYER ����
		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 2 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_2)) {

		scene = 2;
		stage = 2; // STAGE�Q

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 3 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_3)) {

		scene = 2;
		stage = 3; // STAGE�R

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 4 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_4)) {

		scene = 2;
		stage = 4; // STAGE�S

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 5 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_5)) {

		scene = 2;
		stage = 5; // STAGE�T

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 6 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_6)) {

		scene = 2;
		stage = 6; // STAGE�U

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 7 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_7)) {

		scene = 2;
		stage = 7; // STAGE�V

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 8 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_8)) {

		scene = 2;
		stage = 8; // STAGE�W

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 9 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_9)) {

		scene = 2;
		stage = 9; // STAGE�X

		ThingPointa player(new Player);
		ADD_list(player);
	}

	//-------------------------------------------------------------------------------------

	// stage == 10 �ɐݒ�
	if (CheckHitKey(KEY_INPUT_0)) {

		scene = 2;
		stage = 10; // STAGE�P�O

		ThingPointa player(new Player);
		ADD_list(player);
	}
}

//-------------------------------------------------------------------------------------

// scene == 2 �̏ꍇ�@�v���C���
void Game::GAME_PLAY() {

	// �o�b�N�̕`��
	DrawExtendGraph(p_x, 0, p_w, HEIGHT, Game_p, TRUE);
	DrawExtendGraph(p_x + WIDTH, 0, p_w + WIDTH, HEIGHT, Game_p, TRUE); // �Q���ڂ̃��[�v

	//-------------------------------------------------------------------------------------

	if (!pause_flag) {

		// STAGE�P�`�R�̏ꍇ
		if (stage <= 3) {

			// �G�t�F�N�g�̎����i�o�b�N�����։񂷁j
			p_x -= 2 + add_s;
			p_w -= 2 + add_s;
		}

		// STAGE�S�`�X�̏ꍇ
		if (4 <= stage && stage <= 9) {

			p_x -= 3 + add_s;
			p_w -= 3 + add_s;
		}

		// STAGE�P�O�̏ꍇ
		if (stage == 10) {

			p_x -= 4 + add_s;
			p_w -= 4 + add_s;
		}
	}

	// �{�X�̏ꍇ�@�o�b�N�������ŉ�
	if (add_s < 40 && boss_flag) add_s += 1;

	// �o�b�N�̃��[�v
	if (p_x <= -1200) {

		p_x = 0;
		p_w = WIDTH;
	}

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

		for_each(thing_list.begin(), thing_list.end(), [&](ThingPointa & mob) {

			// ������ HIT �^�C�v�EGET �^�C�v�𔻕ʂ��� �Ԃ��^�C�v�̓������ꍇ
			if (main->HIT_TYPE() == mob->GET_TYPE()) {

				// ������ꍇ
				if (main->HIT_test(mob)) {

					// hit�֐���K�p
					// ���Q�ʁE����ʂ̌v�Z�� GET_damage�֐��EGET_energy�֐����g�p
					main->hit(mob->GET_damage(), mob->GET_energy());
					mob->hit(main->GET_damage(), main->GET_energy());
				}
			}
		});
	});

	// shot_count ���v���X����
	shot_count++;

	//-------------------------------------------------------------------------------------

	// �v���C���̏ꍇ
	if (play_flag) {
		
		SetFontSize(20);
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
				if (stage == 1 || stage == 2 || stage == 3 || stage == 4 || stage == 5 || stage == 6 || stage == 8) {

					if (GetRand(80) == 0) {

						ThingPointa enemy2(new Enemy2);
						ADD_list(enemy2);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				//-------------------------------------------------------------------------------------
				// ENEMY3�i�x�N�g���j
				if (stage == 2 || stage == 4 || stage == 7 || stage == 8) {

					if (GetRand(100) == 0) {

						ThingPointa enemy3(new Enemy3);
						ADD_list(enemy3);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				//-------------------------------------------------------------------------------------
				// ENEMY4�i�����j
				if (stage == 3 || stage == 4 || stage == 7 || stage == 9) {

					if (GetRand(40) == 0) {

						ThingPointa enemy4(new Enemy4);
						ADD_list(enemy4);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				//-------------------------------------------------------------------------------------
				// ENEMY5�i�ʏ�U���j
				if (stage == 5 || stage == 7 || stage == 9) {

					if (GetRand(120) == 0) {

						ThingPointa enemy5(new Enemy5);
						ADD_list(enemy5);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}

				//-------------------------------------------------------------------------------------
				// ENEMY6�i�x�N�g���U���j
				if (stage == 6 || stage == 8 || stage == 9) {

					if (GetRand(120) == 0) {

						ThingPointa enemy6(new Enemy6);
						ADD_list(enemy6);
						if (0 <= enemy_num) enemy_num += 1;
					}
				}
			}

			//-------------------------------------------------------------------------------------
			// STAGE�P�O

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
			// �X�R�A �Q�O�O�O�O�ȏ� ������ �{�X�t���O false �̏ꍇ�@�{�X�𐶐�
			if (20000 <= score && !boss_flag) {

				boss_flag = true; // �{�X�t���O�� true ��

				if (boss_flag) {

					StopSoundMem(Play_m); // �v���C��ʂ̉����~
					PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP); // �{�X��ʂ̉����Đ�

					// STAGE�P�`�X�̏ꍇ
					if (stage <= 9) {

						ThingPointa enemy_boss1(new Enemy_Boss1);
						ADD_list(enemy_boss1);
					}

					// STAGE�P�O�̏ꍇ
					if (stage == 10) {

						ThingPointa enemy_boss2(new Enemy_Boss2);
						ADD_list(enemy_boss2);
					}
				}
			}

			//-------------------------------------------------------------------------------------
			// ��ɐ����@ �񕜐���
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
		if (pause_flag) {

			DrawBox(150, 150, WIDTH - 150, HEIGHT - 150, GetColor(255, 255, 255), TRUE);
			DrawExtendGraph(170, 170, WIDTH - 170, 240, Pause_p, TRUE);
			DrawExtendGraph(160, 330, WIDTH - 160, 420, Esc_p, TRUE);

			pause_time = (GetNowCount() - stop_time) / 1000; // �|�[�Y���Ԃ��v�Z
			
			//-------------------------------------------------------------------------------------
			// �|�[�Y�̏I���E�ĊJ
			if (PUSH_space()) {

				pause_flag = false;
				limit_time = pause_time + limit_time; // �|�[�Y���ԕ��v���X����
				pause_time = 0; // �O��

				// �{�X���o��̏ꍇ�@�v���C���̉����Đ�
				if (!boss_flag) PlaySoundMem(Play_m, DX_PLAYTYPE_LOOP);

				// �{�X�o�ꒆ�̏ꍇ�@�{�X���̉����Đ�
				if (boss_flag) PlaySoundMem(Boss_m, DX_PLAYTYPE_LOOP);
			}
		}

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
		DrawFormatString(600, 170, GetColor(0, 255, 255), "B : S H O T");
		DrawFormatString(600, 200, GetColor(255, 255, 255), "E L S E : S P E C I A L  S H O T");
		DrawFormatString(600, 230, GetColor(0, 255, 255), "S C O R E : 2 0 0 0 0");

		DrawFormatString(600, 320, GetColor(255, 255, 255), "�� H I N T ��");
		DrawFormatString(600, 350, GetColor(0, 255, 255), "I F  Y O U  G E T  T H E  B L U E  H E A R T");
		DrawFormatString(600, 380, GetColor(0, 255, 255), "Y O U  C A N  U S E  S P E C I A L  S H O T ...");

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
	if (!boss_flag) {

		SetFontSize(20);
		DrawFormatString(WIDTH - 220, 15, GetColor(255, 255, 255), "S C O R E : %d", score);
	}

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
	auto end = remove_if(thing_list.begin(), thing_list.end(), [](ThingPointa & Thing) {return Thing->GET_remove(); });
	thing_list.erase(end, thing_list.end());
}

//-------------------------------------------------------------------------------------

// scene == 3 �̏ꍇ�@�I�[�o�[���
void Game::GAME_OVER() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Over_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE);

	now_score = score; // �X�R�A��

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Y O U R  S C O R E : %d", now_score);

	// �n�C�X�R�A���X�R�A�̏ꍇ
	if (high_score < now_score) {

		// �l���㏑���E�L�^
		high_score = now_score;
		SAVE_highscore();
	}

	// SPACE �������ꍇ�@�^�C�g����ʂ�
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Over_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

//-------------------------------------------------------------------------------------

// scene == 4 �̏ꍇ�@�N���A���
void Game::GAME_CLEAR() {

	SetBackgroundColor(0, 0, 0);
	DrawExtendGraph(10, 250, WIDTH - 10, 330, Clear_p, TRUE);
	DrawExtendGraph(150, HEIGHT - 100, WIDTH - 150, HEIGHT - 50, Push_p, TRUE); // PUSH SPACE

	// �X�R�A��
	// �X�R�A�@���@���ԃX�R�A�@�{�@�X�R�A�iMAX�Q�O�O�O�O�j�@�{�@STAGE �~ 10000
	now_score = now_time * 100 + score + stage * 10000;

	SetFontSize(20);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Y O U R  S C O R E : %d", now_score);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "T I M E  P O I N T : %d + S C O R E : %d + S T A G E  P O I N T : %d", now_time * 100, score, stage * 10000);

	// �n�C�X�R�A���X�R�A�̏ꍇ
	if (high_score < now_score) {

		// �l���㏑���E�L�^
		high_score = now_score;
		SAVE_highscore();
	}

	// SPACE �������ꍇ �^�C�g����ʂ�
	if (PUSH_space()) {

		scene = 0;
		StopSoundMem(Clear_m);
		PlaySoundMem(Title_m, DX_PLAYTYPE_LOOP);
	}
}

void Game::GAME_END() {

	DxLib_End(); // DX���C�u�����̏I��
}

//-------------------------------------------------------------------------------------

// WinMain �֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game; // Game �N���X�� game ��
	game.GAME_SET();
	game.GAME_ALL();
	game.GAME_END();
	return 0;
}