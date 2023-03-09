// 화면 캡처.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstring>

uint32_t T, N;

using namespace std;


// output의 숫자를 1 증가시킴
int increase(char* output, int len)
{
	for (int i = len - 1; 0 <= i; i--)
	{
		if (output[i] == '9')
			output[i] = '0';
		else
		{
			output[i]++;
			break;
		}
	}

	// 자리수가 모자랄경우
	if (output[0] == '0')
	{
		// 오른쪽으로 한칸 옮겨서 자리를 만듬
		for (uint32_t i = len; 0 < i; i--)
			output[i] = output[i - 1];
		output[len + 1] = NULL;
		output[0] = '1'; // 만든 자리에 1 받아올림

		return len + 1;
	}
	return len;
}

void recur(int num, int depth = 0)
{
	static char order[100];
	static uint32_t outputs;
	uint32_t i;
	if (depth == 0)
	{
		outputs = 0;
		i = 1;
	}
	else if (depth == num)
		return;
	else
		i = 0;

	// i : 비교대상 숫자 결정
	for (; i < 10; i++)
	{
		order[depth] = i + 0x30;
		
		// j : dict 탐색
		char str[100] = "0";
		int len = 1;
		for (uint32_t j = 0; j < N; j++)
		{
			len = increase(str, len);

			// dict중에서 depth길이의 단어만을 대상으로
			if (len == depth + 1)
			{
				// 앞자리가 맞는지 비교
				uint32_t k;
				for (k = 0; k < depth + 1; k++)
				{
					if (order[k] != str[k])
						break;
				}
				if (k < depth + 1) // 틀리면
					continue;

				if (str[depth] == i + 0x30)
				{
					if (outputs++ < 50)
						cout << str << ".png ";
					else
						return;

					recur(num, depth + 1);
					if (50 <= outputs)
						return;
					break;
				}
			}
		}
	}
}

int main()
{
	
	cin >> T;
	
	
	for (uint32_t i = 0; i < T; i++)
	{
		cin >> N;
		
		uint32_t digit;
		uint32_t tmp_j = N;
		for (digit = 0; tmp_j != 0; tmp_j /= 10)
			digit++;

		cout << "#" << i + 1 << ' ';
		recur(digit);
		cout << endl;
	}
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
