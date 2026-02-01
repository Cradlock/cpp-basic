## Using в с++


*using* - ключевое слово обозначающее подключение 


## Выполняет три функции

### Подключение пространства имен
```
using namespace std;

// Больше не нужно постоянно писать std:: 
```


### Создание alias
```
using Matrix = std::vector<std::vector<int>>;

// теперь Matrix это тоже самое что и std::vector<std::vector<int>> 
Matrix photo;  
```

### Можно подключить функцию в namespace класс
```
class SomeClass {
public:
    using SomeParentClass::function;
}
```


