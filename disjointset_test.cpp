/*
 * To compile: g++ disjointset.cpp disjointset_test.cpp timer.cpp -std=c++0x
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "disjointset.hpp"
#include "timer.hpp"

bool test1(std::string &error);
bool test2(std::string &error);
bool test3(std::string &error);
bool test4(std::string &error);
bool test5(std::string &error);
bool test6(std::string &error);
bool test7(std::string &error);
bool test8(std::string &error);
bool test9(std::string &error);
bool test10(std::string &error);
bool test11(std::string &error);
const int numTests = 11;
typedef bool (*TestPtr)(std::string &);

int main(void) {
  TestPtr runTest[numTests] = {test1, test2, test3, test4,  test5, test6,
                               test7, test8, test9, test10, test11};
  std::string msg;
  bool result = true;
  int numPassed = 0;
  for (int i = 0; result && i < numTests; i++) {
    result = runTest[i](msg);
    if (!result) {
      std::cout << msg << std::endl;
    } else {
      numPassed++;
      std::cout << "Test " << i + 1 << " passed!" << std::endl;
    }
  }
  if (numPassed == numTests) {
    std::cout << "All tests passed!" << std::endl;
    return 0;
  } else {
    std::cout << "Tests failing!" << std::endl;
    return 1;
  }
}
/* test1: make 100 disjoint sets, check return value.  Call makeSet() on
   sets that are made, ensure that return is false.
*/
bool test1(std::string &error) {
  DisjointSet theSet(100);
  bool result;
  bool rc = true;
  for (int i = 0; rc && i < 100; i++) {
    result = theSet.makeSet(i);
    if (!result) {
      rc = false;
      error = "Error 1a: makeSet() return value error, function should have "
              "returned true";
    }
  }
  for (int i = 0; rc && i < 100; i++) {
    result = theSet.makeSet(i);
    if (result) {
      rc = false;
      error = "Error 1b: makeSet() return value error, function should have "
              "returned false";
    }
  }
  return rc;
}

/*test2: call findSet() on sets with 1 item, it should be rep*/
bool test2(std::string &error) {
  DisjointSet theSet(100);
  int result;
  bool rc = true;
  for (int i = 0; rc && i < 100; i++) {
    theSet.makeSet(i);
    result = theSet.findSet(i);
    if (result != i) {
      rc = false;
      error = "Error 2: findSet() did not return the correct representative";
    }
  }
  return rc;
}

/*test3: create 100 items, merge together into pairs, check
  that their representatives are consistent*/
bool test3(std::string &error) {
  DisjointSet theSet(100);
  bool result;
  int rep1;
  int rep2;
  bool rc = true;
  for (int i = 0; i < 100; i++) {
    theSet.makeSet(i);
  }
  for (int i = 0; rc && i < 100; i += 2) {
    result = theSet.unionSets(i, i + 1);
    if (result != true) {
      rc = false;
      error = "Error 3: unionSets() did not return the correct value, it "
              "should have returned true";
    }
  }
  for (int i = 0; rc && i < 50; i++) {
    rep1 = theSet.findSet(i * 2);
    rep2 = theSet.findSet(i * 2 + 1);
    if (rep1 != rep2) {
      rc = false;
      error = "Error 3: findSet() is returning two different reps for objects "
              "in same set";
    }
    if (rc && (rep1 != i * 2 && rep1 != (i * 2 + 1))) {
      rc = false;
      error = "Error 3: findSet() is returning a value that is not a member of "
              "the set";
    }
  }
  return rc;
}

/*test 4: try to call unionSets() with values that are not the reps
  for the set, check return value, ensure that union() did not occur*/
bool test4(std::string &error) {
  DisjointSet theSet(100);
  bool result;
  int rep1;
  int rep2;
  bool rc = true;
  for (int i = 0; i < 100; i++) {
    theSet.makeSet(i);
  }
  for (int i = 0; rc && i < 100; i += 2) {
    result = theSet.unionSets(i, i + 1);
  }
  for (int i = 0; rc && i < 50; i += 2) {
    rep1 = theSet.findSet(i * 2);
    rep2 = theSet.findSet((i + 1) * 2);
    int arg1 = (rep1 == i * 2) ? i * 2 + 1 : i * 2;
    int arg2 = (rep2 == (i + 1) * 2) ? (i + 1) * 2 + 1 : (i + 1) * 2;
    result = theSet.unionSets(arg1, arg2);
    if (result != false) {
      rc = false;
      error = "Error 4: unionSets() should return false if non-representatives "
              "are used as arguments";
    } else {
      if (theSet.findSet(arg1) == theSet.findSet(arg2)) {
        rc = false;
        error = "Error 4: uninonSet() should have done nothing if "
                "non-representatives were used as arguments";
      }
    }
  }
  return rc;
}
/*test 5: unionSets() on sets that are more than 1 element big*/

