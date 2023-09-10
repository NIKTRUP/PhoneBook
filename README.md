# PhoneBook

В качестве практики использования Protobuf, реализован проект телефонная книга.
## Использование
### Создание вектора
* конструктор по-умолчанию, создающий пустую телефонную книгу
```c++
  PhoneBook book({
      {"Ivan Ivanov"s, Date{1980, 1, 13}, {"+79850685521"s}},
      {"Margarita Petrova"s, Date{1989, 4, 23}, {"+79998887766"s, "+71112223344"s}},
      {"Just Birthday"s, Date{1989, 4, 23}, {}},
      {"No Birthday"s, std::nullopt, {"+7-4862-77-25-64"s}},
  });
```
### Методы
* сериализация телефонной книги
```c++
    std::ofstream output("path", std::ios::binary);
    book.SaveTo(output);
``` 
* десериализация телефонной книги
```c++
    std::ifstream input("path", std::ios::binary);
    PhoneBook book = DeserializePhoneBook(input);
```
* поиск по префиксу
```c++
    book.FindByNamePrefix("Ivan"sv)
```

## Системные требования
Компилятор С++ с поддержкой стандарта C++17 или новее, CMake страше версии 3.10, библиотека Protobuf.
