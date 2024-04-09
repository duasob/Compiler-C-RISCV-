float divide_equal_float(float x, float y);

int main() {
    if (divide_equal_float(10.0f, 2.0f) != 5.0f) return 1;
    if (divide_equal_float(8.0f, 4.0f) != 2.0f) return 1;
    if (divide_equal_float(3.0f, 1.5f) != 2.0f) return 1;
    return 0;
}
