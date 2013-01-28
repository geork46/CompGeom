#include <iostream>
#include <GeomAlgo.h>

using namespace std;

int main()
{
	GeomAlgo algo;
	cout << "START TEST\n";
	/* 1: Test	*/
	{
		cout << "Test 1:\n";
		vector<point_type> cnt;
			cnt.push_back(point_type(2, 0));	
			cnt.push_back(point_type(6, 0));	
			cnt.push_back(point_type(10, 4));	
			cnt.push_back(point_type(8, 8));	
			cnt.push_back(point_type(5, 11));	
			cnt.push_back(point_type(1, 9));	
			cnt.push_back(point_type(0, 4));	
		polygon_type polygon;
		polygon.push_back(cnt);
		list<polygon_type> ps;
		ps.push_back(polygon);
		algo.init(ps);
		algo.print();
		if (algo.contains(point_type(4, -2)) == ps.end())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
		if (algo.contains(point_type(-2, 5)) == ps.end())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
		if (algo.contains(point_type(11, 4)) == ps.end())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
		if (algo.contains(point_type(9, 9)) == ps.end())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
		if (algo.contains(point_type(4, 12)) == ps.end())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
		if (algo.contains(point_type(7, 12)) == ps.end())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
		if (algo.contains(point_type(5, 5)) == ps.begin())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
	}
	/* 2: Test	*/
	{
		cout << "Test 2:\n";
		vector<point_type> cnt;
			cnt.push_back(point_type(0, 0));	
			cnt.push_back(point_type(100, 60));	
			cnt.push_back(point_type(50, 100));	
		polygon_type polygon;
		polygon.push_back(cnt);
		list<polygon_type> ps;
		ps.push_back(polygon);
		algo.init(ps);
		algo.print();
		if (algo.contains(point_type(10, 30)) == ps.end())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
		if (algo.contains(point_type(20, 70)) == ps.end())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
		if (algo.contains(point_type(90, 80)) == ps.end())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
		if (algo.contains(point_type(50, 50)) == ps.begin())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
		if (algo.contains(point_type(50, 70)) == ps.begin())
			cout << "\tTest OK\n";
		else
			cout << "\tFailed test\n";
	}
	/* 3: Test	*/
	
	cout << "END TEST\n";
	return 0;
}
