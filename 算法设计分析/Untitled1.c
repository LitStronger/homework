#include <stdio.h>
#include <string.h>
int main()
{
	int j, i, key;//key:´ı²åÈëÖµ
	int arr[] = {8,2,4,9,3,6};
	int len = sizeof(arr)/4;
	
	for(j = 1; j < len; j++)
	{
		key = arr[j];
		i = j-1;
		while(i>=0 && key < arr[i])
		{
			arr[i+1] = arr[i];
			i = i-1;
		}
		arr[i+1] = key;
	}
	//output
	for(i = 0; i < len; i++)
		printf("%d ", arr[i]);
	return 0; 
}
