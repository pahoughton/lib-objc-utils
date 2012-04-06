/**
 File:		SMKMp4Support.c
 Project:      SMKCommon
 Desc:
 
 
 
 Notes:
 
 Author(s):   Paul Houghton <Paul.Houghton@SecureMediaKeepers.com>
 Created:     120330
 
 Copyright (c) 2012 Secure Media Keepers. All rights reserved.
 
 Revision History: (See ChangeLog for details)
 
 $Author$
 $Date$
 $Revision$
 $Name$
 $State$
 
 $Id$
 
 **/

#include "SMKMp4Support.h"
#include <stdio.h>
#include <string.h>

const unsigned char PNGCookie[] = "\211PNG\r\n";
const unsigned char JPGCookie[] = "\377\330\377\340";

const Mp4_MediaKind_t Mp4_MediaKinds[] = {
    {MP4_MK_Music,       "Music"},
    {MP4_MK_Audiobook,   "Audiobook"},
    {MP4_MK_MusicVideo,  "Music Video"},
    {MP4_MK_Movie,       "Movie"},
    {MP4_MK_TV,          "TV Show"},
    {MP4_MK_Booklet,     "Booklet"},
    {MP4_MK_Ringtone,    "Ringtone"},  
    {0, NULL},    
};

const Mp4_ContentRating_t Mp4_ContentRatings[] = {
    {0, "None"},
    {2, "Clean"},
    {4, "Explicit"},
    {0, NULL},

};

const Mp4_ITMF_rating_info Mp4_ITMF_Ratings[] = {
    {"--", "-- United States"},
    {"mpaa|NR|000|",      "NR"},          // 1
    {"mpaa|G|100|",       "G"},
    {"mpaa|PG|200|",      "PG"},
    {"mpaa|PG-13|300|",   "PG-13"},
    {"mpaa|R|400|",       "R" },
    {"mpaa|NC-17|500|",   "NC-17"},
    {"mpaa|Unrated|???|", "Unrated"},
    {"--", ""},
    {"us-tv|TV-Y|100|",    "TV-Y"},            // 9
    {"us-tv|TV-Y7|200|",   "TV-Y7"},
    {"us-tv|TV-G|300|",    "TV-G"},
    {"us-tv|TV-PG|400|",   "TV-PG"},
    {"us-tv|TV-14|500|",   "TV-14"},
    {"us-tv|TV-MA|600|",   "TV-MA"},
    {"us-tv|Unrated|???|", "Unrated"},
    {"--", "-- United Kingdom"},
    {"uk-movie|NR|000|",   "Not Rated"},      // 17
    {"uk-movie|U|100|",    "U"},
    {"uk-movie|Uc|150|",   "Uc"},
    {"uk-movie|PG|200|",   "PG"},
    {"uk-movie|12|300|",   "12"},
    {"uk-movie|12A|325|",  "12A"},
    {"uk-movie|15|350|",   "15"},
    {"uk-movie|18|400|",   "18"},
    {"uk-movie|R18|600|",  "R18"},
    {"uk-movie|E|0|",      "Exempt" },
    {"uk-movie|Unrated|???|", "Unrated"},
    {"--", ""},
    {"uk-tv|Caution|500|", "Caution"},      // 29
    {"--", "-- Germany"},
    {"de-movie|ab 0 Jahren|75|", "ab 0 Jahren"},		// 31
    {"de-movie|ab 6 Jahren|100|", "ab 6 Jahren"},
    {"de-movie|ab 12 Jahren|200|", "ab 12 Jahren"},
    {"de-movie|ab 16 Jahren|500|", "ab 16 Jahren"},
    {"de-movie|ab 18 Jahren|600|", "ab 18 Jahren"},
    {"--", ""},
    {"de-tv|ab 0 Jahren|75|", "ab 0 Jahren"},		// 37
    {"de-tv|ab 6 Jahren|100|", "ab 6 Jahren"},
    {"de-tv|ab 12 Jahren|200|", "ab 12 Jahren"},
    {"de-tv|ab 16 Jahren|500|", "ab 16 Jahren"},
    {"de-tv|ab 18 Jahren|600|", "ab 18 Jahren"},
    {"--", "-- Australia"},
    {"au-movie|G|100|", "G"},               // 43
    {"au-movie|PG|200|", "PG"},
    {"au-movie|M|350|", "M"},
    {"au-movie|MA15+|375|", "MA 15+"},
    {"au-movie|R18+|400|", "R18+"},
    {"--", ""},
    {"au-tv|P|100|", "P"},                  // 49
    {"au-tv|C|200|", "C"},
    {"au-tv|G|300|", "G"},
    {"au-tv|PG|400|", "PG"},
    {"au-tv|M|500|", "M"},
    {"au-tv|MA15+|550|", "MA 15+"},
    {"au-tv|AV15+|575|", "AV 15+"},
    {"au-tv|R18+|600|", "R18+"},
    {"--", "-- France"},
    {"fr-movie|Tout Public|100|", "Tout Public"},     // 58
    {"fr-movie|-10|100|", "-10"},
    {"fr-movie|-12|300|", "-12"},
    {"fr-movie|-16|375|", "-16"},
    {"fr-movie|-18|400|", "-18"},
    {"fr-movie|Unrated|???|", "Unrated"},
    {"--", ""},
    {"fr-tv|-10|100|", "-10"},              // 65
    {"fr-tv|-12|200|", "-12"},
    {"fr-tv|-16|500|", "-16"},
    {"fr-tv|-18|600|", "-18"},
    {"--", "-- Canada"},
    {"ca-movie|G|100|", "G"},               // 70
    {"ca-movie|PG|200|", "PG"},
    {"ca-movie|14A|300|", "14A"},
    {"ca-movie|18A|350|", "18A"},
    {"ca-movie|R|400|", "R"},
    {"ca-movie|A|500|", "A"},
    {"--", ""},
    {"ca-tv|TV-E|000|", "TV-E"},              // 77
    {"ca-tv|TV-C|50|", "TV-C"},
    {"ca-tv|TV-C8|75|", "TV-C8"},
    {"ca-tv|TV-G|100|", "TV-G"},
    {"ca-tv|TV-PG|200|", "TV-PG"},
    {"ca-tv|TV-14+|300|", "TV-14+"},
    {"ca-tv|TV-18+|350|", "TV-18+"},
    {"ca-tv|TV-21+|500|", "TV-21+"},
    {"--", ""},
    {"--", "Unknown"},                      // 85
    {NULL, NULL},    
};

