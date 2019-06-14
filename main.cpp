#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <map>
#include <set>
#include <deque>
#include <list>
#include <memory> 
#include <fstream>
#include <iomanip>
#include <sstream>
#include <future>
#include <mutex>
#include <functional>
using namespace std;

void OverloadVsOverideTest(void)
{
	class BaseClass 
	{ 
	public: 
		virtual void Display() 
		{ 
			cout << "\nThis is Display() method"
			" of BaseClass"; 
		} 
		void Show() 
		{ 
			cout << "\nThis is Show() method "
			"of BaseClass First Version"; 
		}
		void Show(string message) 
		{ 
			cout << "\nThis is Show() method " 
			"of BaseClass" << message; 
		} 
	}; 

	class DerivedClass : public BaseClass 
	{ 
	public: 
		// Overriding method - new working of 
		// base class's display method 
		void Display() 
		{ 
			cout << "\nThis is Display() method"
			" of DerivedClass"; 
		} 
	}; 
	
	// Driver code 
	DerivedClass dr; 
	BaseClass &bsd = dr; 
	BaseClass bs;
	bs.Display();
	bsd.Display(); 
	dr.Show();
	dr.Show(" Overloading Show Method By Get Input");
}

void GiveWordsAndSortTest(void)
{
	vector<string> words;
	string strTemp;
	cout << "Input 5 words:" << endl;
	for(auto i : {0, 1, 2, 3, 4})
	{
		cin >> strTemp;
		words.push_back(strTemp);
	}
	sort(words.begin(),words.end());
	cout << endl << "Print Sorted:" << endl;
	for(auto& str : words)
	cout << str << endl;
}	

void TryCatchTest(void)
{
	auto divide = [](int m, int n) {
		if( n == 0 ){
			throw domain_error("Division by zero");
		} else {
			return m / n;
		}
	};
	try {
		auto i = divide(10, 0);
		cout << i << endl;
	}
	catch (const exception& e){
		cout << "Exception: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "Handle all other exceptions" << endl;
	}
}

namespace ConstAndRefInitTest 
{		
	class ConstAndRefInit
	{
	public:
		ConstAndRefInit( int& );
	private:
		int mI;
		const int mCi;
		int& mRi;
	};
	
	// ConstAndRefInit::ConstAndRefInit( int& inI ){
	// mI = inI; //OK
	// mCi = inI; //ERROR: cannot assign to a const
	// mRi = inI; //ERROR: uninitialized reference member
	// }

	ConstAndRefInit::ConstAndRefInit( int& inI ): mI( inI ), mCi( inI ), mRi( inI )
	{
		cout << "\n\nConst And Refrence Initialization is done successfully.";
	}
	
	void Run(void)
	{
		int i = 23;
		ConstAndRefInit cr(i);
		
	}
}

namespace FunctorTest
{
	// A Functor 
	class increment 
	{ 
	private: 
		int num; 
	public: 
		increment(int n) : num(n) { } 

		// This operator overloading enables calling 
		// operator function () on objects of increment 
		int operator () (int arr_num) const { 
			return num + arr_num; 
		} 
	};

	void Run(void)
	{
		int arr[] = {1, 2, 3, 4, 5}; 
		int n = sizeof(arr)/sizeof(arr[0]); 
		int to_add = 5; 

		for (int i=0; i<n; i++) 
		cout << arr[i] << " "; 
		
		cout << endl << "Add " << to_add << " To Each Argument Of Array:" << endl; 
		transform(arr, arr+n, arr, increment(to_add)); 

		
		for (int i=0; i<n; i++) 
		cout << arr[i] << " "; 
	}
}

namespace SetContainerTest
{
	class PersonCompare;
	
	class Person {
		friend class PersonCompare;
		string firstName;
		string lastName;
		int yearOfBirth;
	public:
		Person(string firstName, string lastName, int yearOfBirth) : 
		firstName(firstName),lastName(lastName),yearOfBirth(yearOfBirth){} ;
		friend ostream& operator<<(ostream& os, const Person& person)
		{
			os << " " << person.firstName << " " << person.yearOfBirth;
			return os;
		};
	};
	
