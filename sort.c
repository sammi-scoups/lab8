#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// but first don't I need to make a heapif function? thats what I thought
// extraMemoryAllocated counts bytes of memory allocated

void heapify (int arr[], int a, int b)
{
	int max = b; 
	int lchild= 2*b + 1;
	int rchild = 2*b + 2;

	if (lchild < a && (arr[lchild] > arr[max]))
		max = lchild;

	if (rchild < a && (arr[rchild] > arr[max]))
		max = rchild;
	
	if (max != b)
	{
		int temp = arr[b];
		arr[b]= arr[max];
		arr[max] = temp;
		heapify(arr, a, max);
	}
}
void heapSort(int arr[], int n)
{
	// creates the heap
	
	for (int c = (n/2) - 1; c >= 0; c--)
		heapify(arr,n,c);

	// takes the numbers from heap in order
	// for (int d =0; n - 1; d--)
	// {
	//  	int temp = arr[0];
	//  	arr[0]= arr[d];
	//  	arr[d] = temp;
	//  	heapify(arr, n, d);
	// }

}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if (l < r)
	{
		int m = (l + r)/2;
		mergeSort(pData, l, m);
		mergeSort(pData, m+1, r);
	
	
		int a, b, c;
		int s1 = m - l + 1;
		int s2 = r - m; 

		//arrays for only temporary !Remember to free at end of fucntion
		int* lA = (int*)malloc(s1*sizeof(int));
		int* rA = (int*)malloc(s2*sizeof(int));
		extraMemoryAllocated += (s1 *sizeof(lA)) + (s2* sizeof(rA));
		
		for(a = 0; a < s1; a++)
		{
			lA[a] = pData[l + a];
		}
		for (b = 0; b < s2; b++)
		{
			rA[b] = pData[m + 1 + b];
		}
		
		a = 0, b = 0;
		c = l;

		do 
		{
			if (lA[a] <= rA[b])
			{
				pData[c] = lA[a];
				a++;
			} else 
			{
				pData[c] = rA[b];
				b++;
			}
			c++;
		} while(a < s1 && b < s2);
		
		while (a < s1)
		{
			pData[c] = lA[a];
			a++;
			c++;
		}

		while (b < s2)
		{
			pData[c] = rA[b];
			b++;
			c++;
		}

	free(lA);
	free(rA);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		if (i>= dataSz)
		{
			printf("\n\n");
		return;
		}
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}