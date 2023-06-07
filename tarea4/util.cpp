#include <fstream>
#include <iostream>
#include <string>

void clearFile()
{
  std::ofstream outputFile("log.txt", std::ofstream::out | std::ofstream::trunc);
  if (outputFile.is_open())
  {
    outputFile.close();
  }
}

void writeStringToFile(const std::string &str)
{
  std::ofstream outputFile("log.txt", std::ofstream::app);
  if (outputFile.is_open())
  {
    outputFile << std::endl
               << str;
    outputFile.close();
  }
  else
  {
    std::cerr << "Unable to open file: "
              << "log.txt" << std::endl;
  }
}