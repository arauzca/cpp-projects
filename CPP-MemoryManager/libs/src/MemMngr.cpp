/* --------------------------------------------------
 * Advanced C++ for JAVA Programmers - Module 7503
 * Berner Fachhochschule - Frühlingssemester 2017
 * By: Carlos Alfonso Arauz - arauc1@bfh.ch
 * --------------------------------------------------
 */
#include "MemMngr.h"

#if defined(DEBUG) || defined(_DEBUG) || defined(__debug)
#undef new // important at this point otherwise the overloaded new/new[] will be redefined
#endif // defined(DEBUG) || defined(_DEBUG) || defined(__debug)

MemMngr::MemMngr()
{
    Init();
    atexit(AtExit);
}

/* ------------------------------------------------- */
/* -------- memory management and stamping --------- */
/* ------------------------------------------------- */
int MemMngr::GetMemorySize()
{
    return totalAllocatedMemory;
}

int MemMngr::GetCurrentMemorySize()
{
    int memory = 0;
    Node *temp = root;

    if (temp != NULL)
    {   while (temp->next != NULL)
        {   temp    = temp->next;
            memory += temp->memorySize;
        }
    }

    return memory;
}

int MemMngr::GetMemoryIndex(void *p)
{
    Node *temp = FindNode(p);
    return temp->index;
}

void *MemMngr::Allocate(size_t size, AllocationType at)
{
    void *p = std::malloc(size);
    if (!p) { throw std::bad_alloc(); }
    int index = InsertNode(p, size);
    if (index > 0)
    {
        switch (at)
        {
            case AllocationType::SINGLE:
                std::cout << "operator new  (" << size << "):\t\t" << p << ": #" << index << std::endl;
                break;
            case AllocationType::ARRAY:
                std::cout << "operator new[](" << size << "):\t" << p << ": #" << index << std::endl;
        }
    }

    return p;
}

void MemMngr::Free(void *p, AllocationType at)
{
    std::free(p);
    int index = GetMemoryIndex(p);
    if (DeleteNode(p))
    {
        switch (at)
        {
            case MemMngr::AllocationType::SINGLE:
                std::cout << "operator delete  :\t\t" << p << ", #" << index << std::endl;
                break;
            case MemMngr::AllocationType::ARRAY:
                std::cout << "operator delete[]:\t\t" << p << ", #" << index << std::endl;
        }
    }
}

void MemMngr::PrintLeaks()
{
    Node *temp = root;

    if (temp == NULL) {std::cout << "Memory Management List wasn't initialized correctly" << std::endl;}
    else
    {
        if (temp->next == NULL) { std::cout << "No memory leaks!" << std::endl; }
        else if (temp->next != NULL) { PrintLeaks(temp); }
    }
}

void MemMngr::PrintLeaks(Node *n)
{
    if (n->next == NULL) return;
    std::cout << "#" << n->next->index << ", " << n->next->p << ", size:" << n->next->memorySize;
    if (n->next->lineNumber)
    {
        char const * text;
        int s = static_cast<int> (n->next->memorySize);
        if (s < 10) text = ",    file:";
        else if (s < 100) text = ",   file:";
        else if (s < 1000) text = ",  file:";
        else text = ", file:";

        std::cout << text << n->next->filename << ":" << n->next->lineNumber;
    }
    std::cout << std::endl;
    PrintLeaks(n->next);
}

void MemMngr::Stamp(char const *filename, int lineNum)
{
    // because new elements are always inserted at the beginning of the list...
    Node *node = root->next;
    if (node != NULL) {
        node->filename   = filename;
        node->lineNumber = lineNum;
    }
}

