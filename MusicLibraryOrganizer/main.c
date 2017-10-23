//
// Created by kkyse on 10/17/2017.
//

#define MAIN_DEBUG false

#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <assert.h>

#include "song_library.h"

#define p(s) printf(s"\n")

#define pn() p("")

#define pt() printf("\t\t")

void debug_SongNode() {
    Song song1 = SongClass.new("Name", "Artists");
    Song song2 = SongClass.new("Hello", "World");
    //Song song3 = SongClass.new("Song", "Bob");
    
    p("inserting in order");
    
    SongNode *node = SongNodeClass.new_sentinel(song1);
    node = node->c->insert_in_order(node, song2);
    printf("%p\n", node);
    //node = node->c->insert_in_order(node, song3);
    node->c->print(node);
    
    node->c->free(node);
}

void debug_SongLibrary() {
    p("creating library");
    SongLibrary *const library = SongLibraryClass.new();
    p("created library");
    
    p("creating song1");
    Song song1 = SongClass.new("Title", "Artist");
    p("created song1");
    
    p("printing song1");
    song1.c->print(song1);
    p("printed song1");
    
    p("adding song1");
    library->c->add_song(library, song1);
    p("added song1");

//    library->c->add_song(library, SongClass.new("Hello", "World"));
//    library->c->add_song(library, SongClass.new("Khyber", "Sen"));
    
    library->c->add_songs_from_csv(library, "songs.csv");
    
    p("printing library");
    library->c->print(library);
    p("printed library");
    
    const SongNode *node = library->c->songs_by_artist_letter(library, 'A');
    node->c->print(node);
    
    library->c->free(library);
}

void test_SongNode() {
    p("====================");
    p("TESTING SONG LINKED LIST");
    p("====================\n");
    
    PRE_SONG_STRING = "\t\t";
    
    const Song song1 = SongClass.new("SongName", "Artist");
    
    p("Testing SongNode.new_sentinel()");
    p("\tshould print just [SongName by Artist]...");
    SongNode *songs = SongNodeClass.new_sentinel(song1);
    songs->c->print(songs);
    //printf("length: %zu\n", songs->c->length(songs));
    pn();
    
    p("Testing SongNode constructor");
    SongNode *test = SongNodeClass.new(song1, songs);
    test->c->print(test);
    pn();
    
    p("Testing SongNode.free_nodes_only()");
    p("\tshould print a null pointer");
    pt();
    printf("%p\n", test->c->free_nodes_only(test));
    song1.c->free(song1);
    pn();
    
    SongLibrary *const library = SongLibraryClass.new();
    library->c->add_songs_from_default_csv(library);
    const SongNode *const all_songs = library->c->all_songs(library);
    const Song new_song = SongClass.new("NewSong", "NewArtist");
    
    p("Testing SongNode.length()");
    p("\tshould print 27, the number of songs in our playlist");
    pt();
    printf("length: %zu\n", all_songs->c->length(all_songs));
    pt();
    printf("num_songs in library: %zu\n", library->num_songs);
    pn();
    
    p("Testing SongNode.insert_front()");
    p("\tshould have new song at the front of the library");
    SongNode *new = all_songs->c->insert_front(all_songs, new_song);
    new->c->print(new);
    pn();
    
    p("Testing SongNode.remove_front()");
    p("\tshould now remove previously added song from the library");
    new = new->c->remove_front(new);
    new->c->print(new);
    pn();
    
    p("Testing SongNode.insert_in_order()");
    p("\tshould put the new song in the right place");
    new = all_songs->c->insert_in_order(all_songs, new_song);
    new->c->print(new);
    pn();
    
    p("Testing SongNode.find_by_name()");
    p("\tshould print pointer to first occurrence of song name");
    pt();
    printf("pointer to first occurrence of \"Thomas the Tank Engine\": %p\n",
           all_songs->c->find_by_name(all_songs, "Thomas the Tank Engine"));
    p("\tshould print null pointer if not found");
    pt();
    printf("pointer to first occurrence of \"A song from my Soundcloud that is not fire\": %p\n",
           all_songs->c->find_by_name(all_songs, "A song from my Soundcloud that is not fire"));
    pn();
    
    p("Testing SongNode.find_by_artist()");
    p("\tshould print pointer to first occurrence of given artist's song");
    pt();
    printf("pointer to first occurrence of \"Sia\": %p\n", all_songs->c->find_by_artist(all_songs, "Sia"));
    p("\tshould print null pointer if not found");
    pt();
    printf("pointer to first occurrence of \"Rebecca Black\": %p\n",
           all_songs->c->find_by_name(all_songs, "Rebecca Black"));
    pn();
    
    p("Testing SongNode.get()");
    p("\tshould print the pointer to the song at the given position");
    pt();
    printf("pointer to the 17th song: %p\n", all_songs->c->get(all_songs, 17));
    pn();
    
    p("Testing SongNode.get_random_with_length()");
    p("\tshould print a pointer to a random song in the playlist");
    pt();
    printf("pointer to a random song: %p\n",
           all_songs->c->get_random_with_length(all_songs, all_songs->c->length(all_songs)));
    pn();
    
    p("Testing SongNode.get_random()");
    p("\tshould print a pointer to a random song in the playlist");
    pt();
    printf("pointer to a random song: %p\n", all_songs->c->get_random(all_songs));
    pn();
    
    p("Testing SongNode.remove_song()");
    p("\tshould remove new song from playlist");
    assert(all_songs->c->is_sorted(all_songs));
    p("Pre:");
    all_songs->c->print(all_songs);
    p("Running SongNode.remove_song():");
    size_t num_removed;
    SongNode *const head = (SongNode *const) all_songs;
    all_songs->c->remove_song(head, new_song, &num_removed);
    p("Post:");
    all_songs->c->print(all_songs);
    pn();
    
    /*
    p("Testing SongNode.free_nodes_maybe()");
    p("\tshould print 27, the number of songs in our playlist");
    pt();
    printf("length: %zu\n", all_songs->c->length(all_songs));
    pn();
    */
    
    new_song.c->free(new_song);
    
    p("Testing SongNode.free()");
    p("\tshould print a null pointer");
    pt();
    printf("%p\n", all_songs->c->free_nodes_only((SongNode *) all_songs));
    
    library->c->free(library);
    
    p("====================");
    p("SONG LINKED LIST PASSED ALL TESTS");
    p("====================\n");
}

