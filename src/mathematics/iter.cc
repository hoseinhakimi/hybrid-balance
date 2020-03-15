//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include <algorithm>
#include <vector>
#include <iostream>

#include "../headers/matrix.h"

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

void squares(unsigned r, Matrix *mat)
{
    unsigned oneSquare[4];
    std::vector<bool> v(mat->size);
    std::fill(v.end() - r, v.end(), true);
    short column;
    do
    {
        column = 0;
        for (unsigned i = 0; i < mat->size; ++i)
        {
            if (v[i])
            {
                oneSquare[column] = i;
                column++;
            }
        }
        mat->oneSquareEnergy(oneSquare);
    } while (std::next_permutation(v.begin(), v.end()));
}