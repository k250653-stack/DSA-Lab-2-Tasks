#include <iostream>
using namespace std;

class PlaylistManager {
private:
    int** customPlaylists;
    int* playlistCapacities;
    int playlistCount;

    void release() {
        for (int i = 0; i < playlistCount; i++) {
            delete[] customPlaylists[i];
        }
        delete[] customPlaylists;
        delete[] playlistCapacities;
        customPlaylists = nullptr;
        playlistCapacities = nullptr;
        playlistCount = 0;
    }

    void deepCopyFrom(const PlaylistManager& other) {
        playlistCount = other.playlistCount;
        playlistCapacities = new int[playlistCount];
        customPlaylists = new int*[playlistCount];
        for (int i = 0; i < playlistCount; i++) {
            playlistCapacities[i] = other.playlistCapacities[i];
            customPlaylists[i] = new int[playlistCapacities[i]];
            for (int j = 0; j < playlistCapacities[i]; j++) {
                customPlaylists[i][j] = other.customPlaylists[i][j];
            }
        }
    }

    bool validPlaylist(int p) const {
        return p >= 0 && p < playlistCount;
    }

    bool validTrack(int p, int t) const {
        return validPlaylist(p) && t >= 0 && t < playlistCapacities[p];
    }

public:
    PlaylistManager(int playlists, const int sizes[]) : playlistCount(playlists) {
        playlistCapacities = new int[playlistCount];
        customPlaylists = new int*[playlistCount];
        for (int i = 0; i < playlistCount; i++) {
            playlistCapacities[i] = sizes[i];
            customPlaylists[i] = new int[sizes[i]];
            for (int j = 0; j < sizes[i]; j++) {
                customPlaylists[i][j] = 0;
            }
        }
    }

    PlaylistManager(const PlaylistManager& other) {
        deepCopyFrom(other);
    }

    PlaylistManager& operator=(const PlaylistManager& other) {
        if (this != &other) {
            release();
            deepCopyFrom(other);
        }
        return *this;
    }

    ~PlaylistManager() {
        release();
    }

    bool setTrack(int p, int t, int trackId) {
        if (!validTrack(p, t)) {
            cout << "Error: Invalid playlist " << p << " / track " << t << "." << endl;
            return false;
        }
        customPlaylists[p][t] = trackId;
        return true;
    }

    bool addTrack(int p, int trackId) {
        if (!validPlaylist(p)) {
            cout << "Error: Invalid playlist " << p << "." << endl;
            return false;
        }
        int oldSize = playlistCapacities[p];
        int* resized = new int[oldSize + 1];
        for (int i = 0; i < oldSize; i++) {
            resized[i] = customPlaylists[p][i];
        }
        resized[oldSize] = trackId;
        delete[] customPlaylists[p];
        customPlaylists[p] = resized;
        playlistCapacities[p] = oldSize + 1;
        return true;
    }

    bool playSong(int p, int t) const {
        if (!validPlaylist(p)) {
            cout << "Error: Playlist " << p << " does not exist." << endl;
            return false;
        }
        if (t < 0 || t >= playlistCapacities[p]) {
            cout << "Error: Track " << t << " is out of range for playlist " << p
                 << " (size " << playlistCapacities[p] << ")." << endl;
            return false;
        }
        cout << "Playing playlist " << p << ", track " << t << ": ID " << customPlaylists[p][t] << endl;
        return true;
    }

    void display(const char* label) const {
        cout << label << endl;
        for (int i = 0; i < playlistCount; i++) {
            cout << "  Playlist " << i << " [" << playlistCapacities[i] << " tracks]: ";
            for (int j = 0; j < playlistCapacities[i]; j++) {
                cout << customPlaylists[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int sizes[3] = {3, 2, 4};
    PlaylistManager original(3, sizes);

    int id = 100;
    for (int p = 0; p < 3; p++) {
        for (int t = 0; t < sizes[p]; t++) {
            original.setTrack(p, t, id++);
        }
    }

    original.display("Original database:");

    PlaylistManager archive(original);
    archive.addTrack(1, 999);
    archive.setTrack(0, 0, 777);

    cout << "\nAfter modifying the archive copy:" << endl;
    original.display("Original database:");
    archive.display("Archive database:");

    cout << "\nBounds checks:" << endl;
    original.playSong(2, 3);
    original.playSong(2, 4);
    original.playSong(5, 0);
    archive.playSong(1, 2);

    PlaylistManager another(original);
    another = archive;
    another.display("\nAssigned copy:");

    return 0;
}
