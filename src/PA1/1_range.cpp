#include <cstdio>

int search(int*, int, int, int);
void quick_sort(int*, int, int);
int pivot(int* _elem, int lo, int hi);
void merge_sort(int*, int, int);
void merge(int*, int, int, int);

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int* nums = new int[n + 1];
    for (int i = 0; i < n; ++i) {
        int num;
        scanf("%d", &num);
        nums[i] = num;
    }
    merge_sort(nums, 0, n);
    for (int i = 0; i < m; ++i) {
        int lo, hi;
        scanf("%d%d", &lo, &hi);
        int l = search(nums, 0, n, lo - 1);
        int h = search(nums, 0, n, hi);
        printf("%d\n", h - l);
    }
    delete[] nums;
    return 0;
}

void merge_sort(int* nums, int lo, int hi) {
    if (hi - lo < 2) return;
    int mi = (lo + hi) >> 1;
    merge_sort(nums, lo, mi);
    merge_sort(nums, mi, hi);
    merge(nums, lo, mi, hi);
}

void merge(int* nums, int lo, int mi, int hi) {
    int* temp = new int[hi - lo];
    int i = lo, j = mi, k = 0;
    while (i < mi && j < hi) {
        if (nums[i] < nums[j])
            temp[k++] = nums[i++];
        else
            temp[k++] = nums[j++];
    }
    while (i < mi) temp[k++] = nums[i++];
    while (j < hi) temp[k++] = nums[j++];
    i = 0;
    while (lo < hi) nums[lo++] = temp[i++];
    delete[] temp;
}

void quick_sort(int* nums, int lo, int hi) {
    if (hi - lo < 2) return;
    int piv = pivot(nums, lo, hi - 1);
    int i = lo, j = piv - 1;
    while (i <= j) {
        while (i <= j && nums[i] < nums[piv]) ++i;
        while (i <= j && nums[j] >= nums[piv]) --j;
        if (i < j) {
            nums[i] ^= nums[j];
            nums[j] ^= nums[i];
            nums[i] ^= nums[j];
        }
    }
    nums[i] ^= nums[piv];
    nums[piv] ^= nums[i];
    nums[i] ^= nums[piv];
    quick_sort(nums, i + 1, hi);
    quick_sort(nums, lo, i);
}

int pivot(int* _elem, int lo, int hi) {
    int mi = (lo + hi) >> 1;
    if (_elem[mi] < _elem[lo]) {
        _elem[lo] ^= _elem[mi];
        _elem[mi] ^= _elem[lo];
        _elem[lo] ^= _elem[mi];
    }
    if (_elem[mi] < _elem[hi]) {
        _elem[mi] ^= _elem[hi];
        _elem[hi] ^= _elem[mi];
        _elem[mi] ^= _elem[hi];
    }
    return hi;
}

int search(int* nums, int lo, int hi, int e) {
    while (lo < hi) {
        int mi = (lo + hi) / 2;
        if (e < nums[mi]) {
            hi = mi;
        }
        else {
            lo = mi + 1;
        }
    }
    return lo - 1;
}