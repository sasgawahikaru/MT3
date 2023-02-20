#include <DxLib.h>
//#include "Vector2.h"
#include "Vector3.h"
#include<time.h>
#include<functional>
//int DrawCircle(Vector2 vec, int r, unsigned int color);
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

int DrawLine3D(const Vector3& Pos1, Vector3& Pos2, const unsigned int color);
// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "xx2x_xx_ナマエ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 400;
	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	const int WindowWidth = 1024;
	const int WindowHeight = 576;
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);
	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WindowWidth, WindowHeight, 32);
	// 画面の背景色を設定する
	SetBackgroundColor(0, 0, 64);
	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
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


	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言




	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		//---------  ここからプログラムを記述  ----------//

		// 更新処理
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

		// 描画処理
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
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
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