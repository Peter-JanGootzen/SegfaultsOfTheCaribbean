#ifndef FILE_CSV_READER_HPP
#define FILE_CSV_READER_HPP

#include "std/vector.hpp"
#include "std/string.hpp"

class CSVReader {
public:
    Vector<Vector<String*>*>* readFile(String path);
private:
    static const char CSV_DELIMITER = ';';
    static const bool CSV_IGNORE_HEADER = true;
    Vector<String*>* readRow(const String &row);
};

#endif // FILE_CSV_READER_HPP
