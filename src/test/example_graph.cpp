#include "src/base/graph.h"
#include "src/base/printf_utils.h"

int main(int argc, char* argv[]) {
    graph_adjvex_list_t list;
    vertex_t* A = list.add_vertex("A");
    vertex_t* B = list.add_vertex("B");
    vertex_t* C = list.add_vertex("C");
    vertex_t* D = list.add_vertex("D");
    vertex_t* E = list.add_vertex("E");
    vertex_t* F = list.add_vertex("F");
    vertex_t* G = list.add_vertex("G");
    vertex_t* H = list.add_vertex("H");

    list.add_edge(A, B, "3");
    list.add_edge(B, C, "5");
    list.add_edge(B, D, "5");
    list.add_edge(C, F, "10");
    list.add_edge(E, B, "7");
    list.add_edge(E, F, "7");
    list.add_edge(F, G, "2");
    list.add_edge(H, D, "6");
    list.add_edge(H, F, "6");

    string data = list.dump_dot();
    PRINTF_DEBUG("%s", data.c_str());

    if (list.find_edge("A", "B")) {
        PRINTF_DEBUG("AB");
    }
    if (list.find_edge("B", "C")) {
        PRINTF_DEBUG("BC");
    }
    if (list.find_edge("A", "C")) {
        PRINTF_DEBUG("AC");
    }

    data = list.dfs_traverse_recursion();
    PRINTF_DEBUG("%s", data.c_str());
    data = list.dfs_traverse();
    PRINTF_DEBUG("%s", data.c_str());
    data = list.bfs_traverse();
    PRINTF_DEBUG("%s", data.c_str());
    data = list.topological_sort();
    PRINTF_DEBUG("%s", data.c_str());

    return 0;
}