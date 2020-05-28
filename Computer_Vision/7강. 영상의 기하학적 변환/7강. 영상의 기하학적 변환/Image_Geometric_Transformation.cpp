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
	// ���� ��ȯ �� ������ ������ ����� �� ȸ������ ���̴� ������ �����Ⱚ�� 125 ������ �Ǿ� �ֱ⶧��
	// VerticalFlip(Image, W, H);
	// HorizontalFlip(Image, W, H);
	// Translation(Image, Output, W, H, 100, 40);
	// Scaling(Image, Output, W, H, 0.7, 0.7); // Uniform Scaling (x,y���� ��)
	Rotation(Image, Output, W, H, 60); // ������ �߽����� ȸ��
	
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

	// Tx, Ty -> x, y��ǥ�� �̵����� �����ϴ� ����
	Ty *= -1; // �츮�� �����ϴ� ��ǥ�� �������� ����� �̵�
	// i => y��ǥ
	// j => x��ǥ
	// x�� y��ǥ�� ������ ���� �ֻ�ܺ��� ����
	// BMP������ ���Ʒ��� ������ �ִ�. ���� y��ǥ�� ���� �ʿ�.
	for (int i = 0; i < H; i++) { // ������ 2���������� Ž���ϴ� �������� for�� (����ǥ��)
		for (int j = 0; j < W; j++) {
			if ((i + Ty < H && i + Ty >= 0) && (j + Tx < W && j + Tx >= 0)) { // x�� y�� ������ ���� ����
				Out[(i + Ty)*W + (j + Tx)] = Img[i*W + j]; // ������ ���
			}
		}
	}
}

void VerticalFlip(BYTE *Img, int W, int H) {
	
	// H/2�� �� ����: H�� ������ ���λ����� �ε�
	// ���ݸ�ŭ�� for���� ���鼭 �� ���ٰ� �� �Ʒ����� �ٲٴ� ������ ��ħ.
	for (int i = 0; i < H / 2; i++) { // i�� y��ǥ
		for (int j = 0; j < W; j++) { // j�� x��ǥ
			Swap(&Img[i*W+j], &Img[(H-1-i)*W+j]); // ������ ��������ܰ� �������ϴ��� �ȼ��� �¹ٲ�.
		}
	}
}

void HorizontalFlip(BYTE *Img, int W, int H) {

	// W/2�� �� ����: W�� ������ ���λ����� �ε�
	// ���ݸ�ŭ�� for���� ���鼭 �� ���� �ٰ� �� ������ ���� �ٲٴ� ������ ��ħ.
	for (int i = 0; i < W / 2; i++) { // i�� x��ǥ
		for (int j = 0; j < H; j++) { // j�� y��ǥ
			Swap(&Img[j*W + i], &Img[j*W + (W-1-i)]); 
		}
	}
}

void Scaling(BYTE *Img, BYTE *Out, int W, int H, double SF_X, double SF_Y) {
	int tmpX, tmpY;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			/*tmpX = (int)(j*SF_X); // ������ ��� ����� �� ���(but Hole�߻�)
			tmpY = (int)(i*SF_Y);*/
			tmpX = (int)(j / SF_X); // ������ ��� ���
			tmpY = (int)(i / SF_Y);
			if (tmpY < H && tmpX < W) {
				// Output[tmpY*W + tmpX] = Image[i*W + j]; // ������ ���
				// ������ ����� �Է¿����� ��� ȭ�ҵ��� �˻��ϴ� ���� �ƴ϶�
				// ��¿����� ��� ȭ�ҵ� ��ġ�� Ž���ϸ鼭 ������ �;ߵǴ� �ְ� �������󿡼� ������ ������ ����ϴ� ��
				Out[i*W + j] = Img[tmpY*W + tmpX]; // ������ ���
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
			tmpY = (int)(sin(Radian)*j + cos(Radian)*i);*/ // ������
			tmpX = (int)(cos(Radian)*j + sin(Radian)*i);
			tmpY = (int)(-sin(Radian)*j + cos(Radian)*i); // ������
			if ((tmpY < H && tmpY >= 0) && (tmpX < W && tmpX >= 0)) {
				/*Output[tmpY*W + tmpX] = Image[i*W + j];*/ // ������ ���
				Out[i*W + j] = Img[tmpY*W + tmpX]; // ������ ���
			}
		}
	}
}

void Swap(BYTE *a, BYTE *b) {

	BYTE temp = *a;
	*a = *b;
	*b = temp;
}