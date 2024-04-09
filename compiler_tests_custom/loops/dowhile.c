int do_while_example() {
    int i = 0;

    do {
        int j = 0;
        do {
            i += 2;
            j++;
        } while (j < 3);

        i += 5;
    } while (i < 20);

    return i;
}
