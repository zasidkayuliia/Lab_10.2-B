#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Spec {
    KOMPUTERNI_NAYKU,
    INFORMATUKA,
    MATEMATUKA_TA_EKONOMIKA,
    FIZUKA_TA_INFORMATUKA,
    TRYDOVE_NAVCHANNYA
};

string specStr[] = {
      "Комп'ютерні науки",
      "Інформатика",
      "Математика та економіка",
      "Фізика та інформатика",
      "Трудове навчання"
};

struct Student {
    string prizv;
    int kurs;
    Spec spec;
    int mark_fizuka;
    int mark_matematuka;
    union
    {
        int mark_programyvanna;
        int mark_chuselnimetodu;
        int mark_pedahohika;
    };
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const int kurs, const double avgScore);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть N: "; cin >> N;

    Student* p = new Student[N];

    string prizv;
    int kurs;
    int found;
    int avgScore;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента за прізвищем, курсом та середнім балом"
            << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            break;
        case 4:
            PrintIndexSorted(p, IndexSort(p, N), N);
            break;
        case 5:
            cout << "Введіть ключі пошуку:" << endl;
            cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
            cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
            cout << " прізвище: "; getline(cin, prizv);
            cout << " курс: "; cin >> kurs;
            cout << " середній бал: "; cin >> avgScore;
            cout << endl;

            if ((found = BinSearch(p, N, prizv, kurs, avgScore)) != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;

        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! Введіть номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Student* p, const int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << " прізвище: "; getline(cin, p[i].prizv);
        cout << " курс : "; cin >> p[i].kurs;
        cout << " спеціальність (0 - комп'ютерні науки, 1 - інформатика, 2 - математика та економіка,\n"
            << " 3 - фізика та інформатика, 4 - трудове навчання): "; cin >> spec;
        p[i].spec = (Spec)spec;
        cout << " оцінка з фізики: "; cin >> p[i].mark_fizuka;
        cout << " оцінка з математики: "; cin >> p[i].mark_matematuka;
      
        switch (p[i].spec)
        {
        case KOMPUTERNI_NAYKU:
            cout << " оцінка з програмування : "; cin >> p[i].mark_programyvanna;
            break;
        case  INFORMATUKA:
            cout << " оцінка з чисельних методів : "; cin >> p[i].mark_chuselnimetodu;
            break;
        case MATEMATUKA_TA_EKONOMIKA:
        case FIZUKA_TA_INFORMATUKA:
        case TRYDOVE_NAVCHANNYA:
            cout << " оцінка з педагогіки : "; cin >> p[i].mark_pedahohika;
            break;
        }
        cout << endl;
    }
    cout << endl;
}

void Print(Student* p, const int N) {
    cout << "==============================================================================================================================" << endl;
    cout << "| №  |  Прізвище       | Курс |    Спеціальність         | Фізика | Математика | Програмування| Чисельні методи | Педагогіка |" << endl;
    cout << "==============================================================================================================================" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(16) << left << p[i].prizv;
        cout << "| " << setw(4) << right << p[i].kurs << " ";
        cout << "| " << setw(25) << left << specStr[p[i].spec];
        cout << "| " << setw(6) << right << p[i].mark_fizuka << " ";
        cout << "| " << setw(10) << right << p[i].mark_matematuka << " ";

        if (p[i].spec == KOMPUTERNI_NAYKU) {
            cout << "| " << setw(12) << right << p[i].mark_programyvanna << " ";
            cout << "| " << setw(15) << right << " " << " ";
            cout << "| " << setw(10) << right << " " << " |";
        }
        else if (p[i].spec == INFORMATUKA) {
            cout << "| " << setw(12) << right << " " << " ";
            cout << "| " << setw(15) << right << p[i].mark_chuselnimetodu << " ";
            cout << "| " << setw(10) << right << " " << " |";
        }
        else {
            cout << "| " << setw(12) << right << " " << " ";
            cout << "| " << setw(15) << right << " " << " ";
            cout << "| " << setw(10) << right << p[i].mark_pedahohika << " |";
        }

        cout << endl;
    }

    cout << "==============================================================================================================================" << endl;
    cout << endl;
}