const Mp4_GenreType_t Mp4_GenreTypes[] = {
    {0,   "undefined",         "undefined" },   
    
    {1,   "blues",             "Blues" },
    {2,   "classicrock",       "Classic Rock" },
    {3,   "country",           "Country" },
    {4,   "dance",             "Dance" },
    {5,   "disco",             "Disco" },
    {6,   "funk",              "Funk" },
    {7,   "grunge",            "Grunge" },
    {8,   "hiphop",            "Hop-Hop" },
    {9,   "jazz",              "Jazz" },
    {10,  "metal",             "Metal" },
    {11,  "newage",            "New Age" },
    {12,  "oldies",            "Oldies" },
    {13,  "other",             "Other" },
    {14,  "pop",               "Pop" },
    {15,  "rand_b",            "R&B" },
    {16,  "rap",               "Rap" },
    {17,  "reggae",            "Reggae" },
    {18,  "rock",              "Rock" },
    {19,  "techno",            "Techno" },
    {20,  "industrial",        "Industrial" },
    {21,  "alternative",       "Alternative" },
    {22,  "ska",               "Ska" },
    {23,  "deathmetal",        "Death Metal" },
    {24,  "pranks",            "Pranks" },
    {25,  "soundtrack",        "Soundtrack" },
    {26,  "eurotechno",        "Euro-Techno" },
    {27,  "ambient",           "Ambient" },
    {28,  "triphop",           "Trip-Hop" },
    {29,  "vocal",             "Vocal" },
    {30,  "jazzfunk",          "Jazz+Funk" },
    {31,  "fusion",            "Fusion" },
    {32,  "trance",            "Trance" },
    {33,  "classical",         "Classical" },
    {34,  "instrumental",      "Instrumental" },
    {35,  "acid",              "Acid" },
    {36,  "house",             "House" },
    {37,  "game",              "Game" },
    {38,  "soundclip",         "Sound Clip" },
    {39,  "gospel",            "Gospel" },
    {40,  "noise",             "Noise" },
    {41,  "alternrock",        "AlternRock" },
    {42,  "bass",              "Bass" },
    {43,  "soul",              "Soul" },
    {44,  "punk",              "Punk" },
    {45,  "space",             "Space" },
    {46,  "meditative",        "Meditative" },
    {47,  "instrumentalpop",   "Instrumental Pop" },
    {48,  "instrumentalrock",  "Instrumental Rock" },
    {49,  "ethnic",            "Ethnic" },
    {50,  "gothic",            "Gothic" },
    {51,  "darkwave",          "Darkwave" },
    {52,  "technoindustrial",  "Techno-Industrial" },
    {53,  "electronic",        "Electronic" },
    {54,  "popfolk",           "Pop-Folk" },
    {55,  "eurodance",         "Eurodance" },
    {56,  "dream",             "Dream" },
    {57,  "southernrock",      "Southern Rock" },
    {58,  "comedy",            "Comedy" },
    {59,  "cult",              "Cult" },
    {60,  "gangsta",           "Gangsta" },
    {61,  "top40",             "Top 40" },
    {62,  "christianrap",      "Christian Rap" },
    {63,  "popfunk",           "Pop/Funk" },
    {64,  "jungle",            "Jungle" },
    {65,  "nativeamerican",    "Native American" },
    {66,  "cabaret",           "Cabaret" },
    {67,  "newwave",           "New Wave" },
    {68,  "psychedelic",       "Psychedelic" },
    {69,  "rave",              "Rave" },
    {70,  "showtunes",         "Showtunes" },
    {71,  "trailer",           "Trailer" },
    {72,  "lofi",              "Lo-Fi" },
    {73,  "tribal",            "Tribal" },
    {74,  "acidpunk",          "Acid Punk" },
    {75,  "acidjazz",          "Acid Jazz" },
    {76,  "polka",             "Polka" },
    {77,  "retro",             "Retro" },
    {78,  "musical",           "Musical" },
    {79,  "rockand_roll",      "Rock & Roll" },
    
    {80,  "hardrock",          "Hard Rock" },
    {81,  "folk",              "Folk" },
    {82,  "folkrock",          "Folk-Rock" },
    {83,  "nationalfolk",      "National Folk" },
    {84,  "swing",             "Swing" },
    {85,  "fastfusion",        "Fast Fusion" },
    {86,  "bebob",             "Bebob" },
    {87,  "latin",             "Latin" },
    {88,  "revival",           "Revival" },
    {89,  "celtic",            "Celtic" },
    {90,  "bluegrass",         "Bluegrass" },
    {91,  "avantgarde",        "Avantgarde" },
    {92,  "gothicrock",        "Gothic Rock" },
    {93,  "progressiverock",   "Progresive Rock" },
    {94,  "psychedelicrock",   "Psychedelic Rock" },
    {95,  "symphonicrock",     "SYMPHONIC_ROCK" },
    {96,  "slowrock",          "Slow Rock" },
    {97,  "bigband",           "Big Band" },
    {98,  "chorus",            "Chorus" },
    {99,  "easylistening",     "Easy Listening" },
    {100, "acoustic",          "Acoustic" },
    {101, "humour",            "Humor" },
    {102, "speech",            "Speech" },
    {103, "chanson",           "Chason" },
    {104, "opera",             "Opera" },
    {105, "chambermusic",      "Chamber Music" },
    {106, "sonata",            "Sonata" },
    {107, "symphony",          "Symphony" },
    {108, "bootybass",         "Booty Bass" },
    {109, "primus",            "Primus" },
    {110, "porngroove",        "Porn Groove" },
    {111, "satire",            "Satire" },
    {112, "slowjam",           "Slow Jam" },
    {113, "club",              "Club" },
    {114, "tango",             "Tango" },
    {115, "samba",             "Samba" },
    {116, "folklore",          "Folklore" },
    {117, "ballad",            "Ballad" },
    {118, "powerballad",       "Power Ballad" },
    {119, "rhythmicsoul",      "Rhythmic Soul" },
    {120, "freestyle",         "Freestyle" },
    {121, "duet",              "Duet" },
    {122, "punkrock",          "Punk Rock" },
    {123, "drumsolo",          "Drum Solo" },
    {124, "acapella",          "A capella" },
    {125, "eurohouse",         "Euro-House" },
    {126, "dancehall",         "Dance Hall" },
    {255, "none",              "none" },
    
};

