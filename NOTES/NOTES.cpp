
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
    char* title;//название
    char* description;//описание
    int priority;//приоритет по важности
    time_t date;//срок выполнения
    char* date_ch;
    element_date element;
};
//Фуекция для получения значений даты по отдельности в типе данных int
void Note_time(int& a, const char g[], time_t now)
{

    struct tmt;//импортируем структуру тм
    //структура тм должна выделяться динамически и в конц надо чистить структуру 

    char h[100];//создаем переменную буфера
    //создаем переменную типа структуры тм и присваиваем туда значение
    tm* timeinfo = localtime(&now);//функция разбивает время в секундах на промежутки(дни, месяца и тд)

    strftime(h, 100, g, timeinfo);//с помощью функции переводим нужное нам значение в чар

    a = atoi(h);//преабразовуем массив чар в инт

}
void Data_ch(note*& item, int size, tm& t)
{
    char buf[100];//вспомагательна переменная буфер
    strftime(buf, 100, "%A %d.%m.%y %H:%M", &t);//переводит время в нужный формат(принимет значение структуры tm и возвращает ее) 
    cin.ignore();//очищаем буфер
    item[size].date_ch = new char[strlen(buf + 1)];//выделяем размер
    strcpy(item[size].date_ch, buf);//присваиваем(копируем) полю структуры нужные данные
}
//Функция для заполнения даты
void Dat(note*& item, int size, tm& t)
{
    //импортируем структуру времени в которой храняться показатели на
    // секунды/минуты/дни/и тд

    time_t second = time(NULL);//получаем текущее время в секундах

    //массивы созданы и несут в себе номер месяцев
    //первый массив содержит в себе месяца в которых 31 день
    int mass31[] = { 0, 2, 4, 6, 7, 9, 11 };
    //второй массив содержит в себе месяца в которых 30 дней
    int mass30[] = { 3, 5, 8, 10 };
    //отчет месяцев начинаеться с нулевого по скольку счет месяцев из структури тм начинаеться с 0 до 11 
    //январь(28 дней, по скольку 2022 год не высокосный) будет указываться в ручную

    //переменная бул создана чтобы уменьшить количество условий в последующем цыкле ду вайл
    bool a;
    t.tm_year = 2024 - 1900;
    do
    {
        //блок в котором мы вводим дату(число и месяц)
        do
        {
            cout << "Enter Date\n";
            cout << "Enter number of day\n";
            cin >> t.tm_mday;
            cout << "Enter number month\n";
            cin >> t.tm_mon;
            //иф проверяет не равняеться день или номер месяца 0 или если число месяцев больше 12
            if (t.tm_mday <= 0 || t.tm_mon <= 0)
            {
                //если равно 0 то пишем увидомление о не коректности ввода
                cout << "number day or month shouldn't equal 0!\n";
                //переменная бул получает значение фолс и мы снова запрашиваем
                                //у пользователя ввод даты
                a = 0;
            }
            //проверяем не ввел ли пользователь не правильное количество месяцев
            else if (t.tm_mon > 12)
            {
                cout << "Entered wrong month number\n";
                a = 0;
            }
            // если нет то идем дальше по условиям
            else
            {
                //отнимаем от месяца 1 так как счетчик идет с 0
                t.tm_mon -= 1;
                //в цыкле перебираем количество всех месяцов
                for (int i = 0; i < 11; i++)
                {
                    //если месяц соотвецтвует номеру месяцов из массива то
                    if (t.tm_mon == mass31[i])
                    {
                        //проверяем соотвецтвует ли количество дней для заданого месяца
                        // если дней больше то
                        if (t.tm_mday > 31)
                        {
                            //выводим на экран ошибку о не коректности ввода 
                            cout << "Number of days of doesn't correspond to the month!\n";
                            //переменная получает 0 из за этого пользователь снова перписывает дату
                            a = 0;
                        }
                        //если количество дней соотвецтвует месяцу то а получает 1 и сохраняет нашу дату в поле структуры
                        else
                            a = 1;
                    }
                    //с другими месяцами действуем также но меняеться соотношение дней
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
                        //февраль имеет 28 дней а не 29 по скольку 2022 год не высокосный
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
        //блок для ввода времени исполнения
        do
        {
            cout << "Enter hour\n";
            cin >> t.tm_hour;
            cout << "Enter minutes\n";
            cin >> t.tm_min;
            //проверяем введеная цыфра соотвецтвует ли 24 часовой системе времени
            if (t.tm_hour > 23 || t.tm_min > 59)
                cout << "Time not specified correctly!\n";
            //повторяем цыкл пока не получим нужные результаты
        } while (t.tm_hour > 23 || t.tm_min > 59);
        //t.tm_hour -= 1;
        t.tm_sec = 0;//количество секунд приравниваем нулю так как без этого вывод на экран будет не коректным

        //Записываем все в переменную из структуры
        item[size].date = mktime(&t);//функция получает и возвращает значение t tимеет тип данных mt переводоя все дни/месяца... в секунды
        if (item[size].date < second)//проверям не ввел ли пользователь дату из прошлого
        {
            item[size].date = 0;//обнуляем дату в секундах чтобы перезаполнить ее
            cout << "Entered past date or time!\n";
            a = 0;
        }
        else//если дата корктная то форматируем ее в нужный вид
        {
            //В следующих трех строках мы копируем значение дня недели/день/месяц
            //это понадобиться в будущем
            Note_time(item[size].element.day_week, "%w", item[size].date);
            Note_time(item[size].element.day, "%d", item[size].date);
            Note_time(item[size].element.month, "%m", item[size].date);
            Note_time(item[size].element.hour, "%H", item[size].date);
            Note_time(item[size].element.min, "%M", item[size].date);
            a = 1;
        }
    } while (a != 1);
}
//Функция для полного удаления структуры
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
//функции добавления и вывода на экран
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
//Функция для добавления заметок
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
            size++;//размер структуры увиличиваем на 1
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



//Функция удаления по индексу
//-------------------------------------------
void Del_note(note*& item, int& size, int index)
{
    int a;
    index -= 1;//индекс -1 для того чтобы введеное число пользователя соотвецтвовало индексации что начинаеться с 0
    do
    {
        if (index == -1)
            a = 1;
        else
        {
            note* temp = new note[size - 1];
            //В цыкле копируем все элемнты до и после индекса не включительно
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

//Функция для редактирования
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
//Функция по поиску строки c 100% схожостью
void Search(note*& item, int size, char* buf)
{
    char search[100];
    int counter = 0;//счетчик
    int k = 0;//доп переменная для индекса
    cout << "\tEnter name\t\n"; cin.ignore();  cin.getline(search, 100);//вводим строку
    for (int i = 0; i < size; i++)
    {
        if (strcmp(buf, search) == 0)//сравниваем название заметки с введеным на экран 
            counter++;//если она совпадает на 100% добавляем счетчик
    }
    note* temp = new note[counter];//создаем новую структуру
    for (int i = 0; i < size; i++)
    {
        if (strcmp(buf, search) == 0)
        {
            temp[k] = item[i];
            k++;//заполняем ее с учетом индексации
        }
    }
    if (counter > 0)//если каунтер больше 0 то выводим на экран
    {
        Show(temp, counter);
        delete[] temp;
    }
    else//иначе пишем что таких заметок не найдено
        cout << "\tNo notes foud\n";
}
//Функция поика заметок
void Search_note(note*& item, int& size, int a)
{
    //массивы с содержанием месяцов
    int mass31[] = { 0, 2, 4, 6, 7, 9, 11 };
    int mass30[] = { 3, 5, 8, 10 };

    int counter = 0;//счетчик
    int k = 0;//доп переменная
    int prior;
    char date[100], month[100], hour[100], min[100];
    int b = 0;
    {
        cout << "What do you want to search\t\n0-Exit\t\n1-Name note\t\n2-Description\t\n3-Priority\t\n4-Date\t\n"; cin >> a; cout << "\t";
        switch (a)
        {
        case 1:
            Search(item, size, item->title);//ищем заметку по названию
            b = 1;
            break;
        case 2:
            Search(item, size, item->description);//ищем заметку по описанию
            b = 1;
            break;
        case 3://по приоритету
            if (a == 3)//стоит иф по скольку без него не удалось инициализировать переменные
            {
                do
                {
                    cout << "Enter priority 1-4\t";
                    cin >> prior;//вводим приоритет который хотим искать
                } while (prior > 4 || prior <= 0);

                for (int i = 0; i < size; i++)
                    if (prior == item[i].priority)
                        counter++;//если он соотвецтвует заметке каунтер +1
                note* temp = new note[counter];//создаем структуру
                for (int i = 0; i < size; i++)
                    if (prior == item[i].priority)
                    {
                        temp[k] = item[i];//заполняем ее
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
        case 4://по поиску дате и времени исполнения
            if (a == 4)
            {
                {
                    cout << "Enter number date\n\t";
                    cin >> date;
                    cout << "\tEnter number month\n\t";
                    cin >> month;
                    int da = atoi(date);
                    int mon = atoi(month);

                    if (da <= 0 || mon <= 0)//проверка что пользователь не ввиел число 0 и меньше
                    {
                        cout << "\tnumber day or month shouldn't equal 0!\n";
                        b = 0;
                    }
                    else if (mon > 12)//провиряем на число месяцев
                    {
                        cout << "\tEntered wrong month number\n";
                        b = 0;
                    }
                    else
                    {
                        for (int i = 0; i < 11; i++)//цикыл для массива 
                        {
                            mon -= 1;//месяц -1 так как как его надо сравнивать с элементами массива

                            //В следущих проверках определяем соотвецтвунт ли месяц своему количеству дней
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
                int da = atoi(date);//переводим переменные в инт и присваиваем переменным для удобства(они были чаровыми для удобноговвода)
                int mon = atoi(month);
                do
                {
                    //вводим время
                    cout << "\tEnter hour\n\t";
                    cin >> hour;
                    cout << "\tEnter minutes\n\t";
                    cin >> min;
                    if (atoi(hour) > 23 || atoi(min) > 59)
                        cout << "\tTime not specified correctly!\n";
                } while (atoi(hour) > 23 || atoi(min) > 59);

                for (int i = 0; i < size; i++)
                    if (da == item[i].element.day && mon == item[i].element.month && atoi(hour) == item[i].element.hour && atoi(min) == item[i].element.min)
                        counter++;//определяем размер массива если введеные данные соотвецтвуют заметкам добавляем к каунтеру+1
                note* temp = new note[counter];
                for (int i = 0; i < size; i++)
                    if (da == item[i].element.day && mon == item[i].element.month && atoi(hour) == item[i].element.hour && atoi(min) == item[i].element.min)
                    {
                        temp[k] = item[i];//заполняем стпуктуру
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
//функции поиска по дням/неделям/месяцам
//----------------------------------------
void D_W_M(note*& item, int& size, string a)
{
    //импортируем структуру
    struct tm t;
    int day, day_week, month;
    //узнаем текущее время в сек
    time_t now = time(NULL);

    //Получаем номера текущего дгя недели, месца и даты
    Note_time(day_week, "%w", now);
    Note_time(day, "%d", now);
    Note_time(month, "%m", now);


    int k = 0;
    int time_size = 0;
    note* temp;
    if (a == "day")
    {
        //узнаем размер для списка дел на день
        for (int i = 0; i < size; i++)
            if (item[i].element.day_week == day_week && item[i].element.day == day && item[i].element.month == month)
                time_size++;

        //Ммассив рлдучает размер
        note* temp = new note[time_size];
        for (int i = 0; i < size; i++)
        {
            if (item[i].element.day_week == day_week && item[i].element.day == day && item[i].element.month == month)
            {
                //копируем элементы
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
    //ищем дела на текущую неделю
    else if (a == "week")
    {
        //узнаем количество дней до воскресенья
        int day_before_Sun = 7 - day_week;//текущий номер дня недели ведет отчет с 0-6

        t.tm_year = 2022 - 1900;
        t.tm_mon = month - 1;//отнимаем 1 так как  в структуре они нумеруються с нуля 
        if (day_before_Sun == 7)//если сегодня воскресенье то
            t.tm_mday = day;//присваиваем переменной значение текущего дня
        else
            t.tm_mday = day + day_before_Sun;//присваиваем воскресенье
        t.tm_hour = 23;
        t.tm_min = 59;
        t.tm_sec = 0;
        time_t Sunday = mktime(&t);//переводим все в секунды

        for (int i = 0; i < size; i++)
        {
            if (Sunday >= item[i].date)//если заметка меньше или равна воскрксенья добавляем к каунтеру +1
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

//Функция для вывода меню отображения дел на время
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

//функция сортировок по приоритету и по количеству дней
//-------------------------------------------
void Sort_notes(note*& item, int& size, char a, char b)
//Фунция принимает в себя 2 чаровые переменные  для того чтобы можно было
//выбрать как сортировать структуру 
{
    //Функция сортировки по приоритету

    if (a == '-' && b == 'p')
    {
        //сортировка по возрастанию
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size - 1; j++)
            {
                if (item[j].priority > item[j + 1].priority)
                    swap(item[j], item[j + 1]);
                //если у нас одинаковые приоритеты то список начинает сортироваться по дням
                // чем больше дней тем пункт ниже в списке
                else if (item[j].priority == item[j + 1].priority)
                    if (item[j].date < item[j + 1].date)
                        swap(item[j + 1], item[j]);
            }
    }
    else if (a == '+' && b == 'p')
    {
        //сортировка по убыванию
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size - 1; j++)
            {
                if (item[j].priority < item[j + 1].priority)
                    swap(item[j + 1], item[j]);
                //если у нас одинаковые приоритеты то список начинает сортироваться по дням
                // чем меньше дней тем пункт выше в списке
                else if (item[j].priority == item[j + 1].priority)
                    if (item[j].date > item[j + 1].date)
                        swap(item[j], item[j + 1]);


            }
    }
    //Фунция сортировки по дням
    else if (a == '-' && b == 'd')
    {
        //сортировка по возрастанию
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
        //сортировка по убыванию
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
//функция для выводв меню сортровки чтобы не меньше путаться в основном коде
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
    cout << "Enter name file\n"; cin.ignore(); cin.getline(filename, 100);//вводим название файла
    char buff[100];//буфер
    FILE* stream;//создаем поток с привязкой к файлу


    if (a == 'W')//если записываем в файл
    {

        stream = fopen(filename, "w");//открываем поток для записи
        if (!stream)//если файл не найден
            cout << "File not open!\n";
        else
        {
            for (int i = 0; i < size; i++)//перебираем все элементы
            {
                fputs(item[i].title, stream);//записали в файл поле
                fputc(';', stream);//добавили к нему точку с запятой

                fputs(item[i].description, stream);
                fputc(';', stream);


                sprintf(buff, "%i", item[i].priority);//приоритет перевели в тип чар так как другие типы данных не принимабться
                fputs(buff, stream);
                fputc(';', stream);

                fputs(item[i].date_ch, stream);

                fputc(';', stream);//ставим в конце точку с запятой
                fputc('\n', stream);//переносим следующий элемент на строку дальше


            }
            fclose(stream);//закрываем поток
        }

    }
    else if (a == 'R')
    {
        char* t;//указатель на часть строки

        stream = fopen(filename, "r");
        if (!stream)
            cout << "File not open!\n";
        else
        {
            int counter = 0;
            while (fgets(buff, 100, stream))//функция проверяет наличие записи в файле пока там есть текст получает тру иначе, фолс
                counter++;
            rewind(stream);//перемещаем курсор в начало файла так как он перешел в конец

            note* temp = new note[size + counter];//создем, копируем, переадресуем массив на новый размер
            for (int i = 0; i < size; i++)
                temp[i] = item[i];
            delete[] item;
            item = temp;

            for (int i = size; i < size + counter; i++)//перебираем все элементы плюс записи с файла
            {
                fgets(buff, 100, stream);//читаем строки

                t = strtok(buff, ";");//начинаем подсчет с буф до точки с запятой после этого t обнуляеться
                item[i].title = new char[strlen(t) + 1];//определяем новый размер для поля структуры
                strcpy(item[i].title, t);//копируем туда содержимое т

                t = strtok(NULL, ";");//благодаря NULL курсор не обнуляеться а продолжает свое движение там где он остановился
                item[i].description = new char[strlen(t) + 1];
                strcpy(item[i].description, t);

                t = strtok(NULL, ";");
                item[i].priority = atoi(t);//приабразовуем приоритет в тип данных инт

                t = strtok(NULL, ";");
                item[i].date_ch = new char[strlen(t) + 1];
                strcpy(item[i].date_ch, t);
            }
            size += counter;//добавляем к основному размеру размер элементов с файла
            fclose(stream);//Закрываем поток
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
            //Блок кода с основными функциями программы  
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

            case 6: //функция для вывода дел на день/неделю/месяц
                Switch_D_W_M(item, size, a);
                c = 1;
                break;
            case 7://функция для вывода меню сортировки и сам перебор
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
