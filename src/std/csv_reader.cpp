#include "std/csv_reader.hpp"
#include <fstream>
#include <iostream>

Vector<Vector<String*>*>* CSVReader::readFile(String path) {
    Vector<Vector<String*>*>* table = new Vector<Vector<String*>*>(true);
    std::ifstream stream(path.c_str(), std::ios::in);

    if (!stream.is_open()) throw std::exception();

    std::filebuf* pbuf = stream.rdbuf();
    std::size_t file_size = pbuf->pubseekoff(0, stream.end, stream.in);
    pbuf->pubseekpos(0, stream.in);
    char* file = new char[file_size];
    pbuf->sgetn(file, file_size);
    stream.close();

    const char* file_end = file + file_size;
    const char* row_start = file;
    const char* row_end = file;

    while(true) {
        if (*row_end == '\n') {
            auto row = readRow(String(row_end - row_start, row_start));
            if (row != nullptr)
                table->append(row);
            row_start = ++row_end;
        }
        else {
            row_end++;
        }

        if (row_end == file_end)
            break;
    }
    return table;
}

Vector<String*>* CSVReader::readRow(const String &row) {
    if (row[0] == '#') return nullptr;
    Vector<String*>* fields = new Vector<String*>(true);
    fields->append(new String(""));
    int field_nr = 0;
    for (size_t i = 0; i < row.size(); i++) {
        char c { row[i] };
        switch (c) {
            case CSV_DELIMITER: // end of field
                fields->append(new String());
                field_nr++;
                break;
            case '\n':
                return fields;
            default:
                (*fields)[field_nr]->append(c);
                break;
        }
    }
    return fields;
}
