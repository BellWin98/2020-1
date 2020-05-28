#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ObtainHistogram(BYTE* Img, int* Histo, int W, int H);
void printHistogram(int *Histo);
void Binarization(BYTE *Img, BYTE *Out, int W, int H, BYTE Threshold);
BYTE Initial_Threshold(BYTE *Img, int W, int H);
BYTE Get_G1_G2(int *Histo, BYTE *Threshold);

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
	BYTE temp_thres = Initial_Threshold(Image, hinfo.biWidth, hinfo.biHeight);
	BYTE final_thres = Get_G1_G2(Histo, &temp_thres);
	Binarization(Image, Output, hinfo.biWidth, hinfo.biHeight, final_thres);

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

BYTE Initial_Threshold(BYTE *Img, int W, int H) {
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
	return (BYTE)median;
}
BYTE Get_G1_G2(int *Histo, BYTE *Threshold) {

	int avg;
	int low_sum = 0, high_sum = 0, low_cnt = 0, high_cnt = 0;
	do {
		avg = *Threshold;
		for (int i = 0; i < 256; i++) {
			// 낮은 화소값들의 평균값(G2)
			if (i <= *Threshold) {
				low_cnt += Histo[i];
				low_sum = low_sum + Histo[i] * i;
			}
			// 높은 화소값들의 평균값(G1)
			else {
				high_cnt += Histo[i];
				high_sum = high_sum + Histo[i] * i;
			}
		}
		*Threshold = ((low_sum / (double)low_cnt) + (high_sum / (double)high_cnt)) / 2.0;
	} while (abs(*Threshold-avg)<=3);
	return (BYTE)*Threshold;
}

