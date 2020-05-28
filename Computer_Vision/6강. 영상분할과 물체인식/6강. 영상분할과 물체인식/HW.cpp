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
	BYTE *Temp = (BYTE *)malloc(ImgSize); // 임시배열
	BYTE *Output = (BYTE *)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);

	int H = hinfo.biHeight, W = hinfo.biWidth; // 편의상
	Point *point;
	point = (Point *)malloc(sizeof(Point));

	Binarization(Image, Temp, W, H, 50);
	InverseImage(Temp, Temp, W, H); 
	m_BlobColoring(Temp, H, W); // 라벨링
	SetAxis(Temp, point, W, H);
	DrawRectOutline(Image, W, H, point->x1, point->y1, point->x2, point->y2);
	CenterOfGravity(Temp, point, W, H); // 동공 무게중심 찾기
	DrawCrossLine(Image, W, H, point->xpos, point->ypos); // 동공 무게중심을 기준으로 십자선 그리기
	
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

	// 스택으로 사용할 메모리 할당
	short* stackx = new short[height * width];
	short* stacky = new short[height * width];
	short* coloring = new short[height * width]; // 1부터 24에 해당하는 컴포넌트의 인덱스 정보가 저장됨

	int arr_size = height * width;

	// 라벨링된 픽셀을 저장하기 위해 메모리 할당

	for (k = 0; k < height * width; k++) coloring[k] = 0;  // 메모리 초기화

	for (i = 0; i < height; i++)
	{
		index = i * width;
		for (j = 0; j < width; j++)
		{
			// 이미 방문한 점이거나 픽셀값이 255가 아니라면 처리 안함
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
						//관심 픽셀이 영상경계를 벗어나면 처리 안함
						if (m < 0 || m >= height || n < 0 || n >= width) continue;

						if ((int)CutImage[index + n] == 255 && coloring[index + n] == 0)
						{
							coloring[index + n] = curColor; // 현재 라벨로 마크
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

	// 각 컴포넌트에 라벨링을 하기위해 얼마만큼의 Gap으로 값을 증가시킬건지 
	float grayGap = 255.0f / (float)curColor; // curColor: 총 Component(덩어리)의 개수

											  // 가장 면적이 넓은 영역을 찾아내기 위함 
	for (i = 1; i <= curColor; i++)
	{
		// BlobArea: Component 1번부터 24번까지의 면적정보
		// Out_Area: 가장 큰 면적을 갖고있는 컴포넌트의 인덱스값을 저장.
		if (BlobArea[i] >= BlobArea[Out_Area]) Out_Area = i;
	}
	// CutImage 배열 클리어~
	// 자신이 검출하고 싶은 컴포넌트만 흑색으로 칠하기 위해 나머지 배경은 흰색으로 도배
	for (k = 0; k < width * height; k++) CutImage[k] = 255;

	// coloring에 저장된 라벨링 결과중 (Out_Area에 저장된) 영역이 가장 큰 것만 CutImage에 저장
	for (k = 0; k < width * height; k++)
	{
		// coloring에는 1부터 24에 해당하는 컴포넌트의 인덱스 정보가 저장됨
		if (coloring[k] == Out_Area) CutImage[k] = 0;  // 가장 면적이 큰 컴포넌트에 해당하는 것만 표현(Size Filtering)

	}

	delete[] coloring;
	delete[] stackx;
	delete[] stacky;
}
// 라벨링 후 가장 넓은 영역에 대해서만 뽑아내는 코드 포함

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
			if (Bin[i*W + j] == 0) { // 전경화소라면
				if (!(Bin[(i - 1)*W + j] == 0 && Bin[(i + 1)*W + j] == 0 &&
					Bin[i*W + j - 1] == 0 && Bin[i*W + j + 1] == 0)) { // 4방향 화소 중 하나라도 전경이 아니라면
																	   // Out[i*W+j] = 0; // 하얀 배경에 검출하고자 하는 컴포넌트의 경계만 검은색으로 출력하고 싶을 때 
					Out[i*W + j] = 255; // 영상에 경계를 덮어씌워서 출력할 때 경계가 하얗게 드러나게 할 때

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
	// 좌측상단부터 우방향 가로우선으로 탐색하다가, 0인화소를 처음 만났을 때의 Y좌표
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

	// 좌측상단부터 하방향 세로우선으로 탐색하다가, 0인화소를 처음 만났을 때의 X좌표를 저장: x1
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
// Img: 사각형을 그릴 이미지배열, W: 영상 가로사이즈, H: 영상 세로사이즈.
// LU_X: 사각형의 좌측상단 X좌표, LU_Y: 사각형의 좌측상단 Y좌표.
// RD_X: 사각형의 우측하단 X좌표, RD_Y: 사각형의 우측하단 Y좌표.
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

// Img: 가로/세로 라인을 그릴 이미지배열, W: 영상 가로사이즈, H: 영상 세로사이즈
// Cx: 가로/세로 라인이 교차되는 지점의 X좌표
// Cy: 가로/세로 라인이 교차되는 지점의 Y좌표
void DrawCrossLine(BYTE * Img, int W, int H, int Cx, int Cy) {
	for (int i = 0; i < H; i++) {
		Img[i*W + Cx] = 255;
	}
		
	for (int j = 0; j < W; j++) {
		Img[Cy * W + j] = 255;
	}
}