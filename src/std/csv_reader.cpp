#include "std/csv_reader.hpp"
#include "std/unique_ptr.hpp"
#include "std/unique_array.hpp"
#include <fstream>
#include <iostream>
#include <exception>

unique_ptr<Vector<Vector<String*>*>> CSVReader::readFile(String path) const {
    std::ifstream stream(path.c_str(), std::ios::in);
    if (!stream.is_open()) throw std::ifstream::failure("Could not open file for reading.");

    unique_ptr<Vector<Vector<String*>*>> table { new Vector<Vector<String*>*>(true) };

    std::filebuf* pbuf { stream.rdbuf() };
    std::size_t file_size = pbuf->pubseekoff(0, stream.end, stream.in);
    pbuf->pubseekpos(0, stream.in);
    unique_array<char> file { unique_array<char>(new char[file_size]) };
    pbuf->sgetn(file.get(), file_size);
    stream.close();

    const char* file_end { file.get() + file_size };
    const char* row_start { file.get() };
    const char* row_end { file.get() };

    while(true) {
        //throw std::exception("LEAKY LEAKY?");
        if (*row_end == '\n') {
            auto row { readRow(String(row_end - row_start, row_start)) };
            if (row)
                table->append(row.release());
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

unique_ptr<Vector<String*>> CSVReader::readRow(const String &row) const {
    if (row[0] == '#') return nullptr;
    unique_ptr<Vector<String*>> fields { new Vector<String*>(true) };
    fields->append(new String(""));
    int field_nr { 0 };
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
