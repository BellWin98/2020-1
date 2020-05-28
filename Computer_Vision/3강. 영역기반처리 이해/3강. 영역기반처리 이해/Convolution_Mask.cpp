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
void AverageConv(BYTE *Img, BYTE *Out, int W, int H); // 박스 평활화
void GaussAvrConv(BYTE *Img, BYTE *Out, int W, int H); // 가우시안 평활화
void Prewitt_X_Conv(BYTE *Img, BYTE *Out, int W, int H); 
void Prewitt_Y_Conv(BYTE *Img, BYTE *Out, int W, int H);
void Sobel_X_Conv(BYTE *Img, BYTE *Out, int W, int H); // Sobel이 Prewitt보다 더 첨예한 경계가 나옴!
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
	BYTE *Temp = (BYTE *)malloc(ImgSize); // 임시배열
	BYTE *Output = (BYTE *)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);

	// OriginalImage(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// InverseImage(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// BrightnessAdj(Image, Output, hinfo.biWidth, hinfo.biHeight, 70);
	// ContrastAdj(Image, Output, hinfo.biWidth, hinfo.biHeight, 1.5); 


	// int Histo[256] = { 0 }; // 0으로 초기화
	// int AHisto[256] = { 0 }; // 누적 히스토그램(Accumulated Histogram)

	// ObtainHistogram(Image, Histo, hinfo.biWidth, hinfo.biHeight);
	// ObtainAHistogram(Histo, AHisto);
	// HistogramEqualization(Image, Output, AHisto, hinfo.biWidth, hinfo.biHeight);
	// HistogramStretching(Image, Output, Histo, hinfo.biWidth, hinfo.biHeight);
	// printHistogram(Histo);
	// printAHistogram(AHisto);
	// 임계치를 너무 높거나 낮게 잡으면 이상한 결과가 나옴. 80이 적당.
	// 주관적인 판단, 경험적인 판단 또는 자동 임계치 결정방법이 있음.
	
	// AverageConv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// GaussAvrConv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// Prewitt_X_Conv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	// Prewitt_Y_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// Sobel_X_Conv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	// Sobel_Y_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);
	// Laplace_Conv(Image, Output, hinfo.biWidth, hinfo.biHeight);

	// 고주파(노이즈)성분을 죽이기 위해 평활화를 거침! 저역통과 후 고역통과
	GaussAvrConv(Image, Temp, hinfo.biWidth, hinfo.biHeight);
	Laplace_Conv_DC(Temp, Output, hinfo.biWidth, hinfo.biHeight); 
	 // prewitt 또는 Sobel의 X와 Y를 합치는 과정 
	 /*for (int i = 0; i < ImgSize; i++) {
		 if (Temp[i] > Output[i]) {
			 Output[i] = Temp[i];
		 }
	 }*/
	// Binarization(Output, Output, hinfo.biWidth, hinfo.biHeight, 40); // 경계값을 낮출수록 경계가 진하게 나타남.

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

void AverageConv(BYTE *Img, BYTE *Out, int W, int H) {
	double Kernel[3][3] = {
		 0.11111, 0.11111, 0.11111,
		 0.11111, 0.11111, 0.11111,
		 0.11111, 0.11111, 0.11111
	};
	double SumProduct = 0.0;
	// 위아래 margin을 두어야 하므로 커널의 센터인 i와 j는 [1][1]부터 시작
	for (int i = 1; i < H-1; i++) { // 영상의 행(Y좌표)
		for (int j = 1; j < W-1; j++) { // 영상의 열(X좌표)
			for (int m = -1; m <= 1; m++) { // 커널의 행, 세로방향으로 봤을 때 m=-1은 센터를 중심으로 나보다 위에있는 것을 표현, m=0은 나 자신, m=1은 나보다 아래에 있는 행
				for (int n = -1; n <= 1; n++) { // 커널의 열, 센터가 속해있는 열을 기준으로 -1은 왼쪽, 0은 나자신, 1은 오른쪽
					// 배열의 인덱스는 음수가 될 수 없으므로 +1, 그리고 커널 인덱스에 따라서 영상에서의 행과 열 위치도 m,n과 연동되므로 각각 +m, +n
					SumProduct += Img[(i+m)*W+(j+n)] * Kernel[m+1][n+1]; 
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
	// kernel의 weight의 합 16을 기준으로 각 픽셀의 weight 산정
	// 각 픽셀의 비율의 합은 1이어야 하므로 16으로 나누어준다. 
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
			// Convolution을 돌렸을 때 음수가 곱해지는 경우 weight값이 최소 -255까지 찍힐 수 있다. 
			// 하지만 픽셀의 범위는 0 ~ 255이기 때문에 절댓값과 같은 조정이 필요.
			// 그러나 Prewitt mask를 통해서 절댓값을 취하는 경우 범위는  0부터 255*3 = 765까지 값이 나올 수 있음
			// 0 ~ 765 ====> 0 ~ 255 이렇게 바꿔줘야함. 따라서 3으로 나눠준다
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
			// Sobel Mask를 통해서 절댓값을 취하는 경우 범위는  0부터 255*4 = 1020까지 값이 나올 수 있음
			// 0 ~ 1020 == == > 0 ~255. 따라서 4로 나눠준다.
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
			// Laplacian Mask를 통해서 절댓값을 취하는 경우 범위는  0부터 255*8 = 2040까지 값이 나올 수 있음
			// 0 ~ 2040 == == > 0 ~255. 따라서 8로 나눠준다.
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