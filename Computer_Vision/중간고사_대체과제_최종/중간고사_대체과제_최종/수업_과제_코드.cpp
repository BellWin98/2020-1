#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h> // 동적할당 시 필요!
#include <Windows.h> // 비트맵 헤더 관련된 구조체들이 정의되어 있음.
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
void AverageConv(BYTE *Img, BYTE *Out, int W, int H); // 박스 평활화
void GaussAvrConv(BYTE *Img, BYTE *Out, int W, int H); // 가우시안 평활화
void Prewitt_X_Conv(BYTE *Img, BYTE *Out, int W, int H);
void Prewitt_Y_Conv(BYTE *Img, BYTE *Out, int W, int H);
void Sobel_X_Conv(BYTE *Img, BYTE *Out, int W, int H); // Sobel이 Prewitt보다 더 첨예한 경계가 나옴!
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

	BITMAPFILEHEADER hf; // BMP 파일헤더 14Bytes
	BITMAPINFOHEADER hinfo; // BMP 영상헤더 40Bytes
	RGBQUAD hRGB[256]; // 팔레트 정보 (256 * 4Bytes = 1024)
	FILE *fp;
	fp = fopen("lenna.bmp", "rb");
	if (fp == NULL) {  // 예외처리
		printf("File not found!\n");
		return -1; // main의 반환값이 void 이므로; 비정상 종료표시
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp); // 현재 fp(파일 포인터)에서 1번 읽어온다!
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);
	//	영상의 크기에 맞게 동적 할당을 하고 화소 개수 정보를 넣음.
	//	영상의 크기가 256*256 이므로 65,536 Byte 읽어와야함. 
	int ImgSize = hinfo.biWidth * hinfo.biHeight; // biWidth: 영상의 가로 사이즈
	//  BYTE는 unsigned char type(1 byte)이다. (0~255까지)
	//	malloc 함수의 리턴값이 void포인터이다. 
	//	Heap영역에서 메모리를 65,536만큼 동적할당을 하고 자기가 할당한 메모리의 시작주소를 반환한다. 근데 그 시작주소를 어떤 타입이 받을지 모르기때문에 void포인터타입으로 반환해준다.
	int W = hinfo.biWidth, H = hinfo.biHeight; // 영상의 가로와 세로 변수 선언 및 초기화. 편의상
	BYTE * Image = (BYTE *)malloc(ImgSize); // BYTE *로 강제 형변환 해줌. 그리고 Image변수에는 원본영상을 담을 것임.
	BYTE * Output = (BYTE *)malloc(ImgSize); // 영상처리의 결과는 Output변수에 담음.
	BYTE *Temp = (BYTE *)malloc(ImgSize); // 임시배열
	fread(Image, sizeof(BYTE), ImgSize, fp); // 영상의 화소정보를 읽어올것임. 
	fclose(fp); // fp와 lenna.bmp의 연결관계를 끊어줌.	

	// 2주차 수업 // 
/*	for (int i = 0; i < ImgSize; i++) {
		 Output[i] = Image[i]; // 원본 영상 출력
		 Output[i] = 255 - Image[i]; // 영상의 원래 화소값을 255에서 빼줌. 화소가 반전이됨. 영상이 반전이 되는 효과를 출력.black은 white로 white는 black으로.
		 Output[i] = Image[i] + 100; // 영상 밝기 조절 100을 넣었을때 255보다 큰 숫자가 나오면 overflow 현상 나타남.
	}*/
	// 2주차 수업 // 
	
	// 2주차 과제: 3개의 bmp파일 생성 //
/*	// 원본영상출력
	SaveBMPFile(hf, hinfo, hRGB, Image, hinfo.biWidth, hinfo.biHeight, "output1.bmp");

	// 원본밝기 +50 영상출력
	for (int i = 0; i < ImgSize; i++) {
		Output[i] = Image[i] + 50;
	}

	// 반전영상출력
	for (int i = 0; i < ImgSize; i++) {
		Output[i] = 255 - Image[i];
	}*/
	// 2주차 과제: 3개의 bmp파일 생성 // 

	// 3주차 수업 // 
