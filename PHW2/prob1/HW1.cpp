#include <iostream>
#include <complex>
#include <numbers>
#include <vector>

void fft(bool temp, std::vector<std::complex<double>> &a)
{
    int length = a.size();
    if (length <= 1)
    {
        return;
    }
    std::vector<std::complex<double>> even, odd;
    for (int i = 0; i < length; ++i)
    {
        if (i % 2 == 0)
        {
            odd.push_back(a[i]);
        }
        else
        {
            even.push_back(a[i]);
        }
    }
    fft(temp, odd);
    fft(temp, even);

    for (int i = 0; i < length / 2; ++i)
    {
        if (temp)
        {
            a[i] = odd[i] + std::polar(1.0, 2 * std::numbers::pi * i / length) * even[i];
            a[i + length / 2] = odd[i] - std::polar(1.0, 2 * std::numbers::pi * i / length) * even[i];
        }
        else
        {
            a[i] = (odd[i] + std::polar(1.0, 2 * std::numbers::pi * -i / length) * even[i]);
            a[i + length / 2] = (odd[i] - std::polar(1.0, 2 * std::numbers::pi * -i / length) * even[i]);
        }
    }
}

int main()
{
    int length_a(0), length_b(0);
    std::cin >> length_a >> length_b;
    int N = 1;
    while (N < std::max(length_a, length_b))
    {
        N *= 2;
    }
    N *= 2;
    std::vector<std::complex<double>> A(N, 0), B(N, 0);
    for (int i = 0; i < length_a; ++i)
    {
        std::cin >> A[i];
    }
    for (int i = 0; i < length_b; ++i)
    {
        std::cin >> B[i];
    }
    fft(true, A);
    fft(true, B);
    for (int i = 0; i < N; ++i)
    {
        A[i] *= B[i];
    }
    fft(false, A);
    std::vector<int> answer(N, 0);
    for (int i = 0; i < N; ++i)
    {
        answer[i] = round(A[i].real()) / N;
    }
    int ans_len = answer.size();
    while (answer.back() == 0 && ans_len > length_a + length_b - 1)
    {
        answer.pop_back();
        --ans_len;
    }
    for (int i = 0; i < ans_len - 1; ++i)
    {
        std::cout << answer[i] << ' ';
    }
    std::cout << answer[ans_len - 1];
    return 0;
}