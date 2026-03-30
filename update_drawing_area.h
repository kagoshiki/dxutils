#pragma once
#include "DxLib.h"


inline int UpdateDrawingArea(
	int x1, int y1, int x2, int y2,
	double* image, int imheight, int imwidth
) {

	const int dotSizeW = (x2 - x1) / imwidth;
	const int dotSizeH = (y2 - y1) / imheight;

  // マージンを計算
	const int marginW = ((x2 - x1) % imwidth) / 2;
	const int marginH = ((y2 - y1) % imheight) / 2;
	const int x1a = x1 + marginW;    // x1_adjusted
	const int y1a = y1 + marginH;    // y1_adjusted

	DrawBox(x1, y1, x2, y2, 0, TRUE);

  // マウス入力から配列を更新
  int mouseX, mouseY;
  GetMousePoint(&mouseX, &mouseY);

  if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
    if (mouseX >= x1a && mouseX < x1a + (imwidth * dotSizeW) &&
      mouseY >= y1a && mouseY < y1a + (imheight * dotSizeH)) {

      int imx = (mouseX - x1a) / dotSizeW;
      int imy = (mouseY - y1a) / dotSizeH;

			// マウスを中心とした3x3の範囲に値を加算
      int dx[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
			int dy[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
			double values[] = {0.05, 0.1, 0.05, 0.1, 1.0, 0.1, 0.05, 0.1, 0.05};
      for (int i = 0; i < 9; ++i) {
        int x = imx + dx[i];
        int y = imy + dy[i];
        if (x >= 0 && x < imwidth && y >= 0 && y < imheight) {
          image[y * imwidth + x] += values[i];
					if (image[y * imwidth + x] > 1.0) image[y * imwidth + x] = 1.0;
        }
			}
    }
  }

	// 配列の描画
  for (int i = 0; i < imheight; ++i) {
    for (int j = 0; j < imwidth; ++j) {
      double v = image[i * imwidth + j];
			if (v == 0.0) continue; // 値が0のときは描画しない

      unsigned int color = GetColor((int)(255 * v), (int)(255 * v), (int)(255 * v));
      DrawBox(
        x1a + j * dotSizeW, y1a + i * dotSizeH,
        x1a + (j + 1) * dotSizeW, y1a + (i + 1) * dotSizeH,
        color, TRUE
      );
    }
  }

  return 0;
}
