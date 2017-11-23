/* --------------------------------------------------
 * Advanced C++ for JAVA Programmers - Module 7503
 * Berner Fachhochschule - Frühlingssemester 2017
 * By: Carlos Alfonso Arauz - arauc1@bfh.ch
 * --------------------------------------------------
 */
#ifndef _MEM_MNGR_H_
#define _MEM_MNGR_H_

#include <iostream>
#include <stdlib.h>
#include <new>

class MemMngr
{
public:
/* ----------------------------------- struct Node: base of the stack data structure */
    typedef struct Node
    {
        int          index;
        int          lineNumber;
        size_t       memorySize;
        void        *p;
        char const  *filename;
        struct Node *next;
    } Node;

private: // private member variables
    Node    *root;                  // control node of the stack
    int      length;                // current length of the stack
    int      totalAllocatedMemory;  // total allocated memory over current running time

public:
/* ----------------------------------- type of the (de)allocation SINGLE(for new/delete), ARRAY(for new[]/delete[]) */
    enum class AllocationType
    {
        SINGLE, ARRAY
    };

/* ----------------------------------- helping class to process __FILE__ and __LINE__ */
    class MemStamp {
    public:
        char const * const  filename;
        int const           lineNum;

        MemStamp(char const *filename, int lineNum)
                : filename(filename), lineNum(lineNum) { }
       ~MemStamp() { }
    };

/* ----------------------------------- MemMngr class is a singleton */
    static MemMngr& GetInstance()
    {
        static MemMngr INSTANCE;
        return INSTANCE;
    }

    virtual ~MemMngr(void) { } // destructor

/* ----------------------------------- memory management and stamping prototypes */
    int GetMemorySize(void);

    int GetCurrentMemorySize(void);

    int GetMemoryIndex(void *);

    void *Allocate(size_t, AllocationType);

    void Free(void *, AllocationType);

    void PrintLeaks(void);

    void Stamp(char const *, int);

private:

    MemMngr(void); // private constructor necessary for singleton

    void Init(void);

    static void AtExit(void);

/* ----------------------------------- stack management prototypes */
    void CreateList(Node **);

    Node *Create(void);

    bool Destroy(void);

    bool Destroy(Node *r);

    int InsertNode(void *, size_t);

    bool DeleteNode(void *);

    bool DeleteNodeAux(Node *, void *);

    void PrintLeaks(Node *);

    Node *FindNode(void *);

    Node *FindNode(void *, Node *);
};

#if defined(DEBUG) || defined(_DEBUG) || defined(__debug)
/* ----------------------------------- operator * (MemStamp, ptr) */
template <class T> inline T *operator*(const MemMngr::MemStamp &stamp, T *p)
{
    MemMngr &mngr = MemMngr::GetInstance();
    mngr.Stamp(stamp.filename, stamp.lineNum);
    return p;
}

/* ----------------------------------- new macro */
#define MEMMNGR_NEW MemMngr::MemStamp(__FILE__, __LINE__) * new
#define new MEMMNGR_NEW

#endif // defined(DEBUG) || defined(_DEBUG) || defined(__debug)
#endif // _MEM_MNGR_H_
