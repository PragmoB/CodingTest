// 온풍기 안녕!.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

class Point
{
public:
	uint32_t x, y;
public:
	Point() { }
	Point(uint32_t x, uint32_t y) : x(x), y(y) { }
};

uint32_t R, C, K, W;

uint32_t place[20][20] = { 0, }; // 입력값으로 받은 공간
uint32_t place_temperature[20][20] = { 0, }; // 온도 분포 공간
bool place_wall_x[20][20] = { false, };
bool place_wall_y[20][20] = { false, };

// dir 반전 연산 정의
uint32_t inverseDir(uint32_t dir)
{
	// 오왼위아 => 왼오아위
	switch (dir)
	{
	case 1: return 2;
	case 2: return 1;
	case 3: return 4;
	case 4: return 3;
	}
	return NULL;
}
// dir 회전 연산 정의(좌 = L, 우 = R)
uint32_t turn(uint32_t dir, char _operator)
{
	if (_operator == 'L') // dir을 왼쪽으로 90도 회전
	{
		// 오왼위아 => 위아왼오
		switch (dir)
		{
		case 1: return 3;
		case 2: return 4;
		case 3: return 2;
		case 4: return 1;
		}
	}
	else
		return inverseDir(turn(dir, 'L'));
}
// coordinate가 범위를 벗어나지 않았는가?
bool isValid(Point* coordinate)
{
	return ((0 <= (signed)coordinate->x) && (coordinate->x < C) &&
		(0 <= (signed)coordinate->y) && (coordinate->y < R));
}

// dir 방향으로 coordinate 움직임, (벽이 막고있는 등의 이유로)못 움직이면 false리턴
bool move(Point* coordinate, uint32_t dir)
{
	Point result = *coordinate;

	// 오왼위아
	switch (dir)
	{
	case 1: 
		result.x++;
		if (!isValid(&result))
			return false;
		if (place_wall_y[result.y][result.x - 1])
			return false;
		break;
	case 2:
		result.x--;
		if (!isValid(&result))
			return false;
		if (place_wall_y[result.y][result.x])
			return false;
		break;
	case 3:
		result.y--;
		if (!isValid(&result))
			return false;
		if (place_wall_x[result.y + 1][result.x])
			return false;
		break;
	case 4:
		result.y++;
		if (!isValid(&result))
			return false;
		if (place_wall_x[result.y][result.x])
			return false;
		break;
	}

	*coordinate = result;
	return true;
}

/*
 * temperature : 확산 온도
 * coordinate : 처음엔 대상 히터의 좌표, 재귀시엔 온도의 확산 위치
 * return 히팅이미지(히터가 작동됐을 때 각 위치의 온도변화 값)
 */
uint32_t** heater_image_init(uint32_t temperature, Point coordinate, bool isRecur = false)
{
	static uint32_t dir; // 온풍기 방향값
	static uint32_t** result;

	// 처음이라면
	if (!isRecur)
	{
		// 초기화작업
		dir = place[coordinate.y][coordinate.x];

		result = new uint32_t*[R + 1];
		for (uint32_t i = 0; i < R; i++)
		{
			result[i] = new uint32_t[C + 1];
			for (uint32_t j = 0; j < C; j++)
				result[i][j] = 0;
		}
		if (!move(&coordinate, dir))
			return result;
	}
	if (temperature == 0) // 온도가 식으면
		return result; // 종료

	// 현 위치에 온도 확산
	result[coordinate.y][coordinate.x] = temperature;

	// dir의 왼쪽 대각선 방향으로 확산
	Point temp = coordinate;
	if (move(&temp, turn(dir, 'L')))
		if (move(&temp, dir))
			heater_image_init(temperature - 1, temp, true);

	// dir방향으로 확산
	temp = coordinate;
	if (move(&temp, dir))
		heater_image_init(temperature - 1, temp, true);

	// dir의 오른쪽 대각선 방향으로 확산
	temp = coordinate;
	if (move(&temp, turn(dir, 'R')))
		if (move(&temp, dir))
			heater_image_init(temperature - 1, temp, true);

	return result;
}
// 미리 계산된 히팅이미지 값으로 place_temperature를 데움
void heat(uint32_t** heater_images[400], uint32_t len)
{
	for (uint32_t k = 0; k < len; k++)
		for (uint32_t i = 0; i < R; i++)
			for (uint32_t j = 0; j < C; j++)
				place_temperature[i][j] += heater_images[k][i][j];
}
// place_temperature 온도 조절
void defuse()
{
	uint32_t origin_place_temperature[20][20];
	
	for (uint32_t i = 0; i < R; i++)
		for (uint32_t j = 0; j < C; j++)
			origin_place_temperature[i][j] = place_temperature[i][j];

	// 각 칸에 대해서 온도확산 계산
	Point coordinate;
	for (coordinate.y = 0; coordinate.y < R; coordinate.y++)
		for (coordinate.x = 0; coordinate.x < C; coordinate.x++)
		{
			for (uint32_t i = 1; i <= 4; i++)
			{
				Point temp = coordinate;
				if (move(&temp, i))
				{
					// 온도가 높은 곳에서 낮은 곳으로만
					if (origin_place_temperature[temp.y][temp.x] 
							< origin_place_temperature[coordinate.y][coordinate.x])
					{
						uint32_t delta = (origin_place_temperature[coordinate.y][coordinate.x]
							- origin_place_temperature[temp.y][temp.x]) / 4;

						place_temperature[temp.y][temp.x] += delta;
						place_temperature[coordinate.y][coordinate.x] -= delta;
					}
				}

			}
		}

	// 가장자리 온도 감소
	for (uint32_t i = 0; i < R; i++)
		for (uint32_t j = 0; j < C; j++)
			if ((i == 0 || j == 0 || i == R - 1 || j == C - 1) && 0 < place_temperature[i][j])
				place_temperature[i][j]--;
}

int main()
{
	cin >> R >> C >> K;

	for (uint32_t i = 0; i < R; i++)
		for (uint32_t j = 0; j < C; j++)
			cin >> place[i][j];

	cin >> W;
	for (uint32_t i = 0; i < W; i++)
	{
		uint32_t x, y;
		bool isVertical;
		cin >> x >> y >> isVertical;

		if (isVertical)
			place_wall_y[x - 1][y - 1] = true;
		else
			place_wall_x[x - 1][y - 1] = true;
	}

	/* 여기서부터 풀이 시작 */

	uint32_t cnt_chocolate = 0;

	/* 히팅이미지 구하기 */

	uint32_t** heater_images[400];
	uint32_t len_heater_images = 0;

	for (uint32_t i = 0; i < R; i++)
		for (uint32_t j = 0; j < C; j++)
			if (0 < place[i][j] && place[i][j] < 5) // 온풍기 발견
				heater_images[len_heater_images++] = heater_image_init(5, Point(j, i));

	bool K_complete = false;
	while (!K_complete && cnt_chocolate < 101)
	{
		heat(heater_images, len_heater_images);
		defuse();
		cnt_chocolate++;

		K_complete = true;
		for (uint32_t i = 0; i < R; i++)
			for (uint32_t j = 0; j < C; j++)
				if (place[i][j] == 5)
					if (place_temperature[i][j] < K)
					{
						i = R;
						j = C;
						K_complete = false;
					}
	}
	cout << cnt_chocolate;
}