#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ObtainHistogram(BYTE* Img, int* Histo, int W, int H);
void printHistogram(int *Histo);
void Binarization(BYTE *Img, BYTE *Out, int W, int H, BYTE Threshold);
int GonzalezBinThresh(BYTE *Img, int W, int H);
int PixelExistIndexG1(int *Histo, BYTE Threshold);
int PixelExistIndexG2(int *Histo, BYTE Threshold);
int getNewThreshold(int g1, int g2);


int main() {
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hinfo;
	RGBQUAD hRGB[256];
	FILE *fp;
	fp = fopen("lenna.bmp", "rb");
	if (fp == NULL) {
		printf("File is not found\n");
		return -1;
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);

	int ImgSize = hinfo.biWidth * hinfo.biHeight;
	BYTE *Image = (BYTE *)malloc(ImgSize);
	BYTE *Output = (BYTE *)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);
 
	int Histo[256] = { 0 }; // 0으로 초기화

	ObtainHistogram(Image, Histo, hinfo.biWidth, hinfo.biHeight);
//	printHistogram(Histo);

	int Thres = GonzalezBinThresh(Image, hinfo.biWidth, hinfo.biHeight);

	int G1 = PixelExistIndexG1(Histo, Thres);
	int G2 = PixelExistIndexG2(Histo, Thres);
	int ThresFinal = getNewThreshold(G1, G2);
	G1 = PixelExistIndexG1(Histo, ThresFinal);
	G2 = PixelExistIndexG2(Histo, ThresFinal);
	ThresFinal = getNewThreshold(G1, G2);

	Binarization(Image, Output, hinfo.biWidth, hinfo.biHeight, ThresFinal);

	fp = fopen("output1.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hinfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), ImgSize, fp);

	fclose(fp);
	free(Image);
	free(Output);
}


void ObtainHistogram(BYTE* Img, int* Histo, int W, int H) {
	int ImgSize = W*H;
	for (int i = 0; i < ImgSize; i++) {
		Histo[Img[i]]++; // Image[i]: 화소값, 0~255사이의 어떤 값
	}
}

void printHistogram(int *Histo) {

	for (int i = 0; i < 256; i++) {
		printf("%d\n", Histo[i]);
	}
}

void Binarization(BYTE *Img, BYTE *Out, int W, int H, BYTE Threshold) {
	int ImgSize = W*H;
	for (int i = 0; i < ImgSize; i++) {
		if (Img[i] < Threshold) {
			Out[i] = 0;
		}
		else {
			Out[i] = 255;
		}
	}
}

int GonzalezBinThresh(BYTE *Img, int W, int H) {
	int max = Img[0];
	int min = Img[0];
	int median;
	int ImgSize = W*H;

	for (int i = 1; i < ImgSize; i++) {
		if (Img[i] == 0) {
			continue;
		}
		else {
			if (max < Img[i]) {
				max = Img[i];
			}
		}
	}


	for (int i = 1; i < ImgSize; i++) {
		if (Img[i] == 0) {
			continue;
		}
		else {
			if (min > Img[i]) {
				min = Img[i];
			}
		}
	}
	median = (max + min) / 2;
	return median;
}
// G1: 밝기값이 경계값 T보다 큰 화소들로 구성된 영역
int PixelExistIndexG1(int *Histo, BYTE Threshold) {

	int count = 0;
	int sum = 0;
	int avg;

	for (int i = Threshold; i < 256; i++) {
		if (Histo[i] == 0) {
			continue;
		}
		else {
			sum += i;
			count++;
		}

	}
	avg = sum / count;
	return avg;
}
// G2: 밝기값이 경계값 T보다 작은 화소들로 구성된 영역
int PixelExistIndexG2(int *Histo, BYTE Threshold) {

	int count = 0;
	int sum = 0;
	int avg;

	for (int i = 0; i < Threshold; i++) {
		if (Histo[i] == 0) {
			continue;
		}
		else {
			sum += i;
			count++;
		}
		
	}
	avg = sum / count;
	return avg;
}

int getNewThreshold(int g1, int g2) {

	int avg = (g1 + g2) / 2;
	return avg;
}