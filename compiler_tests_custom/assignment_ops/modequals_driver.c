int modulo_equal(int x, int y);

int main() {
    if (modulo_equal(10, 3) != 1) return 1;
    if (modulo_equal(15, 4) != 3) return 1;
    if (modulo_equal(20, 7) != 6) return 1;
    return 0;
}
