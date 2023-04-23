// 암호코드.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstring>

using namespace std;

// 묶었을때 유효한지 검사
bool connectable(char a, char b)
{
	int num = (a - 0x30) * 10 + (b - 0x30);
	return (10 <= num && num <= 26);
}

int main()
{
	char input[5000];
	cin >> input;

	const size_t len = strlen(input);

	/* 유효하지 않은 입력값 검사 */

	if (input[0] == '0')
	{
		cout << 0 << endl;
		return 0;
	}

	for (uint32_t i = 1; i < len; i++)
	{
		if (input[i] == '0' && !connectable(input[i - 1], input[i]))
		{
			cout << 0 << endl;
			return 0;
		}
	}

	uint64_t unconn = 1, conn = 0; // 경우의 개수를 끝자리가 묶여있지 않은 경우 / 묶여있는 경우로 구분함

	/* 경우의 수 계산 */

	for (uint32_t i = 1; i < len; i++) // 입력값 길이 늘려가며 탐색
	{
		if (connectable(input[i - 1], input[i])) // 암호의 끝 2자리를 묶을 수 있는 경우
		{
			if (input[i] == '0')
			{
				conn = unconn;
				unconn = 0;
			}
			else
			{
				uint64_t tmp = unconn;
				unconn =  (unconn + conn) % 1000000;
				conn = tmp;
			}
		}
		else
		{
			unconn = (unconn + conn) % 1000000;
			conn = 0;
		}
	}

	cout << (unconn + conn) % 1000000 << endl;
	return 0;
}