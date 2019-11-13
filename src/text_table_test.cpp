#include "base/text_table.h"
#include <iostream>


void printNormalStyle() {
  std::cout << "===============Normal style ==============" << std::endl;
  common::base::TextTable t( '-', '|', '+' );
  t.add("Field");
  t.add("Type");
  t.add("NULL");
  t.endOfRow();

  t.add("column1");
  t.add("kInt32");
  t.add("No");
  t.endOfRow();

  t.add("column2");
  t.add("kInt64");
  t.add("YES");
  t.endOfRow();

  t.add("ts");
  t.add("kTimestamp");
  t.add("YES");
  t.endOfRow();
  std::cout << t << std::endl;
}

void printMySqlStyle() {
  std::cout << "===============Mysql style ==============" << std::endl;
  common::base::TextTable t( '-', '|', '+' ,common::base::TextTable::Style::MYSQL);
  t.add("Field");
  t.add("Type");
  t.add("NULL");
  t.endOfRow();

  t.add("column1");
  t.add("kInt32");
  t.add("No");
  t.endOfRow();

  t.add("column2");
  t.add("kInt64");
  t.add("YES");
  t.endOfRow();

  t.add("ts");
  t.add("kTimestamp");
  t.add("YES");
  t.endOfRow();
  std::cout << t << std::endl;
}


int main() {

  printNormalStyle();
  printMySqlStyle();
  return 0;
}