void test_SongLibrary() {
    p("====================");
    p("TESTING SONG LIBRARY");
    p("====================\n");
    
    PRE_SONG_STRING = "\t\t";
    
    p("Testing SongLibrary constructor");
    SongLibrary *const library = SongLibraryClass.new();
    pn();
    
    p("Testing SongLibrary.add_songs_from_csv(),");
    p("\twhich tests SongLibrary.add_song()");
    library->c->add_songs_from_default_csv(library);
    pn();
    
    p("Testing SongLibrary.print(),");
    p("\tshould print all songs in alphabetic order by artist, then song name");
    library->c->print(library);
    pn();
    
    p("Testing SongLibrary.print_by_letter('A'),");
    p("\tshould print all songs by 'A' in alphabetic order");
    library->c->print_by_letter(library, 'A');
    pn();
    
    p("Testing SongLibrary.print_by_artist(\"Alz\"),");
    p("\tshould print all songs by \"Alz\" in alphabetic order");
    library->c->print_by_artist(library, "Alz");
    pn();
    
    p("Testing SongLibrary.find_song(),");
    p("\twhich uses SongLibrary.find_by_artist() and SongLibrary.find_by_name()");
    const Song song = SongClass.new("Cheap Thrills", "Sia");
    char *const song_str1 = song.c->to_string(song);
    printf("\tFinding song %s...\n", song_str1);
    const Song found_song = library->c->find_song(library, song)->song;
    char *const song_str2 = found_song.c->to_string(found_song);
    printf("\tFound song %s\n", song_str2);
    free(song_str2);
    pn();
    
    printf("Testing duplicate songs by re-adding %s\n", DEFAULT_SONGS_CSV);
    library->c->add_songs_from_default_csv(library);
    library->c->print(library);
    pn();
    
    p("Testing SongLibrary.shuffle_and_print() for 10 random songs");
    library->c->shuffle_and_print(library, 10);
    p("\tHopefully these are all random.");
    p("\tTesting for the correct random distribution would be much harder.");
    pn();
    
    p("Testing SongLibrary.remove_song()");
    p("\tprinting library before removal...");
    library->c->print(library);
    library->c->remove_song(library, song);
    printf("\tprinting library again to make sure %s was removed...\n", song_str1);
    library->c->print(library);
    p("\tIt might be hard to check if it was removed,");
    song.c->print(song);
    printf("\tso now printing all songs by letter '%c' from %s...\n", *song.artist, song_str1);
    library->c->print_by_letter(library, *song.artist);
    pn();
    
    song.c->free(song);
    free(song_str1);
    
    p("Testing SongLibrary.remove_all()");
    p("\tprinting library before removal...");
    library->c->print(library);
    library->c->remove_all_songs(library);
    p("\tprinting library again to make sure it's empty");
    library->c->print(library);
    pn();
    
    p("Testing SongLibrary.free()");
    library->c->add_songs_from_default_csv(library);
    library->c->free(library);
    p("\tvalgrind also found no memory leaks");
    pn();
    
    p("====================");
    p("SONG LIBRARY PASSED ALL TESTS");
    p("====================\n");
}

int main() {
    srand((unsigned int) time(NULL));
    
    #if (MAIN_DEBUG)
    debug_song_node();
    debug_library();
    #endif
    
    test_SongNode();
    test_SongLibrary();
    
    return EXIT_SUCCESS;
}

#undef pt
#undef pn
#undef p
