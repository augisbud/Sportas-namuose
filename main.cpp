#include <iostream>
#include <fstream>

using namespace std;

struct Results {
    char name[15];
    int days = 0;
    int minutes = 0;
    int morning = 0;
    int lunch = 0;
    int evening = 0;
    int setToday = 0;
};

int compare(char a[], char b[]) {
    for(int i = 0; a[i] != '\0'; i++) {
        if(a[i] != b[i])
            return 0;
    }
    return 1;
}

void sortStruct(Results Sports[5]) {
    for(int i = 0; i < 5; i++) {
        for(int j = i + 1; j < 5; j++) {
            string str1 = Sports[i].name;
            string str2 = Sports[j].name;
            if(str1 > str2)
                swap(Sports[j], Sports[i]);
        }
    }
}
int findExercise(Results Sports[5], char name[15]) {
    int sportID = -1;
    for(int k = 0; k < 5; k++)
        if(compare(Sports[k].name, name) && Sports[k].name[0] != '\0')
            sportID = k;

    return sportID;
}

int main() {
    ifstream data("U2.txt");

    int d, s, a = 0;
    data >> d;

    Results Sports[5];

    for(int i = 0; i < d; i++) {
        data >> s;
        for(int j = 0; j < s; j++) {
            int sportID = -1, minutes = 0;
            char name[15], timeOfDay[8];

            data.ignore();
            data.get(name, 15);

            sportID = findExercise(Sports, name);

            if(sportID == -1) {
                sportID = a;
                a++;
            }

            data.ignore();
            data.get(timeOfDay, 8);
            data >> minutes;

            for(int k = 0; k < 15; k++)
                Sports[sportID].name[k] = name[k];

            if(Sports[sportID].setToday == 0) {
                Sports[sportID].days++;
                Sports[sportID].setToday = 1;
            }


            if(compare(timeOfDay, "Rytas  "))
                Sports[sportID].morning++;
            else if(compare(timeOfDay, "Diena  "))
                Sports[sportID].lunch++;
            else if(compare(timeOfDay, "Vakaras"))
                Sports[sportID].evening++;

            Sports[sportID].minutes += minutes;
        }

        for(int k = 0; k < 5; k++)
            Sports[k].setToday = 0;
    }

    sortStruct(Sports);

    for(int i = 0; i < 5; i++) {
        cout << Sports[i].name << " " << Sports[i].days << " " << Sports[i].minutes << endl;
        if(Sports[i].morning != 0)
            cout << "Rytas   " << Sports[i].morning << endl;
        if(Sports[i].lunch != 0)
            cout << "Diena   " << Sports[i].lunch << endl;
        if(Sports[i].evening != 0)
            cout << "Vakaras " << Sports[i].evening << endl;
    }


    return 0;
}
