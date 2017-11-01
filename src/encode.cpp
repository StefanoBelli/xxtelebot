#include <tgbot/utils/encode.h>

constexpr char lookup[] = "0123456789abcdef";

std::string tgbot::utils::encode(const std::string &target) {
  std::stringstream stream;
  for (const char &c : target) {
    if ((48 <= c && c <= 57) ||  // 0-9
        (65 <= c && c <= 90) ||  // abc...xyz
        (97 <= c && c <= 122) || // ABC...XYZ
        (c == '-' || c == '_' || c == '.' || c == '~'))
      stream << c; // just put it in the stream
    else {
      stream << '%';
      stream << lookup[(c & 0xF0) >> 4];
      stream << lookup[(c & 0x0F)];
    }
  }
  return stream.str();
}

void tgbot::utils::encode(std::stringstream &stream,
                          const std::string &target) {
  for (const char &c : target) {
    if ((48 <= c && c <= 57) ||  // 0-9
        (65 <= c && c <= 90) ||  // abc...xyz
        (97 <= c && c <= 122) || // ABC...XYZ
        (c == '-' || c == '_' || c == '.' || c == '~'))
      stream << c; // just put it in the stream
    else {
      stream << '%';
      stream << lookup[(c & 0xF0) >> 4];
      stream << lookup[(c & 0x0F)];
    }
  }
}
