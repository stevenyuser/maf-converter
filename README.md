# maf-converter
Converts a multi alignment file (MAF) format into a dataset containing pairs of sequences that can be used in [WFA](https://github.com/smarco/WFA) or [AIM](https://github.com/safaad/aim).

MAF files can be generated using [pbsim2](https://github.com/yukiteruono/pbsim2).

Output example:
```
>GAGTCG
<GAAGTG
>GTGTGG
>GTGTTT
>GTGTGG
>GTGTAA
...
```

Usage: 
run `make` and then `./bin/converter <inputFile.maf> <outputFile>`
