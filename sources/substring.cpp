#include "substring.hpp"
#include <cstddef>
#include <cstring>
#include <cassert>
#include <vector>

namespace ns_substring {
namespace ns_brute_force {
    const char* strstr(const char* s, const char* p) {
        assert(s != nullptr);
        assert(p != nullptr);

        std::size_t len_s = std::strlen(s);
        std::size_t len_p = std::strlen(p);

        if (len_s >= len_p && len_p != 0)
        {
            for(std::size_t i = 0, j = 0; i <= len_s - len_p; ++i, j = 0) {
                for(; j <= len_p; ++j)
                    if (s[i + j] != p[j])
                        break;
                if (j == len_p)
                    return s + i;
            }
        }

        return nullptr;
    }
}

    namespace ns_kmp {
        namespace {
            std::vector<size_t>
            compute_prefix_function(const char *p) {
                assert(p != nullptr);

                std::size_t len_p = strlen(p);
                std::vector<size_t> pi(len_p);

                for(std::size_t i = 1; i < len_p; ++i) {
                    std::size_t k = pi[i - 1];
                    while((k > 0) && (p[k] != p[i]))
                        k = pi[k - 1];
                    if (p[k] == p[i])
                        ++k;
                    pi[i] = k;
                }

                return pi;
            }
        }

        const char* strstr(const char* s, const char* p) {
            assert(s != nullptr);
            assert(p != nullptr);

            auto pi = compute_prefix_function(p);
            std::size_t len_p = pi.size();

            for(std::size_t i = 0, j = 0; s[i]; ++i) {
                while((j > 0) && (s[i] != p[j]))
                    j = pi[j - 1];
                if (s[i] == p[j])
                    ++j;
                if (j == len_p)
                    return s + (i - len_p + 1);
            }

            return nullptr;
        }
    }
}
