#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono> // For timing the execution
#include <iomanip> // For setprecision
using namespace std; 

// Structure to represent an event with start and end days
struct Event {
    int start;
    int end;
};

// Comparator to sort events by end time (greedy strategy)
bool compareByEnd(const Event& a, const Event& b) {
    return a.end < b.end;
}

// Function to calculate the maximum number of events that can be attended using a greedy approach
int maxEvents(vector<Event>& events) {
    // Sort events by their end day (greedy strategy)
    sort(events.begin(), events.end(), compareByEnd);

    int attendCount = 0;
    int currentEndDay = 0; // Represents the end day of the last attended event

    for (const auto& event : events) {
        if (event.start >= currentEndDay) {
            // Attend the event and update the current end day
            currentEndDay = event.end;
            ++attendCount;
        }
    }

    return attendCount;
}

int main() {
   // List of 20 events with their respective start and end days
    std::vector<Event> events = {
        {1, 3}, {2, 5}, {3, 7}, {5, 9}, {6, 10},
        {8, 11}, {9, 12}, {11, 14}, {13, 15}, {14, 16},
        {16, 18}, {17, 19}, {18, 20}, {19, 21}, {20, 22},
        {21, 23}, {23, 25}, {24, 26}, {25, 27}, {26, 28}
    };

    // Measure execution time
    auto start = chrono::high_resolution_clock::now();
    int maxAttended = maxEvents(events);
    auto end = chrono::high_resolution_clock::now();

    // Calculate the duration of the computation
    chrono::duration<double> duration = end - start;

    // Output the result
    cout << "Maximum number of events that can be attended: " << maxAttended << endl;
    cout << fixed << setprecision(6);
    cout << "Execution time: " << duration.count() << " seconds" << endl;

    return 0;
}