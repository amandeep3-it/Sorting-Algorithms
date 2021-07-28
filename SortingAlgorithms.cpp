#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
####################
##### Counting Sort
####################
*/

template<class T> void CountingSort(vector<T>& A, int const k) {
    vector<T> B (A.size()), C (k + 1);

    for (int i=0; i<k; i++) C[i] = 0;
    
    for (int j=0; j<A.size(); j++) C[A[j]]++;

    for (int i=1; i<=k; i++) C[i] += C[i - 1];

    for (int j=(A.size() - 1); j>=0; j--) {
        B[C[A[j]] - 1] = A[j];
        C[A[j]]--;
    }
    A = B;
}

template<class T> void CountingSort(vector<T>& A) {
    vector<T> B = {};

    for (int j=0; j<A.size(); j++) {
        bool add = true;
        for (int i=0; i<B.size(); i++) {
            if (A[j] == B[i]) {
                add = false;
                break;
            }
        }
        if (add) B.push_back(A[j]);
    }

    CountingSort(A, B.size());
}

/*
#########################
##### Insertion Sort
#########################
*/

template<class T> void InsertionSort(vector<T>& A) {
    for (int j=1; j<A.size(); j++) {
        const T key = A[j];
        int i = j - 1;
        while ((i >= 0) && (A[i] > key)) {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
    }
}

/*
####################
##### Merge Sort
####################
*/

template<class T> void Merge(vector<T>& A, int const p, int const q, int const r) {
    const int n1 = q - p + 1, n2 = r - q;

    T L[n1], R[n2];

    for (int i=0; i<n1; i++) L[i] = A[p + i];
    for (int j=0; j<n2; j++) R[j] = A[q + j + 1];

    int i = 0, j = 0, k = p;

    while ((i < n1) && (j < n2)) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

template<class T> void MergeSort(vector<T>& A, int const p, int const r) {
    if (p < r) {
        const int q = p + ((r - p) / 2);
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

template<class T> void MergeSort(vector<T>& A) { MergeSort(A, 0, A.size() - 1); }

/*
#########################
##### Rand Quick Sort
#########################
*/

template<class T> int Partition(vector<T>& A, int const p, int const r) {
    const T x = A[r];
    int i = p - 1;
    for (int j=p; j<=(r - 1); j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

template<class T> int RandPartition(vector<T>& A, int const p, int const r) {
    swap(A[r], A[rand() % (((r - p) + 1) + p)]);
    return Partition(A, p, r);
}

template<class T> void RandQuickSort(vector<T>& A, int const p, int const r) {
    if (p < r) {
        const int q = RandPartition(A, p, r);
        RandQuickSort(A, p, q - 1);
        RandQuickSort(A, q + 1, r);
    }
}

template<class T> void RandQuickSort(vector<T>& A) { RandQuickSort(A, 0, A.size()); }

/*
####################
##### Selection Sort
####################
*/

template<class T> void SelectionSort(vector<T>& A) {
    for (int i=0; i<(A.size() - 1); i++) {
        int min = i;
        for (int j=(i + 1); j<A.size(); j++) if (A[j] < A[min]) min = j;
        swap(A[min], A[i]);
    }
}

int main() {
    vector<int> A = { 3, 4, 0, 2, 0, 2 };
    // 3, 4, 0, 2, 0, 2 --> 0 0 2 2 3 4

    cout << "Array to Sort: ";
    for (int i=0; i<(A.size() - 1); i++) cout << A[i] << ", ";
    cout << A[A.size() - 1] << endl << endl;

    CountingSort(A);
    // InsertionSort(A);
    // MergeSort(A);
    // RandQuickSort(A);
    // SelectionSort(A);

    cout << "Sorted Array:  ";
    for (int i=0; i<(A.size() - 1); i++) cout << A[i] << ", ";
    cout << A[A.size() - 1] << endl;

    return 0;
}