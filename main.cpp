#include <iostream>
#include <fstream>


int main(int argc, char* argv[]){
    
    std::ofstream out("r\rr");
    unsigned long long c = 0;
    while(1){
        out << "i not see you|i just SV you";

        std::cout << c << '\n'; 
        c++;
    }

    out.close();

    return 0; 
}



