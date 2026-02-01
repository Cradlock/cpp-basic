## Перечесления Enum


*enum class* - Позволяет создать класс имеюший только определеные 
 значения 


```
// каждое значение eng и rus по дефолту имеет значение типа int 
// которое выставлено изначально начиная с 0
enum class Language { eng,rus };

// Потом использовать 
Language my {Language::eng}; 

cout << static_cast<int>(my); // будет 0 так как eng первый и он равен 0

```


```
// Можно также писать свои значения
enum class Language { eng = 1,rus = 2 };

// Комбинировать
enum class Language { eng = 2,rus}; 

// Работать с другими 
enum class Language { eng, rus = eng + 1 };

```

Также если хотите можно использовать другой целочисленный тип данных (только те что хранят не дробные числа )

```
//Например char 
enum class Operation: char {Add='+',Subtract='-'};

```

Перечисления очень удобны с использованием switch case 


