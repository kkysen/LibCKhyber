//
// Created by Khyber on 9/16/2018.
//

/**
 * Adapted from the addr2line command line program in GNU Binutils.
 * https://kernel.googlesource.com/pub/scm/linux/kernel/git/hjl/binutils/+/hjl/secondary/binutils/addr2line.c
 */

#include "Addr2Line.h"

#include <libiberty/demangle.h>
#include <string.h>
#include "../../../binutils-gdb/bfd/elf-bfd.h"

#include "../util/utils.h"

static void initLibBFD() {
    static bool initialized = false;
    if (!initialized) {
        bfd_init();
    }
}

static BFD *initBFD(const Addr2LineArgs *const args) {
    BFD *bfd = bfd_openr(String_nullableChars(args->fileName), String_nullableChars(args->bfdTarget));
    if (!bfd) {
        bfd_perror("bfd_openr");
        perror("bfd_openr");
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

static const Symbol *const *readSymbolTable(const BFD *const bfd) {
    bool dynamic = false;
    if (!(bfd->flags & HAS_SYMS)) { // NOLINT
        perror("no symbol table");
        return NULL;
    }
    ssize_t storage = bfd_get_symtab_upper_bound((BFD *) bfd);
    if (!storage) {
        storage = bfd_get_dynamic_symtab_upper_bound((BFD *) bfd);
        dynamic = true;
    }
    if (storage < 0) {
        perror("bfd_get_symtab_upper_bound() and bfd_get_dynamic_symtab_upper_bound(): invalid or no symbol table");
        return NULL;
    }
    const Symbol *const *const symbols = malloc((size_t) storage);
    if (!symbols) {
        perror("malloc");
        return NULL;
    }
    const ssize_t numSymbols = dynamic
                               ? bfd_canonicalize_dynamic_symtab((BFD *) bfd, (Symbol **) symbols)
                               : bfd_canonicalize_symtab((BFD *) bfd, (Symbol **) symbols);
    if (numSymbols < 0) {
        perror("no symbols");
        free((Symbol *) symbols);
        return NULL;
    }
    return symbols;
}

Addr2Line *Addr2Line_new(const Addr2LineArgs *const args) {
    initLibBFD();
    
    Addr2Line *const this = malloc(sizeof(*this));
    if (!this) {
        perror("malloc");
        return NULL;
    }
    
    this->demangleStyle = args->demangleStyle; // TODO check use of demangleStyle
    
    BFD *const bfd = initBFD(args);
    if (!bfd) {
        perror("initBFD");
        return NULL;
    }
    this->bfd = bfd;
    
    const Section *section;
    if (args->sectionName) {
        section = bfd_get_section_by_name(bfd, args->sectionName->chars);
        if (!section) {
            perror("getSectionByName(): section doesn't exist");
            bfd_close(bfd);
            return NULL;
        }
    } else {
        section = NULL;
    }
    this->section = section;
    
    const Symbol *const *const symbols = readSymbolTable(bfd);
    if (!symbols) {
        perror("readSymbolTable");
        free((Section *) section);
        bfd_close(bfd);
        return NULL;
    }
    this->symbols = symbols;
    
    this->frame = malloc(sizeof(*this->frame));
    if (!this->frame) {
        perror("malloc");
        free((Symbol *) symbols);
        free((Section *) section);
        bfd_close(bfd);
        return NULL;
    }
    
    return this;
}

void Addr2Line_clear(const Addr2Line *const this) {
    free(this->frame);
    free((Symbol *) this->symbols);
    free((Section *) this->section);
    bfd_close(this->bfd);
}

void Addr2Line_free(const Addr2Line *const this) {
    Addr2Line_clear(this);
    free((Addr2Line *) this);
}

bfd_vma BFD_getPC(const BFD *const bfd, const void *const address) {
    bfd_vma pc = (bfd_vma) address;
    if (bfd_get_flavour(bfd) == bfd_target_elf_flavour) {
        const struct elf_backend_data *bed = get_elf_backend_data(bfd);
        const bfd_vma sign = 1u << (bed->s->arch_size - 1u);
        pc &= (sign << 1u) - 1;
        if (bed->sign_extend_vma) {
            pc = (pc ^ sign) - sign;
        }
    }
    return pc;
}

static void Addr2Line_findAddressInSection(const Addr2Line *const this, const Section *const section) {
    Addr2LineFrame *const frame = this->frame;
    if (frame->found
        || !(section->flags & (flagword) SEC_ALLOC)
        || frame->pc < section->vma
        || frame->pc >= section->vma + section->size) {
        return;
    }
    frame->found = (bool) bfd_find_nearest_line_discriminator(
            this->bfd,
            (Section *) section,
            (Symbol **) this->symbols,
            frame->pc - section->vma,
            &frame->filePath,
            &frame->functionName,
            &frame->lineNumber,
            &frame->discriminator
    );
    // TODO use discriminator, not sure for what, but it's not there for nothing
}

static void findAddressInSection(BFD *bfd ATTRIBUTE_UNUSED, Section *section, void *data) {
    Addr2Line_findAddressInSection((const Addr2Line *) data, section);
}

static bool Addr2Line_findOffsetInSection(const Addr2Line *const this) {
    Section *section = malloc(sizeof(*section));
    if (!section) {
        perror("malloc");
        return false;
    }
    memcpy(section, this->section, sizeof(*section));
    section->vma = 0;
    Addr2Line_findAddressInSection(this, section);
    return true;
}

static void StackFrame_setFile(StackFrame *const this, const char *const filePath) {
    if (!filePath) {
        this->filePath = NULL;
        this->fileName = NULL;
        return;
    }
    this->filePath = String_ofChars(filePath);
    const ssize_t i = String_rfind(this->filePath, '/');
    this->fileName = i == -1 ? NULL : String_subString(this->filePath, (size_t) i + 1, this->filePath->size);
}

static void StackFrame_copyFrame(StackFrame *const this, const Addr2LineFrame *const frame) {
    StackFrame_setFile(this, frame->filePath);
    this->mangledFunctionName = String_ofChars(frame->functionName);
    this->lineNumber = frame->lineNumber;
}

static void StackFrame_demangle(StackFrame *const this, const BFD *const bfd) {
    const char *const functionName = bfd_demangle((BFD *) bfd, this->mangledFunctionName->chars,
                                                  DMGL_ANSI | DMGL_PARAMS);
    // TODO check if other flags should be included too for more info
//    if (functionName) {
//        perror("bfd_demange");
//        exit(1);
//    }
    this->functionName = functionName ? String_ofChars(functionName) : String_copy(this->mangledFunctionName);
}

static void StackFrame_fill(StackFrame *this, Addr2LineFrame *frame, const BFD *bfd);

static void StackFrame_findInlinerInfo(StackFrame *const this, Addr2LineFrame *const frame,
                                       const BFD *const bfd) {
    this->inlinedBy = NULL;
    this->inlinedDepth = 0;
    if (!bfd_find_inliner_info((BFD *) bfd,
                               &frame->filePath, &frame->functionName, &frame->lineNumber)) {
        return;
    }
    StackFrame *const inlinedBy = malloc(sizeof(*this->inlinedBy));
    if (!inlinedBy) {
        perror("malloc");
        return;
    }
    memClear(inlinedBy);
    StackFrame_fill(inlinedBy, frame, bfd);
    this->inlinedDepth = inlinedBy->inlinedDepth + (stack_size_t) 1;
    this->inlinedBy = inlinedBy;
}

static void StackFrame_fill(StackFrame *const this, Addr2LineFrame *const frame, const BFD *const bfd) {
    StackFrame_copyFrame(this, frame);
    StackFrame_demangle(this, bfd);
    StackFrame_findInlinerInfo(this, frame, bfd);
    this->ok = true;
}

void Addr2Line_convert(const Addr2Line *const this, StackFrame *const frame,
                       const void *const address, const String *const message) {
    memClear(frame);
    memClear(this->frame);
    
    frame->address = address;
    frame->message = message;
    frame->ok = false;
    
    BFD *const bfd = this->bfd;
    const bfd_vma pc = BFD_getPC(bfd, address);
    this->frame->pc = pc;
    
    if (this->section) {
        if (!Addr2Line_findOffsetInSection(this)) {
            goto error;
        }
    } else {
        bfd_map_over_sections(this->bfd, findAddressInSection, (void *) this);
    }
    
    if (!this->frame->found) {
        goto error;
    }
    
    StackFrame_fill(frame, this->frame, bfd);
    return;
    
    error:
    /**
     * TODO
     * when the function is dynamically linked (like from libc.so),
     * Addr2Line won't work b/c the exe file isn't the main program,
     * it's the shared library.
     * message usually contains the shared library file and its address in it,
     * so I can use that
     * I'll have to open a new Addr2Line object in that case, though,
     * so I'll need to have some way of caching them.
     * I could try to just have a libc.so specific cache,
     * since that'll be the most common shared library.
     */
    frame->ok = false;
}