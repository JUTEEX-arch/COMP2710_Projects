//  How to compile code: g++ project_2.cpp
//  How to run code: ./a.out
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
#include <iomanip>
using namespace std;
// Constants
const int ttl_nmbr_runs = 10000;
const double a_acc = 1.0 / 3.0;
const double b_acc = 1.0 / 2.0;
const double c_acc = 1.0;
// Main functions: at_least_two_alive returns true if 2 or more shooters are alive, false otherwise
// aaron_shoots1 - first strategy for aaron changes values of c_alive and b_alive to false in case of a hit
// bob_shoots, charlie_shoots same thing for Bob and Charlie, aaron_shoots2 - second strategy for aaron
// Had couple of bugs in parametes declaration, asked chatGPT for troubleshoot
bool at_least_two_alive(bool a_alive, bool b_alive, bool c_alive)
{
    int alive_count = 0;
    if (a_alive)
        alive_count++;
    if (b_alive)
        alive_count++;
    if (c_alive)
        alive_count++;
    return (alive_count >= 2);
}
void aaron_shoots1(bool &b_alive, bool &c_alive)
{
    int shoot_target_result;
    shoot_target_result = rand() % 100;
    if (c_alive)
    {
        if (shoot_target_result < a_acc * 100)
        {
            c_alive = false;
        }
    }
    else if (b_alive)
    {
        if (shoot_target_result < a_acc * 100)
        {
            b_alive = false;
        }
    }
}
void bob_shoots(bool &a_alive, bool &c_alive)
{
    int shoot_target_result;
    shoot_target_result = rand() % 100;
    if (c_alive)
    {
        if (shoot_target_result < b_acc * 100)
        {
            c_alive = false;
        }
    }
    else if (a_alive)
    {
        if (shoot_target_result < b_acc * 100)
        {
            a_alive = false;
        }
    }
}
void charlie_shoots(bool &a_alive, bool &b_alive)
{
    if (b_alive)
    {
        b_alive = false;
    }
    else if (a_alive)
    {
        a_alive = false;
    }
}
void aaron_shoots2(bool &c_alive, bool &b_alive)
{
    if (b_alive && c_alive)
    {
        return;
    }
    aaron_shoots1(b_alive, c_alive);
}
// methods end here

// test drivers for the functions declared above
// I had no idea on how to use assert or the logic behind it, so I used chatGPT to help me + read through a couple of articles
void test_at_least_two_alive(void)
{
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";

    cout << "Case 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "Case passed ...\n";

    cout << "Case 2: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "Case passed ...\n";

    cout << "Case 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "Case passed ...\n";
    // I also had couple of bugs in cases 4, 6, 7, 8 since I've asserted true, when less then 2 shooters were alive
    cout << "Case 4: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "Case passed ...\n";

    cout << "Case 5: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "Case passed ...\n";

    cout << "Case 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "Case passed ...\n";

    cout << "Case 7: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "Case passed ...\n";

    cout << "Case 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "Case passed ...\n";

    cout << "Press Enter to continue...";
    cin.ignore().get();
}
void test_aaron_shoots1(void)
{
    cout << "Unit Testing 2: Function aaron_shoots1(b_alive, c_alive)\n";
    bool b_alive, c_alive;
    cout << "Case 1: Bob alive, Charlie alive\n";
    b_alive = true;
    c_alive = true;
    aaron_shoots1(b_alive, c_alive);
    cout << "Aaron is shooting at Charlie\n";

    cout << "Case 2: Bob dead, Charlie alive\n";
    b_alive = false;
    c_alive = true;
    aaron_shoots1(b_alive, c_alive);
    cout << "Aaron is shooting at Charlie\n";

    cout << "Case 3: Bob alive, Charlie dead\n";
    b_alive = true;
    c_alive = false;
    aaron_shoots1(b_alive, c_alive);
    cout << "Aaron is shooting at Bob\n";

    cout << "Press Enter to continue...";
    cin.ignore().get();
}

void test_bob_shoots(void)
{
    cout << "Unit Testing 3: Function bob_shoots(a_alive, c_alive)\n";
    bool a_alive, c_alive;
    cout << "Case 1: Aaron alive, Charlie alive\n";
    a_alive = true;
    c_alive = true;
    bob_shoots(a_alive, c_alive);
    cout << "Bob is shooting at Charlie\n";

    cout << "Case 2: Aaron dead, Charlie alive\n";
    a_alive = false;
    c_alive = true;
    bob_shoots(a_alive, c_alive);
    cout << "Bob is shooting at Charlie\n";

    cout << "Case 3: Aaron alive, Charlie dead\n";
    a_alive = true;
    c_alive = false;
    bob_shoots(a_alive, c_alive);
    cout << "Bob is shooting at Aaron\n";

    cout << "Press Enter to continue...";
    cin.ignore().get();
}

