int postfix_decrement(int x);

int main() {
    if (postfix_decrement(3) != 3) return 1;
    if (postfix_decrement(2) != 2) return 1;
    if (postfix_decrement(1) != 1) return 1;

    return 0;
}
