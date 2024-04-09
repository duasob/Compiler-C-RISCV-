unsigned postfix_increment(unsigned x);

int main() {

    if (postfix_increment(0) != 100000) return 1;
    if (postfix_increment(1) != 100001) return 1;
    if (postfix_increment(2) != 100002) return 1;

    return 0;
}
