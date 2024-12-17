// 열쇠.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <cstring>
#include <cstdlib>

#define MAX_hw 100

using namespace std;

int h, w;
char map[MAX_hw][MAX_hw + 1];
bool key_bundle[100];
int res;

typedef struct Point {
    int h, w;
} Point;

// coord_rchable_obj = 현재 무빙 턴에서 접근할 수 있는 오브젝트의 좌표
Point coord_rchable_obj[MAX_hw * MAX_hw];
int len_coord_rchable_obj;

void search_obj(Point coord)
{
    switch (map[coord.h][coord.w])
    {
    case '.':
        // '-' = 탐색된 공간이라고 표시
        map[coord.h][coord.w] = '-';

        // 상하좌우로 공간 탐색
        if (coord.h > 0)
            search_obj(Point{ coord.h - 1, coord.w });
        if (coord.h < h - 1)
            search_obj(Point{ coord.h + 1, coord.w });
        if (coord.w > 0)
            search_obj(Point{ coord.h, coord.w - 1 });
        if (coord.w < w - 1)
            search_obj(Point{ coord.h, coord.w + 1 });
    case '*': case '-': break;
    default:
        coord_rchable_obj[len_coord_rchable_obj++] = coord;
    }
}
// 발견한 오브젝트 처리
bool handle_obj()
{
    bool ret = false; // ret = 지도에 변동사항이 생겼는가?

    for (int i = 0; i < len_coord_rchable_obj; i++)
    {
        Point coord_obj = coord_rchable_obj[i];
        char* obj = &map[coord_obj.h][coord_obj.w];

        switch (*obj)
        {
            // 오브젝트가 문서라면
        case '$':
            res++;
            *obj = '.';
            ret = true;
            break;
        default:
            // 오브젝트가 문이라면
            if ('A' <= *obj && *obj <= 'Z')
            {
                // 가지고 있는 열쇠로 문열기
                if (key_bundle[*obj - 'A'])
                {
                    *obj = '.';
                    ret = true;
                }
            }
            // 오브젝트가 열쇠라면
            else if ('a' <= *obj && *obj <= 'z')
            {
                // 열쇠 꾸러미에 열쇠 추가
                key_bundle[*obj - 'a'] = true;
                *obj = '.';
                ret = true;
            }
        }
    }

    return ret;
}
bool move_forward()
{
    len_coord_rchable_obj = 0;

    for (int i = 0; i < w; i++)
        search_obj(Point{ 0, i });
    for (int i = 1; i < h - 1; i++)
    {
        search_obj(Point{ i, 0 });
        search_obj(Point{ i, w - 1 });
    }
    for (int i = 0; i < w; i++)
        search_obj(Point{ h - 1, i });

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (map[i][j] == '-')
                map[i][j] = '.';
    return handle_obj();
}
void solve()
{
    res = 0;
    for (int i = 0; i < sizeof(key_bundle); i++)
        key_bundle[i] = false;

    cin >> h >> w;
    for (int i = 0; i < h; i++)
        cin >> map[i];

    char key_bundle_char[100];
    memset(key_bundle_char, NULL, sizeof(key_bundle_char));
    cin >> key_bundle_char;

    if (key_bundle_char[0] != '0')
    {
        const unsigned int len_key_bundle = strlen(key_bundle_char);
        for (int i = 0; i < len_key_bundle; i++)
            key_bundle[key_bundle_char[i] - 'a'] = true;
    }

    while (move_forward());

    cout << res << endl;
}
int main()
{
    int T;
    cin >> T;

    for (int i = 0; i < T; i++)
        solve();
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
