//Inheritance
#include<iostream>
#include<string>
using namespace std;

#define delimiter "\n-------------------------------------------------\n"

class Human
{
	string first_name;
	string last_name;
	unsigned int age;
public:
	const string& get_first_name() const
	{
		return this->first_name;
	}
	const string& get_last_name()const
	{
		return this->last_name;
	}
	unsigned int get_age()const
	{
		return this->age;
	}
	void set_first_name(const string& first_name)
	{
		this->first_name = first_name;
	}
	void set_last_name(const string& last_name)
	{
		this->last_name = last_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}
	//			Constructors:
	Human(const string& first_name, const string& last_name, unsigned int age)
	{
		set_first_name(first_name);
		set_last_name(last_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//Methods:
	virtual void info()
	{
		cout << last_name << " " << first_name << " " << age << " лет.\n";
	}
};

class Student :public Human
{
	string specialty;
	string group;
	unsigned int year;	//год обучения.
	unsigned int rating;//успеваемость
public:
	const string& get_specialty()const
	{
		return this->specialty;
	}
	const string& get_group()const
	{
		return this->group;
	}
	unsigned int get_year()const
	{
		return this->year;
	}
	unsigned int get_rating()const
	{
		return this->rating;
	}
	void set_specialty(const string& specialty)
	{
		this->specialty = specialty;
	}
	void set_group(const string& group)
	{
		this->group = group;
	}
	void set_year(unsigned int year)
	{
		this->year = year;
	}
	void set_rating(unsigned int rating)
	{
		this->rating = rating;
	}
	//			Constructors:
	Student(const string& first_name, const string& last_name, unsigned int age, const string& specialty, const string& group, unsigned int year, unsigned int rating):Human(first_name, last_name, age)
	{
		this->specialty = specialty;
		this->group = group;
		this->year = year;
		this->rating = rating;
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	void info()
	{
		Human::info();
		cout << specialty << " " << group << " " << year << " курс, успеваемость" << rating << endl;
	}
};

class Teacher :public Human
{
	string specialty;
	unsigned int experience;
public:
	const string& get_specialty()const
	{
		return specialty;
	}
	unsigned int get_experience() const
	{
		return experience;
	}

	void set_specialty(const string& specialty)
	{
		this->specialty = specialty;
	}
	void set_experience(unsigned int experience) 
	{
		this->experience = experience;
	}

	Teacher(const string& first_name, const string& last_name, unsigned int age, const string& specialty, unsigned int experience) :
		Human(first_name, last_name, age)
	{
		set_specialty(specialty);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	void info()
	{
		Human::info();
		cout << "преподает " << specialty << " опыт преподавания " << experience << " лет\n";
	}
};

class Graduate:public Student
{
	string diploma_theme;
public:
	const string& get_diploma_theme()const
	{
		return diploma_theme;
	}
	void set_diploma_theme(const string& diploma_theme)
	{
		this->diploma_theme = diploma_theme;
	}
	Graduate(const string& first_name, const string& last_name, unsigned int age, const string& specialty, const string& group, unsigned int year, unsigned int rating, const string& diploma_theme) :
		Student(first_name, last_name, age,
			specialty, group, year, rating), diploma_theme(diploma_theme)
	{
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	void info()
	{
		Student::info();
		cout << " тема дипломного проекта: " << diploma_theme << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	/*Human h("Василий", "Дурко", 21);
	h.info();
	
	Student s("Иван", "Тупенко", 18, "Девелупер", "СТ ПУ 34а", 1, 0);
	s.info();

	Teacher Albert("Albert", "Einstein", 140, "Astronomy", 120);
	Graduate Montana("Antonio", "Montana", 25, 
		"массовое распространение наркотиков", "CT PU 34a", 3, 99, 
		"работа с проблемной задолженность.");

	Human* pA = &Albert;
	Human* pM = &Montana;
	cout << "\n--------------------------\n";
	pA->info();
	Human(*pA).info();
	cout << "\n--------------------------\n";*/

	Human* group[] =
	{
		new Graduate("Виталий", "Гавриш", 20, "РПО", "СТ ПУ 34а", 1, 100, "Самообучение ИИ +ы и -ы"),
		new Student("Юлия", "Рыбакова", 18, "РПО", "СТ ПУ 34а", 1, 70),
		new Teacher("Андрей", "Кобылинский", 40, "HardwarePC", 18),
		new Student("Евгений", "Ковтун", 18, "РПО", "СТ ПУ 34а", 1, 70),
		new Graduate("Марианна", "Забрянская", 17, "РПО", "СТ ПУ 34а", 1, 80, "Как разработать свою игру, чтобы тебя хоть кто-то заметил"),
		new Teacher("Роман", "Шерстюк", 30, "WebDev", 5)
	};

	for (int i = 0; i < sizeof(group) / sizeof(Human*); i++)
	{
		cout << delimiter << endl;
		cout << typeid(*group[i]).name() << endl;
		//group[i]->info();
		cout << *group[i] << endl;
	}

	for (int i = 0; i < sizeof(group) / sizeof(Human*); i++)
	{
		delete group[i];
	}
}