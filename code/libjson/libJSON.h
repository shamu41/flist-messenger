#ifndef LIBJSON_H
#define LIBJSON_H

#include "Source/JSONDefs.h"  //for typedefs of functions, strings, and nodes

/*
    This is the C interface to libJSON.
 
    This file also declares various things that are needed for
    C++ programming
*/

#ifdef JSON_LIBRARY  //compiling the library, hide the interface
    #ifdef __cplusplus
	   #ifdef JSON_UNIT_TEST
		  #include "Source/JSONNode.h"
	   #endif
	   extern "C" {
    #endif
		  
		  /*
			 stuff that's in namespace libJSON
		  */
		  void json_free(void * str);
		  void json_delete(JSONNODE * node);
		  #ifdef JSON_MEMORY_MANAGE
			 void json_free_all(void);
			 void json_delete_all(void);
		  #endif
		  JSONNODE * json_parse(const json_char * json);
		  json_char * json_strip_white_space(const json_char * json);
		  #ifdef JSON_VALIDATE
			 JSONNODE * json_validate(const json_char * json);
		  #endif
		  #if defined JSON_DEBUG && !defined JSON_STDERROR
			 //When libjson errors, a callback allows the user to know what went wrong
			 void json_register_debug_callback(json_error_callback_t callback);
		  #endif
		  #ifdef JSON_MUTEX_CALLBACKS
			 #ifdef JSON_MUTEX_MANAGE
				void json_register_mutex_callbacks(json_mutex_callback_t lock, json_mutex_callback_t unlock, json_mutex_callback_t destroy, void * manager_lock);
			 #else
				void json_register_mutex_callbacks(json_mutex_callback_t lock, json_mutex_callback_t unlock, void * manager_lock);
			 #endif
			 void json_set_global_mutex(void * mutex);
			 void json_set_mutex(JSONNODE * node, void * mutex);
			 void json_lock(JSONNODE * node, int threadid);
			 void json_unlock(JSONNODE * node, int threadid);
		  #endif
		  #ifdef JSON_MEMORY_CALLBACKS
			 void json_register_memory_callbacks(json_malloc_t mal, json_realloc_t real, json_free_t fre);
		  #endif

		  
		  /*
			 stuff that's in class JSONNode
		   */
		  //ctors
		  JSONNODE * json_new_a(const json_char * name, const json_char * value);
		  JSONNODE * json_new_i(const json_char * name, long value);
		  JSONNODE * json_new_f(const json_char * name, json_number value);
		  JSONNODE * json_new_b(const json_char * name, int value);  //because C bools are ints and C++ will implicitly cast it
		  JSONNODE * json_new(char type);
		  JSONNODE * json_copy(const JSONNODE * orig);
		  JSONNODE * json_duplicate(const JSONNODE * orig);

		  //assignment
		  void json_set_a(JSONNODE * node, const json_char * value);
		  void json_set_i(JSONNODE * node, long value);
		  void json_set_f(JSONNODE * node, json_number value);
		  void json_set_b(JSONNODE * node, int value);  //because C bools are ints ane C++ will implicit
		  void json_set_n(JSONNODE * node, const JSONNODE * orig);

		  //inspectors
		  char json_type(const JSONNODE * node);
		  json_index_t json_size(const JSONNODE * node);
		  int json_empty(const JSONNODE * node);
		  json_char * json_name(const JSONNODE * node);
		  #ifdef JSON_COMMENTS
			 json_char * json_get_comment(const JSONNODE * node);
		  #endif
		  json_char * json_as_string(const JSONNODE * node);
		  long json_as_int(const JSONNODE * node);
		  json_number json_as_float(const JSONNODE * node);
		  int json_as_bool(const JSONNODE * node);
		  JSONNODE * json_as_node(const JSONNODE * node);
		  JSONNODE * json_as_array(const JSONNODE * node);
		  #ifdef JSON_BINARY
			 void * json_as_binary(const JSONNODE * node, unsigned long * size);
		  #endif
		  #ifdef JSON_WRITER
			 json_char * json_write(const JSONNODE * node);
			 json_char * json_write_formatted(const JSONNODE * node);
		  #endif

		  //modifiers
		  void json_set_name(JSONNODE * node, const json_char * name);
		  #ifdef JSON_COMMENTS
			 void json_set_comment(JSONNODE * node, const json_char * comment);
		  #endif
		  void json_clear(JSONNODE * node);
		  void json_nullify(JSONNODE * node);
		  void json_swap(JSONNODE * node, JSONNODE * node2);
		  void json_merge(JSONNODE * node, JSONNODE * node2);
		  #ifndef JSON_PREPARSE
			 void json_preparse(JSONNODE * node);
		  #endif
		  #ifdef JSON_BINARY
			 void json_set_binary(JSONNODE * node, const void * data, unsigned long length);
		  #endif
		  void json_cast(JSONNODE * node, char type);

		  //children access
		  void json_reserve(JSONNODE * node, json_index_t siz);
		  JSONNODE * json_at(JSONNODE * node, json_index_t pos);
		  JSONNODE * json_get(JSONNODE * node, const json_char * name);
		  #ifdef JSON_CASE_INSENSITIVE_FUNCTIONS
			 JSONNODE * json_get_nocase(JSONNODE * node, const json_char * name);
			 JSONNODE * json_pop_back_nocase(JSONNODE * node, const json_char * name);
		  #endif
		  void json_push_back(JSONNODE * node, JSONNODE * node2);
		  JSONNODE * json_pop_back_at(JSONNODE * node, json_index_t pos);
		  JSONNODE * json_pop_back(JSONNODE * node, const json_char * name);
		  #ifdef JSON_ITERATORS
			 JSONNODE_ITERATOR json_find(JSONNODE * node, const json_char * name);
			 #ifdef JSON_CASE_INSENSITIVE_FUNCTIONS
				JSONNODE_ITERATOR json_find_nocase(JSONNODE * node, const json_char * name);
			 #endif
			 JSONNODE_ITERATOR json_erase(JSONNODE * node, JSONNODE_ITERATOR it);
			 JSONNODE_ITERATOR json_erase_multi(JSONNODE * node, JSONNODE_ITERATOR start, JSONNODE_ITERATOR end);
			 JSONNODE_ITERATOR json_insert(JSONNODE * node, JSONNODE_ITERATOR it, JSONNODE * node2);
			 JSONNODE_ITERATOR json_insert_multi(JSONNODE * node, JSONNODE_ITERATOR it, JSONNODE_ITERATOR start, JSONNODE_ITERATOR end);
	 
			 //iterator functions
			 JSONNODE_ITERATOR json_begin(JSONNODE * node);
			 JSONNODE_ITERATOR json_end(JSONNODE * node);
		  #endif

		  //comparison
		  int json_equal(JSONNODE * node, JSONNODE * node2);

    #ifdef __cplusplus
	   }
    #endif
