#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct {
	int xpos, ypos, x1, x2, y1, y2;
} Point;

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hinfo, RGBQUAD *hRGB, BYTE *Output, int W, int H, char *FileName);
void Binarization(BYTE *Img, BYTE *Out, int W, int H, BYTE Threshold);
void m_BlobColoring(BYTE* CutImage, int height, int width);
int push(short* stackx, short* stacky, int arr_size, short vx, short vy, int* top);
int pop(short* stackx, short* stacky, short* vx, short* vy, int* top);
void BinaryImageEdgeDetection(BYTE *Bin, BYTE *Out, int W, int H);
void InverseImage(BYTE *Img, BYTE *Out, int W, int H);
void SetAxis(BYTE *Temp, Point *point, int W, int H);
void CenterOfGravity(BYTE *Img, Point *center, int W, int H);
void DrawRectOutline(BYTE * Img, int W, int H, int LU_X, int LU_Y, int RD_X, int RD_Y);
void DrawCrossLine(BYTE * Img, int W, int H, int Cx, int Cy);



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
	Point *point;
	point = (Point *)malloc(sizeof(Point));

	Binarization(Image, Temp, W, H, 50);
	InverseImage(Temp, Temp, W, H); 
	m_BlobColoring(Temp, H, W); // �󺧸�
	SetAxis(Temp, point, W, H);
	DrawRectOutline(Image, W, H, point->x1, point->y1, point->x2, point->y2);
	CenterOfGravity(Temp, point, W, H); // ���� �����߽� ã��
	DrawCrossLine(Image, W, H, point->xpos, point->ypos); // ���� �����߽��� �������� ���ڼ� �׸���
	
	SaveBMPFile(hf, hinfo, hRGB, Image, hinfo.biWidth, hinfo.biHeight, "HW_pupil1.bmp");
	free(point);
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

	}

	delete[] coloring;
	delete[] stackx;
	delete[] stacky;
}
// �󺧸� �� ���� ���� ������ ���ؼ��� �̾Ƴ��� �ڵ� ����

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

void BinaryImageEdgeDetection(BYTE *Bin, BYTE *Out, int W, int H) {

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (Bin[i*W + j] == 0) { // ����ȭ�Ҷ��
				if (!(Bin[(i - 1)*W + j] == 0 && Bin[(i + 1)*W + j] == 0 &&
					Bin[i*W + j - 1] == 0 && Bin[i*W + j + 1] == 0)) { // 4���� ȭ�� �� �ϳ��� ������ �ƴ϶��
																	   // Out[i*W+j] = 0; // �Ͼ� ��濡 �����ϰ��� �ϴ� ������Ʈ�� ��踸 ���������� ����ϰ� ���� �� 
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
	printf("sumx: %d, sumy: %d, count: %d\n", center->xpos, center->ypos, count);
	if (count == 0) {
		count = 1;
	}
	center->xpos = (int)center->xpos / count;
	center->ypos = (int)center->ypos / count;
}

void SetAxis(BYTE *Temp, Point *point, int W, int H) {
	bool exitOuterLoop = false;
	// ������ܺ��� ����� ���ο켱���� Ž���ϴٰ�, 0��ȭ�Ҹ� ó�� ������ ���� Y��ǥ
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