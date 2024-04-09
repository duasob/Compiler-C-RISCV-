int increment(int x);

int main() {

    if (increment(0) != 1) return 1;
    if (increment(1) != 2) return 1;
    if (increment(2) != 3) return 1;

    return 0;
}
