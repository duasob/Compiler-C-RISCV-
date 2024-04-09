int greater_than_float(float x, float y);

int main() {
    if (greater_than_float(5.0f, 5.0f) != 0) return 1;
    if (greater_than_float(10.5f, 5.2f) != 1) return 1;
    if (greater_than_float(3.1f, 7.8f) != 0) return 1;
    return 0;
}
