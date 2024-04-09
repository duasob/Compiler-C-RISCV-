int postfix_increment(int x);

int main() {

    if (postfix_increment(0) != 0) return 1;
    if (postfix_increment(1) != 1) return 1;
    if (postfix_increment(2) != 2) return 1;

    return 0;
}