	class PersonCompare {
	public:
		enum Criterion { NAME, BIRTHYEAR};
	private:
		Criterion criterion;
	public:
		PersonCompare(Criterion criterion) : criterion(criterion) {}
		bool operator()(const Person& p1, const Person& p2) {
			switch (criterion) {
			case NAME: //
				return p1.firstName < p2.firstName;
			case BIRTHYEAR: //
				return p1.yearOfBirth < p2.yearOfBirth;
			}
		}
	};	
	
	void Run(void)
	{
		set<Person, PersonCompare> s(PersonCompare::BIRTHYEAR);
		s.insert(Person("Biro", "Istvan", 1960));
		s.insert(Person("Abos", "Gergely", 1996));
		s.insert(Person("Gered","Attila", 1986));

		for( auto& p: s){
			cout << p <<endl;
		}
	}
}

namespace IteratorTest
{
	template<typename Container>
	void IteratorFunc(Container &elements)
	{
		typename Container::const_iterator i;
		
		cout << "With iterators = "; 
		
		// Accessing the elements using iterators 
		for (i = elements.begin(); i != elements.end(); ++i) 
		{ 
			cout << *i << " "; 
		} 
		
		// Adding one more element to vector 
		elements.push_back(4); 
		
		cout << "\nWith iterators = "; 
		
		// Accessing the elements using iterators 
		for (i = elements.begin(); i != elements.end(); ++i)  
		{ 
			cout << *i << " "; 
		} 
	};

	void Run(void)
	{
		// Declaring a vector 
		vector<int> v = { 1, 2, 3 }; 
		list<int> 	l = { 1, 2, 3 }; 
		deque<int> 	d = { 1, 2, 3 }; 
		
		cout << "Vector Without iterators = "; 
		// Accessing the elements without using iterators 
		for (int j = 0; j < 3; ++j)  
		{ 
			cout << v[j] << " "; 
		} 
		
		cout << "\nTest Vector Iteration:" << endl;
		IteratorFunc(v);

		cout << endl;
		cout << "\nList Without iterators = "; 
		for (int &n : l) {
			cout << n << " ";
		}
		cout << "\nTest List Iteration:" << endl;
		IteratorFunc(l);
		
		cout << endl;
		cout << "\nDeque Without iterators = "; 
		for (int n : d) {
			cout << n << " ";
		}	
		cout << "\nDeque List Iteration:" << endl;
		IteratorFunc(d);  
	}
}

namespace AlgorithmsTest
{
	typedef pair<vector<int>::iterator, vector<int>::iterator> PVIT;
	typedef vector<int>::iterator VIT;

	void UtilityAlgoritmTest(void) 
	{
		vector<int>v = {10, 9, 7, 0, -5, 100, 56, 200, -24};
		PVIT result = minmax_element(v.begin(), v.end() );
		cout<<"min: "<<*(result.first)<<endl;
		cout<<"min position: "<<(result.first-v.begin())<<endl;
		cout<<"max: "<<*(result.second)<<endl;
		cout<<"max position: "<<(result.second-v.begin())<<endl;
	}
	
	bool isEven (int i) { return ((i%2)==0); }
	
	void SearchAlgorithmTest(void) 
	{
		vector<int> myvector={1,2,3,4,5};
		VIT it= find_if (myvector.begin(), myvector.end(), isEven);
		cout << "The first even value is " << *it << '\n';
		it = find_if (it + 1, myvector.end(), isEven);
		cout << "The second even value is " << *it << '\n';	
	}
	
	void CountAlgorithmTest(void)
	{
		vector<int> myvector={1,2,3,4,5};
		int n = count_if (myvector.begin(), myvector.end(), isEven);
		cout << "myvector contains " << n << " even values.\n";
	}
	
	// strange alphabet: 'a' ->3, 'b'->1, c->'2'
	map<char, int> order;

	// Compares two characters based on the strange order
	bool compChar( char c1, char c2 ){
		return order[c1]<order[c2];
	}
	
	// Compares two strings based on the strange order
	bool compString(const string& s1, const string& s2){
		return lexicographical_compare(
		s1.begin(), s1.end(), s2.begin(), s2.end(), compChar);
	}
	
