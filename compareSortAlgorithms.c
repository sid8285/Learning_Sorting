#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;


void merge(int pData[], int l, int m, int r)
{
	//in this "l" is the first number in the array (index 0), "m" is the middle digit, and "r" is the last index in the array
	//declaring new variables n1 and n2 to split up the array and sort
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

	//filling our newly created arrays with the info from the previous array
    for (i = 0; i < n1; i++)
        L[i] = pData[l + i];
    for (j = 0; j < n2; j++)
        R[j] = pData[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
	//comparing the two given elements and placing one in front of the other
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            pData[k] = L[i];
            i++;
        }
        else {
            pData[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        pData[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        pData[k] = R[j];
        j++;
        k++;
    }

    extraMemoryAllocated += n1 * sizeof(int) + n2 * sizeof(int);

    free(L);
    free(R);
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	//calculating the middle value in which the array will be split and compared
	if (l < r) {
        int m = l + (r - l) / 2;
		
	//using recursive calls to sort the array by breaking it down to smaller pieces	
        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);
        merge(pData, l, m, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, j, key;
    for (i = 1; i < n; i++) {
        key = pData[i];
        j = i - 1;
	    //finds the correct spot in the array to insert the sorted integer into
        while (j >= 0 && pData[j] > key) {
            pData[j + 1] = pData[j];
            j = j - 1;
        }
	//pushes the sorted digit into its correct spot in the array    
        pData[j + 1] = key;
    }

    extraMemoryAllocated += n * sizeof(int);
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int i, j;
	//outer loop to determine the number of passes needed to prperly sort the array
    for (i = 0; i < n - 1; i++) {
	    //inner loop used to go through the array index for comparison purposes
        for (j = 0; j < n - i - 1; j++) {
		//the comparison process; seeing if the space before is greater than the space after and swapping the value if so
            if (pData[j] > pData[j + 1]) {
                int temp = pData[j];
                pData[j] = pData[j + 1];
                pData[j + 1] = temp;
            }
        }
    }

    extraMemoryAllocated += n * sizeof(int);
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int i, j, min_idx;
	//outer loop to make the correct number of passes for the given array
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
	    //inner loop and logic to compare values and sort
        for (j = i + 1; j < n; j++) {
            if (pData[j] < pData[min_idx]) {
                min_idx = j;
            }
        }
	    //swapping technique to sort the variables correctly
        int temp = pData[min_idx];
        pData[min_idx] = pData[i];
        pData[i] = temp;
    }

    extraMemoryAllocated += n * sizeof(int);
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		//reading the newly sorted file and displaying it when the program runs
        for (int i = 0; i < dataSz; i++) {
            fscanf(inFile, "%d", &(*ppData)[i]);
        }
	}
	
    fclose(inFile);
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
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
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
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
