"""
dirt    = 0 = horizon
        = 1 = vertical
        = 2 = diagonal
"""
def recur(place, loc=(0, 1), dirt=0) :
    horizon = place[loc[0]][loc[1] + 1]
    vertical = place[loc[0] + 1][loc[1]]
    diagonal = place[loc[0] + 1][loc[1] + 1]
    
    result = 0

    # 가로 방향 이동
    if horizon == 0 and (dirt==0 or dirt==2) :
        result += recur(place, (loc[0], loc[1] + 1), 0)
    
    # 세로 방향 이동
    if vertical == 0 and (dirt==1 or dirt==2):
        result += recur(place, (loc[0] + 1, loc[1]), 1)

    # 대각선 방향 이동
    if horizon == 0 and vertical == 0 and diagonal == 0:
        result += recur(place, (loc[0] + 1, loc[1] + 1), 2)

    # 목적지 도착
    if diagonal == 2 :
        return 1
    
    return result

N = int(input())
place = []

for i in range(N) :
    place.append(list(map(int, input().split())))
    place[i].append(1) # 막힌 부분은 1로 둘러쌈

place.append([1 for _ in range(N)]) # 막힌 부분은 1로 둘러쌈
place[-1].append(2) # 도착지점은 2로 표시

print(recur(place))