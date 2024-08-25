#include <stdio.h>
#include <getopt.h>
#include <unistd.h>

#define INPUT_FORMATS_ARG  -2
#define OUTPUT_FORMATS_ARG -3

static const char* output_msg = "This file is generated by nodoc because pandoc is not available on this system.\n";

static const char* input_formats[] = {
    "biblatex",
    "bibtex",
    "bits",
    "commonmark",
    "commonmark_x",
    "creole",
    "csljson",
    "csv",
    "docbook",
    "docx",
    "dokuwiki",
    "endnotexml",
    "epub",
    "fb2",
    "gfm",
    "haddock",
    "html",
    "ipynb",
    "jats",
    "jira",
    "json",
    "latex",
    "man",
    "markdown",
    "markdown_github",
    "markdown_mmd",
    "markdown_phpextra",
    "markdown_strict",
    "mediawiki",
    "muse",
    "native",
    "odt",
    "opml",
    "org",
    "ris",
    "rst",
    "rtf",
    "t2t",
    "textile",
    "tikiwiki",
    "tsv",
    "twiki",
    "typst",
    "vimwiki",
};

static const char* output_formats[] = {
    "asciidoc",
    "asciidoc_legacy",
    "asciidoctor",
    "beamer",
    "biblatex",
    "bibtex",
    "chunkedhtml",
    "commonmark",
    "commonmark_x",
    "context",
    "csljson",
    "docbook",
    "docbook4",
    "docbook5",
    "docx",
    "dokuwiki",
    "dzslides",
    "epub",
    "epub2",
    "epub3",
    "fb2",
    "gfm",
    "haddock",
    "html",
    "html4",
    "html5",
    "icml",
    "ipynb",
    "jats",
    "jats_archiving",
    "jats_articleauthoring",
    "jats_publishing",
    "jira",
    "json",
    "latex",
    "man",
    "markdown",
    "markdown_github",
    "markdown_mmd",
    "markdown_phpextra",
    "markdown_strict",
    "markua",
    "mediawiki",
    "ms",
    "muse",
    "native",
    "odt",
    "opendocument",
    "opml",
    "org",
    "pdf",
    "plain",
    "pptx",
    "revealjs",
    "rst",
    "rtf",
    "s5",
    "slideous",
    "slidy",
    "tei",
    "texinfo",
    "textile",
    "typst",
    "xwiki",
    "zimwiki",
};

static const struct option long_opts[] = {
    {"version", no_argument, 0, 'v'},
    {"output", required_argument, 0, 'o'},
    {"list-input-formats", no_argument, 0, INPUT_FORMATS_ARG},
    {"list-output-formats", no_argument, 0, OUTPUT_FORMATS_ARG},
    {NULL, 0, 0, 0}
};

int main(int argc, char** argv)
{
    int ret;
    opterr = 0;
    FILE* out = stdout;
    while((ret = getopt_long(argc, argv, "vo:", long_opts, NULL)) != -1)
    {
        if(ret == 'v') {
            const char* user = getlogin();
            if(!user)
                user = "unknown";

            // pypandoc needs this
            printf("pandoc 3.1.9\n"
                    "Features: +server +lua\n"
                    "Scripting engine: Lua 5.4\n"
                    "User data directory: /home/%s/.local/share/pandoc\n"
                    "Copyright (C) 2006-2023 John MacFarlane. Web: https://pandoc.org\n"
                    "This is free software; see the source for copying conditions. There is no\n"
                    "warranty, not even for merchantability or fitness for a particular purpose.\n", user);
            return 0;
        } else if (ret == INPUT_FORMATS_ARG) {
            for(size_t i = 0; i < sizeof(input_formats)/sizeof(*input_formats); i++)
                puts(input_formats[i]);
            return 0;
        } else if (ret == OUTPUT_FORMATS_ARG) {
            for(size_t i = 0; i < sizeof(output_formats)/sizeof(*output_formats); i++)
                puts(output_formats[i]);
            return 0;
        } else if(ret == 'o') {
            if(out != stdout) {
                fputs("FIXME: Multiple outputs are ignored\n", stderr);
                continue;
            }
            out = fopen(optarg, "w");
            if(!out)
                return 1;
        }
    }

    // If no files were passed, consume stdin
    if(argc - optind == 0) {
        char dummy[256];
        while(fread(dummy, 1, sizeof(dummy), stdin) == sizeof(dummy));
    }

    fputs(output_msg, out);

    // WARNING: stdout might be closed from now on
    fclose(out);
    return 0;
}