	// Compares two strings based on the strange order
	struct CompStr{
		bool operator()(const string& s1, const string& s2){
			return lexicographical_compare(
			s1.begin(), s1.end(), s2.begin(), s2.end(),
			[](char c1, char c2){return order[c1]<order[c2];} );
		}
	};


	void ComparisonAlgorithmTest(void)
	{
		string s1 = "cba", s2 = "abc";
		order['a']=3;
		order['b']=1;
		order['c']=2;
		bool comp_result = compString(s1, s2);
		cout << s1 <<" is " << (comp_result == 0 ? "bigger than  or equal to " : "smaller than ") << s2   << endl;
		set<string, CompStr> strangeSet;
		strangeSet.insert(s1);
		strangeSet.insert(s2);
		for (auto itr : strangeSet) 
		{ 
			cout << itr << '\t'; 
		} 
		cout << endl;
	}
	
	void ForEachTest(void)
	{
		vector<int> v ={1,2,3};
		for_each(v.begin(), v.end(), []( int& v){ v *=2;});
		for_each(v.begin(), v.end(), []( int& v){ cout << v << "\t";});
		cout << endl;
	}
	
	void print( const vector<int>& v){
		for(auto& x: v){
			cout<<x<<"\t";
		}
		cout << endl;
	}
	
	void PermutationsTest(void)
	{
		vector<int> v ={1,2,3};
		print( v );
		while( next_permutation(v.begin(), v.end())){
			print( v );
		}		
	}
	
	double median(vector<double>& v) {
		int n = v.size();
		if( n == 0 ) throw domain_error("empty vector");
		int mid = n / 2;
		// size is an odd number
		if( n % 2 == 1 ){
			nth_element(v.begin(), v.begin()+mid, v.end());
			return v[mid];
		} else {
			nth_element(v.begin(), v.begin()+mid-1, v.end());
			double val1 = v[ mid -1 ];
			nth_element(v.begin(), v.begin()+mid, v.end());
			double val2 = v[ mid ];
			return (val1+val2)/2;
		}
	}

	void nth_elementTest(void)
	{
		vector<double> v ={1.3,1.2,1.1,1.5,1.6};
		cout << "median 5 elements" << median(v) << endl;
		v.push_back(1.4);
		cout << "median 6 elements" << median(v) << endl;	
	}

	void Run(void)
	{
		cout << "UtilityAlgoritmTest:" << endl;
		UtilityAlgoritmTest();
		cout << "SearchAlgorithmTest:" << endl;
		SearchAlgorithmTest();
		cout << "CountAlgorithmTest:" << endl;
		CountAlgorithmTest();
		cout << "ComparisonAlgorithmTest:" << endl;
		ComparisonAlgorithmTest();
		cout << "ForEachTest:" << endl;
		ForEachTest();
		cout << "PermutationsTest:" << endl;
		PermutationsTest();		
		cout << "nth_elementTest:" << endl;
		nth_elementTest();
	}
}

namespace IteratorDesignPatternTest
{
	// A simple Notification class 
	class Notification
	{ 
		// To store notification message 
		string notification; 
		
	public:
		Notification()
		{
		}
		Notification(string notification) 
		{ 
			this->notification = notification; 
		} 
		string getNotification() 
		{ 
			return notification; 
		} 
	}; 
	
	// We could also use Java.Util.Iterator 
	class Iterator 
	{ 
	public:
		// indicates whether there are more elements to 
		// iterate over 
		virtual bool hasNext() = 0; 
		
		// returns the next element 
		virtual Notification* next() = 0; 
	}; 

	// Collection interface 
	class Collection 
	{ 
	public:
		virtual Iterator* createIterator() = 0; 
	}; 
	
	// Notification iterator 
	class NotificationIterator : public Iterator 
	{ 
		Notification** notificationList; 
		
		// maintains curr pos of iterator over the array 
		int pos = 0; 
		
		// Constructor takes the array of notifiactionList are 
		// going to iterate over. 
	public:
		NotificationIterator (Notification** notificationList) 
		{ 
			this->notificationList = notificationList; 
		} 
		
