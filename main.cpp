#include <DxLib.h>
//#include "Vector2.h"
#include "Vector3.h"
#include<time.h>
#include<functional>
//int DrawCircle(Vector2 vec, int r, unsigned int color);
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

int DrawLine3D(const Vector3& Pos1, Vector3& Pos2, const unsigned int color);
// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "xx2x_xx_�i�}�G: �^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 400;
	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	const int WindowWidth = 1024;
	const int WindowHeight = 576;
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);
	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WindowWidth, WindowHeight, 32);
	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0, 0, 64);
	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);

	int okimono=LoadGraph("tekkyuu.png");
//	int umi = LoadGraph("umi.png");

	SetCameraNearFar(1.0f, 1000.0f);
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		VGet(0.0f, 180.0f, 0.0f),
		VGet(0.0f, 0.0f, 0.0f),
		VGet(0.0f, 0.0f, 1.0f));
	srand((unsigned int)time(NULL));
	int num = rand() % 150;
	int num2 = rand() % 50+200;

	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;

	Vector3 start(-100.0f, 0, 0);
	Vector3 end(+100.0f, 0, 0);
	if (keys[KEY_INPUT_R] == 1) {
		srand((unsigned int)time(NULL));

//		num = power();
	}
	Vector3 p0(-150.0f, 0.0f, 0.0f);
	Vector3 p1(0.0f, 0.0f, num2);
	Vector3 p2(num, 0.0f, 0.0f);
	
	//	Vector3 p3( 100.0f, 0.0f, 0.0f);

	float maxTime = 5.0f;
	float timeRate;

	Vector3 position;

	startCount = GetNowHiPerformanceCount();


	//Vector3 position(0, 0, 0);
	//Vector3 velocity(0.0f, 0.0f, 0.5f);


	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾




	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		//position += velocity;

		if (keys[KEY_INPUT_SPACE] == 0) {

			startCount = GetNowHiPerformanceCount();
		}
		if (keys[KEY_INPUT_SPACE] == 1) {
			nowCount = GetNowHiPerformanceCount();
			elapsedCount = nowCount - startCount;
			float elapsedTime = static_cast<float>(elapsedCount) / 1'000'000.0f;

			timeRate = min(elapsedTime / maxTime, 1.0f);

			Vector3 a = lerp(p0, p1, timeRate);
			Vector3 b = lerp(p1, p2, timeRate);

			position = lerp(a, b, timeRate);
		}
		//position = lerp(start, end, timeRate);

		// �`�揈��
		ClearDrawScreen();
		//		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d,%d", position);
//		DrawFormatString(0, 0, GetColor(255, 255, 255), "position(%6.1f,%6.1f,%6.1f)", position.x, position.y, position.z);
//		DrawFormatString(0, 20, GetColor(255, 255, 255), "%7.3f [s]", elapsedTime);
//		DrawFormatString(0, 40, GetColor(255, 255, 255), "[R]:Restart");
//		DrawFormatString(0, 60, GetColor(255, 255, 255), "p0(% 6.1f, % 6.1f, % 6.1f)", p0.x, p0.y, p0.z);
//		DrawFormatString(0, 80, GetColor(255, 255, 255), "p1(% 6.1f, % 6.1f, % 6.1f)", p1.x, p1.y, p1.z);
//		DrawFormatString(0, 100, GetColor(255, 255, 255), "p2(% 6.1f, % 6.1f, % 6.1f)", p2.x, p2.y, p2.z);
		if (keys[KEY_INPUT_SPACE] == 1) {
			DrawSphere3D(position, 5.0f, 32, GetColor(0, 100, 100), GetColor(255, 255, 255), TRUE);
		}
//		DrawGraph(0,200,GetColor);
		//DrawSphere3D(position, 80.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
//		DrawGraph(0, 0, umi, true);
		DrawGraph(20, 300, okimono, true);
		ScreenFlip();
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

//
//int DrawCircle(Vector2 vec, int r, unsigned int color)
//{
//	return DrawCircle(static_cast<int>(vec.x), static_cast<int>(vec.y), r, color);
//}

int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color)
{
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z };
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z };

	return DrawLine3D(p1, p2, Color);
}