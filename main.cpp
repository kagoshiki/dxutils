#include "DxLib.h"
#include "draw_plot.h"
#include "update_drawing_area.h"
#include <math.h>
#include <string.h>

#define MENUX 120
#define MENUY 40
#define GSIZE 400 
#define GX (MENUX + 40)
#define GY MENUY

void Display();

double image[28 * 28] = { 0.0 };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int MouseInput;
	int MouseX, MouseY;

	// Setting
	ChangeWindowMode(TRUE);							// Window mode
	SetGraphMode(1200, 600, 32);					// Window size
	SetBackgroundColor(255, 255, 255);	// Background color
	SetMouseDispFlag(TRUE);							// Show mouse

	// Init
	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	// Main loop
	while (ProcessMessage() != -1)
	{
		MouseInput = GetMouseInput();
		if ((MouseInput & MOUSE_INPUT_LEFT) == 1) {
			GetMousePoint(&MouseX, &MouseY);

			// Menu
			if (MouseX < MENUX) {
				if (MouseY < MENUY) break;
				else if (MouseY < MENUY * 2) memset(image, 0, sizeof(image));
			}
		}

		// Update screen
		Display();
	}

	// End
	DxLib_End();

	return 0;
}

void Display() {
	int i;
	constexpr int menun = 2;
	char menu[][20] = {"End", "Clear"};

	// Clear screen
	ClearDrawScreen();

	// Draw menu
	for (i = 0; i < menun; ++i) {
		DrawLine(0, MENUY * (i + 1), MENUX, MENUY * (i + 1), 0);	// Horizon line
		DrawLine(MENUX, MENUY * i, MENUX, MENUY * (i + 1), 0);		// Vertical line
		DrawFormatString(10, MENUY * i + 10, 0, menu[i]);
	}

	DrawPlot(
		GX, GY, GX + GSIZE, GY + GSIZE, [](double x) { return 1 / (exp(-x) + 1); },
		-6.0, 6.0, -0.2, 1.2
	);
	DrawPlot(
		GX, GY, GX + GSIZE, GY + GSIZE, [](double x) { return exp(x); },
		-6.0, 6.0, -0.2, 1.2, GetColor(255, 0, 0)
	);
	UpdateDrawingArea(
		GX + GSIZE + 30, GY, GX + GSIZE * 2 + 30, GY + GSIZE, image, 28, 28
	);

	// Flip screen
	ScreenFlip();
}