void test_charlie_shoots(void)
{
    cout << "Unit Testing 4: Function charlie_shoots(Aaron_alive, Bob_alive)\n";

    bool a_alive, b_alive;

    cout << "Case 1: Aaron alive, Bob alive\n";
    a_alive = true;
    b_alive = true;
    charlie_shoots(a_alive, b_alive);
    assert(b_alive == false);
    cout << "Charlie is shooting at Bob\n";

    cout << "Case 2: Aaron dead, Bob alive\n";
    a_alive = false;
    b_alive = true;
    charlie_shoots(a_alive, b_alive);
    assert(b_alive == false);
    cout << "Charlie is shooting at Bob\n";

    cout << "Case 3: Aaron alive, Bob dead\n";
    a_alive = true;
    b_alive = false;
    charlie_shoots(a_alive, b_alive);
    assert(a_alive == false);
    cout << "Charlie is shooting at Aaron\n";

    cout << "Press Enter to continue...";
    cin.ignore().get();
}

void test_aaron_shoots2(void)
{
    cout << "Unit Testing 5: Function aaron_shoots2(Bob_alive, Charlie_alive)\n";

    bool b_alive, c_alive;

    cout << "Case 1: Bob alive, Charlie alive\n";
    b_alive = true;
    c_alive = true;
    aaron_shoots2(b_alive, c_alive);
    cout << "Aaron intentionally misses his first shot\n";

    cout << "Case 2: Bob dead, Charlie alive\n";
    b_alive = false;
    c_alive = true;
    aaron_shoots2(b_alive, c_alive);
    cout << "Aaron is shooting at Charlie\n";

    cout << "Case 3: Bob alive, Charlie dead\n";
    b_alive = true;
    c_alive = false;
    aaron_shoots2(b_alive, c_alive);
    cout << "Aaron is shooting at Bob\n";

    cout << "Press Enter to continue...";
    cin.ignore().get();
}

// test drivers end here

// method to simulate 1 truel, returns 1 if Aaron wins, 2 if Bob wins, 3 if Charlie wins
int simulate_truel(bool strategy2)
{
    bool a_alive = true;
    bool b_alive = true;
    bool c_alive = true;

    bool first_turn = true; // need to check this for strategy 2, since in strategy 2 Aaron intentionally misses
    while (at_least_two_alive(a_alive, b_alive, c_alive))
    {
        if (a_alive)
        {
            if (strategy2 && first_turn)
            {
                aaron_shoots2(b_alive, c_alive);
            }
            else
            {
                aaron_shoots1(b_alive, c_alive);
            }
        }
        first_turn = false;

        if (b_alive)
        {
            bob_shoots(a_alive, c_alive);
        }

        if (c_alive)
        {
            charlie_shoots(a_alive, b_alive);
        }
    }

    if (a_alive)
    {
        return 1;
    }
    if (b_alive)
    {
        return 2;
    }
    return 3;
}

int main()
{
    srand(time(0));
    cout << "*** Welcome to Student X's Truel of the Fates Simulator ***\n\n";
    // calling the test drivers
    test_at_least_two_alive();
    test_aaron_shoots1();
    test_bob_shoots();
    test_charlie_shoots();
    test_aaron_shoots2();
    cout << "Ready to test strategy 1 10000 times):\n";
    cout << "Press enter to continue..\n";
    cin.ignore().get();
    int a_wins1 = 0;
    int b_wins1 = 0;
    int c_wins1 = 0;
    // 10000 simulations for stratagy 1
    for (int i = 0; i < ttl_nmbr_runs; i++)
    {
        int winner = simulate_truel(false);
        if (winner == 1)
        {
            a_wins1++;
        }
        else if (winner == 2)
        {
            b_wins1++;
        }
        else
        {
            c_wins1++;
        }
    }
    // Statistics
    cout << "Aaron won " << a_wins1 << "/" << ttl_nmbr_runs
         << " truels or " << (a_wins1 * 100.0 / ttl_nmbr_runs) << "%\n";
    cout << "Bob won " << b_wins1 << "/" << ttl_nmbr_runs
         << " truels or " << (b_wins1 * 100.0 / ttl_nmbr_runs) << "%\n";
    cout << "Charlie won " << c_wins1 << "/" << ttl_nmbr_runs
         << " truels or " << (c_wins1 * 100.0 / ttl_nmbr_runs) << "%\n\n";

    cout << "Ready to test strategy 2 10000 times:\n";
    cout << "Press enter to continue..\n";

    //

    cin.ignore().get();
    int a_wins2 = 0;
    int b_wins2 = 0;
    int c_wins2 = 0;
    // 10000 simulations for stratagy 2
    for (int i = 0; i < ttl_nmbr_runs; i++)
    {
        int winner = simulate_truel(true);
        if (winner == 1)
        {
            a_wins2++;
        }
        else if (winner == 2)
        {
            b_wins2++;
        }
        else
        {
            c_wins2++;
        }
    }
    // Statistics
    cout << "Aaron won " << a_wins2 << "/" << ttl_nmbr_runs
         << " truels or " << (a_wins2 * 100.0 / ttl_nmbr_runs) << "%\n";
    cout << "Bob won " << b_wins2 << "/" << ttl_nmbr_runs
         << " truels or " << (b_wins2 * 100.0 / ttl_nmbr_runs) << "%\n";
    cout << "Charlie won " << c_wins2 << "/" << ttl_nmbr_runs
         << " truels or " << (c_wins2 * 100.0 / ttl_nmbr_runs) << "%\n\n";

    if (a_wins1 > a_wins2)
    {
        cout << "Strategy 1 is better\n";
    }
    else
    {
        cout << "Strategy 2 is better\n";
    }
    return 0;
}