		Notification* next() 
		{ 
			// return next element in the array and increment pos 
			Notification* notification =  notificationList[pos]; 
			pos += 1; 
			return notification; 
		} 
		
		bool hasNext() 
		{ 
			if (//pos >= notificationList.length || 
					notificationList[pos] == NULL) 
			return false; 
			else
			return true; 
		} 
	};
	

	// Collection of notifications 
	class NotificationCollection : public Collection 
	{ 
		static const int MAX_ITEMS = 6; 
		int numberOfItems = 0; 
		Notification** notificationList = new Notification*[MAX_ITEMS](); 
		
	public:
		NotificationCollection() 
		{ 
			//notificationList = new Notification[MAX_ITEMS]; 
			
			// Let us add some dummy notifications 
			addItem("Notification 1"); 
			addItem("Notification 2"); 
			addItem("Notification 3"); 
		} 
		
		void addItem(string str) 
		{ 
			Notification* notification = new Notification(str); 
			if (numberOfItems >= MAX_ITEMS) 
			cout << "Full" << endl; 
			else
			{ 
				notificationList[numberOfItems] = notification; 
				numberOfItems = numberOfItems + 1; 
			} 
		} 
		
		Iterator* createIterator() 
		{ 
			return new NotificationIterator(notificationList); 
		} 
	}; 
	
	// Contains collection of notifications as an object of 
	// NotificationCollection 
	class NotificationBar 
	{ 
		NotificationCollection* notifications; 
		
	public:
		NotificationBar(NotificationCollection* notifications) 
		{ 
			this->notifications = notifications; 
		} 
		void printNotifications() 
		{ 
			Iterator* iterator = notifications->createIterator(); 
			cout << "-------NOTIFICATION BAR------------" << endl; 
			while (iterator->hasNext()) 
			{ 
				Notification* n = (Notification*)iterator->next(); 
				cout << n->getNotification() << endl; 
			} 
		} 
	}; 

	void Run(void)
	{
		NotificationCollection* nc = new NotificationCollection(); 
		NotificationBar* nb = new NotificationBar(nc); 
		nb->printNotifications(); 
	}
}

void StreamIteratorTest(void)
{
	vector<int> v;
	
	copy(istream_iterator<int>(cin),
	istream_iterator<int>(),
	back_inserter(v));
	
	copy(v.begin(), v.end(),
	ostream_iterator<int>(cout, " "));
	
	cin.clear();
	cout << endl;
	copy(istream_iterator<int>(cin),
	istream_iterator<int>(),
	ostream_iterator<int>(cout, "\n"));
}

namespace DynamicCastTest
{
	class Person{
	public:
		virtual void print(){cout<<"Person";};
	};
	class Employee:public Person{
	public:
		virtual void print(){cout<<"Employee";};
	};
	class Manager:public Employee{
	public:
		virtual void print(){cout<<"Manager";};
	};
	
	void Run(void){
		vector<Person*> v;
		int counter = 0;
		v.push_back(new Person());
		v.push_back(new Person());
		v.push_back(new Employee());
		v.push_back(new Employee());
		v.push_back( new Manager());
		v.push_back( new Manager());
		Employee * p = nullptr;
		for( Person * sz: v ){
			p = dynamic_cast<Employee *>( sz );
			if( p != nullptr ){
				++counter;
			}
		}
		cout << "Number of employee is " << counter << endl;
	}
}

namespace TypeIdTest
{
	class Person{
	public:
		virtual void print(){cout<<"Person";};
	};
	class Employee:public Person{
	public:
		virtual void print(){cout<<"Employee";};
	};
	class Manager:public Employee{
	public:
		virtual void print(){cout<<"Manager";};
	};
	
	void Run(void){
		vector<Person*> v;
		int counter = 0;
		v.push_back(new Person());
		v.push_back(new Person());
		v.push_back(new Employee());
		v.push_back(new Employee());
		v.push_back( new Manager());
		v.push_back( new Manager());
		for( Person * sz: v ){
			if( typeid(*sz) == typeid(Employee) ){
				++counter;
			}
		}		
		cout << "Number of employee is " << counter << endl;
	}
}

