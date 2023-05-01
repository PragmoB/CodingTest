// 줄세우기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

int main()
{
	uint32_t N;
	uint32_t input[200];
	
	cin >> N;
	
	for (uint32_t i = 0; i < N; i++)
		cin >> input[i];

	uint32_t current_max = 0, result = 0;

	for (uint32_t i = 0; i < N; i++)
	{
		if (current_max < input[i])
			current_max = input[i];
		else
			result++;
	}

	cout << result;
}
