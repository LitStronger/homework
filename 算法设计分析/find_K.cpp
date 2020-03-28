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
			exchange(a, i, j);	//�����±�Ϊ i�� j ��������λ��  
		}
	}
	exchange(a, i+1, r);	 

	return i+1;
}
int quick_sort(int *a, int p, int r, int k, int *find)
{
	if(p < r){
		int x_index = partition(a, p, r); //��ȡ��Ԫ���±�	
		printf("��Ԫ���±�x_index=%d\n", x_index);

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
 	int a[] = {0,9,7,5,3,6,1};		//�������� 
 	
 	quick_sort(a, 0, 6, k, &find);	//��Ϊ�������ݹ�����У�����x_index��kһֱ����ȵ������ʵ���Ͼ��ǵݹ鵽��ʱ��xǡ�þ�����k������Ԫ�أ���������find������Ƿ���� 
	 								//�����޷���������󣬼�������������ܲ�������ģ�����x_index��k����Ӧ�������Ѿ�ǡ���ǵ�x_index��͵�k������ˣ�Ŀ�Ĵ�� 
									//ֻ�轫��Ӧ�±�k�����ҳ����� 

 	if(find == -1){					//findΪ-1˵��û����quick_sortû���ҵ� k Ԫ��					
 		printf("find number k = %d\n", a[k]);
	 }
	 
/*��ӡ��ǰ����Ԫ�ص�˳������Ŀ�޹أ��������뿴����������˳�� */ 
 	int i;
	for(i = 0; i <= 6; i++){
		printf("%d ", a[i]);
	}
 }
