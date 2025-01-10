#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;

void showPlaylist(Playlist* playlist);
void deleteSong(Playlist* playlist);
void addSong(Playlist* playlist);
void playSong(Song* song);
void freeSong(Song* song);
void freePlaylist(Playlist* playlist);
void printMainMenu();
void printPlaylistMenu();
void sortPlaylist(Playlist* playlist);
Playlist* createPlaylist();
void clearInputBuffer();

void showPlaylist(Playlist* playlist) 
{
    int choicePlay;
    for (int i = 0; i < playlist->songsNum; i++) 
    {
        printf("%d. Title: %s\n", i + 1, playlist->songs[i]->title);
        printf("   Artist: %s\n", playlist->songs[i]->artist);
        printf("   Released: %d\n", playlist->songs[i]->year);
        printf("   Streams: %d\n", playlist->songs[i]->streams);
        printf("\n");
    }
    do{
        printf("choose a song to play, or 0 to quit:\n");
        scanf("%d", &choicePlay);
        if(choicePlay == 0)
            break;
        else if(choicePlay > 0 && choicePlay <= playlist->songsNum)
        {
            playSong(playlist->songs[choicePlay-1]);   
        }
        else
        {
            printf("Invalid option\n");
        }
    } while(choicePlay != 0);
}

void deleteSong(Playlist* playlist)
{
    int songIndex;
    printf("Choose a song to delete (1 to %d): ", playlist->songsNum);
    scanf("%d", &songIndex);
    songIndex--;
    
    if (songIndex >= 0 && songIndex < playlist->songsNum)
    {
        freeSong(playlist->songs[songIndex]);
        for (int i = songIndex; i < playlist->songsNum - 1; i++) 
        {
            playlist->songs[i] = playlist->songs[i + 1];
        }
        playlist->songsNum--;
        printf("Song deleted successfully.\n");
    } else {
        printf("Invalid option\n");
    }
}

void addSong(Playlist* playlist)
{
    int size,index;
    char ch;
    Song* newSong = (Song*)malloc(sizeof(Song));
    newSong->streams = 0;
    printf("Enter song's details\n");
    printf("Title: \n");
    index = 0;
    size = 2;
    clearInputBuffer();
    newSong->title = (char*)malloc(size * sizeof(char));
    while(1)
    {
        if (scanf("%c", &ch) != 1) 
        {
            break;
        }
        if (ch == '\n') 
        {
            break;
        }
        if (index >= size - 1)
        {
            size += 2;
            newSong->title = (char*)realloc(newSong->title, size * sizeof(char));
        }
        size++;
        newSong->title = (char*)realloc(newSong->title ,size * sizeof(char));
        newSong->title[index] = ch;
        index++;
    }

    printf("Artist: \n");
    index = 0;
    size = 2;
    newSong->artist = (char*)malloc(size * sizeof(char));
    while(1)
    {
        if (scanf("%c", &ch) != 1) 
        {
            break;
        }
        if (ch == '\n') 
        {
            break;
        }
        if (index >= size - 1)
        {
            size += 2; 
            newSong->artist = (char*)realloc(newSong->artist, size * sizeof(char));
        }
        size++;
        newSong->artist = (char*)realloc(newSong->artist ,size * sizeof(char));
        newSong->artist[index] = ch;
        index++;
    }

    printf("Year of release: \n");
    scanf("%d", &newSong->year);

    clearInputBuffer();
    printf("Lyrics: \n");
    index = 0;
    size = 2;
    newSong->lyrics = (char*)malloc(size * sizeof(char));
    while(1)
    {
        if (scanf("%c", &ch) != 1) 
        {
            break;
        }
        if (ch == '\n') 
        {
            break;
        }
        if (index >= size - 1)
        {
            size += 2; 
            newSong->lyrics = (char*)realloc(newSong->lyrics, size * sizeof(char));
        }
        size++;
        newSong->lyrics = (char*)realloc(newSong->lyrics ,size * sizeof(char));
        newSong->lyrics[index] = ch;
        index++;
    }

    playlist->songs = (Song**)realloc(playlist->songs, sizeof(Song*) * (playlist->songsNum + 1));
    playlist->songs[playlist->songsNum] = newSong;
    playlist->songsNum++;
}

void playSong(Song* song)
{
    printf("Now playing %s:\n", song->title);
    printf("$ %s $\n", song->lyrics);
    song->streams++;
}



void freeSong(Song* song)
{
    if(song)
    {
        free(song->title);
        free(song->artist);
        free(song->lyrics);
        free(song);
    }
}

void freePlaylist(Playlist* playlist) 
{
    if (playlist) 
    {
        for (int i = 0; i < playlist->songsNum; i++)
        {
            freeSong(playlist->songs[i]);
        }
        free(playlist->songs);
        free(playlist->name);
        free(playlist);
    }
}

void printMainMenu()
{
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
}

