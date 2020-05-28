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
	for (i = 1; i < H - 1; i++) { // x��ǥ
		for (j = 1; j < W - 1; j++) { // y��ǥ
			temp[0] = Image[(i - 1)*W + j-1]; 
			temp[1] = Image[(i - 1)*W + j];
			temp[2] = Image[(i - 1)*W + j+1];
			temp[3] = Image[i * W + j-1];
			temp[4] = Image[i * W + j]; // 3 by 3���� center�� �ش�Ǵ� �κ�
			temp[5] = Image[i * W + j+1];
			temp[6] = Image[(i + 1)*W + j-1];
			temp[7] = Image[(i + 1)*W + j];
			temp[8] = Image[(i + 1)*W + j+1];
			Output[i*W + j] = Median(temp, 9); // temp�迭�� �����ؼ� �߰��� �ش�Ǵ� ���� ��ȯ, impulse noise(Ư��ȭ�Ұ�)�� ���� �� ���
//			Output[i*W + j] = MaxPooling(temp, 9); // pepper noise�� �����ϰ� salt noise�� ����
//			Output[i*W + j] = MinPooling(temp, 9); // salt noise�� �����ϰ� pepper noise�� ����	
		}
	}*/
//	AverageConv(Image, Output, hinfo.biWidth, hinfo.biHeight); // noise�� Ư�� ȭ�Ұ��� ������ ���� �� Average Mask���
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
// �������� ����
BYTE Median(BYTE *arr, int size) {
	
	const int S = size;
	for (int i = 0; i < size - 1; i++) { // pivot index
		for (int j = i + 1; j < size; j++) { // pivot�̶� �񱳸� �ϴ� ��� �ε���, pivot ���� �ε���
			if (arr[i] > arr[j]) {
				Swap(&arr[i], &arr[j]);
			}
		}
	}
	return arr[S/2];
}

// �������� ���� �� ���� ū �� ��ȯ
BYTE MaxPooling(BYTE *arr, int size) { 

	const int S = size;
	for (int i = 0; i < size - 1; i++) { // pivot index
		for (int j = i + 1; j < size; j++) { // pivot�̶� �񱳸� �ϴ� ��� �ε���, pivot ���� �ε���
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
		for (int j = i + 1; j < size; j++) { // pivot�̶� �񱳸� �ϴ� ��� �ε���, pivot ���� �ε���
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
	// ���Ʒ� margin�� �ξ�� �ϹǷ� Ŀ���� ������ i�� j�� [1][1]���� ����
	for (int i = 1; i < H - 1; i++) { // ������ ��(Y��ǥ)
		for (int j = 1; j < W - 1; j++) { // ������ ��(X��ǥ)
			for (int m = -1; m <= 1; m++) { // Ŀ���� ��, ���ι������� ���� �� m=-1�� ���͸� �߽����� ������ �����ִ� ���� ǥ��, m=0�� �� �ڽ�, m=1�� ������ �Ʒ��� �ִ� ��
				for (int n = -1; n <= 1; n++) { // Ŀ���� ��, ���Ͱ� �����ִ� ���� �������� -1�� ����, 0�� ���ڽ�, 1�� ������
												// �迭�� �ε����� ������ �� �� �����Ƿ� +1, �׸��� Ŀ�� �ε����� ���� ���󿡼��� ��� �� ��ġ�� m,n�� �����ǹǷ� ���� +m, +n
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			Out[i*W + j] = (BYTE)SumProduct;
			SumProduct = 0.0; // ���� convolution�� ��ߵǹǷ� 0���� �ʱ�ȭ
		}
	}
}

void MedianFiltering(BYTE *Img, BYTE *Out, int W, int H, int size) {
	int Length = size;  // Mask�� �� ���� ����
	int Margin = Length / 2; // Mask�� ���󿵿��� ��Ż���� �ʵ��� �ȼ��� ��, �Ʒ�, ��, �쿡 ������ ��. 
	int WSize = Length * Length; // Mask�� ũ�� ����
	BYTE* temp = (BYTE*)malloc(sizeof(BYTE) * WSize); // ���� ������ ���������� �Է¹��� �迭 ���� �Ҵ�
	int i, j, m, n;
	for (i = Margin; i < H - Margin; i++) {
		for (j = Margin; j < W - Margin; j++) {
			for (m = -Margin; m <= Margin; m++) { // m�� n���� i,j�� ����Ǿ� ������. 
				for (n = -Margin; n <= Margin; n++) {
					// �߰����� ã������ �� ������ �迭���� ������ �迭�� ����.
					// Ŀ�� ���� �ȼ����� �Ϸķ� �ÿ� ����.(1���� ��ȯ) 
					temp[(m + Margin) * Length + (n + Margin)] = Img[(i + m)*W + j + n];
				}
			}
			// �Է��� ����� �ش��ϴ� temp�迭�� �����ؼ� �߰��� �ش�Ǵ� ���� ��ȯ��.
			// �� �� �߰����� Center Position�� ��ġ��Ŵ. 
			Out[i * W + j] = Median(temp, WSize);
		}
	}
	free(temp); // �ӽ÷� ������ �迭�� �޸𸮸� ������Ŵ. 
}