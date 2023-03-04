// Add Two Numbers.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>

struct ListNode {
	int val;
	struct ListNode *next;
};
 
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode* result = malloc(sizeof(struct ListNode));
	result->val = 0;
	struct ListNode *tresult = result, *tresult_prev = NULL;

	for (; l1 || l2;)
	{
		int num1, num2;
		if (!l1)
			num1 = 0;
		else
			num1 = l1->val;

		if (!l2)
			num2 = 0;
		else
			num2 = l2->val;

		// 현시점에서 피연산자 num1과 num2가 정해짐

		tresult->val += (num1 + num2) % 10; // 처음자리 수 결정

		// 다음자리 수로 옮김
		tresult_prev = tresult;
		tresult->next = malloc(sizeof(struct ListNode));
		tresult = tresult->next;

		// 둘째자리 수 결정
		tresult->val = 0;
		tresult->val += tresult_prev->val / 10;
		tresult_prev->val %= 10;

		tresult->val += ((num1 + num2) / 10);

		// 현 시점에서 l1->val + l2->val이 완벽히 계산됨

		if (l1)
			l1 = l1->next;
		if (l2)
			l2 = l2->next;
	}
	// 현 시점에서 result가 [?, ?, ?, 0] 또는 [?, ?, ?, 1]으로 됨,tresult는 맨마지막 숫자임 tresult_prev는 맨마지막 바로 뒤를 가리킴

	if (tresult->val == 0)
	{
		free(tresult);
		tresult_prev->next = NULL;
	}
	else
		tresult->next = NULL;

	return result;
}

int main()
{
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
