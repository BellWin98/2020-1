#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h> // �����Ҵ� �� �ʿ�!
#include <Windows.h> // ��Ʈ�� ��� ���õ� ����ü���� ���ǵǾ� ����.
int main()
{
	BITMAPFILEHEADER hf; // BMP ������� 14Bytes
	BITMAPINFOHEADER hInfo; // BMP ������� 40Bytes
	RGBQUAD hRGB[256]; // �ȷ�Ʈ ���� (256 * 4Bytes = 1024)
	FILE *fp;
	fp = fopen("lenna.bmp", "rb");
	if (fp == NULL) {  // ����ó��
		printf("File not found!\n");
		return -1; // main�� ��ȯ���� void �̹Ƿ�; ������ ����ǥ��
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp); // ���� fp(���� ������)���� 1�� �о�´�!
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);

//	������ ũ�⿡ �°� ���� �Ҵ��� �ϰ� ȭ�� ���� ������ ����.
//	������ ũ�Ⱑ 256*256 �̹Ƿ� 65,536 Byte �о�;���. 
	int ImgSize = hInfo.biWidth * hInfo.biHeight; // biWidth: ������ ���� ������
//  BYTE�� unsigned char type(1 byte)�̴�. (0~255����)
//	malloc �Լ��� ���ϰ��� void�������̴�. 
//	Heap�������� �޸𸮸� 65,536��ŭ �����Ҵ��� �ϰ� �ڱⰡ �Ҵ��� �޸��� �����ּҸ� ��ȯ�Ѵ�. �ٵ� �� �����ּҸ� � Ÿ���� ������ �𸣱⶧���� void������Ÿ������ ��ȯ���ش�.
	BYTE * Image = (BYTE *)malloc(ImgSize); // BYTE *�� ���� ����ȯ ����. �׸��� Image�������� ���������� ���� ����.
	BYTE * Output = (BYTE *)malloc(ImgSize); // ����ó���� ����� Output������ ����.
	fread(Image, sizeof(BYTE), ImgSize, fp); // ������ ȭ�������� �о�ð���. 
	fclose(fp); // fp�� lenna.bmp�� ������踦 ������.	
	
	/* ����ó�� */

	for (int i = 0; i < ImgSize; i++) {
		
		 Output[i] = Image[i]; // ���� ���� ���
		// Output[i] = 255 - Image[i]; // ������ ���� ȭ�Ұ��� 255���� ����. ȭ�Ұ� �����̵�. ������ ������ �Ǵ� ȿ���� ���.black�� white�� white�� black����.
		// Output[i] = Image[i] + 100; // ���� ��� ���� 100�� �־����� 255���� ū ���ڰ� ������ overflow ���� ��Ÿ��.
	}
		
	fp = fopen("output.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp); // ����� ���� 1����Ʈ ������ ���
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), ImgSize, fp); // ������ ó���� ����� ���.
	fclose(fp);
	free(Image); // memory leak ���� ����.
	free(Output);
}