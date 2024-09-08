
#include <iostream>
#include <ctime>
using namespace std;
#pragma warning (disable:4996);
struct element_date
{
    int day_week;
    int day;
    int month;
    int hour;
    int min;

};
struct note
{
    char* title;//��������
    char* description;//��������
    int priority;//��������� �� ��������
    time_t date;//���� ����������
    char* date_ch;
    element_date element;
};
//������� ��� ��������� �������� ���� �� ����������� � ���� ������ int
void Note_time(int& a, const char g[], time_t now)
{

    struct tmt;//����������� ��������� ��
    //��������� �� ������ ���������� ����������� � � ���� ���� ������� ��������� 

    char h[100];//������� ���������� ������
    //������� ���������� ���� ��������� �� � ����������� ���� ��������
    tm* timeinfo = localtime(&now);//������� ��������� ����� � �������� �� ����������(���, ������ � ��)

    strftime(h, 100, g, timeinfo);//� ������� ������� ��������� ������ ��� �������� � ���

    a = atoi(h);//������������� ������ ��� � ���

}
void Data_ch(note*& item, int size, tm& t)
{
    char buf[100];//�������������� ���������� �����
    strftime(buf, 100, "%A %d.%m.%y %H:%M", &t);//��������� ����� � ������ ������(�������� �������� ��������� tm � ���������� ��) 
    cin.ignore();//������� �����
    item[size].date_ch = new char[strlen(buf + 1)];//�������� ������
    strcpy(item[size].date_ch, buf);//�����������(��������) ���� ��������� ������ ������
}
//������� ��� ���������� ����
void Dat(note*& item, int size, tm& t)
{
    //����������� ��������� ������� � ������� ��������� ���������� ��
    // �������/������/���/� ��

    time_t second = time(NULL);//�������� ������� ����� � ��������

    //������� ������� � ����� � ���� ����� �������
    //������ ������ �������� � ���� ������ � ������� 31 ����
    int mass31[] = { 0, 2, 4, 6, 7, 9, 11 };
    //������ ������ �������� � ���� ������ � ������� 30 ����
    int mass30[] = { 3, 5, 8, 10 };
    //����� ������� ����������� � �������� �� ������� ���� ������� �� ��������� �� ����������� � 0 �� 11 
    //������(28 ����, �� ������� 2022 ��� �� ����������) ����� ����������� � ������

    //���������� ��� ������� ����� ��������� ���������� ������� � ����������� ����� �� ����
    bool a;
    t.tm_year = 2024 - 1900;
    do
    {
        //���� � ������� �� ������ ����(����� � �����)
        do
        {
            cout << "Enter Date\n";
            cout << "Enter number of day\n";
            cin >> t.tm_mday;
            cout << "Enter number month\n";
            cin >> t.tm_mon;
            //�� ��������� �� ���������� ���� ��� ����� ������ 0 ��� ���� ����� ������� ������ 12
            if (t.tm_mday <= 0 || t.tm_mon <= 0)
            {
                //���� ����� 0 �� ����� ����������� � �� ����������� �����
                cout << "number day or month shouldn't equal 0!\n";
                //���������� ��� �������� �������� ���� � �� ����� �����������
                                //� ������������ ���� ����
                a = 0;
            }
            //��������� �� ���� �� ������������ �� ���������� ���������� �������
            else if (t.tm_mon > 12)
            {
                cout << "Entered wrong month number\n";
                a = 0;
            }
            // ���� ��� �� ���� ������ �� ��������
            else
            {
                //�������� �� ������ 1 ��� ��� ������� ���� � 0
                t.tm_mon -= 1;
                //� ����� ���������� ���������� ���� �������
                for (int i = 0; i < 11; i++)
                {
                    //���� ����� ������������ ������ ������� �� ������� ��
                    if (t.tm_mon == mass31[i])
                    {
                        //��������� ������������ �� ���������� ���� ��� �������� ������
                        // ���� ���� ������ ��
                        if (t.tm_mday > 31)
                        {
                            //������� �� ����� ������ � �� ����������� ����� 
                            cout << "Number of days of doesn't correspond to the month!\n";
                            //���������� �������� 0 �� �� ����� ������������ ����� ����������� ����
                            a = 0;
                        }
                        //���� ���������� ���� ������������ ������ �� � �������� 1 � ��������� ���� ���� � ���� ���������
                        else
                            a = 1;
                    }
                    //� ������� �������� ��������� ����� �� ��������� ����������� ����
                    else if (t.tm_mon == mass30[i])
                    {
                        if (t.tm_mday > 30)
                        {
                            cout << "Number of days of doesn't correspond to the month!\n";
                            a = 0;
                        }
                        else
                            a = 1;
                    }
                    else if (t.tm_mon == 1)
                    {
                        //������� ����� 28 ���� � �� 29 �� ������� 2022 ��� �� ����������
                        if (t.tm_mday > 28)
                        {
                            cout << "Number of days of doesn't correspond to the month!\n";
                            a = 0;

                        }
                        else
                            a = 1;
                    }
                }
            }
        } while (a != 1);
        //���� ��� ����� ������� ����������
        do
        {
            cout << "Enter hour\n";
            cin >> t.tm_hour;
            cout << "Enter minutes\n";
            cin >> t.tm_min;
            //��������� �������� ����� ������������ �� 24 ������� ������� �������
            if (t.tm_hour > 23 || t.tm_min > 59)
                cout << "Time not specified correctly!\n";
            //��������� ���� ���� �� ������� ������ ����������
        } while (t.tm_hour > 23 || t.tm_min > 59);
        //t.tm_hour -= 1;
        t.tm_sec = 0;//���������� ������ ������������ ���� ��� ��� ��� ����� ����� �� ����� ����� �� ���������

        //���������� ��� � ���������� �� ���������
        item[size].date = mktime(&t);//������� �������� � ���������� �������� t t����� ��� ������ mt ��������� ��� ���/������... � �������
        if (item[size].date < second)//�������� �� ���� �� ������������ ���� �� ��������
        {
            item[size].date = 0;//�������� ���� � �������� ����� ������������� ��
            cout << "Entered past date or time!\n";
            a = 0;
        }
        else//���� ���� �������� �� ����������� �� � ������ ���
        {
            //� ��������� ���� ������� �� �������� �������� ��� ������/����/�����
            //��� ������������ � �������
            Note_time(item[size].element.day_week, "%w", item[size].date);
            Note_time(item[size].element.day, "%d", item[size].date);
            Note_time(item[size].element.month, "%m", item[size].date);
            Note_time(item[size].element.hour, "%H", item[size].date);
            Note_time(item[size].element.min, "%M", item[size].date);
            a = 1;
        }
    } while (a != 1);
}
//������� ��� ������� �������� ���������
void Del(note*& item, int size)
{
    for (int i = 0; i < size; i++)
    {
        delete[] item[i].title;
        delete[] item[i].description;
        //delete[] item[i].date_ch;
    }
    delete[] item;

}
//������� ���������� � ������ �� �����
//-------------------------------------------
void Show(note* item, int size)
{

    for (int i = 0; i < size; i++)
    {
        cout << "_________________________\n#" << i + 1 << "\nName\t\t" << item[i].title << "\nDescripton\t" << item[i].description;
        cout << "\npriority\t" << item[i].priority << "\nDate\t" << item[i].date_ch << "\n";
    }
    cout << "_________________________\n";
}
//------------------------------------------
//������� ��� ���������� �������
void Add_note(note*& item, int& size)
{

    struct tm t;

    char d[100];
    char r[100];
    note* temp = new note[size + 1];
    int a;
    do
    {
        cout << "0-Exit\n1-Add\n"; cin >> a;
        switch (a)
        {
        case 1:
            for (int i = 0; i < size; i++)
                temp[i] = item[i];
            delete[] item;
            item = temp;

            cout << "Add a new name for note\n"; cin.ignore(); cin.getline(r, 100);
            item[size].title = new char[strlen(r) + 1];
            strcpy(item[size].title, r);

            cout << "Add descripton for a note\n"; cin.getline(d, 100);
            item[size].description = new char[strlen(d) + 1];
            strcpy(item[size].description, d);
            do
            {
                cout << "Select priority by importance, pleas\n1-very important\n2-important\n3-not very important\n4-not important\n";
                cin >> item[size].priority;

            } while (item[size].priority > 4 || item[size].priority <= 0);

            Dat(item, size, t);
            Data_ch(item, size, t);
            size++;//������ ��������� ����������� �� 1
            Show(item, size);
            a = 0;
            break;
        case 0:
            a = 0;
            break;
        default:
            cout << "Wrong number:(\n";
            break;
        }
    } while (a != 0);
}



