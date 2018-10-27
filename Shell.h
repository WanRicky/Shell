//
// Created by apple on 2018/10/27.
//

#ifndef SHELL_SHELL_H
#define SHELL_SHELL_H

#include <string>
#include <iostream>

struct node{
    std::string dir;
    node *next;
    node *prev;
    node(){next = NULL; prev = NULL;}
    explicit node(std::string ndir){next = NULL; prev = NULL; dir = ndir;}
};

class Shell{
public:
    Shell();
    //Shell(std::string homedir);
    ~Shell();
    void cd(std::string path);
    //void cd();
    void pwd();
    //void distance(std::string path);

private:
    node *home;
    node *currentPath;
};

Shell::Shell() {
    node *temp = new node("/");
    home = temp;
    currentPath = home;
}

void Shell::pwd(){
    for(node *p = currentPath; p !=  NULL; p = p->next)
        std::cout << p->dir;
    std::cout << std::endl;
}

void Shell::cd(std::string path) {
    node *pathHead = NULL;
    node *tail = NULL;
    for(int i = 0; i < path.length(); ++i){
        std::string tempstr = "";
        while(path[i] != '/'){
            tempstr += path[i];
            ++i;
            if(i == path.length())
                break;
        }
        tempstr += '/';
        if(pathHead == NULL){
            node *temp = new node(tempstr);
            pathHead = temp;
            tail = temp;
        }
        else{
            node *temp = new node(tempstr);
            temp->next = NULL;
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }
    for(node *p = pathHead; p !=  NULL; p = p->next)
        std::cout << p->dir;
    std::cout << std::endl;


}

Shell::~Shell() {
    while(currentPath != NULL){
        node *p = currentPath;
        currentPath = currentPath->next;
        delete p;
    }
}

#endif //SHELL_SHELL_H
