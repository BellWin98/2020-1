#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName);
void Binarization(BYTE *Img, BYTE *Out, int W, int H, BYTE Threshold);
BYTE GonzalezBinThresh(BYTE *Img, int W, int H);
int push(short* stackx, short* stacky, int arr_size, short vx, short vy, int* top);
int pop(short* stackx, short* stacky, short* vx, short* vy, int* top);
void m_BlobColoring(BYTE* CutImage, int height, int width);
void BinaryImageEdgeDetection(BYTE *Bin, BYTE *Out, int W, int H);
void InverseImage(BYTE *Img, BYTE *Out, int W, int H); // pupil ������ coin����� �ٸ��� ������ �������������.

int main() {
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hinfo;
	RGBQUAD hRGB[256];
	FILE *fp;
	fp = fopen("pupil1.bmp", "rb");
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

	int H = hinfo.biHeight, W = hinfo.biWidth; // ���ǻ�

	BYTE threshold = GonzalezBinThresh(Image, W, H);
	// Labelling
	 Binarization(Image, Output, hinfo.biWidth, hinfo.biHeight, threshold);
	 m_BlobColoring(Output, hinfo.biHeight, hinfo.biWidth);

	// Edge����
	/*Binarization(Image, Temp, W, H, threshold); // ��� ����� ���. pupil������ Threshold 50�� ����. 
	// InverseImage(Temp, Temp, W, H); // pupil���� ������ �� ���
	m_BlobColoring(Temp, H, W);
	for (int i = 0; i < ImgSize; i++) {
		// Output[i] = 255; // �Ͼ� ��濡 �����ϰ��� �ϴ� ������Ʈ�� ��踸 ����ϰ� ���� �� 
		Output[i] = Image[i]; // ���� ��踦 ������� ����� ��

	}
	BinaryImageEdgeDetection(Temp, Output, W, H);*/

	SaveBMPFile(hf, hinfo, hRGB, Output, hinfo.biWidth, hinfo.biHeight, "output_bin_edge_pupil.bmp");
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

void InverseImage(BYTE *Img, BYTE *Out, int W, int H) {
	int ImgSize = W*H;
	for (int i = 0; i < ImgSize; i++) {
		Out[i] = 255 - Img[i];
	}
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
		//if (BlobArea[coloring[k]] > 500) CutImage[k] = 0; // Ư�� ������ 500���� ū ������Ʈ ������ ���
		
		// CutImage[k] = (unsigned char)(coloring[k] * grayGap); // ���� �󺧸� ����� Ȯ��, ��� ������Ʈ�� ���� grayGap(10.625)����
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
					// Output[i*W+j] = 0; // �Ͼ� ��濡 �����ϰ��� �ϴ� ������Ʈ�� ��踸 ���������� ����ϰ� ���� �� 
					Out[i*W + j] = 255; // ���� ��踦 ������� ����� �� ��谡 �Ͼ�� �巯���� �� ��

				}
			}
		}
	}
}