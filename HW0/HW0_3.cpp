n,a,b,c = map(int,input().split())
val = [b,a,c]
match = [ list(map(int,input().split())) for _ in range(n)]
score = [0 for _ in range(n)];

for i in range(n):
	for j in range(n):
		if i == j :
			continue
		score[i] += val[match[i][j]]

print(*score)