void MemMngr::Init()
{
    std::cout << "MemMngr::init()" << std::endl;
    CreateList(&root);

    if (root == NULL)
    {   std::cout << "Couldn't create Memory Management List, exiting programm..." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void MemMngr::AtExit()
{
    MemMngr &mngr = MemMngr::GetInstance();
    std::cout << std::endl <<
         "--------------------------------------------------------" << std::endl <<
         "MemMngr::atExit()" << std::endl <<
         "No. of memory leaks: " << mngr.length << std::endl <<
         "Total size of leaks: " << mngr.GetCurrentMemorySize() << " bytes" << std::endl <<
         "Max. memory used   : " << mngr.GetMemorySize() << " bytes" << std::endl << std::endl <<
         "Memory leaks: " << std::endl;
    mngr.PrintLeaks();
    std::cout << "--------------------------------------------------------" << std::endl;
    mngr.Destroy();
}

/* ------------------------------------------------- */
/* -------------- stack management ----------------- */
/* ------------------------------------------------- */
void MemMngr::CreateList(Node **r)
{
    *r = Create();

    if (*r == NULL) return;

    (*r)->index      = 0;
    (*r)->memorySize = 0;
    (*r)->p          = NULL;
    (*r)->next       = NULL;
}

MemMngr::Node *MemMngr::Create()
{
    Node *temp  = NULL;
    temp        = (Node *) malloc(sizeof(Node));
    return temp;
}

bool MemMngr::Destroy()
{
    return Destroy(root);
}

bool MemMngr::Destroy(Node *r)
{
    if (r == NULL) return true;
    bool everythingDeleted = true;
    while(r->next)
    {
        everythingDeleted = everythingDeleted && DeleteNode(r->next->p);
    }
    return everythingDeleted;
}

int MemMngr::InsertNode(void *p, size_t size)
{
    Node *temp = NULL;

    if (root == NULL) return 0;

    temp = Create();
    if (temp == NULL) return 0;

    temp->index      = ++length;
    temp->memorySize = size;
    temp->p          = p;
    temp->filename   = "[unknown]";
    temp->lineNumber = 0;

    // stack: inserting at the beginning of the list
    temp->next = root->next;
    root->next = temp;

    totalAllocatedMemory += size;
    return temp->index;
}

bool MemMngr::DeleteNode(void *p)
{
    return DeleteNodeAux(root, p);
}

bool MemMngr::DeleteNodeAux(Node *currP, void *p)
{
    if (currP == NULL) return false;
    if (currP->next == NULL) return false;

    if (currP->next->p == p)
    {
        Node *temp  = NULL;
        temp        = currP->next;
        currP->next = temp->next;

        std::free(temp);
        length--;
        return true;
    }
    return DeleteNodeAux(currP->next, p);
}

MemMngr::Node *MemMngr::FindNode(void *p)
{
    return FindNode(p, root);
}

MemMngr::Node *MemMngr::FindNode(void *p, Node *currP)
{
    if (currP == NULL)       return NULL;
    if (currP->next == NULL) return NULL;
    if (currP->next->p == p) return currP->next;

    return FindNode(p, currP->next);
}

/* ------------------------------------------------- */
/* ---------------- new and delete ----------------- */
/* ------------------------------------------------- */
#if defined(DEBUG) || defined(_DEBUG) || defined(__debug)
void *operator new(size_t size) throw(std::bad_alloc)
{
    MemMngr &mngr = MemMngr::GetInstance();
    return mngr.Allocate(size, MemMngr::AllocationType::SINGLE);
}

void *operator new[](size_t size) throw(std::bad_alloc)
{
    MemMngr &mngr = MemMngr::GetInstance();
    return mngr.Allocate(size, MemMngr::AllocationType::ARRAY);
}

void operator delete(void *p) throw()
{
    MemMngr &mngr = MemMngr::GetInstance();
    mngr.Free(p, MemMngr::AllocationType::SINGLE);
}

void operator delete[](void *p) throw()
{
    MemMngr &mngr = MemMngr::GetInstance();
    mngr.Free(p, MemMngr::AllocationType::ARRAY);
}
#endif // defined(DEBUG) || defined(_DEBUG) || defined(__debug)
