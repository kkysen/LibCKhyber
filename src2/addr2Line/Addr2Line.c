//
// Created by Khyber on 9/16/2018.
//

#include "Addr2Line.h"

static char* charsOrNull(const String* const string) {
    return string ? string->chars : NULL;
}

static BFD* initBFD(const Addr2LineArgs* const args) {
    BFD* bfd = bfd_openr(charsOrNull(args->fileName), charsOrNull(args->bfdTarget));
    if (!bfd) {
        return NULL;
    }
    
    bfd->flags |= BFD_DECOMPRESS;
    if (bfd_check_format(bfd, bfd_archive)) {
        return NULL;
    }
    if (!bfd_check_format_matches(bfd, bfd_object, NULL)) {
        return NULL; // TODO check NULL argument instead of char***
    }
    
    return bfd;
}

static Section* getSectionByName(const String* const sectionName) {

}

static const Symbol* const* const readSymbolTable(const BFD* const bfd) {
    bool dynamic = false;
    if (!(bfd->flags & HAS_SYMS)) { // NOLINT
        perror("no symbol table");
        return NULL;
    }
    ssize_t storage = bfd_get_symtab_upper_bound(bfd);
    if (!storage) {
        storage = bfd_get_dynamic_symtab_upper_bound(bfd);
        dynamic = true;
    }
    if (storage < 0) {
        perror("bfd_get_symtab_upper_bound() and bfd_get_dynamic_symtab_upper_bound(): invalid or no symbol table");
        return NULL;
    }
    const Symbol* const* const symbols = malloc((size_t) storage);
    if (!symbols) {
        perror("malloc");
        return NULL;
    }
    const ssize_t numSymbols = dynamic
                               ? bfd_canonicalize_dynamic_symtab(bfd, symbols)
                               : bfd_canonicalize_symtab(bfd, symbols);
    if (numSymbols < 0) {
        perror("no symbols");
        free((Symbol*) symbols);
        return NULL;
    }
    return symbols;
}

Addr2Line* Addr2Line_new(const Addr2LineArgs* const args) {
    Addr2Line* const this = malloc(sizeof(*this));
    if (!this) {
        perror("malloc");
        return NULL;
    }
    
    this->demangleStyle = args->demangleStyle; // TODO check use of demangleStyle
    
    BFD* const bfd = initBFD(args);
    if (!bfd) {
        return NULL;
    }
    
    const Section* section;
    if (args->sectionName) {
        section = getSectionByName(args->sectionName);
        if (!section) {
            perror("getSectionByName(): section doesn't exist");
            bfd_close(bfd);
            return NULL;
        }
    } else {
        section = NULL;
    }
    this->section = section;
    
    const Symbol* const* const symbols = readSymbolTable(bfd);
    if (!symbols) {
        perror("readSymbolTable");
        free((Section*) section);
        bfd_close(bfd);
        return NULL;
    }
    
    return this;
}

void Addr2Line_free(const Addr2Line* const this) {
    // TODO
    free((Symbol*) this->symbols);
    free((Section*) this->section);
    bfd_close(this->bfd);
}

void Addr2Line_convert(const Addr2Line* const this, StackFrame* const frame,
                       const void* const address, const String* const message) {
    frame->address = address;
    frame->message = message;
    frame->ok = false;
    return;
    // TODO
    frame->ok = true;
}