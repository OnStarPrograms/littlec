#include "../headers/utils.h"

int main(){
    util::DataTracker aba;
    aba.inc();
    aba.tockTrie("hi");
    aba.inc();
    aba.tockTrie("hi");
    aba.writeToFile();
    return 0;
}
