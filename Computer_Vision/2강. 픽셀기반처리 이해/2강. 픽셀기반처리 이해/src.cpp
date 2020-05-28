#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h> // 동적할당 시 필요!
#include <Windows.h> // 비트맵 헤더 관련된 구조체들이 정의되어 있음.
int main()
{
	BITMAPFILEHEADER hf; // BMP 파일헤더 14Bytes
	BITMAPINFOHEADER hInfo; // BMP 영상헤더 40Bytes
	RGBQUAD hRGB[256]; // 팔레트 정보 (256 * 4Bytes = 1024)
	FILE *fp;
	fp = fopen("lenna.bmp", "rb");
	if (fp == NULL) {  // 예외처리
		printf("File not found!\n");
		return -1; // main의 반환값이 void 이므로; 비정상 종료표시
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp); // 현재 fp(파일 포인터)에서 1번 읽어온다!
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);

//	영상의 크기에 맞게 동적 할당을 하고 화소 개수 정보를 넣음.
//	영상의 크기가 256*256 이므로 65,536 Byte 읽어와야함. 
	int ImgSize = hInfo.biWidth * hInfo.biHeight; // biWidth: 영상의 가로 사이즈
//  BYTE는 unsigned char type(1 byte)이다. (0~255까지)
//	malloc 함수의 리턴값이 void포인터이다. 
//	Heap영역에서 메모리를 65,536만큼 동적할당을 하고 자기가 할당한 메모리의 시작주소를 반환한다. 근데 그 시작주소를 어떤 타입이 받을지 모르기때문에 void포인터타입으로 반환해준다.
	BYTE * Image = (BYTE *)malloc(ImgSize); // BYTE *로 강제 형변환 해줌. 그리고 Image변수에는 원본영상을 담을 것임.
	BYTE * Output = (BYTE *)malloc(ImgSize); // 영상처리의 결과는 Output변수에 담음.
	fread(Image, sizeof(BYTE), ImgSize, fp); // 영상의 화소정보를 읽어올것임. 
	fclose(fp); // fp와 lenna.bmp의 연결관계를 끊어줌.	
	
	/* 영상처리 */

	for (int i = 0; i < ImgSize; i++) {
		
		 Output[i] = Image[i]; // 원본 영상 출력
		// Output[i] = 255 - Image[i]; // 영상의 원래 화소값을 255에서 빼줌. 화소가 반전이됨. 영상이 반전이 되는 효과를 출력.black은 white로 white는 black으로.
		// Output[i] = Image[i] + 100; // 영상 밝기 조절 100을 넣었을때 255보다 큰 숫자가 나오면 overflow 현상 나타남.
	}
		
	fp = fopen("output.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // 기록할 떄는 1바이트 단위로 기록
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), ImgSize, fp); // 영상의 처리된 결과를 출력.
	fclose(fp);
	free(Image); // memory leak 현상 방지.
	free(Output);
}