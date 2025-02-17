# ��������� ��� ��������� ���� ������ ������ � ������ �� C++

## ��������
���� ��� ��������� ������� ������ � ����� ������ ������ � ������, ������� ��������� ���������, ������� � ��������� �����, � ����� �������� ����� ����� �� ������ ���������� ������. �������� ���� ��������� � �������� ���� ������ � ������������ �������� ������ � ��������� �������.

## �������� ���������� ����
### 1. **����� `DB` (���� ������):**
- ������ ����� � ��������������� ������� �����.
- ������:
  - **`add(string fact)`** � ��������� ����� ���� � ���� ������, �������� ������� ����������.
  - **`remove(string fact)`** � ������� ��������� ���� �� ���� ������.
  - **`contains(string fact)`** � ��������� ������� ����� � ����.
  - **`find(string fact, int s, int f)`** � ��������� �������� ����� ����� � ���� ������.

### 2. **����� `Fact`:**
- ��������� ��������� ����� � ����� � �����������.
- ��������� ������� ����� � ���� ������ � ������� ������ **`check()`**.

### 3. **����� `Rule`:**
- ����������� �� ������ `Fact` � ��������� �������� ���������� ������.
- ������������ ���������� �������� **� (`&&`)** � **��� (`||`)** ��� �������� �������.
- ����� **`check()`** ��������� ���������� �������, ����������� �� ���� ������.

### 4. **����� `Complier`:**
- �������� �� ��������� �������� � ���� ������.
- ����� **`answer(string request)`** ��������� ���� ����� ���� ������.

### 5. **������� `generateNewFacts`:**
- ���������� ����� �����, ������ �� ������������ ���������� ������.
- ������: ���� ���� `older(Alice, Bob)` � `older(Bob, Charlie)` ����������, ��������� ������� ����� ���� `older(Alice, Charlie)`.

### 6. **��������������� �������:**
- **`split(string line, string sep)`** � ��������� ������ �� ��������� �� ��������� �����������.
- **`parseFact(const string& fact, string& type, string& arg1, string& arg2)`** � ��������� ������ ����� �� ��������� ����������: ��� � ���������.

## ������ ������ ���������

```
int main() {

    // ��������� ����� � ���� ������
    DB::main.add("older(Alice,Bob)");
    DB::main.add("older(Bob,Charlie)");
    DB::main.add("mather(Alice,Bob)");
    DB::main.add("mather(Charlie,Den)");

    // ��������� ������� ��� ��������
    string args1[] = { "X", "Y" };
    Rule rule1("older", 4, args1, "older(X,Z) && older(Z,Y)");
    cout << "Rule added: " << rule1.body << endl;

    // ���������� ����� ����� �� ������ ������������
    generateNewFacts();

    // ��������� ������ �� ����
    string args[] = { "Alice", "Charlie" };
    Fact fact("older", 2, args);
    cout << "older(Alice,Charlie) ?" << endl;
    cout << "Query result: " << (fact.check() ? "True" : "False") << endl;

    // ������ ��� �������� ���������� ��������� ����� ������ 
    string args2[] = { "Bob", "Den" };
    Fact fact2("mather", 2, args2);
    cout << "mather(Bob,Den) ?" << endl;
    cout << "Query result: " << (fact2.check() ? "True" : "False") << endl;

    return 0;
}

```