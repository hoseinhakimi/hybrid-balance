//Author: Mohammad Hossein Hakimi Siboni
//Affiliation: Center For Cognitive and Data Science, Shahid Beheshti University, Physics Dpt.

#include <algorithm>
#include <vector>
#include <iostream>

unsigned nChoosek(unsigned n, unsigned k)
{
    if (k > n)
        return 0;
    if (k * 2 > n)
        k = n - k;
    if (k == 0)
        return 1;

    int result = n;
    for (int i = 2; i <= k; ++i)
    {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

unsigned **squares(unsigned n, unsigned r)
{
    unsigned squares_count = nChoosek(n, r);

    unsigned **squares;
    squares = new unsigned *[squares_count];
    for (short i = 0; i < squares_count; i++)
    {
        squares[i] = new unsigned[4];
    }

    std::vector<bool> v(n);
    std::fill(v.end() - r, v.end(), true);
    short row = 0;
    short column;

    do
    {
        column = 0;
        for (unsigned i = 0; i < n; ++i)
        {
            if (v[i])
            {
                squares[row][column] = i;
                column++;
            }
        }
        row++;
    } while (std::next_permutation(v.begin(), v.end()));

    return squares;
}