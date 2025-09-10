////////////////////////////////////
//
// Performance Profiling merge sort
//
////////////////////////////////////



//InsertionSort, selecttion sort, bubble sort
//on 11aug2025 Merge sort
// take 10000 numbers as input
//use rand and srand
// use time.h header

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include <linux/perf_event.h>    /* Definition of PERF_* constants */
#include <linux/hw_breakpoint.h> /* Definition of HW_* constants */
#include <sys/syscall.h>         /* Definition of SYS_* constants */
#include <sys/ioctl.h>

void swap(int* x, int* y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void copyArr(int *arr, int iBegin, int iEnd, int *workArr){
    for(int i =iBegin; i < iEnd; i++)
        workArr[i] = arr[i];
}

void reverse(int *arr, int size){
	for (int i = 0; i < size/2; i++)
		arr[i] = arr[size-i-1];
}

int insertionSort(int *arr, int size){
    int i = 1;
    while(i < size){
        int j = i;
        while(j > 0 && arr[j-1] > arr[j]){
            swap(&arr[j], &arr[j-1]);
            j = j - 1;
        }
        i += 1;
    }
    return arr[size];
}

int selectionSort(int *arr, int size){
    int smallest;
    for(int i = 0; i < size-1; i++){
        smallest = i;
        for(int j = i+1; j < size; j++){
            if(arr[j] < arr[smallest])
                smallest = j;
        }
        if(smallest != i)
            swap(&arr[i], &arr[smallest]);
    }
    return arr[size];
}

int bubbleSort(int *arr, int size){
    int len = size;
    int newLen;
    while(len > 1){
        newLen = 0;
        for(int i = 1; i < len; i++){
            if(arr[i-1] > arr[i]){
                swap(&arr[i-1], &arr[i]);
                newLen = i;
            }
        }
        len = newLen;
    }
    return arr[size];
}

void topDownMerge(int *workArr, int iBegin,int iMid, int iEnd, int *arr){
    int i = iBegin, j = iMid;
    for(int k = iBegin; k < iEnd; k++){
        if(i < iMid && (j >= iEnd || arr[i] <= arr[j])){
            workArr[k] = arr[i];
            i++;
        } else{
            workArr[k] = arr[j];
            j++;
        }
    }
}

void topDownSplitMerge(int *workArr, int iBegin, int iEnd, int *arr){
    if(iEnd - iBegin <= 1)
        return;
    int iMid = (iEnd + iBegin) / 2;

    topDownSplitMerge(arr, iBegin, iMid, workArr);
    topDownSplitMerge(arr, iMid, iEnd, workArr);

    topDownMerge(workArr, iBegin, iMid, iEnd, arr);
}

void mergeSort(int *arr,int *workArr, int size){
    copyArr(arr, 0, size, workArr);
    topDownSplitMerge(arr, 0, size, workArr);
}

int insertionSortDesc(int *arr, int size){
    int i = 1;
    while(i < size){
        int j = i;
        while(j > 0 && arr[j-1] < arr[j]){
            swap(&arr[j], &arr[j-1]);
            j = j - 1;
        }
        i += 1;
    }
    return arr[size];
}

int selectionSortDesc(int *arr, int size){
    int smallest;
    for(int i = 0; i < size-1; i++){
        smallest = i;
        for(int j = i+1; j < size; j++){
            if(arr[j] > arr[smallest])
                smallest = j;
        }
        if(smallest != i)
            swap(&arr[i], &arr[smallest]);
    }
    return arr[size];
}

int bubbleSortDesc(int *arr, int size){
    int len = size;
    int newLen;
    while(len > 1){
        newLen = 0;
        for(int i = 1; i < len; i++){
            if(arr[i-1] < arr[i]){
                swap(&arr[i-1], &arr[i]);
                newLen = i;
            }
        }
        len = newLen;
    }
    return arr[size];
}

int main(){
	struct perf_event_attr bm;
	memset(&bm, 0, sizeof(bm));
	int lfd = -1;
	int mfd = -1;
	uint64_t branch_count;
	uint64_t branch_miss_count;

	bm.type = PERF_TYPE_HARDWARE;
	bm.size = sizeof(bm);
	bm.config = PERF_COUNT_HW_BRANCH_MISSES;
	bm.disabled = 1;
	bm.exclude_kernel = 1;
	bm.exclude_hv = 1;

    lfd = syscall(SYS_perf_event_open, &bm,
                     0, // pid: for calling process
                     -1, // cpuid: for any cpu
                     -1, // groud_id: -1 for leader group
                     0); // flags: no flags
	if (lfd == -1) {
		perror("ERROR opening leader");
		goto cleanup;
	};

	struct perf_event_attr bi;
	memset(&bi, 0, sizeof(bi));
	bm.type = PERF_TYPE_HARDWARE;
	bm.size = sizeof(bm);
	bm.config = PERF_COUNT_HW_BRANCH_INSTRUCTIONS;
	bm.disabled = 1;
	bm.exclude_kernel = 1;
	bm.exclude_hv = 1;

    mfd = syscall(SYS_perf_event_open, &bm,
                     0, // pid: for calling process
                     -1, // cpuid: for any cpu
                     lfd, // groud_id: for grouped stats
                     0); // flags: no flags
	if (mfd == -1) {
		perror("ERROR opening group");
		goto cleanup;
	};

	size_t size = 100 * 1000 * 1000;
	int *arr = malloc(sizeof(*arr) * size);
	int *workarray = malloc(sizeof(*arr) * size);
	for (size_t i = 0; i < size; i++)
		arr[size-i-1] = i;

	clock_t start = clock();

	ioctl(lfd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
	mergeSort(arr, workarray, size);
	ioctl(lfd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);

	read(lfd, &branch_miss_count, sizeof(branch_miss_count));
	read(mfd, &branch_count, sizeof(branch_count));
	printf("reversed array\n");
	printf("total branches: %lu\n", branch_count);
	printf("branch misses: %lu\n", branch_miss_count);
	printf("branch miss rate: %.3lf\n", ((double) branch_miss_count / branch_count) * 100);
	printf("\n");

	clock_t end = clock();

	double time_taken1 = (double) (end - start) / CLOCKS_PER_SEC;

	start = clock();

	ioctl(lfd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
	mergeSort(arr, workarray, size);
	ioctl(lfd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);

	read(lfd, &branch_miss_count, sizeof(branch_miss_count));
	read(mfd, &branch_count, sizeof(branch_count));
	printf("already sorted array\n");
	printf("total branches: %lu\n", branch_count);
	printf("branch misses: %lu\n", branch_miss_count);
	printf("branch miss rate: %.3lf\n", ((double) branch_miss_count / branch_count) * 100);
	printf("\n");

	end = clock();

	double time_taken2 = (double) (end - start) / CLOCKS_PER_SEC;

	for (size_t i = 0; i < size; i++)
		arr[i] = rand();
	start = clock();

	ioctl(lfd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
	mergeSort(arr, workarray, size);
	ioctl(lfd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);

	read(lfd, &branch_miss_count, sizeof(branch_miss_count));
	read(mfd, &branch_count, sizeof(branch_count));
	printf("randomized array\n");
	printf("total branches: %lu\n", branch_count);
	printf("branch misses: %lu\n", branch_miss_count);
	printf("branch miss rate: %.3lf\n", ((double) branch_miss_count / branch_count) * 100);
	printf("\n");

	end = clock();

	double time_taken3 = (double) (end - start) / CLOCKS_PER_SEC;

	printf("%lf %lf %lf\n", time_taken1, time_taken2, time_taken3);

cleanup:
	if (lfd != -1) close(lfd);
	if (mfd != -1) close(lfd);

	return 0;


    FILE *file_pointer1, *file_pointer2, *file_pointer3, *file_pointer4;
    file_pointer1 = fopen("insertionSort.dat", "w");
    file_pointer2 = fopen("selectionSort.dat", "w");
    file_pointer3 = fopen("bubbleSort.dat", "w");
    file_pointer4 = fopen("mergeSort.dat", "w");
    int array_of_sizes[] = {10000, 20000, 30000, 40000, 50000, 2000000};
    int something=0;

//    printf("Insertion Sort:\n");
//
//    while(something<5){
//        fprintf(file_pointer1, "%d ", array_of_sizes[something]);
//        int arr[array_of_sizes[something]];
//        printf("\nFor %d inputs:\n", array_of_sizes[something]);
//        clock_t start, end;
//        srand(time(0));
//        for(int i =0; i<10000; i++){
//            arr[i] = rand();
//        }
//        int size=sizeof(arr)/sizeof(arr[0]);
//
//        start = clock();
//        insertionSort(arr, size);
//        end = clock();
//	    double difference;
//	    difference = (double)(end - start) / CLOCKS_PER_SEC;
//	    printf("Time difference: %lf\n", difference);
//        fprintf(file_pointer1, "%lf ", difference);
//
//	    start = clock();
//	    insertionSort(arr, size);
//	    end = clock();
//	    difference = (double)(end - start) / CLOCKS_PER_SEC;
//	    printf("Time difference: %lf\n", difference);
//        fprintf(file_pointer1, "%lf ", difference);
//
//	    start = clock();
//	    insertionSortDesc(arr, size);
//	    end = clock();
//	    difference = (double)(end - start) / CLOCKS_PER_SEC;
//	    printf("Time difference: %lf\n", difference);
//        fprintf(file_pointer1, "%lf\n", difference);
//        something++;
//    }
//
//    printf("\nSelection Sort:\n");
//    something = 0;
//    while(something<5){
//        fprintf(file_pointer2, "%d ", array_of_sizes[something]);
//        int arr[array_of_sizes[something]];
//        printf("\nFor %d inputs:\n", array_of_sizes[something]);
//        clock_t start, end;
//        srand(time(0));
//        for(int i =0; i<10000; i++){
//            arr[i] = rand();
//        }
//        int size=sizeof(arr)/sizeof(arr[0]);
//
//        start = clock();
//        selectionSort(arr, size);
//        end = clock();
//        double difference;
//        difference = (double)(end - start) / CLOCKS_PER_SEC;
//        printf("Time difference: %lf\n", difference);
//        fprintf(file_pointer2, "%lf ", difference);
//
//        start = clock();
//        selectionSort(arr, size);
//        end = clock();
//        difference = (double)(end - start) / CLOCKS_PER_SEC;
//        printf("Time difference: %lf\n", difference);
//        fprintf(file_pointer2, "%lf ", difference);
//
//        start = clock();
//        selectionSortDesc(arr, size);
//        end = clock();
//        difference = (double)(end - start) / CLOCKS_PER_SEC;
//        printf("Time difference: %lf\n", difference);
//        fprintf(file_pointer2, "%lf\n", difference);
//        something++;
//    }
//
//    printf("\nBubble Sort:\n");
//    something = 0;
//    while(something<5){
//        fprintf(file_pointer3, "%d ", array_of_sizes[something]);
//        int arr[array_of_sizes[something]];
//        printf("\nFor %d inputs:\n", array_of_sizes[something]);
//        clock_t start, end;
//        srand(time(0));
//        for(int i =0; i<10000; i++){
//            arr[i] = rand();
//        }
//        int size=sizeof(arr)/sizeof(arr[0]);
//
//        start = clock();
//        bubbleSort(arr, size);
//        end = clock();
//        double difference;
//        difference = (double)(end - start) / CLOCKS_PER_SEC;
//        printf("Time difference: %lf\n", difference);
//        fprintf(file_pointer3, "%lf ", difference);
//
//        start = clock();
//        bubbleSort(arr, size);
//        end = clock();
//        difference = (double)(end - start) / CLOCKS_PER_SEC;
//        printf("Time difference: %lf\n", difference);
//        fprintf(file_pointer3, "%lf ", difference);
//
//        start = clock();
//        bubbleSortDesc(arr, size);
//        end = clock();
//        difference = (double)(end - start) / CLOCKS_PER_SEC;
//        printf("Time difference: %lf\n", difference);
//        fprintf(file_pointer3, "%lf\n", difference);
//        something++;
//    }

    printf("\nMerge Sort:\n");
    something = 0;
    while(something<6){
        fprintf(file_pointer4, "%d ", array_of_sizes[something]);
        // int arr[array_of_sizes[something]];
		int *arr = malloc(sizeof(int) * array_of_sizes[something]);
        int workarr[array_of_sizes[something]];
        printf("\nFor %d inputs:\n", array_of_sizes[something]);
        clock_t start, end;
        srand(time(0));
        for(int i =0; i<array_of_sizes[something]; i++){
            arr[i] = rand();
        }
        // size_t size=sizeof(arr)/sizeof(arr[0]);

        start = clock();
        mergeSort(arr, workarr, array_of_sizes[something]);
        end = clock();
        double difference;
        difference = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Time difference: %lf\n", difference);
        fprintf(file_pointer4, "%lf ", difference);

        start = clock();
        mergeSort(arr, workarr, array_of_sizes[something]);
        end = clock();
        difference = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Time difference: %lf\n", difference);
        fprintf(file_pointer4, "%lf ", difference);

		reverse(arr, array_of_sizes[something]);
        start = clock();
        mergeSort(arr, workarr, array_of_sizes[something]);
        end = clock();
        difference = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Time difference: %lf\n", difference);
        fprintf(file_pointer4, "%lf\n", difference);
        something++;
    }

    fclose(file_pointer1);
    fclose(file_pointer2);
    fclose(file_pointer3);
    fclose(file_pointer4);

    return 0;
}