/*	OriginalImage(Image, Output, hinfo.biWidth, hinfo.biHeight);
	InverseImage(Image, Output, hinfo.biWidth, hinfo.biHeight);
	BrightnessAdj(Image, Output, hinfo.biWidth, hinfo.biHeight, 70);
	ContrastAdj(Image, Output, hinfo.biWidth, hinfo.biHeight, 1.5); 

	int Histo[256] = { 0 }; // 0으로 초기화
	int AHisto[256] = { 0 }; // 누적 히스토그램(Accumulated Histogram)

	ObtainHistogram(Image, Histo, hinfo.biWidth, hinfo.biHeight);
	ObtainAHistogram(Histo, AHisto);
	HistogramEqualization(Image, Output, AHisto, hinfo.biWidth, hinfo.biHeight);
	HistogramStretching(Image, Output, Histo, hinfo.biWidth, hinfo.biHeight);
	printHistogram(Histo);
	printAHistogram(AHisto);

//  임계치를 너무 높거나 낮게 잡으면 이상한 결과가 나옴. 80이 적당.
//  주관적인 판단, 경험적인 판단 또는 자동 임계치 결정방법이 있음.
	Binarization(Image, Output, hinfo.biWidth, hinfo.biHeight, 80);*/
	// 3주차 수업 // 

	// 3주차 과제: Gonzalez 자동화 임계치 결정 //
/*	BYTE threshold = GonzalezBinThresh(Image, hinfo.biWidth, hinfo.biHeight);
	Binarization(Image, Output, hinfo.biWidth, hinfo.biHeight, threshold);*/
	// 3주차 과제: Gonzalez 자동화 임계치 결정 //

	// 4주차 수업 //
/*	AverageConv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	GaussAvrConv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	Prewitt_X_Conv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	Prewitt_Y_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	Sobel_X_Conv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	Sobel_Y_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	Laplace_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);

//	고주파(노이즈)성분을 죽이기 위해 평활화를 거침! 저역통과 후 고역통과
	GaussAvrConv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	Laplace_Conv_DC(Temp, Output, hinfo.biWidth, hinfo.biHeight);
//	prewitt 또는 Sobel의 X와 Y를 합치는 과정 
	for (int i = 0; i < ImgSize; i++) {
		if (Temp[i] > Output[i]) {
			Output[i] = Temp[i];
		}
	}
	Binarization(Output, Output, hinfo.biWidth, hinfo.biHeight, 40);*/ // 경계값을 낮출수록 경계가 진하게 나타남.
	// 4주차 수업 //

	// 5주차 수업 // 
/*	BYTE temp[9];
	int i, j;
	for (i = 1; i < H - 1; i++) { // x좌표
		for (j = 1; j < W - 1; j++) { // y좌표
			temp[0] = Image[(i - 1)*W + j - 1];
			temp[1] = Image[(i - 1)*W + j];
			temp[2] = Image[(i - 1)*W + j + 1];
			temp[3] = Image[i * W + j - 1];
			temp[4] = Image[i * W + j]; // 3 by 3에서 center에 해당되는 부분
			temp[5] = Image[i * W + j + 1];
			temp[6] = Image[(i + 1)*W + j - 1];
			temp[7] = Image[(i + 1)*W + j];
			temp[8] = Image[(i + 1)*W + j + 1];
			Output[i*W + j] = Median(temp, 9); // temp배열을 정렬해서 중간에 해당되는 값을 반환, impulse noise(특정화소값)가 있을 때 사용
			Output[i*W + j] = MaxPooling(temp, 9); // pepper noise만 제거하고 salt noise는 증가
			Output[i*W + j] = MinPooling(temp, 9); // salt noise만 제거하고 pepper noise는 증가	
		}
	}
	AverageConv(Image, Output, hinfo.biWidth, hinfo.biHeight);*/ // noise가 특정 화소값을 가지지 않을 때 Average Mask사용
	// 5주차 수업 //

	// 5주차 과제: Median Filter 사이즈에 따른 비교 //
/*	int Length = 3;  // Mask의 한 변의 길이
	int Margin = Length / 2; // Mask의 영상영역을 이탈하지 않도록 픽셀의 위, 아래, 좌, 우에 마진을 줌. 
	int WSize = Length * Length; // Mask의 크기 설정
	BYTE* temp = (BYTE*)malloc(sizeof(BYTE) * WSize); // 원래 영상의 색상정보를 입력받을 배열 동적 할당
	int i, j, m, n;
	for (i = Margin; i < H - Margin; i++) {
		for (j = Margin; j < W - Margin; j++) {
			for (m = -Margin; m <= Margin; m++) { // m과 n값이 i,j와 연결되어 동작함. 
				for (n = -Margin; n <= Margin; n++) {
					// 중간값을 찾기위한 원 영상의 배열값을 임의의 배열에 저장.
					// 커널 내의 픽셀값을 일렬로 늘여 세움.(1차원 변환) 
					temp[(m + Margin) * Length + (n + Margin)] = Image[(i + m)*W + j + n];
				}
			}
			// 입력한 사이즈에 해당하는 temp배열을 정렬해서 중간에 해당되는 값을 반환함.
			// 그 후 중간값을 Center Position에 위치시킴. 
			Output[i * W + j] = Median(temp, WSize);
		}
	}
	free(temp);*/ // 임시로 생성된 배열의 메모리를 해제시킴.
	// 5주차 과제: Median Filter 사이즈에 따른 비교 //

	// 6주차 수업 //
	// Edge검출
