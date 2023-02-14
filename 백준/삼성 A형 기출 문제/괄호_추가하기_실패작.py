import copy

"""
string formula : 수식
list priority : 연산자에 대한 우선순위 정보
"""
def calculate(formula, priority) :

    operators = ['+', '-', '*', '/']

    priority = copy.deepcopy(priority)

    for i in range(len(priority)) :
        """우선순위 배열의 최댓값 인덱스 구하기"""
        max = -1
        max_idx = 0
        for j in range(0, len(priority)) :
            if priority[j] > max :
                max = priority[j]
                max_idx = j
        
        del priority[max_idx]

        """수식에서 max_idx+1번째 연산자와 피연산자를 추출함"""
        operator_idx = -1
        for j in range(0, len(formula)) : # 수식에서 문자 하나씩 꺼내면서
            if formula[j] in operators : # 이게 연산자인지 확인
                operator_idx += 1 # 찾은 연산자의 개수를 저장
                if max_idx == operator_idx :
                    operator_idx = j # 인덱스를 저장
                    break
        
        # 이 시점에서 operator_idx가 수식 문자열에서 연산자의 인덱스임, 피연산자를 추출할 차례

        operand_signed = False
        operand1 = 0
        digit = 1
        single_formula_start_idx = 0
        for j in range(operator_idx-1, -1, -1) :
            if '0' <= formula[j] <= '9' :
                operand1 += digit * int(formula[j])
                digit *= 10
            elif formula[j] == ':' : # :는 음수라는 뜻
                operand_signed = True # 나중에 -1을 곱함
            else :
                single_formula_start_idx = j + 1 # 이번 반복에서 계산할 수식의 시작점 인덱스
                break
        if operand_signed :
            operand1 *= -1
        
        # 오른쪽 피연산자 추출은 높은 자릿수부터 읽어들이기 때문에 각 자릿수를 뽑아내 저장해뒀다가 합치는 식으로 진행합니다
        operand_signed = False
        digit_list = []
        single_formula_end_idx = len(formula)
        for j in range(operator_idx+1, len(formula)) :
            if '0' <= formula[j] <= '9' : # 숫자라면
                digit_list.append(int(formula[j])) # 자릿수 리스트에 저장
            elif formula[j] == ':' : # 음수라면
                operand_signed = True # 나중에 -1을 곱함
            else :
                single_formula_end_idx = j # 이번 반복에서 계산할 수식의 종점 인덱스
                break
        operand2 = 0
        for j in range(len(digit_list)) :
            operand2 += digit_list.pop() * (10 ** j) # 자릿수별로 따로따로 모은걸 하나로 합침
        if operand_signed :
            operand2 *= -1
        # 이시점에서 operand1과 operand2가 추출됨

        """해당하는 연산 수행"""
        if formula[operator_idx] == '+':
            result = operand1 + operand2
        elif formula[operator_idx] == '-' :
            result = operand1 - operand2
        elif formula[operator_idx] == '*' :
            result = operand1 * operand2
        elif formula[operator_idx] == '/' :
            result = operand1 / operand2

        """연산결과를 수식에 반영"""
        formula = list(formula)
        del formula[single_formula_start_idx:single_formula_end_idx]
        formula.insert(single_formula_start_idx, str(result).replace('-', ':')) # 뺄셈 연산자와 구분하기 위해 음수표현은 :로 대체합니다
        formula = ''.join(formula)
    
    return result

# 0부터 length까지의 정수를 배열해서 만들수 있는 모든 경우의 순열 생성
def getCase(length) :
    
    num_lists = []
    num_list = [ -1 for i in range(length) ]

    def recursive(i) : # i가 재귀 반복 횟수
        nonlocal num_list
        nonlocal num_lists

        for j in range(length) :
            if j not in num_list : # 순열에 중복된 숫자가 발견되지 않았다면
                num_list[i] = j # 순열에 추가

                if i == 0 : # 순열을 끝까지 다 채웠다면
                    num_lists.append(copy.deepcopy(num_list)) # 순열 리스트에 저장
                else : # 아직 덜 채웠다면
                    recursive(i - 1) # 다음 자리를 채움

                num_list[i] = -1 # 완성 후에는 다음 반복을 위해 자리를 비움


        return

    recursive(length - 1)
    return num_lists

leng = int(input())
formula = input()

max_num = calculate(formula, [ i for i in range(leng // 2) ])
max_priority = [ i for i in range(leng // 2) ]

for i in getCase(leng // 2):
    tmp = calculate(formula, i)
    if max_num < tmp :
        max_num = tmp
        max_priority = i

print(max_num)
print(max_priority)