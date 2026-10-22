#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#define MAXBYTES (1u << 30) /*Esto es un GiB*/
#define NALLOC 1024
#define MAGIC ((Header *) (uintptr_t)0xDEADBEEF)

void *malloc(size_t n);
void free(void *ap);

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned int size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;
static char *heap_lo = NULL, *heap_hi = NULL;

static void err(const char *msg) {
    size_t n = 0;
    while (msg[n]) n++;
    write(2, msg, n);
}

void *malloc (size_t n) {
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned int nunits;

    nunits = (n+sizeof(Header)-1)/sizeof (Header) + 1;
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp -> s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p -> s.size >= nunits) {
            if (p -> s.size == nunits)
                prevp -> s.ptr = p -> s.ptr;
            else {
                p -> s.size -= nunits;
                p += p -> s.size;
                p ->s.size = nunits;
            }
            freep = prevp;
            return (void *) (p+1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

Header *morecore(unsigned nu) {
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu + sizeof(Header));
    if (cp == (char *) -1) 
        return NULL;
    
    if (heap_lo == NULL || cp < heap_lo)
        heap_lo = cp;
    if (cp + nu * sizeof(Header) > heap_hi)
        heap_hi = cp + nu * sizeof(Header);

    up = (Header *) cp;
    up -> s.size = nu;
    free((void *) (up + 1));
    return freep;
}

void free(void *ap) {
    Header *bp, *p;

    if (ap == NULL)
        return;
    if ((uintptr_t)ap % sizeof(Header) != 0) {
        err("Free: pointer no aliened");
        return;
    }

    bp = (Header *) ap -1;
    
    if ((char *) bp < heap_lo || (char *) (bp + 1) > heap_hi) {
        err("Free: Pointer out of heap limits");
        return;
    } 
    if (bp -> s.ptr != MAGIC) {
        err("Free: double free or invalid pointer");
        return;
    }
    if (bp -> s.size < 2 || (char *)(bp + bp -> s.size) > heap_hi) {
        err("Free: size camp corrupted");
        return;
    }

    for (p = freep; !(bp > p && bp < p -> s.ptr); p = p -> s.ptr)
        if (p >= p -> s.ptr && (bp > p || bp < p -> s.ptr))
            break;
    if(bp + bp -> s.size == p -> s.ptr) {
        bp -> s.size += p -> s.ptr->s.size;
        bp -> s.ptr = p -> s.ptr -> s.ptr;
    } else 
        bp -> s.ptr = p -> s.ptr;
    if (p + p -> s.size == bp) {
        p -> s.size += bp -> s.size;
        p -> s.ptr = bp -> s.ptr;
    } else 
        p -> s.ptr = bp;

    freep = p;
}

int main () {
    char *a = malloc(100);
    free(a);
    free(a);
    free(NULL);
    int x;
    free(&x);
    malloc(0);
    return 0;
}
