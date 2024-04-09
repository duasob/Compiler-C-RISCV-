int greater_than_equal(int x, int y);

int main()
{
    if (greater_than_equal(0, 0) != 1) return 1;
    if (greater_than_equal(0, 1) != 0) return 1;
    if (greater_than_equal(1, 0) != 1) return 1;
    if (greater_than_equal(-1, 1) != 0) return 1;
    if (greater_than_equal(1, -1) != 1) return 1;
    return 0;
}
