int prefix_decrement(int x);

int main() {

    if (prefix_decrement(3) != 2) return 1;
    if (prefix_decrement(2) != 1) return 1;
    if (prefix_decrement(1) != 0) return 1;

    return 0;
}