bool test5(std::string &error) {
  DisjointSet theSet(100);
  bool result;
  int rep1;
  int rep2;
  bool rc = true;
  for (int i = 0; i < 100; i++) {
    theSet.makeSet(i);
  }
  for (int i = 0; rc && i < 100; i += 2) {
    result = theSet.unionSets(i, i + 1);
  }
  for (int i = 0; rc && i < 50; i += 2) {
    rep1 = theSet.findSet(i * 2);
    rep2 = theSet.findSet((i + 1) * 2);

    result = theSet.unionSets(rep1, rep2);
    if (result == false) {
      rc = false;
      error = "Error 5a: unionSets() returned false, it should have returned "
              "true as sets should have been unioned";
    } else {
      if (theSet.findSet(rep1) != theSet.findSet(rep2)) {
        rc = false;
        error = "Error 5b: uninonSet() should have combined the two sets and "
                "their reps should be same";
      }
    }
  }
  return rc;
}

/*Test 6: further testing on unionSets() and findSet()*/
bool test6(std::string &error) {
  DisjointSet theSet(100);
  bool result;
  int rep1;
  int rep2;
  bool rc = true;
  for (int i = 0; i < 100; i++) {
    theSet.makeSet(i);
  }
  for (int i = 0; rc && i < 100; i += 2) {
    result = theSet.unionSets(i, i + 1);
  }
  for (int i = 0; rc && i < 50; i += 2) {
    rep1 = theSet.findSet(i * 2);
    rep2 = theSet.findSet((i + 1) * 2);
    theSet.unionSets(rep1, rep2);
  }
  for (int i = 0, j = 99; rc && i < 48; i += 4, j -= 4) {
    rep1 = theSet.findSet(i);
    rep2 = theSet.findSet(j);
    result = theSet.unionSets(rep1, rep2);
    if (result == false) {
      rc = false;
      error =
          "Error 6a: unionSets() returned false, it should have returned true";
    }
  }
  for (int i = 0, j = 99; rc && i < 48; i += 4, j -= 4) {
    int newRep = theSet.findSet(i);
    for (int k = 0; rc && k < 4; k++) {
      if (theSet.findSet(i + k) != newRep) {
        rc = false;
        error =
            "Error 6b: findSet() did not return a consistent representative";
      }
      if (theSet.findSet(j - k) != newRep) {
        rc = false;
        error =
            "Error 6c: findSet() did not return a consistent representative";
      }
    }
  }
  rep1 = theSet.findSet(97);
  rep2 = theSet.findSet(50);
  result = theSet.unionSets(rep1, rep2);
  if (result == false) {
    rc = false;
    error =
        "Error 6d: unionSets() returned false, it should have returned true";
  }
  int newRep = theSet.findSet(0);
  for (int i = 0; rc && i < 4; i++) {
    if (theSet.findSet(i) != newRep) {
      rc = false;
      error = "Error 6e: findSet() did not return a consistent representative";
    }
  }
  for (int i = 0; rc && i < 4; i++) {
    if (theSet.findSet(99 - i) != newRep) {
      rc = false;
      error = "Error 6f: findSet() did not return a consistent representative";
    }
  }
  for (int i = 0; rc && i < 4; i++) {
    if (theSet.findSet(i + 48) != newRep) {
      rc = false;
      error = "Error 6g: findSet() did not return a consistent representative";
    }
  }
  return rc;
}

