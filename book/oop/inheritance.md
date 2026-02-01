## Наследование 

*Наследование* - является базовым принципом ООП отвечает за 
вынесение общего функционала.При использовании Наследования
структура классов обретает иерархию где одни классы являются
дочерними для других 


логически можно связать так 
<pre>

Обьект <- базовый класс содержит (массу,координаты)
    |
    |
Живое <- Наследник от обьекта  имеет новые аттрибуты (силу,здоровье)
    |
    | 
Человек <- Наследник от живое имеет новые аттрибуты (имя,возраст) 
    |
    |
Доктор <- Наследик от человека имеет новые аттрибуты (стаж,направление) 

</pre>

Таким образом все дочерние классы обладают всеми свойствами 
родителя.


### Рассмотрим на примере:
```
// Просто доп структура 
struct Point{
    int x,y,z;
};

// Базовый родительский класс
class Object{
private: 
    int mass;
    Point coord;

public: 
    Object(int m_m, Point cr) : mass(m_m),coord(cr) {}

    void add_mass(int a){ 
        mass += a; 
    }

    void sub_mass(int a){  
        if(a >= mass) return; 
        mass -= a; 
    }

    void move(Point pt){
        coord = pt;
    }

    void show(){ 
        cout << "Mass: " << mass 
        << " x:" << coord.x  
        << " y:" << coord.y 
        << " z:" << coord.z 
        << endl;
    }

};

```
### И дочерний класс:
```
// Вот здесь и соединяем наш класс-родитель
class Life : public Object
{
public: 
    int health,stamina;
    double hungry,hirst;

};

```


### Модификаторы доступа
*public* - поля передлаются как есть  
*private* - все поля переделываются в `private`
*protected* - все поля становатся `protected`


### Примечание:
```

// значит что от класса нельзя наследоватся 
class Object final {}

// вызовет ошибку
class SomeClass : public Object {}

```

## Наследование особых функций:

### Конструктор

Сам по себе не наследуется нужно прописывать или подключать 
```
Life(int mass,Point cr, int h,int s) : 
Object(mass,cr) // <- вот тут вызываем конструктор родителя 
{
    health = h;
    stamina = s; 
}
```

### Конструктор копирования 
Нужно прописывать самому так как тоже не наследуется
```

Life(const Life& other) :
Object(other) // вызываем родительский
{
    // копируем поля 
}

```


### Деструкторы
Обычно не наследутся вызывается сначала для дочернего потом родителя.
Дополняя друг друга 








## Множественное наследование 


Механизм при котором производный класс может наследоватся от двух классов или более

`Множественное наследование` - происходит через знак `,` в начале инициализации класса 

```
// Один родитель
class Body{
    public: 
        Body(int m) : mass(m) {} 
        
        
        int getMass() {return mass; };
        
        void show() const { cout << "Mass:" << mass << endl; };
    private:
        int mass; 
};

// Второй родитель
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
    private:
        string name;
}; 

```

Как вы видите можно так обьявить сразу двух родителей и использовать то что есть в обоих

```
// Обьявление обьекта
Person bob = Person("Bob",127,100);

```

## Использование методов 
```
bob.eat(12);

cout << bob.getName() << endl;

cout << bob.getMass() << endl;
```


Но бывают случаи когда есть два метода в обоих родителях и они похожи,
Прим: компилятор сначала делает поиск по именам, так что не получится сделать перегрузку


## Так что можно сделать три варианта 

### Явно указать

```
// указываем нужный `namespace`
bob.Body::show();
```

### Cделать один обший метод в производном классе
```

//Внутри Person 
void show() {
    Bio::show();
    Body::show();
}

```


### Сделать один метод главным по умолчанию
```
// Внутри Person 

using Bio::show; // <- используется по умолчанию
// или 
using Body::show; // <- или этот будет использоватся по умолчанию

```
Теперь можно делать так 
```
bob.show();
```



## Проблема Ромба 

Иногда бывает что есть один обший базовый класс
```
class Base{
    ...
};
```


И от него наследуются два производных

```
class Parent1 : public Base{
    ...
};

class Parent2 : public Base{
    ... 
};
```

И эти два класса будут использоватся для наследование еше одного класса 

```
class Child : public Parent1,public Parent2 {
    ... 
};

```
И вот здесь проблема, структура теперь выглядет так

<pre>
        Base 
        /   \
       /     \
    Par1    Par2 
       \     / 
        Child   
</pre>

Напоминает ромб. Теперь в обьектах Child будет дублироватся методы и аттрибуты Base,
чтобы этого избежать.Используется модификатор `virtual`.
А именно нужно изменить обьявление `Parent1` и `Parent2`
```
class Parent1 : public virtual Base {};

class Parent2 : public virtual Base {};
```

Теперь в `Child` только один вариант от `Base` без повторений. 




