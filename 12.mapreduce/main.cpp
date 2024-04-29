

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>


std::vector<std::string> read_file(const std::string &path) {

    std::ifstream file{path};

    std::vector<std::string> out{};
    std::string line;
    
    while(std::getline(file, line)) {
        out.emplace_back(line);
    }

    return out;

}


std::vector<std::string> get_parts(const std::string &filename, size_t parts_number) {
    std::ifstream is (filename, std::ifstream::in | std::ifstream::binary);
    
    // if not file - return
    if (!is) { return {}; }


    // get length of file:
    is.seekg (0, is.end);
    size_t length = is.tellg();
    // return to the start
    is.seekg (0, is.beg);


    // create vector for storing parts of file
    std::vector<std::string> parts;
    parts.reserve(parts_number);

    // set size of the parts
    size_t default_part_size = length / parts_number + 1;
    size_t part_size = default_part_size;

    size_t begin = 0;
    while (begin < length) {

        // find next '\n'
        if (begin + part_size < length){
            // return part_size to default
            part_size = default_part_size;
            is.seekg((begin + part_size) * sizeof(char));
            while(true) {
                char *ch = new char [1];
                is.read(ch, 1);
                part_size++;
                // std::cout << "<" << std::string(ch, 1) << ">" << " ";
                if (*ch == '\n' || part_size > default_part_size * 2) { 
                    delete [] ch;
                    break; 
                };
            }
        }
        // if last part - set part_size so that all the data fits
        else if (begin + part_size > length) { part_size = length - begin; } 
        
        // find new position
        is.seekg(begin * sizeof(char));
        
        // allocate memory:
        char *buffer = new char [part_size * sizeof(char)];

        // read data as a block:
        is.read(buffer, part_size * sizeof(char));

        // add to vector
        parts.emplace_back(std::string{buffer, part_size});

        delete[] buffer;

        // move forward begin value 
        begin += part_size;

    }

    is.close();

    return parts;
}


int main() {

    auto addresses = get_parts("./data.txt", 4);

    int counter = 0;
    for (auto &x : addresses) {
        std::cout << counter++ << "\n";
        std::cout << x << "\n";
    }

}




/*

Артём, [27.03.2024 12:27]
@aklyuchev @Senya3485  
Добрый день!
Можете еще раз простыми словами объяснить, в чем суть домашнего задания mapreduce? В пдф довольно непонятно расписано.
Какая конечная цель? сделать список соответствий первых букв адресам?
т.е. в финальных файлах, которые выдаются на выходе программы должны быть пары типа:
qw - qwerty@mail.com
hello - hello@world.com
1 - 123@mail.com
так?

Alexander Klyuchev, [27.03.2024 12:59]
Добрый день!

Какую задачу решаем в дз? 
Нужно по набору строк (в pdf написано, что в строках будут емейлы, но это не важно) определить минимальную длину префикса, который позволит однозначно идентифицировать строку.
Например, есть строки:
abcdef
abcqwe
Префикс длины 4 abcd/abcq позволяет однозначно определить, из какой строки этот префикс. Префикс меньшей длины - не позволяет. Значит ответ будет 4.

Как мы это решаем?
Решаем в парадигме mapreduce, забудьте пока про бигдату, чтение из файлов и т.д. и подумайте о подходе. Т.е. создайте руками массив строк и попробуйте решить для него эту задачу с помощью std::transform + std::sort (при необходимости) + std::accumulate, представьте, что у вас такой ограниченный язык и работать с массивами можно только через эти три функции. Возможно, придётся сделать не один запуск transform+sort+accumulate, а несколько. 
Спойлер: например, можно в transform обрезать строки до длины 1, затем отсортировать, затем в accumulate проверить, что нет повторов, если повторы есть, повторить всё для префиксов длиной 2 и так до тех пор, пока все префиксы не будут уникальными.

Зачем нам эта чудная парадигма?
Эта парадигма "неплохо" ложится на обработку данных по частям. Например, вместо массива строк из предыдущего примера возьмите несколько подмассивов и решите эту же задачу, не склеивая подмассивы в один массив. Это реализуемо и используется в области BigData, когда все данные не влазят в память, лежат на разных узлах и не могут быть склеены.
Когда делаем домашку, представляем что у нас такая ситуация: есть очень большой набор данных в файле, мы не можем себе позволить обработать всё целиком, поэтому читаем файл кусочками и распихиваем обработку кусочков по разным потокам - как будто в Hadoop-кластере разные узлы обрабатывают блоки файла, хранящегося в HDFS. Каждый поток обрабатывает свою часть, результаты потом агрегируем. 

Как реализуем?
Хочется, чтобы проект был поделен на две части: универсальный map reduce фреймворк, который умеет решать не только задачу поиска длины префиксов, а любую задачу, и клиентский код, который с помощью этого универсального фреймворка решает задачку с префиксам

Alexander Klyuchev, [27.03.2024 12:59]
Скетч кода с комментами

Alexander Klyuchev, [27.03.2024 13:08]
Вопрос распределённой сортировки - это самое интересное. std::sort требует склеить данные в один массив чтобы отсортировать их, а если у нас нет такой возможности (данных много), то надо использовать другие алгоритмы сортировки. Можно гуглить по фразам: external sorting и многопутевая сортировка слиянием. Попробуйте делать ДЗ итеративно - от простого к сложному. Если прямо сейчас не готовы разбираться с external sorting, оставьте заглушку с std::sort. В других вопросах действуйте аналогично - напишите набросок, потом MVP, потом настоящий продукт, насколько успеете.

Alexander Klyuchev, [27.03.2024 14:14]
В ответе выводится просто число - да
Сколько букв минимально требуется - именно это определяет ваша программа
Несколько файлов, что это значит - если ваша mapreduce штуковина обрабатывает данные частями, то и ответ получится тоже частями, сагрегировать эти части ответа можно либо классическими подходами (если это не много данных), либо ещё одним проходом mapreduce (если это много данных), за это обычно отвечает не сам mapreduce фреймворк, а тот клиентский код, который использует фреймворк для обработки данных

Можете для вдохновения глянуть, как работают настоящие реализации, например, hadoop mapreduce


*/