/*Test 7: Test copy constructor*/
bool test7(std::string &error) {
  DisjointSet theSet(100);
  bool result;
  int rep1;
  int rep2;
  bool rc = true;
  for (int i = 0; i < 100; i++) {
    theSet.makeSet(i);
  }
  for (int i = 0; rc && i < 100; i += 2) {
    result = theSet.unionSets(i, i + 1);
  }
  for (int i = 0; rc && i < 50; i += 2) {
    rep1 = theSet.findSet(i * 2);
    rep2 = theSet.findSet((i + 1) * 2);
    theSet.unionSets(rep1, rep2);
  }
  for (int i = 0, j = 99; rc && i < 48; i += 4, j -= 4) {
    rep1 = theSet.findSet(i);
    rep2 = theSet.findSet(j);
    result = theSet.unionSets(rep1, rep2);
  }
  DisjointSet copy = theSet;
  for (int i = 0, j = 99; rc && i < 48; i += 4, j -= 4) {
    int newRep = copy.findSet(i);
    for (int k = 0; rc && k < 4; k++) {
      if (copy.findSet(i + k) != newRep) {
        rc = false;
        error = "Error 7: Copy constructor did not produce a duplicate with "
                "same disjoint sets";
      }
      if (copy.findSet(j - k) != newRep) {
        rc = false;
        error = "Error 7b: Copy constructor did not produce a duplicate with "
                "same disjoint sets";
      }
    }
  }
  rep1 = theSet.findSet(97);
  rep2 = theSet.findSet(50);
  result = theSet.unionSets(rep1, rep2);
  if (copy.findSet(97) == copy.findSet(50)) {
    rc = false;
    error = "Error 7c: Copy constructor appears to not have made a deep copy";
  }
  return rc;
}

/*Test 8: Test Assignment Operator*/
bool test8(std::string &error) {
  DisjointSet theSet(100);
  DisjointSet copy(50);
  DisjointSet copy2(30);
  bool result;
  int rep1;
  int rep2;
  bool rc = true;
  for (int i = 0; i < 50; i++) {
    copy.makeSet(i);
  }
  for (int i = 0; i < 30; i++) {
    copy2.makeSet(i);
  }

  for (int i = 0; i < 100; i++) {
    theSet.makeSet(i);
  }
  for (int i = 0; rc && i < 100; i += 2) {
    result = theSet.unionSets(i, i + 1);
  }
  for (int i = 0; rc && i < 50; i += 2) {
    rep1 = theSet.findSet(i * 2);
    rep2 = theSet.findSet((i + 1) * 2);
    theSet.unionSets(rep1, rep2);
  }
  for (int i = 0, j = 99; rc && i < 48; i += 4, j -= 4) {
    rep1 = theSet.findSet(i);
    rep2 = theSet.findSet(j);
    result = theSet.unionSets(rep1, rep2);
  }
  copy2 = copy = theSet;
  for (int i = 0, j = 99; rc && i < 48; i += 4, j -= 4) {
    int newRep = copy.findSet(i);
    for (int k = 0; rc && k < 4; k++) {
      if (copy.findSet(i + k) != newRep) {
        rc = false;
        error = "Error 8a: copy assignment operator did not produce a "
                "duplicate with same disjoint sets";
      }
      if (copy.findSet(j - k) != newRep) {
        rc = false;
        error = "Error 8b: copy assignment operator did not produce a "
                "duplicate with same disjoint sets";
      }
    }
  }
  for (int i = 0, j = 99; rc && i < 48; i += 4, j -= 4) {
    int newRep = copy2.findSet(i);
    for (int k = 0; rc && k < 4; k++) {
      if (copy2.findSet(i + k) != newRep) {
        rc = false;
        error = "Error 8c: possible return value error in assignment operator";
      }
      if (copy2.findSet(j - k) != newRep) {
        rc = false;
        error = "Error 8d: possible return value error in assignment operator";
      }
    }
  }
  rep1 = theSet.findSet(97);
  rep2 = theSet.findSet(50);
  result = theSet.unionSets(rep1, rep2);
  if (copy.findSet(97) == copy.findSet(50)) {
    rc = false;
    error =
        "Error 8e: assignment operator appears to not have made a deep copy";
  }
  if (copy2.findSet(97) == copy2.findSet(50)) {
    rc = false;
    error =
        "Error 8e: assignment operator appears to not have made a deep copy";
  }

  return rc;
}

