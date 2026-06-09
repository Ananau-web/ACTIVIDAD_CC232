#pragma once

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "PQ_ComplHeap.h"
#include "PQ_LeftHeap.h"

namespace ods {

struct HuffmanSymbol {
  char symbol{};
  int frequency{};
};

struct HuffmanNode {
  char symbol{};
  int frequency{};
  std::shared_ptr<HuffmanNode> left{};
  std::shared_ptr<HuffmanNode> right{};

  HuffmanNode(char s, int f) : symbol(s), frequency(f) {}
  HuffmanNode(std::shared_ptr<HuffmanNode> a, std::shared_ptr<HuffmanNode> b)
      : symbol('\0'),
        frequency(a->frequency + b->frequency),
        left(std::move(a)),
        right(std::move(b)) {}

  bool leaf() const noexcept { return !left && !right; }
};

struct HuffmanBuildStep {
  int leftFrequency{};
  int rightFrequency{};
  int mergedFrequency{};
  std::string leftLabel;
  std::string rightLabel;
};

struct HuffmanLowerFrequencyFirst {
  bool operator()(const std::shared_ptr<HuffmanNode>& a,
                  const std::shared_ptr<HuffmanNode>& b) const {
    if (a->frequency != b->frequency) {
      return a->frequency > b->frequency;
    }
    return a->symbol > b->symbol;
  }
};

inline std::string huffmanNodeLabel(const std::shared_ptr<HuffmanNode>& u) {
  if (!u) return "null";
  if (u->leaf()) return std::string(1, u->symbol);
  return "*";
}

template <class PriorityQueue>
PriorityQueue huffmanMakeForest(const std::vector<HuffmanSymbol>& alphabet) {
  PriorityQueue pq;
  for (const auto& s : alphabet) {
    if (s.frequency > 0) {
      pq.insert(std::make_shared<HuffmanNode>(s.symbol, s.frequency));
    }
  }
  if (pq.empty()) {
    throw std::invalid_argument("Huffman requiere simbolos con frecuencia positiva");
  }
  return pq;
}

template <class PriorityQueue>
std::shared_ptr<HuffmanNode> huffmanGenerateTreeFromForest(PriorityQueue forest) {
  while (forest.size() > 1) {
    auto a = forest.delMax();
    auto b = forest.delMax();
    forest.insert(std::make_shared<HuffmanNode>(a, b));
  }
  return forest.delMax();
}

template <class PriorityQueue>
std::vector<HuffmanBuildStep> huffmanBuildTraceWith(const std::vector<HuffmanSymbol>& alphabet) {
  PriorityQueue forest = huffmanMakeForest<PriorityQueue>(alphabet);
  std::vector<HuffmanBuildStep> steps;
  while (forest.size() > 1) {
    auto a = forest.delMax();
    auto b = forest.delMax();
    steps.push_back({a->frequency, b->frequency, a->frequency + b->frequency,
                     huffmanNodeLabel(a), huffmanNodeLabel(b)});
    forest.insert(std::make_shared<HuffmanNode>(a, b));
  }
  return steps;
}

template <class PriorityQueue>
std::shared_ptr<HuffmanNode> huffmanGenerateTreeWith(const std::vector<HuffmanSymbol>& alphabet) {
  return huffmanGenerateTreeFromForest(huffmanMakeForest<PriorityQueue>(alphabet));
}

inline std::shared_ptr<HuffmanNode> huffmanGenerateTree(const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_ComplHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanGenerateTreeWith<PQType>(alphabet);
}

inline std::shared_ptr<HuffmanNode> huffmanGenerateTreeLeftHeap(
    const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_LeftHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanGenerateTreeWith<PQType>(alphabet);
}

inline std::vector<HuffmanBuildStep> huffmanBuildTrace(const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_ComplHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanBuildTraceWith<PQType>(alphabet);
}

inline std::vector<HuffmanBuildStep> huffmanBuildTraceLeftHeap(
    const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_LeftHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanBuildTraceWith<PQType>(alphabet);
}

inline void huffmanCollectCodes(const std::shared_ptr<HuffmanNode>& u,
                                const std::string& prefix,
                                std::unordered_map<char, std::string>& out) {
  if (!u) return;
  if (u->leaf()) {
    out[u->symbol] = prefix.empty() ? "0" : prefix;
    return;
  }
  huffmanCollectCodes(u->left, prefix + "0", out);
  huffmanCollectCodes(u->right, prefix + "1", out);
}

template <class PriorityQueue>
std::unordered_map<char, std::string> huffmanGenerateCodesWith(
    const std::vector<HuffmanSymbol>& alphabet) {
  std::unordered_map<char, std::string> codes;
  huffmanCollectCodes(huffmanGenerateTreeWith<PriorityQueue>(alphabet), "", codes);
  return codes;
}

inline std::unordered_map<char, std::string> huffmanGenerateCodes(
    const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_ComplHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanGenerateCodesWith<PQType>(alphabet);
}

inline std::unordered_map<char, std::string> huffmanGenerateCodesLeftHeap(
    const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_LeftHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanGenerateCodesWith<PQType>(alphabet);
}

inline std::string huffmanEncode(const std::string& text,
                                 const std::unordered_map<char, std::string>& codes) {
  std::string bits;
  for (char c : text) {
    auto it = codes.find(c);
    if (it == codes.end()) {
      throw std::invalid_argument("Caracter sin codigo Huffman");
    }
    bits += it->second;
  }
  return bits;
}

inline std::string huffmanDecode(const std::string& bits,
                                 const std::shared_ptr<HuffmanNode>& root) {
  if (!root) return {};
  if (root->leaf()) {
    return std::string(bits.size(), root->symbol);
  }

  std::string out;
  auto u = root;
  for (char bit : bits) {
    if (bit == '0') {
      u = u->left;
    } else if (bit == '1') {
      u = u->right;
    } else {
      throw std::invalid_argument("La cadena codificada solo puede contener 0 y 1");
    }
    if (!u) {
      throw std::invalid_argument("Secuencia Huffman invalida");
    }
    if (u->leaf()) {
      out.push_back(u->symbol);
      u = root;
    }
  }
  if (u != root) {
    throw std::invalid_argument("La cadena codificada termina a mitad de un codigo");
  }
  return out;
}

inline bool huffmanIsPrefixFree(const std::unordered_map<char, std::string>& codes) {
  for (const auto& [ca, sa] : codes) {
    for (const auto& [cb, sb] : codes) {
      if (ca == cb) continue;
      if (sb.rfind(sa, 0) == 0) return false;
    }
  }
  return true;
}

inline int huffmanWeightedPathLength(const std::vector<HuffmanSymbol>& alphabet,
                                     const std::unordered_map<char, std::string>& codes) {
  int total = 0;
  for (const auto& s : alphabet) {
    auto it = codes.find(s.symbol);
    if (s.frequency > 0 && it != codes.end()) {
      total += s.frequency * static_cast<int>(it->second.size());
    }
  }
  return total;
}

}  // namespace ods
