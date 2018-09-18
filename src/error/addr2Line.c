//
// Created by Khyber on 9/4/2018.
//

/**
 * Adapted from the addr2line command line program in GNU Binutils.
 * https://kernel.googlesource.com/pub/scm/linux/kernel/git/hjl/binutils/+/hjl/secondary/binutils/addr2line.c
 */

#include "addr2Line.h"
#include "../bfd/BinaryFileDescriptor.h"
#include "../util/utils.h"

static char* charsOrNull(const String* const string) {
    return string ? string->chars : NULL;
}

static Section* getSectionByName(const String* const sectionName) {

}

static Symbol* const* const readSymbolTable(const BFD* const bfd) {
    bool dynamic = false;
    if (!(bfd->flags & HAS_SYMS)) { // NOLINT
        return NULL;
    }
    ssize_t storage = bfd_get_symtab_upper_bound(bfd);
    if (!storage) {
        storage = bfd_get_dynamic_symtab_upper_bound(bfd);
        dynamic = true;
    }
    if (storage < 0) {
        return NULL;
    }
    const Symbol* const* const symbols = malloc((size_t) storage);
    const ssize_t numSymbols = dynamic
                               ? bfd_canonicalize_dynamic_symtab(bfd, symbols)
                               : bfd_canonicalize_symtab(bfd, symbols);
    if (numSymbols < 0) {
        return NULL;
    }
}

static String* translateAddress(
        BFD* const bfd, const Section* const section, const Addr2LineOptions* const options, const size_t i) {
    const void *const address = options->addresses[i];
    bfd_vma pc = (bfd_vma) address;
    if (bfd_get_flavour(bfd) == bfd_target_elf_flavour) {
        const struct elf_backend_data* bed = get_elf_backend_data(abfd);
        const bfd_vma sign = (bfd_vma) 1 << (bed->s->arch_size - 1);
        pc &= (sign << 1u) - 1;
        if (bed->sign_extend_vma) {
            pc = (pc ^ sign) - sign;
        }
    }
    
    String *const out = String_empty(); // TODO pre size
    if (options->showAddresses) {
        String_appendLiteral(out, "0x");
        String_ensureMoreCapacity(out, PTR_MAX_STRLEN * 2);
        // beware buffer overflow here
        bfd_sprintf_vma(bfd, out->chars, pc);
        if (options->prettyPrint) {
            String_appendLiteral(out, ": ");
        } else {
            String_appendLiteral(out, "\n");
        }
    }
    
    static bool found = FALSE;
    if (section) {
    
    } else {

    }
    
    found = FALSE;
    if (section)
        find_offset_in_section(abfd, section);
    else
        bfd_map_over_sections(abfd, find_address_in_section, NULL);
    if (!found) {
        if (with_functions)
            printf("??\n");
        printf("??:0\n");
    } else {
        while (1) {
            if (with_functions) {
                const char* name;
                char* alloc = NULL;
                name = functionname;
                if (name == NULL || *name == '\0')
                    name = "??";
                else if (do_demangle) {
                    alloc = bfd_demangle(abfd, name, DMGL_ANSI | DMGL_PARAMS);
                    if (alloc != NULL)
                        name = alloc;
                }
                printf("%s", name);
                if (pretty_print)
                    /* Note for translators:  This printf is used to join the
                       function name just printed above to the line number/
                       file name pair that is about to be printed below.  Eg:
                         foo at 123:bar.c  */
                    printf(_(" at "));
                else
                    printf("\n");
                if (alloc != NULL)
                    free(alloc);
            }
            if (base_names && filename != NULL) {
                char* h;
                h = strrchr(filename, '/');
                if (h != NULL)
                    filename = h + 1;
            }
            printf("%s:", filename ? filename : "??");
            if (line != 0) {
                if (discriminator != 0)
                    printf("%u (discriminator %u)\n", line, discriminator);
                else
                    printf("%u\n", line);
            } else
                printf("?\n");
            if (!unwind_inlines)
                found = FALSE;
            else
                found = bfd_find_inliner_info(abfd, &filename, &functionname,
                                              &line);
            if (!found)
                break;
            if (pretty_print)
                /* Note for translators: This printf is used to join the
                   line number/file name pair that has just been printed with
                   the line number/file name pair that is going to be printed
                   by the next iteration of the while loop.  Eg:
                     123:bar.c (inlined by) 456:main.c  */
                printf(_(" (inlined by) "));
        }
    }
}

static StackTrace translateAddresses(
        BFD* const bfd, const Section* const section, const Addr2LineOptions* const options) {
    
}

StackTrace addr2Line(const Addr2LineOptions* options) {
    const StackTrace error = StackTrace_invalid();
    
    const char* const fileName = charsOrNull(options->fileName);
    const char* const bfdTarget = charsOrNull(options->bfdTarget);
    const char* const sectionName = charsOrNull(options->sectionName);
    const char* const demangleStyle = charsOrNull(options->demangleStyle);
    
    BFD* bfd = bfd_openr(fileName, bfdTarget);
    if (!bfd) {
        return error;
    }
    
    bfd->flags |= BFD_DECOMPRESS;
    if (bfd_check_format(bfd, bfd_archive)) {
        return error;
    }
    if (!bfd_check_format_matches(bfd, bfd_object, NULL)) {
        return error; // TODO check NULL argument instead of char***
    }
    
    const Section* section;
    if (options->sectionName) {
        section = getSectionByName(options->sectionName);
        if (!section) {
            return error;
        }
    } else {
        section = NULL;
    }
    
    const Symbol* const* const symbols = readSymbolTable(bfd);
    if (!symbols) {
        return error;
    }
    
    const StackTrace stackTrace = translateAddresses(bfd, section, options);
    
    bfd_close(bfd);
    
    return stackTrace;
}
