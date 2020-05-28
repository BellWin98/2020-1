#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void Binarization(BYTE *Img, BYTE *Out, int W, int H, BYTE Threshold);
BYTE GonzalezBinThresh(BYTE *Img, int W, int H);

int main() {
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hinfo;
	RGBQUAD hRGB[256];
	FILE *fp;
	fp = fopen("coin.bmp", "rb");
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

	// Gonzalez방법에 의한 이진화에 필요한 코드만 삽입했습니다. 
	BYTE threshold = GonzalezBinThresh(Image, hinfo.biWidth, hinfo.biHeight);
	Binarization(Image, Output, hinfo.biWidth, hinfo.biHeight, threshold);

	fp = fopen("output1.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hinfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), ImgSize, fp);

	fclose(fp);
	free(Image);
	free(Output);
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

BYTE GonzalezBinThresh(BYTE *Img, int W, int H) {
	int ImgSize = W*H;
	int i, j;
	double t = 0.0; // t: threshold
	double low_sum, high_sum;
	double low_cnt, high_cnt;
	double low_avg, high_avg;

	for (i = 0; i < W; i++) {
		for (j = 0; j < H; j++) {
			t += Img[i*H + j];
		}
	}
	t /= ImgSize; // 초기값

	// G1, G2영역 
	while (1) {
		low_sum = 0.0;
		high_sum = 0.0;
		low_cnt = 0.0;
		high_cnt = 0.0;
		low_avg = 0.0;
		high_avg = 0.0;
		
		for (i = 0; i < W; i++) {
			for (j = 0; j < H; j++) {
				if (Img[i*H + j]<=t) {
					low_sum += Img[i*H + j];
					low_cnt++;
				}
				else {
					high_sum += Img[i*H + j];
					high_cnt++;
				}
			}
		}
		// 각 영역의 평균 계산
		low_avg = low_sum / low_cnt;
		high_avg = high_sum / high_cnt;

		// t값이 변경이 없는 경우 종료, 있으면 반복
		if (t == (((low_avg + high_avg) / 2.0) + 1.0)) {
			break;
		}
		else {
			t = ((low_avg + high_avg) / 2.0) + 1.0;
		}

	}
	return (BYTE)t;

}

