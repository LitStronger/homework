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
			exchange(a, i, j);
		}
	}
	exchange(a, i+1, r);
	return i+1;
}
int quick_sort(int *a, int p, int r)
{
	if(p < r){
		int q = partition(a, p, r);
		quick_sort(a, p, q-1);
		quick_sort(a, q+1, r);
	} 

}

 int main()
 {
 	int a[] = {0,6,5,4,3,2,1};
 	quick_sort(a, 0, 6);
 	int i;
	for(i = 0; i <= 6; i++){
		printf("%d ", a[i]);
	}
 }
