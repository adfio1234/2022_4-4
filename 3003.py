piece=[1,1,2,2,2,8]
chess=list(map(int,input().split()))
result=[]

for i in range(0,6):
   if piece[i]==chess[i]:
       result.append(0)
   else:
        result.append(piece[i]-chess[i])
for i in range(0,6):
    print(result[i],end=' ')
