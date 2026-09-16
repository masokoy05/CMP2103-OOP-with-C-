#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    double x;
        double y;
        };

        double calculateDistance(Point p1, Point p2) {
            return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
            }

            int main() {
                Point center;
                    cout << "Enter center point (x y): ";
                        cin >> center.x >> center.y;

                            int numBuffers;
                                cout << "Enter number of buffer distances: ";
                                    cin >> numBuffers;

                                        vector<double> buffers(numBuffers);
                                            cout << "Enter buffer radii: ";
                                                for (int i = 0; i < numBuffers; ++i) {
                                                        cin >> buffers[i];
                                                            }

                                                                sort(buffers.begin(), buffers.end());

                                                                    int numPoints;
                                                                        cout << "Enter number of points to test: ";
                                                                            cin >> numPoints;

                                                                                vector<Point> points(numPoints);
                                                                                    for (int i = 0; i < numPoints; ++i) {
                                                                                            cout << "Enter point " << i + 1 << " (x y): ";
                                                                                                    cin >> points[i].x >> points[i].y;
                                                                                                        }

                                                                                                            cout << "\n--- Buffer Analysis Results ---\n";
                                                                                                                for (double radius : buffers) {
                                                                                                                        cout << "\nPoints within buffer radius " << radius << ":\n";
                                                                                                                                bool found = false;

                                                                                                                                        for (const auto& p : points) {
                                                                                                                                                    double dist = calculateDistance(center, p);
                                                                                                                                                                if (dist <= radius) {
                                                                                                                                                                                cout << "  Point (" << p.x << ", " << p.y << ") - Distance: " << dist << "\n";
                                                                                                                                                                                                found = true;
                                                                                                                                                                                                            }
                                                                                                                                                                                                                    }

                                                                                                                                                                                                                            if (!found) {
                                                                                                                                                                                                                                        cout << "  No points found within this buffer.\n";
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                    }

                                                                                                                                                                                                                                                        return 0;
                                                                                                                                                                                                                                                        }