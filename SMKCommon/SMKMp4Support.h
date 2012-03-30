#ifndef SMKCommon_SMKMp4Support_h_
#define SMKCommon_SMKMp4Support_h_
/**
  File:		SMKMp4Support.h
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
#include <stdint.h>
#include <mp4v2/mp4v2.h>

#define MP4_MK_Music      1
#define MP4_MK_Audiobook  2
#define MP4_MK_MusicVideo 6
#define MP4_MK_Movie      9
#define MP4_MK_TV        10
#define MP4_MK_Booklet   11
#define MP4_MK_Ringtone  14

typedef struct Mp4_MediaKind_t
{
    uint8_t stik;
    const char * english_name;
} Mp4_MediaKind_t;

extern const Mp4_MediaKind_t Mp4_MediaKinds[];

typedef struct Mp4_ContentRating_t
{
    uint8_t rtng;
    const char * english_name;
} Mp4_ContentRating_t;

extern const Mp4_ContentRating_t Mp4_ContentRatings[];

typedef struct Mp4_ITMF_rating_info
{
    const char * rating;
    const char * english_name;
} Mp4_ITMF_rating_info;

extern const Mp4_ITMF_rating_info Mp4_ITMF_Ratings[];

typedef enum Mp4_ITMF_rating_type_enum {
    MPAA_NR = 1,
    MPAA_G,
    MPAA_PG,
    MPAA_PG_13,
    MPAA_R,
    MPAA_NC_17,
    MPAA_UNRATED,
    US_TV_Y     = 9,
    US_TV_Y7,
    US_TV_G,
    US_TV_PG,
    US_TV_14,
    US_TV_MA,
    US_TV_UNRATED,
    UK_MOVIE_NR     = 17,
    UK_MOVIE_U,
    UK_MOVIE_Uc,
    UK_MOVIE_PG,
    UK_MOVIE_12,
    UK_MOVIE_12A,
    UK_MOVIE_15,
    UK_MOVIE_18,
    UK_MOVIE_R18,
    UK_MOVIE_E,
    UK_MOVIE_UNRATED,
    UK_TV_CAUTION  = 29,
    DE_MOVIE_FSK_0 = 31,
    DE_MOVIE_FSK_6,
    DE_MOVIE_FSK_12,
    DE_MOVIE_FSK_16,
    DE_MOVIE_FSK_18,
    AU_MOVIE_G_0 = 37,
    AU_MOVIE_PG,
    AU_MOVIE_M,
    AU_MOVIE_MA_15,
    AU_MOVIE_R18,
    AU_TV_P = 43,
    AU_TV_C,
    AU_TV_G,
    AU_TV_PG,
    AU_TV_M,
    AU_TV_MA15,
    AU_TV_AV15,
    AU_TV_R18,
    FR_MOVIE_TOUT_PUBLIC = 52,
    FR_MOVIE_10,
    FR_MOVIE_12,
    FR_MOVIE_16,
    FR_MOVIE_18,
    FR_MOVIE_UNRATED,
    FR_TV_10 = 59,
    FR_TV_12,
    FR_TV_16,
    FR_TV_18,
    R_UNKNOWN   = 64,
} Mp4_ITMF_rating_type;

typedef struct Mp4_GenreType_t
{
    uint8_t index;
    const char *short_name;
    const char *english_name;
} Mp4_GenreType_t;

extern const Mp4_GenreType_t Mp4_GenreTypes[];

#define Mp4_ITMF_Meaning_iTunes "com.apple.iTunes"
#define Mp4_ITMF_Name_Rating "iTunEXTC"
#define Mp4_ITMF_Name_Movie "iTunMOVI"

#if defined( __cplusplus )
extern "C" {
#endif

    MP4TagArtworkType Mp4ImageDataArtType( const void * imgData );\
    
    /* MPAA_R from "R" */
    Mp4_ITMF_rating_type Mp4RatingTypeFromEngName( const char * engName );
    /* MPAA_R from "mpaa|R|400" */
    Mp4_ITMF_rating_type Mp4RatingTypeFromITMFRating( const char * rating );
    
    /* mpaa|R|400 from MPAA_R */
    const char * Mp4ITMFRatingFromRatingType( Mp4_ITMF_rating_type type );
    /* PG-13 from MPAA_PG_13 */
    const char * Mp4EngNameFromRatingType( Mp4_ITMF_rating_type type );
    
    /* mpaa|PG-13|300| from PG-13 */
    const char * Mp4ITMFRatingFromEngName( const char * engName );
    /* PG-13 from mpaa|PG-13|300| */
    const char * Mp4EngNameFromITMFRating( const char * rating );
    
#if defined( __cplusplus )
};
#endif


#endif /* ! def SMKCommon_SMKMp4Support_h_ */
