#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName);
void RGB2YCbCr(BYTE *Image, BYTE *Y, BYTE *Cb, BYTE *Cr, int W, int H);

int main() {
	BITMAPFILEHEADER hf; // 14byte
	BITMAPINFOHEADER hinfo; // 40byte
	RGBQUAD hRGB[256]; // 1024byte
	FILE *fp;
	fp = fopen("fruit.bmp", "rb");
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

	// Red값이 큰 화소만 masking(영상에서 특정 영역만 내보내고 나머지 부분은 가린다)
	// RGB 모델 기준
	/*for (int i = 0; i < H; i++) { // Y좌표
		for (int j = 0; j < W; j++) { // X좌표
			if (Image[i*W * 3 + j * 3 + 2] > 130 &&
				Image[i*W * 3 + j * 3 + 1] < 50 &&
				Image[i*W * 3 + j * 3 + 0] < 100) {

				Output[i*W * 3 + j * 3] = Image[i*W * 3 + j * 3];
				Output[i*W * 3 + j * 3 + 1] = Image[i*W * 3 + j * 3 + 1];
				Output[i*W * 3 + j * 3 + 2] = Image[i*W * 3 + j * 3 + 2];
			}
			else {
				Output[i*W * 3 + j * 3] = Output[i*W * 3 + j * 3 + 1] = Output[i*W * 3 + j * 3 + 2] = 0;
			}
		}
	}*/

	BYTE *Y = (BYTE *)malloc(ImgSize);
	BYTE *Cb = (BYTE *)malloc(ImgSize);
	BYTE *Cr = (BYTE *)malloc(ImgSize);

	RGB2YCbCr(Image, Y, Cb, Cr, W, H);
	// 빨간색 딸기영역만 masking(YCbCr 모델 기준)
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (Cb[i*W + j] < 130 && Cr[i*W + j]>200) {
				Output[i*W * 3 + j * 3] = Image[i*W * 3 + j * 3];
				Output[i*W * 3 + j * 3 + 1] = Image[i*W * 3 + j * 3 + 1];
				Output[i*W * 3 + j * 3 + 2] = Image[i*W * 3 + j * 3 + 2];
			}
			else {
				Output[i*W * 3 + j * 3] = Output[i*W * 3 + j * 3 + 1] = Output[i*W * 3 + j * 3 + 2] = 0;
			}
		}
	}

	free(Y);
	free(Cb);
	free(Cr);

	/*fp = fopen("Y.raw", "wb");
	fwrite(Y, sizeof(BYTE), W*H, fp);
	fclose(fp);
	fp = fopen("Cb.raw", "wb");
	fwrite(Y, sizeof(BYTE), W*H, fp);
	fclose(fp);
	fp = fopen("Cr.raw", "wb");
	fwrite(Y, sizeof(BYTE), W*H, fp);
	fclose(fp);*/

	SaveBMPFile(hf, hinfo, hRGB, Output, hinfo.biWidth, hinfo.biHeight, "output.bmp");
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
	for (int i = 0; i < H; i++) { // Y좌표
		for (int j = 0; j < W; j++) { // X좌표
			Y[i * W + j] = (BYTE)(0.299*Image[i*W * 3 + j * 3 + 2] + 0.587*Image[i*W * 3 + j * 3 + 1] + 0.114*Image[i*W * 3 + j * 3]);
			Cb[i * W + j] = (BYTE)(-0.16874*Image[i*W * 3 + j * 3 + 2] + -0.3313*Image[i*W * 3 + j * 3 + 1] + 0.5*Image[i*W * 3 + j * 3] + 128);
			Cr[i * W + j] = (BYTE)(0.5*Image[i*W * 3 + j * 3 + 2] + -0.4187*Image[i*W * 3 + j * 3 + 1] + -0.0813*Image[i*W * 3 + j * 3] + 128);
		}
	}
}
