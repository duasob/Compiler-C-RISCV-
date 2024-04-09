int less_than_float(float x, float y);

int main() {
    if (less_than_float(5.0f, 5.0f) != 0) return 1;
    if (less_than_float(5.2f, 10.5f) != 1) return 1;
    if (less_than_float(7.8f, 3.1f) != 0) return 1;
    return 0;
}
