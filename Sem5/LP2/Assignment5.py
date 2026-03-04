def book_tickets(movie, tickets, showtime):
    ticket_price = 100
    total_bill = tickets * ticket_price
    print(f"\n✅ Booking confirmed for {movie}!")
    print(f"Details: {tickets} tickets for the {showtime} show.")
    print(f"Total Amount: Rs. {total_bill}\n")

def main():
    movies = {
        "Interstellar": ["10:00 AM", "2:00 PM", "6:00 PM"],
        "The Dark Knight": ["11:00 AM", "3:00 PM", "7:00 PM"],
        "Dune": ["9:30 AM", "1:30 PM", "5:30 PM"]
    }

    print("Hello! Welcome to Movie Booking ChatBot.")
    print("You can ask for 'movies', 'showtimes', or just type a movie name to book.")

    while True:
        user_input = input("\nYou: ").strip() #remove leading and trailing whotespaces
        message = user_input.lower()

        # 1. Check if the user typed a movie name directly
        found_movie = next((m for m in movies if m.lower() in message), None)

        if "hi" in message or "hello" in message:
            print("ChatBot: Hello! Which movie are you looking for today?")

        elif "bye" in message:
            print("ChatBot: Goodbye! Enjoy your movie.")
            break

        # 2. If a movie name was found in the input, start booking immediately
        elif found_movie:
            print(f"ChatBot: I see you want to watch {found_movie}!")
            print(f"Available showtimes: {', '.join(movies[found_movie])}")
            
            showtime = input("ChatBot: Which showtime would you like? ")
            
            try:
                tickets = int(input("ChatBot: How many tickets do you need? "))
                book_tickets(found_movie, tickets, showtime)
            except ValueError:
                print("ChatBot: Invalid ticket number. Let's try again from the start.")

        elif "movie" in message:
            print("Currently playing:", ", ".join(movies.keys()))

        elif "showtime" in message or "timing" in message:
            for m, t in movies.items():
                print(f"{m}: {', '.join(t)}")
                
        elif "thankyou" in message or "Thank you" in message or "thank" in message:
            print("Your Welcome! It was pleasure helping you!!")

        else:
            print("ChatBot: I didn't catch that. Try typing a movie name like 'Dune' to book!")

if __name__ == "__main__":
    main()