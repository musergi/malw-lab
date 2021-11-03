int main() {
    const char code[] = SHELLCODE;
    int (*hack_func)();
    hack_func = (int (*)()) code;
    return hack_func();
}
