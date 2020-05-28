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
void InverseImage(BYTE *Img, BYTE *Out, int W, int H); // pupil 영상은 coin영상과 다르게 영상을 반전시켜줘야함.

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

	BYTE threshold = GonzalezBinThresh(Image, W, H);
	// Labelling
	 Binarization(Image, Output, hinfo.biWidth, hinfo.biHeight, threshold);
	 m_BlobColoring(Output, hinfo.biHeight, hinfo.biWidth);

	// Edge검출
	/*Binarization(Image, Temp, W, H, threshold); // 경계 검출시 사용. pupil영상은 Threshold 50이 적당. 
	// InverseImage(Temp, Temp, W, H); // pupil영상 경계검출 시 사용
	m_BlobColoring(Temp, H, W);
	for (int i = 0; i < ImgSize; i++) {
		// Output[i] = 255; // 하얀 배경에 검출하고자 하는 컴포넌트의 경계만 출력하고 싶을 때 
		Output[i] = Image[i]; // 영상에 경계를 덮어씌워서 출력할 때

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
	t /= ImgSize; // 초기값

				  // G1, G2영역 
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
		// 각 영역의 평균 계산
		low_avg = low_sum / low_cnt;
		high_avg = high_sum / high_cnt;

		// t값이 변경이 없는 경우 종료, 있으면 반복
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


// GlassFire 알고리즘을 이용한 라벨링 함수
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
		//if (BlobArea[coloring[k]] > 500) CutImage[k] = 0; // 특정 면적이 500보다 큰 컴포넌트 영역만 출력
		
		// CutImage[k] = (unsigned char)(coloring[k] * grayGap); // 원래 라벨링 결과만 확인, 모든 컴포넌트에 대해 grayGap(10.625)적용
	}

	delete[] coloring;
	delete[] stackx;
	delete[] stacky;
}
// 라벨링 후 가장 넓은 영역에 대해서만 뽑아내는 코드 포함

void BinaryImageEdgeDetection(BYTE *Bin, BYTE *Out, int W, int H) {

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (Bin[i*W + j] == 0) { // 전경화소라면
				if (!(Bin[(i - 1)*W + j] == 0 && Bin[(i + 1)*W + j] == 0 &&
					Bin[i*W + j - 1] == 0 && Bin[i*W + j + 1] == 0)) { // 4방향 화소 중 하나라도 전경이 아니라면
					// Output[i*W+j] = 0; // 하얀 배경에 검출하고자 하는 컴포넌트의 경계만 검은색으로 출력하고 싶을 때 
					Out[i*W + j] = 255; // 영상에 경계를 덮어씌워서 출력할 때 경계가 하얗게 드러나게 할 때

				}
			}
		}
	}
}