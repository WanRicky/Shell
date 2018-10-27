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
    explicit Shell(std::string homedir);
    ~Shell();
    void cd(std::string path);
    void cd();
    void pwd();
    void pwdhome();
    void distance(std::string path);

private:
    node *home;
    node *currentPath;
};

Shell::Shell() {
    node *temp = new node("/");
    home = temp;
    node *temp1 = new node("/");
    currentPath = temp1;
}

Shell::Shell(std::string homedir){
    home = NULL;
    cd(homedir);
    node *tail = NULL;
    for(node *p =  currentPath; p != NULL; p = p->next){
        node *temp = new node(p->dir);
        if(home == NULL){
            home = temp;
            tail = home;
        }
        else{
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }

    }
}

void Shell::cd() {
    currentPath = NULL;
    node *tail = NULL;
    pwdhome();
    for(node *p = home; p != NULL; p = p->next){
        node *temp = new node(p->dir);
        if(currentPath == NULL){
            currentPath = temp;
            tail = currentPath;
        }
        else{
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }
}

void Shell::pwdhome() {
    for(node *p = home; p !=  NULL; p = p->next)
        std::cout << p->dir;
    std::cout << std::endl;
}

void Shell::pwd(){
    for(node *p = currentPath; p !=  NULL; p = p->next)
        std::cout << p->dir;
    std::cout << std::endl;
}

void Shell::cd(std::string path) {
    if(path == "")
        path += "~";
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
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }
    /*for(node *p = pathHead; p !=  NULL; p = p->next)
        std::cout << p->dir;
    std::cout << std::endl;*/

    if(pathHead->dir == "~/"){
        currentPath = NULL;
        for(node * p = home; p != NULL; p = p->next){
            node *temp = new node(p->dir);
            if(currentPath == NULL){
                currentPath = temp;
                tail = currentPath;
            }
            else{
                tail->next = temp;
                temp->prev = tail;
                tail = temp;
            }
        }
        if(pathHead->next != NULL) {
            tail->next = pathHead->next;
            pathHead->next->prev = tail;
        }
    }
    else if(pathHead->dir == "/"){
        currentPath = NULL;
        currentPath = pathHead;
    }
    else if(pathHead->dir == "./"){
        node *tail = currentPath;
        while(tail->next != NULL) tail = tail->next;
        tail->next = pathHead;
        pathHead->prev = tail;
    }
    else {
        tail = currentPath;
        while(tail->next != NULL) tail = tail->next;
        tail->next = pathHead;
        pathHead->prev = tail;
    }
    for(node *p = currentPath; p != NULL; p = p->next) {
        if (p->next != NULL){
            if (p->dir == "./") {
                p->prev->next = p->next;
                p->next->prev = p->prev;
            } else if (p->dir == "../") {
                p->prev->prev->next = p->next;
                p->next->prev = p->prev->prev;
            } else if(p->dir == "~/"){
                node *q = p->next;
                currentPath = NULL;
                tail = NULL;
                for(node * p = home; p != NULL; p = p->next){
                    node *temp = new node(p->dir);
                    if(currentPath == NULL){
                        currentPath = temp;
                        tail = currentPath;
                    }
                    else{
                        tail->next = temp;
                        temp->prev = tail;
                        tail = temp;
                    }
                }
                tail->next = q;
                q->prev = tail;
            }
        }
        else{
            if(p->dir == "./"){
                p->prev->next = NULL;
            }
            else if(p->dir == "../") {
                p->prev->prev->next = NULL;
            }
            else if(p->dir == "~/"){
                currentPath = NULL;
                tail = NULL;
                for(node * p = home; p != NULL; p = p->next){
                    node *temp = new node(p->dir);
                    if(currentPath == NULL){
                        currentPath = temp;
                        tail = currentPath;
                    }
                    else{
                        tail->next = temp;
                        temp->prev = tail;
                        tail = temp;
                    }
                }
            }
        }
    }
}

Shell::~Shell() {
    while(currentPath != NULL){
        node *p = currentPath;
        currentPath = currentPath->next;
        delete p;
    }
    while(home != NULL){
        node *p = home;
        home = home->next;
        delete p;
    }
}

void Shell::distance(std::string path) {
    node *copyCurrentPath = NULL;
    node *tail = NULL;
    for(node *p = currentPath; p != NULL; p = p->next){
        node *temp = new node(p->dir);
        if(copyCurrentPath == NULL){
            copyCurrentPath = temp;
            tail = copyCurrentPath;
        }
        else{
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }
    cd(path);
    /*for(node *p = currentPath; p !=  NULL; p = p->next)
        std::cout << p->dir;
    std::cout << std::endl;
    for(node *p = copyCurrentPath; p !=  NULL; p = p->next)
        std::cout << p->dir;
    std::cout << std::endl;*/
    int depthOfCurrentPath = 0;
    int depthOfCopyCurrentPath = 0;
    int differ = 0;
    for(node *p = currentPath; p != NULL; p = p->next) depthOfCurrentPath++;
   //std::cout << depthOfCurrentPath << std::endl;
    for(node *p = copyCurrentPath; p != NULL; p = p->next) depthOfCopyCurrentPath++;
    //std::cout << depthOfCopyCurrentPath << std::endl;
    node *p = currentPath;
    node *q = copyCurrentPath;
    while(1){
        if(p->dir == q->dir)
            differ++;
        else
            break;
        p = p->next;
        q = q->next;
        if(p == NULL || q == NULL)
            break;
    }
     std::cout << (depthOfCopyCurrentPath - differ) + (depthOfCurrentPath - differ) << std::endl;
    currentPath = NULL;
    tail = NULL;
    for(p = copyCurrentPath; p != NULL; p = p->next){
        node *temp = new node(p->dir);
        if(currentPath == NULL){
            currentPath = temp;
            tail = currentPath;
        }
        else{
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }
}

#endif //SHELL_SHELL_H
