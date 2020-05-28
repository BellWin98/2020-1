#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void OriginalImage(BYTE *Img, BYTE *Out, int W, int H);
void InverseImage(BYTE *Img, BYTE *Out, int W, int H);
void BrightnessAdj(BYTE *Img, BYTE *Out, int W, int H, int Val);
void ContrastAdj(BYTE* Img, BYTE* Out, int W, int H, double Val);
void ObtainHistogram(BYTE* Img, int* Histo, int W, int H);
void ObtainAHistogram(int *Histo, int *AHisto);
void printAHistogram(int *AHisto);
void printHistogram(int *Histo);
void HistogramStretching(BYTE *Img, BYTE *Out, int *Histo, int W, int H);
void HistogramEqualization(BYTE *Img, BYTE *Out, int *AHisto, int W, int H);
void Binarization(BYTE *Img, BYTE *Out, int W, int H, BYTE Threshold);
int GonzalezBinThresh(BYTE *Img, int W, int H);


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

	// OriginalImage(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// InverseImage(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// BrightnessAdj(Image, Output, hinfo.biWidth, hinfo.biHeight, 70);
	// ContrastAdj(Image, Output, hinfo.biWidth, hinfo.biHeight, 1.5); 


	int Histo[256] = { 0 }; // 0���� �ʱ�ȭ
	int AHisto[256] = { 0 }; // ���� ������׷�(Accumulated Histogram)

	// ObtainHistogram(Image, Histo, hinfo.biWidth, hinfo.biHeight);
	// ObtainAHistogram(Histo, AHisto);
	// HistogramEqualization(Image, Output, AHisto, hinfo.biWidth, hinfo.biHeight);
	// HistogramStretching(Image, Output, Histo, hinfo.biWidth, hinfo.biHeight);
	// printHistogram(Histo);
	// printAHistogram(AHisto);
	 int Thres = GonzalezBinThresh(Image, hinfo.biWidth, hinfo.biHeight);
	// �Ӱ�ġ�� �ʹ� ���ų� ���� ������ �̻��� ����� ����. 80�� ����.
	// �ְ����� �Ǵ�, �������� �Ǵ� �Ǵ� �ڵ� �Ӱ�ġ ��������� ����.
	 Binarization(Image, Output, hinfo.biWidth, hinfo.biHeight, Thres);


	fp = fopen("output.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hinfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), ImgSize, fp);

	fclose(fp);
	free(Image);
	free(Output);
}

void OriginalImage(BYTE *Img, BYTE *Out, int W, int H) {
	int ImgSize = W*H;
	for (int i = 0; i < ImgSize; i++) {
		Out[i] = Img[i];
	}
}
void InverseImage(BYTE *Img, BYTE *Out, int W, int H) {
	int ImgSize = W*H;
	for (int i = 0; i < ImgSize; i++) {
		Out[i] = 255 - Img[i];
	}
}

void BrightnessAdj(BYTE *Img, BYTE *Out, int W, int H, int Val) {
	int ImgSize = W*H;
	for (int i = 0; i < ImgSize; i++) {
		if (Img[i] + Val > 255.0) {
			Out[i] = 255;
		}
		else if (Img[i] + Val < 0) {
			Out[i] = 0;
		}
		else {
			Out[i] = Img[i] + Val;
		}

	}
}

// Contrast(���): ��� ��ο� ���� ���̰� Ȯ���� ������.
void ContrastAdj(BYTE* Img, BYTE* Out, int W, int H, double Val) {
	int ImgSize = W*H;
	for (int i = 0; i < ImgSize; i++) {
		if (Img[i] * Val > 255) {
			Out[i] = 255;
		}
		else {
			Out[i] = (BYTE)(Img[i] * Val); // ��°��� BYTE�̱� ������ ��������ȯ ������
		}
	}
}

// ������׷�: ���󿡼� �׷��̿��� �������� 0~255������ ȭ�Ұ��� �ִµ�  
// �� ȭ�Ұ��� ������ ȭ�Ұ� ���� � �ִ��� ī��Ʈ ��.
void ObtainHistogram(BYTE* Img, int* Histo, int W, int H) {
	int ImgSize = W*H;
	for (int i = 0; i < ImgSize; i++) {
		Histo[Img[i]]++; // Image[i]: ȭ�Ұ�, 0~255������ � ��
	}
}

void ObtainAHistogram(int *Histo, int *AHisto) {

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j <= i; j++) {
			AHisto[i] += Histo[j];
		}
	}
}

// ��°��� �����ؼ� ������ �׷����� Ȯ���غ���
void printHistogram(int *Histo) {

	for (int i = 0; i < 256; i++) {
		printf("%d\n", Histo[i]);
	}
}

void printAHistogram(int *AHisto) {
	for (int i = 0; i < 256; i++) {
		printf("%d\n", AHisto[i]);
	}
}

// ��Ʈ��Ī -> ������ ���ü��� ����!
void HistogramStretching(BYTE *Img, BYTE *Out, int *Histo, int W, int H) {
	BYTE Low, High;
	int ImgSize = W*H;
	for (int i = 0; i < 256; i++) {
		if (Histo[i] != 0) {
			Low = i;
			break;
		}
	}
	for (int i = 255; i >= 0; i--) {
		if (Histo[i] != 0) {
			High = i;
			break;
		}
	}
	for (int i = 0; i < ImgSize; i++) {
		Out[i] = (BYTE)((Img[i] - Low) / (double)(High - Low)*255.0); // 0���� 1���̷� ����ȭ
	}
}

// Equalization(��Ȱȭ)�� Stretching ���� ��ũ��ġ�� �� �ߺ���. 
// �ܼ��� 0~255���� ȭ�Ұ� �����ϵ��� ���������� ȭ�Ұ��� �� �Ǵ� �����̾ƴ϶�
// ȭ���� ������������ ����ؼ� ȭ�Ұ� 0~255���� ���� �����ϵ��� ���ġ�� ����
// ������׷��� ����� ���ϴ� ������ �ִ�. 
// ��Ʈ��Ī���� ������ ���ü��� �� ����Ų��. 
void HistogramEqualization(BYTE *Img, BYTE *Out, int *AHisto, int W, int H) {
	int ImgSize = W*H;
	int Nt = W*H, Gmax = 255;
	double Ratio = Gmax / (double)Nt;
	BYTE NormSum[256];
	for (int i = 0; i < 256; i++) {
		NormSum[i] = (BYTE)(Ratio*AHisto[i]);
	}
	for (int i = 0; i < ImgSize; i++) {
		Out[i] = NormSum[Img[i]];
	}
}

// ����ȭ: ������ ȭ�Ұ��� 0~255���� � �Ӱ谪�� �������� �Ӱ谪���� ������ 0, ũ�� 255�� 
// 256�ܰ�� ǥ���Ǵ� ������ ȭ�Ұ��� �� �δܰ�� ǥ��.
// Threshold�� �Ӱ�ġ
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
