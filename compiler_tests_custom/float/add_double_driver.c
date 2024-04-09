double add_double(double x, double y);

int main()
{
    if (add_double(2.5999999, 3.5) != 6.0999999) return 1;
    //if (add_double(-1.0999999, 1.0) != -0.0999999) return 1;
    if (add_double(0.0, 0.0) != 0.0) return 1;
    return 0;
}