void BindTest(void)
{
	using namespace std::placeholders;
	vector<int> v{1,2,3,4,5,6,7};
	int x = 3;
	int y = 5;
	auto i = find_if(v.begin(), v.end(),
			bind(logical_and<bool>(), 
				bind(greater<int>(), _1, x),
				bind(less<int>(), _1, y) 
				) 
			);
	cout << *i << " is greater than " << x << " and less than " << y << endl;
}

void LambadaTest(void)
{
	vector<int> v{1,2,3,4,5,6,7};
	int x = 3;
	int y = 5;
	auto i = find_if( v.begin(), v.end(), [&](int i) { return i > x && i < y; } );	
	cout << *i << " is greater than " << x << " and less than " << y << endl;	
}

namespace SmartPointerTest
{
	class A 
	{ 
	public: 
		void show() { cout << "A::show()" << endl; } 
	};
	
	unique_ptr<A> UniquePtrTest(void)
	{
		unique_ptr<A> p1 (new A); 
		p1 -> show(); 
		// returns the memory address of p1 
		cout << "p1 address: " <<  p1.get() << endl; 
		
		// transfers ownership to p2 
		unique_ptr<A> p2(move(p1)); 
		p2 -> show(); 
		cout << "p1 address: " << p1.get() << endl; 
		cout << "p2 address: " << p2.get() << endl; 
		
		// transfers ownership to p3 
		unique_ptr<A> p3 = move (p2); 
		p3->show(); 
		cout << "p1 address: " << p1.get() << endl; 
		cout << "p2 address: " << p2.get() << endl; 
		cout << "p3 address: " << p3.get() << endl; 
		return p3;
	}

	shared_ptr<A> SharedPtrTest(void)
	{	
		shared_ptr<A> p1 (new A); 
		p1->show(); 
		cout << "p1 address: " << p1.get() << endl; 
		cout << "p1 use count: " << p1.use_count() << endl; 

		shared_ptr<A> p2 (p1); 
		p2->show(); 
		cout << "p1 address: " << p1.get() << endl; 
		cout << "p2 address: " << p2.get() << endl; 
		
		// Returns the number of shared_ptr objects 
		//referring to the same managed object. 
		cout << "p1 use count: " << p1.use_count() << endl; 
		cout << "p2 use count: " << p2.use_count() << endl; 
		
		// Relinquishes ownership of p1 on the object 
		//and pointer becomes NULL 
		p1.reset(); 
		shared_ptr<A> p3 ;
		p3 = p2;
		p3->show(); 
		cout << "p1 address: " << p1.get() << endl; 
		cout << "p2 address: " << p2.get() << endl;
		cout << "p3 address: " << p3.get() << endl;
		cout << "p2 use count: " << p2.use_count() << endl; 
		cout << "p3 use count: " << p2.use_count() << endl; 
		return p2;
	}	
	
	namespace WeakPtrTest
	{
		struct Son;
		struct Daughter;
		struct Mother{
			~Mother(){
				cout << "Mother gone" << endl;
			}
			void setSon(const shared_ptr<Son> s ){
				mySon=s;
			}
			void setDaughter(const shared_ptr<Daughter> d ){
				myDaughter=d;
			}
			shared_ptr<const Son> mySon;
			weak_ptr<const Daughter> myDaughter;
		};

		struct Son{
			Son(shared_ptr<Mother> m):myMother(m){}
			~Son(){
				cout << "Son gone" << endl;
			}
			shared_ptr<const Mother> myMother;
		};

		struct Daughter{
			Daughter(shared_ptr<Mother> m):myMother(m){}
			~Daughter(){
				cout << "Daughter gone" << endl;
			}
			shared_ptr<const Mother> myMother;
		};
		
		void CyclicDependencyTest(void)
		{
			{
				shared_ptr<Mother> mother= shared_ptr<Mother>( new Mother);
				shared_ptr<Son> son= shared_ptr<Son>( new Son(mother) );
				shared_ptr<Daughter> daughter= shared_ptr<Daughter>( new Daughter(mother) );

				mother->setSon(son);
				mother->setDaughter(daughter);
				cout << "mother refrence count: " << mother.use_count() << endl;
				cout << "son refrence count: " << son.use_count() << endl;
				cout << "daughter refrence count: " << daughter.use_count() << endl;
			}
		}	
	}	
	
