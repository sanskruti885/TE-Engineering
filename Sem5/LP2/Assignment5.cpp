#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Convert string to lowercase
string toLower(string text) {
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}

// Display movies
void showMovies(map<string, vector<string>> &movies) {
    cout << "Here are the movies currently playing:\n";
    for (auto &movie : movies) {
        cout << "- " << movie.first << endl;
    }
}

// Display showtimes
void showTimings(map<string, vector<string>> &movies) {
    cout << "Here are the showtimes:\n";
    for (auto &movie : movies) {
        cout << movie.first << ":\n";
        for (auto &time : movie.second) {
            cout << "   " << time << endl;
        }
    }
}

// Booking function
void bookTickets(string movie, int tickets, string showtime) {
    int ticket_price = 100;
    int total_bill = tickets * ticket_price;

    cout << "\nBooking confirmed!\n";
    cout << "Movie: " << movie << endl;
    cout << "Tickets: " << tickets << endl;
    cout << "Showtime: " << showtime << endl;
    cout << "Total amount: Rs. " << total_bill << endl;
}

int main() {

    map<string, vector<string>> movies = {
        {"Interstellar", {"Morning: 10:00 AM", "Afternoon: 2:00 PM", "Evening: 6:00 PM"}},
        {"The Dark Knight", {"Morning: 11:00 AM", "Afternoon: 3:00 PM", "Evening: 7:00 PM"}},
        {"Dune", {"Morning: 9:30 AM", "Afternoon: 1:30 PM", "Evening: 5:30 PM"}}
    };

    string userInput;

    cout << "Hello! Welcome to Movie Booking ChatBot.\n";

    while (true) {
        cout << "\nYou: ";
        getline(cin, userInput);

        string message = toLower(userInput);

        if (message.find("hi") != string::npos || message.find("hello") != string::npos) {
            cout << "ChatBot: Hello! Ready to book some movie tickets?\n";
        }

        else if (message.find("movie") != string::npos) {
            showMovies(movies);
        }

        else if (message.find("showtime") != string::npos || message.find("timing") != string::npos) {
            showTimings(movies);
        }

        else if (message.find("book") != string::npos) {
            string movie, showtime;
            int tickets;

            cout << "Which movie would you like to watch? : ";
            getline(cin, movie);

            cout << "How many tickets do you need? : ";
            cin >> tickets;
            cin.ignore();  // clear buffer

            cout << "At what time would you like to watch the movie? : ";
            getline(cin, showtime);

            bookTickets(movie, tickets, showtime);
        }

        else if (message.find("bye") != string::npos || message.find("goodbye") != string::npos) {
            cout << "ChatBot: Thank you! Enjoy your movie. Goodbye!\n";
            break;
        }

        else {
            cout << "ChatBot: Sorry, I didn't understand. You can ask about movies, showtimes, or book tickets.\n";
        }
    }

    return 0;
}