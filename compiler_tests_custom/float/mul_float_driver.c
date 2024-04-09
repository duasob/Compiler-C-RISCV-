float multiply_float(float x, float y);

int main()
{
    if (multiply_float(2.5f, 3.5f) != 8.75f) return 1;
    if (multiply_float(-1.0f, 1.0f) != -1.0f) return 1;
    if (multiply_float(0.0f, 5.0f) != 0.0f) return 1;
    return 0;
}