	void Run(void)
	{
		cout << "UniquePtrTest: " << endl; 
		unique_ptr<A> pUniquePtrTest =  UniquePtrTest();
		cout << "UniquePtrTest return address: " <<  pUniquePtrTest.get() << endl; 
		cout << endl << "SharedPtrTest: " << endl; 
		shared_ptr<A> pSharedPtrTest =  SharedPtrTest();
		cout << "SharedPtrTest return address: " <<  pSharedPtrTest.get() << endl;
		cout << "pSharedPtrTest use count: " << pSharedPtrTest.use_count() <<endl;
		cout << endl << "WeakPtrTest::CyclicDependencyTes: " << endl; 
		WeakPtrTest::CyclicDependencyTest();
	}	
}

void StreamsTest(void)
{
   string data;

   cout << "Use of left, setfill('x') and setw(6) manipulators before 123 value:" << endl; 
   cout << left << setfill('x') << setw(6) << 123 << endl;

   // open a file in read mode 
   ifstream template_file("templateFile.txt");
   // open a file in write mode and copy templateFile.txt to it
   ofstream out_file("copyOfTemplate.dat", ios::trunc);
   if(template_file && out_file)
		out_file << template_file.rdbuf();
	template_file.close();
	out_file.close();

	// display file content
	ifstream in_file("copyOfTemplate.dat");
	while(getline(in_file, data))
	{
		cout << data << endl;
	}
	in_file.close();


   out_file.open("outFileTest.dat", ios::trunc);
   cout << "Writing to the file" << endl;
   cout << "Enter your name: ";
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   getline(cin, data);
   stringstream str_stream;  
   str_stream << "Name: ";
   data = str_stream.str() + data;
   // write inputted data into the file.
   out_file << data << endl;
   cout << "Enter your age: "; 
   cin >> data; //will tokenize values according to white spaces
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   // reset stringstream
   str_stream.str("");
   str_stream.clear();
   str_stream << " years";
   // again write inputted data into the file.
   out_file << data + str_stream.str() << endl;
   out_file.close();

   // open a file in read mode.
   in_file.open("outFileTest.dat"); 
   cout << "Reading from the file" << endl; 
   while(getline(in_file, data)) 
	cout << data << endl;
   in_file.close();
}


namespace MultiThreadingWithAsyncTest
{
	mutex m;
	inline bool match( const std::string &pattern, std::string word )
	{
		if ( pattern.size() != word.size() )
			return false;
		for ( size_t i = 0 ; i < pattern.size() ; i++ ) 
			if ( pattern[ i ] != '.' && pattern[ i ] != word[ i ] )
				return false;
		return true;
	}

	vector<string> find_matches( string pattern, deque<string> &backlog )
	{
		vector<string> results;
		for ( ; ; ) {
			if ( backlog.size() == 0 ) {
				return results;
			}
			string word = backlog.front();
			backlog.pop_front();
			if ( match( pattern, word ) )
				results.push_back( word );
		}
	}

	vector<string> find_matches_m( string pattern, deque<string> &backlog )
	{
		vector<string> results;
		unique_lock<mutex> guard(m);
		for ( ; ; ) {
			if ( backlog.size() == 0 ) {
				guard.unlock();
				return results;
			}
			string word = backlog.front();
			backlog.pop_front();
			guard.unlock();
			if ( match( pattern, word ) )
				results.push_back( word );
		    guard.lock();
		}
	}

	void print_results(vector<string> words, string &pattern)
	{
		cerr << "Found " << words.size() 
			<< " matches for " << pattern 
			<< endl;
		for ( auto s : words )
			cout << s << "\t";
		cout << endl;
	}
	
	template<class ASYNC>
	void print_results_m( ASYNC &f, string &pattern, int threadno )
	{
		vector<string> words = f.get();
		cerr << "Found " << words.size() 
			<< " matches for " << pattern 
			<< " in thread " << threadno
			<< endl;
		for ( auto s : words )
			cout << s << "\t";
		cout << endl;
	}

