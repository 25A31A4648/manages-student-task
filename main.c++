#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Task {
    string description;
    bool completed;
};

vector<Task> tasks;

// Load tasks from file
void loadTasks() {
    ifstream file("tasks.txt");
    if (!file) return;

    string desc;
    bool status;

    while (getline(file, desc)) {
        file >> status;
        file.ignore();
        tasks.push_back({desc, status});
    }
    file.close();
}

// Save tasks to file
void saveTasks() {
    ofstream file("tasks.txt");
    for (auto &t : tasks) {
        file << t.description << endl;
        file << t.completed << endl;
    }
    file.close();
}

// Add task
void addTask() {
    cin.ignore();
    string desc;
    cout << "Enter task: ";
    getline(cin, desc);

    tasks.push_back({desc, false});
    saveTasks();
    cout << "Task added!\n";
}

// View tasks
void viewTasks() {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    for (int i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i].description;
        if (tasks[i].completed) cout << " [Done]";
        cout << endl;
    }
}

// Mark complete
void markComplete() {
    int n;
    viewTasks();
    cout << "Enter task number to mark complete: ";
    cin >> n;

    if (n > 0 && n <= tasks.size()) {
        tasks[n - 1].completed = true;
        saveTasks();
        cout << "Task marked as completed!\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

// Delete task
void deleteTask() {
    int n;
    viewTasks();
    cout << "Enter task number to delete: ";
    cin >> n;

    if (n > 0 && n <= tasks.size()) {
        tasks.erase(tasks.begin() + (n - 1));
        saveTasks();
        cout << "Task deleted!\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

int main() {
    loadTasks();
    int choice;

    do {
        cout << "\n===== Student Task Manager =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Complete\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markComplete(); break;
            case 4: deleteTask(); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
