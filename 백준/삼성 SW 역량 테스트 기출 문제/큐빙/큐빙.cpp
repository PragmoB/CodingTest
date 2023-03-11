// 큐빙.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

class Plane;

class Plane {
public :
	char color; // 기본값(=가운데 색상값)
	char colors[3][3]; // 한 면에 칸은 9개
	Plane* neighbors[4]; // 인접한 면들이 시계방향으로 배열됨
	char neighbors_dir[4]; // 인접한 면들과 붙어있는 선분이 인접한 면 입장에서 봤을때 어느 방향인지 기술(상하좌우)
	char neighbors_turn_dir[4]; // 인접한 면들과 붙어있는 선분이 시계방향으로 회전할 때 가는 방향(+1, -1)
public :
	Plane(char color) : color(color)
	{ }
	void init()
	{
		for (uint32_t i = 0; i < 3; i++)
			for (uint32_t j = 0; j < 3; j++)
				colors[i][j] = color;
	}

	// 큐브 회전 구현
	void turn(char dir)
	{ 
		char tmp[3];

		switch (dir)
		{
		case '+':

			// 마지막 면 맞닿은 부분 저장
			for (uint32_t i = 0; i < 3; i++)
				switch (neighbors_dir[3])
				{
				case 'U': tmp[i] = neighbors[3]->colors[0][i]; break;
				case 'D': tmp[i] = neighbors[3]->colors[3 - 1][i]; break;
				case 'L': tmp[i] = neighbors[3]->colors[i][0]; break;
				case 'R': tmp[i] = neighbors[3]->colors[i][3 - 1]; break;
				}

			for (uint32_t i = 3 - 1; 0 <= (signed)i; i--) // i번째로 인접한 면(마지막 면 빼고) 반시계방향으로 탐색
				/*
				 * i번째 인접한 면의 부분을 (i + 1)번째 면에 덮어씌우기 구현
				 * j = i번째 인접한 면에서 colors를 탐색하기 위한 변수
				 * k = (i + 1)번째 인접한 면에서 colors를 탐색하기 위한 변수
				 * 식이 좀 스파게티인데, 해당하는 neighbors_turn_dir이 1이면 [ 0, 1, 2 ]순으로 탐색하도록
				 * 해당하는 neighbors_turn_dir이 -1이면 [ 2, 1, 0 ]순으로 탐색하도록 구현한것이라 보면 된다
				 */
				for (uint32_t j = (3 + neighbors_turn_dir[i]) % (3 + 1),
							  k = (3 + neighbors_turn_dir[i + 1]) % (3 + 1);
							  (0 <= (signed)j) && (j < 3) && (0 <= (signed)k) && (k < 3);
							  j += neighbors_turn_dir[i], k += neighbors_turn_dir[i + 1])
				{
					char source, *dest;

					switch (neighbors_dir[i])
					{
					case 'U': source = neighbors[i]->colors[0][j]; break;
					case 'D': source = neighbors[i]->colors[3 - 1][j]; break;
					case 'L': source = neighbors[i]->colors[j][0]; break;
					case 'R': source = neighbors[i]->colors[j][3 - 1]; break;
					default: source = NULL;
					}
					switch (neighbors_dir[i + 1])
					{
					case 'U': dest = &neighbors[i + 1]->colors[0][k]; break;
					case 'D': dest = &neighbors[i + 1]->colors[3 - 1][k]; break;
					case 'L': dest = &neighbors[i + 1]->colors[k][0]; break;
					case 'R': dest = &neighbors[i + 1]->colors[k][3 - 1]; break;
					default: dest = NULL;
					}

					*dest = source;
				}
			/* 반복을 끝낸 시점에서 처음 면만 빼고 회전이 완료됨 */

			// 저장해뒀던 마지막 면을 처음 면에 복사
			for (uint32_t i = (3 + neighbors_turn_dir[0]) % (3 + 1),
						  j = (3 + neighbors_turn_dir[3]) % (3 + 1);
						  (0 <= (signed)i) && (i < 3) && (0 <= (signed)j) && (j < 3);
						  i += neighbors_turn_dir[0], j += neighbors_turn_dir[3])
				switch (neighbors_dir[0])
				{
				case 'U': neighbors[0]->colors[0][i] = tmp[j]; break;
				case 'D': neighbors[0]->colors[3 - 1][i] = tmp[j]; break;
				case 'L': neighbors[0]->colors[i][0] = tmp[j]; break;
				case 'R': neighbors[0]->colors[i][3 - 1] = tmp[j]; break;
				}

			/* 현 시점에서 인접한 면들끼리는 회전이 완료되었으나, 자신은 그대로임 */

			tmp[0] = colors[2][0];
			tmp[1] = colors[1][0];

			colors[2][0] = colors[2][2];
			colors[1][0] = colors[2][1];

			colors[2][2] = colors[0][2];
			colors[2][1] = colors[1][2];

			colors[0][2] = colors[0][0];
			colors[1][2] = colors[0][1];

			colors[0][0] = tmp[0];
			colors[0][1] = tmp[1];
			break;

		case '-':

			for (uint32_t i = 0; i < 3; i++)
				switch (neighbors_dir[0])
				{
				case 'U': tmp[i] = neighbors[0]->colors[0][i]; break;
				case 'D': tmp[i] = neighbors[0]->colors[3 - 1][i]; break;
				case 'L': tmp[i] = neighbors[0]->colors[i][0]; break;
				case 'R': tmp[i] = neighbors[0]->colors[i][3 - 1]; break;
				}

			for (uint32_t i = 1; i < 4; i++) // i번째로 인접한 면(처음 면 빼고) 시계방향으로 탐색
				/*
				 * i번째 인접한 면의 부분을 (i - 1)번째 면에 덮어씌우기 구현
				 * j = i번째 인접한 면에서 colors를 탐색하기 위한 변수
				 * k = (i - 1)번째 인접한 면에서 colors를 탐색하기 위한 변수
				 * 식이 좀 스파게티인데, 해당하는 neighbors_turn_dir이 1이면 [ 0, 1, 2 ]순으로 탐색하도록
				 * 해당하는 neighbors_turn_dir이 -1이면 [ 2, 1, 0 ]순으로 탐색하도록 구현한것이라 보면 된다
				 */
				for (uint32_t j = (3 + neighbors_turn_dir[i]) % (3 + 1),
							  k = (3 + neighbors_turn_dir[i - 1]) % (3 + 1);
							  (0 <= (signed)j) && (j < 3) && (0 <= (signed)k) && (k < 3);
							  j += neighbors_turn_dir[i], k += neighbors_turn_dir[i - 1])
				{
					char source, *dest;

					switch (neighbors_dir[i])
					{
					case 'U': source = neighbors[i]->colors[0][j]; break;
					case 'D': source = neighbors[i]->colors[3 - 1][j]; break;
					case 'L': source = neighbors[i]->colors[j][0]; break;
					case 'R': source = neighbors[i]->colors[j][3 - 1]; break;
					default: source = NULL;
					}
					switch (neighbors_dir[i - 1])
					{
					case 'U': dest = &neighbors[i - 1]->colors[0][k]; break;
					case 'D': dest = &neighbors[i - 1]->colors[3 - 1][k]; break;
					case 'L': dest = &neighbors[i - 1]->colors[k][0]; break;
					case 'R': dest = &neighbors[i - 1]->colors[k][3 - 1]; break;
					default: dest = NULL;
					}

					*dest = source;
				}
			/* 반복을 끝낸 시점에서 처음 면만 빼고 회전이 완료됨 */

			// 저장해뒀던 처음 면을 마지막 면에 복사
			for (uint32_t i = (3 + neighbors_turn_dir[3]) % (3 + 1),
						  j = (3 + neighbors_turn_dir[0]) % (3 + 1);
						  (0 <= (signed)i) && (i < 3) && (0 <= (signed)j) && (j < 3);
						  i += neighbors_turn_dir[3], j += neighbors_turn_dir[0])
				switch (neighbors_dir[3])
				{
				case 'U': neighbors[3]->colors[0][i] = tmp[j]; break;
				case 'D': neighbors[3]->colors[3 - 1][i] = tmp[j]; break;
				case 'L': neighbors[3]->colors[i][0] = tmp[j]; break;
				case 'R': neighbors[3]->colors[i][3 - 1] = tmp[j]; break;
				}

			/* 현 시점에서 인접한 면들끼리는 회전이 완료되었으나, 자신은 그대로임 */

			tmp[0] = colors[0][0];
			tmp[1] = colors[0][1];

			colors[0][0] = colors[0][2];
			colors[0][1] = colors[1][2];

			colors[0][2] = colors[2][2];
			colors[1][2] = colors[2][1];

			colors[2][2] = colors[2][0];
			colors[2][1] = colors[1][0];

			colors[2][0] = tmp[0];
			colors[1][0] = tmp[1];
			break;
		}
	}

