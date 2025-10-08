#include "Graph.h"
#include "Transport.h"
#include "Environment.h"
#include <iostream>
#include <cassert>

using namespace std;

// GRAPH TESTS

void test_add_and_print() {
    cout << "\nTest: add_vertex, add_edge, print\n";
    Graph<int> g;
    g.add_edge(1, 2, 5);
    g.add_edge(2, 3, 2);
    g.add_edge(1, 3, 8);

    auto adj = g.getAdjacency();

    assert(adj.find(1) != adj.end());
    assert(adj.find(2) != adj.end());
    assert(adj.find(3) != adj.end());

    assert(adj.size() == 3);

    bool edge12 = false, edge23 = false, edge13 = false;
    for (auto [to, w] : adj[1]) {
        if (to == 2 && w == 5) edge12 = true;
        else if (to == 3 && w == 8) edge13 = true;
    }
    for (auto [to, w] : adj[2]) {
        if (to == 3 && w == 2) edge23 = true;
    }

    assert(edge12 && edge13 && edge23);

    cout << "test_add_and_print passed\n";
}

void test_remove_vertex() {
    cout << "\nTest: remove_vertex \n";
    Graph<int> g;
    g.add_edge(1, 2, 10);
    g.add_edge(2, 3, 20);

    g.remove_vertex(2);

    auto adj = g.getAdjacency();
    assert(adj.find(2) == adj.end());

    for (auto& [v, edges] : adj) {
        for (auto& [u, w] : edges)
            assert(u != 2);
    }

    cout << "test_remove_vertex passed\n";
}

void test_remove_edge() {
    cout << "\nTest: remove_edge \n";
    Graph<int> g;
    g.add_edge(1, 2, 4);
    g.add_edge(2, 3, 6);

    auto adj = g.getAdjacency();
    bool edge12 = false;
    for (auto [to, w] : adj[1])
        if (to == 2 && w == 4) edge12 = true;
    assert(edge12);

    g.remove_edge(1, 2);

    adj = g.getAdjacency();

    for (auto [to, w] : adj[1])
        assert(to != 2);
    for (auto [to, w] : adj[2])
        assert(to != 1);

    cout << "test_remove_edge passed\n";
}

void test_mst_prim() {
    cout << "\nTest: MST Prim \n";
    Graph<int> g;
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 3);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(2, 3, 4);
    g.add_edge(3, 4, 2);
    g.add_edge(4, 5, 6);

    auto [edges, totalWeight] = g.mst_prim(false);

    assert(edges.size() == 5);
    assert(totalWeight == 14);

    for (auto [u, v] : edges) {
        assert(u >= 0 && u <= 5);
        assert(v >= 0 && v <= 5);
    }

    cout << "test_mst_prim passed\n";
}

void test_mst_kruskal() {
    cout << "\nTest: MST Kruskal \n";
    Graph<int> g;
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 3);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(2, 3, 4);
    g.add_edge(3, 4, 2);
    g.add_edge(4, 5, 6);

    auto [edges, totalWeight] = g.mst_kruskal(false);

    assert(edges.size() == 5);
    assert(totalWeight == 14);

    for (auto [u, v] : edges) {
        assert(u >= 0 && u <= 5);
        assert(v >= 0 && v <= 5);
    }

    cout << "test_mst_kruskal passed\n";
}

void test_mst_boruvka() {
    cout << "\nTest: MST Boruvka \n";
    Graph<int> g;
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 3);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(2, 3, 4);
    g.add_edge(3, 4, 2);
    g.add_edge(4, 5, 6);

    auto [edges, totalWeight] = g.mst_boruvka(false);

    assert(edges.size() == 5);
    assert(totalWeight == 14);

    cout << "test_mst_boruvka passed\n";
}


