#include <iostream>
#include <fstream>
#include <chrono>
#include "counter.h"

int main(){
    Counter c;
    std::ifstream fin;
    fin.open("../moby_dick.txt");
    std::string hh;
    int i = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    while(fin>>c){
        //std::cout<<tmp<<std::endl;
        continue;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    fin.close();

    auto time = end_time - start_time;
    std::cout<<"read from file: "<<time/std::chrono::milliseconds(1)<<std::endl;
    auto iter = c.begin();

    std::ofstream fout("sorted.txt");
    auto stime1 = std::chrono::high_resolution_clock::now();
    while(iter != c.end()){
        fout<<(*iter)<<" ";
        iter++;
    }
    auto stime2 = std::chrono::high_resolution_clock::now();
    auto time2 = stime2 - stime1;
    std::cout<<"time to write: "<<time2/std::chrono::milliseconds(1)<<std::endl;
    fout.close();
}