#else
    #ifndef __cplusplus
	   #error Using the non-library requires C++
    #endif
    #include "Source/JSONNode.h"  //not used in this file, but libJSON.h should be the only file required to use it embedded
    #include "Source/JSONWorker.h"
    #include <stdexcept>  //some methods throw exceptions

    namespace libJSON {
	   //if json is invalid, it throws a std::invalid_argument exception
	   inline static JSONNode parse(const json_string & json){
		  return JSONWorker::parse(json);
	   }
	   
	   //useful if you have json that you don't want to parse, just want to strip to cut down on space
	   inline static json_string strip_white_space(const json_string & json){
		  return JSONWorker::RemoveWhiteSpaceAndComments(json);
	   }
	   
	   //if json is invalid, it throws a std::invalid_argument exception (differs from parse because this checks the entire tree)
	   #ifdef JSON_VALIDATE
		  inline static JSONNode validate(const json_string & json){
			 return JSONWorker::validate(json);
		  }
	   #endif
	   
	   //When libjson errors, a callback allows the user to know what went wrong
	   #if defined JSON_DEBUG && !defined JSON_STDERROR
		  inline static void register_debug_callback(json_error_callback_t callback){
			 JSONDebug::register_callback(callback);
		  }
	   #endif
	   
	   #ifdef JSON_MUTEX_CALLBACKS
		  #ifdef JSON_MUTEX_MANAGE
			 inline static void register_mutex_callbacks(json_mutex_callback_t lock, json_mutex_callback_t unlock, json_mutex_callback_t destroy, void * manager_lock){
				JSONNode::register_mutex_callbacks(lock, unlock, manager_lock);
				JSONNode::register_mutex_destructor(destroy);
			 }
		  #else
			 inline static void register_mutex_callbacks(json_mutex_callback_t lock, json_mutex_callback_t unlock, void * manager_lock){
				JSONNode::register_mutex_callbacks(lock, unlock, manager_lock);
			 }
		  #endif
		  
		  inline static void set_global_mutex(void * mutex){
			 JSONNode::set_global_mutex(mutex);
		  }
	   #endif
	   
	   #ifdef JSON_MEMORY_CALLBACKS
		  inline static void register_memory_callbacks(json_malloc_t mal, json_realloc_t real, json_free_t fre){
			 JSONMemory::registerMemoryCallbacks(mal, real, fre);
		  }
	   #endif

    }
#endif  //JSON_LIBRARY

#endif  //LIBJSON_H
