int not_equal_float(float x, float y);

int main() {
    if (not_equal_float(5.0f, 5.0f) != 0) return 1;
    if (not_equal_float(10.5f, 5.2f) != 1) return 1;
    if (not_equal_float(3.1f, 3.1f) != 0) return 1;
    return 0;
}
