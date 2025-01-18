#include <iostream>
#include <random>
#include <pthread.h>

/*
Create a multi-threaded merge sort algorithm in C++,
we create a new thread on whenever we divide the dataset
*/

struct ThreadArgs {
    std::vector<int>* data;
    int left;
    int right;
};

void merge(std::vector<int>& data, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (data[i] <= data[j]) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = data[i++];
    }

    while (j <= right) {
        temp[k++] = data[j++];
    }

    for (i = left, k = 0; i <= right; ++i, ++k) {
        data[i] = temp[k];
    }
}

void* parallel_merge_sort(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*) args;
    std::vector<int>* data = thread_args->data;
    int left = thread_args->left;
    int right = thread_args->right;

    if (left >= right) {
        return nullptr;
    }

    int mid = (right - left) / 2 + left;

    ThreadArgs left_args = {data, left, mid};
    ThreadArgs right_args = {data, mid+1, right};

    pthread_t left_thread, right_thread;

    pthread_create(&left_thread, nullptr, parallel_merge_sort, &left_args);
    pthread_create(&right_thread, nullptr, parallel_merge_sort, &right_args);

    pthread_join(left_thread, nullptr);
    pthread_join(right_thread, nullptr);

    merge(*data, left, mid, right);

    return nullptr;

}

int main() {
    std::vector<int> data;

    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000);

    for (int i = 0; i < 100; i++) {
        data.push_back(dis(gen));
    }

    ThreadArgs args = {&data, 0, (int)data.size() - 1};

    pthread_t main_thread;
    pthread_create(&main_thread, nullptr, parallel_merge_sort, &args);

    pthread_join(main_thread, nullptr);

    for (int num : data) {
        std::cout << num << " ";
    }

    std::cout << std::endl;

    return 0;
}
