#include "DxLib.h"


typedef double (*PlotFunc)(double);


inline int DrawPlot(
	int x1, int y1, int x2, int y2, PlotFunc f,
	double x_min, double x_max, double y_min, double y_max,
	unsigned int color = 0
) {

	DrawBox(x1, y1, x2, y2, 0, FALSE);
	
	const int width = x2 - x1;
	const int height = y2 - y1;

	// validate
	if (width <= 0 || height <= 0) return -1;
	if (x_max <= x_min || y_max <= y_min) return -1;

	float prev_sx = -1.0, prev_sy = -1.0;

	for (int i = 0; i < width; ++i) {
		const double x = x_min + (x_max - x_min) * (double)i / width;
		const double y = f(x);

		// sx, sy: スクリーン座標
		const float sx = x1 + i;
		const float sy = y2 - (y - y_min) / (y_max - y_min) * height;

		if (i > 0) {
			// 前の点と今回の点がどちらもグラフ範囲外である場合、線を引かない
			//if (!((prev_sy < y1 && sy < y1) || (prev_sy > y2 && sy > y2))) {
			//	DrawLineAA(prev_sx, prev_sy, sx, sy, 0);
			//}
			if ((prev_sy > y1 && sy > y1) && (prev_sy < y2 && sy < y2)) {
				DrawLineAA(prev_sx, prev_sy, sx, sy, color);
			}
		}

		prev_sx = sx;
		prev_sy = sy;
	}

	return 0;
}
