#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono> // For timing the execution

// Structure to represent an event with start and end days
struct Event {
    int start;
    int end;
};

// Comparator to sort events by end time (greedy strategy)
bool compareByEnd(const Event& a, const Event& b) {
    return a.end < b.end;
}

// Recursive binary search function to find the next event that starts on or after 'currentDay'
int findNextEventRecursive(const std::vector<Event>& events, int currentDay, int low, int high) {
    if (low > high) {
        return -1; // No valid event found
    }
    int mid = low + (high - low) / 2;
    
    if (events[mid].start >= currentDay) {
        int leftSearch = findNextEventRecursive(events, currentDay, low, mid - 1);
        return (leftSearch != -1) ? leftSearch : mid;
    } else {
        return findNextEventRecursive(events, currentDay, mid + 1, high);
    }
}

// Function to calculate the maximum number of events that can be attended using a greedy approach
int maxEvents(std::vector<Event>& events) {
    // Sort events by their end day (greedy strategy)
    std::sort(events.begin(), events.end(), compareByEnd);

    int attendCount = 0;
    int currentDay = 0; // Represents the current day we are trying to attend events

    for (size_t i = 0; i < events.size(); ++i) {
        // Find the next event that starts on or after the current day using recursive binary search
        int nextEventIdx = findNextEventRecursive(events, currentDay + 1, i, events.size() - 1);
        if (nextEventIdx != -1) {
            // Attend the event and update the current day
            currentDay = events[nextEventIdx].end;
            ++attendCount;
        }
    }

    return attendCount;
}

int main() {
    // List of events with their respective start and end days
     std::vector<Event> events = {
        {1, 3}, {2, 5}, {3, 7}, {5, 9}, {6, 10},
        {8, 11}, {9, 12}, {11, 14}, {13, 15}, {14, 16},
        {16, 18}, {17, 19}, {18, 20}, {19, 21}, {20, 22},
        {21, 23}, {23, 25}, {24, 26}, {25, 27}, {26, 28}
    };

    // Measure execution time
    auto start = std::chrono::high_resolution_clock::now();
    int maxAttended = maxEvents(events);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration of the computation
    std::chrono::duration<double> duration = end - start;

    // Output the result
    std::cout << "Maximum number of events that can be attended: " << maxAttended << std::endl;
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}