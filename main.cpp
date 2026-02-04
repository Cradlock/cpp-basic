#include <iostream>
#include <vector>

using namespace std;


struct Point{
    int x,y;

    Point(int xp,int yp) : x(xp),y(yp) {}
    
    friend ostream& operator << (ostream& st,const vector<Point>& v){
        
        for(auto& i : v){
            st << " [X: " << i.x;
            st << "  Y: " << i.y << "]";
        }
        return st;       
    }

};
int main(int argc, char* argv[]){
    
    
    return 0; 
}



