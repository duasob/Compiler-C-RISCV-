int less_than_equal_double(double x, double y);

int main() {
    if (less_than_equal_double(5.0, 5.0) != 1) return 1;
    if (less_than_equal_double(10.5, 5.2) != 0) return 1;
    if (less_than_equal_double(3.1, 7.8) != 1) return 1;
    return 0;
}
