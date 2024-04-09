float add_float(float x, float y);

int main()
{
    if (add_float(2.5f, 3.5f) != 6.0f) return 1;
    if (add_float(-1.0f, 1.0f) != 0.0f) return 1;
    if (add_float(0.0f, 0.0f) != 0.0f) return 1;
    return 0;
}
