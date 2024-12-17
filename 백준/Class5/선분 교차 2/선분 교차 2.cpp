#include <iostream>

using namespace std;

typedef struct Point {
	long long x;
	long long y;
} Point;
typedef struct Rect {
	long long bigX, smallX, bigY, smallY;
} Rect;
bool checkPointInRect(Rect rect, Point point)
{
	if (point.y < rect.smallY || rect.bigY < point.y || point.x < rect.smallX || rect.bigX < point.x)
		return false;
	else
		return true;
}
int main() {
	Point L1p1, L1p2, L2p1, L2p2;
	cin >> L1p1.x >> L1p1.y >> L1p2.x >> L1p2.y;
	cin >> L2p1.x >> L2p1.y >> L2p2.x >> L2p2.y;

	Rect rectL1, rectL2;
	rectL1.bigX = max(L1p1.x, L1p2.x);
	rectL1.smallX = min(L1p1.x, L1p2.x);
	rectL1.bigY = max(L1p1.y, L1p2.y);
	rectL1.smallY = min(L1p1.y, L1p2.y);

	rectL2.bigX = max(L2p1.x, L2p2.x);
	rectL2.smallX = min(L2p1.x, L2p2.x);
	rectL2.bigY = max(L2p1.y, L2p2.y);
	rectL2.smallY = min(L2p1.y, L2p2.y);

	if ((L1p1.x == L2p1.x && L1p1.y == L2p1.y) ||
		(L1p1.x == L2p2.x && L1p1.y == L2p2.y) ||
		(L1p2.x == L2p1.x && L1p2.y == L2p1.y) ||
		(L1p2.x == L2p2.x && L1p2.y == L2p2.y))
	{
		cout << 1 << endl;
		return 0;
	}
	long long ax, ay, bx, by, cx, cy, dx, dy;
	ax = L2p1.x - L1p1.x;
	ay = L2p1.y - L1p1.y;
	bx = L1p2.x - L2p1.x;
	by = L1p2.y - L2p1.y;
	cx = L2p2.x - L1p1.x;
	cy = L2p2.y - L1p1.y;
	dx = L1p2.x - L2p2.x;
	dy = L1p2.y - L2p2.y;

	// 외적 방향 계산
	long long d1 = (ax * by - ay * bx);
	if (d1 != 0)
		d1 /= abs(d1);
	long long d2 = (cx * dy - cy * dx);
	if (d2 != 0)
		d2 /= abs(d2);

	ax *= -1;
	ay *= -1;
	dx *= -1;
	dy *= -1;

	long long d3 = (ax * cy - ay * cx);
	if (d3 != 0)
		d3 /= abs(d3);
	long long d4 = (bx * dy - by * dx);
	if (d4 != 0)
		d4 /= abs(d4);

	// 두 선분이 일반적인 모양으로 서로 교차하는 경우
	if (d1 * d2 == -1 && d3 * d4 == -1)
		cout << 1 << endl;
	// 어느 한 선분을 쭉 늘린 직선위에 다른 선분의 점이 하나만 걸쳐있는 경우
	else if ((d1 * d2 == 0) ^ (d3 * d4 == 0))
	{
		// 벡터 방향이 같다면 교차함
		if (((ax * cx > 0 || (ax == 0 && cx == 0)) && (ay * cy > 0 || (ay == 0 && cy == 0))) ||
			((bx * dx > 0 || (bx == 0 && dx == 0)) && (by * dy > 0 || (by == 0 && dy == 0))))
			cout << 1 << endl;
		else if (((-ax * bx > 0 || (-ax == 0 && bx == 0)) && (-ay * by > 0 || (-ay == 0 && by == 0))) ||
			((cx * -dx > 0 || (cx == 0 && -dx == 0)) && (cy * -dy > 0 || (cy == 0 && -dy == 0))))
			cout << 1 << endl;
		// 벡터 방향이 다르다면 교차하지 않음
		else
			cout << 0 << endl;
	}
	// 두 선분이 한 직선 상에 존재하는 경우
	else if (d1 * d2 == 0 && d3 * d4 == 0)
	{
		if (checkPointInRect(rectL1, L2p1) ||
			checkPointInRect(rectL1, L2p2) ||
			checkPointInRect(rectL2, L1p1) ||
			checkPointInRect(rectL2, L1p2))
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}
	else
		cout << 0 << endl;

	return 0;
}