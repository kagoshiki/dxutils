# DXライブラリ向けユーティリティ
ヘッダファイルのみで動作する、関数プロットと描画のためのユーティリティ関数です。
![sample](https://github.com/kagoshiki/dxutils/blob/master/%E3%82%B9%E3%82%AF%E3%83%AA%E3%83%BC%E3%83%B3%E3%82%B7%E3%83%A7%E3%83%83%E3%83%88%202026-03-30%20185946.png)

## draw_plot.h
関数ポインタを受け取り、指定の範囲でプロットを行います。
```c
// sigmoid
DrawPlot(
	GX, GY, GX + GSIZE, GY + GSIZE, [](double x) { return 1 / (exp(-x) + 1); },
	-6.0, 6.0, -0.2, 1.2
);
// sin (赤線)
DrawPlot(
	GX, GY, GX + GSIZE, GY + GSIZE, [](double x) { return 0.5 * sin(x) + 0.5; },
	-6.0, 6.0, -0.2, 1.2, GetColor(255, 0, 0)
);
```

## update_drawing_area.h
0.0 ~ 1.0の値を持つ配列を受け取り、その値を輝度として描画を行います。  
また、マウスによるお絵描きに対応し、配列を更新します。
```c
double image[28 * 28] = { 0.0 };
UpdateDrawingArea(
	GX + GSIZE + 30, GY, GX + GSIZE * 2 + 30, GY + GSIZE, image, 28, 28
);
```
