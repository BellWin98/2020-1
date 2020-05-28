#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName);
void Gradation(BYTE *Image, int W, int H);

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

	Gradation(Image, W, H);

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
 
void Gradation(BYTE *Image, int W, int H) {

	double weight;
	//	 Blue ~ Yellow
	for (int a = 0; a < 160; a++) {
		for (int i = 0; i < W; i++) {
			weight = i / (double)(W - 1);
			Image[a * W * 3 + i * 3] = (BYTE)(255 * (1.0 - weight)); // Blue
			Image[a * W * 3 + i * 3 + 1] = (BYTE)(255 * weight); // Green
			Image[a * W * 3 + i * 3 + 2] = (BYTE)(255 * weight); // Red
		}
	}

	//	 Green ~ Magenta
	for (int a = 160; a < 320; a++) {
		for (int i = 0; i < W; i++) {
			weight = i / (double)(W - 1);
			Image[a * W * 3 + i * 3 + 1] = (BYTE)(255 * (1.0 - weight)); // Green
			Image[a * W * 3 + i * 3] = (BYTE)(255 * weight); // Blue
			Image[a * W * 3 + i * 3 + 2] = (BYTE)(255 * weight); // Red
		}
	}
	//	 Red ~ Cyan
	for (int a = 320; a < 480; a++) {
		for (int i = 0; i < W; i++) {
			weight = i / (double)(W - 1);
			Image[a * W * 3 + i * 3 + 2] = (BYTE)(255 * (1.0 - weight)); // Red
			Image[a * W * 3 + i * 3 + 1] = (BYTE)(255 * weight); // Green
			Image[a * W * 3 + i * 3] = (BYTE)(255 * weight);// Blue
		}
	}
}