#include <iostream>
#include "Shell.h"

int main() {
    std::string homedir = "/a/b/.../c";
    Shell *s = new Shell(homedir);
    s->cd("/");
    s->cd("..");
    s->pwd();
    s->cd();
    s->pwd();
    s->cd("..");
    s->pwd();
    s->cd();
    s->pwd();
    s->cd("/local");
    s->cd("");
    s->pwd();
    return 0;
}