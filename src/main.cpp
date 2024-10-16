#ifndef MAIN
#define MAIN

#include <bit7z/bitfileextractor.hpp>
#include <iostream>
#include <rapidxml.hpp>

void open(const std::string *filename, std::string *out_str) {
  try {
    using namespace bit7z;
    // Assign 7-zip library dll
    Bit7zLibrary lib{"C:/Program Files/7-Zip/7z.dll"};
    // Opening the archive
    BitFileExtractor extractor{lib, BitFormat::Zip};
    // Extract content.xml text into buffer
    vector<byte_t> buffer;
    extractor.extractMatching(filename->c_str(), "content.xml", buffer);
    // Set out_str to content.xml text
    for (const char b : buffer) {
      *out_str = *out_str + b;
    }
  } catch (const bit7z::BitException &ex) {
    std::cout << ex.code() << ": " << ex.what() << '\n';
  }
}

int main() {
  using namespace rapidxml;

  const std::string filename{"accessions.ods"};
  std::string content_xml{};
  open(&filename, &content_xml);

  xml_document<> doc;
  doc.parse<0>(content_xml.data());

  xml_node<> *node = doc.first_node();
  std::cout << node->type() << '\n';
  std::cout << node->name() << '\n';
  std::cout << node->value() << '\n';
  for (xml_attribute<> *attr = node->first_attribute(); attr;
       attr = attr->next_attribute()) {
    std::cout << "Name: " << attr->name() << '\n';
    std::cout << "Value: " << attr->value() << "\n\n";
  }
}

#endif
