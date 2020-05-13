#include <iostream>
using namespace std;

#include "Playlist.h" 

PlaylistNode::PlaylistNode() : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(0) 
{}

PlaylistNode::PlaylistNode(string id, string name, string artist, int length) : uniqueID(id), songName(name), artistName(artist), songLength(length), nextNodePtr(0) 
{}

void PlaylistNode::InsertAfter(PlaylistNode * & newNode) {
    newNode->SetNext(this->GetNext());
    this->SetNext(newNode);
    
}

void PlaylistNode::SetNext(PlaylistNode* next) {
    this->nextNodePtr = next;
}

string PlaylistNode::GetID() const {
    return uniqueID;
}

string PlaylistNode::GetSongName() const {
    return songName;
}

string PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const {
    
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl << endl;

}


