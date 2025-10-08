#include <iostream>
#include "Tests.h"

using namespace std;

int main() {
    // Graph tests
    test_add_and_print();
    test_remove_vertex();
    test_remove_edge();
    test_mst_prim();
    test_mst_kruskal();
    test_mst_boruvka();
    test_shortest_path();
    test_no_path();

    // Transport tests
    test_transport_basic();
    test_land_transport();
    test_water_transport();
    test_air_transport();
    test_car();
    test_train();
    test_yacht();
    test_helicopter();

    // Environment tests
    test_point();
    test_obstacle();
    test_route();
    test_environment_add_show();
    test_find_optimal_route();
    test_move_transport();



    cout << "\nAll tests passed successfully.\n";
    return 0;
}