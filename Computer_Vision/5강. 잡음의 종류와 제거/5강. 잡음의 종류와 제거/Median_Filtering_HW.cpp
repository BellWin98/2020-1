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

	int Length = 5;  // Mask�� �� ���� ����
	int Margin = Length / 2; // Mask�� ���󿵿��� ��Ż���� �ʵ��� �ȼ��� ��, �Ʒ�, ��, �쿡 ������ ��. 
	int WSize = Length * Length; // Mask�� ũ�� ����
	BYTE* temp = (BYTE*)malloc(sizeof(BYTE) * WSize); // ���� ������ ���������� �Է¹��� �迭 ���� �Ҵ�
	int W = hinfo.biWidth, H = hinfo.biHeight; // ������ ���ο� ���� ���� ���� �� �ʱ�ȭ. 
	int i, j, m, n;
	for (i = Margin; i < H - Margin; i++) {
		for (j = Margin; j < W - Margin; j++) {
			for (m = -Margin; m <= Margin; m++) { // m�� n���� i,j�� ����Ǿ� ������. 
				for (n = -Margin; n <= Margin; n++) {
					// �߰����� ã������ �� ������ �迭���� ������ �迭�� ����.
					// Ŀ�� ���� �ȼ����� �Ϸķ� �ÿ� ����.(1���� ��ȯ) 
					temp[(m + Margin) * Length + (n + Margin)] = Image[(i + m)*W + j + n]; 
				}
			}
			// �Է��� ����� �ش��ϴ� temp�迭�� �����ؼ� �߰��� �ش�Ǵ� ���� ��ȯ��.
			// �� �� �߰����� Center Position�� ��ġ��Ŵ. 
			Output[i * W + j] = Median(temp, WSize); 
		}
	}
	free(temp); // �ӽ÷� ������ �迭�� �޸𸮸� ������Ŵ. 
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
		for (int j = i + 1; j < size; j++) { // pivot�̶� �񱳸� �ϴ� ��� �ε���, pivot ���� �ε���
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