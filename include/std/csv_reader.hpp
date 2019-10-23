#ifndef FILE_CSV_READER_HPP
#define FILE_CSV_READER_HPP

#include "std/vector.hpp"
#include "std/string.hpp"
#include "std/unique_ptr.hpp"

class CSVReader {
public:
    unique_ptr<Vector<Vector<String*>*>> readFile(String path) const;
private:
    static const char CSV_DELIMITER = ';';
    static const bool CSV_IGNORE_HEADER = true;
    unique_ptr<Vector<String*>> readRow(const String &row) const;
};

#endif // FILE_CSV_READER_HPP
