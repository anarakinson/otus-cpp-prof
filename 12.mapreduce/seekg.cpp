

int fooo(const std::string &filename, size_t parts_number) {
    std::ifstream is (filename, std::ifstream::binary);
    // if not file - return;
    if (!is) { return 0; }
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    // return to the start
    is.seekg (0, is.beg);

    // allocate memory:
    char * buffer = new char [length];

    // read data as a block:
    is.read (buffer, length);

    is.close();

    // print content:
    std::cout.write (buffer, length);

    delete[] buffer;


    return 0;
}