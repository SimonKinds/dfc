#include <algorithm>
#include "pattern-aggregator.hpp"

namespace dfc {
void PatternAggregator::add(RawPattern pat) {
  patterns_.emplace_back(std::move(pat));
}

std::vector<ImmutablePattern> PatternAggregator::aggregate() {
  removeDuplicates();

  return createPatterns();
}

void PatternAggregator::removeDuplicates() {
  std::sort(std::begin(patterns_), std::end(patterns_));
  patterns_.erase(std::unique(std::begin(patterns_), std::end(patterns_)),
                  std::end(patterns_));
}

std::vector<ImmutablePattern> PatternAggregator::createPatterns() const {
  std::vector<ImmutablePattern> newPatterns;
  newPatterns.reserve(patterns_.size());

  Pid pid = 0;
  for (auto&& pattern : patterns_) {
    newPatterns.emplace_back(pid, std::move(pattern));
    ++pid;
  }

  return newPatterns;
}
}  // namespace dfc
