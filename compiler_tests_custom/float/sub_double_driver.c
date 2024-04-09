double subtract(double x, double y);

int main()
{
    if (subtract(5.5, 2.5) != 3.0) return 1;
    if (subtract(7.0, 3.5) != 3.5) return 1;
    if (subtract(1.0, 0.0) != 1.0) return 1;
    return 0;
}
