#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h> // �����Ҵ� �� �ʿ�!
#include <Windows.h> // ��Ʈ�� ��� ���õ� ����ü���� ���ǵǾ� ����.
#include <math.h>

typedef struct {
	int xpos, ypos, x1, x2, y1, y2;
} Point;

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName);
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
BYTE GonzalezBinThresh(BYTE *Img, int W, int H);
void AverageConv(BYTE *Img, BYTE *Out, int W, int H); // �ڽ� ��Ȱȭ
void GaussAvrConv(BYTE *Img, BYTE *Out, int W, int H); // ����þ� ��Ȱȭ
void Prewitt_X_Conv(BYTE *Img, BYTE *Out, int W, int H);
void Prewitt_Y_Conv(BYTE *Img, BYTE *Out, int W, int H);
void Sobel_X_Conv(BYTE *Img, BYTE *Out, int W, int H); // Sobel�� Prewitt���� �� ÷���� ��谡 ����!
void Sobel_Y_Conv(BYTE *Img, BYTE *Out, int W, int H);
void Laplace_Conv(BYTE *Img, BYTE *Out, int W, int H);
void Laplace_Conv_DC(BYTE *Img, BYTE *Out, int W, int H);
void Swap(BYTE *a, BYTE *b);
BYTE Median(BYTE *arr, int size);
BYTE MaxPooling(BYTE *arr, int size);
BYTE MinPooling(BYTE *arr, int size);
int push(short* stackx, short* stacky, int arr_size, short vx, short vy, int* top);
int pop(short* stackx, short* stacky, short* vx, short* vy, int* top);
void m_BlobColoring(BYTE* CutImage, int height, int width);
void BinaryImageEdgeDetection(BYTE *Bin, BYTE *Out, int W, int H);
void SetAxis(BYTE *Temp, Point *point, int W, int H);
void CenterOfGravity(BYTE *Img, Point *center, int W, int H);
void DrawRectOutline(BYTE * Img, int W, int H, int LU_X, int LU_Y, int RD_X, int RD_Y);
void DrawCrossLine(BYTE * Img, int W, int H, int Cx, int Cy);
void Translation(BYTE *Img, BYTE *Out, int W, int H, int Tx, int Ty);
void VerticalFlip(BYTE *Img, int W, int H);
void HorizontalFlip(BYTE *Img, int W, int H);
void Scaling(BYTE *Img, BYTE *Out, int W, int H, double SF_X, double SF_Y);
void Rotation(BYTE *Img, BYTE *Out, int W, int H, int Angle);

int main() {

	BITMAPFILEHEADER hf; // BMP ������� 14Bytes
	BITMAPINFOHEADER hinfo; // BMP ������� 40Bytes
	RGBQUAD hRGB[256]; // �ȷ�Ʈ ���� (256 * 4Bytes = 1024)
	FILE *fp;
	fp = fopen("lenna.bmp", "rb");
	if (fp == NULL) {  // ����ó��
		printf("File not found!\n");
		return -1; // main�� ��ȯ���� void �̹Ƿ�; ������ ����ǥ��
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp); // ���� fp(���� ������)���� 1�� �о�´�!
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);
	//	������ ũ�⿡ �°� ���� �Ҵ��� �ϰ� ȭ�� ���� ������ ����.
	//	������ ũ�Ⱑ 256*256 �̹Ƿ� 65,536 Byte �о�;���. 
	int ImgSize = hinfo.biWidth * hinfo.biHeight; // biWidth: ������ ���� ������
	//  BYTE�� unsigned char type(1 byte)�̴�. (0~255����)
	//	malloc �Լ��� ���ϰ��� void�������̴�. 
	//	Heap�������� �޸𸮸� 65,536��ŭ �����Ҵ��� �ϰ� �ڱⰡ �Ҵ��� �޸��� �����ּҸ� ��ȯ�Ѵ�. �ٵ� �� �����ּҸ� � Ÿ���� ������ �𸣱⶧���� void������Ÿ������ ��ȯ���ش�.
	int W = hinfo.biWidth, H = hinfo.biHeight; // ������ ���ο� ���� ���� ���� �� �ʱ�ȭ. ���ǻ�
	BYTE * Image = (BYTE *)malloc(ImgSize); // BYTE *�� ���� ����ȯ ����. �׸��� Image�������� ���������� ���� ����.
	BYTE * Output = (BYTE *)malloc(ImgSize); // ����ó���� ����� Output������ ����.
	BYTE *Temp = (BYTE *)malloc(ImgSize); // �ӽù迭
	fread(Image, sizeof(BYTE), ImgSize, fp); // ������ ȭ�������� �о�ð���. 
	fclose(fp); // fp�� lenna.bmp�� ������踦 ������.	

	// 2���� ���� // 
