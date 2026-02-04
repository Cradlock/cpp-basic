#include <iostream>
#include <vector>

using namespace std;


ostream& operator << (ostream& st,const vector<string>& v){
    st << "-";
    for(auto& i : v){
        st << i;
        st << "-";
    }
    return st;
}


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
    vector<Point> massiv = {Point(4,2),Point(2,3),Point(32,1)}; 
    auto it = massiv.begin();

    massiv.emplace_back(1,2);

    cout << massiv << endl;

    return 0; 
}