//������� �������� �� �������
//-------------------------------------------
void Del_note(note*& item, int& size, int index)
{
    int a;
    index -= 1;//������ -1 ��� ���� ����� �������� ����� ������������ �������������� ���������� ��� ����������� � 0
    do
    {
        if (index == -1)
            a = 1;
        else
        {
            note* temp = new note[size - 1];
            //� ����� �������� ��� ������� �� � ����� ������� �� ������������
            for (int i = 0; i < size; i++)
            {
                if (i < index)
                    temp[i] = item[i];
                else if (i > index)
                    temp[i - 1] = item[i];
            }
            delete[] item[index].title;
            delete[] item[index].description;
            delete[] item;
            item = temp;
            size--;
            Show(item, size);
            a = 1;
        }
    } while (a != 1);
}
//----------------------------------

//������� ��� ��������������
//----------------------------------
void Edit_note(note*& item, int& size, int index)
{
    index -= 1;
    int b = 0;
    {
        if (index == -1)
            b = 1;
        else
        {
            struct tm t;
            char r[100];
            int a;
            int nump = item[index].priority;
            cout << "What do you want to edit?\n1-Name\n2-Description\n3-Priority\n4-Data\n"; cin >> a;
            switch (a)
            {
            case 1:
                cout << "Add a new name for note\n"; cin.ignore(); cin.getline(r, 100);
                delete[] item[index].title;
                item[index].title = new char[strlen(r) + 1];
                strcpy(item[index].title, r);
                break;
            case 2:
                cout << "Add a new name for note\n"; cin.ignore(); cin.getline(r, 100);
                delete[] item[index].description;
                item[index].description = new char[strlen(r) + 1];
                strcpy(item[index].description, r);
                break;
            case 3:
                do
                {
                    cout << "Select priority by importance, pleas\n1-very important\n2-important\n3-not very important\n4-not important\n";
                    cin >> item[index].priority;

                    if (item[index].priority == nump)
                        cout << "Attenyion! The new priority shouldn't equal the old priority!\n";

                } while (item[index].priority > 4 || item[index].priority <= 0 || item[index].priority == nump);

                break;
            case 4:
                cout << "To develope^_^\n";
                break;
            default:
                cout << "Wrong number:(\n";
                break;
            }
            Show(item, size);
            b = 1;
        }
    } while (b != 1);
}
//--------------------------------------
//������� �� ������ ������ c 100% ���������
void Search(note*& item, int size, char* buf)
{
    char search[100];
    int counter = 0;//�������
    int k = 0;//��� ���������� ��� �������
    cout << "\tEnter name\t\n"; cin.ignore();  cin.getline(search, 100);//������ ������
    for (int i = 0; i < size; i++)
    {
        if (strcmp(buf, search) == 0)//���������� �������� ������� � �������� �� ����� 
            counter++;//���� ��� ��������� �� 100% ��������� �������
    }
    note* temp = new note[counter];//������� ����� ���������
    for (int i = 0; i < size; i++)
    {
        if (strcmp(buf, search) == 0)
        {
            temp[k] = item[i];
            k++;//��������� �� � ������ ����������
        }
    }
    if (counter > 0)//���� ������� ������ 0 �� ������� �� �����
    {
        Show(temp, counter);
        delete[] temp;
    }
    else//����� ����� ��� ����� ������� �� �������
        cout << "\tNo notes foud\n";
}
//������� ����� �������
void Search_note(note*& item, int& size, int a)
{
    //������� � ����������� �������
    int mass31[] = { 0, 2, 4, 6, 7, 9, 11 };
    int mass30[] = { 3, 5, 8, 10 };

    int counter = 0;//�������
    int k = 0;//��� ����������
    int prior;
    char date[100], month[100], hour[100], min[100];
    int b = 0;
    {
        cout << "What do you want to search\t\n0-Exit\t\n1-Name note\t\n2-Description\t\n3-Priority\t\n4-Date\t\n"; cin >> a; cout << "\t";
        switch (a)
        {
        case 1:
            Search(item, size, item->title);//���� ������� �� ��������
            b = 1;
            break;
        case 2:
            Search(item, size, item->description);//���� ������� �� ��������
            b = 1;
            break;
        case 3://�� ����������
            if (a == 3)//����� �� �� ������� ��� ���� �� ������� ���������������� ����������
            {
                do
                {
                    cout << "Enter priority 1-4\t";
                    cin >> prior;//������ ��������� ������� ����� ������
                } while (prior > 4 || prior <= 0);

                for (int i = 0; i < size; i++)
                    if (prior == item[i].priority)
                        counter++;//���� �� ������������ ������� ������� +1
                note* temp = new note[counter];//������� ���������
                for (int i = 0; i < size; i++)
                    if (prior == item[i].priority)
                    {
                        temp[k] = item[i];//��������� ��
                        k++;
                    }
                if (counter > 0)
                {
                    Show(temp, counter);
                    delete[] temp;
                }
                else
                {
                    cout << "\tNo notes foud\t\n";
                    b = 0;
                }
            }
            b = 1;
            break;
        case 4://�� ������ ���� � ������� ����������
            if (a == 4)
            {
                {
                    cout << "Enter number date\n\t";
                    cin >> date;
                    cout << "\tEnter number month\n\t";
                    cin >> month;
                    int da = atoi(date);
                    int mon = atoi(month);

                    if (da <= 0 || mon <= 0)//�������� ��� ������������ �� ����� ����� 0 � ������
                    {
                        cout << "\tnumber day or month shouldn't equal 0!\n";
                        b = 0;
                    }
                    else if (mon > 12)//��������� �� ����� �������
                    {
                        cout << "\tEntered wrong month number\n";
                        b = 0;
                    }
                    else
                    {
                        for (int i = 0; i < 11; i++)//����� ��� ������� 
                        {
                            mon -= 1;//����� -1 ��� ��� ��� ��� ���� ���������� � ���������� �������

                            //� �������� ��������� ���������� ������������ �� ����� ������ ���������� ����
                            if (mon == mass31[i])
                            {
                                if (da > 31)
                                {
                                    cout << "\tNumber of days of doesn't correspond to the month!\n";
                                    b = 0;
                                }
                                else
                                    b = 1;
                            }
                            else if (mon == mass30[i])
                            {
                                if (da > 30)
                                {
                                    cout << "\tNumber of days of doesn't correspond to the month!\n";
                                    b = 0;
                                }
                                else
                                    b = 1;
                            }
                            else if (mon == 1)
                            {
                                if (da > 28)
                                {
                                    cout << "\tNumber of days of doesn't correspond to the month!\n";
                                    b = 0;
                                }
                                else
                                    b = 1;
                            }
                        }
                    }
                } while (b != 1);
                int da = atoi(date);//��������� ���������� � ��� � ����������� ���������� ��� ��������(��� ���� �������� ��� �������������)
                int mon = atoi(month);
                do
                {
                    //������ �����
                    cout << "\tEnter hour\n\t";
                    cin >> hour;
                    cout << "\tEnter minutes\n\t";
                    cin >> min;
                    if (atoi(hour) > 23 || atoi(min) > 59)
                        cout << "\tTime not specified correctly!\n";
                } while (atoi(hour) > 23 || atoi(min) > 59);

                for (int i = 0; i < size; i++)
                    if (da == item[i].element.day && mon == item[i].element.month && atoi(hour) == item[i].element.hour && atoi(min) == item[i].element.min)
                        counter++;//���������� ������ ������� ���� �������� ������ ������������ �������� ��������� � ��������+1
                note* temp = new note[counter];
                for (int i = 0; i < size; i++)
                    if (da == item[i].element.day && mon == item[i].element.month && atoi(hour) == item[i].element.hour && atoi(min) == item[i].element.min)
                    {
                        temp[k] = item[i];//��������� ���������
                        k++;
                    }
                if (counter > 0)
                {
                    Show(temp, counter);
                    delete[] temp;
                }
                else
                {
                    cout << "\tNo notes foud\t\n";
                    b = 0;
                }
            }
            b = 1;
            break;
        case 0:
            b = 1;
            break;
        default:
            cout << "Wrong number:(\t\n";
            break;
        }
    } while (b != 1);
}
//������� ������ �� ����/�������/�������
//----------------------------------------
void D_W_M(note*& item, int& size, string a)
{
    //����������� ���������
    struct tm t;
    int day, day_week, month;
    //������ ������� ����� � ���
    time_t now = time(NULL);

    //�������� ������ �������� ��� ������, ����� � ����
    Note_time(day_week, "%w", now);
    Note_time(day, "%d", now);
    Note_time(month, "%m", now);


    int k = 0;
    int time_size = 0;
    note* temp;
    if (a == "day")
    {
        //������ ������ ��� ������ ��� �� ����
        for (int i = 0; i < size; i++)
            if (item[i].element.day_week == day_week && item[i].element.day == day && item[i].element.month == month)
                time_size++;

        //������� �������� ������
        note* temp = new note[time_size];
        for (int i = 0; i < size; i++)
        {
            if (item[i].element.day_week == day_week && item[i].element.day == day && item[i].element.month == month)
            {
                //�������� ��������
                temp[k] = item[i];
                k++;
            }
        }
        if (time_size > 0)
        {
            Show(temp, time_size);
            delete[] temp;
        }
        else
            cout << "\tYou havent work this " << a << endl;
    }
    //���� ���� �� ������� ������
    else if (a == "week")
    {
        //������ ���������� ���� �� �����������
        int day_before_Sun = 7 - day_week;//������� ����� ��� ������ ����� ����� � 0-6

        t.tm_year = 2022 - 1900;
        t.tm_mon = month - 1;//�������� 1 ��� ���  � ��������� ��� ����������� � ���� 
        if (day_before_Sun == 7)//���� ������� ����������� ��
            t.tm_mday = day;//����������� ���������� �������� �������� ���
        else
            t.tm_mday = day + day_before_Sun;//����������� �����������
        t.tm_hour = 23;
        t.tm_min = 59;
        t.tm_sec = 0;
        time_t Sunday = mktime(&t);//��������� ��� � �������

        for (int i = 0; i < size; i++)
        {
            if (Sunday >= item[i].date)//���� ������� ������ ��� ����� ����������� ��������� � �������� +1
                time_size++;
        }
        note* temp = new note[time_size];
        for (int i = 0; i < size; i++)
        {
            if (item[i].date <= Sunday)
            {
                temp[k] = item[i];
                k++;
            }

        }
        if (time_size > 0)
        {
            Show(temp, time_size);
            delete[] temp;
        }
        else
            cout << "\tYou havent work this " << a << endl;
    }
    else if (a == "month")
    {
        for (int i = 0; i < size; i++)
            if (item[i].element.month == month)
                time_size++;

        note* temp = new note[time_size];
        for (int i = 0; i < size; i++)
        {
            if (item[i].element.month == month)
            {
                temp[k] = item[i];
                k++;
            }
        }
        if (time_size > 0)
        {
            Show(temp, time_size);
            delete[] temp;
        }
        else
            cout << "\tYou havent work this " << a << endl;
    }
}

