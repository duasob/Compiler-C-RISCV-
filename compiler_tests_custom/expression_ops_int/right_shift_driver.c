int right_shift(int x, int y);

int main() {
    if (right_shift(4, 1) != 2) return 1;
    if (right_shift(20, 2) != 5) return 1;
    if (right_shift(80, 3) != 10) return 1;
    if (right_shift(32, 5) != 1) return 1;
    if (right_shift(-32, 5) != -1) return 1;
    return 0;
}