/*	for (int i = 0; i < ImgSize; i++) {
		 Output[i] = Image[i]; // ���� ���� ���
		 Output[i] = 255 - Image[i]; // ������ ���� ȭ�Ұ��� 255���� ����. ȭ�Ұ� �����̵�. ������ ������ �Ǵ� ȿ���� ���.black�� white�� white�� black����.
		 Output[i] = Image[i] + 100; // ���� ��� ���� 100�� �־����� 255���� ū ���ڰ� ������ overflow ���� ��Ÿ��.
	}*/
	// 2���� ���� // 
	
	// 2���� ����: 3���� bmp���� ���� //
/*	// �����������
	SaveBMPFile(hf, hinfo, hRGB, Image, hinfo.biWidth, hinfo.biHeight, "output1.bmp");

	// ������� +50 �������
	for (int i = 0; i < ImgSize; i++) {
		Output[i] = Image[i] + 50;
	}

	// �����������
	for (int i = 0; i < ImgSize; i++) {
		Output[i] = 255 - Image[i];
	}*/
	// 2���� ����: 3���� bmp���� ���� // 

	// 3���� ���� // 
/*	OriginalImage(Image, Output, hinfo.biWidth, hinfo.biHeight);
	InverseImage(Image, Output, hinfo.biWidth, hinfo.biHeight);
	BrightnessAdj(Image, Output, hinfo.biWidth, hinfo.biHeight, 70);
	ContrastAdj(Image, Output, hinfo.biWidth, hinfo.biHeight, 1.5); 

	int Histo[256] = { 0 }; // 0���� �ʱ�ȭ
	int AHisto[256] = { 0 }; // ���� ������׷�(Accumulated Histogram)

	ObtainHistogram(Image, Histo, hinfo.biWidth, hinfo.biHeight);
	ObtainAHistogram(Histo, AHisto);
	HistogramEqualization(Image, Output, AHisto, hinfo.biWidth, hinfo.biHeight);
	HistogramStretching(Image, Output, Histo, hinfo.biWidth, hinfo.biHeight);
	printHistogram(Histo);
	printAHistogram(AHisto);

//  �Ӱ�ġ�� �ʹ� ���ų� ���� ������ �̻��� ����� ����. 80�� ����.
//  �ְ����� �Ǵ�, �������� �Ǵ� �Ǵ� �ڵ� �Ӱ�ġ ��������� ����.
	Binarization(Image, Output, hinfo.biWidth, hinfo.biHeight, 80);*/
	// 3���� ���� // 

	// 3���� ����: Gonzalez �ڵ�ȭ �Ӱ�ġ ���� //
/*	BYTE threshold = GonzalezBinThresh(Image, hinfo.biWidth, hinfo.biHeight);
	Binarization(Image, Output, hinfo.biWidth, hinfo.biHeight, threshold);*/
	// 3���� ����: Gonzalez �ڵ�ȭ �Ӱ�ġ ���� //

	// 4���� ���� //
/*	AverageConv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	GaussAvrConv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	Prewitt_X_Conv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	Prewitt_Y_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	Sobel_X_Conv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	Sobel_Y_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	Laplace_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);

//	������(������)������ ���̱� ���� ��Ȱȭ�� ��ħ! ������� �� �����
	GaussAvrConv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	Laplace_Conv_DC(Temp, Output, hinfo.biWidth, hinfo.biHeight);
//	prewitt �Ǵ� Sobel�� X�� Y�� ��ġ�� ���� 
	for (int i = 0; i < ImgSize; i++) {
		if (Temp[i] > Output[i]) {
			Output[i] = Temp[i];
		}
	}
	Binarization(Output, Output, hinfo.biWidth, hinfo.biHeight, 40);*/ // ��谪�� ������� ��谡 ���ϰ� ��Ÿ��.
	// 4���� ���� //

	// 5���� ���� // 
