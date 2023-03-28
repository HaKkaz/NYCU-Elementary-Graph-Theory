from collections import defaultdict
n = int(input())
d = defaultdict(int)
for x in list(map(int,input().split())):
	d[x]+=1

count = sorted([(x[1],x[0]) for x in d.items()])
print(count[-1][1] , count[-1][0])