// Laba3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <string>
using namespace std;

// Класс DB представляет базу данных фактов
// В нем реализованы методы для поиска, добавления и удаления фактов
// Также реализованы методы для проверки наличия факта в базе данных и разделения строки на подстроки

class DB {
public:
    static DB main;
    string* facts;
    int count;

    // Конструктор
    DB() {
        facts = new string[1000];
        count = 0;
        main = *this;
    }

    // Метод для поиска фактов
    int find(string fact, int s, int f) {
        if (s > f)
            return -1;
        int mid = (s + f) / 2;
        if (fact == facts[mid])
            return mid;
        if (fact < facts[mid])
            return find(fact, s, mid - 1);
        return find(fact, mid + 1, f);
    }

    // Метод для проверки наличия факта в базе данных
    bool contains(string fact) {
        return find(fact, 0, count - 1) != -1;
    }

    // Метод для добавления фактов
    void add(string fact) {
        if (count == 0 || fact > facts[count - 1]) {
            facts[count++] = fact;
            return;
        }

        int i = count - 1;
        while (i >= 0 && facts[i] > fact) {
            facts[i + 1] = facts[i];
            i--;
        }
        facts[i + 1] = fact;
        count++;
    }

    // Метод для удаления факта из базы данных
    void remove(string fact) {
        int idx = find(fact, 0, count - 1);
        if (idx == -1) return;

        for (int i = idx; i < count - 1; i++) {
            facts[i] = facts[i + 1];
        }
        count--;
    }
};

// Создание статического экземпляра класса DB
DB DB::main;

// Вспомогательная функция для разделения строк
string* split(string line, string sep) {
    static string parts[10];
    size_t pos = 0;
    int index = 0;
    while ((pos = line.find(sep)) != string::npos) {
        parts[index++] = line.substr(0, pos);
        line.erase(0, pos + sep.length());
    }
    parts[index] = line;
    return parts;
}

class Complier {
public:
    // Статический метод для ответа на запросы к базе данных 
    static bool answer(string request) {
        return DB::main.contains(request);
    }
};

// Класс для фактов 
class Fact {
public:
    string type;
    int argsCount;
    string* args;

    Fact() {}

    // Конструктор 
    Fact(string t, int ac, string* a) {
        type = t;
        argsCount = ac;
        args = a;
    }

    // Проверка факта в базе данных
    virtual bool check() {
        string factStr = type + "(";
        for (int i = 0; i < argsCount; i++) {
            factStr += args[i] + (i < argsCount - 1 ? "," : "");
        }
        factStr += ")";
        return DB::main.contains(factStr);
    }
};

// Класс правил наследник от класса Fact
class Rule : public Fact {
public:
    string body;

    // Конструктор 
    Rule(string t, int ac, string* a, string b) {
        Fact(t, ac, a);
        body = b;
    }
    
    // Проверка правил
    bool check() override {
        if (body.find("&&") != string::npos) {
            string* parts = split(body, "&&");
            for (int i = 0; parts[i] != ""; i++) {
                if (!Complier::answer(parts[i]))
                    return false;
            }
            return true;
        }
        if (body.find("||") != string::npos) {
            string* parts = split(body, "||");
            for (int i = 0; parts[i] != ""; i++) {
                if (Complier::answer(parts[i]))
                    return true;
            }
            return false;
        }
        return Complier::answer(body);
    }
};

// Вспомогательная функция для извлечения аргументов факта
void parseFact(const string& fact, string& type, string& arg1, string& arg2) {
    size_t start = fact.find("(");
    size_t end = fact.find(")");
    if (start == string::npos || end == string::npos)
        return;

    type = fact.substr(0, start);
    string args = fact.substr(start + 1, end - start - 1);
    size_t commaPos = args.find(",");
    if (commaPos != string::npos) {
        arg1 = args.substr(0, commaPos);
        arg2 = args.substr(commaPos + 1);
    }
}

// Генерация новых фактов
void generateNewFacts() {
    for (int i = 0; i < DB::main.count; i++) {
        for (int j = 0; j < DB::main.count; j++) {
            string type1, argA, argB;
            string type2, argB2, argC;
            parseFact(DB::main.facts[i], type1, argA, argB);
            parseFact(DB::main.facts[j], type2, argB2, argC);

            // Если типы фактов совпадают и аргументы B и B2 совпадают
            if (!type1.empty() && type1 == type2 && argB == argB2) {
                string newFact = type1 + "(" + argA + "," + argC + ")";
                if (!DB::main.contains(newFact)) {
                    DB::main.add(newFact);
                    cout << "Generated new fact: " << newFact << endl;
                }
            }
        }
    }
}

int main() {

    // Добавляем факты в базу данных
    DB::main.add("older(Alice,Bob)");
    DB::main.add("older(Bob,Charlie)");
    DB::main.add("mather(Alice,Bob)");
    DB::main.add("mather(Charlie,Den)");

    // Добавляем правила для проверки
    string args1[] = { "X", "Y" };
    Rule rule1("older", 4, args1, "older(X,Z) && older(Z,Y)");
    cout << "Rule added: " << rule1.body << endl;

    // Генерируем новые факты на основе существующих
    generateNewFacts();

    // Проверяем запрос на факт
    string args[] = { "Alice", "Charlie" };
    Fact fact("older", 2, args);
    cout << "older(Alice,Charlie) ?" << endl;
    cout << "Query result: " << (fact.check() ? "True" : "False") << endl;

    // Пример для проверки правильной генерации новых фактов 
    string args2[] = { "Bob", "Den" };
    Fact fact2("mather", 2, args2);
    cout << "mather(Bob,Den) ?" << endl;
    cout << "Query result: " << (fact2.check() ? "True" : "False") << endl;

    return 0;
}
