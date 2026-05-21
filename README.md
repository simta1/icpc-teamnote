완전히 갈아엎는 중

# ICPC Teamnote
[teamnote.pdf](/build/teamnote.pdf)

### Prerequisites
- texlive-full (latexmk, lualatex)
- uv (Python >= 3.12)

### build
```bash
uv run latexmk -pdflua -shell-escape -outdir=build teamnote.tex
```

### References
- teamnote.sty: https://github.com/ho94949/teamnote.sty