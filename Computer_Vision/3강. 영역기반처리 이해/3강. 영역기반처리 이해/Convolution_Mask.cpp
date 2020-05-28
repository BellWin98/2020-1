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
void AverageConv(BYTE *Img, BYTE *Out, int W, int H); // �ڽ� ��Ȱȭ
void GaussAvrConv(BYTE *Img, BYTE *Out, int W, int H); // ����þ� ��Ȱȭ
void Prewitt_X_Conv(BYTE *Img, BYTE *Out, int W, int H); 
void Prewitt_Y_Conv(BYTE *Img, BYTE *Out, int W, int H);
void Sobel_X_Conv(BYTE *Img, BYTE *Out, int W, int H); // Sobel�� Prewitt���� �� ÷���� ��谡 ����!
void Sobel_Y_Conv(BYTE *Img, BYTE *Out, int W, int H);
void Laplace_Conv(BYTE *Img, BYTE *Out, int W, int H);
void Laplace_Conv_DC(BYTE *Img, BYTE *Out, int W, int H);

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
	BYTE *Temp = (BYTE *)malloc(ImgSize); // �ӽù迭
	BYTE *Output = (BYTE *)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);

	// OriginalImage(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// InverseImage(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// BrightnessAdj(Image, Output, hinfo.biWidth, hinfo.biHeight, 70);
	// ContrastAdj(Image, Output, hinfo.biWidth, hinfo.biHeight, 1.5); 


	// int Histo[256] = { 0 }; // 0���� �ʱ�ȭ
	// int AHisto[256] = { 0 }; // ���� ������׷�(Accumulated Histogram)

	// ObtainHistogram(Image, Histo, hinfo.biWidth, hinfo.biHeight);
	// ObtainAHistogram(Histo, AHisto);
	// HistogramEqualization(Image, Output, AHisto, hinfo.biWidth, hinfo.biHeight);
	// HistogramStretching(Image, Output, Histo, hinfo.biWidth, hinfo.biHeight);
	// printHistogram(Histo);
	// printAHistogram(AHisto);
	// �Ӱ�ġ�� �ʹ� ���ų� ���� ������ �̻��� ����� ����. 80�� ����.
	// �ְ����� �Ǵ�, �������� �Ǵ� �Ǵ� �ڵ� �Ӱ�ġ ��������� ����.
	
	// AverageConv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// GaussAvrConv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// Prewitt_X_Conv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	// Prewitt_Y_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// Sobel_X_Conv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	// Sobel_Y_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// Laplace_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);

	// ������(������)������ ���̱� ���� ��Ȱȭ�� ��ħ! ������� �� �����
	GaussAvrConv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	Laplace_Conv_DC(Temp, Output, hinfo.biWidth, hinfo.biHeight); 
	 // prewitt �Ǵ� Sobel�� X�� Y�� ��ġ�� ���� 
	 /*for (int i = 0; i < ImgSize; i++) {
		 if (Temp[i] > Output[i]) {
			 Output[i] = Temp[i];
		 }
	 }*/
	// Binarization(Output, Output, hinfo.biWidth, hinfo.biHeight, 40); // ��谪�� ������� ��谡 ���ϰ� ��Ÿ��.

	fp = fopen("Laplacian_DC_After_Gauss.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hinfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), ImgSize, fp);

	fclose(fp);
	free(Image);
	free(Output);
	free(Temp);
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

void AverageConv(BYTE *Img, BYTE *Out, int W, int H) {
	double Kernel[3][3] = {
		 0.11111, 0.11111, 0.11111,
		 0.11111, 0.11111, 0.11111,
		 0.11111, 0.11111, 0.11111
	};
	double SumProduct = 0.0;
	// ���Ʒ� margin�� �ξ�� �ϹǷ� Ŀ���� ������ i�� j�� [1][1]���� ����
	for (int i = 1; i < H-1; i++) { // ������ ��(Y��ǥ)
		for (int j = 1; j < W-1; j++) { // ������ ��(X��ǥ)
			for (int m = -1; m <= 1; m++) { // Ŀ���� ��, ���ι������� ���� �� m=-1�� ���͸� �߽����� ������ �����ִ� ���� ǥ��, m=0�� �� �ڽ�, m=1�� ������ �Ʒ��� �ִ� ��
				for (int n = -1; n <= 1; n++) { // Ŀ���� ��, ���Ͱ� �����ִ� ���� �������� -1�� ����, 0�� ���ڽ�, 1�� ������
					// �迭�� �ε����� ������ �� �� �����Ƿ� +1, �׸��� Ŀ�� �ε����� ���� ���󿡼��� ��� �� ��ġ�� m,n�� �����ǹǷ� ���� +m, +n
					SumProduct += Img[(i+m)*W+(j+n)] * Kernel[m+1][n+1]; 
				}
			}
			Out[i*W + j] = (BYTE)SumProduct;
			SumProduct = 0.0; // ���� convolution�� ��ߵǹǷ� 0���� �ʱ�ȭ
		}
	}
}

// ���Ϳ� ���� ����ġ�� ���� �ְ� �Ÿ��� �־������� ����ġ�� ���� �۰��ִ� ��
// ���Ϳ� ���� ����ġ�� ���� �ְڴٴ� �ǹ̴� ���������� ����(����)�� ���� ������ �ϰڴٶ�� ��.
// ���͸� �������� ���������� �밢���� ��ġ�� �͵麸�� �Ÿ��� �����Ƿ� Weight�� �� ũ�� ��. 
void GaussAvrConv(BYTE *Img, BYTE *Out, int W, int H) {
	// kernel�� weight�� �� 16�� �������� �� �ȼ��� weight ����
	// �� �ȼ��� ������ ���� 1�̾�� �ϹǷ� 16���� �������ش�. 
	double Kernel[3][3] = {
		0.0625, 0.125, 0.0625,
		0.125, 0.25, 0.125,
		0.0625, 0.125, 0.0625
	};
	double SumProduct = 0.0;
	for (int i = 1; i < H - 1; i++) { // ������ ��(Y��ǥ)
		for (int j = 1; j < W - 1; j++) { // ������ ��(X��ǥ)
			for (int m = -1; m <= 1; m++) { // Ŀ���� ��
				for (int n = -1; n <= 1; n++) { // Ŀ���� ��
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			Out[i*W + j] = (BYTE)SumProduct;
			SumProduct = 0.0; // ���� convolution�� ��ߵǹǷ� 0���� �ʱ�ȭ
		}
	}
}
// -1, 0, 1�� ���ι������� �����ִ� mask
// ���ι������� ��, X�������� ���� �� ȭ�Ұ��� ���ϴ� ������ ã�ڴ�!  
void Prewitt_X_Conv(BYTE *Img, BYTE *Out, int W, int H) { // Prewitt Mask X

	double Kernel[3][3] = {
		-1.0, 0.0, 1.0,
		-1.0, 0.0, 1.0,
		-1.0, 0.0, 1.0
	};
	double SumProduct = 0.0;
	for (int i = 1; i < H - 1; i++) { // ������ ��(Y��ǥ)
		for (int j = 1; j < W - 1; j++) { // ������ ��(X��ǥ)
			for (int m = -1; m <= 1; m++) { // Ŀ���� ��
				for (int n = -1; n <= 1; n++) { // Ŀ���� ��
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			// Convolution�� ������ �� ������ �������� ��� weight���� �ּ� -255���� ���� �� �ִ�. 
			// ������ �ȼ��� ������ 0 ~ 255�̱� ������ ���񰪰� ���� ������ �ʿ�.
			// �׷��� Prewitt mask�� ���ؼ� ������ ���ϴ� ��� ������  0���� 255*3 = 765���� ���� ���� �� ����
			// 0 ~ 765 ====> 0 ~ 255 �̷��� �ٲ������. ���� 3���� �����ش�
			Out[i*W + j] = abs((long)SumProduct) / 3; // ���� ���ϴ� �Լ��� �Ķ���͸� ������ �޵��� �������Ƿ� long���� casting. 
			SumProduct = 0.0; 
		}
	}
}

void Prewitt_Y_Conv(BYTE *Img, BYTE *Out, int W, int H) { // Prewitt Mask Y

	double Kernel[3][3] = {
		-1.0, -1.0, -1.0,
		0.0, 0.0, 0.0,
		1.0, 1.0, 1.0
	};
	double SumProduct = 0.0;
	for (int i = 1; i < H - 1; i++) { // ������ ��(Y��ǥ)
		for (int j = 1; j < W - 1; j++) { // ������ ��(X��ǥ)
			for (int m = -1; m <= 1; m++) { // Ŀ���� ��
				for (int n = -1; n <= 1; n++) { // Ŀ���� ��
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			Out[i*W + j] = abs((long)SumProduct) / 3;
			SumProduct = 0.0;
		}
	}
}

void Sobel_X_Conv(BYTE *Img, BYTE *Out, int W, int H) { 

	double Kernel[3][3] = {
		-1.0, 0.0, 1.0,
		-2.0, 0.0, 2.0,
		-1.0, 0.0, 1.0
	};
	double SumProduct = 0.0;
	for (int i = 1; i < H - 1; i++) { // ������ ��(Y��ǥ)
		for (int j = 1; j < W - 1; j++) { // ������ ��(X��ǥ)
			for (int m = -1; m <= 1; m++) { // Ŀ���� ��
				for (int n = -1; n <= 1; n++) { // Ŀ���� ��
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			// Sobel Mask�� ���ؼ� ������ ���ϴ� ��� ������  0���� 255*4 = 1020���� ���� ���� �� ����
			// 0 ~ 1020 == == > 0 ~255. ���� 4�� �����ش�.
			Out[i*W + j] = abs((long)SumProduct) / 4; 
			SumProduct = 0.0;
		}
	}
}

void Sobel_Y_Conv(BYTE *Img, BYTE *Out, int W, int H) { 

	double Kernel[3][3] = {
		-1.0, -2.0, -1.0,
		0.0, 0.0, 0.0,
		1.0, 2.0, 1.0
	};
	double SumProduct = 0.0;
	for (int i = 1; i < H - 1; i++) { // ������ ��(Y��ǥ)
		for (int j = 1; j < W - 1; j++) { // ������ ��(X��ǥ)
			for (int m = -1; m <= 1; m++) { // Ŀ���� ��
				for (int n = -1; n <= 1; n++) { // Ŀ���� ��
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			Out[i*W + j] = abs((long)SumProduct) / 4;
			SumProduct = 0.0;
		}
	}
}

void Laplace_Conv(BYTE *Img, BYTE *Out, int W, int H) {

	double Kernel[3][3] = {
		-1.0, -1.0, -1.0,
		-1.0, 8.0, -1.0,
		-1.0, -1.0, -1.0
	};
	double SumProduct = 0.0;
	for (int i = 1; i < H - 1; i++) { // ������ ��(Y��ǥ)
		for (int j = 1; j < W - 1; j++) { // ������ ��(X��ǥ)
			for (int m = -1; m <= 1; m++) { // Ŀ���� ��
				for (int n = -1; n <= 1; n++) { // Ŀ���� ��
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			// Laplacian Mask�� ���ؼ� ������ ���ϴ� ��� ������  0���� 255*8 = 2040���� ���� ���� �� ����
			// 0 ~ 2040 == == > 0 ~255. ���� 8�� �����ش�.
			Out[i*W + j] = abs((long)SumProduct) / 8;
			SumProduct = 0.0;
		}
	}
}

void Laplace_Conv_DC(BYTE *Img, BYTE *Out, int W, int H) {

	double Kernel[3][3] = {
		-1.0, -1.0, -1.0,
		-1.0, 9.0, -1.0,
		-1.0, -1.0, -1.0
	}; // ���� 1�̱� ������ ���� ������ ��⸦ �����ϸ鼭 ������(+������)�� �������� �����ϰڴٴ� �� 
	double SumProduct = 0.0;
	for (int i = 1; i < H - 1; i++) { // ������ ��(Y��ǥ)
		for (int j = 1; j < W - 1; j++) { // ������ ��(X��ǥ)
			for (int m = -1; m <= 1; m++) { // Ŀ���� ��
				for (int n = -1; n <= 1; n++) { // Ŀ���� ��
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			//Out[i*W + j] = abs((long)SumProduct) / 8;
			// ��� Ŭ����ó���� ���ش�. 
			if (SumProduct > 255.0) Out[i*W + j] = 255;
			else if (SumProduct<0.0) Out[i*W + j] = 0;
			else Out[i*W + j] = (BYTE)SumProduct;
			SumProduct = 0.0;
		}
	}
}