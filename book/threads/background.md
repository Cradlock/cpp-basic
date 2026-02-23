## Фоновые процессы в С++ 

С++ поддерживает многопточность.Для этого есть обьект
`std::thread` - это обьект который представляет собой отдельный исполнитель кода,

### Пример
```
#include <thread>
#include <iostream>

void task() {
    std::cout << "Я работаю в другом потоке!" << std::endl;
}

int main() {
    std::thread t(task); // Создали поток и запустили функцию task
    t.join();            // Главный поток ждет, пока поток 't' закончит работу
    return 0;
}
```
> Важно!!! в конце обязательно вызвать `.join()` чтобы поток завершился корректно.


Так можно запускать функции в другом потоке,тепер представим что два потока
работают с обшей памятью.

```
общий обьект x = "hello";

task1 -> меняет x += " name" 
и
task2 -> меняет x += " !"

```

В итоге x теперь hello  n!ame данные сломались,такое событие называется 
Состояние гонки 
(`race condition`), он может быть непредсказуем так как два потока одновременно
меняют данные.Это как если бы два писателя одновременно писали в одну книгу.


## Mutex 
`mutex` - это обьект замок, которые помогает контролировать доступ к обшей памяти.
Его смысл в том чтобы дать доступ к ресурсу только одному потоку, потом открыть
доступ для следуюшего и т.д
```
x = "hello ";
task1 -> mutex( x += " name" )
task2 -> mutex( x += " !" )

```
Теперь task2 подождет пока task1 закончит работу.

### Пример:
```
std::mutex mtx;

int counter = 0;
void task(){
    mtx.lock(); // блокируем
    // Безопасная зона 
    for(int i = 0;i < 1000;++i){
        counter++;
    }
    mtx.unlock(); // разблокируем
}

int main(){
    std::thread t1(task);
    std::thread t2(task);
    
    t1.join();
    t2.join();
    ...
}

```
Теперь мы точно уверены что обьект counter будет не меньше 2000 потому-что два 
потока выполнятся адекватно.

### Также есть более безопасный способ 
```
void safe_increment() {
    std::lock_guard<std::mutex> lock(mtx); // Замок закрыт
    counter++;
} // Замок открылся автоматически!
```


### Через умный замок 
```
void safe_increment() {
    std::unique_lock<std::mutex> lock(mtx); // Умный замок закрыт
    
    counter++;
    
    // позволяет ненадолго открыть lock 
    lock.unlock();
    ... // что то делаем дальше он сам закроется

} // Замок открылся автоматически!
`

```

> Правило: 1 mutex = 1 ресурс 




## condition variable

`condition_variable` - Обьект нужный для синхронизации которые позволяет ждать
опредленного события чтобы пробудить поток.

---

Если доп поток постоянно будет проверят не пришли ли новые данные он сьест
много ресурсов. `condition_variable` делает так что если данных нет то 
поток спит и ничего не нагружает а если есть данные он активируется и когда 
закончит будет спать пока не придут новые данные.

### Пример:
```
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

mutex mtx; // защита данных 
queue<string> data_queue; // данные 
condition_variable cv; // регулировщик потоков 

bool finished = false; // Флаг завершения подготовки для потока



// Основная функция которая делает тяжелую работу не мешая нашей программе
void writer_task(const string filename){
    ofstream file(filename,ios::app);
    

    // постояно работает
    while(true){
        unique_lock<mutex> lock(mtx); // Для condition_variable используем именно unique_lock
        

        // Ждем пока очередь не станет пустой или не закончится работа (finished)
        cv.wait(lock,[] { return !data_queue.empty() || finished});
        
        
        // делаем тяжелую работу
        
        // Если очередь пустая и работа закончена, выходим
        if (data_queue.empty() && finished) break;

        // Берём данные из очереди
        std::string data = data_queue.front();
        data_queue.pop();
            
        // Разблокируем чтобы другие потоки могли добавлять данные
        lock.unlock();

        file << data << endl;

    }
}

// Функция которая пробуждет поток
void stop_writer() {
    {
        lock_guard<mutex> lock(mtx);
        finished = true;
    }
    cv.notify_one(); // Обязательно "пинаем" поток, иначе он будет вечно спать в wait
}



// Функция которая будет увеломдять поток writer для работы 
void write(string data){
    {
        lock_guard<mutex> lock(mtx);
        data_queue.push(data);
    } // lock уничтожтся когда закроются эти скобки
    cv.notify_one(); // уведомляем один поток чтобы начал работать
}

int main(){
    thread writer_t(writer_task,"output.txt");
    
    write("Data");
    write("Login");
    
    stop_writer(); // Говорим о том что поток освобожден  наши данные загружены

    writer_t.join(); //завершаем 


    
...
}

```

## atomic 
Часто бывает состояние гонки, ее можно предотвратить при помощи mutex но это 
тяжелый способ, если данные простые например просто флажок можем использовать
```
atomic<typename> flag;
```

### Пример
```
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

std::atomic<int> safe_counter(0); // Безопасно
int unsafe_counter = 0;           // Опасно

void increment() {
    for (int i = 0; i < 10000; ++i) {
        safe_counter++;
        unsafe_counter++;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();

    std::cout << "Safe: " << safe_counter << std::endl;   // Всегда 20000
    std::cout << "Unsafe: " << unsafe_counter << std::endl; // Скорее всего < 20000
}

```
Никаких mutex для простых данных это идеально











