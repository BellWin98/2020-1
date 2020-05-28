#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName);
BYTE Median(BYTE *arr, int size);
void Swap(BYTE *a, BYTE *b);

int main() {
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hinfo;
	RGBQUAD hRGB[256];
	FILE *fp;
	fp = fopen("lenna_impulse.bmp", "rb");
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

	int Length = 5;  // Mask의 한 변의 길이
	int Margin = Length / 2; // Mask의 영상영역을 이탈하지 않도록 픽셀의 위, 아래, 좌, 우에 마진을 줌. 
	int WSize = Length * Length; // Mask의 크기 설정
	BYTE* temp = (BYTE*)malloc(sizeof(BYTE) * WSize); // 원래 영상의 색상정보를 입력받을 배열 동적 할당
	int W = hinfo.biWidth, H = hinfo.biHeight; // 영상의 가로와 세로 변수 선언 및 초기화. 
	int i, j, m, n;
	for (i = Margin; i < H - Margin; i++) {
		for (j = Margin; j < W - Margin; j++) {
			for (m = -Margin; m <= Margin; m++) { // m과 n값이 i,j와 연결되어 동작함. 
				for (n = -Margin; n <= Margin; n++) {
					// 중간값을 찾기위한 원 영상의 배열값을 임의의 배열에 저장.
					// 커널 내의 픽셀값을 일렬로 늘여 세움.(1차원 변환) 
					temp[(m + Margin) * Length + (n + Margin)] = Image[(i + m)*W + j + n]; 
				}
			}
			// 입력한 사이즈에 해당하는 temp배열을 정렬해서 중간에 해당되는 값을 반환함.
			// 그 후 중간값을 Center Position에 위치시킴. 
			Output[i * W + j] = Median(temp, WSize); 
		}
	}
	free(temp); // 임시로 생성된 배열의 메모리를 해제시킴. 
	SaveBMPFile(hf, hinfo, hRGB, Output, hinfo.biWidth, hinfo.biHeight, "median_5.bmp");

	free(Image);
	free(Output);
	return 0;
}

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName) {
	FILE *fp = fopen(FileName, "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hinfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), W*H, fp);
	fclose(fp);
}

BYTE Median(BYTE *arr, int size) {

	const int S = size;
	for (int i = 0; i < size - 1; i++) { // pivot index
		for (int j = i + 1; j < size; j++) { // pivot이랑 비교를 하는 대상 인덱스, pivot 다음 인덱스
			if (arr[i] > arr[j]) {
				Swap(&arr[i], &arr[j]);
			}
		}
	}
	return arr[S / 2];
}

void Swap(BYTE *a, BYTE *b) {

	BYTE temp = *a;
	*a = *b;
	*b = temp;
}