sort=[0]*10;
def merge_sort(A,left,right):
    if left<right:
        mid=(left+right)//2
        merge_sort(A,left,mid)
        merge_sort(A,mid+1,right)
        merge(A,left,mid,right)
def merge(A,left,mid,right):
    left_1=left
    mid_1=mid+1
    left_2=left
    tmp=left
    while(left_1<=mid and mid_1<=right):
        if(A[left_1]<=A[mid_1]):
            sort[left_2]=A[left_1]
            left_2+=1
            left_1+=1
        else:
            sort[left_2]=A[mid_1]
            left_2+=1
            mid_1+=1
    if(left_1>mid):
        tmp=mid_1
        while(tmp<=right):
            sort[left_2]=A[tmp]
            left_2+=1
            tmp+=1
        
    else:
        tmp=left_1
        while(tmp<=mid):
            sort[left_2]=A[tmp]
            left_2+=1
            tmp+=1
    tmp=left
    while(left<=right):
        A[tmp]=sort[tmp]
        tmp+=1
        left+=1
A=[21,0,1,10,12,20,20,3,25,52]
merge_sort(A,0,7)
print(A)
        
    
