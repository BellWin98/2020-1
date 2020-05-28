#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName);
void Swap(BYTE *a, BYTE *b);
BYTE Median(BYTE *arr, int size);
void AverageConv(BYTE *Img, BYTE *Out, int W, int H);
BYTE MaxPooling(BYTE *arr, int size);
BYTE MinPooling(BYTE *arr, int size);
void MedianFiltering(BYTE *Img, BYTE *Out, int W, int H, int size);

int main() {
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hinfo;
	RGBQUAD hRGB[256];
	FILE *fp;
	fp = fopen("lenna_gauss.bmp", "rb");
	if (fp == NULL) {
		printf("File is not found\n");
		return -1;
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);

	int ImgSize = hinfo.biWidth * hinfo.biHeight;
	int W = hinfo.biWidth, H = hinfo.biHeight;
	BYTE *Image = (BYTE *)malloc(ImgSize);
	BYTE *Output = (BYTE *)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);

	/*BYTE temp[9];
	int W = hinfo.biWidth, H = hinfo.biHeight;
	int i, j;
	for (i = 1; i < H - 1; i++) { // x좌표
		for (j = 1; j < W - 1; j++) { // y좌표
			temp[0] = Image[(i - 1)*W + j-1]; 
			temp[1] = Image[(i - 1)*W + j];
			temp[2] = Image[(i - 1)*W + j+1];
			temp[3] = Image[i * W + j-1];
			temp[4] = Image[i * W + j]; // 3 by 3에서 center에 해당되는 부분
			temp[5] = Image[i * W + j+1];
			temp[6] = Image[(i + 1)*W + j-1];
			temp[7] = Image[(i + 1)*W + j];
			temp[8] = Image[(i + 1)*W + j+1];
			Output[i*W + j] = Median(temp, 9); // temp배열을 정렬해서 중간에 해당되는 값을 반환, impulse noise(특정화소값)가 있을 때 사용
//			Output[i*W + j] = MaxPooling(temp, 9); // pepper noise만 제거하고 salt noise는 증가
//			Output[i*W + j] = MinPooling(temp, 9); // salt noise만 제거하고 pepper noise는 증가	
		}
	}*/
//	AverageConv(Image, Output, hinfo.biWidth, hinfo.biHeight); // noise가 특정 화소값을 가지지 않을 때 Average Mask사용
	MedianFiltering(Image, Output, W, H, 11);
	SaveBMPFile(hf, hinfo, hRGB, Output, hinfo.biWidth, hinfo.biHeight, "output_11by11.bmp");
	
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

void Swap(BYTE *a, BYTE *b) {

	BYTE temp = *a;
	*a = *b;
	*b = temp;
}
// 오름차순 정렬
BYTE Median(BYTE *arr, int size) {
	
	const int S = size;
	for (int i = 0; i < size - 1; i++) { // pivot index
		for (int j = i + 1; j < size; j++) { // pivot이랑 비교를 하는 대상 인덱스, pivot 다음 인덱스
			if (arr[i] > arr[j]) {
				Swap(&arr[i], &arr[j]);
			}
		}
	}
	return arr[S/2];
}

// 오름차순 진행 후 가장 큰 값 반환
BYTE MaxPooling(BYTE *arr, int size) { 

	const int S = size;
	for (int i = 0; i < size - 1; i++) { // pivot index
		for (int j = i + 1; j < size; j++) { // pivot이랑 비교를 하는 대상 인덱스, pivot 다음 인덱스
			if (arr[i] > arr[j]) {
				Swap(&arr[i], &arr[j]);
			}
		}
	}
	return arr[S-1];
}

BYTE MinPooling(BYTE *arr, int size) {

	const int S = size;
	for (int i = 0; i < size - 1; i++) { // pivot index
		for (int j = i + 1; j < size; j++) { // pivot이랑 비교를 하는 대상 인덱스, pivot 다음 인덱스
			if (arr[i] > arr[j]) {
				Swap(&arr[i], &arr[j]);
			}
		}
	}
	return arr[0];
}

void AverageConv(BYTE *Img, BYTE *Out, int W, int H) {
	double Kernel[3][3] = {
		0.11111, 0.11111, 0.11111,
		0.11111, 0.11111, 0.11111,
		0.11111, 0.11111, 0.11111
	};
	double SumProduct = 0.0;
	// 위아래 margin을 두어야 하므로 커널의 센터인 i와 j는 [1][1]부터 시작
	for (int i = 1; i < H - 1; i++) { // 영상의 행(Y좌표)
		for (int j = 1; j < W - 1; j++) { // 영상의 열(X좌표)
			for (int m = -1; m <= 1; m++) { // 커널의 행, 세로방향으로 봤을 때 m=-1은 센터를 중심으로 나보다 위에있는 것을 표현, m=0은 나 자신, m=1은 나보다 아래에 있는 행
				for (int n = -1; n <= 1; n++) { // 커널의 열, 센터가 속해있는 열을 기준으로 -1은 왼쪽, 0은 나자신, 1은 오른쪽
												// 배열의 인덱스는 음수가 될 수 없으므로 +1, 그리고 커널 인덱스에 따라서 영상에서의 행과 열 위치도 m,n과 연동되므로 각각 +m, +n
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			Out[i*W + j] = (BYTE)SumProduct;
			SumProduct = 0.0; // 다음 convolution때 써야되므로 0으로 초기화
		}
	}
}

void MedianFiltering(BYTE *Img, BYTE *Out, int W, int H, int size) {
	int Length = size;  // Mask의 한 변의 길이
	int Margin = Length / 2; // Mask의 영상영역을 이탈하지 않도록 픽셀의 위, 아래, 좌, 우에 마진을 줌. 
	int WSize = Length * Length; // Mask의 크기 설정
	BYTE* temp = (BYTE*)malloc(sizeof(BYTE) * WSize); // 원래 영상의 색상정보를 입력받을 배열 동적 할당
	int i, j, m, n;
	for (i = Margin; i < H - Margin; i++) {
		for (j = Margin; j < W - Margin; j++) {
			for (m = -Margin; m <= Margin; m++) { // m과 n값이 i,j와 연결되어 동작함. 
				for (n = -Margin; n <= Margin; n++) {
					// 중간값을 찾기위한 원 영상의 배열값을 임의의 배열에 저장.
					// 커널 내의 픽셀값을 일렬로 늘여 세움.(1차원 변환) 
					temp[(m + Margin) * Length + (n + Margin)] = Img[(i + m)*W + j + n];
				}
			}
			// 입력한 사이즈에 해당하는 temp배열을 정렬해서 중간에 해당되는 값을 반환함.
			// 그 후 중간값을 Center Position에 위치시킴. 
			Out[i * W + j] = Median(temp, WSize);
		}
	}
	free(temp); // 임시로 생성된 배열의 메모리를 해제시킴. 
}