void test_shortest_path() {
    cout << "\nTest: Dijkstra shortest_path \n";
    Graph<int> g;
    g.add_edge(1, 2, 4);
    g.add_edge(2, 3, 1);
    g.add_edge(1, 3, 7);
    g.add_edge(3, 4, 2);

    auto [path, dist] = g.shortest_path(1, 4, false);

    assert(dist == 7);
    vector<int> expected = { 1, 2, 3, 4 };
    assert(path == expected);

    cout << "test_shortest_path passed\n";
}

void test_no_path() {
    cout << "\nTest: shortest_path (no path) \n";
    Graph<int> g;
    g.add_edge(1, 2, 5);
    g.add_vertex(3);

    auto [path, dist] = g.shortest_path(1, 3, false);

    assert(dist == -1);
    assert(path.empty());

    cout << "test_no_path passed\n";
}


// TRANSPORT TESTS
// 
// Transport basic class test
void test_transport_basic() {
    cout << "\nTest: Transport basic \n";
    Transport t("Generic", 50);

    assert(t.getName() == "Generic");
    assert(t.getPosition() == 0);

    t.move(10);
    assert(t.getPosition() == 10);

    double prevSpeed = 50;

    t.brake(10);

    assert(t.getPosition() == 10);

    cout << "test_transport_basic passed\n";
}

// LandTransport test
void test_land_transport() {
    cout << "\nTest: LandTransport \n";
    LandTransport l("Truck", 60, 6, 100);

    assert(l.getName() == "Truck");
    assert(l.getPosition() == 0);
    assert(l.hasFuel());

    double initialFuelCheck = l.hasFuel();

    l.move(20);
    assert(l.getPosition() == 20);

    l.brake(10);

    l.accelerate(15);

    assert(l.hasFuel());

    cout << "test_land_transport passed\n";
}

// WaterTransport test
void test_water_transport() {
    cout << "\nTest: WaterTransport \n";
    WaterTransport w("Boat", 40, "Propeller", 200);

    assert(w.getName() == "Boat");
    assert(w.getPosition() == 0);
    assert(w.hasFuel());

    w.move(50);
    assert(w.getPosition() == 50);

    double posBefore = w.getPosition();
    w.move(0);
    assert(w.getPosition() == posBefore);

    assert(w.hasFuel());

    cout << "test_water_transport passed\n";
}

// AirTransport test
void test_air_transport() {
    cout << "\nTest: AirTransport \n";
    AirTransport a("Plane", 800, 10000, 5000);

    assert(a.getName() == "Plane");
    assert(a.getPosition() == 0);
    assert(a.hasFuel());

    a.move(200);

    assert(a.getPosition() == 200);

    a.brake(100);

    a.accelerate(200);

    assert(a.hasFuel());

    a.info();

    cout << "test_air_transport passed\n";
}

// Car test
void test_car() {
    cout << "\nTest: Car \n";
    Car car("BMW", 120, 4, "Petrol", 50, 0.2);

    assert(car.getName() == "BMW");
    assert(car.getPosition() == 0);
    assert(car.hasFuel());

    double initialFuel = car.getFuelLevel();

    car.move(100);
    assert(car.getPosition() == 100);
    assert(car.getFuelLevel() < initialFuel);

    double fuelBefore = car.getFuelLevel();
    car.move(200);
    double fuelAfter = car.getFuelLevel();

    assert(fuelAfter <= fuelBefore + 1e-6);

    assert(car.getPosition() > 100);

    car.accelerate(30);
    car.brake(50);

    if (car.hasFuel()) {
        cout << "Car still has fuel left: " << car.getFuelLevel() << " L\n";
    }
    else {
        cout << "Car ran out of fuel as expected.\n";
        assert(car.getFuelLevel() == 0);
    }

    car.info();
    cout << "test_car passed \n";
}



