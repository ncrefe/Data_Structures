#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Key {
    string team;
    string shirt_number;
};

struct Event {
    int minute;
    string team;
    string shirt_number;
    string event_code;
};

class Player {
private:
    string team;
    string shirt_number;
    int goals;
    int assists;
    int score;

    bool initialized = false;

public:
    Player (string team, string shirt_number, int goals, int assists) {
        this->team = team;
        this->shirt_number = shirt_number;
        this->goals = goals;
        this->assists = assists;
        this->score = goals + assists;
    }
    Player () {
        this->team = "";
        this->shirt_number = "";
        this->goals = 0;
        this->assists = 0;
        this->score = 0;
    }

    string get_team() { return team; }
    string get_shirt_number() { return shirt_number; }
    int get_goals() { return goals; };
    int get_assists() { return assists; };
    int get_score() { return score; };

    void set_team(string team) { this->team = team; };
    void set_shirt_number(string shirt_number) { this->shirt_number = shirt_number; };
    void set_goals(int goals) { this->goals = goals; };
    void set_assists(int assists) { this->assists = assists; };
    void set_score(int score) { this->score = score; };

    void add_score(int value) { this->score = this->score + value;};

    void add_goals(int value) { this->goals = this->goals + value;};

    void add_assists(int value) { this->assists = this->assists + value;};
    
    bool is_initialized() { return initialized; };
    void initialize() { this->initialized = true; };

    void event(string event) {
        initialize();

        if (event.compare("S") == 0) {
            add_score(20);
            add_goals(1);
        } else if (event.compare("A") == 0) {
            add_score(10);
            add_assists(1);
        } else if (event.compare("T") == 0 ||
                   event.compare("P") == 0) {
            add_score(1);
        } else if (event.compare("SH") == 0){
            add_score(2);
        } else if (event.compare("SG") == 0){
            add_score(3);
        } else if (event.compare("IP") == 0){
            add_score(-1);
        } else if (event.compare("YC") == 0){
            add_score(-10);
        } else if (event.compare("RC") == 0){
            add_score(-20);
        } else if (event.compare("L") == 0){
            add_score(-2);
        } else if (event.compare("CG") == 0){
            add_score(-5);
        }

        

    }

};

class HashTable {
private:
    static const int TABLE_SIZE = 28;
    pair<Key, Player> table[TABLE_SIZE];

public:
    bool is_empty();
    
    int hash_function(string team, string shirt_number);
    int f(char team);
    
    void add_event(Event event);
    void print_table();

};


void HashTable::print_table() {
    cout << "Index\tTeam\tNo\tGoals\tAssists\tScore\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << "\t";
        if (table[i].second.is_initialized()) {
            cout    << table[i].second.get_team() << "\t" << table[i].second.get_shirt_number() << "\t" 
                    << table[i].second.get_goals() << "\t" << table[i].second.get_assists() << "\t" 
                    << table[i].second.get_score() << "\n";
        } else if (table[i].second.is_initialized() == false) {
            cout << "\t\t\t\t\t\n";
        }
    }
};



void HashTable::add_event(Event event) {
    int index = hash_function(event.team, event.shirt_number);
    bool is_match = table[index].first.team.compare(event.team) == 0 &&
                    table[index].first.shirt_number.compare(event.shirt_number) == 0;
    

    
    if (!is_match && table[index].second.is_initialized()){
        
        // in case of collision
        int i = 1;

        while (table[index].second.is_initialized()) {
            
            index = (hash_function(event.team, event.shirt_number) + i*i) % TABLE_SIZE;

            i++;
            
        }
    }

    if (!table[index].second.is_initialized()){
        table[index].second.set_team(event.team);
        table[index].second.set_shirt_number(event.shirt_number);
    } 

    Key key = {event.team, event.shirt_number};

    table[index].first = key;
    table[index].second.event(event.event_code);

    
    
};

bool HashTable::is_empty() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!table[i].second.is_initialized()) {
            return false;
        }
    }
    return true;
};

int HashTable::hash_function(string team, string shirt_number) {
    return (f(team[0]) + stoi(shirt_number)) % 28;
};


int HashTable::f(char team) {
    string teamstr = string(1, team);
    if (teamstr.compare("H") == 0){
        return 0;
    }
    
    return 99;

};


vector<string> splitString(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.

    string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
};



int main(int argc, char** argv) {

    // This time no utility functions are provided.

    // Do not forget to parse the command line argument.

    // Consider defining 
    // Key as a struct or a class that contains two fields: team and shirt number, and
    // Value as a struct or a class that contains three fields: goals, assists and score.
    // The hash table is an array of 28 such (Key, Value) pairs.

    string path = argv[1];
    int minute = atoi(argv[2]);

    HashTable table;

    string text;
    ifstream file(path);
    vector<string> data;
    Event event;

    getline(file, text);
    if (file.is_open()) {
        while (getline(file, text) && text != "") {
            
            data = splitString(text, ',');
            event.minute = stoi(data[0]);
            event.team = data[1];
            event.shirt_number = data[2];
            event.event_code = data[3];
            
            
            if (event.minute > minute) {
                break;
            }
            table.add_event(event);

        }
        file.close();
    }

    table.print_table();
    



    return 0;
}
