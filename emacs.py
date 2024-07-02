n, m = map(int, input().split())
mat = []
for i in range(n):
    red = input()
    mat.append(red)

rj = 0
for i in range(n):
    for j in range(m):
        if mat[i][j] == '*':
            rub = 1
            if i + 1 < n and mat[i + 1][j] != '.':
                rub = 0
            if j + 1 < m and mat[i][j + 1] != '.':
                rub = 0
            if i + 1 < n and j + 1 < m and mat[i + 1][j + 1] != '.':
                rub = 0
            rj += rub
print(rj)
