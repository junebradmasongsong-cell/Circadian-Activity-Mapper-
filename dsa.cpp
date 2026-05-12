

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct ActivityRecord {
    string timeSegment;
    string activity;
    int energyLevel;
};

vector<ActivityRecord> records;

string classifyProductivity(double average) {
    if (average >= 4.0) {
        return "High Productivity";
    } else if (average >= 3.0) {
        return "Moderate Productivity";
    } else {
        return "Low Productivity";
    }
}

string getRecommendation(string peakTime) {
    if (peakTime == "Morning") {
        return "Recommended Time: Morning\nUse this period for important tasks, deep focus, and difficult activities.";
    } else if (peakTime == "Afternoon") {
        return "Recommended Time: Afternoon\nUse this period for structured tasks, assignments, and routine productivity.";
    } else {
        return "Recommended Time: Evening\nUse this period for review, planning, reading, or light productive tasks.";
    }
}

void addRecord() {
    ActivityRecord record;
    int choice;

    cout << "\nSelect Time Segment:\n";
    cout << "1. Morning\n";
    cout << "2. Afternoon\n";
    cout << "3. Evening\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        record.timeSegment = "Morning";
    } else if (choice == 2) {
        record.timeSegment = "Afternoon";
    } else if (choice == 3) {
        record.timeSegment = "Evening";
    } else {
        cout << "Invalid time segment.\n";
        return;
    }

    cout << "Enter activity: ";
    getline(cin, record.activity);

    cout << "Enter energy level (1-5): ";
    cin >> record.energyLevel;

    if (record.energyLevel < 1 || record.energyLevel > 5) {
        cout << "Invalid energy level. Please enter 1 to 5 only.\n";
        return;
    }

    records.push_back(record);

    cout << "\nRecord added successfully.\n";
}

void viewRecords() {
    if (records.empty()) {
        cout << "\nNo records available.\n";
        return;
    }

    cout << "\nRecorded Entries\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < records.size(); i++) {
        cout << i + 1 << ". "
             << records[i].timeSegment << " | "
             << records[i].activity << " | Energy: "
             << records[i].energyLevel << "/5\n";
    }
}

void analyzeProductivity() {
    if (records.empty()) {
        cout << "\nNo records to analyze. Please add records first.\n";
        return;
    }

    double morningSum = 0, afternoonSum = 0, eveningSum = 0;
    int morningCount = 0, afternoonCount = 0, eveningCount = 0;

    for (int i = 0; i < records.size(); i++) {
        if (records[i].timeSegment == "Morning") {
            morningSum += records[i].energyLevel;
            morningCount++;
        } else if (records[i].timeSegment == "Afternoon") {
            afternoonSum += records[i].energyLevel;
            afternoonCount++;
        } else if (records[i].timeSegment == "Evening") {
            eveningSum += records[i].energyLevel;
            eveningCount++;
        }
    }

    double morningAvg = (morningCount > 0) ? morningSum / morningCount : 0;
    double afternoonAvg = (afternoonCount > 0) ? afternoonSum / afternoonCount : 0;
    double eveningAvg = (eveningCount > 0) ? eveningSum / eveningCount : 0;

    string peakTime = "Morning";
    double highestAvg = morningAvg;

    if (afternoonAvg > highestAvg) {
        highestAvg = afternoonAvg;
        peakTime = "Afternoon";
    }

    if (eveningAvg > highestAvg) {
        highestAvg = eveningAvg;
        peakTime = "Evening";
    }

    cout << fixed << setprecision(2);

    cout << "\nProductivity Analysis\n";
    cout << "----------------------------------------\n";

    if (morningCount > 0) {
        cout << "Morning: " << morningAvg << "/5 -> "
             << classifyProductivity(morningAvg) << "\n";
    } else {
        cout << "Morning: No record yet\n";
    }

    if (afternoonCount > 0) {
        cout << "Afternoon: " << afternoonAvg << "/5 -> "
             << classifyProductivity(afternoonAvg) << "\n";
    } else {
        cout << "Afternoon: No record yet\n";
    }

    if (eveningCount > 0) {
        cout << "Evening: " << eveningAvg << "/5 -> "
             << classifyProductivity(eveningAvg) << "\n";
    } else {
        cout << "Evening: No record yet\n";
    }

    cout << "\nPeak Productivity: " << peakTime << "\n\n";
    cout << getRecommendation(peakTime) << "\n";
}

void clearRecords() {
    records.clear();
    cout << "\nAll records cleared.\n";
}

void displayMenu() {
    cout << "\n========================================\n";
    cout << "        Circadian Activity Mapper\n";
    cout << "========================================\n";
    cout << "1. Add Record\n";
    cout << "2. View Recorded Entries\n";
    cout << "3. Analyze Productivity\n";
    cout << "4. Clear Records\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord();
                break;

            case 2:
                viewRecords();
                break;

            case 3:
                analyzeProductivity();
                break;

            case 4:
                clearRecords();
                break;

            case 5:
                cout << "\nThank you for using Circadian Activity Mapper.\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}