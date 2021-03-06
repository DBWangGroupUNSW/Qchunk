#ifndef __RAWDATA_H__
#define __RAWDATA_H__

#include <stdio.h>
#include "hashmap.h"
// In this file, we read and manage the acture raw data.
// Raw data keep the basic datas for processing.
// Firstly the data for chars.

// #define VCN_FILTER_LEN 20


typedef struct __raw_data_t{
  int  raw_q;                   // The qgram's Q for this raw.
  int  raw_doc_num;             // Raw document number 
  char **raw_doc_str;            // Raw document strings
  int  *raw_doc_len;            // Raw document string length
  int  raw_doc_max_len;         // The max length of raw data.
  int  raw_doc_min_len;         // The min length of raw data.
  int  *raw_doc_id;             // Raw document ids
  int  **raw_token_list;        // Raw token list for document
  int  *raw_token_num;          // Raw token list number
                                //  *raw_hash_table;
  int  **sorted_token_list;     // Sorted token list for document
  int  **sorted_pos_list;       // Position list for token list
  int  **sel_tokens;             /* Reserve for query */
  int  **sel_pos;               /* reserve for query */
  int  *sel_num;

#ifdef VCN_FILTER_LEN
  int **vcns;
#endif
  
  hash_t *hp;
} raw_data_t;


#ifdef VCN_FILTER_LEN
typedef int (v_bound_map_t)[256];


void init_vcn_map(int seed);
void calculate_vcn_vector(char *str, int str_len, int *vcn);
void create_vcn_vectors(raw_data_t *rp);
int vcn_filter(int *vcna, int *vcnb, int tau);
#endif

/* Build a raw data structure from a string set. */
raw_data_t * build_raw_data_from_strings(int str_num, char **str_list, int *str_len, int q);

/* Save the raw data into a files */
int save_raw_data_to_files(raw_data_t *rp, const char *filename);

/* Build a raw data structrue from saved files */
raw_data_t* build_raw_data_from_files(const char *filename);

/* Output raw data for debuging */
int raw_data_dump(FILE *fp, raw_data_t *rp);

/* Free a raw data strutrue */
void destroy_raw_data(raw_data_t *rp);


#endif
