#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    string title, artist;
    Node *prev, *next;

    Node(string t, string a) {
        title = t;
        artist = a;
        prev = next = NULL;
    }
};

class Playlist {
    Node *head, *current;

public:
    Playlist() {
        head = current = NULL;
    }

    void addSong() {
        string title, artist;

        cin.ignore();

        cout << "Enter song title: ";
        getline(cin, title);

        cout << "Enter artist name: ";
        getline(cin, artist);

        Node *p = new Node(title, artist);

        if (head == NULL)
            head = current = p;
        else {
            Node *q = head;

            while (q->next != NULL)
                q = q->next;

            q->next = p;
            p->prev = q;
        }

        cout << "Song added successfully!\n";
    }

    void deleteSong() {
        if (head == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        string title;

        cin.ignore();

        cout << "Enter song title to delete: ";
        getline(cin, title);

        Node *p = head;

        while (p != NULL && p->title != title)
            p = p->next;

        if (p == NULL) {
            cout << "Song not found.\n";
            return;
        }

        if (p->prev != NULL)
            p->prev->next = p->next;
        else
            head = p->next;

        if (p->next != NULL)
            p->next->prev = p->prev;

        if (current == p)
            current = head;

        delete p;

        cout << "Song deleted successfully!\n";
    }

    void display() {
        Node *q = head;

        if (q == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        while (q != NULL) {
            cout << q->title << " - " << q->artist;

            if (q == current)
                cout << " [CURRENT]";

            cout << endl;
            q = q->next;
        }
    }

    void reverseDisplay() {
        Node *q = head;

        if (q == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        while (q->next != NULL)
            q = q->next;

        while (q != NULL) {
            cout << q->title << " - "
                 << q->artist << endl;

            q = q->prev;
        }
    }

    void playCurrent() {
        if (current == NULL)
            cout << "Playlist is empty.\n";
        else
            cout << "Playing: " << current->title
                 << " - " << current->artist << endl;
    }

    void nextSong() {
        if (current == NULL)
            cout << "Playlist is empty.\n";
        else if (current->next == NULL)
            cout << "Already at the last song.\n";
        else {
            current = current->next;
            playCurrent();
        }
    }

    void previousSong() {
        if (current == NULL)
            cout << "Playlist is empty.\n";
        else if (current->prev == NULL)
            cout << "Already at the first song.\n";
        else {
            current = current->prev;
            playCurrent();
        }
    }

    void playAll() {
        Node *q = head;

        if (q == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        while (q != NULL) {
            cout << "Playing: " << q->title
                 << " - " << q->artist << endl;

            q = q->next;
        }
    }

    void repeatAll() {
        int n;

        if (head == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "Enter number of repetitions: ";
        cin >> n;

        for (int i = 1; i <= n; i++) {
            cout << "Repetition " << i << endl;
            playAll();
        }
    }

    void showCurrent() {
        playCurrent();
    }
};

int main() {
    Playlist p;
    int choice;

    do {
        cout << "\n--- MUSIC PLAYLIST MANAGER ---\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist\n";
        cout << "4. Display in Reverse\n";
        cout << "5. Play Current Song\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Play Complete Playlist\n";
        cout << "9. Repeat All\n";
        cout << "10. Show Current Song\n";
        cout << "11. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                p.addSong();
                break;

            case 2:
                p.deleteSong();
                break;

            case 3:
                p.display();
                break;

            case 4:
                p.reverseDisplay();
                break;

            case 5:
                p.playCurrent();
                break;

            case 6:
                p.nextSong();
                break;

            case 7:
                p.previousSong();
                break;

            case 8:
                p.playAll();
                break;

            case 9:
                p.repeatAll();
                break;

            case 10:
                p.showCurrent();
                break;

            case 11:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 11);

    return 0;
}
/*
--- MUSIC PLAYLIST MANAGER ---
1. Add Song
2. Delete Song
3. Display Playlist
4. Display in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 1
Enter song title: Perfect
Enter artist name: Ed Sheeran
Song added successfully!

--- MUSIC PLAYLIST MANAGER ---
1. Add Song
2. Delete Song
3. Display Playlist
4. Display in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 1
Enter song title: Shape of You
Enter artist name: Ed Sheeran
Song added successfully!

--- MUSIC PLAYLIST MANAGER ---
1. Add Song
2. Delete Song
3. Display Playlist
4. Display in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 3
Perfect - Ed Sheeran [CURRENT]
Shape of You - Ed Sheeran

--- MUSIC PLAYLIST MANAGER ---
1. Add Song
2. Delete Song
3. Display Playlist
4. Display in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 6
Playing: Shape of You - Ed Sheeran

--- MUSIC PLAYLIST MANAGER ---
1. Add Song
2. Delete Song
3. Display Playlist
4. Display in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 4
Shape of You - Ed Sheeran
Perfect - Ed Sheeran

--- MUSIC PLAYLIST MANAGER ---
1. Add Song
2. Delete Song
3. Display Playlist
4. Display in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 11
Thank you!
*/
