int multiply(int x, int y)
{
    int acc=0;
    while(x >= 0){
        acc += y;
        x--;
    }
    return acc;
}
