/*模块名字*/
%module Unix

%{
    #include <unistd.h>
%}

typedef unsigned int uid_t;

/* swig 封装getuid函数 */
extern uid_t getuid(void);