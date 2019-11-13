/*-------------------------------------------------------------------------
 * Copyright (C) 2019, 4paradigm
 * texttable.h.cpp
 *
 * Author: chenjing
 * Date: 2019/11/12
 *--------------------------------------------------------------------------
 **/
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace common {
namespace base {
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class TextTable {
public:
  enum class Alignment { LEFT, RIGHT };
  enum class Style { NORMAL, MYSQL };
  typedef std::vector<std::string> Row;
  TextTable(char horizontal = '-', char vertical = '|', char corner = '+',
            Style style = Style::NORMAL)
      : _horizontal(horizontal), _vertical(vertical), _corner(corner),
        _style(style) {}

  void setAlignment(unsigned i, Alignment alignment) {
    _alignment[i] = alignment;
  }

  const Style &style() const {
    return _style;
  }

  Alignment alignment(unsigned i) const { return _alignment[i]; }

  char vertical() const { return _vertical; }

  char horizontal() const { return _horizontal; }

  void add(std::string const &content) { _current.push_back(content); }

  void endOfRow() {
    _rows.push_back(_current);
    _current.assign(0, "");
  }

  template <typename Iterator> void addRow(Iterator begin, Iterator end) {
    for (auto i = begin; i != end; ++i) {
      add(*i);
    }
    endOfRow();
  }

  template <typename Container> void addRow(Container const &container) {
    addRow(container.begin(), container.end());
  }

  std::vector<Row> const &rows() const { return _rows; }

  void setup() const {
    determineWidths();
    setupAlignment();
  }

  std::string ruler() const {
    std::string result;
    result += _corner;
    for (auto width = _width.begin(); width != _width.end(); ++width) {
      result += repeat(*width, _horizontal);
      result += _corner;
    }

    return result;
  }

  int width(unsigned i) const { return _width[i]; }

private:
  char _horizontal;
  char _vertical;
  char _corner;
  const Style _style;
  Row _current;
  std::vector<Row> _rows;
  std::vector<unsigned> mutable _width;
  std::map<unsigned, Alignment> mutable _alignment;

  static std::string repeat(unsigned times, char c) {
    std::string result;
    for (; times > 0; --times)
      result += c;

    return result;
  }

  unsigned columns() const { return _rows[0].size(); }

  void determineWidths() const {
    _width.assign(columns(), 0);
    for (auto rowIterator = _rows.begin(); rowIterator != _rows.end();
         ++rowIterator) {
      Row const &row = *rowIterator;
      for (unsigned i = 0; i < row.size(); ++i) {
        _width[i] = _width[i] > row[i].size() ? _width[i] : row[i].size();
      }
    }

    if (_style == Style::MYSQL) {
      for (int j = 0; j < _width.size(); ++j) {
        _width[j] += 2;
      }
    }
  }

  void setupAlignment() const {
    for (unsigned i = 0; i < columns(); ++i) {
      if (_alignment.find(i) == _alignment.end()) {
        _alignment[i] = Alignment::LEFT;
      }
    }
  }
};

std::ostream &operator<<(std::ostream &stream, TextTable const &table) {
  table.setup();
  stream << table.ruler() << "\n";
  int line = 0;
  for (auto rowIterator = table.rows().begin();
       rowIterator != table.rows().end(); ++rowIterator) {
    TextTable::Row const &row = *rowIterator;
    stream << table.vertical();
    for (unsigned i = 0; i < row.size(); ++i) {
      auto alignment = table.alignment(i) == TextTable::Alignment::LEFT
                           ? std::left
                           : std::right;
      if (table.style() == TextTable::Style::MYSQL) {
        stream << std::setw(table.width(i)) << alignment << " " + row[i];
      } else {
        stream << std::setw(table.width(i)) << alignment << row[i];
      }
      stream << table.vertical();
    }
    stream << "\n";

    if (table.style() == TextTable::Style::NORMAL || line < 1 || line == table.rows().size() - 1) {
      stream << table.ruler() << "\n";
    }
    line++;
  }

  return stream;
}
} // namespace base
} // namespace common