/*	BYTE temp[9];
	int i, j;
	for (i = 1; i < H - 1; i++) { // x��ǥ
		for (j = 1; j < W - 1; j++) { // y��ǥ
			temp[0] = Image[(i - 1)*W + j - 1];
			temp[1] = Image[(i - 1)*W + j];
			temp[2] = Image[(i - 1)*W + j + 1];
			temp[3] = Image[i * W + j - 1];
			temp[4] = Image[i * W + j]; // 3 by 3���� center�� �ش�Ǵ� �κ�
			temp[5] = Image[i * W + j + 1];
			temp[6] = Image[(i + 1)*W + j - 1];
			temp[7] = Image[(i + 1)*W + j];
			temp[8] = Image[(i + 1)*W + j + 1];
			Output[i*W + j] = Median(temp, 9); // temp�迭�� �����ؼ� �߰��� �ش�Ǵ� ���� ��ȯ, impulse noise(Ư��ȭ�Ұ�)�� ���� �� ���
			Output[i*W + j] = MaxPooling(temp, 9); // pepper noise�� �����ϰ� salt noise�� ����
			Output[i*W + j] = MinPooling(temp, 9); // salt noise�� �����ϰ� pepper noise�� ����	
		}
	}
	AverageConv(Image, Output, hinfo.biWidth, hinfo.biHeight);*/ // noise�� Ư�� ȭ�Ұ��� ������ ���� �� Average Mask���
	// 5���� ���� //

	// 5���� ����: Median Filter ����� ���� �� //
/*	int Length = 3;  // Mask�� �� ���� ����
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
					temp[(m + Margin) * Length + (n + Margin)] = Image[(i + m)*W + j + n];
				}
			}
			// �Է��� ����� �ش��ϴ� temp�迭�� �����ؼ� �߰��� �ش�Ǵ� ���� ��ȯ��.
			// �� �� �߰����� Center Position�� ��ġ��Ŵ. 
			Output[i * W + j] = Median(temp, WSize);
		}
	}
	free(temp);*/ // �ӽ÷� ������ �迭�� �޸𸮸� ������Ŵ.
	// 5���� ����: Median Filter ����� ���� �� //

	// 6���� ���� //
	// Edge����
/*	Binarization(Image, Temp, W, H, 50); // ��� ����� ���. pupil������ Threshold 50�� ����.
	InverseImage(Temp, Temp, W, H); // pupil���� ������ �� ���
	m_BlobColoring(Temp, H, W);
	for (int i = 0; i < ImgSize; i++) {
		Output[i] = 255; // �Ͼ� ��濡 �����ϰ��� �ϴ� ������Ʈ�� ��踸 ����ϰ� ���� ��
		Output[i] = Image[i]; // ���� ��踦 ������� ����� ��
	}
	BinaryImageEdgeDetection(Temp, Output, W, H);*/
	// 6���� ���� //

	// 6���� ����: �������� �����簢�� �� �����߽� ����ϴ� ũ�ν����� �׸��� //
/*	Point *point;
	point = (Point *)malloc(sizeof(Point));

	Binarization(Image, Temp, W, H, 50);
	InverseImage(Temp, Temp, W, H);
	m_BlobColoring(Temp, H, W); // �󺧸�
	SetAxis(Temp, point, W, H);
	DrawRectOutline(Image, W, H, point->x1, point->y1, point->x2, point->y2);
	CenterOfGravity(Temp, point, W, H); // ���� �����߽� ã��
	DrawCrossLine(Image, W, H, point->xpos, point->ypos);*/ // ���� �����߽��� �������� ���ڼ� �׸���
	// 6���� ����: �������� �����簢�� �� �����߽� ����ϴ� ũ�ν����� �׸��� //

	// 7���� ���� // 
	// ���� ��ȯ �� ������ ������ ����� �� ȸ������ ���̴� ������ �����Ⱚ�� 125 ������ �Ǿ� �ֱ⶧��
/*	VerticalFlip(Image, W, H);
	HorizontalFlip(Image, W, H);
	Translation(Image, Output, W, H, 100, 40);
	Scaling(Image, Output, W, H, 0.7, 0.7); // Uniform Scaling (x,y���� ��)
	Rotation(Image, Output, W, H, 60);*/ // ������ �߽����� ȸ��
	// 7���� ���� //

	SaveBMPFile(hf, hinfo, hRGB, Output, hinfo.biWidth, hinfo.biHeight, "output.bmp");
