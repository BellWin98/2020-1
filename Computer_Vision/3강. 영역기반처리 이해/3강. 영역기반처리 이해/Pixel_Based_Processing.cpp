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


	int Histo[256] = { 0 }; // 0으로 초기화
	int AHisto[256] = { 0 }; // 누적 히스토그램(Accumulated Histogram)

	// ObtainHistogram(Image, Histo, hinfo.biWidth, hinfo.biHeight);
	// ObtainAHistogram(Histo, AHisto);
	// HistogramEqualization(Image, Output, AHisto, hinfo.biWidth, hinfo.biHeight);
	// HistogramStretching(Image, Output, Histo, hinfo.biWidth, hinfo.biHeight);
	// printHistogram(Histo);
	// printAHistogram(AHisto);
	 int Thres = GonzalezBinThresh(Image, hinfo.biWidth, hinfo.biHeight);
	// 임계치를 너무 높거나 낮게 잡으면 이상한 결과가 나옴. 80이 적당.
	// 주관적인 판단, 경험적인 판단 또는 자동 임계치 결정방법이 있음.
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
