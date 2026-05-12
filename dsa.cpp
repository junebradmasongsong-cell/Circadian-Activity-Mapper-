#include <iostream>    
#include <vector>     
#include <map>        
#include <fstream>    
#include <iomanip>    
#include <string>     

using namespace std;
// Stores one activity record.
struct ActivityRecord {
    string timeSegment;
    string activityType;
    int energyLevel;
};
// Stores multiple activity records.
vector<ActivityRecord> records;

// Used for grouping energy data.
vector<string> timeSegments = {
    "Morning",
    "Afternoon",
    "Evening"
};

// Used as activity choices in the menu.
vector<string> activityTypes = {
    "Deep Work",
    "Creative Task",
    "Routine Task",
    "Physical Task",
    "Social / Communication",
    "Rest / Break"
};

// Stores the energy demand of each activity type.
map<string, int> taskDemand = {
    {"Deep Work", 4},
    {"Creative Task", 3},
    {"Routine Task", 2},
    {"Physical Task", 3},
    {"Social / Communication", 2},
    {"Rest / Break", 1}
};

// Text file used for saving and loading records.
const string FILE_NAME = "activity_records.txt";

// Clears extra input from the keyboard buffer.
void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}
// Gets a valid number choice from the user.
int getChoice(int minValue, int maxValue) {
    int choice;

    while (true) {
        cin >> choice;

        if (!cin.fail() && choice >= minValue && choice <= maxValue) {
            clearInput();
            return choice;
        }

        cout << "Invalid input. Enter a number from "
             << minValue << " to " << maxValue << ": ";

        clearInput();
    }
}
// Pauses the console screen.
void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.get();
}
// Saves all activity records to a text file.
void saveRecords() {
    ofstream file(FILE_NAME.c_str());

    for (int i = 0; i < records.size(); i++) {
        file << records[i].timeSegment << "|"
             << records[i].activityType << "|"
             << records[i].energyLevel << endl;
    }

    file.close();
}
// Loads saved activity records from the text file.
void loadRecords() {
    ifstream file(FILE_NAME.c_str());

    if (!file) {
        return; // If file does not exist yet, start with empty records.
    }

    string timeSegment;
    string activityType;
    int energyLevel;

    while (getline(file, timeSegment, '|')) {
        getline(file, activityType, '|');
        file >> energyLevel;
        file.ignore(10000, '\n');

        ActivityRecord record;
        record.timeSegment = timeSegment;
        record.activityType = activityType;
        record.energyLevel = energyLevel;

        records.push_back(record);
    }

    file.close();
}
// Classifies the average energy level.
string classifyEnergy(double average) {
    if (average >= 4.2) {
        return "Peak Energy";
    } else if (average >= 3.5) {
        return "High Energy";
    } else if (average >= 2.5) {
        return "Moderate Energy";
    } else if (average >= 1.8) {
        return "Low Energy";
    } else {
        return "Depleted Energy";
    }
}
// Checks if the activity matches the user's energy level.
string taskFit(string activity, int energy) {
    int demand = taskDemand[activity];

    if (energy >= demand) {
        return "Good Match";
    } else if (energy == demand - 1) {
        return "Fair Match";
    } else {
        return "Poor Match";
    }
}
// Groups energy levels by time segment.
map<string, vector<int> > groupEnergyByTime() {
    map<string, vector<int> > groupedEnergy;

    // Create empty groups for Morning, Afternoon, and Evening.
    for (int i = 0; i < timeSegments.size(); i++) {
        groupedEnergy[timeSegments[i]] = vector<int>();
    }

    // Put each energy level into the correct time group.
    for (int i = 0; i < records.size(); i++) {
        string segment = records[i].timeSegment;
        int energy = records[i].energyLevel;

        groupedEnergy[segment].push_back(energy);
    }

    return groupedEnergy;
}
// Computes the average energy for each time segment.
map<string, double> computeAverages() {
    map<string, vector<int> > groupedEnergy = groupEnergyByTime();
    map<string, double> averages;

    for (int i = 0; i < timeSegments.size(); i++) {
        string segment = timeSegments[i];
        vector<int> values = groupedEnergy[segment];

        if (values.size() > 0) {
            double total = 0;

            for (int j = 0; j < values.size(); j++) {
                total += values[j];
            }

            averages[segment] = total / values.size();
        }
    }

    return averages;
}
// Adds a new activity record.
void addRecord() {
    cout << endl;
    cout << "        ADD ACTIVITY RECORD\n";
    cout << "\nSelect Time Segment:\n";
    for (int i = 0; i < timeSegments.size(); i++) {
        cout << i + 1 << ". " << timeSegments[i] << endl;
    }

    cout << "Choice: ";
    int timeChoice = getChoice(1, timeSegments.size());

    cout << "\nSelect Activity Type:\n";
    for (int i = 0; i < activityTypes.size(); i++) {
        cout << i + 1 << ". " << activityTypes[i] << endl;
    }

    cout << "Choice: ";
    int activityChoice = getChoice(1, activityTypes.size());

    cout << "\nEnter Energy Level (1-5): ";
    int energy = getChoice(1, 5);

    ActivityRecord newRecord;
    newRecord.timeSegment = timeSegments[timeChoice - 1];
    newRecord.activityType = activityTypes[activityChoice - 1];
    newRecord.energyLevel = energy;

    records.push_back(newRecord);
    saveRecords();

    cout << "\nRecord added successfully!\n";
    cout << "Task Fit: "
         << taskFit(newRecord.activityType, newRecord.energyLevel)
         << endl;
}
// Displays all saved activity records.
void viewRecords() {
    cout << "              RECORDED ENTRIES\n";
    cout << endl;
    if (records.size() == 0) {
        cout << "No records yet.\n";
        return;
    }

    cout << left
         << setw(5) << "No."
         << setw(15) << "Time"
         << setw(28) << "Activity"
         << setw(10) << "Energy"
         << setw(15) << "Task Fit"
         << endl;

    cout << string(73, '-') << endl;

    for (int i = 0; i < records.size(); i++) {
        cout << left
             << setw(5) << i + 1
             << setw(15) << records[i].timeSegment
             << setw(28) << records[i].activityType
             << setw(10) << records[i].energyLevel
             << setw(15) << taskFit(records[i].activityType, records[i].energyLevel)
             << endl;
    }
}
// Shows current insights or summary.
void showInsights() {
    cout << "            INSIGHTS / CURRENT STATE\n";
    cout << endl;
    if (records.size() == 0) {
        cout << "No records yet. Add records first.\n";
        return;
    }

    int totalEnergy = 0;
    map<string, int> countBySegment;

    for (int i = 0; i < records.size(); i++) {
        totalEnergy += records[i].energyLevel;
        countBySegment[records[i].timeSegment]++;
    }

    double overallAverage = (double) totalEnergy / records.size();

    string mostLogged = "";
    int highestCount = 0;

    for (int i = 0; i < timeSegments.size(); i++) {
        string segment = timeSegments[i];

        if (countBySegment[segment] > highestCount) {
            highestCount = countBySegment[segment];
            mostLogged = segment;
        }
    }

    cout << "Total Records: " << records.size() << endl;
    cout << "Most Logged Period: " << mostLogged << endl;
    cout << "Overall Average Energy: "
         << fixed << setprecision(2)
         << overallAverage << "/5" << endl;

    map<string, double> averages = computeAverages();

    cout << "\nEnergy Overview:\n";

    for (int i = 0; i < timeSegments.size(); i++) {
        string segment = timeSegments[i];

        if (averages.find(segment) != averages.end()) {
            cout << segment << ": "
                 << fixed << setprecision(2)
                 << averages[segment] << "/5 - "
                 << classifyEnergy(averages[segment])
                 << endl;
        } else {
            cout << segment << ": No data yet\n";
        }
    }
}
// Runs the final energy pattern analysis.
void analyzeEnergyPattern() {
    cout << "             ENERGY PATTERN ANALYSIS\n";
    cout << endl;
    if (records.size() == 0) {
        cout << "No records available. Add records first.\n";
        return;
    }

    map<string, double> averages = computeAverages();

    if (averages.size() == 0) {
        cout << "Not enough data to analyze.\n";
        return;
    }

    string peak = "";
    string lowest = "";

    double highestAverage = -1;
    double lowestAverage = 999;

    for (int i = 0; i < timeSegments.size(); i++) {
        string segment = timeSegments[i];

        if (averages.find(segment) != averages.end()) {
            double average = averages[segment];

            if (average > highestAverage) {
                highestAverage = average;
                peak = segment;
            }

            if (average < lowestAverage) {
                lowestAverage = average;
                lowest = segment;
            }
        }
    }

    int good = 0;
    int fair = 0;
    int poor = 0;

    for (int i = 0; i < records.size(); i++) {
        string fit = taskFit(records[i].activityType, records[i].energyLevel);

        if (fit == "Good Match") {
            good++;
        } else if (fit == "Fair Match") {
            fair++;
        } else {
            poor++;
        }
    }

    cout << "Peak Energy Period: " << peak << endl;
    cout << "Lowest Energy Period: " << lowest << endl;

    cout << "\nEnergy by Time Segment:\n";

    for (int i = 0; i < timeSegments.size(); i++) {
        string segment = timeSegments[i];

        if (averages.find(segment) != averages.end()) {
            cout << segment << ": "
                 << fixed << setprecision(2)
                 << averages[segment] << "/5 - "
                 << classifyEnergy(averages[segment])
                 << endl;
        } else {
            cout << segment << ": No data yet\n";
        }
    }

    cout << "\nTask Fit Summary:\n";
    cout << "Good Match: " << good << endl;
    cout << "Fair Match: " << fair << endl;
    cout << "Poor Match: " << poor << endl;

    cout << "\nRecommendation:\n";

    if (peak == lowest) {
        cout << "Most records are focused on " << peak
             << ". Add records from other time periods for better comparison.\n";
    } else {
        cout << "Your energy peaks at " << peak
             << ". Use this period for deep and demanding work.\n";

        cout << "Reserve " << lowest
             << " for lighter tasks, routine work, or recovery.\n";
    }
}
// Deletes one selected record.
void deleteRecord() {
    viewRecords();

    if (records.size() == 0) {
        return;
    }

    cout << "\nEnter record number to delete: ";
    int index = getChoice(1, records.size());

    records.erase(records.begin() + index - 1);
    saveRecords();

    cout << "Record deleted successfully.\n";
}
// Clears all activity records.
void clearRecords() {
    if (records.size() == 0) {
        cout << "No records to clear.\n";
        return;
    }

    cout << "Are you sure you want to clear all records? (Y/N): ";
    char confirm;
    cin >> confirm;
    clearInput();

    if (confirm == 'Y' || confirm == 'y') {
        records.clear();
        saveRecords();
        cout << "All records cleared.\n";
    } else {
        cout << "Clear cancelled.\n";
    }
}

void displayMenu() {
    cout << "        CIRCARDIAN ACTIVITY MAPPER\n";
    cout << endl;
    cout << "1. Add Activity Record\n";
    cout << "2. View Records\n";
    cout << "3. Show Insights\n";
    cout << "4. Analyze Energy Pattern\n";
    cout << "5. Delete Record\n";
    cout << "6. Clear All Records\n";
    cout << "7. Exit\n";
    cout << "Choice: ";
}

int main() {
    loadRecords();

    int choice;

    do {
        displayMenu();
        choice = getChoice(1, 7);

        switch (choice) {
            case 1:
                addRecord();
                pauseScreen();
                break;

            case 2:
                viewRecords();
                pauseScreen();
                break;

            case 3:
                showInsights();
                pauseScreen();
                break;

            case 4:
                analyzeEnergyPattern();
                pauseScreen();
                break;

            case 5:
                deleteRecord();
                pauseScreen();
                break;

            case 6:
                clearRecords();
                pauseScreen();
                break;

            case 7:
                cout << "\nThank you for using Circadian Activity Mapper.\n";
                break;
        }

    } while (choice != 7);

    return 0;
}
