#include <iostream>
#include "Shell.h"

int main() {
    Shell *s = new Shell();
    s->pwd();
    s->cd("~/user/name");
    s->cd("/usr/local/bash");
    s->cd("././../../../hello/./");
    return 0;
}