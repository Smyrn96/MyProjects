#include "avm.h"

int main(int argc, char** argv) {
    int i = 0;
    int j = 0;
    unsigned sz;
    FILE* bf = fopen("TargetCodeFile.abc", "rb");

    fseek(bf, 0L, SEEK_END);
    sz = ftell(bf);
    rewind(bf);

    read_magic(bf);
    read_strings(bf);
    read_numbers(bf);
    read_userFuncs(bf);
    read_libFuncs(bf);
    read_code(bf);
    read_totalglobals(bf);
    avm_initstack();
    //print_abc_file();
    while (executionFinished == 0) {
        execute_cycle();
    }
    fclose(bf);
}