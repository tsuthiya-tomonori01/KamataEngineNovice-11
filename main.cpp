#include <Novice.h>
#include <math.h>
#include <string>
#include "time.h"

const char kWindowTitle[] = "LE2D_14_ツチヤ_トモノリ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	int Block_PosX[4] = { 640, 640, 640, 640 };
	int Block_PosY[4] = { -100,-350,-600,-850 };
	int Block_Radius[4] = { 50, 50,  50,  50 };
	int Block_color[4] = { 0,  1,   2,   3 };

	int Block_2_PosX[4] = { 200, 1080, 200, 1080 };
	int Block_2_PosY[4] = { 200, 200,  520, 520 };
	int Block_2_Radius[4] = { 50, 50,  50,  50 };
	int Block_2_color[4] = { 0,1,2,3 };

	int Hit_Circle_PosX[2] = { 640,640 };
	int Hit_Circle_PosY[2] = { 200,520 };
	int Hit_Circle_Radius[2] = { 70, 70 };

	bool Block_Flag_1[4] = {};
	bool Block_Flag_2[4] = {};
	bool Block_Flag_3[4] = {};
	bool Block_Flag_4[4] = {};

	bool Block_2_Flag_1[4] = {};
	bool Block_2_Flag_2[4] = {};
	bool Block_2_Flag_3[4] = {};
	bool Block_2_Flag_4[4] = {};

	int Block_Speed = 0;

	int GameFrame = 0;

	int Score = 0;

	int GameScene = 0;

	srand((unsigned int)time(NULL));

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		switch (GameScene)
		{
		case 0:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE])
			{
				GameScene = 1;
			}
			break;
		case 1:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE])
			{
				GameScene = 2;

				for (int i = 0; i < 4; i++) {
					Block_Flag_1[i] = 1;
					Block_Flag_2[i] = 1;
					Block_Flag_3[i] = 1;
					Block_Flag_4[i] = 1;
				}

				Block_Speed = 2;

				GameFrame = 0;
			}
			break;
		case 2:

			GameFrame++;
			if (GameFrame >= 2000) {
				Block_Speed = 3;
			}
			if (GameFrame >= 4000) {
				Block_Speed = 4;
			}
			if (GameFrame >= 7000) {
				Block_Speed = 5;
			}

			for (int i = 0; i < 4; i++)
			{
				if (Block_PosX[i] == 640)
				{
					Block_PosY[i] += Block_Speed;
				}
				else
				{
				}

				//消滅処理
				if (Block_PosY[i] >= 870 && Block_color[i] == 0)
				{
					Block_PosY[i] = -150;
					Block_color[i] = rand() % 4;

					//フラグ
					Block_Flag_1[i] = 1;
					Block_2_Flag_1[i] = 0;
				}

				if (Block_PosY[i] >= 870 && Block_color[i] == 1)
				{
					Block_PosY[i] = -150;
					Block_color[i] = rand() % 4;

					//フラグ
					Block_Flag_2[i] = 1;
					Block_2_Flag_2[i] = 0;
				}

				if (Block_PosY[i] >= 870 && Block_color[i] == 2)
				{
					Block_PosY[i] = -150;
					Block_color[i] = rand() % 4;

					//フラグ
					Block_Flag_3[i] = 1;
					Block_2_Flag_3[i] = 0;
				}

				if (Block_PosY[i] >= 870 && Block_color[i] == 3)
				{
					Block_PosY[i] = -150;
					Block_color[i] = rand() % 4;

					//フラグ
					Block_Flag_4[i] = 1;
					Block_2_Flag_4[i] = 0;
				}

				//移動処理
				if (170 <= Block_PosY[i] && Block_PosY[i] <= 230)
				{
					//赤
					if (Block_color[i] == 0 && Block_Flag_1[i] == 1)
					{
						if (keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0)
						{
							Block_Flag_1[i] = 0;
							Block_2_Flag_1[i] = 1;

							Score += 10;
						}
					}

					//青
					if (Block_color[i] == 1 && Block_Flag_2[i] == 1)
					{
						if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0)
						{
							Block_Flag_2[i] = 0;
							Block_2_Flag_2[i] = 1;

							Score += 10;
						}
					}
				}

				//移動処理
				if (490 <= Block_PosY[i] && Block_PosY[i] <= 550)
				{
					//緑
					if (Block_color[i] == 2 && Block_Flag_3[i] == 1)
					{
						if (keys[DIK_UP] && preKeys[DIK_UP])
						{
							Block_Flag_3[i] = 0;
							Block_2_Flag_3[i] = 1;

							Score += 10;
						}
					}

					//黒
					if (Block_color[i] == 3 && Block_Flag_4[i] == 1)
					{
						if (keys[DIK_DOWN] && preKeys[DIK_DOWN])
						{
							Block_Flag_4[i] = 0;
							Block_2_Flag_4[i] = 1;

							Score += 10;
						}
					}
				}

			}

			break;

		case 3:

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE])
			{
				GameScene = 0;

				Score = 0;

				for (int i = 0; i < 4; i++) {
					Block_Flag_1[i] = 0;
					Block_Flag_2[i] = 0;
					Block_Flag_3[i] = 0;
					Block_Flag_4[i] = 0;
				}

			}

			break;
		case 4:

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE])
			{
				GameScene = 0;

				Score = 0;

				for (int i = 0; i < 4; i++) {
					Block_Flag_1[i] = 0;
					Block_Flag_2[i] = 0;
					Block_Flag_3[i] = 0;
					Block_Flag_4[i] = 0;
				}
			}


			break;
		}



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		if (GameScene == 0)
		{

		}

		if (GameScene == 1)
		{

		}

		if (GameScene == 2)
		{
			for (int h = 0; h < 2; h++)
			{
				Novice::DrawEllipse(Hit_Circle_PosX[h], Hit_Circle_PosY[h], Hit_Circle_Radius[h], Hit_Circle_Radius[h], 0.0f, WHITE, kFillModeSolid);

				Novice::DrawEllipse(Hit_Circle_PosX[h], Hit_Circle_PosY[h], Hit_Circle_Radius[h], Hit_Circle_Radius[h], 0.0f, WHITE, kFillModeSolid);
			}

			for (int i = 0; i < 4; i++)
			{
				//ブロック１
				if (Block_color[i] == 0 && Block_Flag_1[i] == 1)
				{
					Novice::DrawEllipse(Block_PosX[i], Block_PosY[i], Block_Radius[i], Block_Radius[i], 0.0f, RED, kFillModeSolid);
				}

				if (Block_color[i] == 1 && Block_Flag_2[i] == 1)
				{
					Novice::DrawEllipse(Block_PosX[i], Block_PosY[i], Block_Radius[i], Block_Radius[i], 0.0f, BLUE, kFillModeSolid);
				}

				if (Block_color[i] == 2 && Block_Flag_3[i] == 1)
				{
					Novice::DrawEllipse(Block_PosX[i], Block_PosY[i], Block_Radius[i], Block_Radius[i], 0.0f, GREEN, kFillModeSolid);
				}

				if (Block_color[i] == 3 && Block_Flag_4[i] == 1)
				{
					Novice::DrawEllipse(Block_PosX[i], Block_PosY[i], Block_Radius[i], Block_Radius[i], 0.0f, BLACK, kFillModeSolid);
				}


				//ブロック２
				if (Block_2_color[i] == 0 && Block_2_Flag_1[i] == 1)
				{
					Novice::DrawEllipse(Block_2_PosX[i], Block_2_PosY[i], Block_2_Radius[i], Block_2_Radius[i], 0.0f, RED, kFillModeSolid);
				}

				if (Block_2_color[i] == 1 && Block_2_Flag_2[i] == 1)
				{
					Novice::DrawEllipse(Block_2_PosX[i], Block_2_PosY[i], Block_2_Radius[i], Block_2_Radius[i], 0.0f, BLUE, kFillModeSolid);
				}

				if (Block_2_color[i] == 2 && Block_2_Flag_3[i] == 1)
				{
					Novice::DrawEllipse(Block_2_PosX[i], Block_2_PosY[i], Block_2_Radius[i], Block_2_Radius[i], 0.0f, GREEN, kFillModeSolid);
				}

				if (Block_2_color[i] == 3 && Block_2_Flag_4[i] == 1)
				{
					Novice::DrawEllipse(Block_2_PosX[i], Block_2_PosY[i], Block_2_Radius[i], Block_2_Radius[i], 0.0f, BLACK, kFillModeSolid);
				}
			}

			Novice::ScreenPrintf(0, 10, "Score %d", Score);
		}

		if (GameScene == 3)
		{

		}

		if (GameScene == 4)
		{

		}
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
