char func(char* arr) {
    int ar[5] = { 1,2,3,4,5 };
    return arr[2];
}
int main() {
    char buf[20] = { 'a', 'b', 'c' };
    func(buf);
}