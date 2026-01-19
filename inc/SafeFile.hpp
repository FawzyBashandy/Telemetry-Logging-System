#pragma once
#include <iostream>
enum class FileMode { ReadOnly, WriteAppend };
class SafeFile final {
private:
  int fd_{-1};

  void close();

public:
  SafeFile() = default;
  // Non-Copyable
  SafeFile(const SafeFile &) = delete;
  SafeFile &operator=(const SafeFile &) = delete;
  // Moveable
  SafeFile(SafeFile &&);
  SafeFile &operator=(SafeFile &&);

  // APIs
  bool open(const std::string &filePath, FileMode mode);

  bool readLine(std::string &out);

  bool write(const std::string &message);
  ~SafeFile();
};