MP4TagArtworkType Mp4ImageDataArtType( const void * imgData )
{
    MP4TagArtworkType artType = MP4_ART_UNDEFINED;
    
    if( memcmp( imgData, PNGCookie, sizeof(PNGCookie) - 1 ) == 0 ) {
        artType = MP4_ART_PNG;
    } else if( memcmp( imgData, JPGCookie, sizeof(JPGCookie) - 1 ) == 0 ) {
        artType = MP4_ART_PNG;
    }          

    return artType;
}

Mp4_ITMF_rating_type Mp4RatingTypeFromEngName( const char * engName ) 
{
    Mp4_ITMF_rating_type itmf = 0;
    for( ; Mp4_ITMF_Ratings[ itmf ].rating != 0; ++ itmf ) {
        if( strcmp(engName, Mp4_ITMF_Ratings[ itmf ].english_name) == 0 ) {
            return itmf;
        }
    }
    return R_UNKNOWN;
}
Mp4_ITMF_rating_type Mp4RatingTypeFromITMFRating( const char * rating ) 
{
    Mp4_ITMF_rating_type itmf = 0;
    for( ; Mp4_ITMF_Ratings[ itmf ].rating != 0; ++ itmf ) {
        if( strcmp(rating, Mp4_ITMF_Ratings[ itmf ].rating) == 0 ) {
            return itmf;
        }
    }
    return R_UNKNOWN;
}