//	SaveBMPFile(hf, hinfo, hRGB, Image, hinfo.biWidth, hinfo.biHeight, "output.bmp"); // ����ϴ� ������ Output�� �ƴ϶� Image�� �� ���
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
	t /= ImgSize; // �ʱⰪ

	// G1, G2���� 
	while (1) {
		low_sum = 0.0;
		high_sum = 0.0;
		low_cnt = 0.0;
		high_cnt = 0.0;
		low_avg = 0.0;
		high_avg = 0.0;

		for (i = 0; i < W; i++) {
			for (j = 0; j < H; j++) {
				if (Img[i*H + j] <= t) {
					low_sum += Img[i*H + j];
					low_cnt++;
				}
				else {
					high_sum += Img[i*H + j];
					high_cnt++;
				}
			}
		}
		// �� ������ ��� ���
		low_avg = low_sum / low_cnt;
		high_avg = high_sum / high_cnt;

		// t���� ������ ���� ��� ����, ������ �ݺ�
		if (t == (((low_avg + high_avg) / 2.0) + 1.0)) {
			break;
		}
		else {
			t = ((low_avg + high_avg) / 2.0) + 1.0;
		}

	}
	return (BYTE)t;
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
//					�迭�� �ε����� ������ �� �� �����Ƿ� +1, �׸��� Ŀ�� �ε����� ���� ���󿡼��� ��� �� ��ġ�� m,n�� �����ǹǷ� ���� +m, +n
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
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
	//  kernel�� weight�� �� 16�� �������� �� �ȼ��� weight ����
	//  �� �ȼ��� ������ ���� 1�̾�� �ϹǷ� 16���� �������ش�. 
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
//			Convolution�� ������ �� ������ �������� ��� weight���� �ּ� -255���� ���� �� �ִ�. 
//			������ �ȼ��� ������ 0 ~ 255�̱� ������ ���񰪰� ���� ������ �ʿ�.
//			�׷��� Prewitt mask�� ���ؼ� ������ ���ϴ� ��� ������  0���� 255*3 = 765���� ���� ���� �� ����
//			0 ~ 765 ====> 0 ~ 255 �̷��� �ٲ������. ���� 3���� �����ش�
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
//			Sobel Mask�� ���ؼ� ������ ���ϴ� ��� ������  0���� 255*4 = 1020���� ���� ���� �� ����
//			0 ~ 1020 == == > 0 ~255. ���� 4�� �����ش�.
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
//			Laplacian Mask�� ���ؼ� ������ ���ϴ� ��� ������  0���� 255*8 = 2040���� ���� ���� �� ����
//			0 ~ 2040 == == > 0 ~255. ���� 8�� �����ش�.
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
	return arr[S / 2];
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
	return arr[S - 1];
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

int push(short* stackx, short* stacky, int arr_size, short vx, short vy, int* top) {

	if (*top >= arr_size) return(-1);
	(*top)++;
	stackx[*top] = vx;
	stacky[*top] = vy;
	return(1);
}

int pop(short* stackx, short* stacky, short* vx, short* vy, int* top) {

	if (*top == 0) return(-1);
	*vx = stackx[*top];
	*vy = stacky[*top];
	(*top)--;
	return(1);
}