/*	Binarization(Image, Temp, W, H, 50); // 경계 검출시 사용. pupil영상은 Threshold 50이 적당.
	InverseImage(Temp, Temp, W, H); // pupil영상 경계검출 시 사용
	m_BlobColoring(Temp, H, W);
	for (int i = 0; i < ImgSize; i++) {
		Output[i] = 255; // 하얀 배경에 검출하고자 하는 컴포넌트의 경계만 출력하고 싶을 때
		Output[i] = Image[i]; // 영상에 경계를 덮어씌워서 출력할 때
	}
	BinaryImageEdgeDetection(Temp, Output, W, H);*/
	// 6주차 수업 //

	// 6주차 과제: 동공영역 외접사각형 및 무게중심 통과하는 크로스라인 그리기 //
/*	Point *point;
	point = (Point *)malloc(sizeof(Point));

	Binarization(Image, Temp, W, H, 50);
	InverseImage(Temp, Temp, W, H);
	m_BlobColoring(Temp, H, W); // 라벨링
	SetAxis(Temp, point, W, H);
	DrawRectOutline(Image, W, H, point->x1, point->y1, point->x2, point->y2);
	CenterOfGravity(Temp, point, W, H); // 동공 무게중심 찾기
	DrawCrossLine(Image, W, H, point->xpos, point->ypos);*/ // 동공 무게중심을 기준으로 십자선 그리기
	// 6주차 과제: 동공영역 외접사각형 및 무게중심 통과하는 크로스라인 그리기 //

	// 7주차 수업 // 
	// 기하 변환 후 영상의 범위를 벗어났을 때 회색으로 보이는 이유는 쓰레기값이 125 정도로 되어 있기때문
/*	VerticalFlip(Image, W, H);
	HorizontalFlip(Image, W, H);
	Translation(Image, Output, W, H, 100, 40);
	Scaling(Image, Output, W, H, 0.7, 0.7); // Uniform Scaling (x,y같을 때)
	Rotation(Image, Output, W, H, 60);*/ // 원점을 중심으로 회전
	// 7주차 수업 //

	SaveBMPFile(hf, hinfo, hRGB, Output, hinfo.biWidth, hinfo.biHeight, "output.bmp");
//	SaveBMPFile(hf, hinfo, hRGB, Image, hinfo.biWidth, hinfo.biHeight, "output.bmp"); // 출력하는 변수가 Output이 아니라 Image일 때 사용
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

// Contrast(대비): 밝고 어두운 것의 차이가 확연히 벌어짐.
void ContrastAdj(BYTE* Img, BYTE* Out, int W, int H, double Val) {
	int ImgSize = W*H;
	for (int i = 0; i < ImgSize; i++) {
		if (Img[i] * Val > 255) {
			Out[i] = 255;
		}
		else {
			Out[i] = (BYTE)(Img[i] * Val); // 출력값이 BYTE이기 때문에 강제형변환 시켜줌
		}
	}
}

// 히스토그램: 영상에서 그레이영상 기준으로 0~255까지의 화소값이 있는데  
// 그 화소값을 가지는 화소가 영상에 몇개 있는지 카운트 함.
void ObtainHistogram(BYTE* Img, int* Histo, int W, int H) {
	int ImgSize = W*H;
	for (int i = 0; i < ImgSize; i++) {
		Histo[Img[i]]++; // Image[i]: 화소값, 0~255사이의 어떤 값
	}
}

void ObtainAHistogram(int *Histo, int *AHisto) {

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j <= i; j++) {
			AHisto[i] += Histo[j];
		}
	}
}

// 출력값을 복사해서 엑셀의 그래프로 확인해보기
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

// 스트레칭 -> 영상의 가시성이 향상됨!
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
		Out[i] = (BYTE)((Img[i] - Low) / (double)(High - Low)*255.0); // 0에서 1사이로 정규화
	}
}

