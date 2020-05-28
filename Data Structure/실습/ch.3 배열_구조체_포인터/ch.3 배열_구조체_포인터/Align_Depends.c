#include <stdio.h>
#include <stdlib.h>

// ���� �ڷ������� �������ִ°� �޸� ����!
struct AlignDepends {
	char c; // packing 3 more bytes
	int i;
};

struct AlignDepends2 {
	char c1; // packing 3 more bytes
	int i;
	char c2; // packing 3 more bytes
};

struct AlignDepends3 {
	char c1, c2; // packing 2 more bytes
	int i;
};

int main() {
	// size_t�� '�̷л� ���� ū ����� ���� �� �ִ� unsigned ������ Ÿ��'���� ���ǵȴ�.
	// ��, 32��Ʈ �ӽſ����� 32��Ʈ �������� unsigned ������(int�� �ƴ϶� �׳� '����'�� �ǹ��Ѵ�)
	// 64��Ʈ �ӽſ����� 64��Ʈ �������� unsigned ������(unsigned long long)�̴�. 
	// ���� ���������� �𸣴� 128��Ʈ �ӽ��̶���� �� ū �ӽ��� �����Ѵٸ� �׿� ���� �� ū ����� �� ���̴�.
	// �� ������, ������ ���ϰ��� 4�Ⱑ�� �Ѿ�� ���ϵ��� ó���ϰų� ū �����͸� ó���Ϸ� �� �� �� ����� �ݵ�� �˰� �ִ°� ����.
	// ����� unsigned int���� �˰� int�� unsigned int�� ����ȯ�� �ؼ� ����ϴٰ� ������ ����� ���׸� �߻���ų ���ɼ��� �ֱ� �����̴�.

	size_t i = sizeof(int);
	size_t size = sizeof(struct AlignDepends);
	size_t size2 = sizeof(struct AlignDepends2);
	size_t size3 = sizeof(struct AlignDepends3);
	printf("%d\n", i);
	printf("%d\n", size);
	printf("%d\n", size2);
	printf("%d\n", size3);
	return 0;
}