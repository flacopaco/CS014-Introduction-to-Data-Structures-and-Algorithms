#ifndef PLAYLIST_H
#define PLAYLIST_H

class PlaylistNode {
    public:
     PlaylistNode();
     PlaylistNode(string, string, string, int);
     void InsertAfter(PlaylistNode* &);
     void SetNext(PlaylistNode*);
     string GetID() const;
     string GetSongName() const;
     string GetArtistName() const;
     int GetSongLength() const;
     PlaylistNode* GetNext() const;
     void PrintPlaylistNode() const;
     
    private:
     string uniqueID;
     string songName;
     string artistName;
     int songLength;
     PlaylistNode* nextNodePtr;

    
};
#endif