/*Test 9: Test move constructor*/
bool test9(std::string &error) {
  DisjointSet theSet(100);
  bool result;
  int rep1;
  int rep2;
  bool rc = true;
  for (int i = 0; i < 100; i++) {
    theSet.makeSet(i);
  }
  for (int i = 0; rc && i < 100; i += 2) {
    result = theSet.unionSets(i, i + 1);
  }
  for (int i = 0; rc && i < 50; i += 2) {
    rep1 = theSet.findSet(i * 2);
    rep2 = theSet.findSet((i + 1) * 2);
    theSet.unionSets(rep1, rep2);
  }
  for (int i = 0, j = 99; rc && i < 48; i += 4, j -= 4) {
    rep1 = theSet.findSet(i);
    rep2 = theSet.findSet(j);
    result = theSet.unionSets(rep1, rep2);
  }
  DisjointSet copy = std::move(theSet);
  for (int i = 0, j = 99; rc && i < 48; i += 4, j -= 4) {
    int newRep = copy.findSet(i);
    for (int k = 0; rc && k < 4; k++) {
      if (copy.findSet(i + k) != newRep) {
        rc = false;
        error = "Error 9a: move constructor did not produce a duplicate with "
                "same disjoint sets";
      }
      if (copy.findSet(j - k) != newRep) {
        rc = false;
        error = "Error 9b: move constructor did not produce a duplicate with "
                "same disjoint sets";
      }
    }
  }

  return rc;
}

/*Test 10: Test Move Assignment Operator*/
bool test10(std::string &error) {
  DisjointSet theSet(100);
  DisjointSet copy(50);
  bool result;
  int rep1;
  int rep2;
  bool rc = true;
  for (int i = 0; i < 50; i++) {
    copy.makeSet(i);
  }
  for (int i = 0; i < 100; i++) {
    theSet.makeSet(i);
  }
  for (int i = 0; rc && i < 100; i += 2) {
    result = theSet.unionSets(i, i + 1);
  }
  for (int i = 0; rc && i < 50; i += 2) {
    rep1 = theSet.findSet(i * 2);
    rep2 = theSet.findSet((i + 1) * 2);
    theSet.unionSets(rep1, rep2);
  }
  for (int i = 0, j = 99; rc && i < 48; i += 4, j -= 4) {
    rep1 = theSet.findSet(i);
    rep2 = theSet.findSet(j);
    result = theSet.unionSets(rep1, rep2);
  }
  copy = std::move(theSet);
  for (int i = 0, j = 99; rc && i < 48; i += 4, j -= 4) {
    int newRep = copy.findSet(i);
    for (int k = 0; rc && k < 4; k++) {
      if (copy.findSet(i + k) != newRep) {
        rc = false;
        error = "Error 10a: move assignment did not produce a duplicate with "
                "same disjoint sets";
      }
      if (copy.findSet(j - k) != newRep) {
        rc = false;
        error = "Error 10b: move assignment did not produce a duplicate with "
                "same disjoint sets";
      }
    }
  }

  return rc;
}
/*Test 11: Timing runs, no errors for these.*/
bool test11(std::string &error) {

  Timer t;
  Timer t2;
  DisjointSet set1(50000);
  DisjointSet set2(50000);
  t.reset();
  for (int i = 0; i < 50000; i++) {
    t.start();
    set1.makeSet(i);
    set2.makeSet(i);
    t.stop();
  }
  std::cout << "100000 makeSet(): " << t.currtime() << std::endl;
  int rep1;
  int rep2;
  t.reset();
  t2.reset();
  for (int i = 0; i < 49999; i++) {
    t.start();
    rep1 = set1.findSet(i);
    rep2 = set1.findSet(i + 1);
    t.stop();
    t2.start();
    set1.unionSets(rep1, rep2);
    t2.stop();
  }
  std::cout << "49998 findSet(): " << t.currtime() << std::endl;
  std::cout << "49999 unionSets(): " << t2.currtime() << std::endl;
  t.reset();
  t2.reset();
  for (int i = 0; i < 49999; i++) {
    int choice = rand() % (i + 1);
    t.start();
    rep1 = set1.findSet(choice);
    rep2 = set1.findSet(i + 1);
    t.stop();
    t2.start();
    set1.unionSets(rep2, rep1);
    t2.stop();
  }
  std::cout << "another 49998 findSet(): " << t.currtime() << std::endl;
  std::cout << "another 49999 unionSets(): " << t2.currtime() << std::endl;

  return true;
}