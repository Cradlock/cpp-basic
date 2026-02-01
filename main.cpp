#include <algorithm>
#include <iostream>

using namespace std;

class Body{
    public: 
        Body(int m) : mass(m) {} 
        
        
        int getMass() {return mass; };
        
        void show() const { cout << "Mass:" << mass << endl; };
    private:
        int mass; 
};

class Bio{
    public:
        Bio(int st) : stamina(st) {} 
        
        void eat(int energy) { stamina += energy; };
        int getStamina(){ return stamina; };
        
        void show() const { cout << "Stamina:" << stamina << endl; };
    private:  
        int stamina;
};
    

class Person : public Body,public Bio{
    public: 
        Person(string name_p,int mass,int stamina) : Body(mass),Bio(stamina),name(name_p) {}
        
        string getName() {return name;};

        using Bio::show;

    private:
        string name;
}; 



int main(int argc, char* argv[]){
    Person bob = Person("Bob",125,100);
    
    bob.eat(12);
    
    bob.show();

    return 0;
}



