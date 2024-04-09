double multiply_double(double x, double y);

int main()
{
    if (multiply_double(2.5, 3.5) != 8.75) return 1;
    if (multiply_double(-1.0, 1.0) != -1.0) return 1;
    if (multiply_double(0.0, 5.0) != 0.0) return 1;
    return 0;
}
