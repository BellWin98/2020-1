#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct {
	int xpos, ypos, x1, x2, y1, y2;
} Point;

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName);
void RGB2YCbCr(BYTE *Image, BYTE *Y, BYTE *Cb, BYTE *Cr, int W, int H);
void SetAxis(BYTE *Temp, Point *point, int W, int H);
void DrawRectOutline(BYTE * Img, int W, int H, int LU_X, int LU_Y, int RD_X, int RD_Y);

int main() {
	BITMAPFILEHEADER hf; // 14byte
	BITMAPINFOHEADER hinfo; // 40byte
	RGBQUAD hRGB[256]; // 1024byte
	FILE *fp;
	fp = fopen("face.bmp", "rb");
	if (fp == NULL) {
		printf("File is not found\n");
		return -1;
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, fp);

	int ImgSize = hinfo.biWidth * hinfo.biHeight;
	int H = hinfo.biHeight, W = hinfo.biWidth;
	Point *point;
	point = (Point *)malloc(sizeof(Point));
	BYTE *Image;
	BYTE *Output;

	if (hinfo.biBitCount == 24) { // True Color
		Image = (BYTE *)malloc(ImgSize * 3);
		Output = (BYTE *)malloc(ImgSize * 3);
		fread(Image, sizeof(BYTE), ImgSize * 3, fp);
	}
	else { // Index(Gray) Color
		fread(hRGB, sizeof(RGBQUAD), 256, fp);
		Image = (BYTE *)malloc(ImgSize);
		Output = (BYTE *)malloc(ImgSize);
		fread(Image, sizeof(BYTE), ImgSize, fp);
	}
	fclose(fp);

	BYTE *Y = (BYTE *)malloc(ImgSize);
	BYTE *Cb = (BYTE *)malloc(ImgSize);
	BYTE *Cr = (BYTE *)malloc(ImgSize);

	RGB2YCbCr(Image, Y, Cb, Cr, W, H);

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if ((Cb[i*W + j] > 80 && Cb[i*W + j] < 140) && (Cr[i*W + j] > 140 && Cr[i*W + j] < 200)) {
				Output[i*W * 3 + j * 3] = Image[i*W * 3 + j * 3];
				Output[i*W * 3 + j * 3 + 1] = Image[i*W * 3 + j * 3 + 1];
				Output[i*W * 3 + j * 3 + 2] = Image[i*W * 3 + j * 3 + 2];
			}
			else {
				Output[i*W * 3 + j * 3] = Output[i*W * 3 + j * 3 + 1] = Output[i*W * 3 + j * 3 + 2] = 0;
			}
		}
	}

	SetAxis(Output, point, W, H);
	DrawRectOutline(Image, W, H, point->x1, point->y1, point->x2, point->y2);

	free(Y);
	free(Cb);
	free(Cr);

	SaveBMPFile(hf, hinfo, hRGB, Image, hinfo.biWidth, hinfo.biHeight, "HW_output.bmp");
	free(point);
	free(Image);
	free(Output);
	return 0;
}

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName) {
	FILE *fp = fopen(FileName, "wb");
	if (hinfo.biBitCount == 24) {
		fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
		fwrite(&hinfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
		fwrite(Output, sizeof(BYTE), W*H * 3, fp);
	}
	else {
		fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
		fwrite(&hinfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
		fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
		fwrite(Output, sizeof(BYTE), W*H, fp);
	}
	fclose(fp);
}

void RGB2YCbCr(BYTE *Image, BYTE *Y, BYTE *Cb, BYTE *Cr, int W, int H) {
	for (int i = 0; i < H; i++) { // YÁÂÇ¥
		for (int j = 0; j < W; j++) { // XÁÂÇ¥
			Y[i * W + j] = (BYTE)(0.299*Image[i*W * 3 + j * 3 + 2] + 0.587*Image[i*W * 3 + j * 3 + 1] + 0.114*Image[i*W * 3 + j * 3]);
			Cb[i * W + j] = (BYTE)(-0.16874*Image[i*W * 3 + j * 3 + 2] + -0.3313*Image[i*W * 3 + j * 3 + 1] + 0.5*Image[i*W * 3 + j * 3] + 128);
			Cr[i * W + j] = (BYTE)(0.5*Image[i*W * 3 + j * 3 + 2] + -0.4187*Image[i*W * 3 + j * 3 + 1] + -0.0813*Image[i*W * 3 + j * 3] + 128);
		}
	}
}

void SetAxis(BYTE *Temp, Point *point, int W, int H) {
	bool exitOuterLoop = false;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (Temp[i*W*3 + j*3] != 0) {
				point->y1 = i;
				printf("y1: %d\n", point->y1);
				exitOuterLoop = true;
				break;
			}
		}
		if (exitOuterLoop == true) {
			exitOuterLoop = false;
			break;
		}
	}

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			if (Temp[j*W*3 + i*3] != 0) {
				point->x1 = i;
				printf("x1: %d\n", point->x1);
				exitOuterLoop = true;
				break;
			}
		}
		if (exitOuterLoop == true) {
			exitOuterLoop = false;
			break;
		}
	}

	for (int i = H-1; i >= 0; i--) {
		for (int j = W-1; j >= 0; j--) {
			if (Temp[i*W*3 + j*3] != 0) {
				point->y2 = i;
				printf("y2: %d\n", point->y2);
				exitOuterLoop = true;
				break;
			}
		}
		if (exitOuterLoop == true) {
			exitOuterLoop = false;
			break;
		}
	}

	for (int i = W-1; i >= 0; i--) {
		for (int j = H-1; j >= 0; j--) {
			if (Temp[j*W*3 + i*3] != 0) {
				point->x2 = i;
				printf("x2: %d\n", point->x2);
				exitOuterLoop = true;
				break;
			}
		}
		if (exitOuterLoop == true) {
			exitOuterLoop = false;
			break;
		}
	}
}

void DrawRectOutline(BYTE * Img, int W, int H, int LU_X, int LU_Y, int RD_X, int RD_Y) {

	for (int i = LU_Y; i <= RD_Y; i++) {
		Img[i*W * 3 + LU_X * 3] = 0;
		Img[i*W * 3 + LU_X * 3+1] = 0;
		Img[i*W * 3 + LU_X * 3+2] = 255;
	}

	for (int j = LU_X; j <= RD_X; j++) {
		Img[LU_Y * W * 3 + j * 3] = 0;
		Img[LU_Y * W * 3 + j * 3+1] = 0;
		Img[LU_Y * W * 3 + j * 3+2] = 255;
	}

	for (int m = LU_Y; m <= RD_Y; m++) {
		Img[m*W * 3 + RD_X * 3] = 0;
		Img[m*W * 3 + RD_X * 3+1] = 0;
		Img[m*W * 3 + RD_X * 3+2] = 255;
	}

	for (int n = LU_X; n <= RD_X; n++) {
		Img[RD_Y*W * 3 + n * 3] = 0;
		Img[RD_Y*W * 3 + n * 3+1] = 0;
		Img[RD_Y*W * 3 + n * 3+2] = 255;
	}
}
