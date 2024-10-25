#ifndef MAIN_CPP_
#define MAIN_CPP_

#include "main.h"

namespace fs = std::filesystem;
namespace rx = rapidxml;

fs::path absPath(const std::string &filename_) {
  std::string fn = "D:/OneDrive/Documents/Code/Projects/OdfReader/";
  fs::path filename = fn + filename_;
  filename = fs::absolute(filename);
  std::cout << filename << '\n';
  return filename;
}

std::string open(const std::string &filename_) {
  fs::path filename = absPath(filename_);
  fs::path abs_filename = fs::absolute(filename);
  std::string entry_name = "content.xml";

  KZip::ZipArchive arch;
  arch.open(abs_filename);
  std::string xml_text = arch.entry(entry_name);
  arch.close();
  return xml_text;
}

void save(const std::string &filename, const std::string &content) {
  fs::path abs_filename = absPath(filename);
  std::ofstream outfile(abs_filename);  // Create an output file stream
  if (outfile.is_open()) {              // Check if the file opened successfully
    outfile << content << std::endl;    // Write text to the file
    outfile.close();                    // Close the file
    std::cout << "Text saved to " << abs_filename << std::endl;
  } else {
    std::cerr << "Error opening file." << std::endl;
  }
}

int main() {
  std::string content = open("accessions.ods");
  save("content.xml", content);

  rx::xml_document<> doc;
  doc.parse<0>(content.data());

  rx::xml_node<> *node = doc.first_node();
  std::cout << node->type() << '\n';
  std::cout << node->name() << '\n';
  std::cout << node->value() << '\n';
  for (rx::xml_attribute<> *attr = node->first_attribute(); attr;
       attr = attr->next_attribute()) {
    std::cout << "Name: " << attr->name() << '\n';
    std::cout << "Value: " << attr->value() << "\n\n";
  }
}

#endif
