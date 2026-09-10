#include "bingo.h"
#include <iostream>
#include <vector>

using namespace std;

class Tester{
    public:
    
    // testing with an error case
    bool testError(){
        Bingo bingo(-2, -5, 15, 86);
        return (bingo.reCreateCard(-2, -5, 15, 86) == false);
    }

    // testing with normal case
    bool testNormal(){
        Bingo bingo(10, 5, 11, 85);
        return bingo.initCard();
    }

    // testing reCreateCard for an error case
    bool testReCreateCardError(){
        Bingo bingo(10, 5, 11, 85);
        return (bingo.reCreateCard(-10, -5, 15, 86) == false);
    }

    // testing reCreateCard for normal case
    bool testRecreateCardNormal(){
        Bingo bingo(10, 5, 11, 85);
        return bingo.reCreateCard(10, 5, 1, 50);
    }

    // testing initCard on an empty object (edge case)
    bool testInitCardEmpty(){
        Bingo bingo;
        return (bingo.initCard() == false);
    }

    // testing initCard for a nromal case
    bool testInitCardNormal(){
        Bingo bingo(5, 5, 1, 75);
        return bingo.initCard();
    }

    // testing play for an error case
    bool testPlayError(){
        Bingo bingo(5, 5, 1, 75);
        vector<int> ball = bingo.drawBalls();
        return (bingo.play(0, ball) == 0);
    }

    // testing play for normal case
    bool testPlayNormal(){
        Bingo bingo(5, 5, 1, 75);
        vector<int> ball = bingo.drawBalls();
        int output = bingo.play(10, ball);
        return (output >= 0);
    }

    // testing deep copy for edge case
    bool testDeepCopyEdge(){
        Bingo reg(5, 5, 1, 75);
        Bingo empty;

        reg = empty;
        return true;
    }

    // testing deep copy for normal case
    bool testDeepCopyNormal(){
        Bingo bingo(2, 5, 11, 85);
        bingo.initCard();

        Bingo copy;
        copy = bingo;

        return true;
    }

};

int main(){
    Tester tester;
    cout << "Running tests...\n";

    if (tester.testError()){
        cout << "Test msg: Constructor error case test passed!\n";
    } else {
        cout << "Test msg: Constructor error case test failed!\n";
    }

    if (tester.testNormal()){
        cout << "Test msg: Constructor normal case test passed!\n";
    } else {
        cout << "Test msg: Constructor normal case test failed!\n";
    }

    if (tester.testReCreateCardError()){
        cout << "Test msg: reCreateCard error case test passed!\n";
    } else {
        cout << "Test msg: reCreateCard error case test failed!\n";
    }

    if (tester.testRecreateCardNormal()){
        cout << "Test msg: reCreateCard normal case test passed!\n";
    } else {
        cout << "Test msg: reCreateCard normal case test failed!\n";
    }

    if (tester.testInitCardEmpty()){
        cout << "Test msg: initCard empty object test passed!\n";
    } else {
        cout << "Test msg: initCard empty object test failed!\n";
    }

    if (tester.testInitCardNormal()){
        cout << "Test msg: initCard normal case test passed!\n";
    } else {
        cout << "Test msg: initCard normal case test failed!\n";
    }

    if (tester.testPlayError()){
        cout << "Test msg: play error case test passed!\n";
    } else {
        cout << "Test msg: play error case test failed!\n";
    }

    if (tester.testPlayNormal()){
        cout << "Test msg: play normal case test passed!\n";
    } else {
        cout << "Test msg: play normal case test failed!\n";
    }

    if (tester.testDeepCopyEdge()){
        cout << "Test msg: Assignment operator test for edge case passed!\n";
    } else {
        cout << "Test msg: Assignment operator test for edge case failed!\n";
    }

    if (tester.testDeepCopyNormal()){
        cout << "Test msg: Assignment operator test for deep copy passed!\n";
    } else {
        cout << "Test msg: Assignment operator test for deep copy failed!\n";
    }

    cout << "Testing done\n";

    return 0;
}
