#include <stdio.h>
int exchange(int *a, int i, int j){
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
int partition(int *a, int p, int r){
	int x = a[r];
	int i = p-1, j;
	for(j = p; j < r; j++){
		if(a[j] < x){
			i++;
			exchange(a, i, j);	//交换下标为 i和 j 两个数的位置  
		}
	}
	exchange(a, i+1, r);	 

	return i+1;
}
int quick_sort(int *a, int p, int r, int k, int *find)
{
	if(p < r){
		int x_index = partition(a, p, r); //获取主元素下标	
		printf("主元素下标x_index=%d\n", x_index);

		if(k == x_index){
			*find = 1;
			printf("find number k = %d\n", a[x_index]);
			return 0;
		}
		else if(k < x_index){
			quick_sort(a, p, x_index-1, k, find);
		}
		else if(k > x_index){
			quick_sort(a, x_index+1, r, k, find);
		}
	} 
}

 int main()
 {
 	int find = -1, k;				 
	scanf("%d", &k); 
	k = k-1;				
 	int a[] = {0,9,7,5,3,6,1};		//试验数组 
 	
 	quick_sort(a, 0, 6, k, &find);	//因为在整个递归过程中，存在x_index与k一直不相等的情况（实际上就是递归到底时，x恰好就是是k的相邻元素）。这里用find来标记是否相等 
	 								//不过无妨，到了最后，即便整个数组可能不是有序的，但是x_index和k所对应的数，已经恰好是第x_index大和第k大的数了，目的达成 
									//只需将对应下标k的数找出即可 

 	if(find == -1){					//find为-1说明没有在quick_sort没有找到 k 元素					
 		printf("find number k = %d\n", a[k]);
	 }
	 
/*打印当前数组元素的顺序与题目无关，仅仅是想看看数组最后的顺序 */ 
 	int i;
	for(i = 0; i <= 6; i++){
		printf("%d ", a[i]);
	}
 }
