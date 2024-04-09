float subtract_float(float x, float y);

int main()
{
    if (subtract_float(5.5f, 2.5f) != 3.0f) return 1;
    if (subtract_float(7.0f, 3.5f) != 3.5f) return 1;
    if (subtract_float(1.0f, 0.0f) != 1.0f) return 1;
    return 0;
}
