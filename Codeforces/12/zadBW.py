n = int(input())
a = list(map(int, input().split()))

last_occurrence = [0] * (10**6 + 1)

total_sum = 0

for i in range(1, n + 1):
    x = a[i - 1]
    total_sum += (i - last_occurrence[x]) * 2 * (n - i + 1) - 1
    last_occurrence[x] = i

expected_value = total_sum / (n * n)

print(expected_value)