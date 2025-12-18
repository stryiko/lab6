#include <iostream>
#include <limits>
#include <string>

using namespace std;

const int N = 50; // максимальний розмір ВХІДНОГО масиву

// ---------- Допоміжні функції введення ----------
int input_int(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error! Please enter an integer value.\n";
        } else {
            return value;
        }
    }
}

int input_int_range(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        value = input_int(prompt);
        if (value < minVal || value > maxVal) {
            cout << "Error! Please enter a value in range [" << minVal << ".." << maxVal << "].\n";
        } else {
            return value;
        }
    }
}

// ---------- Ввід/вивід масиву ----------
void input_array(int arr[], int &n) {
    n = input_int_range("Enter number of elements n (2..50): ", 2, N);
    for (int i = 0; i < n; i++) {
        arr[i] = input_int("A[" + to_string(i + 1) + "] = ");
    }
}

void output_array(const int arr[], int n) {
    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << (i + 1 == n ? "" : " ");
    }
    cout << "\n";
}

// =======================================================
// Завдання 1 (Таблиця 1) — Array49
// Дан цілочисельний масив розміру N. Якщо він є перестановкою (1..N),
// то вивести 0; інакше — номер першого неприпустимого елемента.
// =======================================================
int first_invalid_for_permutation_1_to_n(const int arr[], int n) {
    // used[v] = чи вже зустрічали число v
    bool used[N + 1] = {false};

    for (int i = 0; i < n; i++) {
        int x = arr[i];

        // 1) поза діапазоном 1..n
        if (x < 1 || x > n) {
            return i + 1; // 1-based позиція
        }

        // 2) дубль
        if (used[x]) {
            return i + 1; // перша позиція, де стало "не можна"
        }

        used[x] = true;
    }

    // якщо всі числа 1..n зустрілись рівно по 1 разу
    return 0;
}

void task_array49() {
    cout << "\n=== Task Array49 (Table 1) ===\n";
    int arr[N];
    int n;

    input_array(arr, n);
    output_array(arr, n);

    int res = first_invalid_for_permutation_1_to_n(arr, n);
    cout << "Answer (0 if it is a permutation, otherwise position of first invalid element): "
         << res << "\n";
}

// =======================================================
// Завдання 2 (Таблиця 2) — Array102
// Дан масив розміру N і ціле число K (1 ≤ K ≤ N).
// ПІСЛЯ елемента з номером K вставити новий елемент зі значенням 0.
// Без допоміжних масивів.
// =======================================================
void insert_zero_after_k(int arr[], int &n, int k) {
    // k — 1-based (1..n)
    // вставка ПІСЛЯ k-го => новий елемент стане на позицію k+1 (1-based),
    // тобто індекс k (0-based)
    int pos = k; // 0-based індекс вставки

    // Зсуваємо вправо хвіст масиву на 1, починаючи з кінця
    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos] = 0;
    n++;
}

void task_array102() {
    cout << "\n=== Task Array102 (Table 2) ===\n";
    int arr[N + 1]; // запас 1 елемент для вставки нуля
    int n;

    input_array(arr, n);

    int k = input_int_range("Enter K (1..n): ", 1, n);

    cout << "\nSource array:\n";
    output_array(arr, n);

    insert_zero_after_k(arr, n, k);

    cout << "Modified array (0 inserted after element #" << k << "):\n";
    output_array(arr, n);
}

// =======================================================
// Завдання 3 — меню вибору 1/2, багаторазово
// =======================================================
int main() {
    cout << "Lab 6. One-dimensional arrays (Array49 + Array102)\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1 - Task 1 (Array49: permutation check)\n";
        cout << "2 - Task 2 (Array102: insert 0 after K-th element)\n";
        cout << "0 - Exit\n";

        int choice = input_int_range("Your choice: ", 0, 2);

        if (choice == 0) {
            cout << "Program finished.\n";
            break;
        } else if (choice == 1) {
            task_array49();
        } else { // choice == 2
            task_array102();
        }
    }

    return 0;
}
