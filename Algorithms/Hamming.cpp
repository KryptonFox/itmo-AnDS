#include <cstdint>
#include <expected>
#include <format>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

class BitVec {
public:
  BitVec(std::vector<char> &data) : data_(data) {};

  bool GetAt(size_t index) { return Byte(index) & BitPos(index); }
  void SetAt(size_t index, bool value) {
    value ? SetTrueAt(index) : SetFalseAt(index);
  }

  void SetTrueAt(size_t index) { Byte(index) |= BitPos(index); };
  void SetFalseAt(size_t index) { Byte(index) &= ~BitPos(index); };
  void FlipAt(size_t index) { Byte(index) ^= BitPos(index); };

  std::vector<char> &GetData() { return data_; }

private:
  std::vector<char> &data_;
  char BitPos(size_t index) { return (1 << (7 - index % 8)); };
  char &Byte(size_t index) { return data_[index / 8]; }
};

std::vector<char> HammingEncode(std::vector<char> &data, int encoded_len,
                                int data_len) {
  int codebits_count = encoded_len - data_len - 1;
  auto data_bits = BitVec(data);

  std::vector<char> encoded_data((encoded_len + 7) / 8, 0);
  auto encoded_bits = BitVec(encoded_data);

  int j = 0;
  for (int i = 0; i < encoded_len - 1; ++i) {
    if (i & (i + 1) && data_bits.GetAt(j++)) {
      encoded_bits.SetTrueAt(i);
    }
  }

  for (int codebit_pow = 0; codebit_pow < codebits_count; ++codebit_pow) {
    int codebit = 0;
    for (int i = 0; i < encoded_len - 1; ++i) {
      if ((i + 1) & (1 << codebit_pow)) {
        codebit ^= encoded_bits.GetAt(i);
      }
    }
    if (codebit) {
      encoded_bits.SetTrueAt((1 << codebit_pow) - 1);
    }
  }

  int parity = 0;
  for (int i = 0; i < encoded_len; ++i) {
    parity ^= encoded_bits.GetAt(i);
  }

  if (parity) {
    encoded_bits.SetTrueAt(encoded_len - 1);
  }

  return encoded_data;
}

std::expected<std::vector<char>, std::string>
HammingDecode(std::vector<char> &data, int encoded_len, int data_len) {
  int control_bits_count = encoded_len - data_len - 1;
  auto data_bits = BitVec(data);

  std::vector<char> decoded_data(data_len + 7 / 8, 0);
  auto decoded_bits = BitVec(decoded_data);

  uint32_t syndrome = 0;

  for (int i = control_bits_count - 1; i >= 0; --i) {
    syndrome <<= 1;
    int code = 0;
    for (int j = 0; j < encoded_len - 1; ++j) {
      if ((j + 1) & (1 << i)) {
        code ^= data_bits.GetAt(j);
      }
    }
    syndrome += code;
  }

  if (syndrome) {
    int parity = 0;
    for (int i = 0; i < encoded_len; ++i) {
      parity ^= data_bits.GetAt(i);
    }

    if (parity) {
      std::cout << std::dec << syndrome << std::endl;
      data_bits.FlipAt(syndrome - 1);
    } else {
      return std::unexpected<std::string>(std::string("Double error"));
    }
  }

  int j = 0;
  for (int i = 0; i < encoded_len - 1; ++i) {
    if (i & (i + 1)) {
      if (data_bits.GetAt(i)) {
        decoded_bits.SetTrueAt(j);
      }
      ++j;
    }
  }

  return decoded_data;
};

int main() {
  std::vector<char> input{0, 0, 0, 0, 0, 0x05, (char)0xe1, (char)0xaf};
  auto data = HammingEncode(input, 72, 64);

  std::cout << "Encoded:";
  for (int i = 0; i < 9; ++i) {
    std::cout << std::format("{:02x}:", data[i]);
  }
  std::cout << std::endl;

  data[3] ^= 0b00000001;

  auto decoded = HammingDecode(data, 72, 64).value();

  std::cout << "Decoded:";
  for (int i = 0; i < 8; ++i) {
    std::cout << std::format("{:02x}:", decoded[i]);
  }
}
