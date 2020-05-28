#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName);
void Swap(BYTE *a, BYTE *b);
void Translation(BYTE *Img, BYTE *Out, int W, int H, int Tx, int Ty);
void VerticalFlip(BYTE *Img, int W, int H);
void HorizontalFlip(BYTE *Img, int W, int H);
void Scaling(BYTE *Img, BYTE *Out, int W, int H, double SF_X, double SF_Y);
void Rotation(BYTE *Img, BYTE *Out, int W, int H, int Angle);

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

	int H = hinfo.biHeight, W = hinfo.biWidth;
	// 기하 변환 후 영상의 범위를 벗어났을 때 회색으로 보이는 이유는 쓰레기값이 125 정도로 되어 있기때문
	// VerticalFlip(Image, W, H);
	// HorizontalFlip(Image, W, H);
	// Translation(Image, Output, W, H, 100, 40);
	// Scaling(Image, Output, W, H, 0.7, 0.7); // Uniform Scaling (x,y같을 때)
	Rotation(Image, Output, W, H, 60); // 원점을 중심으로 회전
	
	SaveBMPFile(hf, hinfo, hRGB, Output, hinfo.biWidth, hinfo.biHeight, "output.bmp");
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

void Translation(BYTE *Img, BYTE *Out, int W, int H, int Tx, int Ty) {

	// Tx, Ty -> x, y좌표의 이동량을 저장하는 변수
	Ty *= -1; // 우리가 생각하는 좌표의 기준으로 제대로 이동
	// i => y좌표
	// j => x좌표
	// x와 y좌표는 영상의 좌측 최상단부터 시작
	// BMP파일은 위아래가 뒤집혀 있다. 따라서 y좌표값 조정 필요.
	for (int i = 0; i < H; i++) { // 영상을 2차원적으로 탐색하는 전형적인 for문 (관용표현)
		for (int j = 0; j < W; j++) {
			if ((i + Ty < H && i + Ty >= 0) && (j + Tx < W && j + Tx >= 0)) { // x와 y의 범위의 조건 설정
				Out[(i + Ty)*W + (j + Tx)] = Img[i*W + j]; // 순방향 사상
			}
		}
	}
}

void VerticalFlip(BYTE *Img, int W, int H) {
	
	// H/2를 한 이유: H가 영상의 세로사이즈 인데
	// 절반만큼만 for문을 돌면서 맨 윗줄과 맨 아랫줄을 바꾸는 과정을 거침.
	for (int i = 0; i < H / 2; i++) { // i는 y좌표
		for (int j = 0; j < W; j++) { // j는 x좌표
			Swap(&Img[i*W+j], &Img[(H-1-i)*W+j]); // 영상의 최좌측상단과 최좌측하단의 픽셀을 맞바꿈.
		}
	}
}

void HorizontalFlip(BYTE *Img, int W, int H) {

	// W/2를 한 이유: W가 영상의 가로사이즈 인데
	// 절반만큼만 for문을 돌면서 맨 왼쪽 줄과 맨 오른쪽 줄을 바꾸는 과정을 거침.
	for (int i = 0; i < W / 2; i++) { // i는 x좌표
		for (int j = 0; j < H; j++) { // j는 y좌표
			Swap(&Img[j*W + i], &Img[j*W + (W-1-i)]); 
		}
	}
}

void Scaling(BYTE *Img, BYTE *Out, int W, int H, double SF_X, double SF_Y) {
	int tmpX, tmpY;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			/*tmpX = (int)(j*SF_X); // 순방향 사상 계산일 때 사용(but Hole발생)
			tmpY = (int)(i*SF_Y);*/
			tmpX = (int)(j / SF_X); // 역방향 사상 계산
			tmpY = (int)(i / SF_Y);
			if (tmpY < H && tmpX < W) {
				// Output[tmpY*W + tmpX] = Image[i*W + j]; // 순방향 사상
				// 역방향 사상은 입력영상의 모든 화소들을 검사하는 것이 아니라
				// 출력영상의 모든 화소들 위치를 탐색하면서 나한테 와야되는 애가 원본영상에서 누군지 역으로 계산하는 것
				Out[i*W + j] = Img[tmpY*W + tmpX]; // 역방향 계산
			}
		}
	}
}

void Rotation(BYTE *Img, BYTE *Out, int W, int H, int Angle) {
	int tmpX, tmpY;
	double Radian = Angle * 3.141592 / 180.0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			/*tmpX = (int)(cos(Radian)*j - sin(Radian)*i);
			tmpY = (int)(sin(Radian)*j + cos(Radian)*i);*/ // 순방향
			tmpX = (int)(cos(Radian)*j + sin(Radian)*i);
			tmpY = (int)(-sin(Radian)*j + cos(Radian)*i); // 역방향
			if ((tmpY < H && tmpY >= 0) && (tmpX < W && tmpX >= 0)) {
				/*Output[tmpY*W + tmpX] = Image[i*W + j];*/ // 순방향 사상
				Out[i*W + j] = Img[tmpY*W + tmpX]; // 역방향 사상
			}
		}
	}
}

void Swap(BYTE *a, BYTE *b) {

	BYTE temp = *a;
	*a = *b;
	*b = temp;
}