	void print()
	{
		for (uint32_t i = 0; i < 3; i++)
		{
			for (uint32_t j = 0; j < 3; j++)
				cout << colors[i][j];
			cout << endl;
		}
	}
};


enum cube_dir {
	front = 0,
	back,
	up,
	down,
	left,
	right
};

int main()
{
	uint32_t t, n;

	/* 
	 * 면 6개(앞뒤상하좌우)를 모아서 큐브 조립.
	 * 조립하는 코드 중에 밑에 보면 코드가 반복적으로 길게 늘어져 있는 부분이 있는데,
	 * 반복문을 사용하기엔 규칙이 안보여서 어쩔수 없었음
	 */

	Plane* cube[6];
	cube[cube_dir::front] = new Plane('r');
	cube[cube_dir::back] = new Plane('o');
	cube[cube_dir::up] = new Plane('w');
	cube[cube_dir::down] = new Plane('y');
	cube[cube_dir::left] = new Plane('g');
	cube[cube_dir::right] = new Plane('b');
	for (uint32_t i = 0; i < 6; i++)
		cube[i]->init();
	
	cube[cube_dir::front]->neighbors[0] = cube[cube_dir::up];
	cube[cube_dir::front]->neighbors[1] = cube[cube_dir::right];
	cube[cube_dir::front]->neighbors[2] = cube[cube_dir::down];
	cube[cube_dir::front]->neighbors[3] = cube[cube_dir::left];
	cube[cube_dir::front]->neighbors_dir[0] = 'D';
	cube[cube_dir::front]->neighbors_dir[1] = 'L';
	cube[cube_dir::front]->neighbors_dir[2] = 'U';
	cube[cube_dir::front]->neighbors_dir[3] = 'R';
	cube[cube_dir::front]->neighbors_turn_dir[0] = 1;
	cube[cube_dir::front]->neighbors_turn_dir[1] = 1;
	cube[cube_dir::front]->neighbors_turn_dir[2] = -1;
	cube[cube_dir::front]->neighbors_turn_dir[3] = -1;

	cube[cube_dir::back]->neighbors[0] = cube[cube_dir::up];
	cube[cube_dir::back]->neighbors[1] = cube[cube_dir::left];
	cube[cube_dir::back]->neighbors[2] = cube[cube_dir::down];
	cube[cube_dir::back]->neighbors[3] = cube[cube_dir::right];
	cube[cube_dir::back]->neighbors_dir[0] = 'U';
	cube[cube_dir::back]->neighbors_dir[1] = 'L';
	cube[cube_dir::back]->neighbors_dir[2] = 'D';
	cube[cube_dir::back]->neighbors_dir[3] = 'R';
	cube[cube_dir::back]->neighbors_turn_dir[0] = -1;
	cube[cube_dir::back]->neighbors_turn_dir[1] = 1;
	cube[cube_dir::back]->neighbors_turn_dir[2] = 1;
	cube[cube_dir::back]->neighbors_turn_dir[3] = -1;

	cube[cube_dir::up]->neighbors[0] = cube[cube_dir::back];
	cube[cube_dir::up]->neighbors[1] = cube[cube_dir::right];
	cube[cube_dir::up]->neighbors[2] = cube[cube_dir::front];
	cube[cube_dir::up]->neighbors[3] = cube[cube_dir::left];
	for (uint32_t i = 0; i < 4; i++)
	{
		cube[cube_dir::up]->neighbors_dir[i] = 'U';
		cube[cube_dir::up]->neighbors_turn_dir[i] = -1;
	}

	cube[cube_dir::down]->neighbors[0] = cube[cube_dir::front];
	cube[cube_dir::down]->neighbors[1] = cube[cube_dir::right];
	cube[cube_dir::down]->neighbors[2] = cube[cube_dir::back];
	cube[cube_dir::down]->neighbors[3] = cube[cube_dir::left];
	for (uint32_t i = 0; i < 4; i++)
	{
		cube[cube_dir::down]->neighbors_dir[i] = 'D';
		cube[cube_dir::down]->neighbors_turn_dir[i] = 1;
	}

	cube[cube_dir::left]->neighbors[0] = cube[cube_dir::up];
	cube[cube_dir::left]->neighbors[1] = cube[cube_dir::front];
	cube[cube_dir::left]->neighbors[2] = cube[cube_dir::down];
	cube[cube_dir::left]->neighbors[3] = cube[cube_dir::back];
	cube[cube_dir::left]->neighbors_dir[0] = 'L';
	cube[cube_dir::left]->neighbors_dir[1] = 'L';
	cube[cube_dir::left]->neighbors_dir[2] = 'L';
	cube[cube_dir::left]->neighbors_dir[3] = 'R';
	cube[cube_dir::left]->neighbors_turn_dir[0] = 1;
	cube[cube_dir::left]->neighbors_turn_dir[1] = 1;
	cube[cube_dir::left]->neighbors_turn_dir[2] = 1;
	cube[cube_dir::left]->neighbors_turn_dir[3] = -1;

	cube[cube_dir::right]->neighbors[0] = cube[cube_dir::up];
	cube[cube_dir::right]->neighbors[1] = cube[cube_dir::back];
	cube[cube_dir::right]->neighbors[2] = cube[cube_dir::down];
	cube[cube_dir::right]->neighbors[3] = cube[cube_dir::front];
	cube[cube_dir::right]->neighbors_dir[0] = 'R';
	cube[cube_dir::right]->neighbors_dir[1] = 'L';
	cube[cube_dir::right]->neighbors_dir[2] = 'R';
	cube[cube_dir::right]->neighbors_dir[3] = 'R';
	cube[cube_dir::right]->neighbors_turn_dir[0] = -1;
	cube[cube_dir::right]->neighbors_turn_dir[1] = 1;
	cube[cube_dir::right]->neighbors_turn_dir[2] = -1;
	cube[cube_dir::right]->neighbors_turn_dir[3] = -1;

	/* 조립 끝, 본격적으로 시작 */

	cin >> t;
	
	for (uint32_t i = 0; i < t; i++)
	{
		cin >> n;
		
		char dir[3];
		for (uint32_t j = 0; j < n; j++)
		{
			cin >> dir;
			switch (dir[0])
			{
			case 'U': cube[cube_dir::up]->turn(dir[1]); break;
			case 'D': cube[cube_dir::down]->turn(dir[1]); break;
			case 'F': cube[cube_dir::front]->turn(dir[1]); break;
			case 'B': cube[cube_dir::back]->turn(dir[1]); break;
			case 'L': cube[cube_dir::left]->turn(dir[1]); break;
			case 'R': cube[cube_dir::right]->turn(dir[1]); break;
			}
		}

		cube[cube_dir::up]->print();
		for (uint32_t i = 0; i < 6; i++)
			cube[i]->init();
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
