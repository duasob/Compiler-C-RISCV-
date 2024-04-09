float divide_float(float x, float y);

int main()
{
    if (divide_float(10.0f, 2.0f) != 5.0f) return 1;
    if (divide_float(-10.0f, 2.0f) != -5.0f) return 1;
    if (divide_float(5.0f, 0.0f) != __builtin_inff()) return 1; // Division by zero
    return 0;
}
