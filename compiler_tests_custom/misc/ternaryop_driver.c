int ternary_operator(int condition, int x, int y);

int main() {
    if (ternary_operator(1, 10, 20) != 10) return 1;
    if (ternary_operator(0, 10, 20) != 20) return 1;
    if (ternary_operator(1, -5, -10) != -5) return 1;
    if (ternary_operator(0, -5, -10) != -10) return 1;

    return 0;
}