// Train test
void test_train() {
    cout << "\nTest: Train \n";
    Train train("InterCity", 150, 32, 10, 1000, 2.5);
    train.info();

    assert(train.getName() == "InterCity");
    assert(train.getPosition() == 0);
    assert(train.hasFuel());

    double initialFuel = train.getFuelLevel();

    train.move(100);
    assert(train.getPosition() == 100);
    assert(train.getFuelLevel() < initialFuel);

    double fuelBefore = train.getFuelLevel();
    train.move(600);
    double fuelAfter = train.getFuelLevel();

    assert(fuelAfter <= fuelBefore);

    assert(train.getPosition() >= 100);

    train.info();
    cout << "test_train passed\n";
}


// Yacht test
void test_yacht() {
    cout << "\nTest: Yacht \n";
    Yacht yacht("Sunseeker", 80, "Engine", 5, 300, 0.5);
    yacht.info();

    assert(yacht.getName() == "Sunseeker");
    assert(yacht.getPosition() == 0);
    assert(yacht.hasFuel());

    double initialFuel = yacht.getFuelLevel();

    yacht.move(100);
    assert(yacht.getPosition() == 100);
    assert(yacht.getFuelLevel() < initialFuel);

    double fuelBefore = yacht.getFuelLevel();
    yacht.move(1000);
    double fuelAfter = yacht.getFuelLevel();

    assert(fuelAfter <= fuelBefore);

    assert(yacht.getPosition() >= 100);

    yacht.info();
    cout << "test_yacht passed\n";
}


// Helicopter test
void test_helicopter() {
    cout << "\nTest: Helicopter \n";
    Helicopter heli("Black Hawk", 250, 3000, 6, 400, 1.5);
    heli.info();

    assert(heli.getName() == "Black Hawk");
    assert(heli.getPosition() == 0);
    assert(heli.hasFuel());

    double initialFuel = heli.getFuelLevel();

    heli.move(100);
    assert(heli.getPosition() == 100);
    assert(heli.getFuelLevel() < initialFuel);

    double fuelBefore = heli.getFuelLevel();
    heli.move(400);
    double fuelAfter = heli.getFuelLevel();

    assert(fuelAfter <= fuelBefore);

    assert(heli.getPosition() >= 100);

    heli.accelerate(50);
    heli.brake(100);

    heli.info();
    cout << "test_helicopter passed\n";
}


// ENVIRONMENT TESTS
// 
// Test of Point structure
void test_point() {
    cout << "\nTest: Point \n";

    Point p("Kyiv", 50.45, 30.52);
    cout << "Point created: " << p.getName() << " (" << p.getX() << ", " << p.getY() << ")\n";

    assert(p.getName() == "Kyiv");
    assert(abs(p.getX() - 50.45) < 1e-6);
    assert(abs(p.getY() - 30.52) < 1e-6);

    Point copy = p;
    assert(copy.getName() == "Kyiv");
    assert(abs(copy.getX() - p.getX()) < 1e-6);
    assert(abs(copy.getY() - p.getY()) < 1e-6);

    cout << "test_point passed\n";
}

// Test of Obstacle class
void test_obstacle() {
    cout << "\nTest: Obstacle \n";

    Obstacle o("Storm", 45.1, 28.3);
    cout << "Description: " << o.getDescription() << endl;
    cout << "Coordinates: (" << o.getX() << ", " << o.getY() << ")\n";

    assert(o.getDescription() == "Storm");
    assert(abs(o.getX() - 45.1) < 1e-6);
    assert(abs(o.getY() - 28.3) < 1e-6);

    Obstacle copy = o;
    assert(copy.getDescription() == o.getDescription());
    assert(abs(copy.getX() - o.getX()) < 1e-6);
    assert(abs(copy.getY() - o.getY()) < 1e-6);

    cout << "test_obstacle passed\n";
}


