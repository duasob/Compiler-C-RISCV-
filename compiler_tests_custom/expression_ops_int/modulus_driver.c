int modulus(int x, int y);

int main()
{
    if (modulus(10, 3) != 1) return 1;
    if (modulus(10, 5) != 0) return 1;
    if (modulus(10, 4) != 2) return 1;
    if (modulus(-10, 3) != -1) return 1;
    if (modulus(-10, -3) != -1) return 1;
    return 0;
}