// Equalization(평활화)는 Stretching 보다 스크래치가 더 잘보임. 
// 단순히 0~255까지 화소가 분포하도록 선형적으로 화소값을 쭉 피는 개념이아니라
// 화소의 누적분포까지 고려해서 화소가 0~255까지 고르게 분포하도록 재배치한 개념
// 히스토그램의 모양이 변하는 경향이 있다. 
// 스트레칭보다 영상의 가시성을 더 향상시킨다. 
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

// 이진화: 영상의 화소값을 0~255에서 어떤 임계값을 기준으로 임계값보다 작으면 0, 크면 255로 
// 256단계로 표현되던 영상의 화소값을 단 두단계로 표현.
// Threshold는 임계치
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

void AverageConv(BYTE *Img, BYTE *Out, int W, int H) {
	double Kernel[3][3] = {
		0.11111, 0.11111, 0.11111,
		0.11111, 0.11111, 0.11111,
		0.11111, 0.11111, 0.11111
	};
	double SumProduct = 0.0;
	// 위아래 margin을 두어야 하므로 커널의 센터인 i와 j는 [1][1]부터 시작
	for (int i = 1; i < H - 1; i++) { // 영상의 행(Y좌표)
		for (int j = 1; j < W - 1; j++) { // 영상의 열(X좌표)
			for (int m = -1; m <= 1; m++) { // 커널의 행, 세로방향으로 봤을 때 m=-1은 센터를 중심으로 나보다 위에있는 것을 표현, m=0은 나 자신, m=1은 나보다 아래에 있는 행
				for (int n = -1; n <= 1; n++) { // 커널의 열, 센터가 속해있는 열을 기준으로 -1은 왼쪽, 0은 나자신, 1은 오른쪽
//					배열의 인덱스는 음수가 될 수 없으므로 +1, 그리고 커널 인덱스에 따라서 영상에서의 행과 열 위치도 m,n과 연동되므로 각각 +m, +n
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			Out[i*W + j] = (BYTE)SumProduct;
			SumProduct = 0.0; // 다음 convolution때 써야되므로 0으로 초기화
		}
	}
}

// 센터에 가장 가중치를 많이 주고 거리가 멀어질수록 가중치를 점차 작게주는 것
// 센터에 가장 가중치를 많이 주겠다는 의미는 원본영상의 정보(성분)를 많이 유지를 하겠다라는 뜻.
// 센터를 기준으로 동서남북은 대각선에 위치한 것들보다 거리가 가까우므로 Weight를 더 크게 줌. 
void GaussAvrConv(BYTE *Img, BYTE *Out, int W, int H) {
	//  kernel의 weight의 합 16을 기준으로 각 픽셀의 weight 산정
	//  각 픽셀의 비율의 합은 1이어야 하므로 16으로 나누어준다. 
	double Kernel[3][3] = {
		0.0625, 0.125, 0.0625,
		0.125, 0.25, 0.125,
		0.0625, 0.125, 0.0625
	};
	double SumProduct = 0.0;
	for (int i = 1; i < H - 1; i++) { // 영상의 행(Y좌표)
		for (int j = 1; j < W - 1; j++) { // 영상의 열(X좌표)
			for (int m = -1; m <= 1; m++) { // 커널의 행
				for (int n = -1; n <= 1; n++) { // 커널의 열
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			Out[i*W + j] = (BYTE)SumProduct;
			SumProduct = 0.0; // 다음 convolution때 써야되므로 0으로 초기화
		}
	}
}
// -1, 0, 1이 세로방향으로 뻗어있는 mask
// 가로방향으로 즉, X방향으로 봤을 때 화소값이 변하는 구간을 찾겠다!  
void Prewitt_X_Conv(BYTE *Img, BYTE *Out, int W, int H) { // Prewitt Mask X

	double Kernel[3][3] = {
		-1.0, 0.0, 1.0,
		-1.0, 0.0, 1.0,
		-1.0, 0.0, 1.0
	};
	double SumProduct = 0.0;
	for (int i = 1; i < H - 1; i++) { // 영상의 행(Y좌표)
		for (int j = 1; j < W - 1; j++) { // 영상의 열(X좌표)
			for (int m = -1; m <= 1; m++) { // 커널의 행
				for (int n = -1; n <= 1; n++) { // 커널의 열
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
//			Convolution을 돌렸을 때 음수가 곱해지는 경우 weight값이 최소 -255까지 찍힐 수 있다. 
//			하지만 픽셀의 범위는 0 ~ 255이기 때문에 절댓값과 같은 조정이 필요.
//			그러나 Prewitt mask를 통해서 절댓값을 취하는 경우 범위는  0부터 255*3 = 765까지 값이 나올 수 있음
//			0 ~ 765 ====> 0 ~ 255 이렇게 바꿔줘야함. 따라서 3으로 나눠준다
			Out[i*W + j] = abs((long)SumProduct) / 3; // 절댓값 구하는 함수는 파라미터를 정수만 받도록 되있으므로 long으로 casting. 
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
	for (int i = 1; i < H - 1; i++) { // 영상의 행(Y좌표)
		for (int j = 1; j < W - 1; j++) { // 영상의 열(X좌표)
			for (int m = -1; m <= 1; m++) { // 커널의 행
				for (int n = -1; n <= 1; n++) { // 커널의 열
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
	for (int i = 1; i < H - 1; i++) { // 영상의 행(Y좌표)
		for (int j = 1; j < W - 1; j++) { // 영상의 열(X좌표)
			for (int m = -1; m <= 1; m++) { // 커널의 행
				for (int n = -1; n <= 1; n++) { // 커널의 열
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
//			Sobel Mask를 통해서 절댓값을 취하는 경우 범위는  0부터 255*4 = 1020까지 값이 나올 수 있음
//			0 ~ 1020 == == > 0 ~255. 따라서 4로 나눠준다.
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
	for (int i = 1; i < H - 1; i++) { // 영상의 행(Y좌표)
		for (int j = 1; j < W - 1; j++) { // 영상의 열(X좌표)
			for (int m = -1; m <= 1; m++) { // 커널의 행
				for (int n = -1; n <= 1; n++) { // 커널의 열
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
	for (int i = 1; i < H - 1; i++) { // 영상의 행(Y좌표)
		for (int j = 1; j < W - 1; j++) { // 영상의 열(X좌표)
			for (int m = -1; m <= 1; m++) { // 커널의 행
				for (int n = -1; n <= 1; n++) { // 커널의 열
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
//			Laplacian Mask를 통해서 절댓값을 취하는 경우 범위는  0부터 255*8 = 2040까지 값이 나올 수 있음
//			0 ~ 2040 == == > 0 ~255. 따라서 8로 나눠준다.
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
	}; // 합이 1이기 때문에 원래 영상의 밝기를 유지하면서 고주파(+노이즈)를 증폭시켜 검출하겠다는 뜻 
	double SumProduct = 0.0;
	for (int i = 1; i < H - 1; i++) { // 영상의 행(Y좌표)
		for (int j = 1; j < W - 1; j++) { // 영상의 열(X좌표)
			for (int m = -1; m <= 1; m++) { // 커널의 행
				for (int n = -1; n <= 1; n++) { // 커널의 열
					SumProduct += Img[(i + m)*W + (j + n)] * Kernel[m + 1][n + 1];
				}
			}
			//Out[i*W + j] = abs((long)SumProduct) / 8;
			// 얘는 클리핑처리만 해준다. 
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
// 오름차순 정렬
BYTE Median(BYTE *arr, int size) {

	const int S = size;
	for (int i = 0; i < size - 1; i++) { // pivot index
		for (int j = i + 1; j < size; j++) { // pivot이랑 비교를 하는 대상 인덱스, pivot 다음 인덱스
			if (arr[i] > arr[j]) {
				Swap(&arr[i], &arr[j]);
			}
		}
	}
	return arr[S / 2];
}

// 오름차순 진행 후 가장 큰 값 반환
BYTE MaxPooling(BYTE *arr, int size) {

	const int S = size;
	for (int i = 0; i < size - 1; i++) { // pivot index
		for (int j = i + 1; j < size; j++) { // pivot이랑 비교를 하는 대상 인덱스, pivot 다음 인덱스
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
		for (int j = i + 1; j < size; j++) { // pivot이랑 비교를 하는 대상 인덱스, pivot 다음 인덱스
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
//		if (BlobArea[coloring[k]] > 500) CutImage[k] = 0; // 특정 면적이 500보다 큰 컴포넌트 영역만 출력
//		CutImage[k] = (unsigned char)(coloring[k] * grayGap); // 원래 라벨링 결과만 확인, 모든 컴포넌트에 대해 grayGap(10.625)적용
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
//					Output[i*W+j] = 0; // 하얀 배경에 검출하고자 하는 컴포넌트의 경계만 검은색으로 출력하고 싶을 때 
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
	center->xpos = (int)center->xpos / count;
	center->ypos = (int)center->ypos / count;
}

void SetAxis(BYTE *Temp, Point *point, int W, int H) {
	bool exitOuterLoop = false;
	// 좌측상단부터 우방향 가로우선으로 탐색하다가, 0인화소를 처음 만났을 때의 Y좌표: y1
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
	// 우측하단부터 좌방향 가로우선으로 탐색하다가, 0인화소를 처음 만났을 때의 Y좌표를 저장: y2
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
	// 우측하단부터 상방향 세로우선으로  탐색하다가, 0인화소를 처음 만났을 때의 X좌표를 저장: x2
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

void Translation(BYTE *Img, BYTE *Out, int W, int H, int Tx, int Ty) {

	// Tx, Ty -> x, y좌표의 이동량을 저장하는 변수
	Ty *= -1; // 우리가 생각하는 좌표의 기준으로 제대로 이동
			  // i => y좌표
			  // j => x좌표
			  // x와 y좌표는 영상의 좌측 최상단부터 시작
			  // BMP파일은 위아래가 뒤집혀 있다. 따라서 y좌표값 조정 필요.
	for (int i = 0; i < H; i++) { // 영상을 2차원적으로 탐색하는 전형적인 for문 (관용표현)
		for (int j = 0; j < W; j++) {
			if ((i + Ty < H && i + Ty >= 0) && (j + Tx < W && j + Tx >= 0)) { // x와 y의 범위의 조건 설정
				Out[(i + Ty)*W + (j + Tx)] = Img[i*W + j]; // 순방향 사상
			}
		}
	}
}

void VerticalFlip(BYTE *Img, int W, int H) {

	// H/2를 한 이유: H가 영상의 세로사이즈 인데
	// 절반만큼만 for문을 돌면서 맨 윗줄과 맨 아랫줄을 바꾸는 과정을 거침.
	for (int i = 0; i < H / 2; i++) { // i는 y좌표
		for (int j = 0; j < W; j++) { // j는 x좌표
			Swap(&Img[i*W + j], &Img[(H - 1 - i)*W + j]); // 영상의 최좌측상단과 최좌측하단의 픽셀을 맞바꿈.
		}
	}
}

void HorizontalFlip(BYTE *Img, int W, int H) {

	// W/2를 한 이유: W가 영상의 가로사이즈 인데
	// 절반만큼만 for문을 돌면서 맨 왼쪽 줄과 맨 오른쪽 줄을 바꾸는 과정을 거침.
	for (int i = 0; i < W / 2; i++) { // i는 x좌표
		for (int j = 0; j < H; j++) { // j는 y좌표
			Swap(&Img[j*W + i], &Img[j*W + (W - 1 - i)]); // 영상의 최좌측상단과 최좌측하단의 픽셀을 맞바꿈.
		}
	}
}

void Scaling(BYTE *Img, BYTE *Out, int W, int H, double SF_X, double SF_Y) {
	int tmpX, tmpY;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			/*tmpX = (int)(j*SF_X); // 순방향 사상 계산일 때 사용(but Hole발생)
			tmpY = (int)(i*SF_Y);*/
			tmpX = (int)(j / SF_X); // 역방향 사상 계산
			tmpY = (int)(i / SF_Y);
			if (tmpY < H && tmpX < W) {
				// Output[tmpY*W + tmpX] = Image[i*W + j]; // 순방향 사상
				// 역방향 사상은 입력영상의 모든 화소들을 검사하는 것이 아니라
				// 출력영상의 모든 화소들 위치를 탐색하면서 나한테 와야되는 애가 원본영상에서 누군지 역으로 계산하는 것
				Out[i*W + j] = Img[tmpY*W + tmpX]; // 역방향 계산
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
			tmpY = (int)(sin(Radian)*j + cos(Radian)*i);*/ // 순방향
			tmpX = (int)(cos(Radian)*j + sin(Radian)*i);
			tmpY = (int)(-sin(Radian)*j + cos(Radian)*i); // 역방향
			if ((tmpY < H && tmpY >= 0) && (tmpX < W && tmpX >= 0)) {
				/*Output[tmpY*W + tmpX] = Image[i*W + j];*/ // 순방향 사상
				Out[i*W + j] = Img[tmpY*W + tmpX]; // 역방향 사상
			}
		}
	}
}