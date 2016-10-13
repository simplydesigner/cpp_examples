#ifndef SUBSTRING_H
#define SUBSTRING_H

namespace ns_substring {
    namespace ns_brute_force {
        /* O(len(s) * len(p)) */
        const char* strstr(const char* s, const char* p);
    }

    namespace ns_kmp {
        /* O(len(s) + len(p)) */
        const char* strstr(const char* s, const char* p);
    }
}

#endif
