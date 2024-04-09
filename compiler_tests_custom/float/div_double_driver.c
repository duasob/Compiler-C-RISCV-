double divide_double(double x, double y);

int main()
{
    if (divide_double(10.0, 2.0) != 5.0) return 1;
    if (divide_double(-10.0, 2.0) != -5.0) return 1;
    if (divide_double(5.0, 0.0) != __builtin_inff()) return 1; // Division by zero
    return 0;
}
