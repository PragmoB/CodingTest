// 괄호 추가하기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

uint32_t N;
char* operation;

using namespace std;

int operate(int operand1, char operatorr, int operand2)
{
	switch (operatorr)
	{
	case '+':
		return operand1 + operand2;

	case '-':
		return operand1 - operand2;

	case '*':
		return operand1 * operand2;
	}
}
int dfs(uint32_t loc = 0, int operand1 = operation[0] - 0x30)
{
	static int max = 0x80000000;
	int result;

	result = operate(operand1, operation[loc + 1], operation[loc + 2] - 0x30);
	if (loc + 3 == N)
	{
		if (max < result)
			max = result;
		return max;
	}
	dfs(loc + 2, result);

	if (loc + 4 < N)
	{
		result = operate(operation[loc + 2] - 0x30, operation[loc + 3], operation[loc + 4] - 0x30);
		result = operate(operand1, operation[loc + 1], result);
		if (loc + 5 == N)
		{
			if (max < result)
				max = result;
			return max;
		}
		dfs(loc + 4, result);
	}


	return max;
}


int main()
{
	cin >> N;
	operation = new char[N + 1];
	cin >> operation;
	if (N == 1)
		cout << operation[0];
	else
		cout << dfs();
	
	delete[] operation;
	return 0;
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