// GlassFire �˰����� �̿��� �󺧸� �Լ�
void m_BlobColoring(BYTE* CutImage, int height, int width) {

	int i, j, m, n, top, area, Out_Area, index, BlobArea[1000];
	long k;
	short curColor = 0, r, c;
	//	BYTE** CutImage2;
	Out_Area = 1;

	// �������� ����� �޸� �Ҵ�
	short* stackx = new short[height * width];
	short* stacky = new short[height * width];
	short* coloring = new short[height * width]; // 1���� 24�� �ش��ϴ� ������Ʈ�� �ε��� ������ �����

	int arr_size = height * width;

	// �󺧸��� �ȼ��� �����ϱ� ���� �޸� �Ҵ�

	for (k = 0; k < height * width; k++) coloring[k] = 0;  // �޸� �ʱ�ȭ

	for (i = 0; i < height; i++)
	{
		index = i * width;
		for (j = 0; j < width; j++)
		{
			// �̹� �湮�� ���̰ų� �ȼ����� 255�� �ƴ϶�� ó�� ����
			if (coloring[index + j] != 0 || CutImage[index + j] != 255) continue;
			r = i; c = j; top = 0; area = 1;
			curColor++;

			while (1)
			{
			GRASSFIRE:
				for (m = r - 1; m <= r + 1; m++)
				{
					index = m * width;
					for (n = c - 1; n <= c + 1; n++)
					{
						//���� �ȼ��� �����踦 ����� ó�� ����
						if (m < 0 || m >= height || n < 0 || n >= width) continue;

						if ((int)CutImage[index + n] == 255 && coloring[index + n] == 0)
						{
							coloring[index + n] = curColor; // ���� �󺧷� ��ũ
							if (push(stackx, stacky, arr_size, (short)m, (short)n, &top) == -1) continue;
							r = m; c = n; area++;
							goto GRASSFIRE;
						}
					}
				}
				if (pop(stackx, stacky, &r, &c, &top) == -1) break;
			}
			if (curColor < 1000) BlobArea[curColor] = area;
		}
	}

	// �� ������Ʈ�� �󺧸��� �ϱ����� �󸶸�ŭ�� Gap���� ���� ������ų���� 
	float grayGap = 255.0f / (float)curColor; // curColor: �� Component(���)�� ����

											  // ���� ������ ���� ������ ã�Ƴ��� ���� 
	for (i = 1; i <= curColor; i++)
	{
		// BlobArea: Component 1������ 24�������� ��������
		// Out_Area: ���� ū ������ �����ִ� ������Ʈ�� �ε������� ����.
		if (BlobArea[i] >= BlobArea[Out_Area]) Out_Area = i;
	}
	// CutImage �迭 Ŭ����~
	// �ڽ��� �����ϰ� ���� ������Ʈ�� ������� ĥ�ϱ� ���� ������ ����� ������� ����
	for (k = 0; k < width * height; k++) CutImage[k] = 255;

	// coloring�� ����� �󺧸� ����� (Out_Area�� �����) ������ ���� ū �͸� CutImage�� ����
	for (k = 0; k < width * height; k++)
	{
		// coloring���� 1���� 24�� �ش��ϴ� ������Ʈ�� �ε��� ������ �����
		if (coloring[k] == Out_Area) CutImage[k] = 0;  // ���� ������ ū ������Ʈ�� �ش��ϴ� �͸� ǥ��(Size Filtering)
//		if (BlobArea[coloring[k]] > 500) CutImage[k] = 0; // Ư�� ������ 500���� ū ������Ʈ ������ ���
//		CutImage[k] = (unsigned char)(coloring[k] * grayGap); // ���� �󺧸� ����� Ȯ��, ��� ������Ʈ�� ���� grayGap(10.625)����
	}

	delete[] coloring;
	delete[] stackx;
	delete[] stacky;
}
// �󺧸� �� ���� ���� ������ ���ؼ��� �̾Ƴ��� �ڵ� ����

void BinaryImageEdgeDetection(BYTE *Bin, BYTE *Out, int W, int H) {

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (Bin[i*W + j] == 0) { // ����ȭ�Ҷ��
				if (!(Bin[(i - 1)*W + j] == 0 && Bin[(i + 1)*W + j] == 0 &&
					Bin[i*W + j - 1] == 0 && Bin[i*W + j + 1] == 0)) { // 4���� ȭ�� �� �ϳ��� ������ �ƴ϶��
//					Output[i*W+j] = 0; // �Ͼ� ��濡 �����ϰ��� �ϴ� ������Ʈ�� ��踸 ���������� ����ϰ� ���� �� 
					Out[i*W + j] = 255; // ���� ��踦 ������� ����� �� ��谡 �Ͼ�� �巯���� �� ��

				}
			}
		}
	}
}

void CenterOfGravity(BYTE *Img, Point *center, int W, int H) {
	center->xpos = 0;
	center->ypos = 0;
	int count = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (Img[i*W + j] == 0) {
				count++;
				center->xpos += j;
				center->ypos += i;
			}
		}
	}
	center->xpos = (int)center->xpos / count;
	center->ypos = (int)center->ypos / count;
}