void printPlaylistMenu() 
{
    printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. Sort\n\t5. Play\n\t6. Back\n");
}
void sortPlaylist(Playlist* playlist)
{
    int choiceSort;
    Song* temp;
    printf("choose:\n");
    printf("1. sort by year\n");
    printf("2. sort by streams - ascending order\n");
    printf("3. sort by streams - descending order\n");
    printf("4. sort alphabetically\n");
    scanf("%d",&choiceSort);
    switch(choiceSort)
    {
        //I decided to sort using the bubble sort method
        case 1:
            for(int i = 0;i < playlist->songsNum-1;i++)
            {
                for(int j = 0;j < playlist->songsNum-i-1; j++)
                {
                    if(playlist->songs[j]->year > playlist->songs[j+1]->year)
                    {
                        temp = playlist->songs[j];
                        playlist->songs[j]= playlist->songs[j+1];
                        playlist->songs[j+1] = temp;
                    }
                }
            }
            break;
        case 2:
            for(int i = 0;i < playlist->songsNum-1;i++)
            {
                for(int j = 0;j < playlist->songsNum-i-1; j++)
                {
                    if(playlist->songs[j]->streams > playlist->songs[j+1]->streams)
                    {
                        temp = playlist->songs[j];
                        playlist->songs[j]= playlist->songs[j+1];
                        playlist->songs[j+1] = temp;
                    }
                }
            }    
            break;
        case 3:
            for(int i = 0;i < playlist->songsNum-1;i++)
            {
                for(int j = 0;j < playlist->songsNum-i-1; j++)
                {
                    if(playlist->songs[j]->streams > playlist->songs[j+1]->streams)
                    {
                        temp = playlist->songs[j];
                        playlist->songs[j]= playlist->songs[j+1];
                        playlist->songs[j+1] = temp;
                    }
                }
            }   
            break;
        default:
            for(int i = 0;i < playlist->songsNum-1;i++)
            {   
                for(int j = 0;j < playlist->songsNum-i-1; j++)
                {
                    if(strcmp(playlist->songs[j]->title, playlist->songs[j + 1]->title) > 0)
                    {
                        temp = playlist->songs[j];
                        playlist->songs[j]= playlist->songs[j+1];
                        playlist->songs[j+1] = temp;
                    }
                }
            }    
            break;
    }
    printf("sorted\n");
}

Playlist* createPlaylist()
{
    int size = 2,index = 0;
    char ch;
    Playlist* newPlaylist = (Playlist*)malloc(sizeof(Playlist));
    newPlaylist->name = (char*)malloc(size * sizeof(char));
    printf("Enter playlist's name:\n");
    while(1)
    {
        if (scanf("%c", &ch) != 1) 
        {
            break;
        }
        if (ch == '\n') 
        {
            break;
        }
        if (index >= size - 1)
        {
            size += 2; 
            newPlaylist->name = (char*)realloc(newPlaylist->name, size * sizeof(char));
        }
        size++;
        newPlaylist->name = (char*)realloc(newPlaylist->name ,size * sizeof(char));
        newPlaylist->name[index] = ch;
        index++;
    }
    newPlaylist->name[index] = '\0';
    newPlaylist->songs = NULL;
    newPlaylist->songsNum = 0;
    return newPlaylist;
}

void clearInputBuffer()
{
    scanf("%*[^\n]");
    scanf("%*c");
}

int main()
{
    Playlist** playlists = NULL;
    int choiceMain,choiceCase1,choiceCase3,choicePlaylist,playlistCount=0;
    do{
        printMainMenu();
        scanf("%d",&choiceMain);
        clearInputBuffer();
        switch(choiceMain)
        {
            case 4:
                for(int i = 0;i < playlistCount; i++)
                {
                    freePlaylist(playlists[i]);
                }
                free(playlists);
                break;
            case 1:
                do{
                    printf("Choose a playlist:\n");
                   for(int i = 1; i <= playlistCount+1; i++)
                    {
                        if(i == playlistCount+1)
                            printf("\t %d. Back to main menu\n",i);
                        else
                            printf("\t %d. %s\n",i,playlists[i-1]->name);
                    }
                    scanf("%d",&choiceCase1);
                    if(choiceCase1 == playlistCount+1)
                    {
                        clearInputBuffer();
                        break;
                    }
                    else if(choiceCase1 > 0 && choiceCase1 <= playlistCount)
                    {
                        Playlist* selectedPlaylist = playlists[choiceCase1 - 1];
                        do{
                            printPlaylistMenu();
                            scanf("%d", &choicePlaylist);
                            switch(choicePlaylist)
                            {
                                case 6:
                                    break;
                                case 1:
                                    showPlaylist(selectedPlaylist);
                                    break;
                                case 2:
                                    addSong(selectedPlaylist);
                                    break;
                                case 3:
                                    deleteSong(selectedPlaylist);
                                    break;
                                case 4:
                                    sortPlaylist(selectedPlaylist);
                                    break;
                                case 5:
                                if (selectedPlaylist->songsNum > 0) 
                                {
                                    for (int i = 0; i < selectedPlaylist->songsNum; i++)
                                    {
                                        playSong(selectedPlaylist->songs[i]);
                                        printf("\n");
                                    }
                                }
                                    break;
                            }
                        } while(choicePlaylist != 6);
                    }
                    clearInputBuffer();
                }while(choiceCase1 != playlistCount+1);
                break;
            case 2:
                playlists = (Playlist**)realloc(playlists, sizeof(Playlist*) * (playlistCount + 1));
                playlists[playlistCount] = createPlaylist();
                playlistCount++;
                break;
            case 3:
                printf("Choose a playlist:\n");
                for(int i = 1; i <= playlistCount+1; i++)
                {
                    if(i == playlistCount+1)
                        printf("\t %d. Back to main menu\n",i);
                    else
                        printf("\t %d. %s\n",i,playlists[i-1]->name);
                }
                scanf("%d",&choiceCase3);
                if(choiceCase3 == playlistCount+1)
                {
                    clearInputBuffer();
                    break;
                }
                else if(choiceCase3 > 0 && choiceCase1 <= playlistCount)
                {
                    if (choiceCase3 > 0 && choiceCase3 <= playlistCount)
                    {
                        freePlaylist(playlists[choiceCase3 - 1]);
                        for (int i = choiceCase3 - 1; i < playlistCount - 1; i++)
                        {
                            playlists[i] = playlists[i + 1];
                        }
                        (playlistCount)--;
                    }
                }
                clearInputBuffer();
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(choiceMain != 4);
    printf("Goodbye!\n");  
    return 0;
}