// Test of Route class
void test_route() {
    cout << "\nTest: Route \n";

    Point a("Lviv", 49.84, 24.03);
    Point b("Odessa", 46.48, 30.73);
    Route r(a, b, 800);

    r.showRoute();
    cout << "Distance: " << r.getDistance() << " km\n";

    assert(r.getStart().getName() == "Lviv");
    assert(r.getDestination().getName() == "Odessa");
    assert(abs(r.getStart().getX() - 49.84) < 1e-6);
    assert(abs(r.getDestination().getY() - 30.73) < 1e-6);
    assert(abs(r.getDistance() - 800) < 1e-6);

    Route copy = r;
    assert(copy.getStart().getName() == "Lviv");
    assert(copy.getDestination().getName() == "Odessa");
    assert(abs(copy.getDistance() - 800) < 1e-6);

    cout << "test_route passed\n";
}


// Test of Environment: adding routes and obstacles
void test_environment_add_show() {
    cout << "\nTest: Environment addRoute / addObstacle / showEnvironment\n";

    Environment env;

    env.addRoute(Route(Point("Kyiv", 50.45, 30.52), Point("Lviv", 49.84, 24.03), 540));
    env.addRoute(Route(Point("Lviv", 49.84, 24.03), Point("Odessa", 46.48, 30.73), 800));

    env.addObstacle(Obstacle("Traffic jam", 49.9, 30.4));
    env.addObstacle(Obstacle("Storm", 47.2, 30.5));

    assert(env.getRoutes().size() == 2);
    assert(env.getObstacles().size() == 2);

    const auto& routes = env.getRoutes();
    assert(routes[0].getStart().getName() == "Kyiv");
    assert(routes[0].getDestination().getName() == "Lviv");
    assert(abs(routes[0].getDistance() - 540) < 1e-6);

    assert(routes[1].getStart().getName() == "Lviv");
    assert(routes[1].getDestination().getName() == "Odessa");
    assert(abs(routes[1].getDistance() - 800) < 1e-6);

    const auto& obstacles = env.getObstacles();
    assert(obstacles[0].getDescription() == "Traffic jam");
    assert(abs(obstacles[0].getX() - 49.9) < 1e-6);
    assert(abs(obstacles[0].getY() - 30.4) < 1e-6);

    assert(obstacles[1].getDescription() == "Storm");
    assert(abs(obstacles[1].getX() - 47.2) < 1e-6);
    assert(abs(obstacles[1].getY() - 30.5) < 1e-6);

    env.showEnvironment();

    cout << "test_environment_add_show passed\n";
}


// Test of optimal route search (using Graph + Dijkstra)
void test_find_optimal_route() {
    cout << "\nTest: Environment::findOptimalRoute\n";

    Graph<int> g;
    g.add_edge(1, 2, 5);
    g.add_edge(2, 3, 3);
    g.add_edge(1, 3, 9);
    g.add_edge(3, 4, 4);

    Car car("BMW", 120, 4, "Petrol", 50, 0.2);

    Environment env;

    vector<int> path = env.findOptimalRoute(g, 1, 4, car);

    vector<int> expected = { 1, 2, 3, 4 };

    assert(path.size() == expected.size());
    for (size_t i = 0; i < path.size(); ++i) {
        assert(path[i] == expected[i]);
    }

    cout << "Expected route: ";
    for (int v : expected) cout << v << " ";
    cout << "\nFound route: ";
    for (int v : path) cout << v << " ";
    cout << endl;

    cout << "test_find_optimal_route passed\n";
}


// Test of transport movement along a route
void test_move_transport() {
    cout << "\nTest: Environment::moveTransport\n";

    Environment env;
    Car car("Audi", 100, 4, "Diesel", 40, 0.25);
    vector<int> route = { 1, 2, 3, 4 };

    double initialPos = car.getPosition();
    env.moveTransport(car, route);
    double finalPos = car.getPosition();

    assert(finalPos >= initialPos && "Transport did not move as expected");

    cout << "Initial position: " << initialPos << " km\n";
    cout << "Final position: " << finalPos << " km\n";
    cout << "test_move_transport passed\n";
}



