#include <iostream>
using namespace std;
#include "Playlist.h"

void printMenu(string);


int main() {
    
    string playlistName;
    
    cout << "Enter playlist's title:";
    getline(cin, playlistName);
    cout << endl << endl;
    
    printMenu(playlistName);
    
    return 0;
}

void printMenu(string titleName) {
    char userOption = ' ';
    string validCheck = "adcstoq";
    PlaylistNode * head = 0;
    PlaylistNode * tail = 0;
    int listSize = 0;
    
    // head = new PlaylistNode("A12", "Hello", "Adele", 40);
    // PlaylistNode * next = new PlaylistNode("B1", "Goodbye", "Some Band", 10);
    // PlaylistNode * next2 = new PlaylistNode("C2", "Thanks", "Some Band", 20);
    // PlaylistNode * next3 = new PlaylistNode("D3", "Wowow", "Some Band", 30);
    
    
    // head->InsertAfter(next);
    // next->InsertAfter(next2);
    // next2->InsertAfter(next3);
    // tail = next3;
    
    while (userOption != 'q') {
        cout << titleName << " PLAYLIST MENU" << endl;
        cout << "a - Add song" << endl;
        cout << "d - Remove song" << endl;
        cout << "c - Change position of song" << endl;
        cout << "s - Output songs by specific artist" << endl;
        cout << "t - Output total time of playlist (in seconds)" << endl;
        cout << "o - Output full playlist" << endl;
        cout << "q - Quit" << endl << endl;
                
        cout << "Choose an option:";
        cin >> userOption;
        cin.ignore();
        cout << endl;

        
        
        while(validCheck.find(userOption) == string::npos) {
            cout << titleName << " PLAYLIST MENU" << endl;
            cout << "a - Add song" << endl;
            cout << "d - Remove song" << endl;
            cout << "c - Change position of song" << endl;
            cout << "s - Output songs by specific artist" << endl;
            cout << "t - Output total time of playlist (in seconds)" << endl;
            cout << "o - Output full playlist" << endl;
            cout << "q - Quit" << endl << endl;
            cout << "Choose an option:";
            cin >> userOption;
            cin.ignore();
            cout << endl;
        }
        
        if (userOption == 'q') {
            return;
        }
        
        if (userOption == 'a') {
            string id, name, artist;
            int length;
            cout << endl;
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> id;
            cout << "Enter song's name:" << endl;
            cin.ignore();
            getline(cin, name);
            cout << "Enter artist's name:" << endl;
            getline(cin, artist);
            cout << "Enter song's length (in seconds):" << endl;
            cin >> length;
            cout << endl;
            
            PlaylistNode * temp = tail;
            tail = new PlaylistNode(id, name, artist, length);
            
            if (head == 0) {
                head = tail;
            } else {
                
                temp->SetNext(tail);
            }
            
            ++listSize;
            // if (head == 0) {
            //     head = new PlaylistNode(id, name, artist, length);
            //     tail = head;
            //     } else {
            
            //     PlaylistNode newNode(id, name, artist, length);
            //     tail->SetNext(&newNode);
            //     tail = &newNode;
                
            // }
            
            
        }
        if (userOption == 'd') {
            
            if (head == 0) {
                cout << "Playlist is empty" << endl << endl;
            } else {
                string removeID;
                bool done = true;
                PlaylistNode * preTemp = new PlaylistNode();
                preTemp->SetNext(head);
                cout << "REMOVE SONG" << endl;
                cout << "Enter song's unique ID:" << endl;
                cin >> removeID;
                cin.ignore();
                PlaylistNode* temp = head;
                while (temp != 0 && done) {
                    if (temp->GetID() == removeID) {
                        if (head == temp) {
                            PlaylistNode * toRemove = temp;
                            head = head->GetNext();
                            if (tail == temp) {
                                tail = 0;
                            }
                            cout << "\"" << toRemove->GetSongName() << "\" removed." << endl << endl;
                            temp = 0;
                            delete toRemove;
                            done = false;
                        } else {
                            PlaylistNode * toRemove = temp;
                            preTemp->SetNext(temp->GetNext());
                            if (tail == toRemove) {
                                tail = preTemp;
                            }
                            cout << "\"" << toRemove->GetSongName() << "\" removed." << endl << endl;
                            temp = 0;
                            delete toRemove;
                            done = false;
                        }
                    } else {
                        temp = temp->GetNext();
                        preTemp = preTemp->GetNext();
                    }
    
                }
                --listSize;
            }
            
        }
        
        if (userOption == 'c') {
            int oldPos = 0;
            int newPos = 0;
            
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl;
            cin >> oldPos;
            cin.ignore();
            cout << "Enter new position for song:" << endl;
            cin >> newPos;
            cin.ignore();
            
            if (newPos < 1) {
                newPos = 1;
            }
            // cout << "step 1" << endl;
            if (newPos > listSize) {
                newPos = listSize;
            }
            // cout << "step 2" << endl;
            
            if (newPos != oldPos) {
                PlaylistNode * temp = head;
                PlaylistNode * preTemp = new PlaylistNode();
                // cout << "why" << endl;
                
                preTemp->SetNext(temp);
                // cout << "why not" << endl;
                bool check = true;
                int counter = 1;
                int counterTwo = 1;
                PlaylistNode * oldPositionNode;
                // cout << "starting while loop" << endl;
                while(temp != 0 && check) {
                    // cout << "while loop with counter " << counter << endl;
                    
                    if (counter == oldPos) {
                        oldPositionNode = temp;
                        
                        if (counter == 1) {
                            head = head->GetNext();
                        } else {
                            preTemp->SetNext(temp->GetNext());
                        }
                        
                        if (tail == temp) {
                            tail = preTemp;
                        }
                        check = false;
                    }
                    
                    temp = temp->GetNext();
                    preTemp = preTemp->GetNext();
                    ++counter;
                }
                
                // cout << "old position extracted for " << oldPositionNode->GetSongName() << endl;
                
                PlaylistNode * tempTwo = head;
                bool check2 = true;
                
                while(tempTwo != 0 && check2) {
                    
                    if (newPos == 1) {
                        oldPositionNode->SetNext(head);
                        head = oldPositionNode;
                        check2 = false;
                        cout << "\"" << oldPositionNode->GetSongName() << "\" moved to position " << newPos << endl << endl;

                    } else if (counterTwo == (newPos - 1)) {
                        tempTwo->InsertAfter(oldPositionNode);
                        check2 = false;
                        cout << "\"" << oldPositionNode->GetSongName() << "\" moved to position " << newPos << endl << endl;
                    }
                    
                    tempTwo = tempTwo->GetNext();
                    ++counterTwo;
                }

            }
            
        }
        
        if (userOption == 's') {
            
                
                cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
                if (head == 0) {
                    cout << endl << "Playlist is empty" << endl << endl;
                    } else {
                    string artistFind;
                    cout << "Enter artist's name:" << endl;
                    getline(cin, artistFind);
                    cout << endl;
                    int songNum = 1;
                    PlaylistNode* temp = head;
                    while (temp != 0) {
                        if (temp->GetArtistName() == artistFind) {
                            cout << songNum << '.' << endl;
                            temp->PrintPlaylistNode();
                        }
                        
                        temp = temp->GetNext();
                        ++songNum;  
                    }
                }
        }
        
        
        if (userOption == 't') {
            
            if (head == 0) {
                cout << endl << "Playlist is empty" << endl << endl;
            } else {
                cout <<  "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
                PlaylistNode * temp = head;
                int totalSeconds = 0;
                while (temp != 0) {
                    totalSeconds = totalSeconds + temp->GetSongLength();
                    temp = temp->GetNext();
                    
                }
                cout << "Total time: " << totalSeconds << " seconds" << endl << endl;
            }
        }
        
        
        if (userOption == 'o') {
            cout << titleName << " - OUTPUT FULL PLAYLIST" << endl;
            int songNum = 1;
            if (head == 0) {
                cout << "Playlist is empty" << endl << endl;
            } else { PlaylistNode* temp = head;
                while (temp != 0) {
                    cout << songNum << '.' << endl;
                    temp->PrintPlaylistNode();
                    temp = temp->GetNext();
                    ++songNum;  
                }
            }
        }
        
        
        
    }

}