void Sort(Student* p, const int N) {
    Student tmp;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {

            double avg1 = (p[j].mark_fizuka + p[j].mark_matematuka + p[j].mark_programyvanna + p[j].mark_chuselnimetodu + p[j].mark_pedahohika) / 3.0;
            double avg2 = (p[j + 1].mark_fizuka + p[j + 1].mark_matematuka + p[j + 1].mark_programyvanna + p[j + 1].mark_chuselnimetodu + p[j + 1].mark_pedahohika) / 3.0;


            if ((avg1 < avg2) ||
                (avg1 == avg2 && p[j].kurs > p[j + 1].kurs) ||
                (avg1 == avg2 && p[j].kurs == p[j + 1].kurs && p[j].prizv > p[j + 1].prizv)) {
                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }
}
int* IndexSort(Student* p, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    int value, j;
    for (int i = 1; i < N; i++) {
        value = I[i];

        double avg_value = (p[value].mark_fizuka + p[value].mark_matematuka + p[value].mark_programyvanna + p[value].mark_chuselnimetodu + p[value].mark_pedahohika) / 3.0;

        j = i - 1;

        while (j >= 0) {
            double avg_j = (p[I[j]].mark_fizuka + p[I[j]].mark_matematuka + p[I[j]].mark_programyvanna + p[I[j]].mark_chuselnimetodu + p[I[j]].mark_pedahohika) / 3.0;


            if ((avg_j < avg_value) ||
                (avg_j == avg_value && p[I[j]].kurs > p[value].kurs) ||
                (avg_j == avg_value && p[I[j]].kurs == p[value].kurs && p[I[j]].prizv < p[value].prizv)) {
                I[j + 1] = I[j];
                j--;
            }
            else {
                break;
            }
        }
        I[j + 1] = value;
    }
    return I;
}
void PrintIndexSorted(Student* p, int* I, const int N) {
        cout << "==============================================================================================================================" << endl;
        cout << "| №  |  Прізвище       | Курс |    Спеціальність         | Фізика | Математика | Програмування| Чисельні методи | Педагогіка |" << endl;
        cout << "==============================================================================================================================" << endl;

        for (int i = 0; i < N; i++) {
            cout << "| " << setw(2) << right << i + 1 << " ";
            cout << "| " << setw(16) << left << p[I[i]].prizv;
            cout << "| " << setw(4) << right << p[I[i]].kurs << " ";
            cout << "| " << setw(25) << left << specStr[p[I[i]].spec];
            cout << "| " << setw(6) << right << p[I[i]].mark_fizuka << " ";
            cout << "| " << setw(10) << right << p[I[i]].mark_matematuka << " ";

            if (p[i].spec == KOMPUTERNI_NAYKU) {
                cout << "| " << setw(12) << right << p[I[i]].mark_programyvanna << " ";
                cout << "| " << setw(15) << right << " " << " ";
                cout << "| " << setw(10) << right << " " << " |";
            }
            else if (p[i].spec == INFORMATUKA) {
                cout << "| " << setw(12) << right << " " << " ";
                cout << "| " << setw(15) << right << p[I[i]].mark_chuselnimetodu << " ";
                cout << "| " << setw(10) << right << " " << " |";
            }
            else {
                cout << "| " << setw(12) << right << " " << " ";
                cout << "| " << setw(15) << right << " " << " ";
                cout << "| " << setw(10) << right << p[I[i]].mark_pedahohika << " |";
            }

            cout << endl;
        }

        cout << "==============================================================================================================================" << endl;
        cout << endl;
    }

int BinSearch(Student* p, const int N, const string prizv, const int kurs, const double avgScore)
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;

        double avg_m = (p[m].mark_fizuka + p[m].mark_matematuka + p[m].mark_programyvanna + p[m].mark_chuselnimetodu + p[m].mark_pedahohika) / 3.0;

        if (p[m].prizv == prizv && p[m].kurs == kurs && avg_m == avgScore)
            return m;

        if ((avg_m < avgScore) ||
            (avg_m == avgScore && p[m].kurs < kurs) ||
            (avg_m == avgScore && p[m].kurs == kurs && p[m].prizv < prizv))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    
    return -1;
}
