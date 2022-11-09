#include <DxLib.h>
#include <cstdlib>
#include <vector>
#include "Vector3.h"

Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t);

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

	SetCameraNearFar(1.0f, 1000.0f);
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		VGet(-20.0f, 20.0f, -200.0f),
		VGet(0.0f, 0.0f, 0.0f),
		VGet(0.0f, 1.0f, 0.0f));


	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;

	Vector3 start(-100.0f, 0.0f, 0.0f);
	Vector3 end(+100.0f, 0.0f, 0.0f);

//	Vector3 p0(-100.0f, 0.0f, 0.0f);
//	Vector3 p1(   0.0f, 0.0f, 100.0f);
	Vector3 p2( -50.0f,  50.0f, +50.0f);
	Vector3 p3( +50.0f, -30.0f, -50.0f);

	std::vector<Vector3> points{ start,start,p2,p3,end,end };

	float maxTime = 5.0f;
	float timeRate;

	Vector3 position;

	startCount = GetNowHiPerformanceCount();


	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾


	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	size_t startIndex = 1;

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		//position += velocity;

		if (CheckHitKey(KEY_INPUT_R))
		{
			startCount = GetNowHiPerformanceCount();
			startIndex = 1;
		}

		nowCount = GetNowHiPerformanceCount();
		elapsedCount = nowCount - startCount;
		float elapsedTime = static_cast<float>(elapsedCount) / 1'000'000.0f;

		//timeRate = min(elapsedTime / maxTime, 1.0f);

		timeRate = elapsedTime / maxTime;

		if (timeRate >= 1.0f)
		{
			if (startIndex < points.size() - 3)
			{

				timeRate -= 1.0f;
				startCount = GetNowHiPerformanceCount();
			}
			else
			{
				timeRate = 1.0f;
			}
			position = splinePosition();
		}
//		Vector3 a = lerp(p0,p1,timeRate);
//		Vector3 b = lerp(p1,p2,timeRate);

//		position = lerp(a,b,timeRate);

		//position = lerp(start, end, timeRate);

		// �`�揈��
		ClearDrawScreen();
		DrawSphere3D(start, 2.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p2,    2.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p3,    2.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(end,   2.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(position,   5.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

		//		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d,%d", position);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "position(%5.1f,%5.1f,%5.1f)", position.x, position.y, position.z);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "startIndex %d", startIndex);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "timeRate %7.3f [%%]", timeRate);
		DrawFormatString(0, 60, GetColor(255, 255, 255), "elapsedTime %7.3f [s]", elapsedTime);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "[R]:Restart");

		DrawFormatString(0, 100, GetColor(255, 255, 255), "start (% 6.1f, % 6.1f, % 6.1f)", start.x, start.y, start.z);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "p2 (% 6.1f, % 6.1f, % 6.1f)", p2.x, p2.y, p2.z);
		DrawFormatString(0, 140, GetColor(255, 255, 255), "p3 (% 6.1f, % 6.1f, % 6.1f)", p3.x, p3.y, p3.z);
		DrawFormatString(0, 160, GetColor(255, 255, 255), "end (% 6.1f, % 6.1f, % 6.1f)", end.x, end.y, end.z);

		//DrawSphere3D(position, 80.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

		Vector3 splinePosition(const std::vector<Vector3>&points, size_t startIndex, float t)
		{
			size_t n = points.size() - 2;

			if (startIndex > n)return points[n];
			if (startIndex < 1)return points[1];

			Vector3 p0 = points[startIndex - 1];
			Vector3 p1 = points[startIndex];
			Vector3 p2 = points[startIndex + 1];
			Vector3 p3 = points[startIndex + 2];
			Vector3 position = ;

			return position;
		}
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
