## Segment Tree 

### Rational
It is a specific container that allows $$O(logN)$$ range queries for interval. Data can be updated.

### Short usage example
```cpp
#include "include/segment_tree.hpp"
...
    std::vector<int> data {9, 27, 81, -54, 9};
    auto max_lambda = [](const int a, const int b) noexcept {return std::max(a, b);};

    ::containers::segment_tree stree(data, max_lambda);

    auto const max_ {stree.query(0, 4)};
    std::cout << max_.value() << '\n'; //81 

```

### Implementation details
Everything should be ```noexcept```. If it is not in your case then just remove it from class, it is 3 mins job.

### License
MIT

### Disclosure
Despite of testing performed, no guarantees of any kind are given whatsoever. Use it at your own risk.
