
/*

1. Обработка команд с разным контекстом: 
Команды, переданные в функцию receive с разным контекстом, 
должны обрабатываться независимо друг от друга. 
Другими словами - каждый connect создает свой контекст, 
который никак не пересекается с другим, в том числе при обработке команды receive.

2. Поведение при вызове connect из разных потоков, как и из одного, 
с разным размером блока команд: 
Если функция connect вызывается из разных потоков с 
разными значениями размера блока команд, каждый такой вызов должен инициировать 
уникальный контекст обработки с соответствующим размером блока. 
Это означает, что каждый поток будет иметь свои параметры для обработки команд, 
и эти параметры не будут влиять на другие потоки.




Добрый день
возможно, немного корявая формулировка в описании
main конечно должен осаться(куда ж мы без него) как точка входа вашей программы

но далее в main нужно вызывать методы connect/disconnect, receive для асинхронной обработки данных

пример есть в архиве homework.zip :
int main(int, char *[]) {
    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    auto h2 = async::connect(bulk);
    async::receive(h, "1", 1);
    async::receive(h2, "1\n", 2);
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);
    async::disconnect(h);
    async::disconnect(h2);

    return 0;
}

в материалах для лекции 25 -  Асинхронное программирование

Alexander Klyuchev, [02.03.2024 12:31]
но сама реализация
    async::connect(…);
    async::receive(…);
    async::disconnect(…);

должна быть в отдельной библиотеке подключаемой к вашей основной программе(с точкой входа в main)

Alexander Klyuchev, [02.03.2024 12:34]
контекст в данном случае это - h

это auto h = async::connect(bulk);
async::receive(h, "1", 1);
async::disconnect(h);

тоесть некий хендлер который вы получаете в connect
и можете использовать для последующего приема данных

идея в том что таких контекстов может быть несколько
и программа должна уметь их обрабатывать независимо

auto h = async::connect(bulk);
auto h2 = async::connect(bulk);
async::receive(h, "1", 1);
async::receive(h2, "1\n", 2);





*/




#include <async.h>
#include <utils.h>
#include <bulk.h>
#include <loggers.h>

#include <iostream>
#include <filesystem>
#include <thread>
#include <future>


int main(int argc, char **argv) {

    // create log directory
    std::filesystem::create_directory("./logs");

    // parse arguments
    size_t N = Utils::get_args(argc, argv);
    if (N == 0) return 1;

    try {

        // create loggers
        static ConsoleLogger c_logger = ConsoleLogger{};
        static FileLogger f_logger1 = FileLogger{};
        static FileLogger f_logger2 = FileLogger{};

        std::vector<iLogger*> loggers = {&c_logger, &f_logger1, &f_logger2};

        static LockFreeQueue<Utils::pair_Lines_and_Name> file_queue{};
        static LockFreeQueue<Utils::pair_Lines_and_Name> console_queue{};

        std::vector<LockFreeQueue<Utils::pair_Lines_and_Name>*> queues = {&file_queue, &console_queue};

        // attach queues
        c_logger.attach_queue(&console_queue);
        f_logger1.attach_queue(&file_queue);
        f_logger2.attach_queue(&file_queue);


        std::thread c_thread = c_logger.activate();
        std::thread f_thread1 = f_logger1.activate();
        std::thread f_thread2 = f_logger2.activate();

        // library logic
        auto h = async::connect(N, loggers, queues);
        auto h2 = async::connect(N, loggers, queues);

        async::receive(h, "1", 1);
        async::receive(h2, "1\n", 2);
        async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
        async::receive(h, "b\nc\nd\n}\n89\n", 11);
        
        async::disconnect(h);
        async::disconnect(h2);

        // start threads
        c_thread.join();
        f_thread1.join();
        f_thread2.join();

    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    
    return 0;

}
