## Description :pushpin:
Generation of an image representing the [DBLP](https::dblp.org) references database.

**Work in progress**
- Parsing of DBLP input files is done.
- Computation of final image coordinates is almost done.
- Image generation has not been made.

## Usage :zap:

Files have to be parsed with [UParser](https://github.com/skatos-ux/UParser) before running.

```bash
./projet-dblp.exe -t <list of tags>  -f <paths of files> -o <output bitmap>
```

* list of tags
: list of one or multiples XML tags to analyse

* paths of files
: paths of previously parsed XML files (view [parser repo](https://github.com/skatos-ux/UParser))

* output bitmap
: output bitmap file (not implemented)

## Examples :books:

```bash
./projet-dblp.exe -t title -f parsed_files  -o image.bmp
./projet-dblp.exe -t author -f dblp_files  -o generated.bmp
```

## IDE

[Visual Studio 2019](https://visualstudio.microsoft.com) is the IDE for this project.
