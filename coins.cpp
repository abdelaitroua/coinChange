#include <algorithm>
#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
using namespace std;

//Function Prototypes
int CoinCtDP(vector<int>randomCoins, int);// Dynamic programing coin change
int CoinCtGreedy(vector<int>randomCoins, int);// Greedy coin change
vector<int> Shuffle(vector<int> &, vector<int> &);// Generate n random coins

int main(){

    int m, k, coins = 100, n = 5;
    double avePer = 0, totalAve = 0;
    vector<int> allCoins (coins);
    for(int i = 0; i < coins; i++)
        allCoins[i] = i + 1;// filling array with 1 to 100

    srand(time(NULL));
    cout << fixed << setprecision(2);
    cout << "Please Enter the number of coins you would like to use \n";
    cin >> n;
    vector<int> randomCoins(n);
    cout << "Calculating for n = " << n << ". Please wait ..." << endl;
    for (int T = 100; T <= 400; T++) {

        //cout << "Amount to change: " << T << endl;
        for (int i = 0; i < 100; i++) {
            //cout << "Random coins: ";
            Shuffle(randomCoins, allCoins);
            //cout << "Greedy solution: |" ;
            k = CoinCtGreedy(randomCoins, T);
            //cout << endl;
            //cout << "DP solution: |";
            m = CoinCtDP(randomCoins, T);
            //cout << endl;
            avePer += (m / double(k));
        }
        totalAve += avePer / 100;
        //cout << totalAve << endl;
    }
    //cout << endl;
    cout << "totalAve / 400 = " << totalAve /400 << " %" <<endl;

    //system("pause");
    return 0;

}

/*********************************************************************************
Name: CoinCtDP
Role: Uses dynamic programming to determin optimal number of coins to make change. 
Parameters: Vector randomcoins of 5 integers and an integer ch (Amount to change)
Returns: int number of coins
*********************************************************************************/
int CoinCtDP(vector<int>randomCoins, int ch) {// ch = amount to change
    vector<int> C(ch + 1);// Min # of coins to change T
    vector<int> S(ch + 1);// Last coin used to make change
    int min, coin = 0, count = 0;
    // Handling the base case of Algorithm
    C[0] = 0;
    // Implementing a tweaked version of the Make change algorithm
    for (int p = 1; p <= ch; p++) {
        min = INT_MAX;
        for (int i = 0; i < randomCoins.size(); i++) {
            // Enter loop only if coin is smaller than amout to be changed
            if (randomCoins[i] <= p) {
                if (1 + C[p - randomCoins[i]] < min){
                    min = 1 + C[p - randomCoins[i]];
                    coin = randomCoins[i];
                }
            }
        }
        C[p] = min;// min number of coin to make p cents change
        S[p] = coin;// last used coin to mak change

    }
    // Choose optimal solution
    while (ch > 0) {
        // displaying the last used coins
        //cout << S[ch] << "|";
        // substracting the last used coin from the index of the last used coins vector
        ch = ch - S[ch];
        count++;// counting the number of optimal coins to make change
    }
    //cout << endl;
    return count;
}

/*********************************************************************************
Name: CoinCtGreedy
Role: Uses Cashier greedy algorithm to determin optimal number of coins to make change.
Parameters: Vector randomcoins of 5 integers and and an integer T(Amount to change)
Returns: int number of coins
*********************************************************************************/
int CoinCtGreedy(vector<int>randomCoins, int ch) {
    int coin, count = 0;
    while (ch > 0) {
        for (int i = randomCoins.size() - 1; i >= 0; i--) {
            //coin ← largest coin denomination such that randomCoins[i] ≤ x
            while (randomCoins[i] <= ch) {
                coin = randomCoins[i];
                //cout << coin << "|";
                ch = ch - coin;
                count++;
            }

        }
    }
    return count;
}

/*********************************************************************************
Name: Shuffle
Role:  Uses Fisher-Yates algoritm to shuffle the randomcoins array of 100 numbers
Parameters: Vector randomcoins of 100 integers
Returns: vector integer of 5 unique randoms
*********************************************************************************/
vector<int> Shuffle(vector<int> &randomcoins, vector<int> &allCoins) {
    // Making sure random coins always have a 1
    randomcoins[0] = 1;
    
    //randomly fill array of coins using rand() for testing
    // for (auto it = allCoins.begin(); it < allCoins.end(); it++) {
        //*it = 1 + rand() % allCoins.size();
    //}
    
    //Fisher-Yates Shuffle
    int b, temp;
    for (auto i = allCoins.size() - 1; i > 1; i--){
        b = rand() % i ;//random index
        temp = allCoins[i];
        allCoins[i] = allCoins[b];
        allCoins[b] = temp;
    }
    for (auto i : allCoins)
        cout << i << "|";
    cout << endl;
    // start at position 1 and fill with shuffled all coins, have coin 1 at position 0;
    for (auto i = 1; i < randomcoins.size(); i++)
        randomcoins[i] = allCoins[i];
    // sort random coins
    sort(randomcoins.begin(), randomcoins.end());
    for (auto i : randomcoins)
    	cout << i << "|";

    cout << endl;
    cout << endl;
    cout << endl;
    return randomcoins;
}