//������� ��� ������ ���� ����������� ��� �� �����
void Switch_D_W_M(note*& item, int& size, int a)
{
    do
    {
        cout << "\tSelect search group\n0-Exit\n1-Business on day\n2-Business on this week\n3-Business on this month\n"; cin >> a;
        switch (a)
        {
        case 1:
            cout << "Work on day\n";
            D_W_M(item, size, "day");
            a = 0;
            break;
        case 2:
            cout << "Work on week\n";
            D_W_M(item, size, "week");
            a = 0;
            break;
        case 3:
            cout << "Work on month\n";
            D_W_M(item, size, "month");
            break;
        case 0:
            a = 0;
            break;
        default:
            cout << "Wrong number:(\n";
            break;
        }
    } while (a != 0);

}
//___________________________________________

//������� ���������� �� ���������� � �� ���������� ����
//-------------------------------------------
void Sort_notes(note*& item, int& size, char a, char b)
//������ ��������� � ���� 2 ������� ����������  ��� ���� ����� ����� ����
//������� ��� ����������� ��������� 
{
    //������� ���������� �� ����������

    if (a == '-' && b == 'p')
    {
        //���������� �� �����������
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size - 1; j++)
            {
                if (item[j].priority > item[j + 1].priority)
                    swap(item[j], item[j + 1]);
                //���� � ��� ���������� ���������� �� ������ �������� ������������� �� ����
                // ��� ������ ���� ��� ����� ���� � ������
                else if (item[j].priority == item[j + 1].priority)
                    if (item[j].date < item[j + 1].date)
                        swap(item[j + 1], item[j]);
            }
    }
    else if (a == '+' && b == 'p')
    {
        //���������� �� ��������
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size - 1; j++)
            {
                if (item[j].priority < item[j + 1].priority)
                    swap(item[j + 1], item[j]);
                //���� � ��� ���������� ���������� �� ������ �������� ������������� �� ����
                // ��� ������ ���� ��� ����� ���� � ������
                else if (item[j].priority == item[j + 1].priority)
                    if (item[j].date > item[j + 1].date)
                        swap(item[j], item[j + 1]);


            }
    }
    //������ ���������� �� ����
    else if (a == '-' && b == 'd')
    {
        //���������� �� �����������
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size - 1; j++)
            {
                if (item[j].date > item[j + 1].date)
                    swap(item[j], item[j + 1]);
                else if (item[j].date == item[j].date)
                    if (item[j].priority < item[j + 1].priority)
                        swap(item[j], item[j + 1]);
            }
    }

    else if (a == '+' && b == 'd')
    {
        //���������� �� ��������
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size - 1; j++)
            {
                if (item[j].date < item[j + 1].date)
                    swap(item[j + 1], item[j]);
                else if (item[j].date == item[j].date)
                    if (item[j].priority > item[j + 1].priority)
                        swap(item[j], item[j + 1]);
            }
    }
    Show(item, size);
}
//������� ��� ������ ���� ��������� ����� �� ������ �������� � �������� ����
void Switch_sort(note*& item, int& size, int a)
{

    do
    {
        cout << "How to sort the notes?\n0-Exit\n1-By priority\n2-By the number of days\n"; cin >> a;
        switch (a)
        {
        case 1:
            cout << "Sort list\n1-Hight to low\n2-Low to hight\n"; cin >> a;
            switch (a)
            {
            case 1:
                Sort_notes(item, size, '+', 'p');
                a = 0;
                break;
            case 2:
                Sort_notes(item, size, '-', 'p');
                a = 0;
                break;
            default:
                cout << "Wrong number:(\n";
                break;
            }
            break;
        case 2:
            cout << "\n\tSort list\t1-Hight to low\n2-Low to hight\n"; cin >> a;
            switch (a)
            {
            case 1:
                Sort_notes(item, size, '+', 'd');
                a = 0;
                break;
            case 2:
                Sort_notes(item, size, '-', 'd');
                a = 0;
                break;
            default:
                cout << "Wrong number:(\n";
                break;
            }
            break;
        case 0:
            a = 0;
            break;
        default:
            cout << "Wrong number:(\n";
            break;

        }
    } while (a != 0);
}
//__________________________________
void File(note*& item, int& size, char a)
{
    char filename[100];
    cout << "Enter name file\n"; cin.ignore(); cin.getline(filename, 100);//������ �������� �����
    char buff[100];//�����
    FILE* stream;//������� ����� � ��������� � �����


    if (a == 'W')//���� ���������� � ����
    {

        stream = fopen(filename, "w");//��������� ����� ��� ������
        if (!stream)//���� ���� �� ������
            cout << "File not open!\n";
        else
        {
            for (int i = 0; i < size; i++)//���������� ��� ��������
            {
                fputs(item[i].title, stream);//�������� � ���� ����
                fputc(';', stream);//�������� � ���� ����� � �������

                fputs(item[i].description, stream);
                fputc(';', stream);


                sprintf(buff, "%i", item[i].priority);//��������� �������� � ��� ��� ��� ��� ������ ���� ������ �� ������������
                fputs(buff, stream);
                fputc(';', stream);

                fputs(item[i].date_ch, stream);

                fputc(';', stream);//������ � ����� ����� � �������
                fputc('\n', stream);//��������� ��������� ������� �� ������ ������


            }
            fclose(stream);//��������� �����
        }

    }
    else if (a == 'R')
    {
        char* t;//��������� �� ����� ������

        stream = fopen(filename, "r");
        if (!stream)
            cout << "File not open!\n";
        else
        {
            int counter = 0;
            while (fgets(buff, 100, stream))//������� ��������� ������� ������ � ����� ���� ��� ���� ����� �������� ��� �����, ����
                counter++;
            rewind(stream);//���������� ������ � ������ ����� ��� ��� �� ������� � �����

            note* temp = new note[size + counter];//������, ��������, ������������ ������ �� ����� ������
            for (int i = 0; i < size; i++)
                temp[i] = item[i];
            delete[] item;
            item = temp;

            for (int i = size; i < size + counter; i++)//���������� ��� �������� ���� ������ � �����
            {
                fgets(buff, 100, stream);//������ ������

                t = strtok(buff, ";");//�������� ������� � ��� �� ����� � ������� ����� ����� t �����������
                item[i].title = new char[strlen(t) + 1];//���������� ����� ������ ��� ���� ���������
                strcpy(item[i].title, t);//�������� ���� ���������� �

                t = strtok(NULL, ";");//��������� NULL ������ �� ����������� � ���������� ���� �������� ��� ��� �� �����������
                item[i].description = new char[strlen(t) + 1];
                strcpy(item[i].description, t);

                t = strtok(NULL, ";");
                item[i].priority = atoi(t);//������������� ��������� � ��� ������ ���

                t = strtok(NULL, ";");
                item[i].date_ch = new char[strlen(t) + 1];
                strcpy(item[i].date_ch, t);
            }
            size += counter;//��������� � ��������� ������� ������ ��������� � �����
            fclose(stream);//��������� �����
        }
    }
}
void Switch_file(note*& item, int& size, int a)
{
    int b = 0;
    {
        cout << "0-exit\n1-Wright in file\n2-Read with file\n"; cin >> a;
        switch (a)
        {
        case 1:
            File(item, size, 'W');
            b = 1;
            break;
        case 2:
            File(item, size, 'R');
            b = 1;
            break;
        case 0:
            b = 1;
            break;
        default:
            cout << "Wrong number:(\n";
            break;
        }
    }while (b != 1);
}


