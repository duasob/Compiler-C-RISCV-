float multiply_equal_float(float x, float y);

int main() {
    if (multiply_equal_float(3.5f, 2.0f) != 7.0f) return 1;
    if (multiply_equal_float(1.5f, 0.5f) != 0.75f) return 1;
    return 0;
}