const char * Mp4ITMFRatingFromRatingType( Mp4_ITMF_rating_type type ) 
{
    if( type < R_UNKNOWN ) {
        return Mp4_ITMF_Ratings[ type ].rating;
    }
    return Mp4_ITMF_Ratings[ R_UNKNOWN ].rating;
}
const char * Mp4EngNameFromRatingType( Mp4_ITMF_rating_type type ) 
{
    if( type < R_UNKNOWN ) {
        return Mp4_ITMF_Ratings[ type ].english_name;
    }
    return Mp4_ITMF_Ratings[ R_UNKNOWN ].english_name;
}


const char * Mp4ITMFRatingFromEngName( const char * engName ) 
{
    return Mp4ITMFRatingFromRatingType( Mp4RatingTypeFromEngName( engName ) );
}

const char * Mp4EngNameFromITMFRating( const char * rating ) 
{
    return Mp4EngNameFromRatingType( Mp4RatingTypeFromITMFRating( rating ) );
}

bool
Mp4VidWidthHeightDuration( float *       width,
                          float *        height,
                          int64_t *      seconds,
                          MP4FileHandle  mp4FH )
{
    if( width == NULL && height == NULL && seconds == NULL ) {
        return false;
    }
    if( mp4FH == MP4_INVALID_FILE_HANDLE ) {
        return false;
    }
    uint32_t numTracks = MP4GetNumberOfTracks( mp4FH, 0, 0 );
    for (uint32_t i = 0; i < numTracks; i++) {
        MP4TrackId trackId = MP4FindTrackId( mp4FH, i, 0, 0 );
        const char* trackType = MP4GetTrackType(mp4FH, trackId);
        if( trackType != NULL 
           && !strcmp(trackType, MP4_VIDEO_TRACK_TYPE)) {
            
            if( width ) {
                MP4GetTrackFloatProperty(mp4FH, trackId,
                                         "tkhd.width",
                                         width );
            }
            if( height ) {
                MP4GetTrackFloatProperty(mp4FH, trackId,
                                         "tkhd.height",
                                         height );
            }
            if( seconds ) {
                *seconds = MP4ConvertFromTrackDuration(mp4FH, 
                                                       trackId, 
                                                       MP4GetTrackDuration( mp4FH,
                                                                           trackId), 
                                                       MP4_MSECS_TIME_SCALE) / 1000;
            }
            return true;
        }
    }
    return false;
}