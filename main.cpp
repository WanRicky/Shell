#include <iostream>
#include "Shell.h"

int main() {
    std::string homedir = "/home/user/Documents";
    Shell *s = new Shell(homedir);
    s->pwd();
    s->distance("~/");
    s->cd("~/");
    s->pwd();
    return 0;
}