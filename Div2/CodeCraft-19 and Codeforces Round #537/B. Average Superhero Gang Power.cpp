/*
B. Average Superhero Gang Power

Every superhero has been given a power value by the Felicity Committee. The avengers crew wants to maximize the average power of the superheroes in their team by performing certain operations.

Initially, there are n superheroes in avengers team having powers a1,a2,…,an, respectively. In one operation, they can remove one superhero from their team (if there are at least two) or they can increase the power of a superhero by 1. They can do at most m operations. Also, on a particular superhero at most k operations can be done.

Can you help the avengers team to maximize the average power of their crew?

Input
The first line contains three integers n, k and m (1≤n≤105, 1≤k≤105, 1≤m≤107) — the number of superheroes, the maximum number of times you can increase power of a particular superhero, and the total maximum number of operations.

The second line contains n integers a1,a2,…,an (1≤ai≤106) — the initial powers of the superheroes in the cast of avengers.

Output
Output a single number — the maximum final average power.

Your answer is considered correct if its absolute or relative error does not exceed 10−6.

Formally, let your answer be a, and the jury's answer be b. Your answer is accepted if and only if |a−b|max(1,|b|)≤10−6.

Note
In the first example, the maximum average is obtained by deleting the first element and increasing the second element four times.

In the second sample, one of the ways to achieve maximum average is to delete the first and the third element and increase the second and the fourth elements by 2 each.

http://codeforces.com/contest/1111/problem/B

Description
제거한 인원수가 결정이 되고나면, 최대값은 유일하게 결정된다.
이러한 성질을 바탕으로 다음과 같은 점화식을 세웠다.

D[i] : i명을 제거 했을때 최대값

어떤 수의 인원이 제거될때, 최대값이 되기 위해서는 제거된 대상들이 가장 작은 값을 가지고 있어야한다.
가령, 5, 3, 2, 1, 5라는 능력치를 가진 인원중 한명을 제거한다면, 가장 낮은 능력치인 1를 가진 사람을 제거해야 한다.
이를 위해선 초기에 데이터를 입력받고 정렬하면 매 단계에서 가장 낮은 능력치를 가진 사람을 지울때 쉽게 접근할 수 있다.

이러한 식을 세우고 나면, 다음과 같은 식이 정의된다.
A[k] = k 번째로 낮은 능력치를 가진 사람의 능력치
Sn = A[0] + A[1] + ... + A[n]
D[0] = Sn + min(nk , m) / n
한명도 제거 하지 않은 상태에서의 최댓값은 Sn에서, n명의 사람들을 각각 k만큼의 능력치를 올려주는 경우와 m번의 연산 횟수중 최솟 값을 더해주면 된다.

D[i] = (S[n] - S[i] + min((n - i )*k, m - i )) / (n - i);
결국 위와 같은 식이 정의가 된다.

이 문제에서 주의할 점은 bottom up 시에 i<n 과 i<=m 의 조건을 함께 걸어줘야 문제가 생기지 않는다.
i<=m이 없다면, 지우는 동작을 연산횟수를 초과하여 수행한 결과도 포함되기 때문에, 결과 값이 바뀔 수 있기 때문이다.
또한, 마지막으로 문제에서 출력 precision에 대한 조건이 있다. 
이 떄문에 cout.precision(30)으로 지정하여 출력하고 문제를 해결하였다.


*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cout.precision(30);
	double n, k, m;
	cin >> n >>k >> m;
	vector<double> A(n + 1);
	vector<double> D(n + 1);
	vector<double> S(n + 1);
	double sum = 0;

	for (int i = 1; i <= n; i++)
		cin >> A[i];

	sort(A.begin(), A.end());

	for (int i = 1; i <= n; i++)
		S[i]=S[i-1]+A[i];

	D[0] = (S[n] + min(n*k, m))/n;

	double max =D[0];
	for (int i = 1; i < n && i<=m; i++)
	{

		D[i] = (S[n] - S[i] + min((n - i )*k, m - i )) / (n - i);

		if (D[i] > max)
			max = D[i];
	}
	cout << max;

	return 0;
}