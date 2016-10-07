#ifndef SUBSTRING_H
#define SUBSTRING_H

namespace ns_substring {
    namespace ns_brute_force {
        /*  Алгоритм прямого поиска:
            O(len(s) * len(p))
        */
        const char* strstr(const char* s, const char* p);
    }

    namespace ns_kmp {
        /*  Алгоритм Д. Кнута, Д. Мориса и В. Пратта (КМП-поиск):
            O(len(s) + len(p))
        */
        const char* strstr(const char* s, const char* p);
    }
}

#endif