int main()
{
    srand(time(NULL));
    note* item = nullptr;
    int size = 0;
    int index;
    int a;
    int b = 0;
    bool c = 1;
    cout << "Welcome to programm 'my notes', I'm Poco, your text assistant^_^\nWhat do we do next?\n";
    do
    {
        if (size == 0)
        {
            cout << "\nEnter next action\n0-Exit\n1-Add new note\n";
            cin >> a;
            switch (a)
            {
            case 1:
                Add_note(item, size);
                c = 1;
                break;
            case 0:
                cout << "BUY^_^\n";
                c = 0;
                break;
            default:
                break;
            }
        }
        else
        {
            //���� ���� � ��������� ��������� ���������  
            cout << "\nEnter next action\n0-Exit\n1-Add new note\n2-Show your notes\n3-Delete the note\n";
            cout << "4-Edit the note\n5-Search the note\n6-Search time group notes\n7-Sort the notes\n8-Work with to file\n"; cin >> a;
            switch (a)
            {
            case 1:
                Add_note(item, size);
                c = 1;
                break;
            case 2:
                Show(item, size);
                c = 1;
                break;
            case 3:
                Show(item, size);
                cout << "\nEnter the note that you want to delete, pleas or enter 0 to exit\n"; cin >> index;
                if (index < 0 || index > size)
                    cout << "Wrong number:(\n";
                else
                    Del_note(item, size, index);
                c = 1;
                break;
            case 4:
                Show(item, size);
                cout << "\nEnter the note that you want to edit, pleasor or enter 0 to exit\n"; cin >> index;
                if (index < 0 || index > size)
                    cout << "Wrong number:(\n";
                else
                    Edit_note(item, size, index);
                c = 1;
                break;
            case 5:
                Search_note(item, size, a);
                c = 1;
                break;

            case 6: //������� ��� ������ ��� �� ����/������/�����
                Switch_D_W_M(item, size, a);
                c = 1;
                break;
            case 7://������� ��� ������ ���� ���������� � ��� �������
                Switch_sort(item, size, a);
                c = 1;
                break;
            case 8:
                Switch_file(item, size, a);
                cout << "File added ready to use^_^\n";
                c = 1;
                break;
            case 0:
                cout << "BUY^_^\n";
                Del(item, size);
                c = 0;
                break;
            }
        }
    } while (c != 0);
}
