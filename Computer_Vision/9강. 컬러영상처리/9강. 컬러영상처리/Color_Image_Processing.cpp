#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

/*
- 8bit Gray Image (256 Level) - 256개의 색깔을 골라서 씀
14
40
1024
픽셀정보 (1픽셀 = 8bits (1byte))

- 24bit True color (2^24 = 1600만 color) - 
14
40
픽셀정보 (1픽셀 = 24bit (3bytes))
*/

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName);
void FillColor(BYTE *Image, int X, int Y, int W, int H, BYTE R, BYTE G, BYTE B);
void HorizontalStrip(BYTE *Image, int W, int H, BYTE R, BYTE G, BYTE B);

int main() {
	BITMAPFILEHEADER hf; // 14byte
	BITMAPINFOHEADER hinfo; // 40byte
	RGBQUAD hRGB[256]; // 1024byte
	FILE *fp;
	fp = fopen("doraemon.bmp", "rb");
	if (fp == NULL) {
		printf("File is not found\n");
		return -1;
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, fp);
	int ImgSize = hinfo.biWidth * hinfo.biHeight;
	int H = hinfo.biHeight, W = hinfo.biWidth;
	BYTE *Image;
	BYTE *Output;
	if (hinfo.biBitCount == 24) { // True Color
		Image = (BYTE *)malloc(ImgSize*3);
		Output = (BYTE *)malloc(ImgSize*3);
		fread(Image, sizeof(BYTE), ImgSize*3, fp);
	}
	else { // Index(Gray) Color
		fread(hRGB, sizeof(RGBQUAD), 256, fp);
		Image = (BYTE *)malloc(ImgSize);
		Output = (BYTE *)malloc(ImgSize);
		fread(Image, sizeof(BYTE), ImgSize, fp);
	}
	fclose(fp);

	// 가로 라인 그리기
	/*for (int i = 0; i < W; i++) {
		FillColor(Image, i, 200, W, H, 0, 255, 255);
	}*/

	// (50, 100) ~ (300, 400) 박스 그리기
	/*for (int i = 100; i <= 400; i++) {
		for (int j = 50; j <= 300; j++) {
			FillColor(Image, j, i, W, H, 255, 0, 255);
		}
	}*/

	// 가로 띠 만들기
//	HorizontalStrip(Image, W, H, 255, 255, 255);
	
	// 그라데이션 만들기 (Blue ~ Red)
	double weight; // 가중치
	for (int a = 0; a < 120; a++) {
		for (int i = 0; i < W; i++) {
			weight = i / (double)(W - 1);
			Image[a * W * 3 + i * 3] = (BYTE)(255 * (1.0 - weight)); // Blue, i가 0일때는 255 W-1일때는 0
			Image[a * W * 3 + i * 3 + 1] = (BYTE)(255 * (1.0  - weight)); // Green
			Image[a * W * 3 + i * 3 + 2] = (BYTE)(255 * weight); // Red
		}
	}
	
	SaveBMPFile(hf, hinfo, hRGB, Image, hinfo.biWidth, hinfo.biHeight, "output.bmp");
	free(Image);
	free(Output);
	return 0;
}

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName) {
	FILE *fp = fopen(FileName, "wb");
	if (hinfo.biBitCount == 24) {
		fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
		fwrite(&hinfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
		fwrite(Output, sizeof(BYTE), W*H*3, fp);
	}
	else {
		fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
		fwrite(&hinfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
		fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
		fwrite(Output, sizeof(BYTE), W*H, fp);
	}
	fclose(fp);
}

void FillColor(BYTE *Image, int X, int Y, int W, int H, BYTE R, BYTE G, BYTE B) {
	// (50, 40) 위치를 특정 색상으로 색칠
	// RGB값이 같으면 Gray Scale(무채색: 채도를 가지고 있지 않은 색상)
	Image[Y * W * 3 + X * 3] = B; // (50, 40)의 Blue 성분
	Image[Y * W * 3 + X * 3 + 1] = G; // (50, 40)의 Green 성분
	Image[Y * W * 3 + X * 3 + 2] = R; // (50, 40)의 Red 성분
}

void HorizontalStrip(BYTE *Image, int W, int H, BYTE R, BYTE G, BYTE B) {
	
	// 초기화
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			Image[i*W * 3 + j * 3] = 0;
			Image[i*W * 3 + j * 3 + 1] = 0;
			Image[i*W * 3 + j * 3 + 2] = 0;
		}
	}

	// y좌표 기준 0 ~ 239 (Red)
	for (int i = 0; i < 240; i++) {
		for (int j = 0; j < W; j++) {
			Image[i*W * 3 + j * 3 + 2] = R;
		}
	}
	// y좌표 기준 120 ~ 359(Green)
	for (int i = 120; i < 360; i++) {
		for (int j = 0; j < W; j++) {
			Image[i*W * 3 + j * 3 + 1] = G;
		}
	}
	// y좌표 기준 240 ~ 479(Blue)
	for (int i = 240; i < 479; i++) {
		for (int j = 0; j < W; j++) {
			Image[i*W * 3 + j * 3] = B;
		}
	}
	
}