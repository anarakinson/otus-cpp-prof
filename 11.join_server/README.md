# Задание 11

Разработать асинхронный сервер выполняющий операции пересечения и симметрической разницы над множествами.
Внутренняя реализация должна предоставить возможность работать с двумя таблицами идентичной и фиксированной структуры. Одна таблица имеет название A, вторая - B и общую структуру:
```
{
    int id;
    std::string name;
}
```

id является первичным ключом и не может дублироваться в одной таблице.

Для пополнения коллекции и выполнения операций над множествами необходимо реализовать следующий протокол:
```
INSERT table id name
TRUNCATE table
INTERSECTION
SYMMETRIC_DIFFERENCE
```

### Реализовано

Сервер находится в заголовочнике `server.h`, шаблон таблицы в `table.h`, система управления таблицам в `database.h`

Запуск сервера происходит через:
```
join_server <port>
```

Запуск клиента:
```
client <address> <port>
```
По умолчанию значения `port = 9999`, `address = 127.0.0.1`.

Кроме того, в `server.h` по умолчанию включена опция `CREATE_DUMMY_DATABASE`, благодаря которой таблицы заполняются тестовыми данными и их можно сразу использовать.

Также сервер имеет функцию `HELP`, которая выводит список доступных комманд.

Команды регистронезависимы, можно послать `inTERseCtIon`, и команда будет распознана.