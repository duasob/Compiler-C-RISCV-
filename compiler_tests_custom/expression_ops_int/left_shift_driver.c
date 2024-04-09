int left_shift(int x, int y);

int main()
{
    if (left_shift(2, 1) != 4) return 1;
    if (left_shift(5, 2) != 20) return 1;
    if (left_shift(10, 3) != 80) return 1;
    if (left_shift(1, 5) != 32) return 1;
    if (left_shift(-1, 5) != -32) return 1;
    return 0;
}
