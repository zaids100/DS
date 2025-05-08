// Code 1: Parallel Reduction – Min and Average (C++)
#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>

void parallel_min_avg(const std::vector<int>& data, int& min_val, double& avg_val) {
    int local_min = data[0];
    long long sum = 0;

    #pragma omp parallel for reduction(min:local_min) reduction(+:sum)
    for (int i = 0; i < data.size(); i++) {
        if (data[i] < local_min)
            local_min = data[i];
        sum += data[i];
    }

    min_val = local_min;
    avg_val = static_cast<double>(sum) / data.size();
}

int main() {
    const int data_size = 1000000;
    std::vector<int> data(data_size);

    for (int i = 0; i < data_size; i++) {
        data[i] = rand() % 100;
    }

    int min_val;
    double avg_val;

    parallel_min_avg(data, min_val, avg_val);

    std::cout << "Minimum value: " << min_val << std::endl;
    std::cout << "Average value: " << avg_val << std::endl;

    return 0;
}



// Code 2: Parallel Reduction – Max and Sum (C++)
#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>

void parallel_max_sum(const std::vector<int>& data, int& max_val, long long& sum_val) {
    int local_max = data[0];
    long long total_sum = 0;

    #pragma omp parallel for reduction(max:local_max) reduction(+:total_sum)
    for (int i = 0; i < data.size(); i++) {
        if (data[i] > local_max)
            local_max = data[i];
        total_sum += data[i];
    }

    max_val = local_max;
    sum_val = total_sum;
}

int main() {
    const int data_size = 1000000;
    std::vector<int> data(data_size);

    for (int i = 0; i < data_size; i++) {
        data[i] = rand() % 100;
    }

    int max_val;
    long long sum_val;

    parallel_max_sum(data, max_val, sum_val);

    std::cout << "Maximum value: " << max_val << std::endl;
    std::cout << "Sum value: " << sum_val << std::endl;

    return 0;
}
