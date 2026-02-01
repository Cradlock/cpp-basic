
# friend/friend class на c++

*friend* - это метка которая отмечает те обьекты которые могут лезть в private значения твоего класса 

## Виды
* friend - для функций
* friend class - для других классов 


## friend:
```

class Person{
    // Вот тут мы помечаем что функция `set_name` может 
    // работать с `private` данными класса Person 

    friend void set_name(Person& obj,string new_name);
public:
    Person(string nm) : name(nm){}
private:
    string name;
};

// И тут реализуем функцию
void set_name(Person& obj,string new_name){
    obj.name = new_name;
}

```

## friend class:
```
// создаем класс заранее 
class Food;


// Основной класс 
class Person{
public:
    Person(int st) : stamina(st) {}
    
    // Функция которая взаимодействует с другим классом
    void eat(Food& obj);
private:
    int stamina;
}

// Реализация класса еды
class Food{
// Обьявлем то что любая функция из класса Person может смотреть в наши private данные 
friend class Person;
public:
    Food(int e) : energy(e) {}

private:
    int energy;
};

// Прописываем фукнцию `eat` из класса `Person`
void Person::eat(Food& obj){
// Мы можем смотреть `private` данные по типу `energy` 
    this->stamina += obj.energy;
// Даже менять `energy`
    obj.energy = 0;
}

```


