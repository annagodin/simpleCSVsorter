/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

#define color						0
#define director_name				1
#define num_critic_for_reviews 		2
#define duration					3
#define director_facebook_likes		4
#define actor_3_facebook_likes		5
#define actor_2_name				6
#define actor_1_facebook_likes		7
#define gross						8
#define genres						9
#define actor_1_name				10
#define movie_title					11
#define num_voted_users				12
#define cast_total_facebook_likes	13
#define actor_3_name				14
#define facenumber_in_poster		15
#define plot_keywords				16
#define movie_imdb_link 			17
#define num_user_for_reviews		18
#define language					19
#define country						20
#define content_rating			 	21
#define budget						22
#define title_year					23
#define	actor_2_facebook_likes		24
#define imdb_score					25
#define aspect_ratio				26
#define movie_facebook_likes		27

int stringToInt (char* str);
char* stripNewLineChar (char* token,int tokLen);

typedef struct CSVRecord {
  char** record;
} CSVRecord;

//Suggestion: define a struct that mirrors a record (row) of the data set


//Suggestion: prototype a mergesort function