void SetAxis(BYTE *Temp, Point *point, int W, int H) {
	bool exitOuterLoop = false;
	// ������ܺ��� ����� ���ο켱���� Ž���ϴٰ�, 0��ȭ�Ҹ� ó�� ������ ���� Y��ǥ: y1
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (Temp[i*W + j] == 0) {
				point->y1 = i;
				printf("y1: %d\n", point->y1);
				exitOuterLoop = true;
				break;
			}
		}
		if (exitOuterLoop == true) {
			exitOuterLoop = false;
			break;
		}
	}

	// ������ܺ��� �Ϲ��� ���ο켱���� Ž���ϴٰ�, 0��ȭ�Ҹ� ó�� ������ ���� X��ǥ�� ����: x1
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			if (Temp[j*W + i] == 0) {
				point->x1 = i;
				printf("x1: %d\n", point->x1);
				exitOuterLoop = true;
				break;
			}
		}
		if (exitOuterLoop == true) {
			exitOuterLoop = false;
			break;
		}
	}
	// �����ϴܺ��� �¹��� ���ο켱���� Ž���ϴٰ�, 0��ȭ�Ҹ� ó�� ������ ���� Y��ǥ�� ����: y2
	for (int i = H - 1; i >= 0; i--) {
		for (int j = W - 1; j >= 0; j--) {
			if (Temp[i*W + j] == 0) {
				point->y2 = i;
				printf("y2: %d\n", point->y2);
				exitOuterLoop = true;
				break;
			}
		}
		if (exitOuterLoop == true) {
			exitOuterLoop = false;
			break;
		}
	}
	// �����ϴܺ��� ����� ���ο켱����  Ž���ϴٰ�, 0��ȭ�Ҹ� ó�� ������ ���� X��ǥ�� ����: x2
	for (int i = W - 1; i >= 0; i--) {
		for (int j = H - 1; j >= 0; j--) {
			if (Temp[j*W + i] == 0) {
				point->x2 = i;
				printf("x2: %d\n", point->x2);
				exitOuterLoop = true;
				break;
			}
		}
		if (exitOuterLoop == true) {
			exitOuterLoop = false;
			break;
		}
	}
}
// Img: �簢���� �׸� �̹����迭, W: ���� ���λ�����, H: ���� ���λ�����.
// LU_X: �簢���� ������� X��ǥ, LU_Y: �簢���� ������� Y��ǥ.
// RD_X: �簢���� �����ϴ� X��ǥ, RD_Y: �簢���� �����ϴ� Y��ǥ.
void DrawRectOutline(BYTE * Img, int W, int H, int LU_X, int LU_Y, int RD_X, int RD_Y) {

	for (int i = LU_Y; i <= RD_Y; i++) {
		Img[i*W + LU_X] = 255;
	}

	for (int j = LU_X; j <= RD_X; j++) {
		Img[LU_Y * W + j] = 255;
	}

	for (int m = LU_Y; m <= RD_Y; m++) {
		Img[m*W + RD_X] = 255;
	}

	for (int n = LU_X; n <= RD_X; n++) {
		Img[RD_Y*W + n] = 255;
	}
}

// Img: ����/���� ������ �׸� �̹����迭, W: ���� ���λ�����, H: ���� ���λ�����
// Cx: ����/���� ������ �����Ǵ� ������ X��ǥ
// Cy: ����/���� ������ �����Ǵ� ������ Y��ǥ
void DrawCrossLine(BYTE * Img, int W, int H, int Cx, int Cy) {
	for (int i = 0; i < H; i++) {
		Img[i*W + Cx] = 255;
	}

	for (int j = 0; j < W; j++) {
		Img[Cy * W + j] = 255;
	}
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
			Swap(&Img[i*W + j], &Img[(H - 1 - i)*W + j]); // ������ ��������ܰ� �������ϴ��� �ȼ��� �¹ٲ�.
		}
	}
}

void HorizontalFlip(BYTE *Img, int W, int H) {

	// W/2�� �� ����: W�� ������ ���λ����� �ε�
	// ���ݸ�ŭ�� for���� ���鼭 �� ���� �ٰ� �� ������ ���� �ٲٴ� ������ ��ħ.
	for (int i = 0; i < W / 2; i++) { // i�� x��ǥ
		for (int j = 0; j < H; j++) { // j�� y��ǥ
			Swap(&Img[j*W + i], &Img[j*W + (W - 1 - i)]); // ������ ��������ܰ� �������ϴ��� �ȼ��� �¹ٲ�.
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