	int sampleMain( int argc, char *argv[] )
	{
		if ( argc < 2 ) {
			cerr << "Usage: WordSearch match-expression\n\n"
					"match-expression contains lower case letters and periods.\n"
					"The periods will match any character\n";
			return -1;
		}
		string pattern = argv[ 1 ];
		//
		// Load the words into the deque
		//
		ifstream f( "sowpods.txt" );
		if ( !f ) {
			cerr << "Cannot open sowpods.txt in the current directory\n";
			return -1;
		}
		string word;
		deque<string> backlog, backlog_m;
		while ( f >> word )
		{
			backlog.push_back( word );
			backlog_m.push_back( word );
		}
		auto start = chrono::steady_clock::now();
		vector<string> words = find_matches( pattern, backlog );
		auto end = chrono::steady_clock::now();
		print_results(words, pattern);
		cout << "Elapsed time to find pattern in singlethread form : " 
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl << endl;		
		//
		// Now process the words and print the results
		//
		start = chrono::steady_clock::now();
		auto f1 = async( launch::async, find_matches_m, pattern, ref(backlog_m) );
		auto f2 = async( launch::async, find_matches_m, pattern, ref(backlog_m) );
		auto f3 = async( launch::async, find_matches_m, pattern, ref(backlog_m) );
		f1.wait();
		f2.wait();
		f3.wait();
	    end = chrono::steady_clock::now();
		print_results_m( f1, pattern, 1 );
		print_results_m( f2, pattern, 2 );
		print_results_m( f3, pattern, 3 );
		cout << "Elapsed time to find pattern in multithread form : " 
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;
		return 0;
	}
	void Run(void)
	{
		char* argv[2];
		argv[0] = new char(1);
		argv[1] = new char(10);
		cout << "Please enter a pattern atmost 10 characters for search in a dictionary:";
		cin >> argv[1];
	    sampleMain(2, argv);
	}
}

int showTestMenu(void)
{
	int i = 0;
	cout << "\nPlease choose one of sample test below:";
	cout << "\n1.  OverloadVsOverideTest";
	cout << "\n2.  GiveWordsAndSortTest";
	cout << "\n3.  TryCatchTest";
	cout << "\n4.  ConstAndRefInitTest";
	cout << "\n5.  FunctorTest";
	cout << "\n6.  IteratorTest";
	cout << "\n7.  SetContainerTest";
	cout << "\n8.  AlgorithmsTest";
	cout << "\n9.  IteratorDesignPatternTest";
	cout << "\n10. StreamIteratorTest"; 
	cout << "\n11. DynamicCastTest";
	cout << "\n12. TypeIdTest";
	cout << "\n13. BindTest";
	cout << "\n14. LambadaTest";
	cout << "\n15. SmartPointerTest";
	cout << "\n16. StreamsTest";
	cout << "\n17. MultiThreadingWithAsyncTest";
	cout << endl;
	cin	 >> i;
	cout << endl;
	return i;
}

int main() {
	switch(showTestMenu())
	{
		case(1):
		OverloadVsOverideTest();
		break;
		case(2):
		GiveWordsAndSortTest();
		break;
		case(3):
		TryCatchTest();
		break;
		case(4):
		ConstAndRefInitTest::Run();
		break;
		case(5):
		FunctorTest::Run();
		break;			
		case(6):
		IteratorTest::Run();
		break;		
		case(7):
		SetContainerTest::Run();
		break;
		case(8):
		AlgorithmsTest::Run();
		break;
		case(9):
		IteratorDesignPatternTest::Run();
		break;			
		case(10):
		StreamIteratorTest();
		break;
		case(11):
		DynamicCastTest::Run();
		break;
		case(12):
		TypeIdTest::Run();
		break;
		case(13):
		BindTest();
		break;
		case(14):
		LambadaTest();
		break;	
		case(15):
		SmartPointerTest::Run();
		break;	
		case(16):
		StreamsTest();
		break;
		case(17):
		MultiThreadingWithAsyncTest::Run();	
		break;		
	default:
		break;
	}
	return 0;
}