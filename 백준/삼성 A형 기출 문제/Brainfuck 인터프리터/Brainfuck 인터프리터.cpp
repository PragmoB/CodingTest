// Brainfuck 인터프리터.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstring>
#include <map>

typedef unsigned int UINT;
typedef unsigned char UCHAR;

using namespace std;

UINT testcases;
UINT len_arr, len_program, len_input;
UCHAR *program, *input;

void execute()
{
	uint8_t* arr = new UCHAR[len_arr];
	memset(arr, 0, len_arr);

	int arr_pointer = 0;
	UINT input_pointer = 0;

	// 무한루프의 조건들
	UINT num_executed = 0;
	map<UINT, UINT> loop_pair;
	UINT loop_end = 0;

	for (UINT i = 0; i < len_program; i++)
	{
		if (program[i] == '[')
		{
			UINT num_buckets = 1;
			UINT j;
			for (j = i + 1; num_buckets != 0; j++)
			{
				if (program[j] == ']')
					num_buckets--;
				else if (program[j] == '[')
					num_buckets++;
			}
			j--; // 오차 보정

			loop_pair[i] = j;
			loop_pair[j] = i;
		}
	}


	for (UINT i = 0; i < len_program; i++)
	{
		num_executed++;

		switch (program[i])
		{
		case '-':
			arr[arr_pointer]--;
			break;

		case '+':
			arr[arr_pointer]++;
			break;

		case '<':
			--arr_pointer;
			arr_pointer = (arr_pointer + len_arr) % len_arr;
			break;

		case '>':
			++arr_pointer;
			arr_pointer %= len_arr;
			break;

		case '[':
		{
			if (arr[arr_pointer] == 0)
				i = loop_pair[i];

			break;
		}
		case ']' :

			if (arr[arr_pointer] != 0)
			{
				// 무한루프에 진입한 상태일때 제일 끝에 있는 ]를 찾음
				if (50000000 <= num_executed && loop_end < i)
					loop_end = i;

				/* 짝을 이루는 [위치로 eip를 이동 */
				i = loop_pair[i];
			}
			
			break;
		case '.' :
			// 출력했다고 치고
			break;

		case ',' :
			if (input_pointer < len_input)
				arr[arr_pointer] = input[input_pointer++];
			else
				arr[arr_pointer] = 255;

			break;
		}
		if (100000000 <= num_executed)
		{
			cout << "Loops " << loop_pair[loop_end] << ' ' << loop_end << endl;
			return;
		}
	}

	cout << "Terminates" << endl;
}

int main()
{
	cin >> testcases;

	for (UINT i = 0; i < testcases; i++)
	{
		cin >> len_arr >> len_program >> len_input;
	
		program = new UCHAR[len_program + 1];
		cin >> program;

		input = new UCHAR[len_input + 1];
		cin >> input;

		execute();

		delete[] program;
		delete[] input;
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
