# include <Siv3D.hpp> // Siv3D v0.6.13
# include "field.h"

// ランダムなエンティティをフィールドのサイズに合わせて作成
static void rundfield(field &field);

void Main()
{
	Window::Resize(1366, 768);
	Scene::SetBackground(HSV{ 0, 0.0, 0.86 });


	field field(24);
	rundfield(field);

	Font font{ FontMethod::MSDF, 48, Typeface::Regular };

	std::vector<std::vector<int>> moves;


	while (System::Update())
	{
		/*boardsize = RectF{ 20, 20, 710, 710 };*/
		double edge = 710.0 / field.size();
		for (int32 i = 0; i < field.size(); i++) {
			for (int32 j = 0; j < field.size(); j++) {

				RectF rect{ 20 + edge * j , 20 + edge * i, edge, edge };
				rect
					.drawFrame(3, Palette::Black)
					.draw(Palette::Forestgreen);

				font(field[i][j])
					.draw((30 - field.size()) / 2 * 4, Arg::center(20 + edge / 2 + edge * j, 20 + edge / 2 + edge * i));

				if (rect.mouseOver()) {
					font(U"x:{}, y:{}"_fmt(j, i)).draw(30, Arg::bottomRight(Cursor::Pos()), Palette::White);
					Cursor::RequestStyle(CursorStyle::Hand);
				}

				if (rect.leftClicked()) {
					rundfield(field);
				}
			}
		}


		int32 pairs = 0;
		for (int32 i = 0; i < field.size(); i += 2) {
			for (int32 j = 0; j < field.size(); j += 2) {
				if (field[i][j] == field[i + 1][j]) {
					pairs++;
					RectF{ Arg::topCenter(20 + edge / 2 + edge * j , 20 + edge / 2 + edge * i) , 5 , edge }.rounded(3).draw(ColorF{ 0.6, 0.6, 1.0, 0.6 });
				}
				else if (field[i][j] == field[i][j + 1]) {
					pairs++;
					RectF{ Arg::leftCenter(20 + edge / 2 + edge * j , 20 + edge / 2 + edge * i) , edge , 5 }.rounded(3).draw(ColorF{ 0.6, 0.6, 1.0, 0.6 });
				}
				else if (i - 1 >= 0) {
					if (field[i][j] == field[i - 1][j]) {
						pairs++;
						RectF{ Arg::bottomCenter(20 + edge / 2 + edge * j , 20 + edge / 2 + edge * i) , 5 , edge }.rounded(3).draw(ColorF{ 0.6, 0.6, 1.0, 0.6 });
					}
				}
				else if (j - 1 >= 0) {
					if (field[i][j] == field[i][j - 1]) {
						pairs++;
						RectF{ Arg::rightCenter(20 + edge / 2 + edge * j , 20 + edge / 2 + edge * i) , edge , 5 }.rounded(3).draw(ColorF{ 0.6, 0.6, 1.0, 0.6 });
					}
				}
				if (i + 2 < field.size()) {
					if (field[i + 1][j + 1] == field[i + 2][j + 1]) {
						pairs++;
						RectF{ Arg::topCenter(20 + edge / 2 + edge * (j + 1) , 20 + edge / 2 + edge * (i + 1)) , 5 , edge }.rounded(3).draw(ColorF{ 0.6, 0.6, 1.0, 0.6 });
					}
				}
				else if (j + 2 < field.size()) {
					if (field[i + 1][j + 1] == field[i + 1][j + 2]) {
						pairs++;
						RectF{ Arg::leftCenter(20 + edge / 2 + edge * (j + 1) , 20 + edge / 2 + edge * (i + 1)) , edge , 5 }.rounded(3).draw(ColorF{ 0.6, 0.6, 1.0, 0.6 });
					}
				}
				else if (field[i + 1][j + 1] == field[i][j + 1]) {
					pairs++;
					RectF{ Arg::bottomCenter(20 + edge / 2 + edge * (j + 1) , 20 + edge / 2 + edge * (i + 1)) , 5 , edge }.rounded(3).draw(ColorF{ 0.6, 0.6, 1.0, 0.6 });
				}
				else if (field[i + 1][j + 1] == field[i + 1][j]) {
					pairs++;
					RectF{ Arg::rightCenter(20 + edge / 2 + edge * (j + 1) , 20 + edge / 2 + edge * (i + 1)) , edge , 5 }.rounded(3).draw(ColorF{ 0.6, 0.6, 1.0, 0.6 });
				}
			}
		}


	}
}



void rundfield(field &field) {
	field.setting(field.size());
	int size = field.size();
	for (int num = 0; num < (size * size / 2); num++) {
		for (int i = 0; i < 2; i++) {
			int f = 1, x = Random(0, size - 1), y = Random(0, size - 1);
			while (f) {
				if (field[y][x] == -1) {
					field[y][x] = num;
					f = 0;
				}
				else {
					x = (x + 1) % size;
					if (x == 0) y = (y + 1) % size;
				}
			}
		}
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
